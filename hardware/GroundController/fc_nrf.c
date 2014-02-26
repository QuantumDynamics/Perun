/*
 * fc_nrf.c
 *
 *  Created on: 13-12-2012
 *      Author: terianil
 */

#include "fc_nrf.h"
#include "ch.h"
#include "hal.h"
#include <string.h>
#include "fc_spi.h"

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

#define NRF_PORT_CE			5	// NRF chip enable port pin

// NRF transmit buffer
volatile unsigned char tx_buf[TX_PLOAD_WIDTH] = "1234567890123456789012345678900";

// extern declarations of acceleration and rotation values
extern float accel_x;
extern float accel_y;
extern float accel_z;
extern float gyro;

/*
 * Set CE to high/low
 * 0 sets pin low, 1 sets pin high
 */
static void NRFSetCE(uint8_t state)
{
	if(state == 0){
		palClearPad(GPIOB, 1);
	} else {
		palSetPad(GPIOB, 1);
	}
}

/*
 * Buffers
 */
#define NRF_BUF_SIZE 128
// SPI NRF transmit buffer
static uint8_t txbuf[NRF_BUF_SIZE];

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

static void NRFRead(uint8_t command, uint8_t *outBuf, uint8_t size)
{
	SPIExchangeData(&SPID1, &command, outBuf, size);
}

// NRF transmit address
unsigned char TX_ADDRESS[TX_ADR_WIDTH]  =
{
  0x34,0x43,0x10,0x10,0x01
}; // Define a static TX address

// NRF main function
// copy voltage values of acceleration and rotation into NRF package
// and send it over pooling implementation of NRF driver
void fc_nrf_update()
{
  for(;;)
  {
    unsigned char sstatus = 0;
    NRFRead(STATUS, &sstatus, 1); // read register STATUS's value

    // copy acceleration data into transmit buffer
    memcpy(tx_buf + 0, &gyro, sizeof(gyro));
    memcpy(tx_buf + 1*sizeof(accel_x), &accel_x, sizeof(accel_x));
    memcpy(tx_buf + 2*sizeof(accel_x), &accel_y, sizeof(accel_y));
    memcpy(tx_buf + 3*sizeof(accel_x), &accel_z, sizeof(accel_z));

    if(sstatus&TX_DS)    // if receive data ready (TX_DS) interrupt
    {
    	NRFWriteSingleReg(FLUSH_TX,0);
    	NRFWriteReg(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);       // write playload to TX_FIFO
    }
    if(sstatus&MAX_RT)  // if receive data ready (MAX_RT) interrupt, this is retransmit than  SETUP_RETR
    {
    	NRFWriteSingleReg(FLUSH_TX,0);
    	NRFWriteReg(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);      // disable standy-mode
    }
    NRFWriteSingleReg(NRF_WRITE_REG+STATUS,sstatus);  // clear RX_DR or TX_DS or MAX_RT interrupt flag

    break;
  }
}

// initialize I/O operations with NRF
void fc_nrf_init_io(void)
{
  NRFSetCE(0);			// chip enable
}

// setup NRF transmit mode
void fc_nrf_tx_mode(void)
{
	fc_nrf_init_io();

	NRFSetCE(0);

	NRFWriteReg(NRF_WRITE_REG + TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);    // Writes TX_Address to nRF24L01
	NRFWriteReg(NRF_WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // RX_Addr0 same as TX_Adr for Auto.Ack

	NRFWriteSingleReg(NRF_WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
	NRFWriteSingleReg(NRF_WRITE_REG + SETUP_RETR, 0x1a); // 500us + 86us, 10 retrans...
	NRFWriteSingleReg(NRF_WRITE_REG + RF_CH, 40);        // Select RF channel 40
	NRFWriteSingleReg(NRF_WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
	NRFWriteSingleReg(NRF_WRITE_REG + CONFIG, 0x0e);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:TX. MAX_RT & TX_DS enabled..
	NRFWriteReg(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);

	NRFSetCE(1);
}
