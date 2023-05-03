/*
 * uart_services.c
 *
 * Created: 5/1/2023 12:39:48 AM
 *  Author: Mohamed Sayed
 */ 


#include "uart_services.h"

/***********************************************************************Transmitter*********************************************************************/
static void uart_transmitStringCallBack(void);
static void uart_transmitNumberCallBack(void);
static volatile u8 TFlag_S=0;
static volatile u8 TFlag_N=0;
static volatile u8 *Tstr;
static volatile u8 *Pnum_I=NULLPTR;
/***********************************************************************Reciever*****************************************************************************/
static void uart_recieverStringCallBack(void);
static void uart_recieverNumberCallBack(void);
static volatile u8 RFlag_S=0;
static volatile u8 RFlag_N=0;
static volatile u8 *Rstr;
static volatile u16 *Rnum;
/***********************************************************************************************************************************************************/

/***********************************************************************Transmitter*********************************************************************/
void uart_transmitString(u8*str)
{
	u8 i=0;
	for (i=0;str[i];i++)
	{
		uart_transmit(str[i]);
	}
	uart_transmit(END_SEND);
}

void uart_transmitString_Interrupt(u8*str)
{
	if (TFlag_S==0)
	{
		Tstr=str;
		TFlag_S=1;
		uart_transmit(Tstr[0]);
		uart_transmitComPlete_InterruptSetCallback(uart_transmitStringCallBack);
		uart_transmitComPlete_InterruptEnable();
	}
	else
	{
		//do nothing
	}
}
static void uart_transmitStringCallBack(void)
{
	static u8 i=1;
	uart_transmitNoBlock(Tstr[i]);
	i++;
	if (Tstr[i]=='\0')
	{
		uart_transmitComPlete_InterruptDisable();
		i=1;
		TFlag_S=0;
		uart_transmit(END_SEND);
	}
	else
	{
		//do nothing
	}
}

void uart_transmitNumber_MCU(u32 num)
{
	u8*pnumn=&num;
	u8 i=0;
	for (i=0;i<4;i++)
	{
		uart_transmit(pnumn[i]);
	}
}
void uart_transmitNumber_MCU_Interrupt(u32* num)
{		
		if (TFlag_N==0)
		{
			Pnum_I=num;
			uart_transmit(Pnum_I[0]);
			uart_transmitComPlete_InterruptSetCallback(uart_transmitNumber_MCU_Interrupt_CallBack);
			uart_transmitComPlete_InterruptEnable();
			TFlag_N=1;
		}
		else 
		{
			//do nothing
		}	
}

static void uart_transmitNumber_MCU_Interrupt_CallBack(void)
{
	static u8 i=1;
	uart_transmitNoBlock(Pnum_I[i]);
	i++;
	if (i==4)
	{
		uart_transmitComPlete_InterruptDisable();
		i=0;
		TFlag_N=0;
	}
	else
	{
		//do nothing
	}
}

/*******************************************************Receiver*********************************************************************************************/
void uart_recieverString(u8*str)
{
	u8 i=0;
	str[i]=uart_reciever();
	while (str[i]!=END_SEND)
	{
		i++;
		str[i]=uart_reciever();
	}
	str[i]=NULL;
}

void uart_recieverString_Interrupt(u8*str)
{
	if (RFlag_S==0)
	{
		Rstr=str;
		RFlag_S=1;
		uart_recieveComPlete_InterruptSetCallback(uart_recieverStringCallBack);
		uart_recieveComPlete_InterruptEnable();
	}
}
static void uart_recieverStringCallBack(void)
{
	static u8 i=0;
	Rstr[i]=UDR;
	if (Rstr[i]==END_SEND)
	{
		Rstr[i]=NULL;
		uart_recieveComPlete_InterruptDisable();
		i=0;
		RFlag_S=0;
	}
	else
	{
		i++;
	}
}

void uart_recieveNumber_MCU(u32* num)
{
	u8*pnumn=num;
	u8 i=0;
	for (i=0;i<4;i++)
	{
	   pnumn[i]=uart_reciever();
	}
}
void uart_recieveNumber_MCU_Interrupt(u32* num)
{
	if(RFlag_N==0)
	{
		Rnum_I_Mcu=num;
		uart_recieveComPlete_InterruptSetCallback(uart_recieveNumber_MCU_Interrupt_CallBack);
		uart_recieveComPlete_InterruptEnable();
		RFlag_N=1;
	}
	else
	{
		//do nothing
	}
}

static void uart_recieveNumber_MCU_Interrupt_CallBack(void)
{
	static u8 i=0;
	Rnum_I_Mcu[i]=uart_recieverNoBlock();
	i++;
	if (i==4)
	{
		uart_recieveComPlete_InterruptDisable();
		i=0;
		RFlag_N=0;
	}
	else
	{
		//do nothing
	}
}
