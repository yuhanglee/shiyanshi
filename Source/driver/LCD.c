#include "LCD.h"
#include "UartLcd.h"
#include "delay.h"
#include "mylib.h"


coor		CoorArray[] = {
	{65, 10, 100, 45, 0, 15},
	{115,10, 150, 45, 0, 15},
	{165,10, 200, 45, 0, 15},
	{65, 60, 130, 125,0, 15},
	{5,  129,35,  164,0, 15},
	{45, 129,75,  164,0, 15},
	{156,112,212, 168,0, 15},

};


coor *		CurCoor;
uint16_t	CurCoorIndex = 0;
uint16_t	NextCoorIndex = 0;
float		FreqHz = 0.0;

char  		UartLcdCmdStr[512];
uint16_t	UartLcdCmdStrIndex = 0;


/*****************************************************************************
 函 数 名  : LCD_Choose
 功能描述  : 更改选中位置
 输入参数  : char * cmd      
             coor cur        当前选中位置
             coor next       下一个选中位置
             uint16_t Index  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_Choose(char * cmd, coor cur, coor next, uint16_t Index) {
	Index = DBOX(cmd, 
				 cur.x1,
				 cur.y1,
				 cur.x2,
				 cur.y2,
				 2,
				 cur.bc,
				 Index);
	Index = DBOX(cmd, 
			  	 next.x1,
			  	 next.y1,
			  	 next.x2,
			  	 next.y2,
			  	 2,
			  	 next.c,
			  	 Index);

	CurCoor = CoorArray + NextCoorIndex;

	return Index;
}
/*****************************************************************************
 函 数 名  : LCD_ChooseRight
 功能描述  : 选中区域向右移动一个
 输入参数  : char * cmd      
             uint16_t Index  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_ChooseRight(char * cmd, uint16_t Index) {
	switch (CurCoorIndex) {
		case LCD_COLOR_DISP_1:
			NextCoorIndex = LCD_COLOR_DISP_2;
		break;

		case LCD_COLOR_DISP_2:
			NextCoorIndex = LCD_COLOR_DISP_3;
		break;

		case LCD_COLOR_HZ_I:
			NextCoorIndex = LCD_COLOR_HZ_F;
		break;
		
		case LCD_COLOR_HZ_F:
			NextCoorIndex = LCD_COLOR_NEXT;
		break;


		default:
			return Index;
	}

	// 切换选中区域
	Index = LCD_Choose(cmd, CoorArray[CurCoorIndex], CoorArray[NextCoorIndex], Index);
	// 更改当前索引值
	CurCoorIndex = NextCoorIndex;
	
	return Index;
}
/*****************************************************************************
 函 数 名  : LCD_ChooseLeft
 功能描述  : 选中区域向左移动一个
 输入参数  : char * cmd      
             uint16_t Index  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_ChooseLeft(char * cmd, uint16_t Index) {
	switch (CurCoorIndex) {
		case LCD_COLOR_DISP_2:
			NextCoorIndex = LCD_COLOR_DISP_1;
		break;

		case LCD_COLOR_DISP_3:
			NextCoorIndex = LCD_COLOR_DISP_2;
		break;

		case LCD_COLOR_NEXT:
			NextCoorIndex = LCD_COLOR_HZ_F;
		break;
		
		case LCD_COLOR_HZ_F:
			NextCoorIndex = LCD_COLOR_HZ_I;
		break;
		

		default:
			return Index;
	}

	// 切换选中区域
	Index = LCD_Choose(cmd, CoorArray[CurCoorIndex], CoorArray[NextCoorIndex], Index);
	// 更改当前索引值
	CurCoorIndex = NextCoorIndex;
	
	return Index;
}
/*****************************************************************************
 函 数 名  : LCD_ChooseUp
 功能描述  : 选中区域向上移动一个
 输入参数  : char * cmd      
             uint16_t Index  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_ChooseUp(char * cmd, uint16_t Index) {
	switch (CurCoorIndex) {
		case LCD_COLOR_CUR:
			NextCoorIndex = LCD_COLOR_DISP_1;
		break;

		case LCD_COLOR_NEXT:
			NextCoorIndex = LCD_COLOR_CUR;
		break;

		case LCD_COLOR_HZ_I:
			if (FreqHz < 100) {
				FreqHz = FreqHz + 1;
			}
			printf("freq:%05.1f\r\n", FreqHz);
		break;

		case LCD_COLOR_HZ_F:
			if (!FLOAT_EQ(FreqHz, 100)) {
				FreqHz = FreqHz + 0.1;
			}
			printf("freq:%05.1f\r\n", FreqHz);
		break;
		
		default:
			return Index;
	}

	// 切换选中区域
	Index = LCD_Choose(cmd, CoorArray[CurCoorIndex], CoorArray[NextCoorIndex], Index);
	// 更改当前索引值
	CurCoorIndex = NextCoorIndex;
	
	return Index;
}

/*****************************************************************************
 函 数 名  : LCD_ChooseDown
 功能描述  : 选中区域向下移动一个
 输入参数  : char * cmd      
             uint16_t Index  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_ChooseDown(char * cmd, uint16_t Index) {
	switch (CurCoorIndex) {
		case LCD_COLOR_DISP_1:
		case LCD_COLOR_DISP_2:
		case LCD_COLOR_DISP_3:
			NextCoorIndex = LCD_COLOR_CUR;
		break;

		case LCD_COLOR_CUR:
			NextCoorIndex = LCD_COLOR_HZ_I;
		break;

		case LCD_COLOR_HZ_I:
			if (FreqHz > 0) {
				FreqHz = FreqHz - 1;
			}
			printf("freq:%05.1f\r\n", FreqHz);
		break;

		case LCD_COLOR_HZ_F:
			if (!FLOAT_EQ(FreqHz, 0)) {
				FreqHz = FreqHz - 0.1;
			}
			printf("freq:%03d.%1d\r\n", (int)(FreqHz), ((int)(FreqHz * 10)) % 10);
		break;

		default:
			return Index;
	}

	// 切换选中区域
	Index = LCD_Choose(cmd, CoorArray[CurCoorIndex], CoorArray[NextCoorIndex], Index);
	// 更改当前索引值
	CurCoorIndex = NextCoorIndex;
	
	return Index;
}

uint16_t ass[5] = {
	0x0000, 0xffff, 0xf800, 0x07e0, 0x001f,
};

/*****************************************************************************
 函 数 名  :LCD_ChooseOK 
 功能描述  : ok按键功能
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年6月25日
    作    者   : 李玉航
    修改内容   : 新生成函数

*****************************************************************************/
uint16_t LCD_ChooseOK(char * cmd, uint16_t Index) {
	static int a = 0;
	static uint8_t flag = 0;
	static uint8_t colorDispNum = 0;
	if (flag == 0) {
		flag = 1;
		
		Index = SPG(cmd,
					2,
					Index);
		Delay_ms(20);
		CurCoorIndex = 0;
		
	}
	switch (CurCoorIndex) {
		case LCD_COLOR_NEXT:
			Index = BOXF(cmd,
						CoorArray[colorDispNum + LCD_COLOR_DISP_1].x1,
						CoorArray[colorDispNum + LCD_COLOR_DISP_1].y1,
						CoorArray[colorDispNum + LCD_COLOR_DISP_1].x2,
						CoorArray[colorDispNum + LCD_COLOR_DISP_1].y2,
						63,
						Index);
			// 颜色块索引值增加
			colorDispNum<2 ? colorDispNum++ : 0;
			// 颜色块索引值增加到最后
			if (colorDispNum == 2) {
				
			}
		break;

		case LCD_COLOR_CUR:
			Index = SCC(cmd, 
						63, 
						ass[a++],
						Index);
			if (a == 5)
				a = 0;
			
			Index = BOXF(cmd, 
						CoorArray[LCD_COLOR_CUR].x1,
						CoorArray[LCD_COLOR_CUR].y1,
						CoorArray[LCD_COLOR_CUR].x2,
						CoorArray[LCD_COLOR_CUR].y2,
						63,
						Index);
			Index - DBOX(cmd,
						CoorArray[LCD_COLOR_CUR].x1,
						CoorArray[LCD_COLOR_CUR].y1,
						CoorArray[LCD_COLOR_CUR].x2,
						CoorArray[LCD_COLOR_CUR].y2,
						2,
						0,
						Index);
		break;
	}
	return Index;
}



