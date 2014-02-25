/*
 * engine.h
 *
 *  Created on: 25-02-2014
 *      Author: Novakov
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#define ENGINE_PWM PWMD3
#define ENGINE_PWM_CHANNEL 3

void engineInit(void);
void engineCalibrate(void);
void engineThrottle(int percent);

#endif /* ENGINE_H_ */
