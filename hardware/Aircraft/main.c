#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

#include "drivers/engine.h"
#include "fc_nrf.h"
#include "fc_spi.h"
#include "protocol.h"

static const EXTConfig extcfg =
{
		{
				{ EXT_CH_MODE_DISABLED, NULL },
				{ EXT_CH_MODE_DISABLED, NULL },
				{ EXT_CH_MODE_DISABLED, NULL },
				{ EXT_CH_MODE_DISABLED, NULL },
				{ EXT_CH_MODE_DISABLED, NULL },
				NRFIRQLINECONFIG,
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
				{ EXT_CH_MODE_DISABLED, NULL }
		}
};

void testEngine(void)
{
	int i;

	engineInit();

	AFIO ->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
	palSetGroupMode(GPIOB, PAL_PORT_BIT(1), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(0), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(5), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

	chThdSleepSeconds(2);

	engineCalibrate();

	/*while (TRUE)
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
	 }*/
}

void callback(unsigned char buf[TX_PLOAD_WIDTH])
{
	//if(((char*)buf)[1] == 65)
	//	palTogglePad(GPIOC, GPIOC_LED4);

	HandleCommand(++buf);
}

int main(void)
{
	halInit();
	chSysInit();

	chThdSleepSeconds(1);

	palSetPadMode(GPIOC, GPIOC_LED3, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, GPIOC_LED4, PAL_MODE_OUTPUT_PUSHPULL);

	testEngine();

	extStart(&EXTD1, &extcfg);
	extChannelEnable(&EXTD1, 0);

	SPIInit();

	fc_nrf_rx_mode(callback);

	pwmEnableChannel(&ENGINE_PWM, 2, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + 100);
	pwmEnableChannel(&ENGINE_PWM, 1, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + 100);

	while (1)
	{
		palTogglePad(GPIOC, GPIOC_LED3);

		chThdSleepSeconds(1);

		chThdYield();
	}
}

