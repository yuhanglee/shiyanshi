#include "string.h"
#include "stdlib.h"
#include "botp.h"
#include "uart.h"
#include "max485.h"

// 大小端模式选择
#define BIG_ENCODE
//#define SMALL_ENCODE

// CRC 校验
static const uint16_t CRC16_TABLE[256] = {
    0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
    0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
    0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
    0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
    0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
    0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
    0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
    0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
    0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
    0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
    0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
    0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
    0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
    0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
    0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
    0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
    0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
    0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
    0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
    0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
    0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
    0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
    0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
    0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
    0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
    0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
    0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
    0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
    0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
    0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
    0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
    0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

// crc16 校验算法，返回CRC16校验值
uint16_t CRC16_Calc(char * CrcArray, uint16_t CrcLen) {
	uint16_t CrcRet = 0x00;
	
	for (; CrcLen; CrcLen--) {
		CrcRet = CRC16_TABLE[((CrcRet >> 8)  ^ *CrcArray++) & 0xff] ^ (CrcRet << 8);
	}
	
	return CrcRet & 0xffff;
}


#if defined BIG_ENCODE
// BOTP 协议 数据包获取一个item值
void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
    if (dat != 0) {
        for (i = 0;i < len;i++) {
             dat[i] = p->Data[index++];
        }
    }
}

// BOTP 协议 数据包添加一个item值
void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	uint8_t i = 0;
	
	p->Data[index++] = type & 0xff;
	 
    if (value != 0) {
        for (i = 0;i < len;i++) {
            p->Data[index++] = value[i];
        }
    }
}

#elif defined SMALL_ENCODE

void BOTP_PackGetItemData(Pack_t * p, uint8_t index, uint8_t * dat, uint8_t len) {
	uint8_t i = 0;
	
    if (dat != 0) {
        for (i = 0;i < len;i++) {
             dat[i] = p->Data[len - 1 - i + index];
        }
    }
}
void BOTP_PackAddItem(Pack_t * p, uint8_t index, uint8_t type, uint8_t * value, uint8_t len) {
	int8_t i = 0;
	
	 
	p->Data[index++] = type & 0xff;
	
    if (value != 0) {
        for (i = 0;i < len;i++) {
            p->Data[index++] = value[len - 1 - i];
        }
    }
}

#else
	#error "Please define encode"
#endif											


ExtDev device[8] = {
	{{BUS_UART, MSG_TYPE_USER},     UART_PAD,       0x11111111},    // CH340
	{{BUS_UART, MSG_TYPE_USER},     UART_485_1,     0x12345678},    // 4851
	{{BUS_NET,  MSG_TYPE_USER},     UART_485_2,     0x00000000},    // 4852
	{{BUS_NET,  MSG_TYPE_USER},     UART_485_3,     0x00000000},    // 4853
	{{BUS_NET,  MSG_TYPE_USER},     UART_DEBUG,     0x00000000},    // debug
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
	{{BUS_NET,  MSG_TYPE_USER},     0,  0x00000000},
};

void ExtDev_Init(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID(((Dev - device) / sizeof(device[0]))));
	
	Dev->Msg.BusID 	= BUS_ERROR;
	Dev->Msg.Type  	= MSG_TYPE_ERROR;
	Dev->Index 		= 0xff;
	Dev->Mac		= 0x00000000;
}

// 根据 busid 获取 device 的索引值
uint8_t ExtDev_GetBusIdleIndex(uint8_t BusId) {
	uint8_t i;
	uint8_t index = 0xff;
	
	wc_assert(IS_BUS(BusId));
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if (BusId == device[i].Msg.BusID) {
			index = device[i].Index;
		}
	}
	
	index++;
	
	return index & 0xff;
}

 
 
void ExtDev_SetBusId(ExtDev * Dev, uint8_t BusId) {
	wc_assert(IS_BUS(BusId));
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Msg.BusID = BusId;
}

void ExtDev_SetMsgType(ExtDev * Dev, uint8_t MsgType) {
	wc_assert(IS_MSG_TYPE(MsgType));
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Msg.Type = MsgType;
}

void ExtDev_SetMacCrc32(ExtDev * Dev, uint32_t Mac) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Mac = Mac;
}
void ExtDev_SetBusIndex(ExtDev * Dev, uint8_t Index) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	Dev->Index = Index;
}

uint8_t ExtDev_GetBusId(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));
	
	return Dev->Msg.BusID;
}

uint8_t ExtDev_GetMsgType(ExtDev * Dev) {
	wc_assert(IS_EXT_DEV_ID((Dev - device) / sizeof(device[0])));

	return Dev->Msg.Type;
}

