/* myUtils.h
 *
 * Lots of useful things, in a file ... or more ^^
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.md for more infos about copyright
*/


#ifndef _MYUTILS_H_
#define _MYUTILS_H_


/* ENABLE OTHER LIBRARIES */

/* Other libraries
 *
 * This section is a "shortcut" to the #include section at the end of the file.
 * Just uncomment a line to enable the library.
 *
 * WARNING : some libraries aren't compatible due to pin configurations.
 * See library's specific files for more help.
 *
 * I²C and SPI :
 * Include master OR slave library, NOT both !
*/

#define shift_enable

//#define fresc_enable

// #define harduart_enable
// #define softUart_enable

#define i2c_master_enable
// #define i2c_slave_enable

// #define spi_master_enable
// #define spi_slave_enable

#define lcd_hd44780_enable
// #define glcd_1306_enable



/* REQUIREMENTS */

// AVR ports, pins an registers definitions
// io.h is device specific, common.h is ... common to all devices.
#include <avr/io.h>
#include <avr/common.h>

// Time wasting functions, based on F_CPU
#include <util/delay.h>

// MyUtils libraries' configuration file
#include "config.h"



/* PROTOTYPES */

/* Prototypes
 *
 * Every prototype is defined "static inline", with the attribute
 * "always_inline". This is intended to save many so precious bytes during
 * compilation, especially if functions are unused !
*/

// Maths
static inline unsigned long power(uint8_t a, uint8_t x) __attribute__((always_inline));
static inline unsigned long fact(uint8_t a) __attribute__((always_inline));

// PWM
static inline void pwm_pin0A(uint8_t val) __attribute__((always_inline));
static inline void pwm_pin0B(uint8_t val) __attribute__((always_inline));
static inline void pwm_pin1A(uint16_t val) __attribute__((always_inline));
static inline void pwm_pin1B(uint16_t val) __attribute__((always_inline));



/* CONSTANT DEFINITIONS */

#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1



/* BITS FUNCTIONS */

// Set or Clear a bit
#define sbi(var, pos) (var |= (1<<pos))
#define cbi(var, pos) (var &= ~(1<<pos))

// Read bit
#define readBit(var, pos) (var & (1<<pos))

// Toggle bit
#define toggleBit(var, pos) (var ^= (1<<pos))



/* I/O FUNCTIONS */

// Pin direction
#define setPinIn(pin, bit) (pin &= ~(1<<bit))
#define setPinOut(pin, bit) (pin |= (1<<bit))

// Port direction
#define setPortIn(port) (port = 0x00)
#define setPortOut(port) (port = 0xFF)

// Toggle port
#define togglePort(port) (port ^= 0xFF)



/* MATHS FUNCTIONS AND CONSTANTS */

/* Floating point operations
 *
 * WARNING : multiply, divide and floating point operations are very slow
 * because AVRs don't have dedicated hardware. Use them carefully.
 * Try to use integers as much as possible.
 *     i.e : 1.472 V is 1472 mV.
*/

#define PI			3.1415926535897932
#define HALF_PI		1.5707963267948966
#define TWO_PI		6.2831853071795865
#define EXP			2.7182818284590452
#define SQRT_TWO	1.4142135623730950
#define DEG_TO_RAD  0.0174532925199433
#define RAD_TO_DEG 57.2957795130823209

#define max(a, b) ((a>b) ? a : b)
#define min(a, b) ((a>b) ? b : a)
#define abs(x) ((x>0) ? x : -(x))

#define deg(rad) (rad * RAD_TO_DEG)
#define rad(deg) (deg * DEG_TO_RAD)

#define round(x) ((x>=0) ? (long)(x+0.5) : (long)(x-0.5))

#define inv(x) (1/x)
#define opposite(x) (-(x))

#define sq(x) (x * x)
#define cb(x) (x * x * x)

