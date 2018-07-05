#include "WCOS_task.h"



uint8_t state = TASK_MAX;
uint8_t SchFlag = 0x00;

data uint8_t TaskStk[TASK_MAX + 1][TASK_STACK_SIZE] _at_ TASK_STACK_START_ADDR;	// 任务0的堆栈区

							
xdata WCOS_TASK_CB TaskTcb[TASK_MAX + 1] = {0};

void TaskSave(uint8_t s) {
	assert(s < TASK_MAX);
	TaskTcb[state].TopStk = s;
}

uint8_t TaskRelease(void) {
	return TaskTcb[state].TopStk;
}


void TaskDelayMsDec(void) {
	uint8_t i;
	
	for (i = 0;i < TASK_MAX;i++) {
		if (TaskTcb[i].DelayMs > 0) {
			TaskTcb[i].DelayMs--;
			if (TaskTcb[i].DelayMs == 0) {			
				TaskTcb[i].RunStatus &= TASK_STATUS_CLEAR;
				TaskTcb[i].RunStatus |= TASK_STATUS_READY;
			}
		}
	}
}

uint8_t TaskRun(void) {
	uint8_t i;

	for (i = 0;i < TASK_MAX;i++) {
		if (TaskTcb[i].RunStatus & TASK_STATUS_READY) {
			TaskTcb[i].RunStatus &= TASK_STATUS_CLEAR;
			TaskTcb[i].RunStatus |= TASK_STATUS_ACTIVE;
			return i;
		}
	}
	return TASK_MAX;
}

void TaskReady(uint8_t s) {
	assert(s < TASK_MAX);
	TaskTcb[s].RunStatus &= TASK_STATUS_CLEAR;
	TaskTcb[s].RunStatus |= TASK_STATUS_READY;
}


void TaskDelay(uint16_t ms) {
	EA = 0;

	TaskTcb[state].DelayMs = ms;
	TaskTcb[state].RunStatus &= TASK_STATUS_CLEAR;
	TaskTcb[state].RunStatus |= TASK_STATUS_WATI;	

	SchFlag = TRUE;
	TF0 = 1;
	
	EA = 1;
}


void TaskCreate(uint16_t 		TaskFunc,
   				   uint8_t	  	pri) {

	assert(TaskFunc 	!= NULL);
	assert(TaskStack 	!= NULL);
	assert(pri			<  TASK_MAX);

	TaskTcb[pri].DelayMs 	= 0;
	TaskTcb[pri].RunStatus	= TASK_STATUS_READY;
	TaskStk[pri][1]			= ((uint16_t)TaskFunc) & 0xff;
	TaskStk[pri][2]			= ((uint16_t)TaskFunc >> 8) & 0xff;
	TaskTcb[pri].TopStk		= (uint8_t)(TaskStk[pri]) + 15;
}


void TaskIdle(void) {
	while (1) {
		// idle 
	}
}

void TaskInit(void) {
	TaskTcb[TASK_MAX].DelayMs 	= 0;
	TaskTcb[TASK_MAX].RunStatus	= TASK_STATUS_READY;
	TaskStk[TASK_MAX][1]			= ((uint16_t)TaskIdle) & 0xff;
	TaskStk[TASK_MAX][2]			= ((uint16_t)TaskIdle >> 8) & 0xff;
	TaskTcb[TASK_MAX].TopStk		= (uint8_t)(TaskStk[TASK_MAX]) + 2;
}

void TaskStart(void) {
	SP = TaskTcb[TASK_MAX].TopStk;
}
