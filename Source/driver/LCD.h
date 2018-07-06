/******************************************************************************

                  版权所有 (C), 2018-2028, 李玉航

 ******************************************************************************
  文 件 名   : LCD.h
  版 本 号   : V0.1
  作    者   : 李玉航
  生成日期   : 2018年6月22日
  最近修改   :
  功能描述   : LCD.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年6月22日
    作    者   : 李玉航
    修改内容   : 创建文件

******************************************************************************/
	
	
#ifndef __LCD_H__
#define __LCD_H__
	

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/
	
#include "mylib.h"
	

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

extern char 		UartLcdCmdStr[];
extern uint16_t 	UartLcdCmdStrIndex;

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

#define LCD_COLOR_DISP_1		0
#define LCD_COLOR_DISP_2		1
#define LCD_COLOR_DISP_3		2
#define LCD_COLOR_CUR			3
#define LCD_COLOR_HZ_I			4
#define LCD_COLOR_HZ_F			5
#define LCD_COLOR_NEXT			6


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
typedef struct {
	uint8_t x1;
	uint8_t y1;
	uint8_t x2;
	uint8_t y2;
	uint8_t c;
	uint8_t bc;
	uint8_t flag;
} coor;




extern coor *	CurCoor;
extern uint16_t	CurCoorIndex;
extern uint16_t	NextCoorIndex;



extern uint16_t LCD_Choose(char * cmd, coor cur, coor next, uint16_t Index);
extern uint16_t LCD_ChooseDown(char * cmd, uint16_t Index);
extern uint16_t LCD_ChooseLeft(char * cmd, uint16_t Index);
extern uint16_t LCD_ChooseUp(char * cmd, uint16_t Index);
extern uint16_t LCD_ChooseRight(char * cmd, uint16_t Index);
extern uint16_t LCD_ChooseOK(char * cmd, uint16_t Index);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LCD_H__ */
