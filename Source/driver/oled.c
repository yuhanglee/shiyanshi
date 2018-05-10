#include "oled.h"
#include "uart.h"
#include "stdio.h"
#include "wc_string.h"
#include "mylib.h"
#include "gt20.h"


//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
uint8_t OLED_GRAM[128][8] = {0};

/*************Pin Define***************/
sbit SCL=P7^7;
sbit SDA=P7^6;

/****************************************************/
void Delay_50ms(uint16_t Del_50ms);
void Delay_1ms(uint16_t Del_1ms);
void Delay_us(uint16_t us);
void fill_picture(uint8_t fill_Data);
void Picture_1();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(uint8_t IIC_Command);
void Write_IIC_Data(uint8_t IIC_Data);
void Write_IIC_Byte(uint8_t IIC_Byte);



/***********************Delay****************************************/
static void Delay_50ms(uint16_t Del_50ms) {
	uint16_t m;

	for(;Del_50ms > 0;Del_50ms--) {
		for(m=6245;m>0;m--) {
        
        }
    }
}

static void Delay_1ms(uint16_t Del_1ms) {
	uint8_t j;
    
	while (Del_1ms--) {	
		for (j  =0;j < 123;j++) {
        
        }
	}
}
static void Delay_us(uint16_t us) {
    uint8_t i;
    (void)us;
	i = 2;
	while (--i);
}
/***********************Initial code*********************/
void OLED_Init(void) {
	Write_IIC_Command(OLED_CMD_SLEEP);   //display off
	Write_IIC_Command(OLED_CMD_MEMORY_MODE);	//Set Memory Addressing Mode	
	Write_IIC_Command(OLED_CMD_MEMORY_MODE_P_ADDR);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(OLED_CMD_SET_PAGE_START_ADDR(OLED_CMD_SCROLL_PAGE_0));	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(OLED_CMD_COM_OUT_SCAN_DIR_NOR);	//Set COM Output Scan Direction
	Write_IIC_Command(OLED_CMD_SET_LOW_ADDR(OLED_CMD_SCROLL_PAGE_0));//---set low column address
	Write_IIC_Command(OLED_CMD_SET_HIGH_ADDR(OLED_CMD_SCROLL_PAGE_0));//---set high column address
	Write_IIC_Command(OLED_CMD_SET_DISPLAY_START_LINE(0));//--set start line address
	Write_IIC_Command(OLED_CMD_CONTRAST);//--set contrast control register
	Write_IIC_Command(OLED_CMD_CONTRAST_VALUE(0x7f));
	Write_IIC_Command(OLED_CMD_SET_SEG_NOR);//--set segment re-map 0 to 127
	Write_IIC_Command(OLED_CMD_DSP_NOR);//--set normal display
	Write_IIC_Command(OLED_CMD_MUX_RATIO);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(OLED_CMD_MUX_RATIO_VALUE(0x3F));//
	Write_IIC_Command(OLED_CMD_DSP_ON_RAM);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(OLED_CMD_SET_DSP_OFFSET);//-set display offset
	Write_IIC_Command(OLED_CMD_SET_DSP_OFFSET_VALUE(0x00));//-not offset
	Write_IIC_Command(OLED_CMD_SET_DIV_OSC_FREQ);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(OLED_CMD_SET_DIV_OSC_FREQ_VALUE(OLED_CMD_SET_DIV_VALUE(0) | OLED_CMD_SET_OSC_FREQ_VALUE(0x0f)));//--set divide ratio
	Write_IIC_Command(OLED_CMD_SET_PRE_CHARGE_PERIOD);//--set pre-charge period
	Write_IIC_Command(OLED_CMD_SET_PRE_CHARGE_PERIOD_VALUE(OLED_CMD_SET_PRE_CHARGE_PERIOD_1_VALUE(2) | OLED_CMD_SET_PRE_CHARGE_PERIOD_2_VALUE(2))); //
	Write_IIC_Command(OLED_CMD_SET_COM_PINS);//--set com pins hardware configuration
	Write_IIC_Command(OLED_CMD_SET_COM_PINS_VALUE(OLED_CMD_SET_COM_PINS_ALTER | OLED_CMD_SET_COM_PINS_RL_NOR));
	Write_IIC_Command(OLED_CMD_SET_VCOMH_DESELECT_LEVEL);//--set vcomh
	Write_IIC_Command(OLED_CMD_SET_VCOMH_DESELECT_LEVEL_0_77_VCC);//0x20,0.77xVcc
	Write_IIC_Command(OLED_CMD_SET_CHARGE_PUMP);//--set DC-DC enable
	Write_IIC_Command(OLED_CMD_SET_CHARGE_PUMP_ON);//
	Write_IIC_Command(OLED_CMD_SLEEP_OFF);//--turn on oled panel 
}
/*******************ascii**********************/
static const uint8_t ascii[][ASCII_SIZE_Y*ASCII_SIZE_X/8] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, //   0x20
    {0x00, 0x00, 0x00, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x67, 0x00, 0x00, 0x00, }, // ! 0x21
    {0x00, 0x3E, 0x0E, 0x00, 0x3E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // " 0x22
    {0x20, 0x20, 0xFE, 0x20, 0x20, 0xFE, 0x20, 0x00, 0x04, 0x7F, 0x04, 0x04, 0x7F, 0x04, 0x04, 0x00, }, // # 0x23
    {0x02, 0x0C, 0x30, 0xC0, 0x30, 0x0C, 0x02, 0x00, 0x02, 0x02, 0x02, 0x7F, 0x02, 0x02, 0x02, 0x00, }, // $ 0x24
    {0x3C, 0x42, 0x42, 0xBC, 0x60, 0x18, 0x06, 0x00, 0x60, 0x18, 0x06, 0x3D, 0x42, 0x42, 0x3C, 0x00, }, // % 0x25
    {0x00, 0x3C, 0xC2, 0x22, 0x1C, 0x00, 0x00, 0x00, 0x1C, 0x23, 0x40, 0x47, 0x28, 0x30, 0x4E, 0x00, }, // & 0x26
    {0x00, 0x00, 0x1C, 0xFE, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // ' 0x27
    {0x00, 0x00, 0xE0, 0x18, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x07, 0x18, 0x20, 0x40, 0x00, 0x00, }, // ( 0x28
    {0x00, 0x02, 0x04, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x40, 0x20, 0x18, 0x07, 0x00, 0x00, 0x00, }, // ) 0x29
    {0x40, 0x80, 0x00, 0xF8, 0x00, 0x80, 0x40, 0x00, 0x10, 0x0C, 0x03, 0x01, 0x03, 0x0C, 0x10, 0x00, }, // * 0x2A
    {0x80, 0x80, 0x80, 0xF8, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // + 0x2B
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x38, 0x00, 0x00, 0x00, 0x00, }, // , 0x2C
    {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // - 0x2D
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, }, // . 0x2E
    {0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x06, 0x00, 0x60, 0x18, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, }, // / 0x2F
    {0x00, 0xFC, 0x02, 0x01, 0x01, 0x02, 0xFC, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00, }, // 0 0x30
    {0x00, 0x00, 0x04, 0x02, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, }, // 1 0x31
    {0x04, 0x02, 0x01, 0x81, 0x41, 0x22, 0x1C, 0x00, 0x0C, 0x0A, 0x09, 0x08, 0x08, 0x08, 0x08, 0x00, }, // 2 0x32
    {0x01, 0x11, 0x19, 0x25, 0x23, 0xC1, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, 0x00, }, // 3 0x33
    {0x80, 0x60, 0x18, 0x06, 0xF1, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x00, }, // 4 0x34
    {0x00, 0x1F, 0x11, 0x11, 0x11, 0x21, 0xC1, 0x00, 0x00, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // 5 0x35
    {0xE0, 0x58, 0x24, 0x22, 0x21, 0x40, 0x80, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // 6 0x36
    {0x01, 0x01, 0x01, 0x81, 0x71, 0x0D, 0x03, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // 7 0x37
    {0x8C, 0x52, 0x21, 0x21, 0x21, 0x52, 0x8C, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // 8 0x38
    {0x1C, 0x22, 0x41, 0x41, 0x41, 0xA2, 0x7C, 0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, }, // 9 0x39
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, }, // : 0x3A
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB3, 0x73, 0x00, 0x00, 0x00, 0x00, }, // ; 0x3B
    {0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x04, 0x00, }, // < 0x3C
    {0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, }, // = 0x3D
    {0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, }, // > 0x3E
    {0x18, 0x04, 0x02, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00, 0x00, 0x67, 0x67, 0x00, 0x00, 0x00, 0x00, }, // ? 0x3F
    {0xC4, 0x22, 0x22, 0xC2, 0x02, 0x04, 0xF8, 0x00, 0x1F, 0x20, 0x20, 0x1F, 0x20, 0x20, 0x1F, 0x00, }, // @ 0x40
    {0x00, 0xE0, 0x9C, 0x82, 0x9C, 0xE0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, }, // A 0x41
    {0x00, 0xFE, 0x42, 0x42, 0x42, 0xA2, 0x1C, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x07, 0x00, }, // B 0x42
    {0xF8, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x02, 0x00, }, // C 0x43
    {0x00, 0xFE, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // D 0x44
    {0x00, 0xFE, 0x42, 0x42, 0x42, 0x42, 0x02, 0x00, 0x00, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, }, // E 0x45
    {0x00, 0xFE, 0x22, 0x22, 0x22, 0x22, 0x02, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // F 0x46
    {0xF8, 0x04, 0x02, 0x02, 0x42, 0x44, 0xC8, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x0F, 0x00, }, // G 0x47
    {0x00, 0xFE, 0x40, 0x40, 0x40, 0x40, 0xFE, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, }, // H 0x48
    {0x00, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x08, 0x08, 0x00, 0x00, }, // I 0x49
    {0x00, 0x00, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x00, 0x06, 0x08, 0x08, 0x08, 0x07, 0x00, 0x00, 0x00, }, // J 0x4A
    {0x00, 0xFE, 0x40, 0xB0, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x01, 0x06, 0x08, 0x00, 0x00, }, // K 0x4B
    {0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x08, 0x08, 0x08, 0x0E, 0x00, 0x00, }, // L 0x4C
    {0xFE, 0x0C, 0x70, 0x80, 0x70, 0x0C, 0xFE, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x00, 0x00, 0x0F, 0x00, }, // M 0x4D
    {0x00, 0xFE, 0x0C, 0x30, 0xC0, 0x00, 0xFE, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x01, 0x06, 0x0F, 0x00, }, // N 0x4E
    {0xF8, 0x04, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // O 0x4F
    {0x00, 0xFE, 0x42, 0x42, 0x42, 0x24, 0x18, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // P 0x50
    {0xF8, 0x04, 0x02, 0x02, 0x02, 0x04, 0xF8, 0x00, 0x03, 0x04, 0x08, 0x09, 0x0A, 0x04, 0x0B, 0x00, }, // Q 0x51
    {0x00, 0xFE, 0x42, 0xC2, 0x42, 0x24, 0x18, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x03, 0x04, 0x08, 0x00, }, // R 0x52
    {0x18, 0x24, 0x42, 0x42, 0x82, 0x84, 0x08, 0x00, 0x02, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // S 0x53
    {0x02, 0x02, 0x02, 0xFE, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // T 0x54
    {0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // U 0x55
    {0x0E, 0x70, 0x80, 0x00, 0x80, 0x70, 0x0E, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x00, }, // V 0x56
    {0xFE, 0x00, 0xC0, 0x3C, 0xC0, 0x00, 0xFE, 0x00, 0x0F, 0x06, 0x01, 0x00, 0x01, 0x06, 0x0F, 0x00, }, // W 0x57
    {0x02, 0x0C, 0xB0, 0x40, 0xB0, 0x0C, 0x02, 0x00, 0x08, 0x06, 0x01, 0x00, 0x01, 0x06, 0x08, 0x00, }, // X 0x58
    {0x06, 0x18, 0x60, 0x80, 0x60, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // Y 0x59
    {0x02, 0x02, 0x02, 0xC2, 0x22, 0x1A, 0x06, 0x00, 0x08, 0x0C, 0x0B, 0x08, 0x08, 0x08, 0x08, 0x00, }, // Z 0x5A
    {0x00, 0x00, 0x00, 0xFE, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x40, 0x40, 0x00, 0x00, }, // [ 0x5B
    {0x06, 0x18, 0x60, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0x18, 0x60, 0x00, }, // \ 0x5C
    {0x00, 0x02, 0x02, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7F, 0x00, 0x00, 0x00, 0x00, }, // ] 0x5D
    {0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // ^ 0x5E
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, }, // _ 0x5F
    {0x00, 0x00, 0x00, 0x0E, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // ` 0x60
    {0x20, 0x90, 0x90, 0x90, 0x90, 0x10, 0xE0, 0x00, 0x07, 0x08, 0x08, 0x08, 0x08, 0x05, 0x0F, 0x00, }, // a 0x61
    {0x00, 0xFF, 0x20, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x0F, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00, }, // b 0x62
    {0xC0, 0x20, 0x10, 0x10, 0x10, 0x10, 0x20, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, }, // c 0x63
    {0xC0, 0x20, 0x10, 0x10, 0x20, 0xFF, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x0F, 0x00, 0x00, }, // d 0x64
    {0xC0, 0xA0, 0x90, 0x90, 0x90, 0xA0, 0xC0, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x08, 0x04, 0x00, }, // e 0x65
    {0x00, 0x40, 0x40, 0xFC, 0x42, 0x42, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, }, // f 0x66
    {0x00, 0xE0, 0x10, 0x10, 0x20, 0xF0, 0x00, 0x00, 0x00, 0x23, 0x44, 0x44, 0x42, 0x3F, 0x00, 0x00, }, // g 0x67
    {0x00, 0xFF, 0x20, 0x10, 0x10, 0x10, 0xE0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, }, // h 0x68
    {0x00, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // i 0x69
    {0x00, 0x00, 0x00, 0x00, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x40, 0x3F, 0x00, 0x00, 0x00, }, // j 0x6A
    {0x00, 0xFE, 0x00, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00, 0x0F, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00, }, // k 0x6B
    {0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, 0x00, }, // l 0x6C
    {0xF0, 0x20, 0x10, 0xE0, 0x10, 0x10, 0xE0, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x0F, 0x00, }, // m 0x6D
    {0x00, 0xF0, 0x20, 0x10, 0x10, 0x10, 0xE0, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, }, // n 0x6E
    {0xC0, 0x20, 0x10, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x03, 0x04, 0x08, 0x08, 0x08, 0x04, 0x03, 0x00, }, // o 0x6F
    {0x00, 0xF0, 0x20, 0x10, 0x10, 0x20, 0xC0, 0x00, 0x00, 0x7F, 0x04, 0x08, 0x08, 0x04, 0x03, 0x00, }, // p 0x70
    {0xC0, 0x20, 0x10, 0x10, 0x20, 0xF0, 0x00, 0x00, 0x03, 0x04, 0x08, 0x08, 0x04, 0x7F, 0x00, 0x00, }, // q 0x71
    {0x00, 0x00, 0x10, 0xE0, 0x10, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, }, // r 0x72
    {0x00, 0x60, 0x90, 0x90, 0x10, 0x10, 0x20, 0x00, 0x00, 0x04, 0x08, 0x08, 0x09, 0x09, 0x06, 0x00, }, // s 0x73
    {0x00, 0x10, 0x10, 0xFE, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0x08, 0x04, 0x00, }, // t 0x74
    {0x00, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x04, 0x0F, 0x00, }, // u 0x75
    {0x30, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x00, 0x00, 0x00, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x00, }, // v 0x76
    {0xF0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xF0, 0x00, 0x03, 0x0C, 0x03, 0x00, 0x03, 0x0C, 0x03, 0x00, }, // w 0x77
    {0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00, 0x04, 0x02, 0x01, 0x00, 0x01, 0x02, 0x04, 0x00, }, // x 0x78
    {0x30, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x00, 0x20, 0x10, 0x0B, 0x04, 0x03, 0x00, 0x00, 0x00, }, // y 0x79
    {0x10, 0x10, 0x10, 0x10, 0x90, 0x50, 0x30, 0x00, 0x08, 0x0C, 0x0A, 0x09, 0x08, 0x08, 0x08, 0x00, }, // z 0x7A
    {0x00, 0x00, 0x80, 0x40, 0x3E, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3E, 0x40, 0x00, 0x00, }, // { 0x7B
    {0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, }, // | 0x7C
    {0x00, 0x01, 0x3E, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x40, 0x3E, 0x01, 0x00, 0x00, 0x00, 0x00, }, // } 0x7D
    {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, }, // ~ 0x7E
};

static const uint8_t logo[4][256] = {

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0xE0,0xC0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xE0,0xE0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF0,0xE0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0xC0,0xC0,0xE0,0xF0,0xF0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF0,0xF0,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xE0,0xE0,0xE0,0xE0,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xF3,0xF3,0xE7,0xE7,0xCF,0xCF,0x9F,0x9F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x1F,0x9F,0xCF,0xCF,0xE7,0xE7,0xF3,0xF3,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0xF9,0xF9,0xF9,0xF9,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x98,0x98,0x98,0x98,0x98,0x98,0xF8,0xF8,0xE0,0xE0,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x18,0x18,0x78,0x78,0xE0,0xE0,0x80,0x80,0x00},
{0x00,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0xEF,0xDF,0xFF,0xBE,0xFE,0x7C,0xFC,0xF9,0xF9,0xF3,0xF7,0xE7,0xEF,0xEF,0xDF,0xBF,0xBF,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0xBF,0xBF,0xDF,0xCF,0xEF,0xE7,0xF7,0xF3,0xF9,0xF9,0xFC,0x7C,0xFE,0xFE,0xFF,0xDF,0xFF,0x6F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xFF,0xFF,0xFF,0xFF,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0xFF,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0xE0,0xE0,0xF8,0xF8,0x00,0x00,0x7E,0x7E,0xFF,0xFF,0x81,0x81,0x81,0x81,0x7F,0x7F,0xFF,0xFF,0x80,0x80,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x80,0x80,0x80,0xFF,0xFF,0x7F,0x7F,0x00,0x00,0x07,0x0F,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFE,0xFF,0xFD,0xFF,0xFB,0xF7,0xF6,0xEF,0xED,0xDF,0xFB,0xFF,0xF7,0xEF,0xEF,0xDF,0xFF,0xFF,0xFE,0xFE,0xFD,0x03,0x03,0x03,0xFD,0xFC,0xFE,0xFE,0xFF,0xDF,0xFF,0xEF,0xFF,0xF7,0xFF,0xDB,0xDD,0xED,0xFE,0xF6,0xFF,0xFB,0xFF,0xFD,0xFE,0x7F,0x7F,0x3F,0x3F,0x1F,0x1F,0x0F,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x07,0x0F,0x3F,0x1F,0x1F,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x1F,0x3F,0x0F,0x07,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x03,0x00,0x00,0x00,0x03,0x07,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
};
/**********************************************
//IIC Start
**********************************************/
static void IIC_Start(void) {
   SCL = high;
   Delay_us(1);		
   SDA = high;
   Delay_us(1);
   SDA = low;
   Delay_us(1);
   SCL = low;
   Delay_us(1);
}

/**********************************************
//IIC Stop
**********************************************/
static void IIC_Stop(void) {
   SCL = low;
   Delay_us(1);
   SDA = low;
   Delay_us(1);
   SCL = high;
   Delay_us(1);
   SDA = high;
   Delay_us(1);
}
/**********************************************
// IIC Write byte
**********************************************/
static void Write_IIC_Byte(uint8_t IIC_Byte) {
	uint8_t i;
	for(i = 0;i < 8;i++) {
		if(IIC_Byte & 0x80) {		//1?0?
            SDA=high;
		} else {
            SDA=low;
        }
        
		Delay_us(1);
		SCL=high;
		Delay_us(1);
		SCL=low;
		Delay_us(1);
		IIC_Byte<<=1;			//loop
	}
	SDA=1;
	Delay_us(1);
	SCL=1;
	Delay_us(1);
	SCL=0;
	Delay_us(1);
}
/**********************************************
// IIC Write Command
**********************************************/
static void Write_IIC_Command(uint8_t IIC_Command) {
   IIC_Start();
   Write_IIC_Byte(OLED_WRITE);            //Slave address,SA0=0
   Write_IIC_Byte(0x00);			//write command
   Write_IIC_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
static void Write_IIC_Data(uint8_t IIC_Data) {
   IIC_Start();
   Write_IIC_Byte(OLED_WRITE);			
   Write_IIC_Byte(0x40);			//write data
   Write_IIC_Byte(IIC_Data);
   IIC_Stop();
}

void OLED_Scroll(uint8_t Direction, uint8_t StartPage, uint8_t EndPage, uint8_t Franes) {
    wc_assert(IS_DIRECTION(Direction));
    wc_assert(IS_PAGE(StartPage));
    wc_assert(IS_PAGE(EndPage));
    wc_assert(IS_FRANES(Franes));
    
    Write_IIC_Command(OLED_CMD_SCROLL_OFF);
    Write_IIC_Command(Direction);
    Write_IIC_Command(0x00);
    Write_IIC_Command(StartPage);
    Write_IIC_Command(Franes);
    Write_IIC_Command(EndPage);
    Write_IIC_Command(0x00);
    Write_IIC_Command(0xff);
    Write_IIC_Command(OLED_CMD_SCROLL_ON);
} 

//更新显存到LCD		 
void OLED_Refresh_Gram(void) {
    static uint8_t i = 0,n = 0;		    
    while (i < OLED_Y_MAX*ASCII_SIZE_Y/8) {
		Write_IIC_Command(0xb0+i);    //设置页地址（0~7）
		Write_IIC_Command(0x00);      //设置显示位置—列低地址
		Write_IIC_Command(0x10);      //设置显示位置—列高地址   

		for (n = 0;n < OLED_X_MAX * ASCII_SIZE_X;n++) {
            Write_IIC_Data(OLED_GRAM[n][i]);
        }
        i++;
	}
    i=0;
}


void OLED_DisplayIcon(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t * ch, uint16_t len) {
    uint8_t i;
    uint8_t n = x << 3; // x*8
    
    wc_assert(x < OLED_X_MAX);
    wc_assert(y < OLED_Y_MAX);
    wc_assert((x + w / 8) <= OLED_X_MAX);
    wc_assert((y + h / 16) <= OLED_Y_MAX);
    
    for (i = 0;i < w;++i) {
        OLED_GRAM[n + i][y << 1]     = ch[i];
        OLED_GRAM[n + i][(y << 1) + 1] = ch[i + (len / 2)];
    }
}

void OLED_DisplayLogo(void) {
    OLED_DisplayIcon(0, 0, 128, 16, logo[0], sizeof(logo[0]));
    OLED_DisplayIcon(0, 1, 128, 16, logo[1], sizeof(logo[0]));
    OLED_DisplayIcon(0, 2, 128, 16, logo[2], sizeof(logo[0]));
    OLED_DisplayIcon(0, 3, 128, 16, logo[3], sizeof(logo[0]));
}

/*
 * x  0-15
 * y  0-3
 */
void OLED_DisplayChar(uint8_t x, uint8_t y, uint8_t ch) {
    uint8_t i;
    uint8_t n = x << 3; // x*8
    uint8_t index = ch - ' ';
    
    
    wc_assert(x < OLED_X_MAX);
    wc_assert(y < OLED_Y_MAX);
    
    for (i = 0;i < ASCII_SIZE_Y / 2;++i) {
        OLED_GRAM[n + i][y*2] = ascii[index][i];
        OLED_GRAM[n + i][y*2 + 1] = ascii[index][i + ASCII_SIZE_Y / 2];
    }
}
void OLED_DisplayStr(uint8_t x, uint8_t y, uint8_t * str) {
    uint8_t len = str_len(str);
    uint8_t i;
    
    wc_assert(x < OLED_X_MAX);
    wc_assert(y < OLED_Y_MAX);
    for (i = 0;(i < len) && ((x + i) < OLED_X_MAX);++i) {
        OLED_DisplayChar(x+i, y, str[i]);
    }
    
}

void OLED_DispalyHanzi(uint8_t x, uint8_t y, uint8_t msb, uint8_t lsb) {
	uint8_t dat[32];
    
    GT20_ReadChar(GT20FontAddr(msb, lsb), 16*16/8, dat);
    OLED_DisplayIcon(x, y, 16, 16, dat, 16*16/8);
}

void OLED_DisplayHanziStr(u8 x, u8 y, char * disStr) {
	u8 i;
	u8 len = str_len(disStr);
	u8 msb, msl;
	
    wc_assert(len <= OLED_X_MAX);
	for (i = 0;i < len;i+=2) {
		msb = disStr[i];
		msl = disStr[i + 1];
		OLED_DispalyHanzi(x+i, y, msb, msl);
	}
}
void OLED_Clear(void) {
    uint8_t i = 0, j = 0;
    
    for (i = 0;i < OLED_X_MAX * ASCII_SIZE_X;++i) {
        for (j = 0;j < OLED_Y_MAX * ASCII_SIZE_Y / 8;++j) {
            OLED_GRAM[i][j] = 0x00;
        }
    }
}
