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

#include "myUtils.h"



/* LCD DISPLAY CONSTANTS */

// RS pin direction
#define CMD  0
#define DATA 1

// Busy flag state (reading data.7)
#define BF 0

// Calculate the "number of lines" bit
#define _lcd_linesCalc ((lcd_lines % 2) << 3)

// Define 8-bits or 4-bits mode from user settings
#define _lcd_modeCalc  ( ((lcd_mode == 4) ? 0 : 1) << 4)

// Main commands
#define lcd_CMD_clearDisplay 0x01
#define lcd_CMD_returnHome   0x02

#define lcd_displayOn  (1<<1)
#define lcd_displayOff (0<<1)

#define lcd_cursorOn  (1<<1)
#define lcd_cursorOff (0<<1)

#define lcd_blinkingOn  (1<<0)
#define lcd_blinkingOff (0<<0)

#define lcd_CMD_shiftCursorLeft  0x10
#define lcd_CMD_shiftCursorRight 0x14

#define lcd_CMD_shiftDisplayLeft  0x18
#define lcd_CMD_shiftDisplayRight 0x1C



/* PROTOTYPES */

// Library initialisation
static inline void lcd_init(void) __attribute__((always_inline));

// Small pulse on lcd_EN pin
static inline void lcd_pulse(void) __attribute__((always_inline));

// Read from and write to the display
static inline void lcd_write(uint8_t mode, uint8_t cmd) __attribute__((always_inline));
static inline uint8_t lcd_read(uint8_t mode) __attribute__((always_inline));

// User-leveled functions : displays string on LCD
static inline void lcd_print(uint8_t* str, uint8_t line, uint8_t col) __attribute__((always_inline));



/* LCD DISPLAY FUNCTIONS */

#include "displays/lcd_hd44780.c"


#endif	/* !_LCD_HD44780_H_ */
