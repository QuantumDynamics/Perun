#ifndef MPU_H
#define MPU_H

#include <stdint.h>
#include <protocol.h>

typedef struct
{
	int16_t A_X;
	int16_t A_Y;
	int16_t A_Z;

	int16_t G_X;
	int16_t G_Y;
	int16_t G_Z;
} mpuValues;


extern volatile mpuValues calib;

mpuValues add(mpuValues a, mpuValues b);
mpuValues sub(mpuValues a, mpuValues b);
mpuValues divMpu(mpuValues a, int factor);

mpuValues readMotion(void);
void mpuCalibrate(void);

vector3f readAcceleration(void);

#endif
