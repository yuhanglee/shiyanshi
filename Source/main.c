#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"
#include "wc_string.h"
#include "command.h"
#include "string.h"
#include "24c02.h"
#include "oled.h"



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
    
    
    Uart3Init();
    EA = 1;
    
    OLED_Init();
    while (1) {
        OLED_DisplayStr(0, 0, str);
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