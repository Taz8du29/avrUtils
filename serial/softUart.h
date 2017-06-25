/* softUart.h
 *
 * A basic, software managed, Tx (Rx soon) UART library
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _SOFTUART_H_
#define _SOFTUART_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* UART CONSTANTS */

// Moved to config file



/* PROTOTYPES */

// Library initialisation
static inline void softuart_init(void) __attribute__((always_inline));

// Fixing bitrate
static inline void softuart_delay(void) __attribute__((always_inline));

// Low level implementation of read/write functions
static inline void softuart_write(char input) __attribute__((always_inline));
//static inline void softuart_read(void) __attribute__((always_inline));

// End-user function for outputing string
static inline void softuart_print(char* str) __attribute__((always_inline));



/* UART FUNCTIONS */

void softuart_init(void) {
	setDirOut(softuart_DIR, softuart_PIN);
	sbi(softuart_PORT, softuart_PIN);
}


void softuart_delay(void) {
	// 9600 Bd
	_delay_us(104);
}


void softuart_write(char input) {
	// Disable interrupts
	saveSREG();
	cli();

	// Start Bit
	cbi(softuart_PORT, softuart_PIN);
	softuart_delay();

	// Data Bits
	char i = 8;
	while ( i ) {
		--i;
		if ( readBit(input, i) ) { sbi(softuart_PORT, softuart_PIN); }
		else { cbi(softuart_PORT, softuart_PIN); }
		softuart_delay();
	}

	// Stop Bit
	sbi(softuart_PORT, softuart_PIN);
	softuart_delay();

	// Enable interrupts
	restoreSREG();
}

/*
void softuart_read(void) {
	// Disable interrupts
	saveSREG();
	cli();

	char i = 8;
	while(i) {
		--i;
	}

	// Enable interrupts
	restoreSREG();

	return something;
}
*/


void softuart_print(char* str) {
	while ( *str ) { softuart_write(*str++); }
}


#endif
