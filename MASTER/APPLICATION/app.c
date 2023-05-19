/*
 * app.c
 *
 * Created: 5/19/2023 3:12:22 AM
 *  Author: ebrahem
 */ 
#include "app.h"



volatile uint8_t flag=0;
uint8_t i=0;
uint8_t PIN_PASS[5];
//uint8_t AMOUNT[8]="0000.00";
uint8_t Target_ST=90;
uint8_t trial =0;
uint8_t once_trans = 0;

uint8_t PAN[19]="0000";
uint8_t PIN[5]="0000";
	st_dataBank_t dataBase[4] ;
	
	

void app_init()
{
	sei();
	LCD_init();
	EXI_Enable (EX_INT0);
	EXI_Trigger(EX_INT0,LOW_LEVEL);
	//	EXI_SetCallBack(EX_INT0,Button_Pressed);
	SPImaster_init();
	Keypad_Status_en check =  KEYPAD_Init(KEYPAD_ROW,KEYPAD_COL);
	bazz_init(BAZZER_PIN);
	
	button_init(BUTTON_PIN);
	button_init(button_trigger);
	
	
	SPImaster_init();
	strcpy(dataBase[0].PAN , "Ebrahem Mostafa");
	strcpy(dataBase[0].PIN , "2233");
	strcpy(dataBase[0].Card_Amount , "3000.00");
	dataBase[0].Card_Available = valid;
	
	strcpy(dataBase[1].PAN , "medo");
	strcpy(dataBase[1].PIN , "1010");
	strcpy(dataBase[1].Card_Amount , "5700.00");
	dataBase[1].Card_Available = valid;
	
	strcpy(dataBase[2].PAN , "Mohamed Adel");
	strcpy(dataBase[2].PIN , "9044");
	strcpy(dataBase[2].Card_Amount , "2940.00");
	dataBase[2].Card_Available = valid;
	
	strcpy(dataBase[3].PAN , "Osama mohamed");
	strcpy(dataBase[3].PIN , "2043");
	strcpy(dataBase[3].Card_Amount , "2190.00");
	dataBase[3].Card_Available = blocked;
	
}



