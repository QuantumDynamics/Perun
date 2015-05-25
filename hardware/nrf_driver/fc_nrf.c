/*
 * fc_nrf.c
 *
 *  Created on: 13-12-2012
 *      Author: Kamil Maciejczek
 */

#include "fc_nrf.h"
#include "ch.h"
#include "hal.h"
#include <string.h>
#include "fc_spi.h"
#include "chprintf.h"

extern SerialUSBDriver SDU1;

#define TX_ADR_WIDTH	5   // 5 unsigned chars TX(RX) address width
static WORKING_AREA(myThreadWorkingArea, 128);
NRFCallback nrfCallback;
BinarySemaphore NRFSemIRQ;

/*
 * Buffers
 */
#define NRF_BUF_SIZE 128
static uint8_t txbuf[NRF_BUF_SIZE];
unsigned char rx_buf[TX_PLOAD_WIDTH] =
		{ 0 };	// NRF receive buffer

unsigned char tx_buf[TX_PLOAD_WIDTH] = "A";

#include "nrf_config.h"

/*
 * Set CE to high/low
 * 0 sets pin low, 1 sets pin high
 */
static void NRFSetCE(uint8_t state)
{
	if (state == 0)
		palClearPad(NRFCEPORT, NRFCEPIN);
	else
		palSetPad(NRFCEPORT, NRFCEPIN);
}

/*
 * Write byte to register
 */
static void NRFWriteReg(uint8_t reg, uint8_t val[], uint8_t size)
{
	txbuf[0] = (reg);
	memcpy(txbuf + 1, val, size);

	SPISendData(&NRFSPI, txbuf, size + 1);
}

/*
 * Write byte to register
 */
void NRFWriteSingleReg(uint8_t reg, uint8_t val)
{
	NRFWriteReg(reg, &val, 1);
}


void nrf_read_reg(uint8_t reg, uint8_t * out, uint8_t recvSize)
{
	uint8_t input[1] =
	{ reg };

	SPIWriteRead(&NRFSPI, input, 1, out, recvSize);
}

msg_t fc_nrf_update(void* arg)
{
	(void) arg;

	for (;;)
	{
		//chBSemWait(&NRFSemIRQ);

		unsigned char status = 0;
		nrf_read_reg(STATUS, &status, 1);    // read register STATUS's value

		if (status & RX_DR)
		{				// if receive data ready (TX_DS) interrupt
			nrf_read_reg(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);     // read playload to rx_buf
			NRFWriteSingleReg(FLUSH_RX, 0);           // clear RX_FIFO
			//NRFWriteSingleReg(NRF_WRITE_REG + STATUS, status);

			nrfCallback(rx_buf);
		}

		//chBSemReset(&NRFSemIRQ, TRUE);

		NRFWriteSingleReg(NRF_WRITE_REG + STATUS, status);     // clear RX_DR or TX_DS or MAX_RT interrupt flag
		chThdSleepMilliseconds(10);
	}

	return (msg_t) 0;
}

// initializes NRF I/O lines
void fc_nrf_init_io(void)
{
	NRFSetCE(0);	// chip enable
}

#if HAL_USE_EXT
void nrfIrqHandler(EXTDriver *extp, expchannel_t channel)
{
	(void)extp;
	(void)channel;

	// DEBUG IRQ
	//palTogglePad(GPIOC, GPIOC_LED3);

	chBSemSignalI(&NRFSemIRQ);
}

#endif

