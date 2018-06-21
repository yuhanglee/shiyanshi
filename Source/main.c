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
#include "delay.h"
#include "crc.h"

/****************************/
// WCOS
#include "WCOS_task.h"

WCOS_TASK_CB TCB[5] = {0};

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


void TCB_Init(void) {
    uint8_t i = 0;
    
    for (i = 0;i < 5;i++) {
        TCB[i].ReadBufIndex     =   0;
        TCB[i].WriteBufIndex    =   0;
        TCB[i].TaskStatus       &=  0x00;
    }
    TCB[0].ReadBuf              =   (void *)_PadReadBuf;
    TCB[0].WriteBuf             =   (void *)_PadWriteBuf;
    
    TCB[1].ReadBuf              =   (void *)_4851ReadBuf;
    TCB[1].WriteBuf             =   (void *)_4851WriteBuf;
    TCB[1].FuncArgc             =   (void *)_4851Data;
    
    TCB[2].ReadBuf              =   (void *)_4852ReadBuf;
    TCB[2].WriteBuf             =   (void *)_4852WriteBuf;
    
    TCB[3].ReadBuf              =   (void *)_4853ReadBuf;
    TCB[3].WriteBuf             =   (void *)_4853WriteBuf;
    
    TCB[4].ReadBuf              =   (void *)_DebugReadBuf;
    TCB[4].WriteBuf             =   (void *)_DebugWriteBuf;
		
	memset(TCB[0].ReadBuf, 0, 256);
	memset(TCB[0].WriteBuf, 0, 256);
	memset(TCB[1].ReadBuf, 0, 256);
	memset(TCB[1].WriteBuf, 0, 256);
	memset(TCB[2].ReadBuf, 0, 256);
	memset(TCB[2].WriteBuf, 0, 256);
	memset(TCB[3].ReadBuf, 0, 256);
	memset(TCB[3].WriteBuf, 0, 256);
	memset(TCB[4].ReadBuf, 0, 256);
	memset(TCB[4].WriteBuf, 0, 256);
}


void SystemInit(void) {
    SCON    = 0x00;
    S2CON   = 0x00;
    S3CON   = 0x00;
    S4CON   = 0x00;
    
    AUXR    = 0x00;
    AUXR2   = 0x00;
}


void HardwareInit(void) {
    UartInit();     // 调试串口
    MAX485_Init();  // 485 1 
    Uart3Init();    // pad ch340
    
    OLED_Init();    // OLED
}

BOTP b; // 保存led的发送数据
void RunKey(void) {   
	int i = 0;
    uint8_t key = 0;
    // 按键控制
    key = KEY_Scan();
    if (key != 0x00) {
        switch (key) {
            case KEY_1:
                KeyFunc1(&b);
            break;
            
            case KEY_2:
                KeyFunc2(&b);
            break;
            
            case KEY_3:
                KeyFunc3(&b);
            break;
            
            case KEY_4:
                KeyFunc4(&b);
            break;
            
            default:
                print_debug("key error\r\n");
                return ;
        }
        b.Msg.BusID = device[1].Msg.BusID;
        b.Msg.Type  = device[1].Msg.Type;
        BOTP_SendData(&b);
        
        for (i = 0;i < 128;i++) {
            print_debug("%bx ", ((uint8_t *)(&b))[i]);
        }
    }
}

void OLEDRunTask(void) {
    uint8_t c1, c, OLEDChange = 0x00;
    static uint8_t oldChange = 0x00;

    uint8_t *bc = (uint8_t *)(&b);
    uint32_t freq = 0x00;
    
    if (0xff == bc[29]) {
        freq =((*((uint32_t *)(&(bc[32])))) >> 20) & 0x3ff;
    } else if (0xff == bc[30]) {
        freq =((*((uint32_t *)(&(bc[32])))) >> 10) & 0x3ff;
    } else if (0xff == bc[31]) {
        freq =((*((uint32_t *)(&(bc[32])))) >> 00) & 0x3ff;
    }
    c = freq;
    c1 = 2;
    // 如果两次的值不一致，进行更改
    if (freq != oldChange) {
        print_debug("%bx, %bx\r\n", freq, oldChange);
        OLEDChange = 1;
        oldChange = freq;
    }
    c = freq;
    c1 = 2;
    // 进行刷新屏幕
    if (OLEDChange) {
        OLEDChange = 0;
        OLED_Clear();
        OLED_DisplayHanziStr(1, 0, "当前频率", 0);
        OLED_DisplayStr(9, 1, "Hz", 0);
        while (c1) {
            c1--;
            OLED_DisplayChar(c1 + 6, 1, (c % 10) + '0', 0);
            c /= 10;
        }
        OLED_Refresh_Gram();
    } else if (bc[28] == 0x01) {
        memset(&b, 0, sizeof(b));
        OLED_DisplayLogo();
        OLED_Refresh_Gram();
    }
}
void RunUser(void) {
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
}

void main(void) {
	uint8_t value = 0;
    uint8_t a = 0;
	int i = 0;
    BOTP * pb;
	
    SystemInit();
    HardwareInit();
	TCB_Init();		// 任务初始化
     
    memset(&b, 0, sizeof(b));
	// 开启中断
    EA = 1;
    
    // 寤舵椂锛屼娇绯荤粺姝ｅ父鍚姩
    Delay500ms();
    print_debug("uart Init\r\n");
	OLED_DisplayLogo();
	OLED_Refresh_Gram();
/*
	while (1) {
		if (TCB[0].ReadBufIndex > 0) {
			Delay_ms(3);
			if (TCB[0].ReadBufIndex > 0x1A) {
                pb = (BOTP *)(TCB[0].ReadBuf);
                if (TCB[0].ReadBufIndex >= (pb->PackLen + 0x1C)) {
                    Delay_ms(3);
					//ret = BOTP_Exec(pb);
	                print_debug("CRC = %X\r\n", CRC_16((uint8_t *)(&(pb->Pack)), pb->PackLen));
					for (i = 0;i < TCB[0].ReadBufIndex;i++) {
						print_debug("%02bX ", ((uint8_t *)TCB[0].ReadBuf)[i]);
                    }
					print_debug("\r\n");
                    TCB[0].ReadBufIndex = 0;
                }
			}
		}
	}
	*/
	
    while (1) {
        RunKey();
        RunUser();
        OLEDRunTask();
    }
}