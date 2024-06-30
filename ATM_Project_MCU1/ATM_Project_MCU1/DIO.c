/*
 * DIO.c
 *
 * Created: 1/28/2024 9:52:31 PM
 *  Author: Mina Waguih
 * Description: Source file for the AVR DIO driver
 *
 */ 

#include "DIO.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_voidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction)
{
	if (Copy_u8Direction == PIN_OUTPUT)
	{
		switch(Copy_u8Port){
			case PORTA_ID: SET_BIT(DDRA,Copy_u8Pin); break;
			case PORTB_ID: SET_BIT(DDRB,Copy_u8Pin); break;
			case PORTC_ID: SET_BIT(DDRC,Copy_u8Pin); break;
			case PORTD_ID: SET_BIT(DDRD,Copy_u8Pin); break;
		}
	}
	else if (Copy_u8Direction == PIN_INPUT)
	{
		switch(Copy_u8Port){
			case PORTA_ID: CLR_BIT(DDRA,Copy_u8Pin); break;
			case PORTB_ID: CLR_BIT(DDRB,Copy_u8Pin); break;
			case PORTC_ID: CLR_BIT(DDRC,Copy_u8Pin); break;
			case PORTD_ID: CLR_BIT(DDRD,Copy_u8Pin); break;
		}
	}
}


/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_voidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value)
{
	if (Copy_u8Value == PIN_HIGH)
	{
		switch(Copy_u8Port){
			case PORTA_ID: SET_BIT(PORTA,Copy_u8Pin); break;
			case PORTB_ID: SET_BIT(PORTB,Copy_u8Pin); break;
			case PORTC_ID: SET_BIT(PORTC,Copy_u8Pin); break;
			case PORTD_ID: SET_BIT(PORTD,Copy_u8Pin); break;
		}
	}
	else if (Copy_u8Value == PIN_LOW)
	{
		switch(Copy_u8Port){
			case PORTA_ID: CLR_BIT(PORTA,Copy_u8Pin); break;
			case PORTB_ID: CLR_BIT(PORTB,Copy_u8Pin); break;
			case PORTC_ID: CLR_BIT(PORTC,Copy_u8Pin); break;
			case PORTD_ID: CLR_BIT(PORTD,Copy_u8Pin); break;
		}
	}
}


/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
u8 DIO_u8GetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	switch(Copy_u8Port){
		case PORTA_ID: return GET_BIT(PINA,Copy_u8Pin);
		case PORTB_ID: return GET_BIT(PINB,Copy_u8Pin); 
		case PORTC_ID: return GET_BIT(PINC,Copy_u8Pin);
		case PORTD_ID: return GET_BIT(PIND,Copy_u8Pin); 
	}
}


/*
 * Description :
 * configure the pin as an input and activate the internal pull-up resistor
 */
void DIO_voidSetPinPullUpRes(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_voidSetPinDirection(Copy_u8Port,Copy_u8Pin,PIN_INPUT);
	DIO_voidSetPinValue(Copy_u8Port,Copy_u8Pin,LOGIC_HIGH);
}


/*
 * Description :
 * Setup the direction of the required port all pins input/output.
 * If the direction value is PORT_INPUT all pins in this port should be input pins.
 * If the direction value is PORT_OUTPUT all pins in this port should be output pins.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_voidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction)
{
	switch(Copy_u8Port){
		case PORTA_ID: DDRA = Copy_u8Direction; break;
		case PORTB_ID: DDRB = Copy_u8Direction; break;
		case PORTC_ID: DDRC = Copy_u8Direction; break;
		case PORTD_ID: DDRD = Copy_u8Direction; break;
	}
}


/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_voidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value)
{
	switch(Copy_u8Port){
		case PORTA_ID: PORTA = Copy_u8Value; break;
		case PORTB_ID: PORTB = Copy_u8Value; break;
		case PORTC_ID: PORTC = Copy_u8Value; break;
		case PORTD_ID: PORTD = Copy_u8Value; break;
	}
}


/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
u8 DIO_u8GetPortValue(u8 Copy_u8Port)
{
	switch(Copy_u8Port){
		case PORTA_ID: return PINA;
		case PORTB_ID: return PINB;
		case PORTC_ID: return PINC;
		case PORTD_ID: return PIND;
	}
}


/*
 * Description :
 * configure the port as an input and activate the internal pull-up resistor
 */
void DIO_voidSetPortPullUpRes(u8 Copy_u8Port)
{
	DIO_voidSetPortDirection(Copy_u8Port,PORT_INPUT);
	DIO_voidSetPortValue(Copy_u8Port,PORT_HIGH);
}