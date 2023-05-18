/*
 * i2c.h
 *
 * Created: 4/30/2023 9:39:06 PM
 *  Author: Mohamed Abdelsalam
 */ 
#ifndef I2C_H_
#define I2C_H_
#include "memmap.h"
#include <math.h>
#define F_CPU 8000000U
#define SLA_CLK 400000U
#define TWI_prescalar_1 0x00
#define TWI_prescalar_4 0x01
#define TWI_prescalar_16 0x02
#define TWI_prescalar_64 0x03
#define BITRATE	(((F_CPU/SLA_CLK)-16)/(2*pow(4,TWI_prescalar_1)))
#define READ 1
#define WRITE 0
#define NACK 1
#define ACK 0

/*states*/
#define START_STATE 0x08
#define REPEATED_START_STATE 0x10
#define SLA_W_ACK_STATE 0x18
#define SLA_W_NACK_STATE 0x20
#define DATA_WRITE_ACK_STATE 0x28
#define DATA_WRITE_NACK_STATE 0x30
#define SLA_R_ACK_STATE 0x40
#define SLA_R_NACK_STATE 0x48
#define DATA_READ_ACK_STATE 0x50
#define DATA_READ_NACK_STATE 0x58
/*RETURNS*/
#define EVENT_OK 0
#define START_NOT_SENT 1
#define REPEATED_START_NOT_SENT 2
#define SLA_W_ACK_SENT 3
#define SLA_W_NACK_SENT 4
#define SLA_R_ACK_SENT 5
#define SLA_R_NACK_SENT 6
#define SLA_RW_FAILED 7
#define DATA_WRITE_ACK_SENT 8
#define DATA_WRITE_NACK_SENT 9
#define DATA_WRITE_FAILED 10
#define DATA_READ_ACK_SENT 11
#define DATA_READ_NACK_SENT 12
#define DATA_READ_FAILED 13
#define DATA_RW_FAILED 14

/*APIs*/
void TWI_init(void);
u8 TWI_start(void);
u8 TWI_repeated_start(void);
u8 TWI_address_select (u8 address,u8 rw);
u8 TWI_data_event (u8 *data,u8 rw,u8 ack);
void TWI_stop(void);
#endif /* I2C_H_ */
