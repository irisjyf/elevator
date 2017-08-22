#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "STC15Fxxxx.h"
#include "intrins.h"
//-----------------------------------------------


#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3               //IAP扇区擦除命令

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
//#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//测试地址
#define IAP_ADDRESS 0x0000

//#define DEVICE_STATUS_ADDR  	0x00
//#define Ver_ADDR				0x01
//#define OFFSET_ADDR  			0x02
//#define OFFSET_FLAG_ADDR  		0x03
//#define AGENT_FLAG_ADDR  		0x04
//#define PSW_DATA_ADDR  			0x05
//#define AGENT_DATA_ADDR  		0x09 
//#define PRODUCE_FLAG_ADDR  		0x0D 
//#define VERIFY_PRODUCE_ADDR		0x0E 
//#define REVERSE_FLAG_ADDR		0x0F
//#define RECODE_TYPE_ADDR  		0x09
//#define SECTION_PSW_ADDR		0x0A
//#define PSW_FLAG_ADDR			0x0E

#define DEVICE_STATUS_ADDR  	0x00
#define VER_ADDR				0x01
#define OFFSET_ADDR  			0x02
#define OFFSET_FLAG_ADDR  		0x03
#define AGENT_FLAG_ADDR  		0x04
#define PSW_DATA_ADDR  			0x05
#define AGENT_DATA_ADDR  		0x09 
#define VERIFY_PRODUCE_ADDR 	0x0D 
#define REVERSE_FLAG_ADDR		0x0E 

#define DIS_VERIFY				0
#define DO_VERIFY				1


#define DIS_VERIFY_AGENT		1
#define DO_VERIFY_AGENT			0

#define DIS_REVERSE				0
#define DO_REVERSE				1

#define CUSTOMER_CARD  			0
#define MANAGER_CARD			1

#define DIS_PASSWORD			0
#define DO_PASSWORD				1



#define Do_True		0x01
#define Do_False	0x00


extern void Delay1();
extern void IapIdle();
extern uchar IapReadByte(uint addr);
extern void IapProgramByte(uint addr, uchar dat);
extern void IapEraseSector(uint addr);
extern void IapProgramBytes(uint addr,uchar *dat,unsigned int length);
extern void IapReadBytes(uint addr,unsigned char *dat,unsigned int length);
//extern unsigned long ReadAgentID(void);
//extern uchar WriteAgentID(uchar ucData[]);
//extern uchar ReadVerifyProduceFlag(void);
//extern uchar WriteVerifyProduceFlag(uchar ucData);
//extern uchar ReadOffset();
//extern uchar WriteOffset(uchar chOffset);
//extern uchar WriteSectionPsw(uchar datas[]);
//extern void ReadSectionPsw(uchar datas[]);
//extern uchar WritePasswordFlag(uchar ucData);
extern uchar ReadPasswordFlag(void);
//extern uchar WriteFlagDatas(uchar ucDatas[], uint uLen);


unsigned long ReadAgentID(void);
uchar ReadVerifyProduceFlag(void);
uchar WriteVerifyProduceFlag(uchar ucData);
uchar ReadOffset();
void ReadSectionPsw(uchar* pdatas);
uchar WriteFlagDatas(uchar* pdatas, uint uLen);
uchar ReadFlagDatas(uchar* pdatas);
uchar ReadReverseCheckFlag(void);


//extern uchar ReadVerifyAgentFlag(void);
//extern uchar WriteVerifyAgentFlag(uchar ucData);



#endif
