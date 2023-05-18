/*
 * lcd.c
 *
 * Created: 4/20/2023 3:34:50 PM
 *  Author: Mohamed Abdelsalam
 */ 
#include "lcd.h"
/************************************************************************/
/* LCD initialize function                                              */
/************************************************************************/
/*Description
This function initialize All LCD pins Direction
according to chosen mode (4 or 8) bit
then it send this command to LCD
And Also make some LCD settings:
-display on cursor off
-auto increment cursor
-clear display
-cursor at home position
*/
void LCD_init(void)
{
	#if Mode == bit_8			//if LCD mode chosen in 8bit mode
	DIO_InitPin (D7 ,OUTPUT);		//make data7 pin output
	DIO_InitPin (D6 ,OUTPUT);		//make data6 pin output
	DIO_InitPin (D5 ,OUTPUT);		//make data5 pin output
	DIO_InitPin (D4 ,OUTPUT);		//make data4 pin output
	DIO_InitPin (D3 ,OUTPUT);		//make data3 pin output
	DIO_InitPin (D2 ,OUTPUT);		//make data2 pin output
	DIO_InitPin (D1 ,OUTPUT);		//make data1 pin output
	DIO_InitPin (D0 ,OUTPUT);		//make data0 pin output
	DIO_InitPin (EN ,OUTPUT);		//make enable pin output
	DIO_InitPin (RW ,OUTPUT);		//make rw pin output
	DIO_InitPin (RS ,OUTPUT);		//make rs pin output
	Delay_ms(20);				//LCD power on delay is always more than 15ms
	LCD_sendcommand(0x38);			//initialization LCD 16x2 in 8bit mode
	LCD_sendcommand(0x0C);			//display on cursor off
	LCD_sendcommand(0x06);			//auto increment cursor
	LCD_sendcommand(0x01);			//clear display
	LCD_sendcommand(0x80);			//cursor at home position
	#elif Mode == bit_4			//if LCD mode chosen in 4bit mode
	DIO_InitPin (D7 ,OUTPUT);		//make data7 pin output
	DIO_InitPin (D6 ,OUTPUT);		//make data6 pin output
	DIO_InitPin (D5 ,OUTPUT);		//make data5 pin output
	DIO_InitPin (D4 ,OUTPUT);		//make data4 pin output
	DIO_InitPin (EN ,OUTPUT);		//make enable pin output
	DIO_InitPin (RW ,OUTPUT);		//make rw pin output
	DIO_InitPin (RS ,OUTPUT);		//make rs pin output
	Delay_ms(20);				//LCD power on delay is always more than 15ms
	LCD_sendcommand(0x02);			//initialization LCD in 4bit mode
	LCD_sendcommand(0x28);			//2 lines, 8x5 pixels in 4bit mode
	LCD_sendcommand(0x0C);			//display on cursor off
	LCD_sendcommand(0x06);			//auto increment cursor
	LCD_sendcommand(0x01);			//clear display
	LCD_sendcommand(0x80);			//cursor at home position
	#endif
}
/************************************************************************/
/*LCD Send Command function                                             */
/************************************************************************/
/*Description
This function takes command input
then it send this command to LCD
*/
void LCD_sendcommand (u8 cmnd)
{
	#if Mode == bit_8				//if LCD mode chosen in 8bit mode
	DIO_WritePort(LCD_Data_Port,cmnd);		//LCD Data Port = cmnd
	DIO_WRitePin (RS ,LOW);				//RS = 0 Command register
	DIO_WRitePin (RW ,LOW);				//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);			//EN = 1 high pulse
	delay_us(1);					//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);				//EN = 0 low pulse
	Delay_ms(3);					//delay 3ms
	#elif Mode == bit_4				//if LCD mode chosen in 4bit mode
	UPPER_NIPPLE(LCD_Data_Port , cmnd); 		//Sending upper nipple of cmnd to LCD Data Port
	DIO_WRitePin (RS ,LOW);				//RS = 0 Command register
	DIO_WRitePin (RW ,LOW);				//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);			//EN = 1 high pulse
	delay_us(1);					//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);				//EN = 0 low pulse
	Delay_ms(2);					//delay 2ms
	LOWER_NIPPLE(LCD_Data_Port , cmnd); 		//Sending lower nipple of cmnd to LCD Data Port
	DIO_WRitePin (RS ,LOW);				//RS = 0 Command register
	DIO_WRitePin (RW ,LOW);				//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);			//EN = 1 high pulse
	delay_us(1);					//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);				//EN = 0 low pulse
	Delay_ms(3);					//delay 3ms
	#endif
}
/************************************************************************/
/*LCD Send Character function                                           */
/************************************************************************/
/*Description
This function takes one character data type input
then send this character to LCD
*/
void LCD_sendChar (u8 char_data)
{
	#if Mode == bit_8			//if LCD mode chosen in 8bit mode
	DIO_WritePort(LCD_Data_Port,char_data); //LCD Data Port = char data
	DIO_WRitePin (RS ,HIGH);		//RS = 1 Data register
	DIO_WRitePin (RW ,LOW);			//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);		//EN = 1 high pulse
	delay_us(1);				//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);			//EN = 0 low pulse
	Delay_ms(1);				//delay 1ms
	#elif Mode == bit_4			//if LCD mode chosen in 4bit mode
	UPPER_NIPPLE(LCD_Data_Port,char_data);  //Sending upper nipple of char data to LCD Data Port
	DIO_WRitePin (RS ,HIGH);		//RS = 1 Data register
	DIO_WRitePin (RW ,LOW);			//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);		//EN = 1 high pulse
	delay_us(1);				//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);			//EN = 0 low pulse
	Delay_ms(2);				//delay 2ms
	LOWER_NIPPLE(LCD_Data_Port,char_data);  //Sending lower nipple of char data to LCD Data Port
	DIO_WRitePin (RS ,HIGH);		//RS = 1 Data register
	DIO_WRitePin (RW ,LOW);			//RW = 0 write operation
	DIO_WRitePin (EN ,HIGH);		//EN = 1 high pulse
	delay_us(1);				//delay 1us is always more than 450ns
	DIO_WRitePin (EN ,LOW);			//EN = 0 low pulse
	Delay_ms(2);				//delay 2ms
	#endif
}
/************************************************************************/
/*LCD Send String function		                                        */
/************************************************************************/
/*Description
This function takes string input
then send this string to LCD
*/
void LCD_sendString (u8 *str)
{
	u16 i;
	for(i = 0;str[i]!= '\0'; i++)
	{
		LCD_sendChar(str[i]);
	}
}
/************************************************************************/
/*LCD Send Custom Character function                                    */
/************************************************************************/
/*Description
This function takes one character data type input
and it send the inputs to string
then send this string to LCD
*/
void LCD_createCustomCharacter (u8 *pattern , u8 location )
{
	u8 i;
	LCD_sendcommand(( 0x40 + (location*8)));
	for(i = 0; i<8; i++)
	{
		LCD_sendChar(pattern[i]);
	}
}
/************************************************************************/
/*LCD Clear function                                           */
/************************************************************************/
/*Description
This function Clear the Display
*/
void LCD_clear(void)
{
	LCD_sendcommand(0x01);			//clear display
	Delay_ms(1);				//delay 1ms
	LCD_sendcommand(0x80);			//cursor at home position
}
/************************************************************************/
/*LCD float into string function                                        */
/************************************************************************/
/*Description
This function takes float data type inputs
and it converts the inputs to string
then send this string to LCD
*/
void LCD_floattostring (f32 float_value)
{
	u8 pattern[10] , tempRearrange, digit_count=0,i,j;
	u32 number;
	f32 temp_float = float_value * 10;
	number = temp_float;
	for (i=0;number>0;i++)
	{
		pattern[i] = ((number%10) +'0');
		number/=10;
		digit_count++;
	}
	
	for (j=0,i--;i>j;j++)
	{
		tempRearrange = pattern[i];
		pattern[i] = pattern[j];
		pattern[j] = tempRearrange;
		i--;
	}
	pattern[digit_count] =pattern[digit_count - 1];
	pattern[digit_count - 1] = '.';
	pattern[digit_count + 1] = '\0';
	LCD_sendString(pattern);
}
/************************************************************************/
/*LCD Set Cursor function                                               */
/************************************************************************/
/*Description
This function takes row an column inputs
then set cursor position according to inputs
*/
void LCD_setCursor (u8 row , u8 column)
{
	if (row == 0 && column<16)
	LCD_sendcommand((column & 0x0F)|0x80);	/* Command of first row and required column<16 */
	else if (row == 1 && column<16)
	LCD_sendcommand((column & 0x0F)|0xC0);	/* Command of first row and required column<16 */
	
}
