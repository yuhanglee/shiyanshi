#ifndef __KEY_H__
#define __KEY_H__
#include "mylib.h"
#include "botp.h"

#define KEY_VALUE   P2

#define KEY_1       0xF7
#define KEY_2       0xFB
#define KEY_3       0xFD
#define KEY_4       0xFE

#define BOOT_MENU						0x00

#define BOOT_MENU_SELF_CHECK			0x01
#define BOOT_MENU_FREQ_SET				0x02

#define BOOT_MENU_FREQ_SET_LOW			0x21
#define BOOT_MENU_FREQ_SET_HIGH			0x22


typedef struct {
	uint8_t value;
	uint8_t index;
} Menu;
extern Menu menu;

uint8_t KEY_Scan(void);
void KeyFunc1(BOTP * b);
void KeyFunc2(BOTP * b);
void KeyFunc3(BOTP * b);
void KeyFunc4(BOTP * b);

uint8_t MenuFunc1(void);
uint8_t MenuFunc2(void);
uint8_t MenuFunc3(void);
uint8_t MenuFunc4(void);
#endif
