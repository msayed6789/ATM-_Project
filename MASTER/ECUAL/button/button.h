/*
 * Button.h
 *
 * Created: 4/5/2023 4:19:28 AM
 *  Author: Mohamed Sayed
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "dio.h"
#include "timer.h"

#define  Time_Test  2      //Time in sec
/*******************************************************************************/
typedef enum{
	Pressed,
	NotPressed	
}Button_Status;

typedef enum{
	Pressed_UnderTime=22,
	Pressed_OverTime=44
}Button_Status_Time;

void button_init(PIn_name pin);

Button_Status Button_Check(u8 Button);

Button_Status_Time Button_Check_Time(u8 Button);



#endif /* BUTTON_H_ */
