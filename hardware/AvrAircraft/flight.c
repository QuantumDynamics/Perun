#include <avr/io.h>
#include <util/delay.h>

#include "flight.h"
#include "leds.h"
#include "utils.h"

PwmOutput elevatorPwm = { .min = 9, .max = 40, .registry = &OCR0A};
PwmOutput rudderPwm = { .min = 8, .max = 42, .registry = &OCR0B};
	
PwmOutput throttlePwm = { .min = 16, .max = 32, .registry = &OCR1AL};

void setPwm(PwmOutput * pwm, int percent)
{
	*(pwm->registry) = scale(percent, pwm->min, pwm->max);
}

void initializeFlightControls()
{
	DDRD |= _BV(PORTD6) | _BV(PORTD5);
	
	TCCR0A = _BV(COM0A1) | _BV(COM0B1) |_BV(WGM01) | _BV(WGM00);
	TCCR0B = _BV(CS01) | _BV(CS00);
	
	OCR0A = 25;
	OCR0B = 30;
	
	TCCR1A = _BV(COM1A1) | _BV(WGM11);
	TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11) | _BV(CS10);
	ICR1 = 157;

	DDRB |= _BV(PORTB1);	
}

void calibrate()
{
	setPwm(&throttlePwm, 100);
	
	red(OFF);
	yellow(OFF);
	
	_delay_sec(3);
	
	red(ON);
	yellow(ON);
	
	_delay_sec(2);
	
	yellow(OFF);
	
	setPwm(&throttlePwm, 0);
	_delay_sec(2);
	
	red(OFF);
	yellow(OFF);	
}

void setFlightParams(uint8_t throttle, uint8_t elevator, uint8_t rudder)
{	
	setPwm(&throttlePwm, throttle);
	setPwm(&elevatorPwm, elevator);
	setPwm(&rudderPwm, rudder);	
}