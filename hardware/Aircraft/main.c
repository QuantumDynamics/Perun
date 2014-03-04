#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

#include "drivers/engine.h"
#include "fc_nrf.h"
#include "fc_spi.h"

extern BinarySemaphore NRFSemIRQ;

static void extcb1(EXTDriver *extp, expchannel_t channel) {
  static VirtualTimer vt4;

  (void)extp;
  (void)channel;

  palTogglePad(GPIOC, GPIOC_LED3);

  chSysLockFromIsr();

  chBSemSignalI(&NRFSemIRQ);

  chSysUnlockFromIsr();
}

static const EXTConfig extcfg = {
  {
	{EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb1},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

void testEngine(void)
{
	int i;

	engineInit();

	AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
	palSetGroupMode(GPIOB, PAL_PORT_BIT(1), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

	chThdSleepSeconds(2);

	engineCalibrate();

	while (TRUE)
	{
		for (i = 0; i <= 100; i += 1)
		{
			engineThrottle(i);
			chThdSleepMilliseconds(250);
		}

		chThdSleepSeconds(2);

		for (i = 100; i >= 0; i -= 1)
		{
			engineThrottle(i);
			chThdSleepMilliseconds(250);
		}

		chThdSleepSeconds(2);
	}
}

static WORKING_AREA(myThreadWorkingArea, 128);

int main(void)
{
	uint8_t cmd[1] =
	{ 0 };
	uint8_t result[1] =
	{ 0 };

	halInit();
	chSysInit();

	chThdSleepSeconds(1);

	palSetPadMode(GPIOC, GPIOC_LED3, PAL_MODE_OUTPUT_PUSHPULL); palSetPadMode(GPIOC, GPIOC_LED4, PAL_MODE_OUTPUT_PUSHPULL);

	//palSetPad(GPIOC, GPIOC_LED3);

	extStart(&EXTD1, &extcfg);
	extChannelEnable(&EXTD1, 0);

//	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;

	SPIInit();

	cmd[0] = 0x07;
	SPIExchangeData(&SPID1, cmd, result, 1);

	if (result[0] == 0xE)
		palSetPad(GPIOC, GPIOC_LED4);
	else
		return;

	fc_nrf_rx_mode();

	fc_nrf_update();

	(void)chThdCreateStatic(myThreadWorkingArea, sizeof(myThreadWorkingArea),
	                          NORMALPRIO, fc_nrf_update, NULL);

	while (1)
	{
		chThdYield();
	}
}

