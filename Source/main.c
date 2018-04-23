#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"

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
    int a = 0;
    
    Uart3Init();
    EA = 1;
    while (1) {
        printf("printf ok\n");
        Delay500ms();
    }
}