/* spi_slave.h
 *
 * USI (or Universal Serial Interface) specific functions.
 * Covers SPI (3-wire) protocol as slave device.
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _SPI_SLAVE_H_
#define _SPI_SLAVE_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* SPI SLAVE CONSTANTS */

// Moved to config file


/* PROTOTYPES */

// Initialisation of SPI hardware
static inline void spi_init(void) __attribute__((always_inline));



/* SPI SLAVE FUNCTIONS */

void spi_init(void) {
	// Enable interrupts (set (I) flag) Because this library is based on interrupts.
	sei();
}



#endif	/* !_SPI_SLAVE_H_ */
