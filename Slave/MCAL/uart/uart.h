/*
 * uart.h
 *
 * Created: 4/29/2023 2:24:56 AM
 *  Author: Mohamed Sayed
 */ 


#ifndef UART_H_
#define UART_H_

#include "memmap.h"
#include "utlise.h"
#include "standard_type.h"

#define F8MHZ   8
#define F4MHZ   4

#define FCPU   F8MHZ                         //The CPU Frequency in MHz
 
#define ERROR_DATA         'E'
#define DATA_DONE          'D'



typedef enum {
	Baudrate2400,
	Baudrate4800,
	Baudrate9600,
	Baudrate144K,
	Baudrate_Total
}Uart_BaudRate_en;

typedef enum {
	Normal_Speed,
	Double_Speed,
	Speed_Total
}Uart_Speed_en;

typedef enum{
	Asynchronous,
	Synchronous
}Uart_Mode_en;

typedef enum{
	Even,
	Odd,
	No_Parity
}Uart_Parity_en;

typedef enum{
	StopBit_1,
	StopBit_2
}Uart_StopBit_en;

typedef enum{
	DataBit_5,
	DataBit_6,
	DataBit_7,
	DataBit_8,
}Uart_DataBit_en;

typedef enum{
	Transmitter,
	Reciever,
	TR
}Uart_Enable_en;

void uart_init(Uart_BaudRate_en BaudRate,Uart_Speed_en Speed,Uart_Mode_en mode,Uart_Parity_en parity,Uart_StopBit_en stopbit,Uart_DataBit_en databit,Uart_Enable_en enable);
/*******************************************************Transmitter************************************************************************************************/
void uart_transmit(u8 data);
void uart_transmitNoBlock(u8 data);
/**************************************************Transmitter Interrupt********************************************************************************************/
void uart_transmitComPlete_InterruptEnable(void);
void uart_transmitComPlete_InterruptDisable(void);
void uart_transmitComPlete_InterruptSetCallback(void(*fptr)(void));

/*******************************************************Receiver*********************************************************************************************/
u8 uart_reciever(void);
u8 uart_recieverNoBlock(void);
/*******************************************Receiver Interrupt***********************************************************************************************/
void uart_recieveComPlete_InterruptEnable(void);
void uart_recieveComPlete_InterruptDisable(void);
void uart_recieveComPlete_InterruptSetCallback(void(*fptr)(void));


#endif /* UART_H_ */
