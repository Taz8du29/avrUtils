/* hardUart.h
 *
 * Implementation of the AVR's USART hardware
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _HARDUART_H_
#define _HARDUART_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file must not be included directly
#endif

#ifndef F_CPU
	#error This library requires for baud rate maths
#endif



/* UART CONSTANTS */

// Pre computed clock speed (for baud rate)
#define harduart_BAUD_CALC_VAR (F_CPU / 16)



/* PROTOTYPES */

// Library initialisation
static inline void harduart_init(void) __attribute__((always_inline));

// Low level implementation of read/write functions
static inline void harduart_write(char input) __attribute__((always_inline));
//static inline void harduart_read(void) __attribute__((always_inline));

// End-user function for outputing string
static inline void harduart_print(char* str) __attribute__((always_inline));



/* REGISTERS USED */

/* Registers
 *
 * This section is for information only.
 * These tables are extracted from Atmel's Attiny2313a/4313 datasheet
 *
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
 * | Bit     |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
 * | UCSRA   |  RXC  |  TXC  | UDRE  |   FE  |  DOR  |  UPE  |  U2X  |  MPCM |
 * | R/W ?   |   R   |  R/W  |   R   |   R   |   R   |   R   |  R/W  |  R/W  |
 * | Default |   0   |   0   |   1   |   0   |   0   |   0   |   0   |   0   |
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
 * | Bit     |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
 * | UCSRB   | RXCIE | TXCIE | UDRIE | RXEN  | TXEN  | UCSZ2 | RXB8  | TXB8  |
 * | R/W ?   |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |   R   |  R/W  |
 * | Default |   0   |   0   |   0   |   0   |   0   |   0   |   0   |   0   |
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
 *
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
 * | Bit     |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
 * | UCSRC   |   –   | UMSEL | UPM1  | UPM0  | USBS  | UCSZ1 | UCSZ0 | UCPOL |
 * | R/W ?   |   R   |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |
 * | Default |   0   |   0   |   0   |   0   |   0   |   1   |   1   |   0   |
 * +---------+-------+-------+-------+-------+-------+-------+-------+-------+
*/



/* UART FUNCTIONS */

/* Pins functions
 *
 * You can use this functions to enable / disable both transmitter and receiver.
 * Enabling means that the USART hardware controls the pin behavior.
 * Disabling restores normal pin functionnality.
 *
 * Warning : disabling the receiver flushes (empty) the receive buffer, so the
 * remaining data will be lost !
*/

#define harduart_disable_Tx cbi(UCSRB, TXEN);
#define harduart_disable_Rx cbi(UCSRB, RXEN);

#define harduart_enable_Tx sbi(UCSRB, TXEN);
#define harduart_enable_Rx sbi(UCSRB, RXEN);


/* UART initialisation
 *
 * UBRR is loaded with a value calculated from the baudrate, using the following
 * formula :
 *          f OSC
 * UBRR = --------- – 1
 *        16 * BAUD
 *
 * In order to reduce AVR CPU's use, (fosc / 16) has already been calculated. It
 * is defined under the name "harduart_BAUD_CALC_VAR" (Yeah, I hadn't a better
 * name in mind ...).
*/

void harduart_init(int baudrate) {
	UBRR = (harduart_BAUD_CALC_VAR * inv(baudrate)) - 1;

	#if ( harduart_BITS_DATA == 9 )
		sbi(UCSRB, UCSZ2);
		UCSRC = harduart_BITS_PARITY | harduart_BITS_STOP | (3<<UCSZ0);
	#else
		cbi(UCSRB, UCSZ2);
		UCSRC = harduart_BITS_PARITY | harduart_BITS_STOP | ((harduart_BITS_DATA - 5)<<UCSZ0);
    #endif
}


void harduart_write(char input) {}

void harduart_read(void) {}


void harduart_print(char* str) { while (*str) harduart_write(*str++); }


#endif
