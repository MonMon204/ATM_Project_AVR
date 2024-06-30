/*
 * USART.c
 *
 * Created: 3/23/2024 1:26:55 PM
 *  Author: Mina Waguih
 */ 

#include "USART.h"


void M_USART_Init(u32 baud_rate)
{
	u16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<UCSRA_U2X);

	UCSRB = (1<<UCSRB_RXEN) | (1<<UCSRB_TXEN);
	
	UCSRC = (1<<UCSRC_URSEL) | (1<<UCSRC_UCSZ0) | (1<<UCSRC_UCSZ1); 
	
	/* Calculate the UBRR register value */
	ubrr_value = (u16)(((16000000 / (baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

void M_USART_sendByte(const u8 data)
{
	
	
	while( BIT_IS_CLR(UCSRA,UCSRA_UDRE) ){} /* Wait for empty transmit buffer */
		
	UDR = data;
}

void M_USART_sendString(const u8 *Str)
{
	while(*Str != '\0')
	{
		M_USART_sendByte(*Str);
		
		Str++;
	}
}

u8 M_USART_recieveByte(void)
{
	/* Wait for data to be received */
	while ( BIT_IS_CLR(UCSRA, UCSRA_RXC) ) {}
	
	/* Get and return received data from buffer */
	return UDR;
}

void M_USART_receiveString(u8 *Str)
{
	u8 i = 0;

	/* Receive the first byte */
	Str[i] = M_USART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = M_USART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

void M_USART_sendU32(u32 number) {
	// Split the unsigned long into 4 bytes for transmission
	u8 data_bytes[4];
	data_bytes[0] = (u8)(number & 0xFF); // Least significant byte (LSB)
	data_bytes[1] = (u8)((number >> 8) & 0xFF);
	data_bytes[2] = (u8)((number >> 16) & 0xFF);
	data_bytes[3] = (u8)((number >> 24) & 0xFF); // Most significant byte (MSB)

	// Send each byte sequentially
	for (int i = 0; i < 4; i++) {
		while (!(UCSRA & (1 << UCSRA_UDRE))); // Wait for transmit buffer to become empty
		UDR = data_bytes[i];              // Send data byte
	}
}

u32 M_USART_receiveU32(void) {
	u8 data_bytes[4];
	
	u32 received_number;

	// Receive each byte sequentially
	for (int i = 0; i < 4; i++) {
		while (!(UCSRA & (1 << UCSRA_RXC))); // Wait for data to be received
		data_bytes[i] = UDR;            // Read received data byte
	}

	// Combine received bytes into the unsigned long
	received_number = (data_bytes[3] << 24) | (data_bytes[2] << 16) |
	(data_bytes[1] << 8) | data_bytes[0];
	
	return received_number;
}