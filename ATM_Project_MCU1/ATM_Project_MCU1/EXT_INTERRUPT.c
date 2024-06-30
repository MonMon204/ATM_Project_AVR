/*
 * INTERRUPT.c
 *
 * Created: 2/17/2024 7:54:01 PM
 *  Author: Mina Waguih
 */ 


#include "EXT_INTERRUPT.h"


void (*EXTI_CallBack[3])() = { NULL };  // array of pointer to function to used in the CallBack function



void EXTI_voidGlobalINT_Enable()
{
	SET_BIT(SREG,SREG_I);
}

void EXTI_voidGlobalINT_Disable()
{
	CLR_BIT(SREG,SREG_I);
}

void EXTI_void_INT_Init(u8 Copy_u8INT_Number, u8 Copy_u8Sense_Control)
{
	switch (Copy_u8INT_Number)
	{
	case INT0:
				SET_BIT(GICR,GICR_INT0);
				switch (Copy_u8Sense_Control)
				{
				case LOW_LEVEL:
								CLR_BIT(MCUCR,MCUCR_ISC00);
								CLR_BIT(MCUCR,MCUCR_ISC01);
								break;
				case LOGICAL_CHANGE:
								SET_BIT(MCUCR,MCUCR_ISC00);
								CLR_BIT(MCUCR,MCUCR_ISC01);
								break;
				case FALLNG_EDGE:
								CLR_BIT(MCUCR,MCUCR_ISC00);
								SET_BIT(MCUCR,MCUCR_ISC01);
								break;
				case RISING_EDGE:
								SET_BIT(MCUCR,MCUCR_ISC00);
								SET_BIT(MCUCR,MCUCR_ISC01);
								break;
				}
				break;
	case INT1:
				SET_BIT(GICR,GICR_INT1);
				switch (Copy_u8Sense_Control)
				{
					case LOW_LEVEL:
									CLR_BIT(MCUCR,MCUCR_ISC10);
									CLR_BIT(MCUCR,MCUCR_ISC11);
									break;
					case LOGICAL_CHANGE:
									SET_BIT(MCUCR,MCUCR_ISC10);
									CLR_BIT(MCUCR,MCUCR_ISC11);
									break;
					case FALLNG_EDGE:
									CLR_BIT(MCUCR,MCUCR_ISC10);
									SET_BIT(MCUCR,MCUCR_ISC11);
									break;
					case RISING_EDGE:
									SET_BIT(MCUCR,MCUCR_ISC10);
									SET_BIT(MCUCR,MCUCR_ISC11);
									break;
				}
				break;
	case INT2:
				SET_BIT(GICR,GICR_INT2);
				switch (Copy_u8Sense_Control)
				{
					case FALLNG_EDGE:
									CLR_BIT(MCUCSR,MCUCSR_ISC2);
									break;
					case RISING_EDGE:
									SET_BIT(MCUCSR,MCUCSR_ISC2);
									break;
				}
				break;
	}
}

void EXTI_voidDisableInterrupt(u8 Copy_u8INT_Number)
{
	switch (Copy_u8INT_Number)
	{
	case INT0:
				CLR_BIT(GICR,GICR_INT0);
				break;
	case INT1:
				CLR_BIT(GICR,GICR_INT1);
				break;
	case INT2:
				CLR_BIT(GICR,GICR_INT2);
				break;
	}
}

u8 EXTI_u8GetFlag(u8 Copy_u8INT_Number)
{
	if (Copy_u8INT_Number >= INT2 && Copy_u8INT_Number <= INT1)
	{
		return GET_BIT(GIFR,Copy_u8INT_Number);
	}
	return 0;
}

void EXTI_voidSetCallBack(void (*Copy_pvoidCallBack)(void) , u8 Copy_u8INT_Number)
{
	if (Copy_pvoidCallBack != NULL)
	{
		switch (Copy_u8INT_Number)
		{
		case INT0:
					EXTI_CallBack[0] = Copy_pvoidCallBack;
					break;
		case INT1:
					EXTI_CallBack[1] = Copy_pvoidCallBack;
					break;
		case INT2:
					EXTI_CallBack[2] = Copy_pvoidCallBack;
					break;
		}
	} 
	else
	{
	}
}



void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	if( EXTI_CallBack[0] != NULL )
	{	
		EXTI_CallBack[0]();      /*  Call The Global Pointer to Function   */
	}

}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	if (EXTI_CallBack[1] != NULL)
	{
		EXTI_CallBack[1]();
	}
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	if (EXTI_CallBack[2] != NULL)
	{
		EXTI_CallBack[2]();
	}
}

