#include "led.h"
#include "wc_string.h"
#include "string.h"
#include "mylib.h"
#include "timer.h"

uint32_t StatusFreq = 0x01;			// LED 的起始闪烁频率

void FreqAdd(BOTP * pb, uint8_t num) {
    uint8_t *bc = (uint8_t *)pb;
    uint32_t * freq = ((uint32_t *)(&(bc[32])));
    
    if (0xff == bc[29]) {
        *freq += (((uint32_t)num & 0x3ff) << 20);
        // 赫兹数 最大是100
        if ((((*freq) >> 20) & 0x3ff) > 100) {
            *freq &= ~(0x3ff << 20);
            *freq |= (100 << 20);
        }
    } else if (0xff == bc[30]) {
        *freq += ((uint32_t)num & 0x3ff) << 10;
        // 赫兹数 最大是100
        if ((((*freq) >> 10) & 0x3ff) > 100) {
            *freq &= ~(0x3ff << 10);
            *freq |= (100 << 10);
        }
    } else if (0xff == bc[31]) {
        *freq += ((uint32_t)num & 0x3ff) << 0;
        
        // 赫兹数 最大是100
        if ((((*freq) >> 0) & 0x3ff) > 100) {
            *freq &= ~(0x3ff << 0);
            *freq |= (100 << 0);
        }
    }
}

void FreqDec(BOTP * pb, uint8_t num) {
    uint8_t *bc = (uint8_t *)pb;
    uint32_t * freq = ((uint32_t *)(&(bc[32])));
    
    if (0xff == bc[29]) {
        // 赫兹数 最小是0
        if ((((*freq) >> 20) & 0x3ff) > (uint32_t)num) {
            *freq -= ((uint32_t)num & 0x3ff) << 20;
        } else {
            *freq &= ~(0x3ff << 20);
        }
        
    } else if (0xff == bc[30]) {
        // 赫兹数 最小是0
        if ((((*freq) >> 10) & 0x3ff) > (uint32_t)num) {
            *freq -= ((uint32_t)num & 0x3ff) << 10;
        } else {
            *freq &= ~(0x3ff << 10);
        }
    } else if (0xff == bc[31]) {
        // 赫兹数 最小是0
        if ((((*freq) >> 0) & 0x3ff) > (uint32_t)num) {
            *freq -= ((uint32_t)num & 0x3ff) << 0;
        } else {
            *freq &= ~(0x3ff << 0);
        }
    }
}

void ColorChange(BOTP * pb, uint8_t num) {
    uint8_t *bc = (uint8_t *)pb;
    uint8_t index = 29;
    uint32_t * freq = ((uint32_t *)(&(bc[32])));
    
    
    *freq &= 0xC0000000;
    if (0xff == bc[index]) {
        bc[index] = 0x00;
        bc[index-1] = 0x01;
    }
    index++;
    
    if (0xff == bc[index]) {
        bc[index] = 0x00;
        bc[index-1] = 0xff;
        *freq |= (StatusFreq << 20);
    }
    index++;
    
    
    if (0xff == bc[index]) {
        bc[index] = 0x00;
        bc[index-1] = 0xff;
        *freq |= (StatusFreq << 10);
    }
    index++;
    
    // 切换记录
    bc[32] += 0x40;
}

