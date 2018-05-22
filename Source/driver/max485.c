#include "max485.h"



sbit MAX485_EN = P4^3;	// 1£∫∑¢ÀÕ  0£∫Ω” ‹

void MAX485_Init(void) {
    Uart3Init();
	MAX485_EN = 0;
}

void MAX485_WriteStr(uint8_t * str) {
	MAX485_EN = 1;
    Uart3SendStr(str);
	MAX485_EN = 0;
}

void MAX485_WriteHex(uint8_t * str, uint16_t len) {
	MAX485_EN = 1;
    Uart3SendHex(str, len);
	MAX485_EN = 0;
}
