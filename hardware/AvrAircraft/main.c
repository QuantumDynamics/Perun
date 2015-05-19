#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#include "leds.h"
#include "spi.h"
#include "nrf/nrf24l01.h"
#include "nrf/nrf24l01registers.h"
#include <math.h>

uint8_t servoValue(uint8_t percent)
{
	const uint8_t min = 15;
	const uint8_t max = 31;
	
	float range = (float)max - (float)min;
	float fraction = (float)percent / 100.0f;
	
	float rangeFraction = range * fraction;
	
	return min + floorf(rangeFraction);
}

void engine(uint8_t percent)
{
	OCR1A = servoValue(percent);
}


void setFlightParams(uint8_t throttle, uint8_t elevator, uint8_t rudder)
{	
	OCR0A = servoValue(elevator);
	OCR0B = servoValue(rudder);
	
	engine(throttle);
}

static inline void _delay_sec(uint8_t count)
{	
	uint8_t i = 0;
	for(i = 0; i < count; i++)
	{		
		_delay_ms(250);	
		_delay_ms(250);	
		_delay_ms(250);	
		_delay_ms(250);	
	}	
}

int main(void)
{
	uint8_t status = 0;	
	
	initLeds();
		
	DDRD |= _BV(PORTD6) | _BV(PORTD5);
	
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) |_BV(WGM01) | _BV(WGM00);
	TCCR0B = _BV(CS01) | _BV(CS00);
	
	OCR0A = 25;
	OCR0B = 30;
	
	TCCR1A = _BV(COM1A1) | _BV(WGM11);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11) | _BV(CS10);
	ICR1 = 157;	

	DDRB |= _BV(PORTB1);
	
	OCR1A = 31;
	
	red(OFF);
	yellow(OFF);
	
	_delay_sec(3);
	
	red(ON);
	yellow(ON);	
	
	OCR1A = 31;
	_delay_sec(2);
	
	yellow(OFF);
	
	OCR1A = 15;
	_delay_sec(2);	
	
	OCR1A = 15;
	
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
			
			if(recvData[0] == 4)
			{
				yellow(ON);
				uint8_t throttle = recvData[1];
				uint8_t rudder = recvData[2];
				uint8_t elevator = recvData[3];
				
				setFlightParams(throttle, elevator, rudder);				
			}
			
			nrf24l01_writeregister(NRF24L01_REG_STATUS, _BV(6));
			nrf24l01_flushRXfifo();
			nrf24l01_write_ack_payload(0);
        }       
		
		_delay_ms(100);		
    }
}