
/*
 * application.c
 *
 * Created: 5/6/2023 3:37:43 AM
 *  Author: lenovo
 */ 
#include "application.h"
u8 STOP_USER_MODE;
u8 u8_g_operation_mode;
u8 Pin[5];
u8 Pan[21];
u8 New_Pin[5];
u8 ConfirmNew_Pin[5];
void APP_init(void)
{
	DIO_InitPin(PINB0,OUTPUT);
	SPIslave_init();
	EEPROM_init();
	//EEPROM_pageWrite(0x03,0x00,&u8_g_operation_mode);
	EEPROM_pageRead(0x03,0x00,&u8_g_operation_mode);
	uart_init(Baudrate9600,Normal_Speed,Asynchronous,No_Parity,StopBit_1,DataBit_8,TR);
	
}
void APP_start(void)
{
	s8 i;
	if(u8_g_operation_mode == USER_MODE)
	{
		u8 selector=0;
		uart_transmitString("Please press:  ");
		uart_transmitString((u8*)"1 for Entering user mode ");
		uart_transmitString((u8*)"2 for programming mode");
		uart_transmitString((u8*)"**********************");
		selector=uart_reciever();
		//uart_transmitString((u8*)"Please Enter Card Pan:");
		
		if (selector == 2)
		{
			//u8_g_operation_mode = PROGRAMMING_MODE;
			uart_transmitString((u8*)"Please Enter Card Pan:");
			uart_recieverString(Pan);
			for (i=0;Pan[i] != '\0';i++)
			{
				
			}
			u8 u8_l_flag=1;
			while(u8_l_flag)
			{
				
				
				if ( i < 16 || i > 19 )
				{
					uart_transmitString((u8*)"Wrong Pan");
					uart_transmitString((u8*)"Please Enter Pan:");
					uart_recieverString(Pan);
					
				}
				else
				{
					EEPROM_pageWrite(0x01,0x00,Pan);
					u8_l_flag = 0;
				}
			}
			uart_transmitString((u8*)"Please Enter New Pin:");
			uart_recieverString(New_Pin);
			uart_transmitString((u8*)"Please confirm New Pin:");
			uart_recieverString(ConfirmNew_Pin);
			for (i=0;i<5;i++)
			{
				if ( New_Pin[i] != ConfirmNew_Pin[i] )
				{
					uart_transmitString((u8*)"Wrong Pin");
					uart_transmitString((u8*)"Please Enter New Pin:");
					uart_recieverString(New_Pin);
					uart_transmitString((u8*)"Please confirm New Pin:");
					uart_recieverString(ConfirmNew_Pin);
					i=-1;
				}
				else
				{
					Pin[i] = New_Pin[i];
				}
			}
			
			for (i=0;i<4;i++)
			{
				if ( Pin[i] < '0' && Pin[i] > '9'  )
				{
					uart_transmitString((u8*)"Wrong Pin");
					uart_transmitString((u8*)"Please Enter New Pin:");
					uart_recieverString(New_Pin);
					uart_transmitString((u8*)"Please confirm New Pin:");
					uart_recieverString(ConfirmNew_Pin);
				}
				else
				{
				}
			}
			for (i=0;Pin[i] != '\0';i++)
			{
				
			}
			if ( i != 4 )
			{
				uart_transmitString((u8*)"Wrong Pin");
				uart_transmitString((u8*)"Please Enter New Pin:");
				uart_recieverString(New_Pin);
				uart_transmitString((u8*)"Please confirm New Pin:");
				uart_recieverString(ConfirmNew_Pin);
			}
			else
			{
				u8_g_operation_mode = USER_MODE;
				EEPROM_pageWrite(0x02,0x00,Pin);
				
				EEPROM_pageWrite(0x03,0x00,&u8_g_operation_mode);
				
				
				DIO_WRitePin(PINB0,HIGH);
				Delay_ms(20);
				DIO_WRitePin(PINB0,LOW);

			}
		}
		else if (selector == 1)
		{
			u8_g_operation_mode = USER_MODE;
		}
		if(u8_g_operation_mode == PROGRAMMING_MODE)
		{
			uart_transmitString((u8*)"Please Enter Card Pan:");
			uart_recieverString(Pan);
			for (i=0;Pan[i] != '\0';i++)
			{
				
			}
			u8 u8_l_flag=1;
			while(u8_l_flag)
			{
				
				
				if ( i < 16 || i > 19 )
				{
					uart_transmitString((u8*)"Wrong Pan");
					uart_transmitString((u8*)"Please Enter Pan:");
					uart_recieverString(Pan);
					
				}
				else
				{
					EEPROM_pageWrite(0x01,0x00,Pan);
					u8_l_flag = 0;
				}
			}
			uart_transmitString((u8*)"Please Enter New Pin:");
			uart_recieverString(New_Pin);
			uart_transmitString((u8*)"Please confirm New Pin:");
			uart_recieverString(ConfirmNew_Pin);
			for (i=0;i<5;i++)
			{
				if ( New_Pin[i] != ConfirmNew_Pin[i] )
				{
					uart_transmitString((u8*)"Wrong Pin");
					uart_transmitString((u8*)"Please Enter New Pin:");
					uart_recieverString(New_Pin);
					uart_transmitString((u8*)"Please confirm New Pin:");
					uart_recieverString(ConfirmNew_Pin);
					i=-1;
				}
				else
				{
					Pin[i] = New_Pin[i];
				}
			}
			
			for (i=0;i<4;i++)
			{
				if ( Pin[i] < '0' && Pin[i] > '9'  )
				{
					uart_transmitString((u8*)"Wrong Pin");
					uart_transmitString((u8*)"Please Enter New Pin:");
					uart_recieverString(New_Pin);
					uart_transmitString((u8*)"Please confirm New Pin:");
					uart_recieverString(ConfirmNew_Pin);
				}
				else
				{
				}
			}
			if ( Pin[4] != '\0' )
			{
				uart_transmitString((u8*)"Wrong Pin");
				uart_transmitString((u8*)"Please Enter New Pin:");
				uart_recieverString(New_Pin);
				uart_transmitString((u8*)"Please confirm New Pin:");
				uart_recieverString(ConfirmNew_Pin);
			}
			else
			{
				u8_g_operation_mode = USER_MODE;
				EEPROM_pageWrite(0x01,0x00,Pan);
				EEPROM_pageWrite(0x02,0x00,Pin);
				EEPROM_pageWrite(0x03,0x00,&u8_g_operation_mode);
				DIO_WRitePin(PINB0,HIGH);
				Delay_ms(20);
				DIO_WRitePin(PINB0,LOW);

			}
		}
		else if (u8_g_operation_mode == USER_MODE)
		{
			EEPROM_pageRead(0x01,0x00,Pan);
			EEPROM_pageRead(0x02,0x00,Pin);
			SPIslave_receive(Pan,19);
			SPIslave_receive(Pin,4);
			SPIslave_receive(&STOP_USER_MODE,1);
			
			if(STOP_USER_MODE == 'E')
			{
				u8_g_operation_mode = USER_MODE;
			}
			//////////////////////////////////////
			
		}
	}
	else
	{
		uart_transmitString((u8*)"Please Enter Card Pan:");
		uart_recieverString(Pan);
		for (i=0;Pan[i] != '\0';i++)
		{
					
		}
		u8 u8_l_flag=1;
		while(u8_l_flag)
		{
					
				
			if ( i < 16 || i > 19 )
			{
				uart_transmitString((u8*)"Wrong Pan");
				uart_transmitString((u8*)"Please Enter Pan:");
				uart_recieverString(Pan);
					
			}
			else
			{
				EEPROM_pageWrite(0x01,0x00,Pan);
				u8_l_flag = 0;
			}
		}
		uart_transmitString((u8*)"Please Enter New Pin:");
		uart_recieverString(New_Pin);
		uart_transmitString((u8*)"Please confirm New Pin:");
		uart_recieverString(ConfirmNew_Pin);
		for (i=0;i<5;i++)
		{
			if ( New_Pin[i] != ConfirmNew_Pin[i] )
			{
				uart_transmitString((u8*)"Wrong Pin");
				uart_transmitString((u8*)"Please Enter New Pin:");
				uart_recieverString(New_Pin);
				uart_transmitString((u8*)"Please confirm New Pin:");
				uart_recieverString(ConfirmNew_Pin);
				i=-1;
			}
			else
			{
				Pin[i] = New_Pin[i];
			}
		}
		
		for (i=0;i<4;i++)
		{
			if ( Pin[i] < '0' && Pin[i] > '9'  )
			{
				uart_transmitString((u8*)"Wrong Pin");
				uart_transmitString((u8*)"Please Enter New Pin:");
				uart_recieverString(New_Pin);
				uart_transmitString((u8*)"Please confirm New Pin:");
				uart_recieverString(ConfirmNew_Pin);
			}
			else
			{
			}
		}
		for (i=0;Pin[i] != '\0';i++)
		{
			
		}
		if ( i != 4 )
		{
			uart_transmitString((u8*)"Wrong Pin");
			uart_transmitString((u8*)"Please Enter New Pin:");
			uart_recieverString(New_Pin);
			uart_transmitString((u8*)"Please confirm New Pin:");
			uart_recieverString(ConfirmNew_Pin);
		}
		else
		{
			u8_g_operation_mode = USER_MODE;
			EEPROM_pageWrite(0x02,0x00,Pin);
			
			EEPROM_pageWrite(0x03,0x00,&u8_g_operation_mode);
			
			
			DIO_WRitePin(PINB0,HIGH);
			Delay_ms(20);
			DIO_WRitePin(PINB0,LOW);

		}
	}
	
}
