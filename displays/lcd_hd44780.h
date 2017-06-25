/* hd44780.h
 *
 * HD44780 LCD display driver functions
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _HD44780_H_
#define _HD44780_H_


/* REQUIREMENTS */

#ifndef _MYUTILS_H_
	#error This file needs the following dependencies : myUtils
#endif



/* LCD DISPLAY FUNCTIONS */

// RS pin direction
#define CMD 0
#define DATA 1

// Busy flag state (reading data.7)
#define BF 0


// Main commands
#define lcd_clearDisplay_CMD 0x01
#define lcd_returnHome_CMD 0x02

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
static inline void lcd_write(bool mode, char cmd) __attribute__((always_inline));
static inline char lcd_read(bool mode) __attribute__((always_inline));

// User-leveled functions : displays string on LCD
static inline void lcd_print(char* str, char line, char col) __attribute__((always_inline));



/* LCD DISPLAY FUNCTIONS */

// Wait for busy bit to clear
#define lcd_wait() while ( lcd_read(BF) & 0x80 );


void lcd_init(void) {
	// Set command pins to output, then LOW
	lcd_CMD_DIR |= (1<<lcd_RS) | (1<<lcd_RW) | (1<<lcd_EN);
	lcd_CMD_PORT |= ~(1<<lcd_RS) | ~(1<<lcd_RW) | ~(1<<lcd_EN);


	#if ( lcd_mode == 8 )
		// Set data port as output
		setPortOut(lcd_DATA_DIR);
		lcd_DATA_PORT = 0x00;

		_delay_us(100);

		// 8 bits mode, 2 lines of 8x5 matrixes
		lcd_write(CMD, 0x38);
		lcd_wait();
	#else // lcd_mode == 4
		// Set data port as output
		lcd_DATA_DIR |= 0xF0;
		lcd_DATA_PORT &= 0x0F;

		_delay_us(100);

		// 4 bits mode, 2 lines of 8x5 matrixes
		lcd_write(CMD, 0x28);
		lcd_wait();
	#endif


	// Display on, show static cursor
	lcd_write(CMD, 0x0E);
	lcd_wait();
	// Write from Left to Right, no shift
	lcd_write(CMD, 0x06);
	lcd_wait();
	// Clear the display
	lcd_write(CMD, lcd_clearDisplay_CMD);
	lcd_wait();
}


// Small pulse on lcd_EN pin
void lcd_pulse(void) {
	_delay_us(10);
	sbi(lcd_CMD_PORT, lcd_EN);
	_delay_us(10);
	cbi(lcd_CMD_PORT, lcd_EN);
}


#if ( lcd_mode == 8 )

void lcd_write(bool mode, char cmd) {
	setPortOut(lcd_DATA_DIR);
	cbi(lcd_CMD_PORT, lcd_RW);

	if( mode ) { sbi(lcd_CMD_PORT, lcd_RS); }
	else { cbi(lcd_CMD_PORT, lcd_RS); }

	lcd_DATA_PORT = cmd;
	lcd_pulse();
}

char lcd_read(bool mode) {
	setPortIn(lcd_DATA_DIR);
	sbi(lcd_CMD_PORT, lcd_RW);

	if( mode ) { sbi(lcd_CMD_PORT, lcd_RS); }
	else { cbi(lcd_CMD_PORT, lcd_RS); }

	char outbyte = 0x00;

	lcd_pulse();
	outbyte |= lcd_DATA_PIN;

	return outbyte;
}

#else // lcd_mode == 4

void lcd_write(bool mode, char cmd) {
	lcd_DATA_DIR &= 0x0F;
	lcd_DATA_DIR |= 0xF0;

	cbi(lcd_CMD_PORT, lcd_RW);

	if ( mode ) { sbi(lcd_CMD_PORT, lcd_RS); }
	else { cbi(lcd_CMD_PORT, lcd_RS); }

	lcd_DATA_PORT &= 0x0F;
	lcd_DATA_PORT |= (cmd & 0xF0);
	lcd_pulse();

	lcd_DATA_PORT &= 0x0F;
	lcd_DATA_PORT |= ((cmd<<4) & 0xF0);
	lcd_pulse();
}

char lcd_read(bool mode) {
	lcd_DATA_DIR &= 0x0F;

	sbi(lcd_CMD_PORT, lcd_RW);

	if ( mode ) { sbi(lcd_CMD_PORT, lcd_RS); }
	else { cbi(lcd_CMD_PORT, lcd_RS); }

	char outbyte = 0x00;

	lcd_pulse();
	outbyte |= (lcd_DATA_PIN & 0xF0);
	lcd_pulse();
	outbyte |= ((lcd_DATA_PIN & 0xF0)<<4);

	return outbyte;
}

#endif


void lcd_print(char* str, char line, char col) {
	if ( line == 0 && col != -1 ) {
		lcd_write(CMD, (0x80 + col));
		lcd_wait();
	}
	else if ( line == 1 && col != -1 ) {
		lcd_write(CMD, (0xC0 + col));
		lcd_wait();
	}

	while ( *str ) {
		lcd_write(DATA, *str++);
		lcd_wait();
	}
}


#endif
