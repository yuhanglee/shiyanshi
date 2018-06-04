#ifndef __WCOS_TASK_H__
#define __WCOS_TASK_H__

#include "wcos_typedef.h"

#define TASK_STATUS_ACTIVE				((1) << (0))
#define TASK_STATUS_READ_BUF_READY		((1) << (1))
#define TASK_STATUS_WRITE_BUF_READY		((1) << (2))




typedef struct TaskTCB {
	void 				* Func;				// 任务入口函数指针
	void				* FuncArgc; 		// 保存数据，指针类型，需强制转换
	void 				* ReadBuf;			// 读取缓冲区指针
	void				* WriteBuf;			// 写入缓冲区指针
	volatile uint32_t	RunStatus;			// 运行状态机，由任务进行控制
 	volatile uint16_t	ReadBufIndex;		// 读取缓冲区当前下标
	volatile uint16_t 	WriteBufIndex;		// 写入缓冲区当前下标
	volatile uint8_t 	TaskStatus;			// 任务状态
} WCOS_TASK_CB;

extern WCOS_TASK_CB TCB[];

typedef struct Task {
	WCOS_TASK_CB		* RunTask;			// 当前运行任务
	WCOS_TASK_CB		* NextTask;			// 下一个任务
} WCOS_TASK;



#endif
