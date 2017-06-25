/* spi_master.h
 *
 * USI (or Universal Serial Interface) specific functions.
 * Covers SPI (3-wire) protocol as master
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _SPI_MASTER_H_
#define _SPI_MASTER_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* SPI SLAVE CONSTANTS */

// Moved to config file


/* PROTOTYPES */

// Initialisation of SPI hardware
static inline void spi_init(void) __attribute__((always_inline));

static inline void spi_write(uint8_t data) __attribute__((always_inline));
static inline uint8_t spi_write(void) __attribute__((always_inline));



/* SPI MASTER FUNCTIONS */

void spi_init(void) {}

void spi_write(uint8_t data) {}

uint8_t spi_read(void) {}


#endif
