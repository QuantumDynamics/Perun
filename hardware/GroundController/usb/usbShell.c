#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "stdlib.h"

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

static void handler(unsigned char buf[TX_PLOAD_WIDTH])
{
	chprintf(&SDU1, ".");
}

static void cmd_req(BaseSequentialStream * chp, int argc, char * argv[])
{
	(void) argc;
	(void) argv;

	unsigned char buf[TX_PLOAD_WIDTH] =
	{ 0 };
	msg_t readResult = 0;

	chprintf(chp, "Requesting...\r\n");

	CreateRequestStatusCommandHandler(buf);

	fc_transmit_and_wait(buf);

//	fc_nrf_rx_mode(NULL);
	fc_set_as_rx();

	chprintf(chp, "In RX\r\n");

	while (1)
	{
		unsigned char status = 0;
		NRFRead(STATUS, &status, 1);

		chprintf(chp, "%x ",status);

		chThdSleepMilliseconds(10);
	}

//	fc_sync_read(buf);

	chThdSleepSeconds(10);

	fc_nrf_tx_mode();

	chprintf(chp, "Received: ");
	chprintf(chp, buf);
	chprintf(chp, "\r\n");
}

const ShellCommand commands[] =
		{
				{ "leds", cmd_leds },
				{ "control", cmd_control },
				{ "start", cmd_start },
				{ "stop", cmd_stop },
				{ "req", cmd_req },
				{ NULL, NULL }
		};

