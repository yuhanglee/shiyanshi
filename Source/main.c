#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"
#include "wc_string.h"
#include "command.h"
#include "string.h"
#include "24c02.h"
#include "oled.h"
#include "max485.h"


void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
extern char wptr;
extern char rptr;
extern char buffer[];

void main(void) {
    char str[10] = "hello";
    uint8_t i = 0;
    
    
    UartInit();
    
    Uart2Init();
    Uart4Init();
    
    EA = 1;
//    while (1) {
//            print_info("EE");
//        if (rptr != wptr)
//        {
//            buffer[wptr] = 0;
//            print_info("L");
//            wptr = 0;
//        }
//        Uart2Send('a');
//        Delay500ms();
//    }
    OLED_Init();
    while (1) {
        OLED_DisplayStr(1, 1, str);
        Delay500ms();
        OLED_Refresh_Gram();
        OLED_Clear();
        Delay500ms();
        OLED_Refresh_Gram();
    }
//    while (AT24CXX_Check()) {
//        print_debug("EEPROM check faild");
//    }
//    while (1) {
//        if (wptr != rptr) {
//            a = cmd_exec(cmd_check(buffer));
//            print_info(buffer);
//            wptr = 0;
//            memset(buffer, 0, 16);
//        }
//        Delay500ms();
//    }
}