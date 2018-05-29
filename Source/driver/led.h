#ifndef __LED_H__
#define __LED_H__
#include "mylib.h"
#include "botp.h"

extern uint32_t StatusFreq;

void FreqAdd(BOTP * pb, uint8_t num);
void FreqDec(BOTP * pb, uint8_t num);
void ColorChange(BOTP * pb, uint8_t num);
#endif
