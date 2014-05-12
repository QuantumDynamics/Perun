#include "ch.h"
#include "hal.h"
#include "stm32f10x.h"
#include "i2c.h"

#include "drivers/engine.h"
#include "drivers/MPU6050.h"

#include "fc_nrf.h"
#include "fc_spi.h"
#include "protocol.h"

static VirtualTimer watchdog;

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
						{ EXT_CH_MODE_DISABLED, NULL }
				}
		};

static void watchdog_expired(void * _)
{
	(void) _;

	SetFlightParametersCommandHandler(0, 145, 145);
}

void callback(unsigned char buf[TX_PLOAD_WIDTH])
{
	if (chVTIsArmedI(&watchdog))
	{
		chVTReset(&watchdog);
	}

	chVTSet(&watchdog, S2ST(5), watchdog_expired, NULL);
	HandleCommand(buf);
}

unsigned char text[] = "ZBCD";

static const I2CConfig i2cCfg =
		{ OPMODE_I2C, 360000, FAST_DUTY_CYCLE_2 };

void testuj()
{

	uint8_t cond = 0;

	MPU6050_I2C_Init();

	MPU6050_Initialize();

	cond = MPU6050_TestConnection();

	if (cond)
	{
		palSetPad(GPIOC, GPIOC_LED3);
	}
	else
	{
		palSetPad(GPIOC, GPIOC_LED4);
	}

	chThdSleepSeconds(5);

	palClearPad(GPIOC, GPIOC_LED3);

	chThdSleepSeconds(2);

	cond = MPU6050_GetSleepModeStatus();

	if (cond)
	{
		palSetPad(GPIOC, GPIOC_LED3);
	}
	else
	{
		palSetPad(GPIOC, GPIOC_LED4);
	}

	chThdSleepSeconds(5);

	palClearPad(GPIOC, GPIOC_LED3);

	chThdSleepSeconds(2);

	MPU6050_SetSleepModeStatus(ENABLE);

	cond = MPU6050_GetSleepModeStatus();

	if (cond)
	{
		palSetPad(GPIOC, GPIOC_LED3);
	}
	else
	{
		palSetPad(GPIOC, GPIOC_LED4);
	}
}

int main(void)
{
	halInit();
	chSysInit();

	chThdSleepSeconds(1);

	palSetPadMode(GPIOC, GPIOC_LED3, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOC, GPIOC_LED4, PAL_MODE_OUTPUT_PUSHPULL);

	engineInit();

	AFIO->MAPR |= AFIO_MAPR_TIM3_REMAP_PARTIALREMAP;
	//AFIO ->MAPR |= AFIO_MAPR_I2C1_REMAP;

	palSetGroupMode(GPIOB, PAL_PORT_BIT(1), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(0), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
	palSetGroupMode(GPIOB, PAL_PORT_BIT(5), 0, PAL_MODE_STM32_ALTERNATE_PUSHPULL);

//TODO: TUTUAJ KURWA!!!!!!!!!!!!!
//	chThdSleepSeconds(2);
//	engineCalibrate();

	SPIInit();

	fc_nrf_init(callback, NRF_MODE_PRX);

	pwmEnableChannel(&ENGINE_PWM, 2, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + 100);
	pwmEnableChannel(&ENGINE_PWM, 1, PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 0) + 100);

	palSetPadMode(GPIOB, 10, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SCL */
	palSetPadMode(GPIOB, 11, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SDA */

	//i2cStart(&I2CD2, &i2cCfg);

	chThdSleepMilliseconds(500);

	//testuj();
	while (1)
	{
		int16_t r[6] =
		{ 0 };
		//palTogglePad(GPIOC, GPIOC_LED3);

		chThdSleepSeconds(1);

		chThdYield();


	}
}

