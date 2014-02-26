#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"

#include "drivers/engine.h"
#include "fc_nrf24l01.h"
#include "fc_spi.h"

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

	palSetPad(GPIOC, GPIOC_LED3);

//	AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;

	SPIInit();

	//NRFInit();

	palClearPad(GPIOB, 4);

	cmd[0] = 0x07;
	SPIExchangeData(&NRF_SPI, cmd, result, 1);

	if (result[0] == 0xE)
	{
		palSetPad(GPIOC, GPIOC_LED4);
	}

	while (1)
	{
		chThdYield();
	}
}

