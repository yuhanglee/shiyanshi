#include "timer.h"
#include "led.h"

#define BRT         (65536 - FOSC / 9600 / 4)


void Timer3_Init(uint16_t count) { 
    TIMER3_TL(count & 0xff);
    TIMER3_TH((count >> 8) & 0xff);
    TIMER3_RUN();
    TIMER3_FREQ_DISABLE();
}
/* 用作波特率发生器 */
void Timer2_Init(uint16_t count) { 
    TIMER2_TL(count & 0xff);
    TIMER2_TH((count >> 8) & 0xff);
    TIMER2_RUN();
    TIMER2_FREQ_DISABLE(); 
}

void Timer1_Init(uint16_t count) { 
    TIMER1_TL(count & 0xff);
    TIMER1_TH((count >> 8) & 0xff);
    TIMER1_RUN();
    TIMER1_FREQ_DISABLE();
}
void Timer0_Init(uint16_t count) { 
	TIMER0_MODE(0);
	TIMER0_TL(count & 0xff);
    TIMER0_TH((count >> 8) & 0xff);
    TIMER0_RUN();
    TIMER0_FREQ_DISABLE();
    /*AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时*/
}