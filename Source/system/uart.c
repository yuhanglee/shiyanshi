#include "uart.h"
#include "stc8.h"
#include "timer.h"

#define BRT         (65536 - FOSC / 115200 / 4)

bit busy;
uint8_t wptr = 0;
uint8_t rptr = 0;
char buffer[256] = {0};


char putchar(char c) {
    Uart1Send(c);
    return c;
}
void Uart1Isr(void) interrupt 4 using 1 {
    if (RI)
    {
        RI = 0;
    }
}

void UartInit(void) {
    SCON |= 0x50;
    Timer2_Init(BRT);
    AUXR |= 0x01; // ѡ��ʱ��2��Ϊ�����ʷ�����
    ES = 1;
}

void Uart1Send(char dat) {
    SBUF = dat;
    while (!TI);
    TI = 0;
}

void Uart1SendStr(char *p) {
    while (*p) {
        Uart1Send(*p++);
    }
}



void Uart2Isr() interrupt 8 using 1
{
    if (S2CON & 0x01)
    {
        S2CON &= ~0x01;
    }
}

void Uart2Init()
{
    S2CON |= 0x50;
    Timer2_Init(BRT);
    IE2 |= 0x01;
}

void Uart2Send(char dat)
{
    S2BUF = dat;
    while (!(S2CON & 0x02));
        S2CON &= ~0x02;
}

void Uart2SendStr(char *p)
{
    while (*p)
    {
        Uart2Send(*p++);
    }
}


void Uart3Isr() interrupt 17 using 1
{
    if (S3CON & 0x01)
    {
        S3CON &= ~0x01;
        buffer[wptr++] = SBUF;
    }
}

void Uart3Init()
{
    S3CON |= 0x10;
    Timer2_Init(BRT);
    IE2 |= 0x08;
}

void Uart3Send(char dat)
{
    S3BUF = dat;
    while (!(S3CON & 0x02));
    S3CON &= ~0x02;
}

void Uart3SendStr(char *p)
{
    while (*p)
    {
        Uart3Send(*p++);
    }
}



void Uart4Isr() interrupt 18 using 1
{
    if (S4CON & 0x01)
    {
        S4CON &= ~0x01;
        buffer[wptr++] = S4BUF;
        wptr &= 0x0f;
    }
}

void Uart4Init()
{
    S4CON |= 0x10;
    Timer2_Init(BRT);
    IE2 |= 0x10;
}

void Uart4Send(char dat)
{
    
    S4BUF = dat;
    while (!(S4CON & 0x02));
    S4CON &= ~0x02;
}

void Uart4SendStr(char *p)
{
    while (*p)
    {
        Uart4Send(*p++);
    }
}
