/*
 * FUNCTIONS.h
 *
 * Created: 6/28/2024 1:41:08 PM
 *  Author: dell
 */ 

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO.h"
#include "Timer.h"
#include "USART.h"
#include "KEYPAD.h"
#include "LCD.h"
#include "LED.h"
#include <util/delay.h>

void mainLoop();

void LEDs_Init();

void BUZZER_Init();

void  InitCheckPassword();

void checkPassword();

void checkingPassword();

void DisplayProgamChoices();

void DepositChoice();

void CheckChoice();

void WithdrawChoice();

void ChangePSWChoice();

void Exit();

void Program();






#endif