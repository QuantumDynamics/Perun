#ifndef FLIGHT_H_
#define FLIGHT_H_

#include <stdint.h>

typedef struct 
{
	uint8_t min; 
	uint8_t max; 
	volatile uint8_t * registry;
} PwmOutput;

extern PwmOutput elevatorPwm;
extern PwmOutput rudderPwm;
extern PwmOutput throttlePwm;

void setPwm(PwmOutput * pwm, int percent);

void initializeFlightControls();

void setFlightParams(uint8_t throttle, uint8_t elevator, uint8_t rudder);

#endif /* FLIGHT_H_ */