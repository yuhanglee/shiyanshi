#include "uart.h"
#include "stc8.h"
#include "timer.h"
#include "botp.h"

#include "WCOS_task.h"

char putchar(char c) {
    Uart1Send(c);
    return c;
}
void Uart1Isr(void) interrupt 4 using 0 {
    if (RI) {
        ((uint8_t *)(TCB[0].ReadBuf))[TCB[0].ReadBufIndex++] = SBUF;
        TCB[0].ReadBufIndex &= 0xffff;
        RI = 0;
    }
}

void UartInit(void) {
    SCON |= 0x50;
    Timer2_Init(BRT);
    AUXR |= 0x01; 
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

void Uart1SendHex(uint8_t * buf, uint16_t len) {
    uint8_t i;
    
    for (i = 0;i < len;i++) {
        Uart1Send(buf[i]);
    }
}


void Uart2Isr(void) interrupt 8 using 1 {
    if (S2CON & 0x01) {
        ((uint8_t *)(TCB[2].ReadBuf))[TCB[2].ReadBufIndex++] = S2BUF;
        TCB[2].ReadBufIndex &= 0xffff;
        S2CON &= ~0x01;
    }
}

void Uart2Init(void){
    S2CON |= 0x50;
    Timer2_Init(BRT);
    IE2 |= 0x01;
}

void Uart2Send(char dat) {
    S2BUF = dat;
    while (!(S2CON & 0x02));
    S2CON &= ~0x02;
}

void Uart2SendStr(char *p) {
    while (*p) {
        Uart2Send(*p++);
    }
}

void Uart2SendHex(uint8_t * buf, uint16_t len) {
    while (len--) {
        Uart2Send(*buf++);
    }
}

void Uart3Isr(void) interrupt 17 using 1 {
    if (S3CON & 0x01) {
        ((uint8_t *)(TCB[0].ReadBuf))[TCB[0].ReadBufIndex++] = S3BUF;
        TCB[0].ReadBufIndex &= 0xffff;
        S3CON &= ~0x01;
    }
}
void Uart3Init(void) {
    S3CON |= 0x10;
    Timer2_Init(BRT);
    IE2 |= 0x08;
}
void Uart3Send(char dat) {
    S3BUF = dat;
    while (!(S3CON & 0x02));
    S3CON &= ~0x02;
}

void Uart3SendStr(char *p) {
    while (*p) {
        Uart3Send(*p++);
    }
}


void Uart3SendHex(uint8_t * buf, uint16_t len) {
    while (len--) {
        Uart3Send(*buf++);
    }
}

void Uart4Isr(void) interrupt 18 using 1 {
    if (S4CON & 0x01) {
        ((uint8_t *)(TCB[1].ReadBuf))[TCB[1].ReadBufIndex++] = S4BUF;
        TCB[1].ReadBufIndex &= 0xffff;
        S4CON &= ~0x01;
    }
}

void Uart4Init(void) {
    S4CON |= 0x10;
    Timer2_Init(BRT);
    IE2 |= 0x10;
}

void Uart4Send(char dat) {
    
    S4BUF = dat;
    while (!(S4CON & 0x02));
    S4CON &= ~0x02;
}

void Uart4SendStr(char *p) {
    while (*p)
    {
        Uart4Send(*p++);
    }
}

void Uart4SendHex(uint8_t * buf, uint16_t len) {
    while (len--) {
        Uart4Send(*buf++);
    }
}