/******************************************************************************

                  版权所有 (C), 2018-2028, 李玉航

 ******************************************************************************
  文 件 名   : UartLcd.h
  版 本 号   : V0.1
  作    者   : 李玉航
  生成日期   : 2018年6月22日
  最近修改   :
  功能描述   : UartLcd.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年6月22日
    作    者   : 李玉航
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/

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

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

#ifndef __UARTLCD_H__
#define __UARTLCD_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "stc8.h"
#include "mylib.h"


typedef enum ALIGN
{
    ALIGN_LIFT 		= 0,
	ALIGN_CENTER	= 1,
	ALIGN_RIGHT		= 2,
}ALIGN_ENUM;

typedef enum FONT_SIZE
{
    FONT_SIZE_12	= 12,
    FONT_SIZE_16	= 16,
    FONT_SIZE_24	= 24,
    FONT_SIZE_32	= 32,
    FONT_SIZE_48	= 48,
    FONT_SIZE_64	= 64,       
}FONT_SIZE_ENUM;

typedef enum FONT_LW
{
    FONT_LW_12		= 4,
	FONT_LW_16		= 4,
	FONT_LW_24		= 6,
}FONT_LW_ENUM;

extern uint16_t BOX(char * cmd, 
         			  uint16_t x1,
         			  uint16_t y1,
         			  uint16_t x2,
         			  uint16_t y2,
         			  uint16_t c,
         			  uint16_t len);
extern uint16_t BOXF(char * cmd, 
         			    uint16_t x1,
         			    uint16_t y1,
         			    uint16_t x2,
         			    uint16_t y2,
         			    uint16_t c,
         			    uint16_t len);
extern uint16_t BPIC(char *		cmd,
         				uint16_t	m,
         				uint16_t	x1,
         				uint16_t	y1,
         				uint16_t	pn,
         				uint16_t	ishide,
         				uint16_t	len);
extern uint16_t BSn(char *				cmd,
         			   FONT_SIZE_ENUM	m,
         			   uint16_t			x1,
         			   uint16_t			y1,
         			   uint16_t			x2,
         			   FONT_LW_ENUM		lw,
         			   char *			str,
         			   uint16_t			c,
         			   uint16_t			len);
extern uint16_t CBOF(char * cmd,
         				 uint16_t x1,
         				 uint16_t y1,
         				 uint16_t x2,
         				 uint16_t y2,
         				 uint16_t r,
         				 uint16_t c,
         				 uint16_t len);
extern uint16_t CBOX(char * cmd,
         			    uint16_t x1, 
         			    uint16_t y1,
         			    uint16_t x2, 
         			    uint16_t y2,
         			    uint16_t r,
         			    uint16_t c,
         			    uint16_t len);
extern uint16_t CIR(char * cmd, 
         			  uint16_t x, 
         			  uint16_t y,
         			  uint16_t r,
         			  uint16_t c,
         			  uint16_t len);
extern uint16_t CIRF(char * cmd, 
         			   uint16_t x, 
            			   uint16_t y,
         			   uint16_t r,
         			   uint16_t c,
         			   uint16_t len);
extern uint16_t CLS(char * cmd, 
         			  uint16_t c,
         			  uint16_t len);
extern uint16_t CPIC(char *		cmd,
         				uint16_t	x1,
         				uint16_t	y1,
         				uint16_t	pn,
         				uint16_t	px1,
         				uint16_t	py1,
         				uint16_t	w,
         				uint16_t	h,
         				uint16_t	len);
extern uint16_t DBOX(char *			cmd,
         				uint16_t		x1,
         				uint16_t		y1,
         				uint16_t		x2,
         				uint16_t		y2,
         				uint16_t		w,
         				uint16_t		c,
         				uint16_t		len);
extern uint16_t DSn(char *			cmd,
          			  FONT_SIZE_ENUM m, 
         			  uint16_t 		x1,
         		  	  uint16_t 		y1,
         			  char *   		str,
         			  uint16_t 		c,
         			  uint16_t		limitX,
         			  uint16_t		len);
extern uint16_t ICON(char *		cmd,
         				uint16_t	x1,
         				uint16_t	y1,
         				uint16_t	pn,
         				uint16_t	xn,
         				uint16_t	yn,
         				uint16_t	n,
         				uint16_t	len);
extern uint16_t INF(char *				cmd,
         			  uint16_t			len);
extern uint16_t LABL(char *			cmd,
          				FONT_SIZE_ENUM 	m, 
         			    uint16_t 		x1, 
         			    uint16_t 		y1,
         			    uint16_t 		x2,
         			    char *   		str,
         			    uint16_t  		c,
         			    uint16_t		limitX,
         			    uint16_t		len);
extern uint16_t MENU(char *			cmd,
         				uint16_t		x,
         				uint16_t		y,
         				uint16_t		w,
         				uint16_t		h,
         				uint16_t		pw,
         				uint16_t		x1,
         				uint16_t		x2,
         				FONT_SIZE_ENUM	hzm,
         				uint16_t		max,
         				uint16_t		pg,
         				uint16_t		len);
extern uint16_t MSET(char *  			cmd, 
         				uint16_t		n,
         				uint16_t		len);
extern uint16_t MSHW(char *			cmd,
         				uint16_t		len);
extern uint16_t PBOX(char *			cmd,
         				uint16_t		pn,
         				uint16_t		x1,
         				uint16_t		y1,
         				uint16_t		x2,
         				uint16_t		y2,
         				uint16_t		w,
         				uint16_t		len);
extern uint16_t PIC(char *			cmd,
         			  uint16_t 		x1, 
         			  uint16_t		y1,
         			  uint16_t		pn,
         			  uint16_t		len);
extern uint16_t PL(char * cmd, 
         			 uint16_t x1,
         			 uint16_t y1,
         			 uint16_t x2,
         			 uint16_t y2, 
         			 uint16_t c,
         			 uint16_t len);
extern uint16_t PLAB(char *			cmd,
         				FONT_SIZE_ENUM	m,
         				uint16_t		x1,
         				uint16_t		y1,
         				uint16_t		x2,
         				char *			str,
         				uint16_t		c,
         				ALIGN_ENUM		ali,
         				uint16_t		pn,
         				uint16_t		len);
#if 0
extern uint16_t PS(char * cmd, 
         			 uint16_t x,
         			 uint16_t y,
         			 uint16_t c,
         			 uint16_t len);
#endif
extern uint16_t PSn(char *				cmd,
         			  FONT_SIZE_ENUM	m,
         			  uint16_t			pn,
         			  uint16_t			x1,
         			  uint16_t			y1,
         			  char *			str,
         			  uint16_t			c,
         			  uint16_t			limitX,
         			  uint16_t			len);
extern uint16_t SBC(char * 		cmd,
         			  uint16_t		c,
         			  uint16_t		len);
extern uint16_t SCC(char * 		cmd,
         			  uint16_t		cn,
         			  uint16_t		color,
         			  uint16_t		len);
extern uint16_t SNF(char *				cmd,
         			  uint16_t			x,
         			  uint16_t			y,
         			  uint16_t			len);
extern uint16_t SPG(char *				cmd,
         			   uint16_t			n,
         			   uint16_t			len);
extern uint16_t TERM(char *			cmd,
         				uint16_t		len);
extern void UartLcdInit(void);
extern void UartLcdSendChar(uint8_t ch);
extern void UartLcdSendStr(uint8_t * str);
extern uint16_t W8SE(char *			cmd,
         				uint16_t		n,
         				uint16_t		len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __UARTLCD_H__ */
