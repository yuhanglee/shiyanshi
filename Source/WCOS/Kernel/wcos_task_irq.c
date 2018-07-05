#include "stc8.h"
#include "mylib.h"


unsigned char t0Count;

extern unsigned char state;
extern unsigned char TopStk[];
extern uint8_t SchFlag;

extern unsigned char 	TaskRun(void);
extern void 			TaskDelayMsDec(void);
extern void 			TaskSave(unsigned char s);
extern unsigned char 	TaskRelease(void);
extern void 			TaskReady(uint8_t s);

void TIM0_IRQ(void)    interrupt 1 using 0 {
	EA = 0;
#pragma asm
	PUSH AR7
	PUSH AR6
	PUSH AR5
	PUSH AR4
	PUSH AR3
	PUSH AR2
	PUSH AR1
	PUSH AR0
#pragma endasm
	TaskSave(SP);

	if (!SchFlag) {
		t0Count++;
	}
	TaskDelayMsDec();
	if ((SchFlag) || // 系统延时，进行任务切换 
		(t0Count >> 3)) { // 8ms 时间片用完
		if (!SchFlag) { // 如果非任务延时进行任务切换
			TaskReady(state); // 置当前状态为ready
		}
		SchFlag = FALSE;
		t0Count &= 0x07; 	// 取最低3位
		state = TaskRun();
	}


	
	SP = TaskRelease();
#pragma asm
	POP AR0
	POP AR1
	POP AR2
	POP AR3
	POP AR4
	POP AR5
	POP AR6
	POP AR7
#pragma endasm
	EA = 1;
}

