/*
 * lcd.h
 *
 * Created: 4/20/2023 3:34:31 PM
 *  Author: Mohamed Abdelsalam
 */ 

#ifndef LCD_H_
#define LCD_H_
#include "dio.h"
#include "delay.h"
/******************************************************************************************************************/
/******************************************************************************************************************/

							/************************************************************************/
							/*                            LCD Settings							     */
							/************************************************************************/

/************************************************************************/
/* LCD Modes                                                                     */
/************************************************************************/
#define bit_4 4
#define bit_8 8
/************************************************************************/
/************************************************************************/
/*  Mode for data transfer Choose ( bit_4 or bit_8 )                                                                     */
/************************************************************************/
#define Mode bit_4
/************************************************************************/
/************************************************************************/
/*							Definitions										*/
/************************************************************************/
/*
					4 bits mode definitions
*/
#if Mode == bit_4						//if LCD mode chosen in 4bit mode
#define D7 PINA7						//Data7 Pin and Port
#define D6 PINA6						//Data6 Pin and Port
#define D5 PINA5						//Data5 Pin and Port
#define D4 PINA4						//Data4 Pin and Port
#define EN PINA3						//EN Pin and Port
#define RW PINA2						//RW Pin and Port
#define RS PINA1						//RS Pin and Port
#define LCD_Data_Port PORTA				//Data Port
/*
					8 bits mode definations
*/
#elif Mode == bit_8						//if LCD mode chosen in 8bit mode
#define D7 PINA7						//Data7 Pin and Port
#define D6 PINA6						//Data6 Pin and Port
#define D5 PINA5						//Data5 Pin and Port
#define D4 PINA4						//Data4 Pin and Port
#define D3 PINA3						//Data3 Pin and Port
#define D2 PINA2						//Data2 Pin and Port
#define D1 PINA1						//Data1 Pin and Port
#define D0 PINA0						//Data0 Pin and Port
#define RS PINB0						//RS Pin and Port
#define RW PINB1						//RW Pin and Port
#define EN PINB2						//EN Pin and Port
#define LCD_Data_Port PA				//Data Port
#endif
/******************************************************************************************************************/
/******************************************************************************************************************/
/************************************************************************/
/*  LCD APIs                                                            */
/************************************************************************/
void LCD_init(void);
void LCD_sendcommand (u8 cmnd);
void LCD_sendChar (u8 char_data);
void LCD_sendString (u8 *str);
void LCD_createCustomCharacter (u8 *pattern , u8 location );
void LCD_clear(void);
void LCD_floattostring (f32 float_value);
void LCD_setCursor (u8 row , u8 column);
/************************************************************************/
#endif /* LCD_H_ */
