#include "ch.h"
#include "hal.h"

#include "fc_spi.h"

#include <string.h>

#define GPIOA_SPI1NSS 4

/*
 * Mutex to lock output buffer
 */
static Mutex					SPIMtx; /* Mutex */

/*
 * SPI configuration
 * Maximum speed SPI configuration (18MHz, CPHA=0, CPOL=0, MSb first).
 */
static const SPIConfig hs_spicfg = {
	NULL,
	GPIOA,
	GPIOA_SPI1NSS,
	SPI_CR1_BR_1 |SPI_CR1_BR_2
};

/*
 * Initialize the SPI interface
 */
void SPIInit(void)
{
	/*
	* SPI1 I/O pins setup.
	*/
	palSetPadMode(GPIOA, 4, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);           /* NSS.     */
	palSetPadMode(GPIOA, 5, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);           /* SCK.     */
	palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(5));              /* MISO.    */
	palSetPadMode(GPIOA, 7, PAL_MODE_ALTERNATE(5) | PAL_STM32_OSPEED_HIGHEST);           /* MOSI.    */

	palSetPad(GPIOA, GPIOA_SPI1NSS);

	/*
	* Initialize Mutex
	*/
	chMtxInit(&SPIMtx); /* Mutex initialization before use */
}

/*
 * SPI bus exchange routine
 */
int SPIExchangeData(SPIDriver *spip, uint8_t *tx, uint8_t *rx, size_t size) {

	chMtxLock(&SPIMtx);

	/*
	 * Do exchange between device and MCU.
	 */
	spiAcquireBus(spip);              /* Acquire ownership of the bus.    */
	spiStart(spip, &hs_spicfg);       /* Setup transfer parameters.       */
	spiSelect(spip);                  /* Slave Select assertion.          */
	spiExchange(spip, size, tx, rx);  /* Atomic transfer operations.      */
	spiUnselect(spip);                /* Slave Select de-assertion.       */
	spiReleaseBus(spip);              /* Ownership release.               */
	chMtxUnlock();

	return 0;
}

/*
 * SPI bus exchange routine
 */
int SPIExchangeDataI(SPIDriver *spip, uint8_t *tx, uint8_t *rx, size_t size) {
	//chMtxLock(&SPIMtx);

	/*
	 * Do exchange between device and MCU.
	 */
	spiStartExchangeI(spip, size, tx, rx);  /* Atomic transfer operations.      */

	return 0;
}

/*
 * SPI bus send routine
 */
int SPISendData(SPIDriver *spip, uint8_t *tx, size_t size) {

	chMtxLock(&SPIMtx);

	/*
	 * Do exchange between device and MCU.
	 */
	spiAcquireBus(spip);              /* Acquire ownership of the bus.    */
	spiStart(spip, &hs_spicfg);       /* Setup transfer parameters.       */
	spiSelect(spip);                  /* Slave Select assertion.          */
	spiSend(spip, size, tx);					/* Send command											*/
	spiUnselect(spip);                /* Slave Select de-assertion.       */
	spiStop(spip);
	spiReleaseBus(spip);              /* Ownership release.               */
	chMtxUnlock();

	return 0;
}

/*
 * SPI bus receive routine
 */
int SPIReceiveData(SPIDriver *spip, uint8_t *rx, size_t size) {

	chMtxLock(&SPIMtx);

	/*
	 * Do exchange between device and MCU.
	 */
	spiAcquireBus(spip);              /* Acquire ownership of the bus.    */
	spiStart(spip, &hs_spicfg);       /* Setup transfer parameters.       */
	spiSelect(spip);                  /* Slave Select assertion.          */
	spiReceive(spip, size, rx);
	spiUnselect(spip);                /* Slave Select de-assertion.       */
	spiReleaseBus(spip);              /* Ownership release.               */
	chMtxUnlock();

	return 0;
}
