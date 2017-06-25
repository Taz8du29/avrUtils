// fuseresc.h
//
// Small program to recover bad fuse configurations
// Supported chips : Attiny 2313A/4313, Atmega 328P
//
// Copyright 2015 - 2017 (C) Taz8du29
// Refer to LICENSE.MD for more infos about copyright



#ifndef _FUSE_RESCUE_H_
#define _FUSE_RESCUE_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* FUSE RESCUE CONSTANTS */

// DO NOT CHANGE PINS AND PORTS.
#define fresc_OE PD0	// Target's enable pin

// This pins must be in that order !!! Otherwise some functions won't work
#define fresc_WR	PD2	 // Write clock
#define fresc_BS1	PD3	 // Byte select 1 OR Page Load
#define fresc_XA0	PD4	 // Xtal Action bit 0
#define fresc_XA1	PD5	 // Xtal Action bit 1 OR Byte select 2

// Input pin used to read target's status
#define fresc_RDY PD6

// PA0 is used to power the target with 5V
// PA1 controls the 12V transistor for the reset pin
#define fresc_POW PA0
#define fresc_RES PA1



/* CHIPS DEFAULT FUSES */

// Attiny 2313A
#define fresc_lowFuse 0x
#define fresc_highFuse 0x
#define fresc_extFuse 0x00

// Atmega 328P
// #define fresc_lowFuse 0x
// #define fresc_highFuse 0x
// #define fresc_extFuse 0x



/* FUSE RESCUE FUNCTIONS */

void fresc_setProgEnable(char cmd) {
	PORTD &= ((0x0<<fresc_WR) & 0xFF);
	PORTD |= (cmd<<fresc_WR);
}

void fresc_init(void) {
	// All ports as output
	setPortOut(PORTA);
	setPortOut(PORTB);
	setPortOut(PORTD);

	// Excepted the status pin
	setDirIn(PORTD, fresc_RDY);

	fresc_setProgEnable(0x0);

	cbi(PORTA, fresc_POW);
	cbi(PORTA, fresc_RES);
}

void fresc_enterProgMode() {
	// Power the target, then wait power to raise
	sbi(PORTA, fresc_POW);
	_delay_us(60);

	// Apply 12V to the reset pin
	sbi(PORTA, fresc_RES);
	_delay_us(500);
}



int main(void) {
	fresc_init();
	fresc_enterProgMode();


}



/*
Programming the Flash
	A. Load Command “Write Flash”
		1. Set XA1, XA0 to “10”. This enables command loading.
		2. Set BS1 to “0”.
		3. Set DATA to “0001 0000”. This is the command for Write Flash.
		4. Give XTAL1 a positive pulse. This loads the command.

	B. Load Address Low byte
		1. Set XA1, XA0 to “00”. This enables address loading.
		2. Set BS1 to “0”. This selects low address.
		3. Set DATA = Address low byte (0x00 - 0xFF).
		4. Give XTAL1 a positive pulse. This loads the address low byte.

	C. Load Data Low Byte
		1. Set XA1, XA0 to “01”. This enables data loading.
		2. Set DATA = Data low byte (0x00 - 0xFF).
		3. Give XTAL1 a positive pulse. This loads the data byte.

	D. Load Data High Byte
		1. Set BS1 to “1”. This selects high data byte.
		2. Set XA1, XA0 to “01”. This enables data loading.
		3. Set DATA = Data high byte (0x00 - 0xFF).
		4. Give XTAL1 a positive pulse. This loads the data byte.

	E. Repeat B through E until the entire buffer is filled or until all data within the page is loaded.

		While the lower bits in the address are mapped to words within the page, the higher bits
		address the pages within the FLASH. This is illustrated in Figure 21-2 on page 189. Note
		that if less than eight bits are required to address words in the page (pagesize < 256), the
		most significant bit(s) in the address low byte are used to address the page when performing
		a Page Write.

	F. Load Address High byte
		1. Set XA1, XA0 to “00”. This enables address loading.
		2. Set BS1 to “1”. This selects high address.
		3. Set DATA = Address high byte (0x00 - 0xFF).
		4. Give XTAL1 a positive pulse. This loads the address high byte.

	G. Program Page
		1. Give WR a negative pulse. This starts programming of the entire page of data. RDY/BSY goes low.
		2. Wait until RDY/BSY goes high (See Figure 21-3 on page 189 for signal waveforms).

	H. Repeat B through H until the entire Flash is programmed or until all data has been programmed.

	I. End Page Programming
		1. 1. Set XA1, XA0 to “10”. This enables command loading.
		2. Set DATA to “0000 0000”. This is the command for No Operation.
		3. Give XTAL1 a positive pulse. This loads the command, and the internal write signals are reset.
*/



/*
Programming Low Fuse Bits
	A: Load Command “0100 0000”.
	C: Load Data Low Byte. Bit n = “0” programs and bit n = “1” erases the Fuse bit.
	Give WR a negative pulse and wait for RDY/BSY to go high.

Programming High Fuse Bits
	A: Load Command “0100 0000”.
	C: Load Data Low Byte. Bit n = “0” programs and bit n = “1” erases the Fuse bit.
	Set BS1 to “1” and BS2 to “0”. This selects high data byte.
	Give WR a negative pulse and wait for RDY/BSY to go high.
	Set BS1 to “0”. This selects low data byte.

Programming Extended Fuse Bits
	A: Load Command “0100 0000”.
	C: Load Data Low Byte. Bit n = “0” programs and bit n = “1” erases the Fuse bit.
	Set BS1 to “0” and BS2 to “1”. This selects extended data byte.
	Give WR a negative pulse and wait for RDY/BSY to go high.
	Set BS2 to “0”. This selects low data byte.
*/
