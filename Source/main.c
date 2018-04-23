#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"
#include "wc_string.h"

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
    uint8_t a = 0;
    char str[10];
    char str1[] = "str1";
    char str2[] = "str2";
    
    Uart3Init();
    EA = 1;
    while (1) {
        print_info(str);
        Delay500ms();
        Delay500ms();
    }
}