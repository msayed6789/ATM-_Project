/*
 * app.h
 *
 * Created: 5/19/2023 2:52:18 AM
 *  Author: ebrahem
 */ 


#ifndef APP_H_
#define APP_H_

#include "lcd.h"
#include "ex_interrupt.h"
#include "keypad.h"
#include "button.h"
#include "bazzer.h"
#include "string.h"
#include "spi.h"
#define KEYPAD_ROW		PINC2
#define KEYPAD_COL	    PINC5
#define BUTTON_PIN		PIND7
#define BAZZER_PIN		PIND6
#define button_trigger	PIND0


typedef enum
{
	valid,
	blocked
}en_avb_t;

typedef struct
{
	uint8_t PAN[21];
	uint8_t PIN[5];
	en_avb_t Card_Available;
	uint8_t Card_Amount[8];
}st_dataBank_t;


void app_init();


void app_start();



#endif /* APP_H_ */
