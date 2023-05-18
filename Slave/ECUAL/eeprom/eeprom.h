/*
 * eeprom.h
 *
 * Created: 5/2/2023 1:17:12 PM
 *  Author: lenovo
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "i2c.h"
#include "delay.h"
void EEPROM_init(void);
void EEPROM_byteWrite(u8 data_address1,u8 data_address2,u8 data);
void EEPROM_byteRead(u8 data_address1,u8 data_address2,u8 *data);
void EEPROM_pageWrite(u8 data_address1,u8 data_address2,u8 *data);
void EEPROM_pageRead(u8 data_address1,u8 data_address2,u8 *data);
void EEPROM_erase(void);
#endif /* EEPROM_H_ */
