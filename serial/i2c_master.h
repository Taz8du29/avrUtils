/* i2c_master.h
 *
 * USI (or Universal Serial Interface) specific functions.
 * Covers I²C (2-wire) protocol as master device.
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_


/* DEPENDENCIES */

#if !defined( _MYUTILS_H_ ) || !defined ( _UTIL_DELAY_H_ )
	#error This file needs the following dependencies : myUtils, avr/util/delay
#endif



/* I²C MASTER CONSTANTS */

// Counter masks for data transfert
#define i2c_Mode_1BIT 0b11101110
#define i2c_Mode_8BIT 0b11101000

// First data byte crafting function.
// Uses the slave's address and the R/W bit.
#define i2c_addrByte(addr, mode) ((addr<<1) | mode)



/* PROTOTYPES */

// Initialisation of TWI hardware
static inline void i2c_init(void) __attribute__((always_inline));

// Start and stop conditions
static inline void i2c_start(void) __attribute__((always_inline));
static inline void i2c_stop(void) __attribute__((always_inline));

// Loop for sending 1 or 8 bits (it also returns data register's content)
static inline uint8_t i2c_transfert(uint8_t countMask) __attribute__((always_inline));

// Functions that checks slave's Ack
static inline bool i2c_checkAck(void) __attribute__((always_inline));

// Fully implemented read/write functions
static inline void i2c_send(uint8_t *data) __attribute__((always_inline));
static inline uint8_t i2c_receive(uint8_t addr, uint8_t *data, uint8_t dataLen) __attribute__((always_inline));



/* I²C MASTER FUNCTIONS */
#include "i2c_master.c"


#endif	/* !_I2C_MASTER_H_ */
