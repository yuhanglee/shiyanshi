#ifndef __OLED_H__
#define __OLED_H__

#include "mylib.h"

#define OLED_X_MAX      16
#define OLED_Y_MAX      8

#define ASCII_SIZE_X    8
#define ASCII_SIZE_Y    16

void OLED_Init(void);
void OLED_DisplayChar(uint8_t x, uint8_t y, uint8_t ch);
void OLED_Refresh_Gram(void);
void OLED_DisplayStr(uint8_t x, uint8_t y, uint8_t * str);

#endif
