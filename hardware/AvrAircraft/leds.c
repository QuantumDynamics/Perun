/*
 * leds.c
 *
 * Created: 2015-05-12 20:30:56
 *  Author: Novakov
 */ 

#include <avr/io.h>
#include <avr/sfr_defs.h>

#include "leds.h"

#define LED_DDR DDRD
#define LED_PORT PORTD

#define LED_RED PORTD0
#define LED_YELLOW PORTD1

void initLeds()
{
	LED_DDR |= _BV(LED_RED) | _BV(LED_YELLOW);
	
}

void red(LedStatus status)
{	
	switch(status)	
	{
		case ON:
			LED_PORT &= ~_BV(LED_RED);
			break; 	
		case OFF:
			LED_PORT |= _BV(LED_RED);
			break;	
		case TOGGLE:
			LED_PORT ^= ~_BV(LED_RED);
			break;
	}
}

void yellow(LedStatus status)
{
	switch(status)
	{
		case ON:
			LED_PORT &= ~_BV(LED_YELLOW);
			break;
		case OFF:
			LED_PORT |= _BV(LED_YELLOW);
			break;
		case TOGGLE:
			LED_PORT ^= ~_BV(LED_RED);
			break;
	}
}