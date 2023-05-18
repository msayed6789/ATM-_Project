/*
 * dio.h
 *
 * Created: 4/23/2023 12:46:54 PM
 *  Author: Mohamed Sayed
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "memmap.h"
#include "utlise.h"
#include "standard_type.h"

typedef enum {
	PINA0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	PINs_Total
}PIn_name;

typedef enum{
	OUTPUT,
	INFREE,
	INPUT
}PIN_Status;

typedef enum {
	PA,
	PB,
	PC,
	PD
}PORT_Type;

typedef enum {
	LOW,
	HIGH
}Voltage_type;

void DIO_InitPin (PIn_name pin ,PIN_Status status );

void DIO_WRitePin (PIn_name pin ,Voltage_type s);

Voltage_type DIO_ReadPin(PIn_name pin);

void DIO_WritePort(PORT_Type Port,u8 data);

void DIO_TogglePin(PIn_name pin);





#endif /* DIO_H_ */
