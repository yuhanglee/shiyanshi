#ifndef __KEY_H__
#define __KEY_H__
#include "mylib.h"
#include "botp.h"

#define KEY_ERROR		0x00

#define KEY_UP			0x08
#define KEY_DOWN		0x01
#define KEY_LIFT		0x41
#define KEY_RIGHT 		0x04
#define KEY_OK			0x02


void KEY_Init(void);
uint8_t KEY_Scan(void);

#endif
