/* config.h
 *
 * All the user-editable variables needed by the different libraries.
 * Specific instructions can be found lower.
 *
 * Copyright 2015 - 2017 (C) Taz8du29
 * Refer to LICENSE.MD for more infos about copyright
*/


#ifndef _MYUTILS_CONFIG_H_
#define _MYUTILS_CONFIG_H_


/*******************************
 * INTERRUPTS
*******************************/

// If you are using interrupts, it is recommended to disable them during
// operations on 16 bits registers. Just uncomment the "pwm_interrupts" line
// and every function using 16 bits registers will disable interrupts long
// enough to operate.

// #define using_interrupts 1



/*******************************
 * SHIFTING
*******************************/

// All pins must be on the same port
#define shift_DIR	DDRD
#define shift_PORT	PORTD
#define shift_PIN	PIND

//		Pin Name	Pin			HC595		HC165
#define shift_DATA	PD3		//  SER			Qh
#define shift_CLK	PD4		//  SRCLK		CLK
#define shift_LD	PD5		//  RCLK		SH/_LD
#define shift_IOE	PD6		//  _OE			CLK INH



/*******************************
 * FUSERESC
*******************************/

/* DO NOT EDIT THIS PINS AND PORTS CONFIG. */

// Target's enable pin
#define fresc_OE PD0

// Clock pin (XTAL1)
#define fresc_CLK	PD1

// Prog_enable = [WR, BS1, XA0, XA1];
#define fresc_WR	PD2	 // Write pulse
#define fresc_BS1	PD3	 // Byte select 1 OR Page Load
#define fresc_XA0	PD4	 // Xtal Action bit 0
#define fresc_XA1	PD5	 // Xtal Action bit 1 OR Byte select 2

// Input pin used to read target's status
#define fresc_RDY PD6

// Power control of the target chip
#define fresc_POW PA0	// 5Vcc
#define fresc_RES PA1	// 12Vcc aka Reset



/*******************************
 * HARDWARE UART
*******************************/

// Pin configuration
#define harduart_DIR	DDRD
#define harduart_PORT	PORTD
#define harduart_PIN	PD6


// Frame formats (Uncomment wanted one)

#define harduart_BITS_PARITY (0<<UPM0)		// No parity bit
// #define harduart_BITS_PARITY (2<<UPM0)	// Even parity
// #define harduart_BITS_PARITY (3<<UPM0)	// Odd parity

#define harduart_BITS_STOP (0<<USBS)		// One stop bit
// #define harduart_BITS_STOP (1<<USBS)		// Two stop bits

#define harduart_BITS_DATA 8				// 5,6,7,8 or 9 bits



/*******************************
 * SOFTWARE UART
*******************************/

// Pin configuration
#define softuart_DIR	DDRD
#define softuart_PORT	PORTD
#define softuart_PIN	PIND

#define softuart_RX_BIT PD5
#define softuart_TX_BIT PD6



/*******************************
 * I²C
*******************************/

/* Pin configuration
 *
 * Warning : You must change these to match your hardware.
 *
 * This pin configuration is for an attiny 2313a.
 * I had to define new names for values because I/O definition file ones have
 * ambiguous names.
*/

// I²C
#define i2c_DIR		DDRB
#define i2c_PORT	PORTB
#define i2c_PIN		PINB

// SDA (data)
#define i2c_SDA_BIT PB5

// SCL (clock)
#define i2c_SCL_BIT PB7

// transfer modes
#define i2c_WRITE 0
#define i2c_READ  1

// Device's address, in slave mode (change it if you desire)
#define i2c_address 0x69



/*******************************
 * SPI
*******************************/

/* Pin configuration
 *
 * Warning : You must change these to match your hardware.
 *
 * This pin configuration is for an attiny 2313a.
 * I had to define new names for values because I/O definition file ones have
 * ambiguous names.
*/

// SPI ports
#define spi_DDR   DDRB
#define spi_PORT  PORTB
#define spi_PIN   PINB

// MOSI (master out, slave in)
#define spi_MOSI_BIT   PB5

// MISO (master in, slave out)
#define spi_MISO_BIT   PB6

// SCK (clock)
#define spi_SCK_BIT   PB7



/*******************************
 * HD44780
*******************************/

// LCD mode : 4 or 8 bits
#define lcd_mode 4

// Data ports (bits [0-3] or [0-7] used)
#define lcd_DATA_DIR	DDRB
#define lcd_DATA_PORT	PORTB
#define lcd_DATA_PIN	PINB

// Command ports
#define lcd_CMD_DIR		DDRD
#define lcd_CMD_PORT	PORTD

// Command bits
#define lcd_EN PD5
#define lcd_RS PD4
#define lcd_RW PD3



/*******************************
 * SSD1306
*******************************/

// I²C address used by the device (default : 0x7A or 0x7B)
#define glcd_address 0x7B

// Screen size (in pixels)
#define glcd_Vsize 64
#define glcd_Hsize 128



#endif	/* !_MYUTILS_CONFIG_H_ */
