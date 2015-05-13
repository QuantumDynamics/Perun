/*
 * leds.h
 *
 * Created: 2015-05-12 20:30:03
 *  Author: Novakov
 */ 


#ifndef LEDS_H_
#define LEDS_H_

typedef enum {ON, OFF,TOGGLE} LedStatus;
	
void initLeds();
	
void red(LedStatus status);
void yellow(LedStatus status);


#endif /* LEDS_H_ */