/*
 * delay.c
 *
 * Created: 4/16/2023 8:16:02 PM
 *  Author: Mohamed Abdelsalam
 */ 
#include "delay.h"
void Delay_ms(u32 milliseconds)
{
	TIMER2_init (normal,ticks_250);
	TIMER2_start (pres_8);
	u32 i;
	u8 counter;
	for(i=0;i< milliseconds ;i++)
	{
		// N = (1000us)/(250u);  //= 4 without approximation
		//for one millisecond delay iterate 4 times of timer2 overflow
		counter = 0;
		while(counter<4)
		{	
		while((TIFR & clear_T2) == 0);
		TIMER2_set(ticks_250);
		TIFR |= clear_T2;
		counter++;
		}
	}
	TIMER2_Stop ();
}

void delay_us(u32 microseconds)
{
	TIMER2_init (normal,ticks_250);
	TIMER2_start (pres_8);
	u32 i;
	for(i=0;i< microseconds ;i++){
		// N = (1000us)/(250u);  //= 4 without approximation
		//for one millisecond delay iterate 4 times of timer2 overflow
		while((TIFR & clear_T2) == 0);
		TIMER2_set(ticks_100);
		TIFR |= clear_T2;
	}
	TIMER2_Stop ();
}
