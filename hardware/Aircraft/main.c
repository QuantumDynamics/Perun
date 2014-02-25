#include "ch.h"
#include "hal.h"

int main(void)
{
	halInit();
	chSysInit();

	palSetPadMode(GPIOC, GPIOC_LED3, PAL_MODE_OUTPUT_PUSHPULL);

	while (TRUE)
	{
		chThdSleep(500);
		palTogglePad(GPIOC, GPIOC_LED3);
		chThdYield();
	}
}