void fc_nrf_init(NRFCallback callback, unsigned char mode)
{
	unsigned char feature = 0;

	fc_nrf_init_io();

	chBSemInit(&NRFSemIRQ, TRUE);

	NRFSetCE(0);

	NRFWriteSingleReg(NRF_WRITE_REG + FEATURE, NRF_FEATURE_EN_DPL | NRF_FEATURE_PAYLOAD_WITH_ACK);

	nrf_read_reg(FEATURE, &feature, 1);

	if (((feature & NRF_FEATURE_EN_DPL) == 0) || ((feature & NRF_FEATURE_PAYLOAD_WITH_ACK) == 0))
	{
		NRFWriteSingleReg(ACTIVATE, ACTIVATE_ARG);

		NRFWriteSingleReg(NRF_WRITE_REG + FEATURE, NRF_FEATURE_EN_DPL | NRF_FEATURE_PAYLOAD_WITH_ACK);
	}

	NRFWriteReg(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
	NRFWriteReg(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // RX_Addr0 same as TX_Adr for Auto.Ack

	NRFWriteSingleReg(NRF_WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + SETUP_RETR, NRF_SETUP_RETR_750 | 10); // 500us + 86us, 10 retrans...
	NRFWriteSingleReg(NRF_WRITE_REG + RF_CH, 40);        // Select RF channel 40
	NRFWriteSingleReg(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); // Select same RX payload width as TX Payload width
	NRFWriteSingleReg(NRF_WRITE_REG + RF_SETUP, NRF_RF_SETUP_LNA_HCURR | NRF_RF_SETUP_PWR_0_dB);   // TX_PWR:0dBm, Datarate:1Mbps, LNA:HCURR
	NRFWriteSingleReg(NRF_WRITE_REG + CONFIG, mode | NRF_CFG_PWR_UP | NRF_CFG_CRCO | NRF_CFG_EN_CRC);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:TX. MAX_RT & TX_DS enabled..

	NRFWriteSingleReg(DYNPD, 0x01);

	if (mode == NRF_MODE_PRX)
	{
		NRFSetCE(1);
	}

	if (callback != NULL)
	{
		nrfCallback = callback;

		(void) chThdCreateStatic(myThreadWorkingArea, sizeof(myThreadWorkingArea), NORMALPRIO, fc_nrf_update, NULL);
	}
}

int fc_nrf_test_spi_connection(void)
{
	uint8_t cmd[1] =
			{ 0 };
	uint8_t result[1] =
			{ 0 };

	cmd[0] = 0x07;

	SPIExchangeData(&NRFSPI, cmd, result, 1);

	if (result[0] == 0xE)
		return 1;

	return 0;
}

void fc_transmit(unsigned char buffer[TX_PLOAD_WIDTH])
{
	unsigned char sstatus = 0;

	memcpy(tx_buf, buffer, TX_PLOAD_WIDTH);

	NRFWriteSingleReg(FLUSH_TX, 0);
	NRFWriteSingleReg(NRF_WRITE_REG + STATUS, RX_DR | TX_DS | MAX_RT);

	NRFWriteReg(WR_TX_PLOAD, tx_buf, TX_PLOAD_WIDTH);       // write playload to TX_FIFO

	NRFSetCE(1);
	chThdSleepMicroseconds(100);
	NRFSetCE(0);
}

uint8_t fc_request_reply(unsigned char requestBuffer[TX_PLOAD_WIDTH], unsigned char responseBuffer[TX_PLOAD_WIDTH])
{
	fc_transmit(requestBuffer);

	unsigned char status = 0;

	systime_t startedAt = chTimeNow();

	while (chTimeElapsedSince(startedAt) < MS2ST(500))
	{
		nrf_read_reg(STATUS, &status, 1);

		if(status & MAX_RT)
		{
			palSetPad(GPIOD, GPIOD_LED6);
		}
		else
		{
			palClearPad(GPIOD, GPIOD_LED6);
		}

		if (status & TX_DS)
		{
			if (status & RX_DR)
			{
				palTogglePad(GPIOD, GPIOD_LED5);
			}

			nrf_read_reg(RD_RX_PLOAD, responseBuffer, TX_PLOAD_WIDTH);
			NRFWriteSingleReg(FLUSH_RX, 0);

			NRFWriteSingleReg(NRF_WRITE_REG + STATUS, status);

			return RETURN_OK;
		}

		chThdYield();
	}

	return ERROR_TIMEOUT;
}

void fc_put_ack_payload(unsigned char buffer[TX_PLOAD_WIDTH])
{
	NRFWriteReg(WR_ACK_PAYLOAD, buffer, TX_PLOAD_WIDTH);
}
