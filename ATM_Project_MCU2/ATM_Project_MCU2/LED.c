/*
 * LED.c
 *
 * Created: 1/28/2024 10:28:19 PM
 *  Author: Mina Waguih
 * description: driver for leds configuration and functions
 */ 

#include "LED.h"


void LedConfig(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_voidSetPinDirection(Copy_u8Port, Copy_u8Pin, PIN_OUTPUT);
}


void LedStatus(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Status, u8 Copy_u8Value)
{
	if (Copy_u8Status == SOURCE_CONNECTION)
	{
		DIO_voidSetPinValue(Copy_u8Port, Copy_u8Pin, Copy_u8Value);
	} 
	else if(Copy_u8Status == SINK_CONNECTION)
	{
		DIO_voidSetPinValue(Copy_u8Port, Copy_u8Pin, !Copy_u8Value);
	}
}