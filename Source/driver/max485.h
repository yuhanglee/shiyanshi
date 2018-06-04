#ifndef __MAX485_H__
#define __MAX485_H__

#include "uart.h"
#include "mylib.h"

#define _485_1      0x01
#define _485_2      0x02
#define _485_3      0x03


sbit MAX485_1_EN = P4^3;	// 1：发送  0：接受
sbit MAX485_2_EN = P5^5;	// 1：发送  0：接受
sbit MAX485_3_EN = P4^0;


void MAX485_Init(void);
void MAX485_WriteStr(uint8_t n, uint8_t * str);
void MAX485_WriteHex(uint8_t n, uint8_t * str, uint16_t len);

#endif
