#include "key.h"
#include "timer.h"
#include "delay.h"


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


