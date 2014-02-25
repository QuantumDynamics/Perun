#include "engine.h"

#include "hal.h"

static int throttleMin;
static int throttleMax;

static PWMConfig pwmcfg =
{ 100000, /* 100kHz PWM clock frequency.   */
2000, /* PWM period 2ms (in ticks).    */
NULL,
{
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_DISABLED, NULL },
{ PWM_OUTPUT_ACTIVE_HIGH, NULL } },
/* HW dependent part.*/
0, 0,
#if STM32_PWM_USE_ADVANCED
		0
#endif
	};

void engineInit()
{
	pwmStart(&ENGINE_PWM, &pwmcfg);

	throttleMin = PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 1);
	throttleMax = PWM_FRACTION_TO_WIDTH(&ENGINE_PWM, 20, 2);
}

void engineCalibrate()
{
	pwmEnableChannelI(&ENGINE_PWM, ENGINE_PWM_CHANNEL, throttleMax);
	chThdSleepSeconds(2);

	pwmEnableChannelI(&ENGINE_PWM, ENGINE_PWM_CHANNEL, throttleMin);
	chThdSleepSeconds(2);
}

void engineThrottle(int percent)
{
	pwmEnableChannel(&ENGINE_PWM, ENGINE_PWM_CHANNEL, throttleMin + percent);
}
