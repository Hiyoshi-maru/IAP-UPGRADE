#ifndef __COM_H
#define __COM_H
#include "UART.h"
#include "Flash_operation.h"
/*各部分接收数据大小*/
#define SyncNumber            2
#define Packet_LengthNumber   2
#define Device_CodeNumber     17
#define Frame_TypeNumber      1
#define Packet_TypeNumber     1     
#define Frame_NoNumber        1
#define CRC16Number           2
#define EndNumber             1
#define Maxfilelength        491502



/*取人数据包数据定义*/
#define Sync0                 0xA5
#define Sync1                 0x5A
#define End_Value             0x96
#define packetlength0_start   0x03
#define packetlength1_start   0x00
#define packetlength0         0x01
#define packetlength1         0x00
#define frametype_ack         0x14
#define frametype_host        0x13
#define packettype_process    0xC8
#define packettype_start      0xC7
#define packettype_end        0xC9

#define Upgrade_OK                      (uint32_t)0x00000000
#define Upgrade_Onepacket_Error         (uint32_t)0x10101010
#define Upgrade_Fail                    (uint32_t)0x11111111
/*MD5校验*/
#define F(X,Y,Z)        ((X&Y)|((~X)&Z))
#define G(X,Y,Z)        ((X&Z)|(Y&(~Z)))
#define H(X,Y,Z)        (X^Y^Z)
#define I(X,Y,Z)        (Y^(X|(~Z)))
#define RL(x, y)        (((x) << (y)) | ((x) >> (32 - (y))))
#define PP(x)          ((x<<24)|((x<<8)&0x00ff0000)|((x>>8)&0x0000ff00)|(x>>24))////将一个32位数据颠倒
#define FF(a, b, c, d, x, s, ac)   a = b + (RL((a + F(b,c,d) + x + ac),s))
#define GG(a, b, c, d, x, s, ac)   a = b + (RL((a + G(b,c,d) + x + ac),s))
#define HH(a, b, c, d, x, s, ac)   a = b + (RL((a + H(b,c,d) + x + ac),s))
#define II(a, b, c, d, x, s, ac)   a = b + (RL((a + I(b,c,d) + x + ac),s))
typedef enum
{
  Com_OK_this =0,
  Com_Start,
  Com_Timeout,
  Com_Exit,
  Com_Error
} Com_Status;
Com_Status OnePacket_Rec(void);
void Data_Map(uint8_t* Data,uint8_t type);
uint8_t Communication(void);///////0：升级失败   1：升级成功  2：接收超时，数据无效
void OnePacket_Tra(uint8_t In1,uint32_t In2,uint8_t In3,uint8_t type);////第一个参数是frametype，第二个参数是packettype,第三个参数是Rev_Status
void Cpy_String(uint8_t* Data1,uint8_t* Data2,uint32_t length);
uint8_t Com_String(uint8_t* Data1,uint8_t* Data2,uint32_t length);
uint32_t Com_4_Data(uint8_t in1,uint8_t in2,uint8_t in3,uint8_t in4);
uint16_t RTU_CRC(uint8_t * puchMsg,uint32_t usDataLen);
void MD5_Loop(void);
void MD5_init(void);
void MD5_Cal(void);
#endif