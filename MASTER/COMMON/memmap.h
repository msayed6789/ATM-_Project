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

/****************************************************************************************************/


/*******************************************************************************************************/
//interrupt

#define INT0		6
#define INT1		7
#define	INT2		5
#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3
#define ISC2		6

#define GICR	(*(volatile unsigned char *)(0x5B))

#define MCUCR	(*(volatile unsigned char *)(0x55))

#define MCUCSR	(*(volatile unsigned char *)(0x54))






/*TIMER 1*/

#define WGM10		0
#define WGM11		1
#define WGM12		3
#define WGM13		4
#define OCIE1A		4



#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)
#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B       (*(volatile unsigned char*)0x4E)
#define TCCR1A        (*(volatile unsigned char*)0x4F)

#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)

//#define TCCR1A		(*(volatile unsigned char*)0x4F)

// Timer2 Registers
/******************************************************************************/
#define TCNT2   (*(volatile unsigned char*)(0x44))
#define TCCR2   (*(volatile unsigned char*)(0x45))
#define OCR2    (*(volatile unsigned char*)(0x43))
#define TOIE2 6 //overflow enable bit
#define OCF2  7 //Output Compare Flag bit
#define TOV2  6 //Timer2 Overflow Flag bit
/******************************************************************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0
/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    PE           2
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define    URSEL        7
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0

/*********************************************************************************/
/* Interrupt vectors */
/* External Interrupt Request 0 */
#define INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define INT2_vect			__vector_3
/* Timer/Counter1 Capture Event */
#define TIMER1_ICU_vect		__vector_6
/* Timer/Counter1 Compare Match A */
#define TIMER1_OCA_vect		__vector_7
/* Timer/Counter1 Compare Match B */
#define TIMER1_OCB_vect		__vector_8
/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect			__vector_9
/* USART, Rx Complete */
#define UART_RX_vect			__vector_13
/* USART Data Register Empty */
#define UART_UDRE_vect			__vector_14
/* USART, Tx Complete */
#define UART_TX_vect			__vector_15
/******************************************************************************/
/*interrupt functions*/

#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)
# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)




/*******************************************************************************************/

// SPI


#define SPCR  (*(volatile unsigned char *)0x2D)
#define SPSR  (*(volatile unsigned char *)0x2E)
#define SPDR  (*(volatile unsigned char *)0x2F)







#endif /* MEMMAP_H_ */