void app_start()
{
		first:
		LCD_clear();
		LCD_sendString ("Welcome to ATM");
		Delay_ms(1000);
		LCD_clear();
		LCD_sendString ("Insert a card");
		while(Button_Check(button_trigger));
		
		z:
		LCD_clear();
		LCD_sendString ("Enter your PIN");
		LCD_setCursor(1,0);
		u8 TIME_CHECK = NO_KEY;
		u8 check = 0;
		uint8_t AMOUNT[8]="0000.00";
		i=0;
		while(i<4)
		{
			
			
			TIME_CHECK = KEYPAD_GetNum_time(20) ;
			if(TIME_CHECK != NO_KEY)
			{
				LCD_sendChar('*');
				PIN_PASS[i]=TIME_CHECK+'0';
				TIME_CHECK=NO_KEY;
				i++;
			}
			
			check = Button_Check_Time(BUTTON_PIN);
			
			
			if(check == Pressed_UnderTime)
			{
				
				LCD_sendChar('*');
				PIN_PASS[i]='0';
				check=0;
				i++;
			}
			
			
		}
		
		while(check != Pressed_OverTime)
		{
			check = Button_Check_Time(BUTTON_PIN);
		}
		check=0;
		LCD_clear();
		LCD_sendString("Please wait ");
		Delay_ms(1000);
		LCD_sendChar('.');
		Delay_ms(1000);
		LCD_sendChar('.');
		Delay_ms(1000);
		LCD_sendChar('.');
		Delay_ms(150);
		if(once_trans == 0)
		{
			
			SPImaster_send(PIN,4);
			SPImaster_send(PAN,4);
			once_trans =1;
		}
		
		
		uint8_t count_check1=0;
		uint8_t count_check2=0;
		
		flag=2;
		
		//while((count_check1<4)&&(flag))
		{
			// flag = strcmp(dataBase[count_check1].PIN, PIN);
			//count_check1++;
			flag = strcmp(PIN_PASS , PIN);
		}
		if(flag != 0)
		{
			LCD_clear();
			LCD_sendString("Wrong PIN");
			trial++;
			Delay_ms(500);
			if(trial < 3 )
			{
				LCD_setCursor(1,0);
				LCD_sendString("Try Again");
				Delay_ms(1000);
				goto z;
			}
			else
			{
				LCD_clear();
				LCD_sendString("ACC BLOCKED");
				Delay_ms(4000);
				goto first;
			}
		}
		
		
		if(flag == 0)
		{
			Target_ST = count_check1;
			LCD_clear();
			LCD_sendString("Enter Amount");
			LCD_setCursor(1,0);
			LCD_sendString(AMOUNT);
			//LCD_setCursor(1,6);
			i=7;
			while(i>0)
			{
				TIME_CHECK = KEYPAD_GetNum_time(20) ;
				if(TIME_CHECK != NO_KEY)
				{
					AMOUNT[6]=TIME_CHECK+'0';
					if(i>1)
					{
						
						
						LCD_clear();
						
						LCD_sendString("Enter Amount");
						LCD_setCursor(1,0);
						LCD_sendString(AMOUNT);
						uint8_t j=0;
						uint8_t temp=AMOUNT[0];
						for(j=0;j<7;j++)
						{
							if(j!=3)
							{
								AMOUNT[j]=AMOUNT[j+1];
							}
							else
							{
								AMOUNT[j]=AMOUNT[j+2];
								j++;
							}
							
						}
						AMOUNT[6]=temp;
					}
					//PIN_PASS[i]=TIME_CHECK;
					TIME_CHECK=NO_KEY;
					i--;
					if(i==5)
					{
						i--;
					}
					
				}
				check = Button_Check_Time(BUTTON_PIN);
				
				
				if(check == Pressed_UnderTime)
				{
					AMOUNT[6]='0';
					if(i>1)
					{
						LCD_clear();
						
						LCD_sendString("Enter Amount");
						LCD_setCursor(1,0);
						LCD_sendString(AMOUNT);
						uint8_t j=0;
						uint8_t temp=AMOUNT[0];
						for(j=0;j<7;j++)
						{
							if(j!=3)
							{
								AMOUNT[j]=AMOUNT[j+1];
							}
							else
							{
								AMOUNT[j]=AMOUNT[j+2];
								j++;
							}
							
						}
						AMOUNT[6]=temp;
					}
					//PIN_PASS[i]=TIME_CHECK;
					TIME_CHECK=NO_KEY;
					i--;
					if(i==5)
					{
						i--;
					}
					
				}
				
				
			}
			Delay_ms(100);
			LCD_clear();
			LCD_sendString("Checking Account");
			Delay_ms(1000);
			LCD_sendChar('.')	;
			Delay_ms(500);
			LCD_sendChar('.')	;
			Delay_ms(500);
			LCD_sendChar('.')	;
			Delay_ms(200);
			count_check1=0;
			uint8_t flag_valid=2;
			while ((count_check1 < 4)&&(flag_valid!=0))
			{
				flag_valid = strcmp(dataBase[count_check1].PAN,PAN);
				count_check1++;
			}
			Target_ST = count_check1-1;
			if(flag_valid == 0)
			{
				
				
				
				if(dataBase[Target_ST].Card_Available == blocked)
				{
					LCD_clear();
					LCD_sendString("This card is stolen");
					Delay_ms(2000);
					goto first;
					
				}
				if (AMOUNT[0] > '5')
				{
					LCD_clear();
					LCD_sendString("Maximum limit is exceeded");
					Delay_ms(2000);
					goto first;
				}
				else if(AMOUNT[0] == '5')
				{
					for(count_check1=1;count_check1<7;count_check1++)
					{
						if(AMOUNT[count_check1] >'0')
						{
							count_check1=7;
							LCD_clear();
							LCD_sendString("Maximum limit is exceeded");
							LCD_setCursor(1,0);
							LCD_sendChar(AMOUNT[0]);
							Delay_ms(2000);
							goto first;
						}
						
					}
				}
				
				if(AMOUNT[0] > dataBase[Target_ST].Card_Amount[0])
				{
					LCD_clear();
					LCD_sendString("Insufficient fund");
					Delay_ms(2000);
					goto first;
				}
				else if(AMOUNT[0] == dataBase[Target_ST].Card_Amount[0] )
				{
					for(count_check1=1;count_check1<7;count_check1++)
					{
						if(AMOUNT[count_check1] >dataBase[Target_ST].Card_Amount[count_check1])
						{
							count_check1=7;
							LCD_clear();
							LCD_sendString("Insufficient fund");
							Delay_ms(2000);
							goto first;
						}
						
					}
				}
				
				uint32_t conv_amount = atoi(AMOUNT);
				uint32_t conv_acc = atoi(dataBase[Target_ST].Card_Amount);
				
				
				
				conv_acc = conv_acc - conv_amount;
				
				
				sprintf(dataBase[Target_ST].Card_Amount, "%d",conv_acc );
				
				
				LCD_clear();
				LCD_sendString("Approved transaction");
				Delay_ms(1000);
				LCD_clear();
				LCD_sendString("Curr balance: ");
				LCD_setCursor(1,0);
				LCD_sendString(dataBase[Target_ST].Card_Amount);
				Delay_ms(5000);
				LCD_clear();
				LCD_sendString("EJECT CARD");
				Delay_ms(1000);
				u8 send_ending = 'E';
				
				//	SPImaster_send(&send_ending,1);
			}
			
			else
			{
				LCD_clear();
				LCD_sendString(PAN);
				LCD_setCursor(1,0);
				LCD_sendString(dataBase[1].PAN);
				Delay_ms(5000);
			}
			
			
			
			
			
		}
		
}		
		
		
		
		
