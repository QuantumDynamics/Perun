/*
 ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
 2011,2012 Giovanni Di Sirio.

 This file is part of ChibiOS/RT.

 ChibiOS/RT is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 3 of the License, or
 (at your option) any later version.

 ChibiOS/RT is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 ---

 A special exception to the GPL can be applied should you wish to distribute
 a combined work that includes ChibiOS/RT, without being obliged to provide
 the source code for any proprietary components. See the file exception.txt
 for full details of how and when the exception can be applied.
 */

#include "ch.h"
#include "hal.h"
#include "pal.h"

#include "fc_spi.h"
#include "fc_nrf.h"

#include "usb/usbShell.h"
#include "chprintf.h"

//LED_GREEN  (4)    on PD12
//LED_ORANGE (3)    on PD13
//LED_RED    (5)    on PD14
//LED_BLUE   (6)    on PD15

int main(void)
{
	halInit();
	chSysInit();

	palSetPadMode(GPIOA, GPIOA_BUTTON, PAL_MODE_INPUT_PULLDOWN);
	palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOD, GPIOD_LED5, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPadMode(GPIOD, GPIOD_LED6, PAL_MODE_OUTPUT_PUSHPULL);

	chThdSleepSeconds(1);

	initUsbShell();

	SPIInit();

	fc_nrf_init(NULL, NRF_MODE_PTX);

	if(fc_nrf_test_spi_connection() == 1) {
		palSetPad(GPIOD, GPIOD_LED3);
	}

	while (TRUE)
	{
		palTogglePad(GPIOD, GPIOD_LED4);
		keepShellAlive();
		chThdYield();
	}
}
