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
static volatile u8 Tstr[500];
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
	u8 k=0;
	if (TFlag_S==0)
	{
		for (k=0;str[k];k++)
		{
			Tstr[k]=str[k];
		}
		Tstr[k]='\0';
		TFlag_S=1;
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
	static u8 i=0;
	UDR=Tstr[i];
	i++;
	if (Tstr[i]=='\0')
	{
		uart_transmitComPlete_InterruptDisable();
		i=0;
		TFlag_S=0;
		uart_transmit(END_SEND);
	}
	else
	{
		//do nothing
	}
}

void uart_transmitNumber(u32 num)
{
	u8*pnum=&num;
	u8 i=0;
	for (i=0;i<4;i++)
	{
		uart_transmit(pnum[i]+'0');
		if (i==1)
		{
			uart_transmit(END_SEND);
		}
		else
		{
			//do nothing
		}
	}
}

void uart_transmitNumber_Interrupt(u32 num)
{
	if(TFlag_N==0)
	{
		Pnum_I=&num;
		uart_transmitComPlete_InterruptSetCallback(uart_transmitNumberCallBack);
		uart_transmitComPlete_InterruptEnable();
	}
	else
	{
		//do nothing
	}
	
}

static void uart_transmitNumberCallBack(void)
{
	static u8 i=0;
	UDR=Pnum_I[i];
	if (i==1)
	{
		uart_transmit(END_SEND);
	}
	else
	{
		//do nothing
	}
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

void uart_recieveNumber(u16* num)
{
	u8 uart_str[6];
	u8 i=0;
	u16 mul=10000;
	uart_str[0]=uart_reciever();
	while(uart_str[i]!=END_SEND)
	{
		i++;
		uart_str[i]= uart_reciever();
	}
	if ( uart_str[0]==END_SEND)
	{
		*num=0;
		return;
	}
	else
	{
		*num=0;
	}
	switch (i)
	{
		case 5:
		mul=10000;
		break;
		case 4:
		mul=1000;
		break;
		case 3:
		mul=100;
		break;
		case 2:
		mul=10;
		break;
		default:
		*num=uart_str[0]-'0';
		return;
	}
	for (i=0;uart_str[i]!=END_SEND;i++)
	{
		*num=*num+(u32)(mul*(uart_str[i]-'0'));
		mul=mul/10;
	}
}

void uart_recieveNumber_Interrupt(u16* num)
{
	if (RFlag_N==0)
	{
		Rnum=num;
		RFlag_N=1;
		uart_recieveComPlete_InterruptSetCallback(uart_recieverNumberCallBack);
		uart_recieveComPlete_InterruptEnable();
	}
}

static void uart_recieverNumberCallBack(void)
{
	static u8 i=0;
	static u8 uart_str[6];
	u16 mul=10000;
	uart_str[i]=UDR;
	if (uart_str[0]==END_SEND)
	{
		*Rnum=0;
	}
	else if (uart_str[i]==END_SEND||i==5)
	{
		uart_recieveComPlete_InterruptDisable();
		RFlag_N=0;
		switch (i)
		{
			case 5:
			mul=10000;
			break;
			case 4:
			mul=1000;
			break;
			case 3:
			mul=100;
			break;
			case 2:
			mul=10;
			break;
			default:
			*Rnum=uart_str[0]-'0';
			return;
		}
		*Rnum=0;
		for (i=0;i<5;i++)
		{
			*Rnum=*Rnum+(u32)(mul*(uart_str[i]-'0'));
			mul=mul/10;
			uart_str[i]=0;
		}
		i=0;
	}
	else
	{
		i++;
	}
}
