/*
 * USART.h
 *
 * Created: 3/23/2024 1:27:15 PM
 *  Author: Mina Waguih
 */ 


#ifndef USART_H
#define USART_H

#include "BIT_MATH.h"
#include "STD_TYPES.h"



#define UDR						*((volatile u8*) 0x2C)		// USART I/O Data Register – UDR

#define UCSRA					*((volatile u8*) 0x2B)		// USART Control and Status Register A – UCSRA

#define UCSRA_RXC               7
#define UCSRA_TXC               6
#define UCSRA_UDRE              5
#define UCSRA_FE                4
#define UCSRA_DOR               3
#define UCSRA_PE                2
#define UCSRA_U2X               1
#define UCSRA_MPCM              0


/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART TX Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/

#define UCSRB					*((volatile u8*) 0x2A)		// USART Control and Status Register B – UCSRB

#define UCSRB_RXCIE             7		// RXCIE: RX Complete Interrupt Enable
#define UCSRB_TXCIE             6		// TXCIE: TX Complete Interrupt Enable
#define UCSRB_UDRIE             5		// UDRIE: USART Data Register Empty Interrupt Enable
#define UCSRB_RXEN              4		// RXEN: Receiver Enable
#define UCSRB_TXEN              3		// TXEN: Transmitter Enable
#define UCSRB_UCSZ2             2		// UCSZ2: Character Size
#define UCSRB_RXB8              1		// RXB8: Receive Data Bit 8
#define UCSRB_TXB8              0		// TXB8: Transmit Data Bit 8


/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/

#define UCSRC					*((volatile u8*) 0x40)		// USART Control and Status Register C – UCSRC

#define UCSRC_URSEL             7		// URSEL: Register Select
#define UCSRC_UMSEL             6		// UMSEL: USART Mode Select
#define UCSRC_UPM1              5		// UPM1:0: Parity Mode
#define UCSRC_UPM0              4
#define UCSRC_USBS              3		// USBS: Stop Bit Select
#define UCSRC_UCSZ1             2		// UCSZ1:0: Character Size
#define UCSRC_UCSZ0             1
#define UCSRC_UCPOL             0		// UCPOL: Clock Polarity


// USART Baud Rate Registers – UBRRL and UBRRH
#define UBRRH					*((volatile u8*) 0x40)
#define UBRRL					*((volatile u8*) 0x29)

#define UBRRH_URSEL             7		// URSEL: Register Select



/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void M_USART_Init(u32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void M_USART_sendByte(const u8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
u8 M_USART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void M_USART_sendString(const u8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void M_USART_receiveString(u8 *Str); // Receive until #


void M_USART_sendU32(u32 number);
u32 M_USART_receiveU32(void);



#endif
