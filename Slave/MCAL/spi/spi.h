/*
 * spi.h
 *
 * Created: 5/2/2023 8:00:54 PM
 *  Author: ebrahem
 */ 

#ifndef SPI_H_
#define SPI_H_
#include "memmap.h"
#include "standard_type.h"


#define MOSI	5
#define MISO	6
#define SCK		7
#define SS		4

//////////////////////////

#define SPE		6
#define MSTR	4
#define SPR0	0

/////////////////////

#define SPI2X	0


////////////////////

#define SPIF	7



void SPImaster_init(void);

u8 SPImaster_send(u8* text,u8 size);

//u8 SPImaster_receive(u8* text,u8 size);

void SPIslave_init(void);

//u8 SPIslave_send(u8* text,u8 size);

u8 SPIslave_receive(u8* text,u8 size);


#endif /* SPI_H_ */
