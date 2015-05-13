/*
nrf24l01 lib 0x02

copyright (c) Davide Gironi, 2012

References:
  -  This library is based upon nRF24L01 avr lib by Stefan Engelke
     http://www.tinkerer.eu/AVRLib/nRF24L01
  -  and arduino library 2011 by J. Coliz
     http://maniacbug.github.com/RF24

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/

#ifndef _NRF24L01_H_
#define _NRF24L01_H_

#include <avr/io.h>

//CE and CSN port definitions
#define NRF24L01_CE_DDR DDRC
#define NRF24L01_CE_PORT PORTC
#define NRF24L01_CE PC3
#define NRF24L01_CSN_DDR DDRB
#define NRF24L01_CSN_PORT PORTB
#define NRF24L01_CSN PB2

//define the spi path
#define NRF24L01_SPIPATH "../spi.h" //spi lib path

//CE and CSN functions
#define nrf24l01_CSNhi NRF24L01_CSN_PORT |= (1<<NRF24L01_CSN);
#define nrf24l01_CSNlo NRF24L01_CSN_PORT &= ~(1<<NRF24L01_CSN);
#define nrf24l01_CEhi NRF24L01_CE_PORT |=  (1<<NRF24L01_CE);
#define nrf24l01_CElo NRF24L01_CE_PORT &= ~(1<<NRF24L01_CE);

//power setup
#define NRF24L01_RF24_PA_MIN 1
#define NRF24L01_RF24_PA_LOW 2
#define NRF24L01_RF24_PA_HIGH 3
#define NRF24L01_RF24_PA_MAX 4
#define NRF24L01_RF24_PA NRF24L01_RF24_PA_MAX

//speed setup
#define NRF24L01_RF24_SPEED_250KBPS 1
#define NRF24L01_RF24_SPEED_1MBPS 2
#define NRF24L01_RF24_SPEED_2MBPS 3
#define NRF24L01_RF24_SPEED NRF24L01_RF24_SPEED_1MBPS

//crc setup
#define NRF24L01_RF24_CRC_DISABLED 1
#define NRF24L01_RF24_CRC_8 2
#define NRF24L01_RF24_CRC_16 3
#define NRF24L01_RF24_CRC NRF24L01_RF24_CRC_16

//transmission channel
#define NRF24L01_CH 40// 76

//payload lenght
#define NRF24L01_PAYLOAD 32 //16

//auto ack enabled
#define NRF24L01_ACK 1

//auto retransmit delay and count
#define NRF24L01_RETR (0b0010 << NRF24L01_REG_ARD) | (10 << NRF24L01_REG_ARC) //750uS, 10 times

//enable / disable pipe
#define NRF24L01_ENABLEDP0 1 //pipe 0
#define NRF24L01_ENABLEDP1 0 //pipe 1
#define NRF24L01_ENABLEDP2 0 //pipe 2
#define NRF24L01_ENABLEDP3 0 //pipe 3
#define NRF24L01_ENABLEDP4 0 //pipe 4
#define NRF24L01_ENABLEDP5 0 //pipe 5

//address size
#define NRF24L01_ADDRSIZE 5

//pipe address
#define NRF24L01_ADDRP0 { 0x34,0x43,0x10,0x10, 0x01} //pipe 0, 5 byte address
#define NRF24L01_ADDRP1 { 0x34,0x43,0x10,0x10, 0x02} //pipe 1, 5 byte address
#define NRF24L01_ADDRP2 { 0x34,0x43,0x10,0x10, 0x03} //pipe 2, 5 byte address
#define NRF24L01_ADDRP3 { 0x34,0x43,0x10,0x10, 0x04} //pipe 3, 5 byte address
#define NRF24L01_ADDRP4 { 0x34,0x43,0x10,0x10, 0x05} //pipe 4, 5 byte address
#define NRF24L01_ADDRP5 { 0x34,0x43,0x10,0x10, 0x06} //pipe 5, 5 byte address
//#define NRF24L01_ADDRTX {0xE8, 0xE8, 0xF0, 0xF0, 0xE2} //tx default address*/
#define NRF24L01_ADDRTX { 0x34,0x43,0x10,0x10, 0x01}

extern void nrf24l01_init();
extern uint8_t nrf24l01_getstatus();
extern uint8_t nrf24l01_readready();
extern void nrf24l01_read(uint8_t *data);
extern uint8_t nrf24l01_write(uint8_t *data);
extern void nrf24l01_setrxaddr(uint8_t channel, uint8_t *addr);
extern void nrf24l01_settxaddr(uint8_t *addr);
extern void nrf24l01_writeregister(uint8_t reg, uint8_t value);
extern void nrf24l01_write_ack_payload(uint8_t * data);
extern void nrf24l01_flushRXfifo() ;
#endif
