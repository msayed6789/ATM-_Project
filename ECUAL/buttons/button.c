/*
 * Button.c
 *
 * Created: 4/5/2023 4:18:47 AM
 *  Author: Mohamed Sayed 
 */ 
 
 #include "button.h"
static void Time_Count(void);
volatile u16 count=0;
u16 Time_OVF = (u32)(Time_Test*1000000)/(50000*8);

void button_init(PIn_name Buttonpin)
{
	DIO_InitPin ( Buttonpin , INPUT );
}

 Button_Status Button_Check(u8 Button)
 {
	 if(DIO_ReadPin(Button)==0)
	 {
		 while (!DIO_ReadPin(Button));
		 return Pressed;
	 }
	 else 
	 {
		 return NotPressed;
	 }
 }
 
 Button_Status_Time Button_Check_Time(u8 Button)
 {
	 u8 status=0;
	 if(DIO_ReadPin(Button)==0)
	 {
		 Timer1_OCA_SetCallBack(Time_Count);
		 Timer1_OCA_InterruptEnable();
		 Timer1_Init(TIMER1_CTC_OCRA_TOP_MODE,TIMER1_SCALER_64);
		 OCR1A=49999;
		 while (!DIO_ReadPin(Button));
		 Timer_1Stop();
		 if (count>=Time_OVF)
		 {
			 status=Pressed_OverTime;
		 }
		 else
		 {
			 status=Pressed_UnderTime;
		 } 
		 count=0;
	 }
	return status;
 }
 
 static void Time_Count(void)
 {
	 count++;
 }
