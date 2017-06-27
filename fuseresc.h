/* fuseresc.h
 *
 * Small program to recover bad fuse configurations
 * Supported chips : Attiny 2313A/4313, Atmega 328P
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _FUSE_RESCUE_H_
#define _FUSE_RESCUE_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* CHIPS DEFAULT FUSES */

// Attiny 2313A
#define fresc_lowFuse 0x64
#define fresc_highFuse 0xDF
#define fresc_extFuse 0xFF

// Atmega 328P
// #define fresc_lowFuse 0x62
// #define fresc_highFuse 0xD9
// #define fresc_extFuse 0xFF



/* PROTOTYPES */

// Initializes the library
void fresc_init(void) __attribute__((always_inline));

// Low level functions
void fresc_enterProgMode(void) __attribute__((always_inline));
void fresc_leaveProgMode(void) __attribute__((always_inline));

// Main, user-level function
void fresc_eraseFuses(void) __attribute__((always_inline));



/* FUSE RESCUE FUNCTIONS */
#include "fuseresc.c"


#endif	/* !_FUSE_RESCUE_H_ */
