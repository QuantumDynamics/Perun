/*
 * spi_config.h
 *
 *  Created on: 03-04-2014
 *      Author: Novakov
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

static const SPIConfig hs_spicfg =
{ NULL, GPIOA, GPIOA_SPI1NSS, HIGHSPEED_SPI_DIV };

static inline void ConfigureSPIPins(void)
{
	palSetPadMode(GPIOA, 5, PAL_MODE_STM32_ALTERNATE_PUSHPULL); /* SCK. */
	palSetPadMode(GPIOA, 6, PAL_MODE_STM32_ALTERNATE_PUSHPULL); /* MISO.*/
	palSetPadMode(GPIOA, 7, PAL_MODE_STM32_ALTERNATE_PUSHPULL); /* MOSI.*/
	palSetPadMode(GPIOA, GPIOA_SPI1NSS, PAL_MODE_OUTPUT_PUSHPULL);
	palSetPad(GPIOA, GPIOA_SPI1NSS);
}

#endif /* SPI_CONFIG_H_ */
