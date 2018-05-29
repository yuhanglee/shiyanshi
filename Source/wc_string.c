#include "wc_string.h"
#include "mylib.h"
#include "uart.h"


typedef char * va_list;
va_list ap;		// 定义一个指针类型
#define _INTSIZEOF(n)		((sizeof(n) + sizeof(int) - 1) & ~ (sizeof(int) - 1))  // 计算各种数据类型按4字节（int占4字节）对齐后的结果
#define va_start(ap, v)		(ap = (va_list)(&v) + _INTSIZEOF(v))				// ap指向变参列表的首地址指针；
#define va_args(ap, t)		(*(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t))) // 更新变量ap指向列表中的下一个参数，然后通过偏移取出变量ap所指向的上一个参数地址（为偏移前的参数）
#define va_end(ap)			(ap = (va_list)0) // ap指向空

uint8_t str_len(const int8_t * str) {
    uint8_t len = 0;
    
    wc_assert(0 != str);
    for (len = 0;*str;len++, str++);
    
    return len;
}

int8_t str_cmp(const int8_t * str1, const int8_t * str2) {
    uint8_t len1 = str_len(str1);
    uint8_t len2 = str_len(str2);
    uint8_t i;
    
    wc_assert(0 != str1);
    wc_assert(0 != str2);
    
    if (len1 > len2) {
        return 1;
    } else if (len1 < len2) {
        return -1;
    } else {
        for (i = 0;i < len1;++i) {
            if (str1[i] > str2[i]) {
                return 1;
            } else if (str1[i] < str2[i]) {
                return -1;
            }
        }
    }
    
    return 0;
}



