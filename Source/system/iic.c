#include "stc8.h"
#include "iic.h"

/*
 * 目前只支持 at24c02 使用
 */
#define high 1
#define low 0 
sbit SCL=P2^5;
sbit SDA=P2^4;

void Delay_us(unsigned int us) {
    int i = 3;
    (void)us;
    for (;i;i--);
}
/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{
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
void IIC_Stop()
{
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
void IIC_Send_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)		
	{
		if(IIC_Byte & 0x80)		//1?0?
            SDA=high;
		else
            SDA=low;
		Delay_us(1);
		SCL=high;
		Delay_us(1);
		SCL=low;
		Delay_us(1);
		IIC_Byte<<=1;			//loop
	}
}


/*******************************************************************************
* oˉ êy ??         : IIC_Read_Byte
* oˉêy1|?ü		   : IIC?áò???×??ú 
* ê?    è?         : ack=highê±￡?·￠?íACK￡?ack=low￡?·￠?ínACK 
* ê?    3?         : ó|′e?ò·?ó|′e
*******************************************************************************/  
u8 IIC_Read_Byte(u8 ack)
{
	u8 i,receive=0;
    for(i=0;i<8;i++ )
	{
        SCL=low; 
        Delay_us(2);
		SCL=high;
        receive<<=1;
        if(SDA)receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//·￠?ínACK
    else
        IIC_Ack(); //·￠?íACK   
    return receive;
}
/*******************************************************************************
* oˉ êy ??         : IIC_Wait_Ack
* oˉêy1|?ü		   : μè′yó|′eD?o?μ?à′   
* ê?    è?         : ?T
* ê?    3?         : 1￡??óê?ó|′eê§°ü
        			 0￡??óê?ó|′e3é1|
*******************************************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 tempTime=0;
	SDA=high;
	Delay_us(1);	   
	SCL=high;
	Delay_us(1);	 
	while(SDA)
	{
		tempTime++;
		if(tempTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	SCL=low;//ê±?óê?3?0 	   
	return 0;  
} 

/*******************************************************************************
* oˉ êy ??         : IIC_Ack
* oˉêy1|?ü		   : 2úéúACKó|′e  
* ê?    è?         : ?T
* ê?    3?         : ?T
*******************************************************************************/
void IIC_Ack(void)
{
	SCL=low;
	SDA=low;
	Delay_us(2);
	SCL=high;
	Delay_us(5);
	SCL=low;
}

/*******************************************************************************
* oˉ êy ??         : IIC_NAck
* oˉêy1|?ü		   : 2úéúNACK·?ó|′e  
* ê?    è?         : ?T
* ê?    3?         : ?T
*******************************************************************************/		    
void IIC_NAck(void)
{
	SCL=low;
	SDA=high;
	Delay_us(2);
	SCL=high;
	Delay_us(5);
	SCL=low;
}	


/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   IIC_Send_Byte(0x78);            //Slave address,SA0=low
   IIC_Send_Byte(0x00);			//write command
   IIC_Send_Byte(IIC_Command); 
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   IIC_Send_Byte(0x78);			
   IIC_Send_Byte(0x40);			//write data
   IIC_Send_Byte(IIC_Data);
   IIC_Stop();
}