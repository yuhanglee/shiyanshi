#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "uart.h"
#include "string.h"
#include "24c02.h"
#include "max485.h"
#include "timer.h"
#include "key.h"
#include "botp.h"
#include "delay.h"
#include "crc.h"

/****************************/


typedef struct {
	void *		ReadBuf;
	void *		WriteBuf;
	uint16_t	ReadBufIndex;
	uint16_t	WriteBufIndex;
	uint8_t		Status;
} TASK;


volatile uint8_t     _PadReadBuf[256]        = {0};
volatile uint8_t     _PadWriteBuf[256]       = {0};

volatile uint8_t     _4851ReadBuf[256]       = {0};
volatile uint8_t     _4851WriteBuf[256]      = {0};
volatile uint32_t    _4851Data[4]            = {0};

volatile uint8_t     _4852ReadBuf[256]       = {0};
volatile uint8_t     _4852WriteBuf[256]      = {0};

volatile uint8_t     _4853ReadBuf[256]       = {0};
volatile uint8_t     _4853WriteBuf[256]      = {0};

volatile uint8_t     _DebugReadBuf[256]      = {0};
volatile uint8_t     _DebugWriteBuf[256]     = {0};




void SystemInit(void) {
    SCON    = 0x00;
    S2CON   = 0x00;
    S3CON   = 0x00;
    S4CON   = 0x00;
    
    AUXR    = 0x00;
    AUXR2   = 0x00;

	IE2 	= 0x00;
	T4T3M 	= 0x00;
}


void HardwareInit(void) {
	Timer0_Init(CALC_COUNT(1,1000));
    UartInit();     // uart 1 
    MAX485_Init();  // uart 2 
    Uart3Init();    // uart 3
    
}

BOTP b; // 保存 led 的数据
void RunKey(void) {   
	int i = 0;
    uint8_t key = 0;
    
    key = KEY_Scan();
    if (key != 0x00) {
        switch (key) {
        }
        b.Msg.BusID = device[1].Msg.BusID;
        b.Msg.Type  = device[1].Msg.Type;
        BOTP_SendData(&b);
        
        for (i = 0;i < 128;i++) {
            print_debug("%bx ", ((uint8_t *)(&b))[i]);
        }
    }
}

void RunUser(void) {
    /*
    BOTP * pb;
	int i = 0;
    uint8_t index = 0;
	uint8_t ret = 0;
    for (index = 0;index < 2;index++) {
        if (TCB[index].ReadBufIndex > 0) {
            Delay_ms(3);
            if (TCB[index].ReadBufIndex > 0x1A) {
                pb = (BOTP *)(TCB[index].ReadBuf);
                if (TCB[index].ReadBufIndex >= (pb->PackLen + 0x1C)) {
                    Delay_ms(3);
					ret = BOTP_Exec(pb);
                    TCB[index].ReadBufIndex = 0;
	                if (0x12345678 == BOTP_GetDMacAddr(*pb)) {
	                    memcpy(&b, pb, sizeof(b));
	                }
					for (i = 0;i < 256;i++) {
                        ((uint8_t *)(TCB[index].ReadBuf))[i] = 0x00;
                    }
                }
			}
		}
    }
    */
}

void main(void) {
	uint8_t value = 0;
    uint8_t a = 0;
	int i = 0;
    BOTP * pb;
	
    SystemInit();
    HardwareInit();
     
    memset(&b, 0, sizeof(b));
	// 开启中断
    EA = 1;
    
    // 延时，使系统正常启动
    Delay500ms();
    print_debug("uart Init\r\n");

	
    while (1) {
		if (IS_TIME_OUT_1MS(e_TimTest, 1000) == 1) {
			printf("time out test\r\n");
		}
	}

	
	
    while (1) {
        RunKey();
        RunUser();
    }
}