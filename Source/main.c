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

static void Delay_ms(uint16_t Del_1ms) {
	uint8_t j;
    
	while (Del_1ms--) {	
		for (j  =0;j < 123;j++) {
        
        }
	}
}

static void Delay500ms()		//@11.0592MHz
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
    uint8_t i = 0x20, j = 0, c = 0;
    
    
    UartInit();
    
//    Uart2Init();
//    Uart4Init();
    
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
//    OLED_DisplayStr(0, 0, "45sss");
//    OLED_DisplayStr(0, 1, "45sss");
//    OLED_DisplayStr(0, 2, "45sss");
//    OLED_DisplayStr(0, 3, "45sss");
//    OLED_Refresh_Gram();
    OLED_DisplayChar(0, 0, '1');
    OLED_DisplayChar(0, 1, '2');
    OLED_DisplayChar(0, 2, '3');
    OLED_DisplayChar(0, 3, '4');
    
    OLED_Refresh_Gram();
    OLED_ScrollLeft(OLED_CMD_SCROLL_PAGE_4, OLED_CMD_SCROLL_PAGE_7, OLED_CMD_SCROLL_2_FRANES);
    while (1) {
//        if (rptr != wptr)
//        {
//            buffer[wptr] = 0;
//            OLED_DisplayStr((i&0x0f), (i >> 4)&0x03, buffer);
//            wptr = 0;
//        }
//        Uart2Send(i);
        i = i<8?i+1:0;
        Delay_ms(5000);
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