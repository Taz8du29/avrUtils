/* fuseresc.c
 *
 * Small program to recover bad fuse configurations
 * Supported chips : Attiny 2313A/4313, Atmega 328P
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _FUSE_RESCUE_C_
#define _FUSE_RESCUE_C_

#include "fuseresc.h"


/* FUSE RESCUE FUNCTIONS */

void fresc_init(void) {
	// All ports as output
	// Prog_enable[] bits at 0000
	// Reset, 5Vcc and CLK pins LOW (0V)
	setPortOut(PORTA);
	PORTA = 0x00;
	setPortOut(PORTB);
	PORTB = 0x00;
	setPortOut(PORTD);
	PORTD = 0x00;

	// Excepted the status pin
	setDirIn(PORTD, fresc_RDY);

	// Output enable (!OE) HIGH
	sbi(PORTD, fresc_OE);
}


void fresc_enterProgMode(void) {
	// Power the target, then wait power to raise
	sbi(PORTA, fresc_POW);
	_delay_us(50);

	// Apply 12V to the reset pin
	sbi(PORTA, fresc_RES);
	_delay_us(500);

	// Set `write pulse` (!WR) HIGH
	sbi(PORTD, fresc_WR);
}

void fresc_leaveProgMode(void) {
	// Reset Prog_enable[] bits
	cbi(PORTD, fresc_WR);
	cbi(PORTD, fresc_BS1);
	cbi(PORTD, fresc_XA0);
	cbi(PORTD, fresc_XA1);

	// Power off device
	cbi(PORTA, fresc_RES);
	_delay_us(50);
	cbi(PORTA, fresc_POW);
}


#define fresc_pulseCLK()	\
	sbi(PORTD, fresc_CLK);	\
	_delay_us(100);			\
	cbi(PORTD, fresc_CLK);	\

#define fresc_pulseWR()		\
	cbi(PORTD, fresc_WR);	\
	_delay_us(100);			\
	sbi(PORTD, fresc_WR);	\

#define fresc_waitForRDY()	\
	while ( !readBit(PIND, fresc_RDY) );


void fresc_eraseFuses(void) {
	fresc_init();
	fresc_enterProgMode();

	// Enable command loading (XA1:XA0 = 10)
	sbi(PORTB, fresc_XA1);
	cbi(PORTB, fresc_XA0);

	// Send `write fuses` command (0100 0000), and pulse CLK
	PORTB = 0x40;
	fresc_pulseCLK();

	// Enable data loading (XA1:XA0 = 01)
	cbi(PORTB, fresc_XA1);
	sbi(PORTB, fresc_XA0);

	// Send Low fuse data (BS1:XA1/BS2 = 00) and pulse CLK
	PORTB = fresc_lowFuse;
	fresc_pulseCLK();

	//pulse CLK and pulse !WR to write memory
	fresc_pulseWR();
	fresc_waitForRDY();


	// Send High fuse data (BS1:XA1/BS2 = 10) and pulse CLK
	sbi(PORTD, fresc_BS1);
	PORTB = fresc_highFuse;
	fresc_pulseCLK();

	// Pulse !WR to write memory and wait for RDY bit
	fresc_pulseWR();
	fresc_waitForRDY();


	// Send Extended fuse (BS1:XA1/BS2 = 01) and pulse CLK
	cbi(PORTD, fresc_BS1);
	sbi(PORTD, fresc_XA1);
	PORTB = fresc_extFuse;
	fresc_pulseCLK();

	// Pulse !WR to write memory and wait for RDY bit
	fresc_pulseWR();
	fresc_waitForRDY();


	// Release everything and shutdown device
	fresc_leaveProgMode();
}


#endif	/* !_FUSE_RESCUE_C_ */
