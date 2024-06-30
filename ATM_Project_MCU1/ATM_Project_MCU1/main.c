/*
 * ATM_Project_MCU1.c
 *
 * Created: 6/27/2024 5:11:22 PM
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
#include <string.h>

u8 running = 0;

int main(void)
{
	M_USART_Init(9600);
    while (1) 
    {
		u8 receivedData = M_USART_recieveByte();
		if (receivedData == 'x')
		{
			running = 1;
			check_Password();
		}
		while (running)
		{
			ProgramChoices();
		}
    }
}

