/* i2c_slave.h
 *
 * USI (or Universal Serial Interface) specific functions.
 * Covers I²C (2-wire) protocol as slave device.
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _I2C_SLAVE_H_
#define _I2C_SLAVE_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file must not be included directly
#endif



/* I²C SLAVE CONSTANTS */

/* Pin configuration
 *
 * Warning : You must change these to match your hardware.
 *
 * This pin configuration is for an attiny 2313a.
 * I had to define new names for values because I/O definition file
 * ones have too ambiguous names.
*/

// I²C
#define i2c_DIR		DDRB
#define i2c_PORT	PORTB
#define i2c_PIN		PINB

// SDA (data)
#define i2c_SDA_BIT PB5

// SCL (clock)
#define i2c_SCL_BIT PB7


// transfer modes
#define i2c_READ 0
#define i2c_WRITE 1



/* PROTOTYPES */

// Initialisation of TWI hardware
static inline void i2c_init(void) __attribute__((always_inline));



/* I²C SLAVE FUNCTIONS */

void i2c_init(void) {
	// Enable interrupts (set (I) flag) Because this library is based on interrupts.
	sei();
}

ISR(USI_START_vect) {

	// Return and enable interrupts
	reti();
}

ISR(USI_OVERFLOW_vect) {

	// Return and enable interrupts
	reti();
}


#endif	/* !_I2C_SLAVE_H_ */
