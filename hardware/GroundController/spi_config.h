/*
 * spi_config.h
 *
 *  Created on: 03-04-2014
 *      Author: Novakov
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#define GPIOA_SPI1NSS 4

static const SPIConfig hs_spicfg =
{
		NULL,
		GPIOA,
		GPIOA_SPI1NSS,
		SPI_CR1_BR_1 | SPI_CR1_BR_2
};

static inline void ConfigureSPIPins(void)
{
	palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST); /* NSS.     */
	palSetPadMode(GPIOA, 5, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST); /* SCK.     */
	palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(5)); /* MISO.    */
	palSetPadMode(GPIOA, 7, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST); /* MOSI.    */

	palSetPad(GPIOA, GPIOA_SPI1NSS);

}

#endif /* SPI_CONFIG_H_ */
