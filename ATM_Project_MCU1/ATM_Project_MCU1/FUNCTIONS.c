/*
 * FUNCTIONS.c
 *
 * Created: 6/28/2024 1:32:49 PM
 *  Author: dell
 */ 

#include "FUNCTIONS.h"


volatile u8 Password[] = "1234";
volatile u32 Balance = 100;

volatile u8 passTries = 1;
const u8 maxPassTries = 3;


void check_Password()
{
	u8 checking = 1;
	while (checking)
	{
		u8 checkPassword[5] = "";
		u8 receivedData[2];
		for (u8 i=0; i<4; i++)
		{
			receivedData[0] = M_USART_recieveByte();
			receivedData[1] = '\0';
			strcat(checkPassword, receivedData);
		}
		if (strcmp(Password,checkPassword) == 0)
		{
			M_USART_sendByte('y');
			passTries = 1;
			checking = 0;
		}
		else
		{
			
			if (passTries==maxPassTries)
			{
				M_USART_sendByte('w');
				passTries = 1;
				while (M_USART_recieveByte() != 'x')
				{}
			}
			else
			{
				M_USART_sendByte('n');
				passTries++;
			}
		}
	}
}


void ProgramChoices()
{
	u8 receivedData = M_USART_recieveByte();
	if (receivedData == '1')
	{
		u32 data = M_USART_receiveU32();
		Balance += data; 
	}
	else if (receivedData == '2')
	{
		u8 sendData[10] ;
		convertIntToString(Balance,sendData);
		M_USART_sendString(sendData);
	}
	else if (receivedData == '3')
	{
		u32 data = M_USART_receiveU32();
		if (Balance < data)
		{
			M_USART_sendByte('n');
		} 
		else
		{
			Balance -= data;
			M_USART_sendByte('y');
		}
	}
	else if (receivedData == '4')
	{
		check_Password();
		u8 checkPassword[2][5] = {"",""} ;
		for (u8 i=0; i<2; i++)
		{
			u8 receivedData[2];
			for (u8 j=0; j<4; j++)
			{
				receivedData[0] = M_USART_recieveByte();
				receivedData[1] = '\0';
				strcat(checkPassword[i], receivedData);
			}
			if (i == 0)
			{
				if (strcmp(Password,checkPassword[0]) == 0)
				{
					M_USART_sendByte('n');
				}
				else
				{
					M_USART_sendByte('y');
				}
			}
			else
			{
				if (strcmp(checkPassword[1], checkPassword[0]) != 0)
				{
					M_USART_sendByte('n');
				}
				else
				{
					strcpy(Password,checkPassword[0]);
					M_USART_sendByte('y');
					passTries = 1;
					check_Password();
				}
			}
		}
	}
	else if (receivedData == 'x')
	{
		check_Password();
		ProgramChoices();
	}
}

void convertIntToString(u32 intnumber, u8 *Str) {
	sprintf(Str, "%d", intnumber);
	strcat(Str, "#");
}

