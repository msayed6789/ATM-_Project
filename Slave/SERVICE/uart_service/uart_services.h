/*
 * uart_services.h
 *
 * Created: 5/1/2023 12:40:11 AM
 *  Author: Mohamed Sayed
 */ 


#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_

#include "uart.h"


#define END_SEND           0x0D
#define INVALID_NUM        0x00


/*******************************************************Transmitter************************************************************************************************/
void uart_transmitString(u8*str);
void uart_transmitString_Interrupt(u8*str);
void uart_transmitNumber_MCU(u32 num);
void uart_transmitNumber_MCU_Interrupt(u32* num);


/*******************************************************Receiver*********************************************************************************************/
void uart_recieverString(u8*str);
void uart_recieverString_Interrupt(u8*str);
void uart_recieveNumber_MCU(u32* num);
void uart_recieveNumber_MCU_Interrupt(u32* num);


#endif /* UART_SERVICES_H_ */
