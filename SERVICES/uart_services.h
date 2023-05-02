/*
 * uart_services.h
 *
 * Created: 5/2/2023 12:40:11 AM
 *  Author: AIO
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_
#include "uart.h"


#define END_SEND           0x0D
#define INVALID_NUM        0x00

/*******************************************************Transmitter************************************************************************************************/
void uart_transmitString(u8*str);
void uart_transmitString_Interrupt(u8*str);
void uart_transmitNumber(u32 num);
void uart_transmitNumber_Interrupt(u32 num);
void uart_transmitStringCheckSum(u8*str);        //firstly send the length, then send the string, finally send the sum of data in string

/*******************************************************Receiver*********************************************************************************************/
void uart_recieverString(u8*str);
void uart_recieverString_Interrupt(u8*str);
void uart_recieveNumber(u16* num);
void uart_recieveNumber_Interrupt(u16* num);
u8   uart_recieveStringCheckSum(u8*str);

#endif /* UART_SERVICES_H_ */