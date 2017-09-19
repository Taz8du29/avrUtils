/* shifting.c
 *
 * Shift In/Out library for HC165 and HC595
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/



#ifndef _SHIFTING_C_
#define _SHIFTING_C_

#include "shifting.h"


/* SHIFT (IN/OUT) FUNCTIONS */

void shift_init(void) {
	// All command pins as output
	shift_DIR |= (1<<shift_CLK) | (1<<shift_LD) | (1<<shift_IOE);

	// Then defined in a known state
	cbi(shift_PORT, shift_CLK);
	sbi(shift_PORT, shift_LD);
	cbi(shift_PORT, shift_IOE);
}


#define shift_pulse() \
	sbi(shift_PORT, shift_CLK); \
	cbi(shift_PORT, shift_CLK);


uint8_t shift_in(void) {
	// Set data pin as input
	setPinIn(shift_DIR, shift_DATA);

	// Save data on the chip
	cbi(shift_PORT, shift_LD);
	sbi(shift_PORT, shift_LD);

	// Start reading session => CLK INH = Low
	cbi(shift_PORT, shift_IOE);

	uint8_t outbyte = 0x00;

	uint8_t i = 8;
	while ( --i ) {
		if ( readBit(shift_PORT, shift_DATA) ) { sbi(outbyte, i); }
		else { cbi(outbyte, i); }
		shift_pulse();
	}

	// End reading session => CLK INH = High
	cbi(shift_PORT, shift_IOE);

	return outbyte;
}

void shift_out(uint8_t inbyte) {
	// Set data pin as output
	setPinOut(shift_DIR, shift_DATA);
	cbi(shift_PORT, shift_LD);

	// Put HC's pins in Hi Z
	sbi(shift_PORT, shift_IOE);

	// Output all the bits, serially
	uint8_t x = 8;
	while ( --x ) {
		if ( readBit(inbyte, x) ) {sbi(shift_PORT, shift_DATA);}
		else { cbi(shift_PORT, shift_DATA); }
		shift_pulse();
	}

	// Load data into HC's storage
	sbi(shift_PORT, shift_LD);
	cbi(shift_PORT, shift_LD);

	// Enable HC's pins
	cbi(shift_PORT, shift_IOE);
}


#endif	/* !_SHIFTING_C_ */
