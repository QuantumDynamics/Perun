

#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

#include "drivers/engine.h"


int main(void)
{
	int i;

	halInit();
	chSysInit();

	/*
	 * Initializes the PWM driver 3, re-routes the TIM3 outputs, programs the
	 * pins as alternate functions.
	 * Note, the AFIO access routes the TIM3 output pins on the PC6...PC9
	 * where the LEDs are connected.
	 */

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
