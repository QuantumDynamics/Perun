#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "stdlib.h"

#include "usbSetup.h"
#include "fc_spi.h"
#include "fc_nrf.h"

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
	int enginePower = atoi(argv[0]);
	//int servo1Power = ator(argv[1]);
	//int servo2Power = ator(argv[2]);

	chprintf(chp, "Setting engine power to %d\n\r", enginePower);
}

static void cmd_stop(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) argc;
	(void) argv;
	chprintf(chp, "Stopping!\n\r");
}

static void cmd_test(BaseSequentialStream *chp, int argc, char *argv[])
{
	(void) argc;
	(void) argv;

	fc_transmit("B");
}

const ShellCommand commands[] =
		{
				{ "leds", cmd_leds },
				{ "control", cmd_control },
				{ "stop", cmd_stop },
				{ "test_tx", cmd_test },
				{ NULL, NULL }
		};

