#include "remote_control.h"
#include "ch.h"
#include "../Aircraft/protocol.h"
#include "fc_nrf.h"


static WORKING_AREA(remoteControlThreadArea, 128);

static Thread * remoteControlThread = NULL;

static volatile int enabled = 0;

static struct
{
	unsigned char throttle;
	unsigned char rudder;
	unsigned char elevator;
} current =
{ 0, 145, 145 };

static msg_t remoteControl(void * _)
{
	(void)_;

	unsigned char sendBuffer[TX_PLOAD_WIDTH] = {0};

	while (enabled == 1)
	{
		CreateSetFlightParametersCommand(sendBuffer, current.throttle, current.rudder, current.elevator);

		fc_transmit(sendBuffer);

		chThdSleepMilliseconds(500);
	}

	return 0;
}

void startRemoteControl(void)
{
	remoteControlThread = chThdCreateStatic(remoteControlThreadArea, sizeof(remoteControlThreadArea), NORMALPRIO, remoteControl, NULL);
	enabled = 1;
}

void stopRemoteControl(void)
{
	if (remoteControlThread != NULL)
	{
		enabled = 0;
		chThdWait(remoteControlThread);

		remoteControlThread = NULL;
	}
}

void setFlightParameters(unsigned char throttle, unsigned char rudder, unsigned char elevator)
{
	current.throttle = throttle;
	current.rudder = rudder;
	current.elevator = elevator;
}
