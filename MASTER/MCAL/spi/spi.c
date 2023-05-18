/*
 * spi.c
 *
 * Created: 5/2/2023 8:00:01 PM
 *  Author: ebrahem
 */ 
#include "spi.h"

void SPImaster_init()
{
	
	// 1. set MOSI, SCK, SS as an output pin
	
	DDRB |= (1<<MOSI)  | (1<<SS)  | (1<<SCK);
	
	//2. set MISO ad an input pin
	
	DDRB &= ~(1<<MISO);
	
	//3.Set ss pin to high
	
	//PORTB |= (1<<SS);
	
	//4. Enable SPI in master mode with /16 prescaler
	
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	//5. Disable Speed doubler
	
	SPSR &= ~(1<<SPI2X);
}


u8 SPImaster_send(u8* text,u8 size)
{
	u8 flush_buffer;
	u8 i=0;
	
	//1. Pull SS Pin to low
	
	//PORTB &= ~(1<<SS);
	//Delay_ms(50);
	
	
	for(i=0;i<size;i++)
	{
		//2. Write data to SPI data register
		SPDR = text[i];
		
		//3. Wait till transmission complete
		while(!(SPSR & (1<<SPIF)));
		//4. Flush received data
		text[i] = SPDR;
		
	}
	
	//PORTB |= (1<<SS);
	
	return flush_buffer;
	
}



void SPIslave_init()
{
	DDRB	|=	(1<<3);
	// 1. set MOSI, SCK, SS as an input pin
	
	
	
	//2. set MISO ad an output pin
	
	DDRB |= (1<<MISO);
	
	
	//3. Enable SPI in slave mode with /16 prescaler
	
	SPCR = (1<<SPE)|(1<<SPR0);
	
	//5. Disable Speed doubler
	
	SPSR &= ~(1<<SPI2X);
}



u8 SPIslave_receive(u8* text,u8 size)
{
	
		u8 i=0;
		
		for(i=0;i<size;i++)
		{
			//1. Set dummy value
			SPDR = 0x01;
			
			//2. Wait till reception complete
			while(!(SPSR & (1<<SPIF)));
			
			
			//3. Return received data
			text[i] = SPDR;
			
			
		}
		
		
		return 1;
}
