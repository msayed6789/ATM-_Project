/*
 * i2c.c
 *
 * Created: 4/30/2023 9:39:38 PM
 *  Author: Mohamed Abdelsalam
 */ 
#include "i2c.h"
void TWI_init(void)
{
	TWSR = TWI_prescalar_1;
	TWBR = BITRATE;
}
u8 TWI_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Send START condition 
	while (!(TWCR & (1<<TWINT)));			/*Wait for TWINT Flag set.
		This indicates that the START condition has been transmitted*/
	if ((TWSR & 0xF8) != START_STATE) //Check value of TWI Status Register, Mask prescaler bits(0xF8). 
	{
		return START_NOT_SENT;	//If status different from START STATE
	}
	else
	{
		return EVENT_OK;	//If status different from START STATE
	}
	
}
u8 TWI_repeated_start(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); //Send START condition 
	while (!(TWCR & (1<<TWINT)));			/*Wait for TWINT Flag set.
		This indicates that the START condition has been transmitted*/
	if ((TWSR & 0xF8) != REPEATED_START_STATE) //Check value of TWI Status Register, Mask prescaler bits(0xF8). 
	{
		return REPEATED_START_NOT_SENT;	//If status different from REPEATED START STATE
	}
	else
	{
		return EVENT_OK;	//If status different from REPEATED START STATE
	}
}
u8 TWI_address_select (u8 address,u8 rw)
{
	u8 status;
	if (rw == WRITE)
	{
		TWDR = address + 0;
	}
	else if (rw == READ)
	{
		TWDR = address + 1;
	}
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	status = TWSR & 0xF8;
	if (status==SLA_W_ACK_STATE)
	{
		return SLA_W_ACK_SENT;
	}
	else if (status==SLA_W_NACK_STATE)
	{
		return SLA_W_NACK_SENT;
	}
	else if (status==SLA_R_ACK_STATE)
	{
		return SLA_R_ACK_SENT;
	}
	else if (status==SLA_R_NACK_STATE)
	{
		return SLA_R_NACK_SENT;
	}
	else
	{
		return SLA_RW_FAILED;
	}
}
u8 TWI_data_event (u8 *data,u8 rw,u8 ack)
{
	u8 status;
	if (rw == WRITE)
	{
		TWDR = *data;
		TWCR = (1<<TWINT) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
		status = TWSR & 0xF8;
		if (status==DATA_WRITE_ACK_STATE)
		{
			return DATA_WRITE_ACK_SENT;
		}
		else if (status==DATA_WRITE_NACK_STATE)
		{
			return DATA_WRITE_NACK_SENT;
		}
		else
		{
			return DATA_WRITE_FAILED;
		}
	}

	else if (rw == READ)
	{
		if (ack == ACK)
		{
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		} 
		else if (ack == NACK)
		{
			TWCR = (1<<TWINT) | (1<<TWEN);
		}
		
		while (!(TWCR & (1<<TWINT)));
		*data = TWDR;
		status = TWSR & 0xF8;
		if (status==DATA_READ_ACK_STATE)
		{
			return DATA_READ_ACK_SENT;
		}
		else if (status==DATA_READ_NACK_STATE)
		{
			return DATA_READ_NACK_SENT;
		}
		else
		{
			return DATA_READ_FAILED;
		}
	}
	else 
	{
		return DATA_RW_FAILED;
	}
	
}
void TWI_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); //Send STOP condition
	while ((TWCR & (1<<TWSTO)));			/*Wait for TWSTO Flag set.*/
}
