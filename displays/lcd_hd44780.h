/* lcd_hd44780.h
 *
 * HD44780 LCD display driver functions
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _LCD_HD44780_H_
#define _LCD_HD44780_H_


/* DEPENDENCIES */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* LCD DISPLAY CONSTANTS */

// RS pin direction
#define CMD  0
#define DATA 1

// Busy flag state (reading data.7)
#define BF 0


// Main commands
#define lcd_clearDisplay_CMD 0x01
#define lcd_returnHome_CMD   0x02

// TODO :make commands for
// Display on/off control = 0b00001 + D + C + B

// #define lcd_shiftCursorLeft  0x1 // 0b0001 1? 1? 00
// #define lcd_shiftCursorRight 0x1 // 0b0001 1? 0? 00

#define lcd_setCGRAM_CMD 0x40
#define lcd_setDDRAM_CMD 0x80



/* PROTOTYPES */

// Library initialisation
static inline void lcd_init(void) __attribute__((always_inline));

// Small pulse on lcd_EN pin
static inline void lcd_pulse(void) __attribute__((always_inline));

// Read from and Write to the display
// Structure is both for 8 and 4 bits functions
static inline void lcd_write(uint8_t mode, uint8_t cmd) __attribute__((always_inline));
static inline uint8_t lcd_read(uint8_t mode) __attribute__((always_inline));

// User-leveled functions : displays string on LCD
static inline void lcd_print(uint8_t* str, uint8_t line, uint8_t col) __attribute__((always_inline));



/* LCD DISPLAY FUNCTIONS */
#include "lcd_hd44780.c"


#endif	/* !_LCD_HD44780_H_ */
