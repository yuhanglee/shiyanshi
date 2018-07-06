#ifndef __TIMER_H__
#define __TIMER_H__

#include "mylib.h"

#define CALC_COUNT(t, n)				(t)?(0x10000 - FOSC / 1000000 * n):(0x10000 - FOSC / 120000000 * n)

typedef enum {
	TIMER_Mode_0 = 0,
	TIMER_Mode_1 = 1,
	TIMER_Mode_2 = 2,
	TIMER_Mode_3 = 3,
} TimerMode;	

#define IS_TIMER_MODE(mode)				(\
											TIMER_Mode_0 == (mode) || \
											TIMER_Mode_1 == (mode) || \
											TIMER_Mode_2 == (mode) || \
											TIMER_Mode_3 == (mode)    \
										)

typedef enum {
	TIMER_TYPE_TIMER = 0,
	TIMER_TYPE_COUNT = 1,
} TimerType;							
#define IS_TIMER_TYPE(type)				(\
											TIMER_TYPE_TIMER == (type) || \
											TIMER_TYPE_COUNT == (type)    \
										)

typedef enum {
	TIMER_FREQ_DIV_12 = 0,
	TIMER_FREQ_DIV_1 = 1,
} TimerFreqDiv;					

#define IS_TIMER_FREQ_DIV(div)			(\
											TIMER_FREQ_DIV_1  == (div) || \
											TIMER_FREQ_DIV_12 == (div)    \
										)						
	
#define IS_TIMER_COUNT(count)			(\
											0     <= (count) || \
											65535 >= (count)    \
										)
typedef struct {
    TimerType  Type;
    TimerMode  Mode;
    uint8_t  FreqDiv;
    uint16_t Count;
} Timer;


#define e_TimTest		0
#define e_TimMax		1



extern uint16_t TimerDelayArray[];


#define IS_TIME_OUT_1MS(i, c)	( \
									!(TimerDelayArray[(i)] & 0x8000) ? \
									TimerDelayArray[(i)] = (c) | 0x8000 : \
										!(TimerDelayArray[(i)] << 1) ? \
										((TimerDelayArray[(i)] = 0) == 0) : \
										0 \
								)


void Timer0_Init(uint16_t count);
void Timer1_Init(uint16_t count);
void Timer2_Init(uint16_t count);
void Timer3_Init(uint16_t count);

#endif