// If LSB is set, `var` is Odd, otherwise `var` is Even
#define isOdd(var)	((var & 0x01) ? true : false)
#define isEven(var)	((var & 0x01) ? false : true)

unsigned long power(uint8_t a, uint8_t x) {
	unsigned long result = 1;
	while(x) {result *= a; x--;}
	return result;
}

// Returns factorial of the given 8-bit integer.
unsigned long fact(uint8_t a) {
	// Pre-computed factorials for : 0 <= a <= 8
	const uint16_t fact[9] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320};

	if ( a < 9 ) {
		return (unsigned long) fact[a];
	}
	else {
		unsigned long result = 1;
		while(a) {result *= a; a--;}
		return result;
	}
}



/* INTERRUPTS */

/* Interrupts
 *
 * This is a simplified version of the official interrupt.h file.
 * All deprecated, pre-4.1 code and heavy doxygen stuff has been removed.
 *
 * Copyright (c) 2002,2005,2007 Marek Michalkiewicz
 * Copyright (c) 2007, Dean Camera
 * Copyright (c) 2015 - 2017, Taz8du29
*/

// Set or clear global interrupt flag (I)
#define cli() __asm__ __volatile__ ("cli" ::: "memory")
#define sei() __asm__ __volatile__ ("sei" ::: "memory")

// Return from interrupt routine
#define reti() __asm__ __volatile__ ("reti" ::)


/* BADISR_vect
 *
 * This vector is aliased to __vector_default, the vector executed when an ISR
 * fires with no accompanying ISR handler. This may be used with the ISR() macro
 * to create a catch-all for undefined but used ISRs for debugging purposes.
*/

#  define BADISR_vect __vector_default


/* ISR(vector [, attributes])
 *
 * Introduces an interrupt handler function (interrupt service routine).
 * Valid ISR attributes (optional) :
 *
 *  - ISR_BLOCK      : Identical to an ISR with no attributes specified.
 *  - ISR_NOBLOCK    : The (I) flag is activated asap by the compiler within the ISR.
 *  - ISR_NAKED      : ISR is created with no prologue or epilogue code.
 *  - ISR_ALIASOF(v) : The ISR is linked to another ISR, specified by the vect parameter.
 *
 * Attributes alters the interrupt routine's behaviour and compilation.
 * Multiple attributes may be used for a single function, using space as seperator.
*/