uint8_t ExtDev_GetDeviceIdleIndex(void) {
	uint8_t i;
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if (device[i].Mac == 0x0000000) {
			return i;
		}
	}
	
	return BOTP_ERROR_INDEX;
}

uint8_t ExtDev_GetDeviceIndexByMac(uint32_t Mac) {
	int i;
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		 if (Mac == device[i].Mac) {
 			return i;
 		}
	}
	
	return BOTP_ERROR_INDEX;
}

uint8_t ExtDev_GetDeviceIndexByBusIndex(uint8_t BusId, uint8_t Index) {
	uint8_t i = 0;
	
	wc_assert(IS_BUS(BusId));
	wc_assert(IS_EXT_DEV_ID(Index));
	
	for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
		if ((BusId == device[i].Msg.BusID) && (Index == device[i].Index)) {
			return i;
		}
	}
	
	return BOTP_ERROR_INDEX;
} 



// 清除device数组，将重复设备数据的保留第一个，其余的删除
void ExtDev_ClearDeviceTable(void) {
    uint8_t i, j;
    
    for (i = 0;i < (sizeof(device) / sizeof(device[0]));i++) {
        if (0x00000000 != device[i].Mac) {
            for (j = i+1;j < (sizeof(device) / sizeof(device[0]));j++) {
                if (device[j].Mac == device[i].Mac) {
                    device[j].Mac = 0x00000000;
                }
            }
        }
    }
}

void BOTP_Init(BOTP * botp, uint32_t SrcMacAddr, uint32_t DecMacAddr) {
	memset(botp, 0, sizeof(BOTP));
	botp->Header 			= HEADER;
	botp->Family			= FAMILY;
	botp->Version			= VERSION;
	botp->SMacAddr			= SrcMacAddr;
	botp->MsgCount			= 0x0000;
	botp->DMacAddr			= DecMacAddr;
}

uint8_t BOTP_Exec(BOTP * botp) {
	uint8_t index = 0x00;
    uint16_t i = 0;
	// 格式
	if (0 == BOTP_CheckFormat(*botp)) {
		return BOTP_ERROR_FORMAT;
	}
	// 协议簇 
	if (0 == BOTP_CheckFamilyVaild(*botp)) {
		return BOTP_ERROR_FAMILY;
	}
	
	// 是否是本机数据
	if (0 == BOTP_CheckDMacAddr(*botp)) {
		index = ExtDev_GetDeviceIndexByMac(botp->DMacAddr);
        if (BOTP_ERROR_INDEX != index) { // 进行转发
            botp->Msg.BusID = device[index].Msg.BusID;
            botp->Msg.Type = device[index].Msg.Type;
            return BOTP_SendData(botp);	// 发送
        } else { // device 数组中没有保存当前dmac地址，将这个dmac地址保存到device数组中
            index = ExtDev_GetDeviceIdleIndex(); 
            if (BOTP_ERROR_INDEX != index) {
                ExtDev_SetBusId(&(device[index]), botp->Msg.BusID);
                ExtDev_SetMsgType(&(device[index]), botp->Msg.Type);
                ExtDev_SetBusIndex(&(device[index]), ExtDev_GetBusIdleIndex(botp->Msg.BusID));
                ExtDev_SetMacCrc32(&(device[index]), botp->SMacAddr); 
                return BOTP_OK;
            } else {
                print_debug("idle device index error\r\n");
                return BOTP_ERROR_INDEX;
            }
            print_debug("idle device index error\r\n");
        }
		return BOTP_ERROR_DMAC_ADDR;
	} else {
        if (0 == BOTP_PackExtTest(&(botp->Pack), botp->PackLen)) {
			print_debug("ext ok\r\n");
		} else {
			print_debug("ext error\r\n");
		}
	}
	
    return BOTP_OK;	
}

