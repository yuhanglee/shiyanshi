#ifndef __BOTP_H__
#define __BOTP_H__
#include "mylib.h"

#define BOTP_CRC16		0x2AE6
#define BOTP_MAC_ADDR	0x12345678


#define BOTP_OK					0x00
#define BOTP_ERROR_FORMAT		0x01
#define BOTP_ERROR_FAMILY		0x02
#define BOTP_ERROR_VERSION		0x03
#define BOTP_ERROR_LENGTH		0x04
#define BOTP_ERROR_MSG_BUS		0x05
#define BOTP_ERROR_MSG_TYPE		0x06
#define BOTP_ERROR_SMAC_ADDR	0x07
#define BOTP_ERROR_MSG_COUNT	0x08
#define BOTP_ERROR_DMAC_ADDR	0x09
#define BOTP_ERROR_UQICK_CMD	0x0A
#define BOTP_ERROR_TYPE			0x10
#define BOTP_ERROR_STR_LENGTH	0x11
#define BOTP_ERROR_TEXT_LENGTH	0x12
#define BOTP_ERROR_DATA_LENGTH	0x13
#define BOTP_ERROR_DATA_CRC16	0x14





#define PACK_LEN				(256)
#define PACK_DATA_LEN			(PACK_LEN - 0x18)


#define HEADER_BOTP				0x424F5450
#define HEADER					HEADER_BOTP
#define IS_HEADER(h)			(\
									HEADER_BOTP == (h) \
								)

#define FAMILY_WC				0x0000
#define FAMILY_FREE				0xffff
#define FAMILY					FAMILY_WC
#define IS_FAMILY(f)			(\
									FAMILY_WC 		== (f) 	|| \
									FAMILY_FREE 	== (f)     \
								)

#define VERSION_DEV				0x00
#define VERSION					VERSION_DEV
#define IS_VERSION(v)			(\
									VERSION_DEV 	== (v) \
								)

#define BUS_NET					0x00
#define BUS_SPI					0x01
#define BUS_UART				0x02
#define BUS_I2C					0x03
#define BUS_CAN					0x04
#define BUS_ERROR				0x0f
#define IS_BUS(b)				(\
									BUS_NET 	== (b) || \
									BUS_SPI		== (b) || \
									BUS_UART	== (b) || \
									BUS_I2C 	== (b) || \
									BUS_CAN		== (b) || \
									BUS_ERROR	== (b)    \
								)

#define MSG_TYPE_USER			0x00
#define MSG_TYPE_HEARBATE		0x01
#define MSG_TYPE_UP				0x02
#define MSG_TYPE_DOWN			0x03
#define MSG_TYPE_ASK			0x04
#define MSG_TYPE_ACK			0x05
#define MSG_TYPE_CS				0x06
#define MSG_TYPE_INT			0x07
#define MSG_TYPE_CTRL			0x08
#define MSG_TYPE_ERROR			0x0f
#define IS_MSG_TYPE(t)			(\
									MSG_TYPE_USER		== (t) || \
									MSG_TYPE_HEARBATE 	== (t) || \
									MSG_TYPE_UP			== (t) || \
									MSG_TYPE_DOWN		== (t) || \
									MSG_TYPE_ASK		== (t) || \
									MSG_TYPE_ACK		== (t) || \
									MSG_TYPE_CS			== (t) || \
									MSG_TYPE_INT		== (t) || \
									MSG_TYPE_CTRL		== (t) || \
									MSG_TYPE_ERROR		== (t)    \
								)

#define SET_MAC_ADDR(a1, a2, a3, a4)	((a1 << 24) | (a2 >> 16) | (a3 << 8) | (a4 << 0))

#define QUICK_CMD_USER			MSG_TYPE_USER
#define QUICK_CMD_TIMESTAMPS	MSG_TYPE_HEARBATE
#define QUICK_CMD_FIND			MSG_TYPE_ACK
#define QUICK_CMD_CTRL			MSG_TYPE_CTRL
#define QUICK_CMD_ERROR			MSG_TYPE_ERROR
#define IS_QUICK_CMD(c)			(\
									QUICK_CMD_USER 			== (c) || \
									QUICK_CMD_TIMESTAMPS	== (c) || \
									QUICK_CMD_FIND			== (c) || \
									QUICK_CMD_CTRL			== (c) || \
									QUICK_CMD_ERROR			== (c)    \
								)

