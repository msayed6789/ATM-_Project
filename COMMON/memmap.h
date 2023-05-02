/*
 * memmap.h
 *
 * Created: 4/23/2023 12:40:56 PM
 *  Author: AIO
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

/*************************DIO*********************/
#define DDRA  (*(volatile unsigned char *)0x3A)
#define PORTA (*(volatile unsigned char *)0x3B)
#define PINA  (*(volatile unsigned char *)0x39)


#define DDRB  (*(volatile unsigned char *)0x37)
#define PORTB (*(volatile unsigned char *)0x38)
#define PINB  (*(volatile unsigned char *)0x36)


#define DDRD  (*(volatile unsigned char *)0x31)
#define PORTD (*(volatile unsigned char *)0x32)
#define PIND  (*(volatile unsigned char *)0x30)


#define DDRC  (*(volatile unsigned char *)0x34)
#define PORTC (*(volatile unsigned char *)0x35)
#define PINC  (*(volatile unsigned char *)0x33)




/****************************ADC******************************/


#define ADMUX	(*(volatile unsigned char *)0x27)
#define ADCSRA  (*(volatile unsigned char *)0x26)
#define ADCH	(*(volatile unsigned char *)0x25)
#define ADCL	(*(volatile unsigned char *)0x24)

// Timer0 Registers
/******************************************************************************/
#define TCNT0   (*(volatile unsigned char*)(0x52))
#define TCCR0   (*(volatile unsigned char*)(0x53))
#define OCR0    (*(volatile unsigned char*)(0x5C))
#define TIMSK   (*(volatile unsigned char*)(0x59))
#define TOIE0 0 //overflow enable bit
#define TIFR    (*(volatile unsigned char*)(0x58))

// Timer2 Registers
/******************************************************************************/
#define TCNT2   (*(volatile unsigned char*)(0x44))
#define TCCR2   (*(volatile unsigned char*)(0x45))
#define OCR2    (*(volatile unsigned char*)(0x43))
#define TOIE2 6 //overflow enable bit
#define OCF2  7 //Output Compare Flag bit
#define TOV2  6 //Timer2 Overflow Flag bit
/******************************************************************************/
/******************************************************************************/
/*interrupt functions*/

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)


#endif /* MEMMAP_H_ */