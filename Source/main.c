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
#include "timer.h"
#include "gt20.h"
#include "led.h"
#include "key.h"
#include "botp.h"

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
void SystemInit(void) {
    SCON    = 0x00;
    S2CON   = 0x00;
    S3CON   = 0x00;
    S4CON   = 0x00;
    
    AUXR    = 0x00;
    AUXR2   = 0x00;
}

void RunDev(void) {        
    BOTP b;
    BOTP * pb;
	Pack_t *p = &(b.Pack);
    
	int i = 0;
    if (DevBufIndex > 0) {
        printf("DevBuffer:%bx\r\n", DevBuffer[0]);
        Delay_ms(10);
        if (DevBufIndex > 0x1A) {
            pb = (BOTP *)DevBuffer;
            if (DevBufIndex >= (pb->PackLen + 0x1C)) {
                Delay_ms(10);
                printf("dev ret:%bu\r\n", BOTP_Exec(pb));
                DevBufIndex = 0;
                for (i = 0;i < 256;i++) {
                    DevBuffer[i] = 0x00;
                }
            } 
            ExtDev_ClearDeviceTable();
        }
        DevBufIndex = 0;
    }
}

void RunUser(void) {
    BOTP b;
    BOTP * pb;
	Pack_t *p = &(b.Pack);
	int i = 0;
    
    if (UserBufIndex > 0) {
        Delay_ms(10);            
        if (UserBufIndex > 0x1A) {
            pb = (BOTP *)UserBuffer;
            if (UserBufIndex >= (pb->PackLen + 0x1C)) {
                Delay_ms(10);
                printf("User ret:%bu\r\n", BOTP_Exec(pb));
                UserBufIndex = 0;
                for (i = 0;i < 256;i++) {
                    UserBuffer[i] = 0x00;
                }
            } 
            ExtDev_ClearDeviceTable();
        }
    }
}


void main(void) {
    SystemInit();
    
    
    UartInit();
    MAX485_Init();
    Uart4Init();
    
    EA = 1;
    
    Delay500ms();
    Delay500ms();
    Delay500ms();
    Delay500ms();
    printf("uart Init\r\n");
    DevBufIndex = 0;
    UserBufIndex = 0;
    while (1) {
        RunDev();
        RunUser();
        
//        if (IS_HAVE_DATA()) {
//            Delay500ms();            
//            if (wptr > 0x1A) {
//                pb = (BOTP *)buffer;
//                if (wptr >= (pb->PackLen + 0x1C)) {
//                    Delay_ms(10);
//                    printf("ret:%bu\r\n", BOTP_Exec(pb));
//                    wptr = 0;
//                    for (i = 0;i < 256;i++) {
//                        buffer[i] = 0x00;
//                    }
//                } 
//                ExtDev_ClearDeviceTable();
//            }
//        }
    }
}