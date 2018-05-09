#ifndef __OLED_H__
#define __OLED_H__

#include "mylib.h"

#define OLED_X_MAX      16
#define OLED_Y_MAX      4

#define ASCII_SIZE_X    8
#define ASCII_SIZE_Y    16




#define OLED_CMD_SCROLL_PAGE_0          0X00    // page0   
#define OLED_CMD_SCROLL_PAGE_1          0X01    // page1   
#define OLED_CMD_SCROLL_PAGE_2          0X02    // page2   
#define OLED_CMD_SCROLL_PAGE_3          0X03    // page3   
#define OLED_CMD_SCROLL_PAGE_4          0X04    // page4   
#define OLED_CMD_SCROLL_PAGE_5          0X05    // page5   
#define OLED_CMD_SCROLL_PAGE_6          0X06    // page6   
#define OLED_CMD_SCROLL_PAGE_7          0X07    // page7

#define IS_PAGE(page)                   (\
                                            OLED_CMD_SCROLL_PAGE_0 == page || \
                                            OLED_CMD_SCROLL_PAGE_1 == page || \
                                            OLED_CMD_SCROLL_PAGE_2 == page || \
                                            OLED_CMD_SCROLL_PAGE_3 == page || \
                                            OLED_CMD_SCROLL_PAGE_4 == page || \
                                            OLED_CMD_SCROLL_PAGE_5 == page || \
                                            OLED_CMD_SCROLL_PAGE_6 == page || \
                                            OLED_CMD_SCROLL_PAGE_7 == page \
                                        )


#define OLED_CMD_SCROLL_5_FRANES        0x00    // 5 frames
#define OLED_CMD_SCROLL_64_FRANES       0x01    // 64 frames
#define OLED_CMD_SCROLL_128_FRANES      0x02    // 128 frames
#define OLED_CMD_SCROLL_256_FRANES      0x03    // 256 frames
#define OLED_CMD_SCROLL_3_FRANES        0x04    // 3 frames
#define OLED_CMD_SCROLL_4_FRANES        0x05    // 4 frames
#define OLED_CMD_SCROLL_25_FRANES       0x06    // 25 frames
#define OLED_CMD_SCROLL_2_FRANES        0x07    // 2 frames

#define IS_FRANES(Franes)               (\
                                            OLED_CMD_SCROLL_5_FRANES == Franes || \
                                            OLED_CMD_SCROLL_64_FRANES == Franes || \
                                            OLED_CMD_SCROLL_128_FRANES == Franes || \
                                            OLED_CMD_SCROLL_256_FRANES == Franes || \
                                            OLED_CMD_SCROLL_3_FRANES == Franes || \
                                            OLED_CMD_SCROLL_4_FRANES == Franes || \
                                            OLED_CMD_SCROLL_25_FRANES == Franes || \
                                            OLED_CMD_SCROLL_2_FRANES == Franes\
                                        )

#define OLED_ADDR       0x78        // 0x78 0x7A������
#define OLED_WRITE      OLED_ADDR
#define OLED_READ       OLED_ADDR+1

#define OLED_CMD_CONTRAST           0x81    // ���öԱȶ�  81H xxH  �Աȶ�����ֵ�����Ӷ�����
#define OLED_CMD_CONTRAST_VALUE(v)  (v) 
#define OLED_CMD_DSP_ON_RAM         0xA4    // ��ʾ�����һָ�RAM����
#define OLED_CMD_DSP_ON             0xA5    // ��ʾ�������ָ�RAM����
#define OLED_CMD_DSP_NOR            0xA6    // ������ʾ
#define OLED_CMD_DSP_REV            0xA7    // ������ʾ
#define OLED_CMD_SLEEP              0xAE    // ˯��ģʽ  ��ʱ��֪����ô�˳�˯��ģʽ
#define OLED_CMD_SLEEP_OFF          0xAF    // ����ģʽ�������˯��ģʽ��˵
// scroll, �������ܿ���֮�󣬲����Խ���RAMд
#define OLED_CMD_SCROLL_H_R         0x26    // ˮƽ���ҹ��� 26H 00H 0xH 0yH 0zH  x:��ʼҳ��ַ(0-7) 
                                            // y:������ʱ����(0-7) z:����ҳ��ַ(0-7, z >= x)
#define OLED_CMD_SCROLL_H_L         0x27    // ˮƽ�������
#if defined OLED_CMD_SCROLL_H_R || defined OLED_CMD_SCROLL_H_L   
    #define IS_DIRECTION(d)         ((OLED_CMD_SCROLL_H_R == d) || (OLED_CMD_SCROLL_H_L == d))
#endif

#define OLED_CMD_SCROLL_V_R         0x29    // ��ֱ���ҹ��� 29H 00H 0xH 0yH 0zH iiH x:��ʼҳ��ַ(0-7) 
                                            // y:������ʱ����(0-7) z:����ҳ��ַ(0-7 z>=x) 
                                            // ii:��ֱ������λ��(0-63)
#define OLED_CMD_SCROLL_V_L         0x2A    // ��ֱ�������
#if defined OLED_CMD_SCROLL_V_R || defined OLED_CMD_SCROLL_V_L
#endif

// NOTE: �رչ�������֮��RAM������Ҫ����д��
#define OLED_CMD_SCROLL_OFF         0x2E    // �رչ������� 
// ���һ���������ܻᱻ������֮ǰ�Ĺ������ûᱻ���
#define OLED_CMD_SCROLL_ON          0x2F    // ������������

#define OLED_CMD_SCROLL_V_AREA      0xA3    // ���ô�ֱ�������� A3H xxH yyH
                                            // xx: ����̶�����(0-64)
                                            // yy: �ײ��������(0-64)
                                    
