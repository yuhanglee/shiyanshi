#include "timer.h"
#include "led.h"

#define BRT         (65536 - FOSC / 115200 / 4)

uint16_t t3_1 = 0;

uint16_t TimerDelayArray[e_TimMax] = {0};

void TIM0_IRQ(void)         interrupt 1 {

}
    
void TIM1_IRQ(void)         interrupt 3 {

}


void TIM2_IRQ(void)         interrupt 12 {
    /* empty */
}

void TIM3_IRQ(void)         interrupt 19 {
    static uint16_t i = 0;
    EA = 0;
    if (i < fre/2) {
        switch (color) {
            case LED_R:
                LED_R_SET();
                LED_G_RESET();
                LED_B_RESET();
            break;
            
            case LED_B:
                LED_B_SET();
                LED_R_RESET();
                LED_G_RESET();
            break;
            break;
            
            case LED_G:
                LED_G_SET();
                LED_R_RESET();
                LED_B_RESET();
            break;
            
            case 4:
                LED_G_RESET();
                LED_R_RESET();
                LED_B_RESET();
            break;
            
            default:
                
            break;
        }
    } else {
        switch (color) {
            case LED_R:
                LED_R_RESET();
            break;
            
            case LED_B:
                LED_B_RESET();
            break;
            
            case LED_G:
                LED_G_RESET();
            break;
            
            default:
                
            break;
        }
    }
    i = i >= fre? 0: i+1;
    EA = 1;
    AUXINTIF &= ~T3IF;                          //���жϱ�־
}

void TIM4_IRQ(void)         interrupt 20 {

}



/* �̶�Ϊ��ʱ1mS��ʱ�����ѭ����ʱҪ�� */
void Timer3_Init(Timer * tim) {
    uint8_t tmod_t = 0;
    uint16_t count = 0;
    
    wc_assert(IS_TIMER_TYPE(tim->Type));
    wc_assert(IS_TIMER_MODE(tim->Mode));
    wc_assert(IS_TIMER_FREQ_DIV(tim->FreqDiv));
    wc_assert(IS_TIMER_COUNT(tim->Count));

    if (TIMER_TYPE_COUNT == tim->Type) {
        TIMER3_COUNT();
    } else {
        tmod_t = TIMER3_GET_COUNT();
        TMOD = 0x00;
        TMOD = tmod_t;
    }
    if (TIMER_FREQ_DIV_12 == tim->FreqDiv) {
        TIMER3_FREQ_ENABLE();
    } else {
        TIMER3_FREQ_DISABLE();
    }
    
    count = CALC_COUNT(FOSC, tim->FreqDiv, tim->Count);
//    TIMER3_TH(((count >> 8) & 0xff));
//    TIMER3_TL((count & 0xff));
	T3L = 0xA0;		//??????
	T3H = 0xF6;		//??????
    TIMER3_ENABLE();
    TIMER3_RUN();
}
/* ��ʱ��2�Ǹ����ڵ��������ʷ������ģ�����������������; 
 * �����Ҫʹ�� 12T ģʽ������Ҫ����Ϊ 11.0592MHz��
 * 24MHz ʹ��12T ģʽ�����ֵ̫����ɶ�дʧ��
 */
void Timer2_Init(uint16_t count) { 
    TIMER2_TL(count &0xff);
    TIMER2_TH((count >> 8) & 0xff);
    TIMER2_RUN();
    TIMER2_FREQ_DISABLE();          // @24MHz
}

void Timer1_Init(Timer * tim) {
    uint8_t tmod_t = 0;
    uint16_t count = 0;
    
    wc_assert(IS_TIMER_TYPE(tim->Type));
    wc_assert(IS_TIMER_MODE(tim->Mode));
    wc_assert(IS_TIMER_FREQ_DIV(tim->FreqDiv));
    wc_assert(IS_TIMER_COUNT(tim->Count));

    if (TIMER_TYPE_COUNT == tim->Type) {
        TIMER1_COUNT();
    } else {
        tmod_t = TIMER1_GET_COUNT();
        TMOD = 0x00;
        TMOD = tmod_t;
    }
    
    TIMER1_MODE(tim->Mode);
    if (TIMER_FREQ_DIV_12 == tim->FreqDiv) {
        TIMER1_FREQ_ENABLE();
    } else {
        TIMER1_FREQ_DISABLE();
    }
    
    count = CALC_COUNT(FOSC, tim->FreqDiv, tim->Count);
    
    TIMER1_TH(((count >> 8) & 0xff));
    TIMER1_TL((count & 0xff));
}

void Timer_Init(uint8_t TimerNum, Timer * tim) {
    wc_assert(IS_TIMER(TimerNum));
    wc_assert(IS_TIMER_TYPE(tim->Type));
    wc_assert(IS_TIMER_MODE(tim->Mode));
    wc_assert(IS_TIMER_FREQ_DIV(tim->FreqDiv));
    wc_assert(IS_TIMER_COUNT(tim->Count));
    
    switch (TimerNum) {
        case Timer1:
            break;
        
        case Timer2:
            break;
        
        case Timer3:
            break;
        
        case Timer4:
            break;
        
        case Timer5:
            break;
    }
    
}
