/*
 * timer.c
 *
 * Created: 4/6/2023 11:14:21 PM
 *  Author: MOHAMED ABDELSALAM
 */ 

#include "timer.h"


void TIMER_init (u8 Mode,u8 intial_value){
//choose timer mode
TCCR0 &= Mode;
//TimerSet initial value
TCNT0 = intial_value;
}
void TIMER_start (u8 prescaler_value){

TCCR0 |= prescaler_value;  //Set Pre_scaler, for ex:ck(source)(8MHz)/8 to get,
//T(tick) = 1 microseconds
//Stop after one overflow 250 microseconds
}
void TIMER_set(u8 intial_value){
//TimerSet initial value
TCNT0 = intial_value;
}
void TIMER_getStatus(u8 *value){
	if ((TIFR & clear_T0) == 0)
	{
		*value = 0x01;
	}
	else if ((TIFR & clear_T0) == 1)
	{
		*value = 0x00;
		TIFR |= clear_T0;
	}
}
	void TIMER_Stop (void){
		//Timer Stop
		TCCR0 = no_clk;	
	}
	/*************************************************Timer_1***********************************************************/
	/****************************************************Pointer to Function************************************************/
	static void (*Timer1_OCA_Fptr) (void)=NULLPTR;
	/*************************************************************************************************************************/
	void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler)
	{
		switch (mode)
		{
			case TIMER1_NORMAL_MODE:
			CLR_Bit(TCCR1A,WGM10);
			CLR_Bit(TCCR1A,WGM11);
			CLR_Bit(TCCR1B,WGM12);
			CLR_Bit(TCCR1B,WGM13);
			break;
			
			case TIMER1_CTC_OCRA_TOP_MODE:
			CLR_Bit(TCCR1A,WGM10);
			CLR_Bit(TCCR1A,WGM11);
			Set_Bit(TCCR1B,WGM12);
			CLR_Bit(TCCR1B,WGM13);
			break;
			
			
			case TIMER1_FASTPWM_OCRA_TOP_MODE:
			Set_Bit(TCCR1A,WGM10);
			Set_Bit(TCCR1A,WGM11);
			Set_Bit(TCCR1B,WGM12);
			Set_Bit(TCCR1B,WGM13);
			break;
		}

		TCCR1B&=0XF8;
		TCCR1B|=scaler;
	}
	

	/****************************Timer 1 Interrupt functions**************************************/

	void Timer1_OCA_InterruptEnable(void)
	{
		Set_Bit(TIMSK,OCIE1A);
	}
	void Timer1_OCA_InterruptDisable(void)
	{
		CLR_Bit(TIMSK,OCIE1A);
	}

	/*********************************Timer 1 Call Back functions*****************************************/

	void Timer1_OCA_SetCallBack(void(*LocalFptr)(void))
	{
		Timer1_OCA_Fptr=LocalFptr;
	}

	/*********************************Timer 1 ISR functions*********************************************/
	ISR(TIMER1_OCA_vect)
	{
		if(Timer1_OCA_Fptr!=NULLPTR)
		{
			Timer1_OCA_Fptr();
		}
	}
/*****************************************************Timer_2***********************************************************/
void TIMER2_init (u8 Mode,u8 intial_value){
	//choose timer mode
	TCCR2 &= Mode;
	//TimerSet initial value
	TCNT2 = intial_value;
}
void TIMER2_start (u8 prescaler_value){

	TCCR2 |= prescaler_value;  //Set Pre_scaler, for ex:ck(source)(8MHz)/8 to get,
	//T(tick) = 1 microseconds
	//Stop after one overflow 250 microseconds
}
void TIMER2_set(u8 intial_value){
	//TimerSet initial value
	TCNT2 = intial_value;
}
void TIMER2_getStatus(u8 *value){
	if ((TIFR & clear_T2) == 0)
	{
		*value = 0x01;
	}
	else if ((TIFR & clear_T2) == 1)
	{
		*value = 0x00;
		TIFR |= clear_T2;
	}
}
void TIMER2_Stop (void){
	//Timer Stop
	TCCR2 = no_clk;
}