#define PACK_TYPE_NULL			0x00
#define PACK_TYPE_TRUE			0x01
#define PACK_TYPE_FALSE			0x02
#define PACK_TYPE_BYTE			0x03
#define PACK_TYPE_SHORT			0x04		
#define PACK_TYPE_INT			0x05
#define PACK_TYPE_LONG			0x06
#define PACK_TYPE_FLOAT			0x07
#define PACK_TYPE_DOUBLE		0x08
#define PACK_TYPE_DATE			0x09
#define PACK_TYPE_TIME			0x0A
#define PACK_TYPE_DATETIME		0x0B
#define PACK_TYPE_UUID			0x0C
#define PACK_TYPE_STRING		0x0D
#define PACK_TYPE_TEXT			0x0E
#define PACK_TYPE_OBJ			0x40
#define PACK_TYPE_OBJ_NULL		(PACK_TYPE_OBJ + 1)
#define PACK_TYPE_OBJ_NOT_NULL	(PACK_TYPE_OBJ + 2)
#define PACK_TYPE_OBJ_NULL_STR	(PACK_TYPE_OBJ + 3)
#define PACK_TYPE_OBJ_STR		(PACK_TYPE_OBJ + 4)
#define PACK_TYPE_ARRAY_SMALL	0x80				// �������͵�С���� �������Ϊ 255 
#define PACK_TYPE_ARRAY_LONG	0xA0				// �������͵Ĵ����� �������Ϊ 65535 
#define PACK_TYPE_CLCT_NULL		0xC0				// �����͵Ĳɼ� 
#define PACK_TYPE_CLCT			0xE0 				// �����͵Ĳɼ�

#define IS_PACK_TYPE(t)			(\
									PACK_TYPE_NULL 				== (t) || \
									PACK_TYPE_TRUE				== (t) || \
									PACK_TYPE_FALSE				== (t) || \
									PACK_TYPE_BYTE				== (t) || \
									PACK_TYPE_SHORT				== (t) || \
									PACK_TYPE_INT				== (t) || \
									PACK_PYTE_LONG				== (t) || \
									PACK_PYTE_FLOAT				== (t) || \
									PACK_PYTE_DOUBLE			== (t) || \
									PACK_PYTE_DATE				== (t) || \
									PACK_PYTE_TIME				== (t) || \
									PACK_PYTE_DATETIME			== (t) || \
									PACK_TYPE_UUID				== (t) || \
									PACK_TYPE_STRING			== (t) || \
									PACK_TYPE_TEXT				== (t) || \
									PACK_TYPE_OBJ				== (t) || \
									PACK_TYPE_OBJ_NULL			== (t) || \
									PACK_TYPE_OBJ_NOT_NULL		== (t) || \
									PACK_TYPE_OBJ_NULL_STR		== (t) || \
									PACK_TYPE_OBJ_STR			== (t) || \
									PACK_TYPE_ARRAY_SMALL		== (t) || \
									PACK_TYPE_ARRAY_LONG		== (t) || \
									PACK_TYPE_CLCT_NULL			== (t) || \
									PACK_TYPE_CLCT				== (t)    \
								)


#define FLOAT_EQ(f1, f2) 					(((f1) - (f2)) < 0.001 && ((f2) - (f1)) < 0.001)

#define BOTP_CheckFormat(b)					((IS_HEADER((b).Header)) && (IS_VERSION((b).Version)))
#define BOTP_CheckVersionVaild(b)			(IS_VERSION((b).Version) && (VERSION >= (b).Version))
#define BOTP_CheckFamilyVaild(b)			(IS_FAMILY((b).Family))
#define BOTP_CheckBusID(b)					(IS_BUS((b).Msg.BusID))
#define BOTP_CheckMsgType(b)				(IS_BUS((b).Msg.BusID) && IS_MSG_TYPE((b).Msg.Type))
#define BOTP_CheckQuickCmd(b)				(IS_QUICK_CMD((b).QuickCmd))
#define BOTP_CheckDMacAddr(b)				((BOTP_MAC_ADDR) == BOTP_GetDMacAddr((b)))
#define BOTP_CheckCrc(b)					((b).Pack.Crc16 == CRC16_Calc((uint8_t *)(&b), (b).PackLen + 0x18))
#define BOTP_CheckPackType(p)				(IS_PACK_TYPE((p).Type))


#define BOTP_PackLength(b)					((b).PackLen + 0x18)


