/*
 * Timer.c
 *
 * Created: 3/9/2024 7:51:02 PM
 *  Author: Mina Waguih
 */ 


#include "Timer.h"


static void (*Global_pvTimerCTCCallBack[2])(void)={NULL,NULL};


void M_TIMER0_voidInit()
{
	SET_BIT(SREG,SREG_I);
	TCNT0 = TIMER_U8_PRELOAD_INITIAL_VALUE;
	
	#if  TIMER0_Mode == TIMER0_Normal         /*Choose Normal Mode*/
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		
		SET_BIT(TIMSK,TIMSK_TOIE0);
		
	#elif TIMER0_Mode == TIMER0_CTC           /*Choose CTC Mode*/
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		
		SET_BIT(TIMSK,TIMSK_OCIE0);
		
		OCR0 = OCR0_valu_CTC;
		
	#elif TIMER0_Mode == TIMER0_Fast_PWM      /*Choose PWM Mode*/
		SET_BIT(TCCR0, TCCR0_WGM00);
		SET_BIT(TCCR0, TCCR0_WGM01);

		/*Set OC0 on top Clear OC0 on Compare => Non Inverting*/
		CLR_BIT(TCCR0, TCCR0_COM00);
		SET_BIT(TCCR0, TCCR0_COM01);

		OCR0=OCR0_valu_PWM;
		
	#elif TIMER0_Mode == TIMER0_correct_PWM    /*Choose Correct PWM Mode*/
		SET_BIT(TCCR0, TCCR0_WGM00);
		CLR_BIT(TCCR0, TCCR0_WGM01);

		/*Set OC0 on top Clear OC0 on Compare => Non Inverting*/
		CLR_BIT(TCCR0, TCCR0_COM00);
		SET_BIT(TCCR0, TCCR0_COM01);

		OCR0=OCR0_valu_PWM;
		
	#else
		#error "wrong sense conrol config"
	#endif
	
		
	/* Prescaler */
	
	#if   TIMER0_PRESCALER   ==  Prescale_CLK8
	CLR_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);
	#elif  TIMER0_PRESCALER   ==  Prescale_CLK64
	SET_BIT(TCCR0, TCCR0_CS00);
	SET_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);
	#elif  TIMER0_PRESCALER   ==  Prescale_CLK256
	CLR_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);
	#elif  TIMER0_PRESCALER   ==  Prescale_CLK1024
	SET_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	SET_BIT(TCCR0, TCCR0_CS02);
	#else
		#error "wrong Prescaler config"
	#endif
	
	
}


void M_TIMER0_void_Disable()
{
	CLR_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);
	CLR_BIT(SREG,SREG_I);
}


void M_TIMER0_voidSetDuty(u8 Copy_u8DutyCycle)
{
	/*Check for mode in PWM*/
	OCR0 = Copy_u8DutyCycle;  /*Sets OCR0 value*/
}


void M_TIMER0_voidTimer0SetCallBack(void (*Copy_pvCallBackFunc)(void),u8 copy_u8TimersINTRPTIndex)
{

	if(Copy_pvCallBackFunc != NULL)
	{
		switch(copy_u8TimersINTRPTIndex)
		{
			case TIMERS_U8_CMP_MTH_INTRPT:
			Global_pvTimerCTCCallBack[TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN] = Copy_pvCallBackFunc;
			break;
			case TIMERS_U8_OVF_INTRPT:
			Global_pvTimerCTCCallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN] = Copy_pvCallBackFunc;
			break;
			default:   break;/* return error */
		}
	}
	else
	{
		/* return error */
	}

}


/*prototype for ISR of TIMER0 CTC*/
void __vector_10(void)	__attribute__((signal));
void __vector_10(void)
{
	static u16 L_u16CounterCTC = 0;
	L_u16CounterCTC++;
	if(L_u16CounterCTC == TIMER_U8_CTC_NO_OF_OVF)
	{
		/*clear counter*/
		L_u16CounterCTC = 0;
		/*call callback function*/
		if(Global_pvTimerCTCCallBack[TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN] != NULL)  /* mistake or more save*/
		{
			Global_pvTimerCTCCallBack[TIMERS_U8_CMP_MTH_INTRPT_ENB_PIN]();
		}
	}
}

/*prototype for ISR of TIMER0 OVF*/
void __vector_11(void)	__attribute__((signal));
void __vector_11(void)
{
	static u16 L_u16CounterOVF = 0;
	L_u16CounterOVF++;
	if(L_u16CounterOVF == TIMER_U8_NORMAL_NO_OF_OVF)
	{
		/*update preload value*/
		TCNT0 = TIMER_U8_PRELOAD_INITIAL_VALUE;
		/*clear the OVF counter*/
		L_u16CounterOVF = 0;
		/*call APP function*/
		if(Global_pvTimerCTCCallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN] != NULL)
		{
			// MTIMER0_void_Disable();
			Global_pvTimerCTCCallBack[TIMERS_U8_OVF_INTRPT_ENB_PIN]();
		}
	}
}