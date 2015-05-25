#include "remote_control.h"
#include "ch.h"
#include "../Aircraft/protocol.h"
#include "fc_nrf.h"
#include "chprintf.h"

extern SerialUSBDriver SDU1;

static WORKING_AREA(remoteControlThreadArea, 512);

static Thread * remoteControlThread = NULL;

static volatile int enabled = 0;

static struct
{
	unsigned char throttle;
	unsigned char rudder;
	unsigned char elevator;
} current =
{ 0, 50, 50 };

static msg_t remoteControl(void * _)
{
	(void)_;

	unsigned char sendBuffer[TX_PLOAD_WIDTH] = {0};
	unsigned char responseBuffer[TX_PLOAD_WIDTH] = {0};

	//chprintf(&SDU1, "Starting remote control\n\r");

	while (enabled == 1)
	{
		palTogglePad(GPIOD, GPIOD_LED3);
		//chprintf(&SDU1, ".");

		CreateSetFlightParametersCommand(sendBuffer, current.throttle, current.rudder, current.elevator);

		fc_request_reply(sendBuffer, responseBuffer);

		chThdSleepMilliseconds(50);
	}

	//chprintf(&SDU1, "Stopped remote control\n\r");

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
