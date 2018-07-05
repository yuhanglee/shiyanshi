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

volatile uint8_t     PadReadBuf[256]        = {0};
volatile uint8_t     PadWriteBuf[256]       = {0};

volatile uint8_t     max485ReadBuf[256] 	= {0};
volatile uint8_t     max485WriteBuf[256]    = {0};

int a = 0;
void SystemInit(void) {
    SCON    = 0x00;
    S2CON   = 0x00;
    S3CON   = 0x00;
    S4CON   = 0x00;
    
    AUXR    = 0x00;
    AUXR2   = 0x00;
}


void HardwareInit(void) {
    UartInit();     // debug uarts
    MAX485_Init();  // 485 1 
    Uart3Init();    // pad ch340
}

void TaskTest1(void) {
	while(1) {
		Uart1Send('a');
		TaskDelay(1000);
	}
}

void TaskTest2(void) {
	while (1) {
		Uart1Send('b');
		TaskDelay(500);
	}
}

void CreateUserTask(void) {
	TaskCreate(TaskTest1, 0);
	TaskCreate(TaskTest2, 1);
}

BOTP b; 
void main(void) {
    SystemInit();
    HardwareInit();
	TaskInit();    
    memset(&b, 0, sizeof(b));

	CreateUserTask();

	Timer0_Init(0xD4CD);
	TIMER0_ENABLE();
	EA = 1;
    TaskStart();
}