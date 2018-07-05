#ifndef __MAX485_H__
#define __MAX485_H__

#include "uart.h"
#include "mylib.h"


sbit MAX485_EN = P2^7;	// 1������  0������


void MAX485_Init(void);
void MAX485_WriteStr(uint8_t * str);
void MAX485_WriteHex(uint8_t * str, uint16_t len);

#endif