#define OLED_CMD_SET_LOW_ADDR(addr)     (addr & 0x0f)                   // ҳģʽ����������ʼ��ַ��λ
#define OLED_CMD_SET_HIGH_ADDR(addr)    (((addr >> 4) & 0x0f) | 0x20)   // ҳģʽ����������ʼ��ַ��λ

#define OLED_CMD_MEMORY_MODE            0x20    // �����ڴ�ģʽ  20H 0xH   x:ģʽѡ��(0-2)
#define OLED_CMD_MEMORY_MODE_H_ADDR     0x00    // ˮƽ��ַģʽ
#define OLED_CMD_MEMORY_MODE_V_ADDR     0x01    // ��ֱ��ַģʽ
#define OLED_CMD_MEMORY_MODE_P_ADDR     0x02    // ҳ��ַģʽ

#define OLED_CMD_SET_COLUMN_ADDR        0x21    // �����е�ַ    21H xxH yyH xx: ��ʼ��ַ(0-127) yy:������ַ(0-127)
#define OLED_CMD_SET_PAGE_ADDR          0x22    // ����ҳ��ַ    22H xxH yyH xx: ��ʼ��ַ(0-7) yy:������ַ(0-7)
#define OLED_CMD_SET_PAGE_START_ADDR(a) (0xB0 | a)  // ����ҳ��ʼ��ַ��Ϊҳ��ַģʽ

#define OLED_CMD_SET_DISPLAY_START_LINE(line)           (0x40 | line)
#define OLED_CMD_SET_SEG_NOR            0xA0    // �е�ַ0ӳ�䵽seg0
#define OLED_CMD_SET_SEG_RE_MAP         0xA1    // �е�ַ127ӳ�䵽seg0�������Ҿ���

#define OLED_CMD_MUX_RATIO              0xA8    // ���ø����� A8H xxH xx:������(16-64)
#define OLED_CMD_MUX_RATIO_VALUE(v)     (v)     // ���ø����ʵ�ֵ

#define OLED_CMD_COM_OUT_SCAN_DIR_NOR   0xC0    // ɨ�跽ʽ��com0-comN
#define OLED_CMD_COM_OUT_SCAN_DIR_REMAP 0xC8    // ɨ�跽ʽ��comN-com0 ���¾���

#define OLED_CMD_SET_DSP_OFFSET          0xD3    // ���ô�ֱƫ���� D3H xxH  xx: ��ֱƫ����(0-63)
#define OLED_CMD_SET_DSP_OFFSET_VALUE(v) (v)
#define OLED_CMD_SET_COM_PINS           0xDA    // ����������Ӳ������ DAH x2H    x: ģʽѡ��(0x00-0x0f)
#define OLED_CMD_SET_COM_PINS_SEQU      0x00    // ˳����������
#define OLED_CMD_SET_COM_PINS_ALTER     0x10    // �����������
#define OLED_CMD_SET_COM_PINS_RL_NOR    0x00    // �ر�����ӳ��
#define OLED_CMD_SET_COM_PINS_RL_REMAP  0x20    // ��������ӳ��
#define OLED_CMD_SET_COM_PINS_VALUE(v)  ((v) | 0x02)  // ģʽ����ֵ

#define OLED_CMD_SET_DIV_OSC_FREQ       0xD5    // ����ʱ�Ӻ�DCLK��Ƶϵ��
#define OLED_CMD_SET_DIV_VALUE(v)       (v)     // ��Ƶϵ��
#define OLED_CMD_SET_OSC_FREQ_VALUE(v)  ((v) << 4)// ʱ��Ƶ��
#define OLED_CMD_SET_DIV_OSC_FREQ_VALUE(v)  (v)

#define OLED_CMD_SET_PRE_CHARGE_PERIOD              0xD9    // ����Ԥ�������
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_1_VALUE(v)   (v)
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_2_VALUE(v)   ((v) << 4)
#define OLED_CMD_SET_PRE_CHARGE_PERIOD_VALUE(v)     (v)

#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL           0xDB    // ����VCOMH��ѹֵ
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_65_VCC  0x00    // ~0.65*Vcc
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_77_VCC  0x20    // ~0.77*Vcc
#define OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_83_VCC  0x30    // ~0.83*Vcc

#define OLED_CMD_NOP                    0xE3    // �޲���

#define OLED_CMD_SET_CHARGE_PUMP        0x8D    // ��ɱ�����    8DH 1xH x:0 �ر�  4:����
#define OLED_CMD_SET_CHARGE_PUMP_ON     0x14    // ����
#define OLED_CMD_SET_CHARGE_PUMP_OFF    0x10    // �ر�









#define OLED_ScrollLeft(StartPage, EndPage, Franes)   \
            OLED_Scroll(OLED_CMD_SCROLL_H_L, StartPage, EndPage, Franes)
#define OLED_ScrollRight(StartPage, EndPage, Franes)   \
            OLED_Scroll(OLED_CMD_SCROLL_H_R, StartPage, EndPage, Franes)





void OLED_Init(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_DisplayChar(uint8_t x, uint8_t y, uint8_t ch);
void OLED_DisplayStr(uint8_t x, uint8_t y, uint8_t * str);
void OLED_Scroll(uint8_t Direction, uint8_t StartPage, uint8_t EndPage, uint8_t Franes);
void OLED_ScrollUp(uint8_t StartPage, uint8_t EndPage, uint8_t Franes);
void OLED_DisplayIcon(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * ch, uint16_t len);
void OLED_DisplayHanziStr(u8 x, u8 y, char * disStr);
void OLED_DisplayLogo(void);
#endif
