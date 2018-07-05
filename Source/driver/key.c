#include "key.h"
#include "mylib.h"
#include "wcos_task.h"

uint8_t old_key = 0x00;

void KEY_Init(void) {
	P6 &= 0x0f;
	P4 &= 0xfe;
}



uint8_t KEY_Scan(void) {
	if (old_key != ((P6 & 0xf0) | (P4 & 0x01))) {
	    if ((P6 >> 4) || (P4 & 0x01)) { // 高四位有高电平
			TaskDelay(20); // 消抖
			if ((P6 >> 4) ||  (P4 & 0x01)) {
				old_key = ((P6 & 0xf0) | (P4 & 0x01));
				if (P4 & 0x01) {
					return 0x41; // 0x41 只是代表一个按键号
	 			} else {
					return (P6 >> 4);
				}
			}
		} else {
			old_key = 0x00;
		}
	}
	
	return KEY_ERROR;
}




