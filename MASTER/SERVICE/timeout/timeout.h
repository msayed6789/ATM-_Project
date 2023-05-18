/*
 * timeout.h
 *
 * Created: 4/23/2023 1:07:54 PM
 *  Author: AIO
 */ 


#ifndef TIMEOUT_H_
#define TIMEOUT_H_

#include "interrupt_service.h"
#include "timer.h"
//intial values
#define zero_intial 0x00
#define Intial_value_time_out 0x0F  // ff -0f = 240 * 4 loops = 960 us which there is 40 us consumed by program
//prescaler values
#define pres_1 0x01
#define pres_8 0x02
#define pres_64 0x03
#define pres_256 0x04
#define pres_1024 0x05

void TIME_out (u32 milliseconds);




#endif /* TIMEOUT_H_ */
