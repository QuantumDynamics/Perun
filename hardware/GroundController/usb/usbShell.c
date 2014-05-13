#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "stdlib.h"
#include "string.h"

#include "usbSetup.h"
#include "fc_spi.h"
#include "fc_nrf.h"

#include "../Aircraft/protocol.h"

#include "remote_control.h"

SerialUSBDriver SDU1;

#define SHELL_WA_SIZE THD_WA_SIZE(2048)

static WORKING_AREA(shellArea, 2048);

const ShellCommand commands[];
static const ShellConfig shell_cfg =
		{ (BaseSequentialStream *) &SDU1, commands };

msg_t keepShellAlive(void)
{
	static Thread *shelltp = NULL;

	if (!shelltp)
	{
		if (SDU1.config->usbp->state == USB_ACTIVE)
		{
			shelltp = shellCreateStatic(&shell_cfg, shellArea, sizeof(shellArea), NORMALPRIO);
		}
	}
	else
	{
		if (chThdTerminated(shelltp))
		{
			chThdRelease(shelltp);
			shelltp = NULL;
		}
	}

	chThdSleepMilliseconds(500);

	return 0;
}

void initUsbShell(void)
{
	shellInit();

	sduObjectInit(&SDU1);
	sduStart(&SDU1, &serusbcfg);

	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1000);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);
}

static void cmd_leds(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) chp;
	int i;
	int leds[] =
			{ GPIOD_LED3, GPIOD_LED4, GPIOD_LED5, GPIOD_LED6 };

	for (i = 0; i < argc; i++)
	{
		int ledIndex = atoi(argv[i]);

		palTogglePad(GPIOD, leds[ledIndex]);
	}
}

static void cmd_control(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	unsigned char enginePower = atoi(argv[0]);
	unsigned char rudder = atoi(argv[1]);
	unsigned char elevator = atoi(argv[2]);

	chprintf(chp, "Engine: %d\tRudder:%d\tElevator:%d\r\n", enginePower, rudder, elevator);

	setFlightParameters(enginePower, rudder, elevator);
}

static void cmd_start(BaseSequentialStream *chp, int argc, char * argv[])
{
	(void) argc;
	(void) argv;

	chprintf(chp, "Starting remote control!\r\n");

	startRemoteControl();
}

static void cmd_stop(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	chprintf(chp, "Stopping remote control!\r\n");

	stopRemoteControl();
}

static void cmd_req(BaseSequentialStream * chp, int argc, char * argv[])
{
	(void) argc;
	(void) argv;

	unsigned char req[TX_PLOAD_WIDTH] =
			{ 0 };
	unsigned char resp[TX_PLOAD_WIDTH] =
			{ 0 };
	unsigned char s = 0;

	nrf_read_reg(STATUS, &s, 1);

	chprintf(chp, "STATUS: %X\n\r", s);

	CreateRequestStatusCommandHandler(req);

	chprintf(chp, "Requesting");
	//fc_transmit(req);
	chprintf(chp, ".");
	fc_request_reply(req, resp);

	chprintf(chp, "Received:");
	chprintf(chp, "'%s'", resp);
	chprintf(chp, "\r\n");
}

static void cmd_echo(BaseSequentialStream * chp, int argc, char * argv[])
{
	uint8_t buffer[TX_PLOAD_WIDTH] =
			{ 0 };
	uint8_t tmp = FetchFromBuffer;
	uint8_t i, len;

	buffer[0] = RequestStatus;
	len = strlen(argv[0]);

	for (i = 0; i < len; i++)
	{
		buffer[1 + i] = (argv[0])[i];
	}

	chprintf(chp, "Requested...\r\n");

	fc_transmit(buffer);

	chThdSleepMicroseconds(2000);

	chprintf(chp, "Fettching response\r\n");
	fc_request_reply(&tmp, buffer);

	chprintf(chp, "Response: %s\r\n", buffer);
}

static void cmd_acceleration(BaseSequentialStream * chp, int argc, char * argv[])
{
	uint8_t buffer[TX_PLOAD_WIDTH] =
			{ 0 };
	uint8_t fetch = FetchFromBuffer;
	uint8_t req = RequestStatus;
	uint8_t i;

	buffer[0] = RequestStatus;

	chprintf(chp, "Requested...\r\n");

	for (i = 0; i < 60; i++)
	{
		fc_transmit(&req);

		chThdSleepMicroseconds(2000);

		if(fc_request_reply(&fetch, buffer) == RETURN_OK)
		{
			chprintf(chp, "R(%d): %s\r\n", i, buffer);
		}
		else
		{
			chprintf(chp, "R(%d): Timeout\r\n", i);
		}

		chThdSleepMilliseconds(500);
	}
}

const ShellCommand commands[] =
		{
				{ "leds", cmd_leds },
				{ "control", cmd_control },
				{ "start", cmd_start },
				{ "stop", cmd_stop },
				{ "req", cmd_req },
				{ "echo", cmd_echo },
				{ "acc", cmd_acceleration },
				{ NULL, NULL }
		};

