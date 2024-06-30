/*
 * LCD.c
 *
 * Created: 2/7/2024 7:52:05 PM
 *  Author: Mina Waguih
 * Description: Driver for the configuration and functions prototype for the LCD
 */ 

#include "LCD.h"

void LCD_voidInit(void)
{	
	_delay_ms(32);
	LCD_voidSendCommand(LCD_TWO_LINES_EIGHT_BITS_5x7_FONT_MODE);
	LCD_voidSendCommand(LCD_DISPLAY_ON);
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
	_delay_ms(2);
	LCD_voidSendCommand(LCD_MOVE_CURSOR_TO_RIGHT_AUTO_MODE);
	LCD_moveCursor(0,0);
}

void LCD_voidSendCommand(u8 Copy_u8Command)
{	
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,PIN_OUTPUT);
	
	DIO_voidSetPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
	
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,PIN_LOW);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,PIN_LOW);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_LOW);
	
	DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Command);
	
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_LOW);
	
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,PIN_OUTPUT);
	
	DIO_voidSetPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
	
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,PIN_HIGH);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,PIN_LOW);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_LOW);
	
	DIO_voidSetPortValue(LCD_DATA_PORT,Copy_u8Data);
	
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_LOW);
}

void LCD_voidSendString(u8 *str)
{
	for (u32 i = 0;str[i] != '\0';i++)
	{
		LCD_voidSendData(str[i]);
	}
}

void LCD_voidClearScreen(void)
{
	LCD_voidSendCommand(LCD_CLEAR_DISPLAY);
}

void LCD_moveCursor(u8 row,u8 col)
{
	u8 address = 0x00 + ((row % 2) * 0x40) + col;
	
	LCD_voidSendCommand(LCD_SET_CURSOR_LOCATION | address);
}

u8 LCD_u8GetCursorAddress(void)
{
	u8 u8CURSOR_ADDRESS;
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RS_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_RW_PIN,PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CTRL_PORT,LCD_E_PIN,PIN_OUTPUT);
	
	DIO_voidSetPortDirection(LCD_DATA_PORT,PORT_INPUT);
	
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN,PIN_LOW);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN,PIN_HIGH);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_HIGH);
	_delay_ms(2);
	u8CURSOR_ADDRESS = DIO_u8GetPortValue(LCD_DATA_PORT);
	DIO_voidSetPinValue(LCD_CTRL_PORT,LCD_E_PIN,PIN_LOW);
	return u8CURSOR_ADDRESS;
	
}

void LCD_voidMoveToNextlineAuto(void)
{
	u8 u8CURSOR_ADDRESS = LCD_u8GetCursorAddress();
	if (u8CURSOR_ADDRESS == (LCD_SET_CURSOR_LOCATION + 16))
	{
		LCD_moveCursor(1,0);
	}
}

void LCD_voidArabeMode(void)
{
	LCD_voidSendCommand(LCD_MOVE_CURSOR_TO_LEFT_AUTO_MODE);
	LCD_moveCursor(0,15);
}

void LCD_voidMoveToNextlineAutoArabeMode(void)
{
	u8 u8CURSOR_ADDRESS = LCD_u8GetCursorAddress();
	if (u8CURSOR_ADDRESS == (LCD_SET_CURSOR_LOCATION))
	{
		LCD_moveCursor(1,15);
	}
}

void LCD_voidCreateCustomChar(u8 *Copy_u8Data, u8 Copy_u8CGRAMAddress)
{
	if (Copy_u8CGRAMAddress < 8)
	{
		LCD_voidSendCommand(LCD_SET_CGRAM_ADDRESS + Copy_u8CGRAMAddress*8);
		
		for(u8 i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
		LCD_voidSendData(Copy_u8Data[i]);
	}
		
}