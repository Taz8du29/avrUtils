/* i2c_master.c
 *
 * USI (or Universal Serial Interface) specific functions.
 * Covers I²C (2-wire) protocol as master device.
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _I2C_MASTER_C_
#define _I2C_MASTER_C_

#include "i2c_master.h"


/* I²C MASTER FUNCTIONS */

void i2c_init(void) {
	// Two wire mode and software clock source
	USICR = (10<<USIWM0) | 0x00;

	// Clearing all flags, counter = 0
	USISR = (1<<USISIF) | (1<<USIOIF) | (1<<USIPF) | 0x00;

	// Empty data register (SDA : released state)
	USIDR = 0xFF;

	// Set pull-up resistors on SDA and SCL, just to be sure
	sbi(i2c_PORT, i2c_SDA_BIT);
	sbi(i2c_PORT, i2c_SCL_BIT);

	// Pins as output
	setDirOut(i2c_DIR, i2c_SDA_BIT);
	setDirOut(i2c_DIR, i2c_SCL_BIT);
}


void i2c_start(void) {
	// clear USI data register bit 7 : it holds SDA low
	USIDR = 0x00;

	// Wait and clear SCL
	_delay_us(5);
	sbi(USICR, USITC);

	// Wait again
	_delay_us(10);
}

void i2c_stop(void) {
	// Set SCL and wait
	sbi(USICR, USITC);
	_delay_us(2);
	//while ( !readBit(i2c_PIN, i2c_SCL_BIT) );

	// Set SDA
	USIDR = 0xFF;
	//while ( !readBit(i2c_PIN, i2c_SDA_BIT) );
}


uint8_t i2c_transfert(uint8_t countMask) {
	// Setup the counter to overflow in x bits
	USISR = countMask;

	// Transmit until counter overflow bit is set
	while ( !readBit(USISR, USIOIF) ) {
		// Rising edge on SCL
		sbi(USICR, USITC);

		// Wait until SCL is released by slave
		while ( !readBit(i2c_PIN, i2c_SCL_BIT) );
		_delay_us(1);

		// Falling edge on SCL
		sbi(USICR, USITC);
		_delay_us(1);

		// Shift Data register
		sbi(USICR, USICLK);
	}

	// return data register's content
	return USIDR;
}


#define i2c_sendAck() USIDR = 0x00; i2c_transfert(i2c_Mode_1BIT);
#define i2c_sendNack() USIDR = 0xFF; i2c_transfert(i2c_Mode_1BIT);

bool i2c_checkAck(void) {
	// Rising edge on SCL
	sbi(USICR, USITC);
	_delay_us(2);

	// Save bit state into var
	bool bitState = readBit(i2c_PIN, i2c_SDA_BIT);

	// Falling edge on SCL
	sbi(USICR, USITC);

	// return "0" if SDA is LOW, "1" if SDA is HIGH
	return bitState;
}


void i2c_send(uint8_t *data) {
	// Start condition
	i2c_start();

	// Write data. First byte MUST be slave address and R/W bit
	// Use i2c_addrByte(address, mode) function to craft this byte.
	while ( *data ) {
		// Set Data Rgister, then shift it out
		USIDR = *data++;
		i2c_transfert(i2c_Mode_8BIT);

		// Check for slave Ack
		if ( !i2c_checkAck() ) { break; }
	}

	// Stop condition
	i2c_stop();
}

uint8_t i2c_receive(uint8_t addr, uint8_t *data, uint8_t dataLen) {
	// Start condition
	i2c_start();

	// Broadcast slave address and direction bit
	USIDR = (addr<<1) | i2c_READ;
	i2c_transfert(i2c_Mode_8BIT);

	// Check if a slave is responding, otherwise end transmission
	if ( !i2c_checkAck() ) { i2c_stop(); return 0; }

	// Receive data
	uint8_t i = 0;
	while ( i < dataLen ) {
		// Shift in data, then store DR content into array
		data[i++] = i2c_transfert(i2c_Mode_8BIT);

		// Send NACK to end transmission if last byte
		if ( i == (dataLen - 1) ) { i2c_sendNack(); }
		else { i2c_sendAck(); }
	}

	// Stop condition
	i2c_stop();
}


#endif	/* !_I2C_MASTER_C_ */
