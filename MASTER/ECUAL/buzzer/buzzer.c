/*
 * bazzer.c
 *
 * Created: 4/23/2023 9:58:05 AM
 *  Author: ebrahem
 */ 


#include "bazzer.h"



void bazz_init(PIn_name pin_num)
{
	DIO_InitPin(pin_num , OUTPUT);
}

void bazz_ON(PIn_name pin_num)
{
	DIO_WRitePin(pin_num , HIGH);
}


void bazz_OFF(PIn_name pin_num)
{
	DIO_WRitePin(pin_num,LOW);
}	