#ifdef __cplusplus
	#define ISR(vector, ...) \
		extern "C" void vector(void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
		void vector(void);
#else
	#define ISR(vector, ...) \
		void vector(void) __attribute__ ((signal, used, externally_visible)) __VA_ARGS__; \
		void vector(void);
#endif

#define ISR_BLOCK
#define ISR_NOBLOCK    __attribute__((interrupt))
#define ISR_NAKED      __attribute__((naked))
#define ISR_ALIASOF(v) __attribute__((alias(#v)))


/* EMPTY_INTERRUPT(vector)
 *
 * Defines an empty interrupt handler function.
 * This will not generate any prolog or epilog code and will only return from the ISR.
 * Do not define a function body as this will define it for you.
*/

#ifdef __cplusplus
	#define EMPTY_INTERRUPT(vector) \
		extern "C" void vector(void) __attribute__ ((signal, naked, used, externally_visible)); \
		void vector(void) { reti(); }
#else	  /* !__cplusplus */
	#define EMPTY_INTERRUPT(vector) \
		void vector(void) __attribute__ ((signal, naked, used, externally_visible)); \
		void vector(void) { reti(); }
#endif



/* POWER MANAGEMENT */

/* Power register.
 *
 * Attinys have a build in register, used to disable some
 * of their functionnalities, to decrease their power
 * consumption.
 *
 * Other functions are used for components not included
 * in the power register. Enabling or disabling these
 * components is achieved by editing their specific register.
*/

#define pwr_disable_all()		PRR = 0xFF; disable_AC();
#define pwr_enable_all()		PRR = 0x00; enable_AC();

#define pwr_disable_timer0()	sbi(PRR, PRTIM0);
#define pwr_enable_timer0()		cbi(PRR, PRTIM0);

#define pwr_disable_timer1()	sbi(PRR, PRTIM1);
#define pwr_enable_timer1()		cbi(PRR, PRTIM1);

#define pwr_disable_USI()		sbi(PRR, PRUSI);
#define pwr_enable_USI()		cbi(PRR, PRUSI);

#define pwr_disable_USART()		sbi(PRR, PRUSART);
#define pwr_enable_USART()		cbi(PRR, PRUSART);

// AC is analog comparator
#define pwr_disable_AC()		sbi(ACSR, ACD);
#define pwr_enable_AC()			cbi(ACSR, ACD);

#define pwr_disable_watchdog()	cbi(WDTCR, WDE); cbi(WDTCR, WDIE);
#define pwr_enable_watchdog()	sbi(WDTCR, WDE); sbi(WDTCR, WDIE);

// en/disable brown-out detector
// #define pwr_disable_BOD()	sbi(??, ??);
// #define pwr_enable_BOD()		cbi(??, ??);



/* SLEEP MODES */

#define sleep_enter() sbi(MCUCR, SE); asm("sleep");
#define sleep_leave() cbi(MCUCR, SE);

#define sleep_idle()		cbi(MCUCR, SM1); cbi(MCUCR, SM0); enterSleep();
#define sleep_powerDown()	cbi(MCUCR, SM1); sbi(MCUCR, SM0); enterSleep();
#define sleep_standBy()		sbi(MCUCR, SM1); cbi(MCUCR, SM0); enterSleep();



/* STATUS REGISTER */

/* Status register asm commands.
 *
 * Flags are bits, contained in the status register (SREG), that inform
 * the APU of different operations' result.
 *
 * You can manually force these bits by using the following commands.
 * The interrupt flag (I) can also be set and cleared using sei() and cli().
 *
 * Read the datasheet for more infos.
*/

// Carry flag (C)
#define flag_set_carry() asm("sec");
#define flag_clr_carry() asm("clc");

// Half carry flag (H)
#define flag_set_halfCarry() asm("seh");
#define flag_clr_halfCarry() asm("clh");

// Global interrupt flag (I)
#define flag_set_interrupt() asm("sei");
#define flag_clr_interrupt() asm("cli");

// Negative flag (N)
#define flag_set_negative() asm("sen");
#define flag_clr_negative() asm("cln");

// Signed test flag (S)
#define flag_set_signed() asm("ses");
#define flag_clr_signed() asm("cls");

// Tranfer bit flag (T)
#define flag_set_transfer() asm("set");
#define flag_clr_transfer() asm("clt");

// Two's complement overflow flag (V)
#define flag_set_twoComp() asm("sev");
#define flag_clr_twoComp() asm("clv");

// Zero flag (Z)
#define flag_set_zero() asm("sez");
#define flag_clr_zero() asm("cez");

// Save/restore SREG state
#define saveSREG()		uint8_t _sreg_temp_ = SREG;
#define restoreSREG()	SREG = _sreg_temp_;



/* PWM GENERATION */

/* PWM using the 8 bits counter (TCNT0).
 *
 * Compare match of OCR0A outputs on pin0A, compare match of OCR0B on pin0B.
 * The PWM resolution is 8 bits (0 -> 255).
 *
 * Settings :
 * - Fast-PWM mode, TOP = 0xFF (WGM2:0 = 011)
 * - IO clock source, no prescaler (CS02:0 = 001)
 * - Pin setup : Clear on compare match / Set at "TOP" (COM0x1:0 = 10)
 *
 * Read datasheet for more infos
*/

void pwm_pin0A(uint8_t val) {
	// Apply settings (0xFF is a mask for other settings)
	TCCR0A &= (1<<COM0A1) | (3<<WGM00) | 0xFF;
	TCCR0B = (1<<CS00);

	// Then setup the compare match value
	OCR0A = val;

	// Finally set the pin as output
	setPinOut(OC0A_DDR, OC0A_BIT);
}

void pwm_pin0B(uint8_t val) {
	// Apply settings (0xFF is a mask for other settings)
	TCCR0A &= (1<<COM0B1) | (3<<WGM00) | 0xFF;
	TCCR0B = (1<<CS00);

	// Then setup the compare match value
	OCR0B = val;

	// Finally set the pin as output and high
	setPinOut(OC0B_DDR, OC0B_BIT);
}


/* PWM using the 16 bits counter (TCNT1)
 *
 * Compare match of OCR1A outputs on pin1A, compare match of OCR1B on pin1B.
 * The PWM resolution is 10 bits (0 -> 1023).
 *
 * Settings :
 * - Fast-PWM mode - 10 bits, TOP = 0x03FF (WGM13:0 = 0111)
 * - IO clock source, no prescaler (CS12:0 = 001)
 * - Pin setup : Clear on compare match / Set at "TOP" (COM1x1:0 = 10)
 *
 * Read datasheet for more infos
*/

void pwm_pin1A(uint16_t val) {
	// Apply settings (0xFF is a mask for other settings)
	TCCR1A &= (1<<COM1A1) | (3<<WGM10) | 0xFF;
	TCCR1B = (1<<WGM12) | (1<<CS10);

	// Disable interrupts for 16 bits operations
	#ifdef using_interrupts
		saveSREG();
		cli();
	#endif

	// Then setup the compare match value
	OCR1A = val;

	// Enable interrupts
	#ifdef using_interrupts
		restoreSREG();
	#endif

	// Finally set the pin as output
	setPinOut(OC1A_DDR, OC1A_BIT);
}

void pwm_pin1B(uint16_t val) {
	// Apply settings (0xFF is a mask for other settings)
	TCCR1A &= (1<<COM1B1) | (3<<WGM10) | 0xFF;
	TCCR1B = (1<<WGM12) | (1<<CS10);

	// Disable interrupts for 16 bits operations
	#ifdef using_interrupts
		saveSREG();
		cli();
	#endif

	// Then setup the compare match value and reset counter
	OCR1B = val;

	// Enable interrupts
	#ifdef using_interrupts
		restoreSREG();
	#endif

	// Finally set the pin as output
	setPinOut(OC1B_DDR, OC1B_BIT);
}



/* MISCELLANOUS FONCTIONS */

// Split Words (up to 32 bits) into Bytes (8 bits)
#define lowByte(var)	((uint8_t)(var | 0xFF))
#define highByte(var)	((uint8_t)(var>>8 | 0xFF))
#define highByte2(var)	((uint8_t)(var>>16 | 0xFF))
#define highByte3(var)	((uint8_t)(var>>24 | 0xFF))

// No operation
#define nop() asm("nop");



/* INCLUDE OTHER LIBRARIES */

// Shift registers
#ifdef shift_enable
	#include "shifting.h"
#endif


// Fuse rescuer
#ifdef fresc_enable
	#include "fuseresc.h"
#endif


// UART
#ifdef softUart_enable
	#include "serial/softUart.h"
#endif

#ifdef harduart_enable
	#include "serial/hardUart.h"
#endif


// I²C
#ifdef i2c_master_enable
	#include "serial/i2c_master.h"
#endif

#ifdef i2c_slave_enable
	#include "serial/i2c_slave.h"
#endif


// SPI
#ifdef spi_master_enable
	#include "serial/spi_master.h"
#endif

#ifdef spi_slave_enable
	#include "serial/spi_slave.h"
#endif


// LCDs
#ifdef lcd_hd44780_enable
	#include "lcd_hd44780.h"
#endif


// Graphic LCDs
#ifdef glcd_ssd1306_enable
	#include "glcd_ssd1306.h"
#endif



#endif	/* !_MYUTILS_H_ */
