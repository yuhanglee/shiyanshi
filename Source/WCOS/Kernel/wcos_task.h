#ifndef __WCOS_TASK_H__
#define __WCOS_TASK_H__

#include "wcos_typedef.h"


#define TASK_STACK_START_ADDR			0x30
#define TASK_STACK_SIZE					20
#define TASK_MAX						3

#if (((TASK_STACK_SIZE * TASK_MAX) + TASK_STACK_START_ADDR) >= 0xf8)
	#error "tThe end address of the stack cannot exceed 0xf8"
#endif

#if !(TASK_STACK_SIZE > 15)
	#error "The task stack must be larger than 15 bytes"
#endif

#if !(TASK_MAX > 1)
	#error "Too few tasks can be created"
#endif

#define TASK_STATUS_CLEAR				((0x0) << (0))
#define TASK_STATUS_ACTIVE				((0x0) << (0))
#define TASK_STATUS_READY				((0x1) << (0))
#define TASK_STATUS_WATI				((0X2) << (0))





typedef struct TaskTCB {
	void 				* Func;				// 任务入口函数指针
	void				* FuncArgc; 		// 保存数据，指针类型，需强制转换
	volatile uint8_t	RunStatus;			// 运行状态机，由任务进行控制
 	volatile uint8_t 	TopStk;
	volatile uint16_t	DelayMs;
} WCOS_TASK_CB;


void TaskDelay(uint16_t ms);
void TaskCreate(uint16_t TaskFunc, uint8_t	  pri);
void TaskInit(void);
void TaskStart(void);



#endif
