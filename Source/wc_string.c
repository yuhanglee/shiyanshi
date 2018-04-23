#include "wc_string"


uint8_t str_len(const int8_t * str) {
    uint8_t len = 0;
    
    for (len = 0;*str;len++);
    
    return len;
}

int8_t str_cmp(const int8_t * str1, const int8_t * str2) {
    uint8_t len1 = str_len(str1);
    uint8_t len2 = str_len(str2);
    uint8_t i;
    
    
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
