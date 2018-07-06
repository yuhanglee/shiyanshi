#include "stc8.h"
#include "24c02.h"

// 读取一个字节
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr) {
	uint8_t temp=0;		  	    																 

	IIC_Start();  
	#if (EE_TYPE > AT24C16) 
		IIC_Send_Byte(WRITE);	   			// 发送设备地址和写信号
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr >> 8);		// 发送数据地址高8位
	#else
		IIC_Send_Byte(WRITE);   			// 发送设备地址和读信号
	#endif
		
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr & 0xff);   		// 发送数据地址低8位
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(READ);          		 	// 发送读信号	   
	IIC_Wait_Ack();	 
    temp = IIC_Read_Byte(0);		   
    IIC_Stop();	return temp;
}

// 写入一个字节
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite) {				   	  	    																 
    IIC_Start();  

	#if (EE_TYPE > AT24C16)
		IIC_Send_Byte(WRITE);	    		// 发送设备地址和写信号
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr >> 8);		// 发送数据地址高8位
	#else
		IIC_Send_Byte(WRITE); 
	#endif
	
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr & 0xff);
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);				// 输入数据
	IIC_Wait_Ack();  		    	   
    IIC_Stop();
}


// 写一个小于32位的数字
void AT24CXX_WriteLenByte(uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len) {  	
	uint8_t t;

	for (t = 0;t < Len;t++) {
		AT24CXX_WriteOneByte(WriteAddr + t, (DataToWrite >> (t << 3)) & 0xff);
	}												    
}

// 读一个小于32位的数字
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len) {  	
	uint8_t t;
	uint32_t temp = 0;

	for (t = 0;t < Len;t++) {
		temp <<= 8;
		temp += AT24CXX_ReadOneByte(ReadAddr + Len - t - 1); 	 				   
	}
	return temp;												    
}

// eeprom 自检
// 成功返回 0 
// 失败返回 1
uint8_t AT24CXX_Check(void) {
	uint8_t temp;
	
	temp=AT24CXX_ReadOneByte(EE_TYPE);

	if (temp == 0x36) {
		return 0;
	} else { // 避免第一次使用，重新写一次
		AT24CXX_WriteOneByte(EE_TYPE, 0X36);
	    temp = AT24CXX_ReadOneByte(EE_TYPE);	  
		if(temp == 0X36) {
			return 0;
		}
	}
	return 1;											  
}

// 写一个数组到指定地址处
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	for (;NumToRead;pBuffer++, ReadAddr++, NumToRead--) {
		*pBuffer = AT24CXX_ReadOneByte(ReadAddr);	
	}
} 

// 从指定数据处，读一个数组数据
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	for (;NumToWrite;WriteAddr++, pBuffer++, NumToWrite--) {
		AT24CXX_WriteOneByte(WriteAddr, *pBuffer);
	}
}


