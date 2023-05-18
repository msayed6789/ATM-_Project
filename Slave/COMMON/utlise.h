/*
 * utlise.h
 *
 * Created: 4/23/2023 12:42:10 PM
 *  Author: AIO
 */ 


#ifndef UTLISE_H_
#define UTLISE_H_


#define F_CPU  8000000
#include <util/delay.h>
#include "standard_type.h"


#define Read_Bit(reg,bit)         (reg>>bit & 1)
#define Set_Bit(reg,bit)          (reg|=1<<bit)
#define CLR_Bit(reg,bit)          (reg&=~(1<<bit))
#define TOG_BIT(reg,bit)          (reg=reg^(1<<bit))
#define WRITE_BIT(reg,bit,val)    (reg=(reg&(~(1<<bit))) | (val<<bit))

#define UPPER_NIPPLE(reg,data)     (reg =(reg & 0x0F) | (data & 0xF0))
#define LOWER_NIPPLE(reg,data)     (reg =(reg & 0x0F) | (data << 4))



#endif /* UTLISE_H_ */