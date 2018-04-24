#include "stc8.h"
#include "24c02.h"

/*******************************************************************************
* o�� ��y ??         : AT24CXX_ReadOneByte
* o����y1|?��		   : ?��AT24CXX???����??��?��3?��???��y?Y
* ��?    ��?         : ReadAddr:?a��??����y��?��??�� 
* ��?    3?         : ?����?��?��y?Y
*******************************************************************************/
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����?��D��?����?
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//����?��??��??��	    
	}
	else 
	{
		IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����?��?��?t��??��0XA0,D�䨺y?Y
	} 	   
	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //����?���̨���??��
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //??��??����??�꨺?			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//2��������???����?1��??t	    
	return temp;
}

/*******************************************************************************
* o�� ��y ??         : AT24CXX_WriteOneByte
* o����y1|?��		   : ?��AT24CXX???����??��D�䨨?��???��y?Y
* ��?    ��?         : WriteAddr  :D�䨨?��y?Y��???��?��??�� 
					 DataToWrite:��aD�䨨?��?��y?Y
* ��?    3?         : ?T
*******************************************************************************/
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //����?��D��?����?
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//����?��??��??��	  
	}
	else 
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����?��?��?t��??��0XA0,D�䨺y?Y
	} 	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //����?���̨���??��
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //����?����??��							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//2��������???����?1��??t 
}

/*******************************************************************************
* o�� ��y ??         : AT24CXX_WriteLenByte
* o����y1|?��		   : ?��AT24CXX��???��????����??��?a��?D�䨨?3��?��?aLen��?��y?Y
					 ��?����D�䨨?16bit?��??32bit��?��y?Y
* ��?    ��?         : WriteAddr  :D�䨨?��y?Y��???��?��??�� 
					 DataToWrite:��aD�䨨?��?��y?Y
					 Len        :��aD�䨨?��y?Y��?3��?��2,4
* ��?    3?         : ?T
*******************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*******************************************************************************
* o�� ��y ??         : AT24CXX_ReadLenByte
* o����y1|?��		   : ?��AT24CXX��???��????����??��?a��??��3?3��?��?aLen��?��y?Y
					 ��?����?��3?16bit?��??32bit��?��y?Y
* ��?    ��?         : ReadAddr   :?a��??��3?��?��??�� 
					 Len        :��a?��3?��y?Y��?3��?��2,4
* ��?    3?         : ?����?��?��y?Y
*******************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

/*******************************************************************************
* o�� ��y ??         : AT24CXX_Check
* o����y1|?��		   : ?��2��AT24CXX��?��??y3��
* ��?    ��?         : ?T
* ��?    3?         : 1:?��2a����㨹��?0:?��2a3��1|
*******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
	temp=AT24CXX_ReadOneByte(0);//����?a??��??a?��??D��AT24CXX	
    printf("%bd\n", temp);
	if(temp == 0x36)return 0;		   
	else//??3y�̨���?��?3?��??����??��??
	{
		AT24CXX_WriteOneByte(0,0X36);
	    temp = AT24CXX_ReadOneByte(0);	  
		if(temp == 0X36)return 0;
	}
	return 1;											  
}

/*******************************************************************************
* o�� ��y ??         : AT24CXX_Read
* o����y1|?��		   : ?��AT24CXX��???��????����??��?a��??��3????��??��y��?��y?Y
* ��?    ��?         : ReadAddr :?a��??��3?��?��??�� ??24c02?a0~255
					 pBuffer  :��y?Y��y����������??��
					 NumToRead:��a?��3?��y?Y��???��y
* ��?    3?         : ?T
*******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
} 

/*******************************************************************************
* o�� ��y ??         : AT24CXX_Write
* o����y1|?��		   : ?��AT24CXX��???��????����??��?a��?D�䨨????��??��y��?��y?Y
* ��?    ��?         : WriteAddr :?a��?D�䨨?��?��??�� ??24c02?a0~255
					 pBuffer  :��y?Y��y����������??��
					 NumToRead:��a?��3?��y?Y��???��y
* ��?    3?         : ?T
*******************************************************************************/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}


