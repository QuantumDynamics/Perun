#include <math.h>
#include <stdint.h>

uint8_t scale(uint8_t percent, uint8_t min, uint8_t max)
{	
	float range = (float)max - (float)min;
	float fraction = (float)percent / 100.0f;
	
	float rangeFraction = range * fraction;
	
	return min + floorf(rangeFraction);	
}