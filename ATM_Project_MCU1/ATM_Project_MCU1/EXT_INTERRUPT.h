/*
 * INTERRUPT.h
 *
 * Created: 2/17/2024 7:54:18 PM
 *  Author: Mina Waguih
 * Description: Header file for the AVR External Interrupt driver
 */ 

#ifndef EXT_INTERRUPT_H
#define EXT_INTERRUPT_H

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#define NULL                 0

#define SREG                 *((volatile u8*) 0x5F)  //Status register ---------- Global Interrupt Enable
#define SREG_I               7

#define GICR                 *((volatile u8*) 0x5B)  //General Interrupt Control Register ------- control the EXTI enable
#define GICR_INT0            6
#define GICR_INT1            7
#define GICR_INT2            5

#define GIFR                 *((volatile u8*) 0x5A)  //General Interrupt Flag Register -------- EXTI flag
#define GIFR_INT0            6
#define GIFR_INT1            7
#define GIFR_INT2            5

#define MCUCR                *((volatile u8*) 0x55)  //MCU Control Register --------- EXTI0,1 status
#define MCUCR_ISC00          0
#define MCUCR_ISC01          1
#define MCUCR_ISC10          2
#define MCUCR_ISC11          3

#define MCUCSR               *((volatile u8*) 0x54)  //MCU Control and Status Register -------- EXTI2 status
#define MCUCSR_ISC2          6

#define      LOW_LEVEL        0
#define      LOGICAL_CHANGE   1
#define      FALLNG_EDGE      2
#define      RISING_EDGE      3


/* Copy_u8INT_Number */
#define INT1     7
#define INT0     6
#define INT2     5


#define      ENABLED         1
#define      DISABLED        0


void EXTI_voidGlobalINT_Enable();

void EXTI_voidGlobalINT_Disable();

void EXTI_void_INT_Init(u8 Copy_u8INT_Number, u8 Copy_u8Sense_Control);

void EXTI_voidDisableInterrupt(u8 Copy_u8INT_Number);

u8   EXTI_u8GetFlag(u8 Copy_u8INT_Number);

void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number);


#endif
