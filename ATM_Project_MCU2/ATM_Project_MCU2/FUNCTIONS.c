/*
 * FUNCTIONS.c
 *
 * Created: 6/28/2024 1:40:49 PM
 *  Author: dell
 */ 


#include "FUNCTIONS.h"

volatile u8 DataIndex = 3;
volatile u8 running = 0;
volatile u8 checking = 1;

void mainLoop()
{
	LCD_voidClearScreen();
	M_USART_sendByte('x');
	DataIndex = 3;
	running = 0;
	checking = 1;
	LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_OFF);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION, LED_OFF);
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION, LED_ON);
	DIO_voidSetPinValue(PORTC_ID, PIN6_ID, PIN_LOW);
	checkingPassword();
	while (running)
	{
		LCD_voidMoveToNextlineAuto();
		Program();
		
	}
}

void LEDs_Init()
{
	LedConfig(PORTC_ID, PIN3_ID);
	LedConfig(PORTC_ID, PIN4_ID);
	LedConfig(PORTC_ID, PIN5_ID);
}

void BUZZER_Init()
{
	DIO_voidSetPinDirection(PORTC_ID, PIN6_ID, PIN_OUTPUT);
}

void InitCheckPassword(u8 *Str)
{
	LCD_voidClearScreen();
	while(*Str != '\0')
	{
		LCD_voidSendData(*Str);
		Str++;
	}
	for (u8 i=3; i<16; i=i+4)
	{
		LCD_moveCursor(1,i);
		LCD_voidSendData('*');
	}
	LCD_moveCursor(1,3);
}

void checkPassword()
{
	u8 DATA = KEYPAD_u8GetPressedKey();
	if (DATA != KEYPAD_BUTTON_RELEASED)
	{
		M_USART_sendByte(DATA);
		LCD_voidSendData(DATA);
		DataIndex += 4;
		LCD_moveCursor(1,DataIndex);
		if (DataIndex>15)
		{
			LCD_voidClearScreen();
			u8 receivedData = M_USART_recieveByte();
			if (receivedData == 'y')
			{
				LCD_moveCursor(0,0);
				LCD_voidSendString("Correct !!");
				LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION, LED_ON);
				LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_OFF);
				_delay_ms(2000);
				LCD_voidClearScreen();
				running = 1;
				checking = 0;
				DataIndex = 3;
			}
			else if (receivedData == 'n')
			{
				LCD_moveCursor(0,0);
				LCD_voidSendString("Wrong !!");
				LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_ON);
				DIO_voidSetPinValue(PORTC_ID, PIN6_ID, PIN_HIGH);
				_delay_ms(2000);
				LCD_voidClearScreen();
				DataIndex = 3;
				DIO_voidSetPinValue(PORTC_ID, PIN6_ID, PIN_LOW);
				LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_OFF);
				InitCheckPassword("Enter Password: ");
				checkPassword();
			}
			else if (receivedData == 'w')
			{
				LCD_voidClearScreen();
				LCD_voidSendString("Warning ERROR !");
				LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION, LED_OFF);
				LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_ON);
				LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION, LED_OFF);
				DIO_voidSetPinValue(PORTC_ID, PIN6_ID, PIN_HIGH);
				running = 0;
				checking = 0;
				DataIndex = 3;
			}
		}
	}
}

void checkingPassword()
{
	checking = 1;
	InitCheckPassword("Enter Password: ");
	while (checking)
	{
		LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
		checkPassword();
	}
	DataIndex = 3;
}

void DisplayProgamChoices()
{
	LCD_voidClearScreen();
	LCD_voidSendString("1-DP   2-Check");
	LCD_moveCursor(1,0);
	LCD_voidSendString("3-WD 4-Chg PSW");
}

void DepositChoice()
{
	u32 dataSend = 0;
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
	LCD_voidClearScreen();
	LCD_voidSendString("Deposit :");
	LCD_moveCursor(1,0);
	u8 depositing = 1;
	while (depositing)
	{
		u8 DATA = KEYPAD_u8GetPressedKey();
		if (DATA != KEYPAD_BUTTON_RELEASED)
		{
			if (DATA == '=')
			{
				M_USART_sendByte('1');
				M_USART_sendU32(dataSend);
				depositing = 0;
				Program();
			}
			else
			{
				LCD_voidSendData(DATA);
				dataSend = (dataSend * 10) + (DATA - '0');
			}
		}
	}
}

