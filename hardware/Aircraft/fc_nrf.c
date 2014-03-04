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

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

#define NRF_PORT_CE			5	// NRF chip enable port pin

/*
 * Buffers
 */
#define NRF_BUF_SIZE 128
static uint8_t txbuf[NRF_BUF_SIZE];
unsigned char rx_buf[TX_PLOAD_WIDTH] = {0};	// NRF receive buffer

/*
 * Set CE to high/low
 * 0 sets pin low, 1 sets pin high
 */
static void NRFSetCE(uint8_t state)
{
	if(state == 0){
		palClearPad(GPIOB, 4);
	} else {
		palSetPad(GPIOB, 4);
	}
}


/*
 * Toggle LED 2
 */
static void ledtoggle2(void){
	palTogglePad(GPIOC, GPIOC_LED4);
}

/*
 * Write byte to register
 */
static void NRFWriteReg(uint8_t reg, uint8_t val[], uint8_t size)
{
	txbuf[0]=(reg);
	memcpy(txbuf+1, val, size);

	SPISendData(&SPID1, txbuf, size+1);
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
	SPIExchangeData(&SPID1, &command, outBuf, size);
}


// Define a static transmit address
unsigned char TX_ADDRESS[TX_ADR_WIDTH]  =
{
  0x34,0x43,0x10,0x10,0x01
};

// NRF main procedure
// polling actual status of device, receive and parse values of gyroscope and accelerometer voltages

BinarySemaphore NRFSemIRQ;

msg_t fc_nrf_update(void *arg)
{
	// gyroscope and accelerometer voltages
	float gyro, acc_x, acc_y, acc_z;
	gyro = acc_x = acc_y = acc_z = 0.0f;

	for(;;)
	{

		chBSemWait(&NRFSemIRQ);

		unsigned char status = 0;
		NRFRead(STATUS, &status, 1);     // read register STATUS's value
		if(status&RX_DR)     // if receive data ready (TX_DS) interrupt
		{
		  NRFRead(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);     // read playload to rx_buf
		  NRFWriteSingleReg(FLUSH_RX,0);           // clear RX_FIFO

		  // parse data
		  memcpy(&gyro, sizeof(unsigned char)+rx_buf, sizeof(float));
		  memcpy(&acc_x, sizeof(unsigned char)+rx_buf+sizeof(float), sizeof(float));
		  memcpy(&acc_y, sizeof(unsigned char)+rx_buf+2*sizeof(float), sizeof(float));
		  memcpy(&acc_z, sizeof(unsigned char)+rx_buf+3*sizeof(float), sizeof(float));

		  //status &= ~RX_DR;

		  //if(strcmp(rx_buf, "A") == 0)
		  if(((char*)rx_buf)[1] == 65)
		  	  ledtoggle2();
		}
		NRFWriteSingleReg(NRF_WRITE_REG+STATUS, status);     // clear RX_DR or TX_DS or MAX_RT interrupt flag
		chThdSleepMilliseconds(30);
	}

	return (msg_t)0;
}

// initializes NRF I/O lines
void fc_nrf_init_io(void)
{
  palClearPad(GPIOC, 4); // IRQ
  NRFSetCE(0);	// chip enable
}

// setup NRF as receiver
void fc_nrf_rx_mode(void)
{
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

	NRFSetCE(1);                             // Set CE pin high to enable RX device
	//  This device is now ready to receive one packet of 16 unsigned chars payload from a TX device sending to address
	//  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.
}
