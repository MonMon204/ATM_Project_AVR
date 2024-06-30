/*
 * KEYPAD.h
 *
 * Created: 2/7/2024 7:56:00 PM
 *  Author: Mina Waguih
 * Description: Driver for the configuration and functions prototype for the KEYPAD
 */ 

#ifndef KEYPAD_H
#define KEYPAD_H

#define F_CPU 8000000UL
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include <util/delay.h>


#define KEYPAD_COL_NUM           4
#define KEYPAD_ROW_NUM           4

#define KEYPAD_COL_PORT          PORTB_ID

#define KEYPAD_C0_PIN            PIN0_ID
#define KEYPAD_C1_PIN            PIN1_ID
#define KEYPAD_C2_PIN            PIN2_ID
#define KEYPAD_C3_PIN            PIN3_ID


#define KEYPAD_ROW_PORT          PORTB_ID

#define KEYPAD_R0_PIN            PIN4_ID
#define KEYPAD_R1_PIN            PIN5_ID
#define KEYPAD_R2_PIN            PIN6_ID
#define KEYPAD_R3_PIN            PIN7_ID


#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH


#define KEYPAD_VALUES             {{'7','8','9','/'},\
								   {'4','5','6','*'},\
								   {'1','2','3','-'},\
								   {'c','0','=','+'}}
									   
									   
   
// function prototypes

void KEYPAD_voidInit(void);

u8 KEYPAD_u8GetPressedKey(void);
								   









#endif
