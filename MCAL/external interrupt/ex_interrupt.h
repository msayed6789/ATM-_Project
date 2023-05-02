/*
 * EX_Interrupt.h
 *
 * Created: 5/2/2022 7:54:42 PM
 *  Author: Mohamed Sayed
 */ 


#ifndef EX_INTERRUPT_H_
#define EX_INTERRUPT_H_

#include "memmap.h"
#include "utlise.h"
#include "standard_type.h"


typedef enum {
	LOW_LEVEL=0,
	ANY_LOGIC_CHANGE,
	FALLING_EDGE,
	RISING_EDGE
}TriggerEdge_type;

typedef enum{
	EX_INT0,
	EX_INT1,
	EX_INT2,
}ExInterruptSource_type;

void EXI_Enable (ExInterruptSource_type Interrupt);
void EXI_Disable (ExInterruptSource_type Interrupt);
void EXI_Trigger(ExInterruptSource_type Interrupt,TriggerEdge_type trigger);
void EXI_SetCallBack(ExInterruptSource_type Interrupt,void(*pf)(void));





#endif /* EX_INTERRUPT_H_ */
