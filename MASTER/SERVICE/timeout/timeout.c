/*
 * timeout.c
 *
 * Created: 4/23/2023 1:08:16 PM
 *  Author: Mohamed Sayed
 */ 

#include "timeout.h"
static void TIMER_out_Stop (void);
static void TIME_out_init (void);
static void TIMER_ISR(void);
static void Timer0_Ovf_CALLBACK (void (*copyFuncptr) (void));
static void (*Callbackptr10) (void) = 0;

u32 TIME_OUT_=0;
u32 TIME_Count=0;
u8 Time_Flag=0;

static void Timer0_Ovf_CALLBACK (void (*copyFuncptr) (void)){
	Callbackptr10 = copyFuncptr;
}
ISR (TIMER0_OVF){
	if(Callbackptr10 == 0){
	}
	else{
		Callbackptr10();
	}
}
static void TIME_out_init (void){
	//choose timer mode
	TIMER_init (normal,Intial_value_time_out); // start counting from 6
	
	Set_Bit(TIMSK,TOIE0); //enable interrupt overflow of timer 0
	Timer0_Ovf_CALLBACK (TIMER_ISR);
}

void TIME_out (u32 milliseconds)
{	Time_Flag = 1;
	TIME_Count=0;
	TIME_OUT_=milliseconds*4;
	TIME_out_init ();
	TIMER_start (pres_8);  //Set Pre_scaler, for ex:ck(8MHz)/1 to get,
}

static void TIMER_out_Stop (void)
{
	//Timer Stop
	TIMER_Stop ();
	CLR_Bit(TIMSK,TOIE0); //disable interrupt overflow of timer 0
	
}
void TIMER_ISR(void)
{
	TIME_Count++;
	if (TIME_Count == TIME_OUT_)
	{
		Time_Flag = 0;
		TIMER_out_Stop ();
	}

	TIMER_set(Intial_value_time_out);
}
