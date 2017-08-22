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

//#define ENABLE      1
//#define DISABLE     2

#define ENABLESWITCH 	0x01


#define Do_True		0x01
#define Do_False	0x00

#define DISABLE_COUNTER	0x2
#define ENABLE_COUNTER	0xFD

//测试地址
#define IAP_ADDRESS 0x0000

#define SECTION     0x200  //512
//#define BLACK_LIST_COUNT 0
#define ENABLEORNOTSHANQU  0

#define DEVICE_STATUS_ADDR  	0x00
#define VER_ADDR				0x01
#define OFFSET_ADDR  			0x02
#define OFFSET_FLAG_ADDR  		0x03
#define AGENT_FLAG_ADDR  		0x04
#define PSW_DATA_ADDR  			0x05
#define AGENT_DATA_ADDR  		0x09 
#define VERIFY_PRODUCE_ADDR 	0x0D 
#define REVERSE_FLAG_ADDR		0x0E  
#define INNER_FLAG_ADDR			0x0F 

//#define DIS_VERIFY				1
//#define DO_VERIFY				0


//#define DIS_VERIFY_AGENT		1
//#define DO_VERIFY_AGENT			0

//#define DIS_REVERSE				1
//#define DO_REVERSE				0

//#define CUSTOMER_CARD  			0
//#define MANAGER_CARD			1

//#define DIS_PASSWORD			1
//#define DO_PASSWORD				0



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




#define INBLACKLIST       0x01
#define NOINBLACKLIST     0x00
#define BLACKLISTSTATUS   0x02


#define REVERSE_CHECK_OK       0x01
#define REVERSE_CHECK_ERROR     0x00


#define BLACK_LIST  0x200
#define MGR_BLACK_LIST 0x1200
#define BLACK_LIST_ITEM_LEN  4
#define REVERSE_LIST_ITEM_LEN  6
#define TEMP_ADDRESS 0xA00        

void Delay1();
void IapIdle();
uchar IapReadByte(uint addr);
void IapProgramByte(uint addr, uchar dat);
void IapEraseSector(uint addr);
void IapProgramBytes(uint addr,uchar *dat,unsigned int length);
void IapReadBytes(uint addr,unsigned char *dat,unsigned int length);
uchar SetDevice(uchar status);
uchar GetDevice();
uchar ReadOffset();
// uchar WriteOffset(uchar chOffset);
unsigned long ReadAgentID(void);
uchar WriteAgentID(uchar datas[]);
uchar ReadVerifyAgentFlag(void);
uchar WriteVerifyAgentFlag(uchar ucData);
void ClearBlackList(void);
//extern uchar WriteSectionPsw(uchar datas[]);
void ReadSectionPsw(uchar datas[]);
uchar ReadPasswordFlag(void);
uchar WritePasswordFlag(uchar ucData);

void WriteStatusData(uchar datas[]);
void ReadStatusData(uchar datas[]);

uchar ReadReverseCheckFlag(void);

uchar ReadInnerFlag(void);

//void WriteInnerFlag(uchar uchData);


//uchar modifyBlackList(uint items,uchar *list);

//extern uchar AddBlackList(uchar iType, uchar *list);
//extern uchar deleteBlackList(uchar iType, uchar *list);
//extern uchar checkBlackList(uchar iType, uchar *list);


/******************************************************
添加反写列表
*******************************************************/

uchar RecordCardList(uchar iType, uchar *list, uchar ucData);
/**********************************************************
清空黑名单
***********************************************************/ 

void ClearAllReverseList();

/**********************************************************
//删除黑名单
//***********************************************************/ 

//uchar RecordReverseData(uchar iType, uchar *list, uchar ucData);


/**********************************************************
删除黑名单
***********************************************************/ 

uchar DeleteBlackList(uchar iType, uchar *list);


/**********************************************************
删除黑名单
***********************************************************/ 

uchar Record2BlackList(uchar iType, uchar *list);

/**********************************************************

**************************************************************/
uchar CheckBlackList(uchar iType, uchar *list, uchar* pData);


/**********************************************************

**************************************************************/
//uchar CheckReverseData(uchar iType, uchar *list, uchar ucData, uchar *pCheckData);


/**********************************************************

**************************************************************/

uchar ReadDisableCounterFlag(void);

/**********************************************************

**************************************************************/

uchar ReadAgentFlagData(void);

/**********************************************************

**************************************************************/

uchar EnableCounter();

/**********************************************************

**************************************************************/

uchar DisableCounter();


#endif
