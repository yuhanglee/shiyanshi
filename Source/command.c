#include "command.h"
#include "mylib.h"
#include "wc_string.h"

#define CMDSTR_SIZE     3

static const char CMDSTR[CMDSTR_SIZE][10] = {
    "LCD OFF",
    "LCD ON",
    "PING",
}; 

cmd cmd_ckeck(char * cmd_str) {
    int8_t i;
    
    wc_assert(cmd_str == 0);
    
    for (i = 0;i < CMDSTR_SIZE;++i) {
        if (str_cmp(CMDSTR[i], cmd_str)) {
            return (cmd)(i + LCD_OFF);
        }
    }
    
    return (cmd)(LCD_OFF - 1);
}

