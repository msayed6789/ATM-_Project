/*
 * eeprom.c
 *
 * Created: 5/2/2023 1:16:44 PM
 *  Author: lenovo
 */ 
#include "eeprom.h"
void EEPROM_init(void)
{
	TWI_init();

}
void EEPROM_byteWrite(u8 data_address1,u8 data_address2,u8 data)
{
			if(TWI_start()==EVENT_OK)
			{
				if (TWI_address_select(0xA0,WRITE)== SLA_W_ACK_SENT)
				{
					if (TWI_data_event(&data_address1,WRITE,ACK) == DATA_WRITE_ACK_SENT)
					{
						if (TWI_data_event(&data_address2,WRITE,ACK) == DATA_WRITE_ACK_SENT)
						{
							if (TWI_data_event(&data,WRITE,ACK) == DATA_WRITE_ACK_SENT)
							{
								TWI_stop();
								Delay_ms(5);
							}
						}
					}
				}
			}

}
void EEPROM_pageWrite(u8 data_address1,u8 data_address2,u8 *data)
{
	u8 i = 0;
	u8 n_bytes = 0;
	if(TWI_start()==EVENT_OK)
	{
		if (TWI_address_select(0xA0,WRITE)== SLA_W_ACK_SENT)
		{
			if (TWI_data_event(&data_address1,WRITE,ACK) == DATA_WRITE_ACK_SENT)
			{
				if (TWI_data_event(&data_address2,WRITE,ACK) == DATA_WRITE_ACK_SENT)
				{
					while (data[n_bytes])
					{
						n_bytes++;
					} 
					if (TWI_data_event(&n_bytes,WRITE,ACK) == DATA_WRITE_ACK_SENT)
						do 
						{
							if (TWI_data_event((data+i),WRITE,ACK) == DATA_WRITE_ACK_SENT)
							i++;
						} while ((i<(n_bytes)) && (i<64));
						TWI_stop();
						Delay_ms(10);
				}
			}
		}
	}

}
void EEPROM_byteRead(u8 data_address1,u8 data_address2,u8 *data)
{
				if(TWI_start()==EVENT_OK)
				{
					if (TWI_address_select(0xA0,WRITE)== SLA_W_ACK_SENT)
					{
						if (TWI_data_event(&data_address1,WRITE,ACK) == DATA_WRITE_ACK_SENT)
						{
							if (TWI_data_event(&data_address2,WRITE,ACK) == DATA_WRITE_ACK_SENT)
							{
								if (TWI_repeated_start()==EVENT_OK)
								{
									if (TWI_address_select(0xA0,READ)== SLA_R_ACK_SENT)
									{
										if (TWI_data_event(data,READ,NACK) == DATA_READ_NACK_SENT)
										{
											
											TWI_stop();
											Delay_ms(6);
										}
									}
								}
							}
						}
					}
				}
	

}
void EEPROM_pageRead(u8 data_address1,u8 data_address2,u8 *data)
{
u8 i=0;
u8 n_byte;
if(TWI_start()==EVENT_OK)
{
	if (TWI_address_select(0xA0,WRITE)== SLA_W_ACK_SENT)
	{
		if (TWI_data_event(&data_address1,WRITE,ACK) == DATA_WRITE_ACK_SENT)
		{
			if (TWI_data_event(&data_address2,WRITE,ACK) == DATA_WRITE_ACK_SENT)
			{
				if (TWI_repeated_start()==EVENT_OK)
				{
					if (TWI_address_select(0xA0,READ)== SLA_R_ACK_SENT)
					{
						if (TWI_data_event(&n_byte,READ,ACK) == DATA_READ_ACK_SENT)
						{
							do
							{
								if (TWI_data_event((data+i),READ,ACK) == DATA_READ_ACK_SENT)
								i++;
							} while (i<(n_byte-1));
							if (TWI_data_event((data+i),READ,NACK) == DATA_READ_NACK_SENT)
							TWI_stop();
							Delay_ms(10);
							
						}
					}
				}
			}
		}
	}
	
}
}
void EEPROM_erase(void)
{
	u8 i;
	u8 empty[] = "ÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿÿ";
	for (i=0x0000;i<=0x04;i++)
	{
	EEPROM_pageWrite(i,0x00,empty);
	Delay_ms(10);
	}
}
