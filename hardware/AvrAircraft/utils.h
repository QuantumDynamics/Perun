/*
 * utils.h
 *
 * Created: 2015-05-19 18:30:04
 *  Author: Novakov
 */ 


#ifndef UTILS_H_
#define UTILS_H_

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

uint8_t scale(uint8_t percent, uint8_t min, uint8_t max);



#endif /* UTILS_H_ */