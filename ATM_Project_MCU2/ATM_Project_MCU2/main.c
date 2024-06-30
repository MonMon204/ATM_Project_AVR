/*
 * ATM_Project_MCU2.c
 *
 * Created: 6/27/2024 1:11:15 PM
 * Author : Mina Waguih
 */ 

#define F_CPU 8000000UL
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "Timer.h"
#include "USART.h"
#include "EXT_INTERRUPT.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "LED.h"
#include "FUNCTIONS.h"
#include <util/delay.h>

extern u8 running;
extern u8 checking;
extern u8 DataIndex;

int main(void)
{
    LCD_voidInit();
    KEYPAD_voidInit();
	M_USART_Init(9600);
	LEDs_Init();
	BUZZER_Init();
	EXTI_void_INT_Init(INT1,RISING_EDGE);
	EXTI_voidSetCallBack(mainLoop,INT1);
	EXTI_voidGlobalINT_Enable();
    LCD_voidSendCommand(LCD_BLINK_WITH_CURSOR_DISPLAY_ON);
    LCD_voidSendString(" Welcome !! ");
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
    _delay_ms(2000);
    LCD_voidClearScreen();
	
    while (1)
    {
		while(1)
		{}
		mainLoop();
    }
}
