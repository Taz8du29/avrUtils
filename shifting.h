/* shifting.h
 *
 * Shift In/Out library for HC165 and HC595
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/



#ifndef _SHIFTING_H_
#define _SHIFTING_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* PROTOTYPES */

// Library initialisation
static inline void shift_init(void) __attribute__((always_inline));

// End user functions
static inline uint8_t shift_in(void) __attribute__((always_inline));
static inline void shift_out(uint8_t inbyte) __attribute__((always_inline));



/* SHIFTING (IN/OUT) FUNCTIONS */
#include "shifting.c"


#endif	/* !_SHIFTING_H_ */
