#include "key.h"
#include "timer.h"
#include "led.h"



static void Delay_ms(uint16_t Del_1ms) {
	uint8_t j;
    
	while (Del_1ms--) {	
		for (j  =0;j < 123;j++) {
        
        }
	}
}
uint8_t old_key = 0xff;
uint8_t KEY_Scan(void) {
    
    if ((KEY_VALUE & 0x0f) != 0x0f) {       // 键盘按下
        if (old_key != KEY_VALUE) {         // 不是上一个键
            Delay_ms(20);
            if (KEY_VALUE != 0x0f) {
                old_key = KEY_VALUE;
                return KEY_VALUE;
            }
        }
    } else {
        old_key = KEY_VALUE;
    }
    return 0;
}



// 按键 1 执行函数
void KeyFunc1(BOTP * b) {
	FreqAdd(b, 1);
}
// 按键 2 执行函数
void KeyFunc2(BOTP * b) {
	FreqDec(b, 1);
}

// 按键 3 执行函数
void KeyFunc3(BOTP * b) {
	ColorChange(b, 1);
}

// 按键 4 执行函数
void KeyFunc4(BOTP * b) {
	StatusFreq = 100 - StatusFreq;
}

/*
 * 开机自检测部分函数
 */

//Menu menu = {1, 0};

//// 向下移动
//uint8_t MenuFunc1(void) {	
//uint8_t index = 1;	
//	switch (menu.value & 0xf0) {
//		case BOOT_MENU:
//			menu.value += ((menu.value & 0x0f) < 2  ? 1 : 0);
//		break;
//		
//		case BOOT_MENU_FREQ_SET:	// 自检
//			menu.value += ((menu.value & 0x0f) < 2 ? 1 : 0);
//		break;
//	}
//	
//	return 0x00;
//}

//// 向上移动
//uint8_t MenuFunc2(void) {
//	switch (menu.value & 0xf0) {
//		case BOOT_MENU:
//			menu.value -= ((menu.value & 0x0f) > 1 ? 1 : 0);
//		break;
//		
//		case BOOT_MENU_FREQ_SET:	// 自检
//			menu.value -= ((menu.value & 0x0f) > 1 ? 1 : 0);
//		break;
//	}
//	
//	return 0x00;
//}

//extern void BootSelfCheck(void);

//// 进入
//uint8_t MenuFunc3(void) {
//	switch (menu.value) {
//		menu.value = ((menu.value & 0x0f) << 4) | 0x01;
//		case BOOT_MENU_SELF_CHECK:
//			BootSelfCheck();
//		break;
//		
//		case BOOT_MENU_FREQ_SET:
//            
//		break;
//	}
//	
//	return 0x00;
//}

///*
// * 	退出		 返回1
// *  返回上层菜单 返回0
// */
//uint8_t MenuFunc4(void) {
//	if (0x00 == (menu.value & 0xf0)) { // 最上层菜单
//		return 0x01;
//	}
//	
//	menu.value = ((menu.value & 0xf0) >> 4) & 0x0f;
//	
//	return 0x00;
//}



