/*
 * Timer.h
 *
 * Created: 3/9/2024 7:51:16 PM
 *  Author: Mina Waguih
 */ 

#ifndef  TIMER_H
#define  TIMER_H

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define NULL             0


#define SREG             *((volatile u8*)0x5F) //status register----------------global interrupt enable
#define SREG_I               7


#define TCCR0            *((volatile u8*)0x53)   // Timer/Counter Control Register
#define TCCR0_WGM00          6                
#define TCCR0_WGM01          3                
#define TCCR0_CS02           2                
#define TCCR0_CS01           1                
#define TCCR0_CS00           0                
#define TCCR0_COM00          4                
#define TCCR0_COM01          5                


#define TCNT0            *((volatile u8*)0x52)   // Timer/Counter Register

#define OCR0             *((volatile u8*)0x5C)   // Output Compare Register

#define TIMSK            *((volatile u8*)0x59)   // Timer/Counter Interrupt Mask Register
#define TIMSK_TOIE0          0
#define TIMSK_OCIE0          1


#define TIFR             *((volatile u8*)0x58)   // Timer/Counter Interrupt Flag Register
#define TIFR_TOV0            0
#define TIFR_OCF0            1


/* Define TIMER0 Mode Options */

#define TIMER0_Normal            1
#define TIMER0_CTC               2
#define TIMER0_Fast_PWM          3
#define TIMER0_correct_PWM       4

/* Compare Output Mode Options, non-PWM Mode */

#define OC0_Disconnect           0
#define Toggle_OC0               1
#define Clear_OC0                2
#define Set_OC0                  3

/* Compare Output Mode Options, Fast PWM Mode */

#define OC0_Disconnect           0
#define Clear_OC0_Set_OC0_atTop  2
#define Set_OC0_Clear_OC0_atTop  3

/* Compare Output Mode Options, Phase Correct PWM Mode */

#define OC0_Disconnect                           0
#define Clear_OC0_Upcomming_Set_OC0_Downcomming  2
#define Set_OC0_Upcomming_Clear_OC0_Downcomming  3

/* Clock Select */

#define NO_Clock                    0
#define Prescale_CLK                1
#define Prescale_CLK8               2
#define Prescale_CLK64              3
#define Prescale_CLK256             4
#define Prescale_CLK1024            5
#define External_CLK_Falling_Edge   6
#define External_CLK_Rising_Edge    7


#define TIMER0_PRESCALER         Prescale_CLK8


/*Interrupt Vectors for TIPMERS0*/
#define TIMERS_U8_CMP_MTH_INTRPT			11	/*Timer Counter0 Output Compare Match Interrupt Enable*/
#define TIMERS_U8_OVF_INTRPT				12	/*Timer Counter0 Overflow Interrupt Enable*/


#define TIMERS_U8_OVF_INTRPT_ENB_PIN			0	/*Timer Counter0 Overflow Interrupt Enable*/
#define TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN		1	/*Timer Counter0 Output Compare Match Interrupt Enable*/


// Set the Timer Mode
#define  TIMER0_Mode   TIMER0_Normal


/* 1. The No of overflow you want to get the required time delay.
 * 2. The preload value to make sure you set the exact time.
 */
#define TIMER_U8_NORMAL_NO_OF_OVF					457
#define TIMER_U8_PRELOAD_INITIAL_VALUE				195


/* 1. The No of overflow you want to get required time delay.
 * 2. The Initial value you want to make the timer start from, this value ranges from 0 to 2^n(max).
 */
#define TIMER_U8_CTC_NO_OF_OVF						500
#define TIMER_U8_SET_CTC_INITIAL_VALUE				100


#define OCR0_valu_CTC								125
#define OCR0_valu_PWM								250




void M_TIMER0_voidInit();

void M_TIMER0_void_Disable();

void M_TIMER0_voidSetDuty(u8 Copy_u8DutyCycle);

void M_TIMER0_voidTimer0SetCallBack(void (*Copy_pvCallBackFunc)(void),u8 copy_u8TimersInterruptIndex);


#endif