// 数据包的填充测试
uint16_t BOTP_PackDataFill(Pack_t * p) {
	int i = 0;
	uint32_t data_i;
	float data_f;
	double data_d; 
	uint8_t data_ch[16] = {
		0x1,
		0x2,
		0x3,
		0x4,
		0x5,
		0x6,
		0x7,
		0x8,
		0x9,
		0xa,
		0xb,
		0xc,
		0xd,
		0xe,
		0xf,
		0x0,
	};
	
	
	BOTP_ObjToNull(p, i); i+=1;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	data_i = 0x12345678;
	data_f = 0.22;
	data_d = 0.24;
	
	BOTP_ObjToByte(p, i, &data_i); i+=2;
	BOTP_ObjToShort(p, i, &data_i); i+=3;
	BOTP_ObjToInt(p, i, &data_i); i+=5;
	BOTP_ObjToLong(p, i, &data_i); i+=9;
	BOTP_ObjToFloat(p, i, &data_f); i+=5;
	BOTP_ObjToDouble(p, i, &data_d); i+=9;
	BOTP_ObjToDate(p, i, data_ch); i+=4;
	BOTP_ObjToTime(p, i, data_ch); i+=4;
	BOTP_ObjToDateTime(p, i, data_ch); i+=7;
	BOTP_ObjToUuid(p, i, data_ch); i+=17;
	BOTP_ObjToBool(p, i, i % 2); i+=1;
	BOTP_ObjToDate(p, i, data_ch); i+=4;
		
	return i;
} 

// pack数据包的解析测试
uint8_t BOTP_PackExtTest(Pack_t * p, uint16_t len) {
	uint16_t i = 0, u_8 = 0;
	uint16_t item_len = 0;
	char res[16];
	
	do {
		switch (p->Data[i]) {
			case PACK_TYPE_NULL:
				print_debug("NULL\r\n");
				item_len = 1;
			break;
			
			case PACK_TYPE_TRUE:
			case PACK_TYPE_FALSE:
				print_debug("%bx\r\n", BOTP_BoolToObj(p, i));
				item_len = 1;
			break;
			
			case PACK_TYPE_BYTE:
				BOTP_ByteToObj(p, i+1, res);
				print_debug("byte:\t%bx\r\n", *((uint8_t *)(res)));
				item_len = 2;
			break;
			case PACK_TYPE_SHORT:
				BOTP_ShortToObj(p, i+1, res);
				print_debug("short:\t%x\r\n", *((uint16_t *)(res)));
				item_len = 3;
			break;
			case PACK_TYPE_INT:
				BOTP_IntToObj(p, i+1, res);
				print_debug("int:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_LONG:
				BOTP_LongToObj(p, i+1, res);
				print_debug("long:\t%lx\r\n", *((uint32_t *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_FLOAT:
				BOTP_FloatToObj(p, i+1, res);
				print_debug("float:\t%f\r\n", *((float *)(res)));
				item_len = 5;
			break;
			case PACK_TYPE_DOUBLE:
				BOTP_DoubleToObj(p, i+1, res);
				print_debug("double:\t%f\r\n", *((double *)(res)));
				item_len = 9;
			break;
			case PACK_TYPE_DATE:
				BOTP_DateToObj(p, i+1, res);
				print_debug("date:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_TIME:
				BOTP_TimeToObj(p, i+1, res);
				print_debug("time:");
				item_len = 4;
				for (u_8 = 0;u_8 < 3;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_DATETIME:
				BOTP_DateTimeToObj(p, i+1, res);
				print_debug("datetime:");
				item_len = 7;
				for (u_8 = 0;u_8 < 6;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
			case PACK_TYPE_UUID:
				BOTP_UuidToObj(p, i+1, res);
				print_debug("uuid:");
				item_len = 17;
				for (u_8 = 0;u_8 < 16;u_8++) {
					print_debug("%bx ", res[u_8]);
				}
				print_debug("\r\n");
			break;
                
			default:
				print_debug("cmd default: %bx\r\n", p->Data[i]);
                item_len = 1;
			break;
		}
		i += item_len;
		len -= item_len;
		item_len = 0;
        if ((int)len < 0) {
            return 0xff;
        }
	} while (len);
    
	return 0x00;
}

// 数据的转发
uint8_t BOTP_SendData(BOTP * b) {
    uint8_t Index = ExtDev_GetDeviceIndexByMac(b->DMacAddr);
    
	switch (device[Index].Msg.BusID) {
		case BUS_UART:
			switch (device[Index].Index) {
				case UART_PAD:
                    Uart1SendHex((uint8_t *)b, BOTP_GetPackLength(*b) + 0x1C);
				break;
                
                case UART_485_1:
                case UART_485_2:
                case UART_485_3:
                    MAX485_WriteHex(device[Index].Index, (uint8_t *)b, BOTP_GetPackLength(*b) + 0x1C);
				break;
                
				default:
					print_debug("Uart index:%02bx\r\n", Index);
                    return BOTP_ERROR_MSG_BUS;
				break;
			}
		break;
		
		default:
			print_debug("busId:%02bx\r\n", device[Index].Msg.BusID);
            return BOTP_ERROR_MSG_BUS;
        break;
	}
    
    return BOTP_OK;
}