void CheckChoice()
{
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
	u8 balance[10] ;
	LCD_voidClearScreen();
	LCD_voidSendString("Balance :");
	LCD_moveCursor(1,0);
	M_USART_sendByte('2');
	M_USART_receiveString(balance);
	LCD_voidSendString(balance);
	_delay_ms(3000);
	Program();
}

void WithdrawChoice()
{
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
	u32 dataSend = 0;
	LCD_voidClearScreen();
	LCD_voidSendString("withdraw :");
	LCD_moveCursor(1,0);
	u8 withdrawing = 1;
	while (withdrawing)
	{
		u8 DATA = KEYPAD_u8GetPressedKey();
		if (DATA != KEYPAD_BUTTON_RELEASED)
		{
			if (DATA == '=')
			{
				M_USART_sendByte('3');
				M_USART_sendU32(dataSend);
				u8 receivedData = M_USART_recieveByte();
				if (receivedData == 'n')
				{
					LCD_voidClearScreen();
					LCD_voidSendString("Not Enough");
					LCD_moveCursor(1,0);
					LCD_voidSendString("Balance !!!");
					_delay_ms(2000);
					withdrawing = 0;
					Program();
				}
				else
				{
					LCD_voidClearScreen();
					LCD_voidSendString("Withdraw");
					LCD_moveCursor(1,0);
					LCD_voidSendString("Complete !!!");
					_delay_ms(2000);
					withdrawing = 0;
					Program();
				}
			}
			else
			{
				LCD_voidSendData(DATA);
				dataSend = (dataSend * 10) + (DATA - '0');
			}
		}
	}
}

void ChangePSWChoice()
{
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
	M_USART_sendByte('4');
	u8 changing = 1;
	while (changing)
	{
		u8 confirming = 0;
		checking = 1;
		checkingPassword();
		InitCheckPassword("Enter New PSW: ");
		while (!checking)
		{
			LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
			LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
			u8 DATA = KEYPAD_u8GetPressedKey();
			if (DATA != KEYPAD_BUTTON_RELEASED)
			{
				M_USART_sendByte(DATA);
				LCD_voidSendData(DATA);
				DataIndex += 4;
				LCD_moveCursor(1,DataIndex);
				if (DataIndex>15)
				{
					LCD_voidClearScreen();
					u8 receivedData = M_USART_recieveByte();
					if (receivedData == 'y')
					{
						if (confirming == 1)
						{
							LCD_voidSendString("PSW saved !!");
							LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION, LED_ON);
							_delay_ms(2000);
							LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_ON);
							LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_OFF);
							DataIndex = 3;
							checkingPassword();
							DataIndex = 3;
							running = 1;
							checking = 1;
							changing = 0;
							Program();
						}
						else
						{
							InitCheckPassword("Confirm PSW:");
							DataIndex = 3;
							confirming = 1;
						}

					}
					else if (receivedData == 'n')
					{
						LCD_voidSendString("Error !!");
						LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_ON);
						_delay_ms(2000);
						LCD_voidClearScreen();
						DataIndex = 3;
						LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_OFF);
						InitCheckPassword("Enter New PSW: ");
					}
				}
			}
			
		}
		
	}
	
}

void Exit()
{
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION, LED_OFF);
	LedStatus(PORTC_ID, PIN4_ID, SOURCE_CONNECTION, LED_OFF);
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION, LED_ON);
	LCD_voidClearScreen();
	running = 0;
}

void Program()
{
	LedStatus(PORTC_ID, PIN5_ID, SOURCE_CONNECTION,LED_OFF);
	LedStatus(PORTC_ID, PIN3_ID, SOURCE_CONNECTION,LED_ON);
	DisplayProgamChoices();
	while (running)
	{
		u8 DATA = KEYPAD_u8GetPressedKey();
		if (DATA != KEYPAD_BUTTON_RELEASED)
		{
			
			if (DATA == '1')
			{
				DepositChoice();
			}
			else if (DATA == '2')
			{
				CheckChoice();
			}
			else if (DATA == '3')
			{
				WithdrawChoice();
			}
			else if (DATA == '4')
			{
				ChangePSWChoice();
			}
			else
			{
				Exit();
			}
		}
	}
}



