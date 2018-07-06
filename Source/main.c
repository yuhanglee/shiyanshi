#include "stc8.h"
#include "mylib.h"
#include "intrins.h"
#include "LCD.h"
#include "uart.h"
#include "UartLcd.h"
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
	KEY_Init();
    UartInit();     // uart 1 
    MAX485_Init();  // uart 3
    Uart2Init();    // uart 2
    UartLcdInit();	// uart 4
}

BOTP b; // 保存 led 的数据

extern uint16_t UartLcdCmdStrIndex;
extern char 	UartLcdCmdStr[];    // 串口屏读写缓冲区
void RunKeyUartLcd(void) {   
	int i = 0;
    uint8_t key = 0;
    
    key = KEY_Scan();
    if (key != KEY_ERROR) {
		print_debug("%d", key);
		switch (key) {
			case KEY_UP: 
				printf("up\r\n");
				UartLcdCmdStrIndex = LCD_ChooseUp(UartLcdCmdStr, UartLcdCmdStrIndex);
			break;
				

			case KEY_DOWN:
				printf("down\r\n");
				UartLcdCmdStrIndex = LCD_ChooseDown(UartLcdCmdStr, UartLcdCmdStrIndex);
			break;

			case KEY_LIFT:
				printf("lift\r\n");
				UartLcdCmdStrIndex = LCD_ChooseLeft(UartLcdCmdStr, UartLcdCmdStrIndex);
			break;

			case KEY_RIGHT:
				printf("right\r\n");
				UartLcdCmdStrIndex = LCD_ChooseRight(UartLcdCmdStr, UartLcdCmdStrIndex);
			break;

			case KEY_OK:
				printf("ok\r\n");
				UartLcdCmdStrIndex = LCD_ChooseOK(UartLcdCmdStr, UartLcdCmdStrIndex);
			break;
		}
		UartLcdSendStr(UartLcdCmdStr);
		UartLcdCmdStrIndex = 0;
		printf("cur:%02bu\r\n", CurCoorIndex);
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
    
	UartLcdSendStr("SPG(2);"); // 直接跳转到第二页
    // 延时，使系统正常启动
   	while (IS_TIME_OUT_1MS(e_TimTest, 500));
    print_debug("uart Init\r\n");

	
    while (1) {
		RunKeyUartLcd();
		RunUser();
	}
}