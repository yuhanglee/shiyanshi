#ifndef __IIC_H__
#define __IIC_H__

#include "mylib.h"

void Delay_us(unsigned int us);

void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void IIC_Send_Byte(unsigned char IIC_Byte);
void IIC_Ack(void);
void IIC_NAck(void);
u8 IIC_Wait_Ack(void);
u8 IIC_Read_Byte(u8 ack);

#endif
