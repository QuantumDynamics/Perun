#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#include "leds.h"
#include "spi.h"
#include "nrf/nrf24l01.h"
#include "nrf/nrf24l01registers.h"

int main(void)
{
	uint8_t status = 0;	
	
	initLeds();
	
	red(ON);
	yellow(ON);
	
	_delay_ms(2000);
	
	red(OFF);
	yellow(OFF);
	
	_delay_ms(2000);
	
	nrf24l01_init();
	
	_delay_ms(1000);
	
	status = nrf24l01_getstatus();
	
	if((status == 0xE))
	{		
		red(ON);	
	}
	else
	{
		yellow(ON);		
	}
	
	_delay_ms(2000);
	
	red(OFF);
	yellow(OFF);
	
	nrf24l01_write_ack_payload(0);
	
	yellow(OFF);
	
    while(1)
    {
		uint8_t pipe = 0;
		uint8_t dataReady = 0;
		uint8_t recvData[32] = {0};
						
		red(OFF);
				
        //dataReady = nrf24l01_readready(&pipe);
		status = nrf24l01_getstatus();
        
        if(bit_is_set(status, NRF24L01_REG_RX_DR))
		//if(status != 0xE)
        {
	        red(ON);	        
			
			nrf24l01_read(recvData);
			
			yellow(recvData[1] == 1 ? ON : OFF);
			
			nrf24l01_writeregister(NRF24L01_REG_STATUS, _BV(6));
			nrf24l01_flushRXfifo();
			nrf24l01_write_ack_payload(0);
        }       
		
		_delay_ms(1000);		
    }
}