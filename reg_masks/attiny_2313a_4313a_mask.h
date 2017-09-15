/* register_mask.h
 *
 * Aliases for useful register masks
 * MCUs: AtTiny 2313a & 4313a
 *
 * Copyright 2017 (C) Taz8du29
 * Refer to LICENSE.md for more infos about copyright
*/


#ifndef _MASK_ATTINY_2313A_4313A_H_
#define _MASK_ATTINY_2313A_4313A_H_


/* 0x01 (0x21)
 *
 * DIDR - Digital input disable
 * Used by: Analog comparator
 *
 * Set the bit to disable input, clear to enable
*/

// Digital input for AIN1 pin enable/disable
#define AC_DI1_on  (0<<1)
#define AC_DI1_off (1<<1)

// Digital input for AIN0 pin enable/disable
#define AC_DI0_on  (0<<0)
#define AC_DI0_off (1<<0)




/* 0x03 (0x23)
 *
 * UCSRC - USART control & status C
 * Used by: USART, USART in MSPIM mode
*/

// USART Mode select
#define USART_Mode_Async (00<<6)   // Asynchronous mode
#define USART_Mode_Sync  (01<<6)   // Synchronous mode
#define USART_Mode_MSPIM (11<<6)   // Master SPI mode

// USART Parity bit
#define USART_Parity_None (00<<4)  // No parity bit
#define USART_Parity_Even (10<<4)  // Even parity bit
#define USART_Parity_Odd  (11<<4)  // Odd parity bit

// USART Number of stop bits
#define USART_Stop_1 (0<<3)        // 1 stop bit
#define USART_Stop_2 (1<<3)        // 2 stop bits

// USART Charater size (bits 1:0)
#define USART_SizeC_5 (00<<1)      // 5-bits word
#define USART_SizeC_6 (01<<1)      // 6-bits word
#define USART_SizeC_7 (10<<1)      // 7-bits word
#define USART_SizeC_8 (11<<1)      // 8-bits word
#define USART_SizeC_9 (11<<1)      // 9-bits word

// USART Clock polarity (sync mode)
#define USART_Clk_TxRx (0<<0)      // Tx on Rising edge  / Rx on Falling edge
#define USART_Clk_RxTx (1<<0)      // Tx on Falling edge / Rx on Rising edge

// MPSIM Data order
#define MSPIM_MSB_First (0<<2)
#define MSPIM_LSB_First (1<<2)

// MSPIM XCK phase and polarity
#define MSPIM_Mode_0 (00<<1)
#define MSPIM_Mode_1 (10<<1)
#define MSPIM_Mode_2 (01<<1)
#define MSPIM_Mode_3 (11<<1)



/* 0x04 (0x24)
*
* PCMSK1 - Pin change mask register 1
* Used by: Pin change interrupts 8 to 10
*/

// Pin change interrupt enable/disable
#define PC_Int_10_on  (1<<2)
#define PC_Int_10_off (0<<2)

#define PC_Int_9_on  (1<<1)
#define PC_Int_9_off (0<<1)

#define PC_Int_8_on  (1<<0)
#define PC_Int_8_off (0<<0)



/* 0x05 (0x25)
 *
 * PCMSK2 - Pin change mask register 2
 * Used by: Pin change interrupts 11 to 17
*/

// Pin change interrupt enable/disable
#define PC_Int_17_on  (1<<6)
#define PC_Int_17_off (0<<6)

#define PC_Int_16_on  (1<<5)
#define PC_Int_16_off (0<<5)

#define PC_Int_15_on  (1<<5)
#define PC_Int_15_off (0<<5)

#define PC_Int_14_on  (1<<3)
#define PC_Int_14_off (0<<3)

#define PC_Int_13_on  (1<<2)
#define PC_Int_13_off (0<<2)

#define PC_Int_12_on  (1<<1)
#define PC_Int_12_off (0<<1)

#define PC_Int_11_on  (1<<0)
#define PC_Int_11_off (0<<0)



