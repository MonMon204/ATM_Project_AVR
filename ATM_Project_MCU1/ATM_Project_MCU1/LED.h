/*
 * LED.h
 *
 * Created: 1/28/2024 10:22:05 PM
 *  Author: Mina Waguih
 * Description: driver for leds configuration and functions
 */ 

#ifndef LED_H
#define LED_H

#include "DIO.h"
#include "BIT_MATH.h"
#include "STD_TYPES.h"

/* Led Status */
#define SOURCE_CONNECTION     0
#define SINK_CONNECTION       1

/* Led Values */
#define LED_OFF          PIN_LOW
#define LED_ON           PIN_HIGH


void LedConfig(u8 Copy_u8Port, u8 Copy_u8Pin);

void LedStatus(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Status, u8 Copy_u8Value);



#endif
