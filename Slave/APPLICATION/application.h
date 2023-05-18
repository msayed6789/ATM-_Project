/*
 * application.h
 *
 * Created: 5/6/2023 3:37:08 AM
 *  Author: lenovo
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "eeprom.h"
#include "uart_services.h"
#include "delay.h"
#include "spi.h"
#include "dio.h"

typedef enum{
	PROGRAMMING_MODE,
	USER_MODE,
	CHECK_MODE
}en_card_mode;
void APP_init(void);
void APP_start(void);




#endif /* APPLICATION_H_ */
