#include "max485.h"


void Delay50us() {		//@24.000MHz
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}

void MAX485_Init(void) {
    Uart4Init();
//    Uart2Init();
	MAX485_1_EN = 0;
//	MAX485_2_EN = 0;
}

void MAX485_WriteStr(uint8_t n, uint8_t * str) {
	switch (n) {
        case _485_1:
            MAX485_1_EN = 1;
            Uart4SendStr(str);
            Delay50us();
            Delay50us();
            MAX485_1_EN = 0;
        break;
        
        case _485_2:
            MAX485_2_EN = 1;
            Uart2SendStr(str);
            Delay50us();
            Delay50us();
            MAX485_2_EN = 0;
        break;
        case _485_3:
            MAX485_3_EN = 1;
            Uart1SendStr(str);
            Delay50us();
            Delay50us();
            MAX485_3_EN = 0;
        break;
    }
}

void MAX485_WriteHex(uint8_t n, uint8_t * str, uint16_t len) {
	switch (n) {
        case _485_1:
            MAX485_1_EN = 1;
            Uart4SendHex(str, len);
            Delay50us();
            Delay50us();
            MAX485_1_EN = 0;
        break;
        
        case _485_2:
            MAX485_2_EN = 1;
            Uart2SendHex(str, len);
            Delay50us();
            Delay50us();
            MAX485_2_EN = 0;
        break;
        case _485_3:
            MAX485_3_EN = 1;
            Uart1SendHex(str, len);
            Delay50us();
            Delay50us();
            MAX485_3_EN = 0;
        break;
    }
}
