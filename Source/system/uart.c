#include "uart.h"
#include "stc8.h"

#define BRT         (65536 - FOSC / 115200 / 4)

bit busy;
char wptr = 0;
char rptr = 0;
char buffer[16] = {0};


char putchar(char c) {
    Uart3Send(c);
    return c;
}

void Uart1Isr(void) interrupt 4 using 1 {
    
}

void UartInit(void) {
    SCON = 0x50;
    T2L = BRT &0xff;
    T2H = (BRT >> 8) & 0xff;
    AUXR = 0x15;
    ES = 1;
}

void Uart1Send(char dat) {
    //EA = 0;
    SBUF = dat;
    while (!TI);
    TI = 0;
    //EA = 1;
}

void Uart1SendStr(char *p) {
    while (*p) {
        Uart1Send(*p++);
    }
}



void Uart2Isr() interrupt 8 using 1
{
    if (S2CON & 0x02)
    {
        S2CON &= ~0x02;
        busy = 0;
    }
}

void Uart2Init()
{
    S2CON = 0x50;
    IE2 = 0x11;
}

void Uart2Send(char dat)
{
    while (busy);
    busy = 1;
    S2BUF = dat;
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
    if (S3CON & 0x02)
    {
        S3CON &= ~0x02;
        busy = 0;
    }
    if (S3CON & 0x01)
    {
        S3CON &= ~0x01;
        buffer[wptr++] = S3BUF;
        wptr &= 0x0f;
    }
}

void Uart3Init()
{
    S3CON = 0x10;
    T2L = BRT;
    T2H = BRT >> 8;
    AUXR = 0x14;
    
    IE2 = 0x08;
}

void Uart3Send(char dat)
{
    while (busy);
    busy = 1;
    S3BUF = dat;
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
    S4CON = 0x10;
}

void Uart4Send(char dat)
{
    while (busy);
    busy = 1;
    S4BUF = dat;
}

void Uart4SendStr(char *p)
{
    while (*p)
    {
        Uart4Send(*p++);
    }
}