#define BOTP_SetBusID(b, id)				((b)->Msg.BusID = (id))
#define BOTP_SetMsgType(b, type)			((b)->Msg.Type = (type))
#define BOTP_SetSMacAddr(b, addr)			((b)->SMacAddr = (addr))
#define BOTP_SetMsgCount(b, count)			((b)->MsgCount = (count))
#define BOTP_SetDMacAddr(b, addr)			((b)->DMacAddr = (addr))
#define BOTP_SetQuickCmd(b, cmd)			((b)->QuickCmd = (cmd))
#define BOTP_SetPackLength(b, length)		((b)->PackLen = (length))

#define BOTP_SetPackType(p, type)			((p)->Type = (type))
#define BOTP_SetPackStringLength(p, l)		((p)->StrLen = (l))
#define BOTP_SetPackTextLength(p, l)		((p)->TextLen = (l))
#define BOTP_SetPackDataCrc16(p, crc)		((p)->Crc16 = (crc))

#define BOTP_GetBusID(b)					((b).Msg.BusID)
#define BOTP_GetMsgType(b)					((b).Msg.Type)
#define BOTP_GetSMacAddr(b)					((b).SMacAddr)
#define BOTP_GetMsgCount(b)					((b).MsgCount)
#define BOTP_GetDMacAddr(b) 				((b).DMacAddr)
#define BOTP_GetQuickCmd(b)					((b).QuickCmd)
#define BOTP_GetPackLength(b)				((b).PackLen)
#define BOTP_GetPackType(p)					((p).Type)
#define BOTP_GetPackStringLength(p)			((p).StrLen)
#define BOTP_GetPackTextLength(p)			((p).TextLen)
#define BOTP_GetPackDataCrc16(p)			((p).Crc16)

#define IS_EXT_DEV_ID(id)					( \
												((id) >= 0) && \
												((id) <= 7) \
											) 

typedef struct {
	uint8_t 	Data[PACK_DATA_LEN];
	uint16_t 	Crc16;
} Pack_t;

struct _msg{
	uint8_t BusID:4;
	uint8_t Type:4; 
};
typedef struct {
	uint32_t	 	Header; 		// "BOTP"
	uint16_t 		Family;			// ushort ����  	0x0000 ΢��    0xffff ����Э��
	uint8_t 		Version;		// �汾			 	0x00   �����汾
	struct _msg		Msg;			// ��Ϣ���� 
	uint32_t 		SMacAddr;				// ���豸mac��ַ 
 	uint32_t 		MsgCount;				// ��Ϣ����
 	uint32_t 		DMacAddr;				// Ŀ���豸mac��ַ  ���м�ʹ��
	uint32_t 		QuickCmd;				// ����ָ��
	uint16_t 		PackLen;				// ���ݳ���
	Pack_t 	 		Pack;
} BOTP;



typedef struct {
	struct _msg	Msg; 		// ��ǰ�豸��Ϣ����  �ο� BOTP ����Ϣ����
	uint8_t 	Index;		// ��ǰ�豸ռ����Դ����ֵ 
	uint32_t 	Mac;		// ��ǰ�豸 MAC ��ַ(CRC32) 
} ExtDev;
extern ExtDev device[];

uint16_t CRC16_Calc(char * CrcArray, uint16_t CrcLen);
void CRC16_CreateTable(void);
uint16_t BOTP_PackDataFill(Pack_t * p);
void BOTP_Init(BOTP * botp);
uint8_t BOTP_PackExtTest(Pack_t * p, uint16_t len);
uint8_t BOTP_Exec(BOTP * botp);

void ExtDev_Init(ExtDev * Dev);
void ExtDev_SetBusId(ExtDev * Dev, uint8_t BusId);
void ExtDev_SetMsgType(ExtDev * Dev, uint8_t MsgType);
void ExtDev_SetMacCrc32(ExtDev * Dev, uint32_t Mac);
void ExtDev_SetBusIndex(ExtDev * Dev, uint8_t Index);
uint8_t ExtDev_GetBusId(ExtDev * Dev);
uint8_t ExtDev_GetMsgType(ExtDev * Dev);
uint8_t ExtDev_GetDeviceIdleIndex(void);
uint8_t ExtDev_GetDeviceIndexByMac(uint32_t Mac);
uint8_t ExtDev_GetDeviceIndexByBusIndex(uint8_t BusId, uint8_t Index);
uint8_t ExtDev_GetBusIdleIndex(uint8_t BusId);
uint8_t BOTP_SendData(BOTP * b);
#endif
