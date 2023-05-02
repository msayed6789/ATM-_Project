#include "keypad.h"


PIn_name FIRST_OUTPUt;
PIn_name FIRST_INPUT;
volatile u8 Timeout_Count=0;
static u8 KEYPAD_GetKey(void);
extern volatile u8 Time_Flag ;

Keypad_Status_en KEYPAD_Init(PIn_name First_Output,PIn_name Firs_Input)
{
	u8 i=0;
	if (First_Output-Firs_Input>=ROW||First_Output-Firs_Input<=-ROW)
	{
		FIRST_OUTPUt=First_Output;
		FIRST_INPUT=Firs_Input;
		for (i=0;i<ROW;i++)
		{
			DIO_InitPin(First_Output+i,OUTPUT);
		}
		for (i=0;i<COL;i++)
		{
			DIO_InitPin(Firs_Input+i,INPUT);
		}
		return Done;
	}
	return Error;
}
static u8 KEYPAD_GetKey(void)
{
	u8 key=NO_KEY;
	u8 r=0;
	u8 c=0;
	u8 i=0;
	for (i=0;i<r;i++)
	{
		DIO_WRitePin(FIRST_OUTPUt+i,HIGH);
	}
	for (r=0;r<ROW;r++)
	{
		DIO_WRitePin(FIRST_OUTPUt+r,LOW);
		for (c=0;c<COL;c++)
		{
			if (DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key = KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_WRitePin(FIRST_OUTPUt+r,HIGH);
	}
	return key;
}

u8 KEYPAD_GetNum_time(u32 timeout) //timeout is time in sec
{
	u8 key=NO_KEY;
	u8 num=0;
	Timeout_Count=timeout/(50*32);
	TIME_out (timeout*1000);
	while(Time_Flag==1)
	{
		key=KEYPAD_GetKey();
		if(key!=NO_KEY)
		{
			num=key-'0';
			return num;
		}
	}
	return key;
}
