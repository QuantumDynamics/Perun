/*
 * nrf_config.h
 *
 *  Created on: 03-04-2014
 *      Author: Novakov
 */

#ifndef NRF_CONFIG_H_
#define NRF_CONFIG_H_

#define CE       1
// CE_BIT:   Digital Input     Chip Enable Activates RX or TX mode

#define CSN      9
// CSN BIT:  Digital Input     SPI Chip Select

#define IRQ      10
// IRQ BIT:  Digital Output    Maskable interrupt pin

#define NRFSPI SPID1

#define NRFCEPORT GPIOB
#define NRFCEPIN 1

#define NRFIRQPORT GPIOB
#define NRFIRQPIN 0

static unsigned char TX_ADDRESS[TX_ADR_WIDTH] =
		{
				0x34, 0x43, 0x10, 0x10, 0x01
		};

#endif /* NRF_CONFIG_H_ */
