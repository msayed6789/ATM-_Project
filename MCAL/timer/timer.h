/*
 * timer.h
 *
 * Created: 4/6/2023 11:16:46 PM
 *  Author: MOHAMED ABDELSALAM
 */ 


#ifndef TIMER_H_
#define TIMER_H_

//#include "memmap.h"
//#include "utlise.h"
//#include "standard_type.h"
#include "MEMMAP.h"
#include "Standard_Type.h"
#include "Utlise.h"

#define normal 0x00
#define no_clk 0x00
#define zero_intial 0x00
#define ticks_250 0x07 
#define ticks_16 0xFB  
#define pres_1 0x01
#define pres_8 0x02
#define pres_64 0x03
#define pres_256 0x04
#define pres_1024 0x05
#define clear_T0 0x01
void TIMER_init (u8 Mode,u8 intial_value);
void TIMER_start (u8 prescaler_value);
void TIMER_set(u8 intial_value);
void TIMER_getStatus(u8 *value);
void TIMER_Stop (void);
/**************************************************Timer_1***************************************************************/
typedef enum{
	TIMER1_SCALER_1=1,
	TIMER1_SCALER_8,
	TIMER1_SCALER_64,
	TIMER1_SCALER_256,
	TIMER1_SCALER_1024,
}Timer1Scaler_type;

typedef enum
{
	TIMER1_NORMAL_MODE=0,
	TIMER1_CTC_OCRA_TOP_MODE,
	TIMER1_FASTPWM_OCRA_TOP_MODE,
}Timer1Mode_type;

#define Timer_1Stop()     TCCR1B&=0XF8

void Timer1_Init( Timer1Mode_type mode,Timer1Scaler_type scaler);

/***************************************Interrupt************************************************************************************************************/
void Timer1_OCA_InterruptEnable(void);
void Timer1_OCA_InterruptDisable(void);
void Timer1_OCA_SetCallBack(void(*LocalFptr)(void));




/**************************************************Timer_2***************************************************************/

#define normal 0x00
#define no_clk 0x00
#define zero_intial 0x00
#define ticks_250 0x07
#define ticks_100 0x9C
#define pres_1 0x01
#define pres_8 0x02
#define pres_64 0x03
#define pres_256 0x04
#define pres_1024 0x05
#define clear_T2 0x40
void TIMER2_init (u8 Mode,u8 intial_value);
void TIMER2_start (u8 prescaler_value);
void TIMER2_set(u8 intial_value);
void TIMER2_getStatus(u8 *value);
void TIMER2_Stop (void);













#endif /* TIMER_H_ */