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

#define TX_ADR_WIDTH	5   // 5 unsigned chars TX(RX) address width

static WORKING_AREA(myThreadWorkingArea, 128);
NRFCallback nrfCallback;
BinarySemaphore NRFSemIRQ;

/*
 * Buffers
 */
#define NRF_BUF_SIZE 128
static uint8_t txbuf[NRF_BUF_SIZE];
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0};	// NRF receive buffer

#include "nrf_config.h"

/*
 * Set CE to high/low
 * 0 sets pin low, 1 sets pin high
 */
static void NRFSetCE(uint8_t state)
{
	if(state == 0)
		palClearPad(NRFCEPORT, NRFCEPIN);
	else
		palSetPad(NRFCEPORT, NRFCEPIN);
}

/*
 * Write byte to register
 */
static void NRFWriteReg(uint8_t reg, uint8_t val[], uint8_t size)
{
	txbuf[0]=(reg);
	memcpy(txbuf+1, val, size);

	SPISendData(&NRF_SPI, txbuf, size+1);
}

/*
 * Write byte to register
 */
static void NRFWriteSingleReg(uint8_t reg, uint8_t val)
{
	NRFWriteReg(reg, &val, 1);
}

/*
 * Read byte from register
 */
static void NRFRead(uint8_t command, uint8_t *outBuf, uint8_t size)
{
	SPIExchangeData(&NRF_SPI, &command, outBuf, size);
}


msg_t fc_nrf_update(void* arg){
	(void)arg;

	for(;;)
	{
		chBSemWait(&NRFSemIRQ);

		unsigned char status = 0;
		NRFRead(STATUS, &status, 1);    // read register STATUS's value

		if(status&RX_DR){				// if receive data ready (TX_DS) interrupt
			NRFRead(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);     // read playload to rx_buf
			NRFWriteSingleReg(FLUSH_RX, 0);           // clear RX_FIFO

			nrfCallback(rx_buf);
		}

		NRFWriteSingleReg(NRF_WRITE_REG+STATUS, status);     // clear RX_DR or TX_DS or MAX_RT interrupt flag
		chThdSleepMilliseconds(10);
	}

	return (msg_t)0;
}

// initializes NRF I/O lines
void fc_nrf_init_io(void)
{
  NRFSetCE(0);	// chip enable
}

void nrfIrqHandler(EXTDriver *extp, expchannel_t channel) {
  (void)extp;
  (void)channel;

  // DEBUG IRQ
  //palTogglePad(GPIOC, GPIOC_LED3);

  chBSemSignalI(&NRFSemIRQ);
}

// setup NRF as receiver
void fc_nrf_rx_mode(NRFCallback callback){
	fc_nrf_init_io();

	chBSemInit(&NRFSemIRQ, TRUE);

	NRFSetCE(0);

	NRFWriteReg(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
	NRFWriteSingleReg(NRF_WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + RF_CH, 40);        // Select RF channel 40
	NRFWriteSingleReg(NRF_WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); // Select same RX payload width as TX Payload width
	NRFWriteSingleReg(NRF_WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
	NRFWriteSingleReg(NRF_WRITE_REG + CONFIG, 0x0f);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:RX. RX_DR enabled..

	NRFSetCE(1);	// Set CE pin high to enable RX device
	//  This device is now ready to receive one packet of 16 unsigned chars payload from a TX device sending to address
	//  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.

	nrfCallback = callback;

	(void)chThdCreateStatic(myThreadWorkingArea, sizeof(myThreadWorkingArea), NORMALPRIO, fc_nrf_update, NULL);
}

int fc_nrf_test_spi_connection(void){
	uint8_t cmd[1] = { 0 };
	uint8_t result[1] =	{ 0 };

	cmd[0] = 0x07;

	SPIExchangeData(&NRF_SPI, cmd, result, 1);

	if (result[0] == 0xE)
		return 1;

	return 0;
}
