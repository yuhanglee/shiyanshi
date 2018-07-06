#include "timer.h"


volatile uint16_t TimerDelayArray[e_TimMax];

static uint8_t DelayIndex;

void TIM0_IRQ(void) interrupt 1 using 1 {
	for (DelayIndex = 0;DelayIndex < e_TimMax;DelayIndex++) {
		if (TimerDelayArray[DelayIndex] << 1) { // 最高为代表标志
			TimerDelayArray[DelayIndex]--;
		}
	}
}


void Timer3_Init(uint16_t count) { 
    wc_assert(IS_TIMER_COUNT(count));

    TIMER3_TL(count &0xff);
    TIMER3_TH((count >> 8) & 0xff);
    TIMER3_RUN();
    TIMER3_FREQ_DISABLE();          // @34MHz
    TIMER3_ENABLE();
}

void Timer2_Init(uint16_t count) { 
    wc_assert(IS_TIMER_COUNT(count));

    TIMER2_TL(count &0xff);
    TIMER2_TH((count >> 8) & 0xff);
    TIMER2_RUN();
    TIMER2_FREQ_DISABLE();          // @24MHz
}


void Timer1_Init(uint16_t count) {
    wc_assert(IS_TIMER_COUNT(count));

    TIMER1_TL(count &0xff);
    TIMER1_TH((count >> 8) & 0xff);
    TIMER1_RUN();
    TIMER1_FREQ_DISABLE();          // @24MHz
}

void Timer0_Init(uint16_t count) {
    wc_assert(IS_TIMER_COUNT(count));
	
	TIMER0_MODE(TIMER_Mode_0);
    TIMER0_TL(count &0xff);
    TIMER0_TH((count >> 8) & 0xff);
    TIMER0_RUN();
    TIMER0_FREQ_DISABLE();
    TIMER0_ENABLE();
}

