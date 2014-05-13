/*
 * kalman.h
 *
 *  Created on: 11-06-2013
 *      Author: Novakov
 */

#ifndef KALMAN_H_
#define KALMAN_H_

#include <stdint.h>

#define Q_ANGLE 0.001 /*<! Q Angle multiplier of the kalman filter */
#define Q_GYRO  0.003 /*<! Q Gyro multiplier of the kalman filter */
#define R_ANGLE 0.03 /*<! R Angle multiplier of the kalman filter */

float kalman_calculate(float acc, float gyro, uint16_t looptime, uint8_t key);

#endif /* KALMAN_H_ */