/* 0x08 (0x28)
 *
 * ACSR - Analog comparator control & status
 * Used by: Analog comparator
*/

// Enable/disable analog comparator
#define AC_enable  (1<<7)
#define AC_disable (0<<7)

// Use bandgap voltage reference
#define AC_Bandgap_on  (1<<6)
#define AC_Bandgap_off (0<<6)

// Analog comparator output
#define AC_get_output (1<<5)

// Clear AC interrupt flag
#define AC_clr_IntFlag (1<<4)

// Analog comparator interrupt
#define AC_Int_on  (1<<3)
#define AC_Int_off (0<<3)

// Analog comparator input capture for Timer/Counter1
#define AC_Capture_on  (1<<2)
#define AC_Capture_off (0<<2)

// Analog comparator mode select
#define AC_Int_onToggle  (00<<0)
#define AC_Int_onFalling (10<<0)
#define AC_Int_onRising  (11<<0)



/* 0x0A (0x2A)
 *
 * UCSRB - USART control & status B
 * Used by: USART
*/

// Interrupt on Rx complete
#define USART_Int_RxC_on  (1<<7)
#define USART_Int_RxC_off (0<<7)

// Interrupt on Tx complete
#define USART_Int_TxC_on  (1<<6)
#define USART_Int_TxC_off (0<<6)

// Interrupt on USART data register empty
#define USART_Int_DRe_on  (1<<5)
#define USART_Int_DRe_off (0<<5)

// USART Receiver enable/disable
#define USART_Rx_on  (1<<4)
#define USART_Rx_off (0<<4)

// USART Transmitter enable/disable
#define USART_Rx_on  (1<<3)
#define USART_Rx_off (0<<3)

// USART Charater size (bit 2)
#define USART_SizeB_5 (0<<2)
#define USART_SizeB_6 (0<<2)
#define USART_SizeB_7 (0<<2)
#define USART_SizeB_8 (0<<2)
#define USART_SizeB_9 (1<<2)

// USART Receive data bit
#define USART_get_Data8 (1<<1)

// USART Transmit data bit
#define USART_set_Data8 (1<<0)
#define USART_clr_Data8 (0<<0)



/* 0x0B (0x2B)
 *
 * UCSRA - USART control & status A
 * Used by: USART
*/

// Status bits
#define USART_get_RxC (1<<7)      // Receive complete
#define USART_get_TxC (1<<6)      // Transmit complete
#define USART_get_DRe (1<<5)      // Data register empty
#define USART_get_FE (1<<4)       // Frame error
#define USART_get_DOR (1<<3)      // Data overrun
#define USART_get_PE (1<<2)       // Parity error

// USART Double transmit speed
#define USART_2XSpeed_on  (1<<1)
#define USART_2XSpeed_off (0<<1)

// USART DoubleMulti-processor
#define USART_MultiProc_on  (1<<1)
#define USART_MultiProc_off (0<<1)



/* 0x20 (0x40)
 *
 * PCMSK0 - Pin change mask register 0
 * Used by: Pin change interrupts 0 to 7
 *
 * Set to enable interrupt on pin, clear to disable.
*/

// Pin change interrupt enable/disable
#define PC_Int_7_on  (1<<7)
#define PC_Int_7_off (0<<7)

#define PC_Int_6_on  (1<<6)
#define PC_Int_6_off (0<<6)

#define PC_Int_5_on  (1<<5)
#define PC_Int_5_off (0<<5)

#define PC_Int_4_on  (1<<5)
#define PC_Int_4_off (0<<5)

#define PC_Int_3_on  (1<<3)
#define PC_Int_3_off (0<<3)

#define PC_Int_2_on  (1<<2)
#define PC_Int_2_off (0<<2)

#define PC_Int_1_on  (1<<1)
#define PC_Int_1_off (0<<1)

#define PC_Int_0_on  (1<<0)
#define PC_Int_0_off (0<<0)


#endif  /* !_MASK_ATTINY_2313A_4313A_H_ */
