/*
 * uart.c
 *
 * Created: 4/29/2023 2:24:40 AM
 *  Author: Mohamed Sayed
 */ 
 #include "uart.h"

 /************************************************************Pointer to function****************************************************************************/
 static void (*Tfptr)(void)=NULLPTR;
 static void (*Rfptr)(void)=NULLPTR;
 
 #if FCPU==8
 static u16 BaudRate_arr[Baudrate_Total][Speed_Total]={
	 {207,416},
     {103,207},
	 {51,103},
	 {34,68},	 
 };
 #elif FCPU==4
 static u16 BaudRate_arr[Baudrate_Total][Speed_Total]={
	 {103,207},
	 {51,103},
	 {25,51},
	 {16,34},
 };
 #endif
 
 void uart_init(Uart_BaudRate_en BaudRate,Uart_Speed_en Speed,Uart_Mode_en mode,Uart_Parity_en parity,Uart_StopBit_en stopbit,Uart_DataBit_en databit,Uart_Enable_en enable)
 {
	 if (BaudRate_arr[BaudRate][Speed]>255)
	 {
		  CLR_Bit(UCSRC,URSEL);
		 UBRRH=(u8)(BaudRate_arr[BaudRate][Speed]>>8);
		 UBRRL=(u8)BaudRate_arr[BaudRate][Speed];
	 }
	 else
	 {
		UBRRL=BaudRate_arr[BaudRate][Speed];
	 }
	 //speed
	 if (Speed==Normal_Speed)
	 {
		 CLR_Bit(UCSRA,U2X);
	 }
	 else
	 {
		Set_Bit(UCSRA,U2X);
	 }
	 //uart operation mode
	 if (mode==Asynchronous)
	 {
		 Set_Bit(UCSRC,URSEL);
		 CLR_Bit(UCSRC,UMSEL);
	 }
	 else
	 {
		 Set_Bit(UCSRC,URSEL);
		 Set_Bit(UCSRC,UMSEL);
	 }
	 //uart Frame
	 //parity
	 if (parity==Even)
	 {
		 Set_Bit(UCSRC,URSEL);
		 CLR_Bit(UCSRC,UPM0);
		 Set_Bit(UCSRC,UPM1);
	 }
	 else if (parity==Odd)
	 {
		 Set_Bit(UCSRC,URSEL);
		 Set_Bit(UCSRC,UPM0);
		 Set_Bit(UCSRC,UPM1);
	 }
	 else
	 {
		 Set_Bit(UCSRC,URSEL);
		 CLR_Bit(UCSRC,UPM0);
		 CLR_Bit(UCSRC,UPM1);
	 }
	 //stop bit
	 if (stopbit==StopBit_1)
	 {
		 Set_Bit(UCSRC,URSEL);
		 CLR_Bit(UCSRC,USBS);
	 }
	 else 
	 {
		 Set_Bit(UCSRC,URSEL);
		 Set_Bit(UCSRC,USBS);
	 }
	 //data
	 switch(databit)
	 {
		 case DataBit_5:
		  Set_Bit(UCSRC,URSEL);
		  CLR_Bit(UCSRC,UCSZ0);
		  CLR_Bit(UCSRC,UCSZ1);
		  CLR_Bit(UCSRB,UCSZ2);
		  break;
		  case DataBit_6:
		  Set_Bit(UCSRC,URSEL);
		  Set_Bit(UCSRC,UCSZ0);
		  CLR_Bit(UCSRC,UCSZ1);
		  CLR_Bit(UCSRB,UCSZ2);
		  break;
		  case DataBit_7:
		  Set_Bit(UCSRC,URSEL);
		  CLR_Bit(UCSRC,UCSZ0);
		  Set_Bit(UCSRC,UCSZ1);
		  CLR_Bit(UCSRB,UCSZ2);
		  break;
		  case DataBit_8:
		  Set_Bit(UCSRC,URSEL);
		  Set_Bit(UCSRC,UCSZ0);
		  Set_Bit(UCSRC,UCSZ1);
		  CLR_Bit(UCSRB,UCSZ2);
		  break;
	 }
	 //Enable
	 switch(enable)
	 {
		case Transmitter:
		Set_Bit(UCSRB,TXEN);
		break;
		case Reciever:
		Set_Bit(UCSRB,RXEN);
		break;
		case TR:
		Set_Bit(UCSRB,TXEN);
		Set_Bit(UCSRB,RXEN);
		break;
	 }
 }
 /*******************************************************Transmitter************************************************************************************************/
 void uart_transmit(u8 data)
 {
	 while (!Read_Bit(UCSRA,UDRE));
	 UDR=data;
 }
 
 void uart_transmitNoBlock(u8 data)
 {
	 UDR=data;
 }
 /**************************************************Transmitter Interrupt********************************************************************************************/
 void uart_transmitComPlete_InterruptEnable(void)
 {
	 Set_Bit(UCSRB,TXCIE);
 }
 void uart_transmitComPlete_InterruptDisable(void)
 {
	  CLR_Bit(UCSRB,TXCIE);
 }
 void uart_transmitComPlete_InterruptSetCallback(void(*fptr)(void))
 {
	 Tfptr=fptr;
 }
 
 ISR(UART_TX_vect)
 {
	 if (Tfptr!=NULLPTR)
	 {
		 Tfptr();
	 }
	 else
	 {
		 //do nothing
	 }
 }
 
 /*******************************************************Receiver*********************************************************************************************/
 
 u8 uart_reciever(void)
 {
	 while (!Read_Bit(UCSRA,RXC));
	 if (Read_Bit(UCSRA,FE)||Read_Bit(UCSRA,PE))
	 {
		 return ERROR_DATA;
	 }
	 else if (Read_Bit(UCSRA,DOR))
	 {
		 return DATA_OVERRUN;
	 }
	 else
	 {
		 return UDR;
	 }
	 
 }
 
 u8 uart_recieverNoBlock(void)
 {
	  return UDR;
 }
 /*******************************************Receiver Interrupt*****************************************************************************/
 
 void uart_recieveComPlete_InterruptEnable(void)
 {
	 Set_Bit(UCSRB,RXCIE);
 }
 
 void uart_recieveComPlete_InterruptDisable(void)
 {
	 CLR_Bit(UCSRB,RXCIE);
 }
 
 void uart_recieveComPlete_InterruptSetCallback(void(*fptr)(void))
 {
	 Rfptr=fptr;
 }
 
 
 
 
 ISR(UART_RX_vect)
 {
	 if (Rfptr!=NULLPTR)
	 {
		 Rfptr();
	 }
	 else
	 {
		 //do nothing
	 }
 }
