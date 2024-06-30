/*
 * LCD.h
 *
 * Created: 2/7/2024 7:51:49 PM
 *  Author: Mina Waguih
 * Description: Driver for the configuration and functions prototype for the LCD
 *
 */ 

#ifndef LCD_H
#define LCD_H

#define F_CPU 8000000UL
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include <util/delay.h>

#define LCD_CTRL_PORT        PORTC_ID
#define LCD_DATA_PORT        PORTA_ID

#define LCD_RS_PIN           PIN0_ID
#define LCD_RW_PIN           PIN1_ID
#define LCD_E_PIN            PIN2_ID



// LCD commands

#define LCD_CLEAR_DISPLAY                         0x01
#define LCD_RETURN_HOME                           0x02
#define LCD_SHIFT_TO_LEFT_MODE                    0x07
#define LCD_SHIFT_TO_RIGHT_MODE                   0x05
#define LCD_MOVE_CURSOR_TO_RIGHT_AUTO_MODE        0x06
#define LCD_MOVE_CURSOR_TO_LEFT_AUTO_MODE         0x04
#define LCD_DISPLAY_ON                            0x0C
#define LCD_DISPLAY_OFF                           0x08
#define LCD_CURSOR_DISPLAY_ON                     0x0E
#define LCD_CURSOR_DISPLAY_OFF                    0x0C
#define LCD_BLINK_WITH_CURSOR_DISPLAY_ON          0x0F
#define LCD_BLINK_WITHOUT_CURSOR_DISPLAY_ON       0x0D
#define LCD_BLINK_DISPLAY_OFF                     0x0C
#define LCD_TWO_LINES_EIGHT_BITS_5x7_FONT_MODE    0x38
#define LCD_TWO_LINES_EIGHT_BITS_5x10_FONT_MODE   0x3C
#define LCD_TWO_LINES_FOUR_BITS_5x7_FONT_MODE     0x28
#define LCD_TWO_LINES_FOUR_BITS_5x10_FONT_MODE    0x2C 
#define LCD_SET_CURSOR_LOCATION                   0x80
#define LCD_SET_CGRAM_ADDRESS                     0x40
#define LCD_SET_DDRAM_ADDRESS                     0x80


// Function prototypes

void LCD_voidInit(void);

void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidSendString(u8 *str);

void LCD_voidClearScreen(void);

void LCD_moveCursor(u8 row,u8 col);

u8 LCD_u8GetCursorAddress(void);

void LCD_voidMoveToNextlineAuto(void);

void LCD_voidArabeMode(void);

void LCD_voidMoveToNextlineAutoArabeMode(void);

void LCD_voidCreateCustomChar(u8 *Copy_u8Data, u8 Copy_u8CGRAMAddress);

    





#endif