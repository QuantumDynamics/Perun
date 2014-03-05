#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

#include "drivers/engine.h"
#include "fc_nrf.h"
#include "fc_spi.h"

static const EXTConfig extcfg =
{
{
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL }, NRFIRQLINECONFIG,
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL },
{ EXT_CH_MODE_DISABLED, NULL } } };

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

void callback(unsigned char buf[TX_PLOAD_WIDTH])
{
	if (((char*) buf)[1] == 65)
		palTogglePad(GPIOC, GPIOC_LED4);
}

void testRadio(void)
{
	chThdSleepSeconds(1);

	palSetPadMode(GPIOC, GPIOC_LED3, PAL_MODE_OUTPUT_PUSHPULL);palSetPadMode(GPIOC, GPIOC_LED4, PAL_MODE_OUTPUT_PUSHPULL);

	//palSetPad(GPIOC, GPIOC_LED3);

	extStart(&EXTD1, &extcfg);
	extChannelEnable(&EXTD1, 0);

	SPIInit();

	fc_nrf_rx_mode(callback);

	while (1)
	{
		chThdYield();
	}
}

static PWMConfig pwmcfg =
{ 100000, /* 100kHz PWM clock frequency.   */
2000, /* PWM period 2ms (in ticks).    */
NULL,
{
{ PWM_OUTPUT_ACTIVE_HIGH, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL } },
/* HW dependent part.*/
0, 0,
#if STM32_PWM_USE_ADVANCED
		0
#endif
	};

int main(void)
{
	halInit();
	chSysInit();

	engineInit();

	AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
	palSetGroupMode(GPIOB, PAL_PORT_BIT(0), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(1), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

//	pwmEnableChannelI(&PWMD3, 2, 1900);

//	pwmEnableChannelI(&PWMD3, 3, 1500);

//	pwmEnableChannel(&PWMD3, 2, PWM_FRACTION_TO_WIDTH(&pwmcfg, 20, 1) + 50);

	while (1)
	{
		int i;

		for (i = 50; i < 270; i++)
		{
			pwmEnableChannel(&PWMD3, 2,i);
			chThdSleepMilliseconds(50);
		}

		chThdYield();
	}
}

