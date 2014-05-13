#include "mpu.h"
#include "MPU6050.h"
#include "ch.h"
#include "kalman.h"

volatile mpuValues calib;

mpuValues add(mpuValues a, mpuValues b)
{
	mpuValues r;
	r.A_X = a.A_X + b.A_X;
	r.A_Y = a.A_Y + b.A_Y;
	r.A_Z = a.A_Z + b.A_Z;

	r.G_X = a.G_X + b.G_X;
	r.G_Y = a.G_Y + b.G_Y;
	r.G_Z = a.G_Z + b.G_Z;

	return r;
}

mpuValues sub(mpuValues a, mpuValues b)
{
	mpuValues r;
	r.A_X = a.A_X - b.A_X;
	r.A_Y = a.A_Y - b.A_Y;
	r.A_Z = a.A_Z - b.A_Z;

	r.G_X = a.G_X - b.G_X;
	r.G_Y = a.G_Y - b.G_Y;
	r.G_Z = a.G_Z - b.G_Z;

	return r;
}

mpuValues divMpu(mpuValues a, int factor)
{
	mpuValues r;
	r.A_X = a.A_X / factor;
	r.A_Y = a.A_Y / factor;
	r.A_Z = a.A_Z / factor;

	r.G_X = a.G_X / factor;
	r.G_Y = a.G_Y / factor;
	r.G_Z = a.G_Z / factor;

	return r;
}

mpuValues readMotion(void)
{
	mpuValues v;
	int16_t r[6] =
			{ 0 };

	MPU6050_GetRawAccelGyro(r);

	v.A_X = r[0];
	v.A_Y = r[1];
	v.A_Z = r[2];

	v.G_X = r[3];
	v.G_Y = r[4];
	v.G_Z = r[5];

	return sub(v, calib);
}

volatile vector3f position;

static WORKING_AREA(mpuPositionUpdateWorkingArea, 128);
msg_t mpuPositionUpdate(void* arg)
{
	systime_t lastTime = 0;

	while (1)
	{
		mpuValues motion = readMotion();

		position.x = kalman_calculate((float) motion.A_X, (float) motion.G_X, 11, 0) / 2048.0;
		position.y = kalman_calculate((float) motion.A_Y, (float) motion.G_Y, 11, 1) / 2048.0;
		position.z = kalman_calculate((float) motion.A_Z, (float) motion.G_Z, 11, 2) / 2048.0;

		chThdSleepMilliseconds(10);
	}

	return 0;
}

void mpuCalibrate(void)
{
	int i;
	int count = 200;

	mpuValues sum =
	{ 0, 0, 0, 0, 0, 0 };

	for (i = 0; i < count; i++)
	{
		mpuValues v;
		int16_t r[6] =
				{ 0 };

		MPU6050_GetRawAccelGyro(r);

		v.A_X = r[0];
		v.A_Y = r[1];
		v.A_Z = r[2];

		v.G_X = r[3];
		v.G_Y = r[4];
		v.G_Z = r[5];

		sum = add(sum, v);

		chThdSleepMilliseconds(1);
	}

	calib = divMpu(sum, count);

	chThdCreateStatic(mpuPositionUpdateWorkingArea, sizeof(mpuPositionUpdateWorkingArea), NORMALPRIO, mpuPositionUpdate, NULL);
}



volatile static systime_t lastTime = 0;

vector3f readAcceleration(void)
{
	return position;
}
