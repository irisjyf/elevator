/*********************************************************
     +---------------------------------------------+
     |智趣电子       原创程序    多功能旋转POV LED |
     +---------------------------------------------+	   

 此源码版权属 智趣电子 全权享有，如欲引用，敬请署名并告知
        严禁随意用于商业目的，违者必究，后果自负
        智趣电子 
         ->产品咨询 QQ:1327074668 MSN:zhiqudz@163.com
		 ->产品网店 http://58788771.taobao.com/
	                Tel:18106718021
	 /*********************************************/
	 /*	项 目:	平面/立体/三色/多功能旋转POV LED  */
	 /*	模 块：	EEPROM模块						  */
	 /*	功 能：	EEPROM驱动              		  */
	 /*	版 本：	V3.0							  */
	 /*	设 计：	ZhiQu Studio					  */
	 /*	时 间：	2013年7月5日					  */
	 /*	修 改:	2013.7.5.19:00 创建项目			  */
	 /*	说 明：	主控MCU STC115F08S2  			  */		 
	 /*********************************************/
#include "EEPROM.H"
#include <string.h>

typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;
//#define USED_BYTE_QTY_IN_ONE_SECTOR   1
//#define USED_BYTE_QTY_IN_ONE_SECTOR   2
//#define USED_BYTE_QTY_IN_ONE_SECTOR   4
//#define USED_BYTE_QTY_IN_ONE_SECTOR   8
//#define USED_BYTE_QTY_IN_ONE_SECTOR   16
//#define USED_BYTE_QTY_IN_ONE_SECTOR   32
//#define USED_BYTE_QTY_IN_ONE_SECTOR   64
#define USED_BYTE_QTY_IN_ONE_SECTOR   128
//#define USED_BYTE_QTY_IN_ONE_SECTOR   256
//#define USED_BYTE_QTY_IN_ONE_SECTOR   512

//#define DEBUG_Data_Memory_Begin_Sector_addr     0x0400

//BYTE xdata protect_buffer[USED_BYTE_QTY_IN_ONE_SECTOR];

#define ERROR   0
#define OK      1
/*----------------------------
软件延时
----------------------------*/
void Delay1() //延时程序
{
    uint i;
    uint d=100;
    while (d--)
    {
        i=10;
        while (i--);
    }
}

/*----------------------------
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
uchar IapReadByte(uint addr)
{
    uchar dat;                       //数据缓冲区

    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(uint addr, uchar dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}
void IapProgramBytes(uint addr,uchar *dat,unsigned int length)
{
    unsigned char i=0;
	for(i=0;i<length;i++)
	{
		IapProgramByte(addr+i,dat[i]);
	}
}
void IapReadBytes(uint addr,unsigned char *dat,unsigned int length)
{
	unsigned char i=0;
	for(i=0;i<length;i++)
	{
		dat[i]=IapReadByte(addr+i);
	}
}
 /*********************
 设置刷卡状态
 **********************/
uchar SetDevice(uchar status)
{
	uchar temp[16];
	IapReadBytes(ENABLEORNOTSHANQU, temp, 16);

	IapEraseSector(ENABLEORNOTSHANQU);

	temp[0] = status;
	//IapProgramByte(ENABLEORNOTSHANQU,status);
	IapProgramBytes(ENABLEORNOTSHANQU,temp, 16);
	return 1;
}
/***********************************
得到刷卡器状态
**************************************/
uchar GetDevice()
{
	uchar ret;
	ret = IapReadByte(DEVICE_STATUS_ADDR);
	return ret;
}


uchar ReadOffset()
{
	uchar ucData = 0;
	ucData = IapReadByte(OFFSET_ADDR);
 	if(ucData >= 0x20)
		return 0;
 	return ucData;
}

//uchar WriteOffset(uchar chOffset)
//{
//	uchar xdata ucData = 0;
//	
//	uchar xdata temp[16];
//	IapReadBytes(ENABLEORNOTSHANQU, temp, 16);

//	temp[OFFSET_ADDR] = chOffset;
//	IapEraseSector(ENABLEORNOTSHANQU);
//	
//	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

//	if(IapReadByte(OFFSET_ADDR) == chOffset)
//		return Do_True;
//	return Do_False;
//}


unsigned long ReadAgentID(void)
{
	unsigned long lAgentID = 0;
	unsigned char datas[4]= {0xff, 0xff, 0xff, 0xff};
	IapReadBytes(AGENT_DATA_ADDR, datas, 4);

	if(datas[0] == 0xFF 
		&& datas[1] == 0xFF 
		&& datas[2] == 0xFF 
		&& datas[3] == 0xFF)
	{
		lAgentID = 0xFFFFFFFF;
	}
	else
	{
		lAgentID = (datas[0] << 24) 
			+ (datas[1] << 16) 
			+ (datas[2] << 8) 
			+ datas[3];
	}
	return lAgentID;
}

uchar WriteAgentID(uchar datas[])
{	
	uchar xdata temp[16] = {0};
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	temp[2] = datas[0];
	temp[3] = datas[1];
	temp[4] = datas[2];
	temp[5] = datas[3];
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

	IapReadBytes(AGENT_DATA_ADDR, (unsigned char *)&temp, 4);

	if(temp[0] == datas[0] 
		&& temp[1] == datas[1] 
		&& temp[2] == datas[2] 
		&& temp[3] == datas[3])
		
		return Do_True;
	
	return Do_False;
}


//uchar WriteSectionPsw(uchar datas[])
//{	
//	uchar xdata temp[16] = {0};
//	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

//	memcpy(temp + PSW_DATA_ADDR,datas,4);
//	
//	IapEraseSector(DEVICE_STATUS_ADDR);
//	
//	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

//	IapReadBytes(PSW_DATA_ADDR, (unsigned char *)&temp, 4);

//	if(temp[0] == datas[0] 
//		&& temp[1] == datas[1] 
//		&& temp[2] == datas[2] 
//		&& temp[3] == datas[3])
//		
//		return Do_True;
//	
//	return Do_False;
//}


void WriteStatusData(uchar datas[])
{	
	uchar xdata temp[16] = {0};
	uchar xdata temp1[16] = {0};
	uchar xdata i = 0;
	uchar xdata ucFlag = 0;
	
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	for(i = AGENT_FLAG_ADDR; i < AGENT_FLAG_ADDR + 4; i++)
	{
		if(temp[i] != 0xFF)
		{
			ucFlag = 1;
			break;
		}
	}

	if(ucFlag == 1)
	{
		memcpy(temp1, temp, 16);

		memcpy(temp + 1, datas, 14);

		memcpy(temp + AGENT_DATA_ADDR, temp1 + AGENT_DATA_ADDR, 4);

		temp[AGENT_FLAG_ADDR] = temp1[AGENT_FLAG_ADDR];

		temp[INNER_FLAG_ADDR] = 0x01;
	}
	else
	{
		memcpy(temp + 1, datas, 14);
		temp[INNER_FLAG_ADDR] = 0x01;		
	}
	
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);
}

void ReadStatusData(uchar datas[])
{	
	uchar xdata temp[16] = {0};
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	memcpy(datas, temp + 1, 14);
	
}

void ReadSectionPsw(uchar datas[])
{	
	IapReadBytes(PSW_DATA_ADDR, datas, 4);
}


uchar ReadVerifyAgentFlag(void)
{
	uchar temp = 0;
	temp = IapReadByte(AGENT_FLAG_ADDR);
	if(temp == 0x01)
		return DO_VERIFY_AGENT;
	return DIS_VERIFY_AGENT;
}


uchar ReadPasswordFlag(void)
{
	uchar chFlag = 0;
	chFlag = IapReadByte(OFFSET_FLAG_ADDR);
	if(chFlag  == 0x01)
		return DO_PASSWORD;
	return DIS_PASSWORD;

}

uchar ReadReverseCheckFlag(void)
{
	uchar chFlag = 0;
	chFlag = IapReadByte(REVERSE_FLAG_ADDR);
	if(chFlag == 0x01)
		return DO_REVERSE;
	return DIS_REVERSE;
}

uchar ReadInnerFlag(void)
{
	uchar chFlag = 0;
	chFlag = IapReadByte(INNER_FLAG_ADDR);
	return chFlag;
}


uchar ReadDisableCounterFlag(void)
{
	uchar temp = 0;
	temp = IapReadByte(AGENT_FLAG_ADDR);
	if(temp != 0xFF && 
		(temp & DISABLE_COUNTER) == DISABLE_COUNTER)
		return DISABLE_COUNTER;
	return ENABLE_COUNTER;
}



uchar ReadAgentFlagData(void)
{
	uchar temp = 0;
	temp = IapReadByte(AGENT_FLAG_ADDR);
	return temp;
}

uchar EnableCounter()
{
	uchar xdata temp[16] = {0};
	
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	temp[AGENT_FLAG_ADDR] &= ENABLE_COUNTER;
	
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

	if((temp[AGENT_FLAG_ADDR] & DISABLE_COUNTER) != DISABLE_COUNTER)
		return ENABLE_COUNTER;
	return DISABLE_COUNTER;
}


uchar DisableCounter()
{
	uchar xdata temp[16] = {0};
	
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	temp[AGENT_FLAG_ADDR] |= DISABLE_COUNTER;
	
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

	if((temp[AGENT_FLAG_ADDR] & DISABLE_COUNTER) != DISABLE_COUNTER)
		return ENABLE_COUNTER;
	
	return DISABLE_COUNTER;
}



//void WriteInnerFlag(uchar uchData)
//{
//	uchar xdata temp[16] = {0};
//	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);
//		
//	IapEraseSector(DEVICE_STATUS_ADDR);

//	temp[INNER_FLAG_ADDR] = uchData;
//	
//	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);
//}


//uchar WritePasswordFlag(uchar ucData)
//{
//	uchar chFlag = 0;
//	uchar xdata temp[16] = {0};
//	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

//	temp[OFFSET_FLAG_ADDR] = ucData;
//	
//	IapEraseSector(DEVICE_STATUS_ADDR);
//	
//	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);

//	chFlag = ReadPasswordFlag();

//	if(chFlag == ucData)		
//		return Do_True;
//	
//	return Do_False;
//}


uchar WriteVerifyAgentFlag(uchar ucData)
{
	unsigned char ucFlag;
	uchar temp[16] = {0};
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	temp[AGENT_FLAG_ADDR] = ucData;
	IapEraseSector(DEVICE_STATUS_ADDR);

	IapProgramBytes(ENABLEORNOTSHANQU, temp, 16);
	
	ucFlag = IapReadByte(AGENT_FLAG_ADDR);

	if(ucFlag == ucData )		
		return Do_True;
	
	return Do_False;
}



/******************************************************
//添加黑名单
//*******************************************************/

//uchar AddBlackList(uchar iType, uchar *list)
//{
//	uint i=0;
//	uint AddrBase = BLACK_LIST;
//	uchar temp[4];
//	for(i=0;i<4;i++)
//	{
//		temp[i]=list[i];
//	}
//	if(MANAGER_CARD == iType)
//		AddrBase = MGR_BLACK_LIST;
//	
//	for(i=0;i<1024;i++)
//	{
//		if(IapReadByte(AddrBase + i*4) == 0xff)
//		{
//			 IapProgramBytes(AddrBase + 4*i,temp,4);
//			 return 1;
//		}
//	}
//	return 0;	
//}	 
/********************************************************\
//修改黑名单
//***********************************************************/
/*
uchar modifyBlackList(uint items,uchar *list)
{
	uchar xdata temp[10];
	uchar i=0;
	IapReadBytes(BLACK_LIST_COUNT,temp,2);
	if(temp[0]*256+temp[1]>items)
	return 0;
    IapReadBytes(((items*4)/SECTION)*SECTION,temp,SECTION);
	IapEraseSector(((items*4)/SECTION)*SECTION);
	for(i=0;i<4;i++)
	{
		temp[(items*4)%SECTION+i]=list[i];
	}
	IapProgramBytes(((items*4)/SECTION)*SECTION,temp,SECTION);
	return 1;
}	
*/

/**********************************************************
//清空黑名单
//***********************************************************/ 

//void ClearBlackList()
//{
//	uint i=0;
//	
//	for(i=0;i<8;i++)
//	{
//		IapEraseSector(BLACK_LIST + i * SECTION);
//	}
//	for(i=0;i<8;i++)
//	{
//		IapEraseSector(MGR_BLACK_LIST + i * SECTION);
//	}
//}  

/**********************************************************
删除黑名单
***********************************************************/ 
/*
uchar deleteBlackList(uchar iType, uchar *list)
{
	uchar xdata temp[128];
	uint i=0;
	uint k;
	uchar j=0;
	uint AddrBase = BLACK_LIST;
	
	for(i=0;i<1024;i++)
	{
		if(IapReadByte(BLACK_LIST+i*4)==list[0]&&IapReadByte(BLACK_LIST+i*4+1)==list[1]&&
		   IapReadByte(BLACK_LIST+i*4+2)==list[2])
		{	 
			//IapReadBytes(BLACK_LIST+((i*4)/SECTION)*SECTION,temp,SECTION/4);
			for(j=0;j<4;j++)
			{
				IapReadBytes(BLACK_LIST+((i*4)/SECTION)*SECTION+j*128,temp,SECTION/4);
				for(k=0;k<32;k++){
					if(temp[4*k]==list[0]&&temp[4*k+1]==list[1]&&temp[4*k+2]==list[2])
					{
						temp[4*k]=0xff;temp[4*k+1]=0xff;temp[4*k+2]=0xff;
						break;
					}
				}
				
				IapReadBytes(TEMP_ADDRESS+j*128,temp,SECTION/4);
			}

			 IapEraseSector(BLACK_LIST+((i*4)/SECTION)*SECTION);

			 for(j=0;j<4;j++){
			 IapReadBytes(TEMP_ADDRESS+j*128,temp,SECTION/4);
			 IapProgramBytes(BLACK_LIST+((i*4)/SECTION)*SECTION+j*128,temp,SECTION/4);
			 }
			 //IapProgramBytes(BLACK_LIST+((i*4)/SECTION)*SECTION,temp,SECTION);
			 return 1;
		}
	}
	return 0;
	
}  

*/

/**********************************************************
//删除黑名单
//***********************************************************/ 

//uchar deleteBlackList(uchar iType, uchar *list)
//{
//	uchar xdata temp[128];
//	uint i=0;
//	uint k;
//	uchar j=0;
//	uint AddrBase = BLACK_LIST;

//	if(iType == MANAGER_CARD)
//		AddrBase = MGR_BLACK_LIST;
//	
//	for(i=0;i<1024;i++)
//	{
//		if(IapReadByte(AddrBase + i*4) == list[0]
//			&&IapReadByte(AddrBase + i*4 + 1) == list[1]
//			&&IapReadByte(AddrBase + i*4 + 2) == list[2])
//		{	 
//			//IapReadBytes(BLACK_LIST+((i*4)/SECTION)*SECTION,temp,SECTION/4);
//			for(j=0;j<4;j++)
//			{
//				IapReadBytes(AddrBase+((i*4)/SECTION)*SECTION+j*128,temp,SECTION/4);

//				for(k=0;k<32;k++)
//				{
//					if(temp[4*k]==list[0]
//						&&temp[4*k+1]==list[1]
//						&&temp[4*k+2]==list[2])
//					{
//						temp[4*k]=0xff;temp[4*k+1]=0xff;temp[4*k+2]=0xff;
//						break;
//					}
//				}
//				
//				IapReadBytes(TEMP_ADDRESS+j*128,temp,SECTION/4);
//			}

//			IapEraseSector(AddrBase+((i*4)/SECTION)*SECTION);

//			for(j=0;j<4;j++)
//			{
//				IapReadBytes(AddrBase+j*128,temp,SECTION/4);
//				IapProgramBytes(AddrBase+((i*4)/SECTION)*SECTION+j*128,temp,SECTION/4);
//			}
//			 //IapProgramBytes(BLACK_LIST+((i*4)/SECTION)*SECTION,temp,SECTION);
//			return 1;
//		}
//	}
//	return 0;
//	
//}  



/**********************************************************

//**************************************************************/
//uchar checkBlackList(uchar iType, uchar *list)
//{
//	uint i=0;
//	uchar temp[4];
//	uint AddrBase = BLACK_LIST;

//	if(iType == MANAGER_CARD)
//		AddrBase = MGR_BLACK_LIST;
//	
//	for(i=0;i < 1024; i++)
//	{
//		IapReadBytes(AddrBase + 4*i,temp,4);
//		if(temp[0] == list[0] 
//			&& temp[1] == list[1]
//			&&temp[2] == list[2])
//		{
//			return 1;
//		}
//	}
//	return 0;
//}


/******************************************************
添加反写列表
*******************************************************/

uchar RecordCardList(uchar iType, uchar *list, uchar ucData)
{
	uint  i=0;
	uint  AddrBase = BLACK_LIST;
	uchar xdata temp[128];
	uchar  ucCardNo[6];
	uchar  ucFlag = 0;
	uchar  k = 0;
	uchar  j = 0;
	
	for(i=0;i<4;i++)
	{
		temp[i]=list[i];
	}

	temp[4] = 0xFF;	
	temp[5] = ucData;
	
	if(MANAGER_CARD == iType)
		AddrBase = MGR_BLACK_LIST;
	
	for(i=0;i<1024;i++)
	{		
		IapReadBytes(AddrBase + i*6, ucCardNo, 6);

		if(ucCardNo[0] == 0xFF 
			&& ucCardNo[1] == 0xFF 
			&& ucCardNo[2] == 0xFF )
			{
				IapProgramBytes(AddrBase + 6 * i,temp,6);
		 		return 1;
			}
		
		if(ucCardNo[0] == list[0]
			&& ucCardNo[1] == list[1]
			&& ucCardNo[2] == list[2] )
		{
			for(j=0;j<4;j++)
			{
				//IapReadBytes(AddrBase + ((i*6)/SECTION)*SECTION + j*128, temp, SECTION/4);
				IapReadBytes(AddrBase + (i*6) & 0xFE00 + j * 128, temp, 128);
				
				if(ucFlag == 1)
					continue;
				
				for(k=0;k<32;k++)
				{
					if(temp[6*k] == list[0]
						&&temp[6*k+1] == list[1]
						&&temp[6*k+2] == list[2])
					{
						temp[6*k+4] = 0xFF;
						temp[6*k+5] = ucData;
						ucFlag = 1;
						break;
					}
				}
				
				IapProgramBytes(TEMP_ADDRESS + j * 128, temp, 128);
			}

			IapEraseSector((AddrBase+(i*6)) & 0xFE00 );

			for(j=0;j<4;j++)
			{
				IapReadBytes(TEMP_ADDRESS + j * 128, temp, 128);
				IapProgramBytes(AddrBase + (i*6) & 0xFE00 + j*128, temp, 128);
			}

			IapEraseSector(TEMP_ADDRESS);
			
			return 1;
		}
	}
	return 0;	
}	 


/**********************************************************
清空黑名单
***********************************************************/ 

void ClearAllReverseList()
{
	uint xdata i=0;
	
	for(i=0;i<8;i++)
	{
		IapEraseSector(BLACK_LIST + i * SECTION);
	}
	for(i=0;i<8;i++)
	{
		IapEraseSector(MGR_BLACK_LIST + i * SECTION);
	}
}  

/**********************************************************
//删除黑名单
//***********************************************************/ 

//uchar RecordReverseData(uchar iType, uchar *list, uchar ucData)
//{
//	uchar xdata temp[128];
//	uint xdata i=0;
//	uchar xdata k;
//	uchar xdata j=0;
//	//uint xdata  AddrBase = BLACK_LIST;
//	
//	for(i=0;i<1024;i++)
//	{
//		if(IapReadByte(BLACK_LIST + i*6) ==list[0]
//			&&IapReadByte(BLACK_LIST + i*6 + 1)==list[1]
//			&&IapReadByte(BLACK_LIST + i*6 + 2)==list[2])
//		{	 
//			for(j=0;j<4;j++)
//			{
//				IapReadBytes(BLACK_LIST + ( (i*6) / SECTION) * SECTION + j*128,temp, SECTION/4);
//				for(k=0;k<32;k++)
//				{
//					if(temp[6 * k] == list[0]
//						&&temp[6*k+1] == list[1]
//						&&temp[6*k+2] == list[2])
//					{
//						//temp[6*k] = 0xff;
//						//temp[6*k+1] = 0xff;
//						//temp[6*k+2] = 0xff;

//						temp[6*k+5] = ucData;
//						
//						break;
//					}
//				}
//				
//				IapReadBytes(TEMP_ADDRESS+j*128,temp,SECTION/4);
//			}

//			 IapEraseSector(BLACK_LIST+((i*6)/SECTION)*SECTION);

//			 for(j=0;j<4;j++)
//			 {
//			 	IapReadBytes(TEMP_ADDRESS + j * 128,temp,SECTION/4);
//			 	IapProgramBytes(BLACK_LIST + ((i * 6)/SECTION)*SECTION + j*128,temp,SECTION/4);
//			 }
//			 
//			 return 1;
//		}
//	}
//	return 0;
//	
//}  



/**********************************************************
删除黑名单
***********************************************************/ 

uchar DeleteBlackList(uchar iType, uchar *list)
{
	uchar xdata temp[128];
	uint   i=0;
	uchar   k;
	uchar  j=0;
	uint  AddrBase = BLACK_LIST;

	if(iType == MANAGER_CARD)
		AddrBase = MGR_BLACK_LIST;
	
	for(i=0; i<1024; i++)
	{
	
		if(IapReadByte(AddrBase + i*6) == 0xFF
			&&IapReadByte(AddrBase + i*6 + 1) == 0xFF
			&&IapReadByte(AddrBase + i*6 + 2) == 0xFF)
			{
				return 1;
			}
		if(IapReadByte(AddrBase + i*6) == list[0]
			&&IapReadByte(AddrBase + i*6 + 1) == list[1]
			&&IapReadByte(AddrBase + i*6 + 2) == list[2])
		{	 
			for(j=0;j<4;j++)
			{
				IapReadBytes(AddrBase + (i*6) & 0xFE00 + j*128, temp, 128);

				for(k=0;k<32;k++)
				{
					if(temp[6*k] == list[0]
						&&temp[6*k+1] == list[1]
						&&temp[6*k+2] == list[2])
					{
						//temp[6*k] =0xff;
						//temp[6*k+1] =0xff;
						//temp[6*k+2] =0xff;
						
						temp[6*k+4] =0xFF;
						
						break;
					}
				}
				
				IapProgramBytes(TEMP_ADDRESS + j * 128, temp, 128);
			}

			IapEraseSector((AddrBase+(i*6)) & 0xFE00 );

			for(j=0;j<4;j++)
			{
				IapReadBytes(TEMP_ADDRESS + j * 128, temp, 128);
				IapProgramBytes(AddrBase + (i*6) & 0xFE00 + j*128, temp, 128);
			}

			IapEraseSector(TEMP_ADDRESS);
			
			return 1;
		}
	}
	return 0;
	
} 



/**********************************************************
删除黑名单
***********************************************************/ 

uchar Record2BlackList(uchar iType, uchar *list)
{
	uchar xdata temp[128];	
	uchar  ucCardNo[6];
	uint  i = 0;
	uchar  k;
	uchar  j = 0;
	uchar  m = 0;
	uint  AddrBase = BLACK_LIST;

	if(iType == MANAGER_CARD)
		AddrBase = MGR_BLACK_LIST;

	for(i=0; i<4; i++)
		temp[i]=list[i];
	
	for(i=0;i<1024;i++)
	{	
		IapReadBytes(AddrBase + i*6, ucCardNo, 6);

		if(ucCardNo[0] == 0xFF 
			&& ucCardNo[1] == 0xFF 
			&& ucCardNo[2] == 0xFF )
			{
				temp[4] = 0;
				temp[5] = 0xFF;
				
				IapProgramBytes(AddrBase + 6 * i,temp,5);
		 		return 1;
			}
		
		if( ucCardNo[0] == list[0]
			&& ucCardNo[1] == list[1]
			&& ucCardNo[2] == list[2] )
		{	 
			for(j=0;j<4;j++)
			{
				IapReadBytes(AddrBase + (i*6)&0xFE00 + j*128, temp, 128);

				for(k=0;k<32;k++)
				{
					if(temp[6*k] == list[0]
						&&temp[6*k+1] == list[1]
						&&temp[6*k+2] == list[2])
					{						
						temp[6*k+4] =0x0;
						
						break;
					}
				}
				
				IapProgramBytes(TEMP_ADDRESS + j * 128, temp, 128);
			}

			IapEraseSector((AddrBase+(i*6)) & 0xFE00 );

			for(j=0;j<4;j++)
			{
				IapReadBytes(TEMP_ADDRESS + j * 128, temp, 128);
				IapProgramBytes(AddrBase + (i*6)&0xFE00 + j*128, temp,  128);
			}

			IapEraseSector(TEMP_ADDRESS);
			
			return 2;
		}
	}
	return 0;
	
}  


/**********************************************************

**************************************************************/
uchar CheckBlackList(uchar iType, uchar *list, uchar* pData )
{
	uint  i=0;	
	uchar  ucCardNo[6];
	uint  AddrBase = BLACK_LIST;

	*pData = 0xFF;

	if(iType == MANAGER_CARD)
		AddrBase = MGR_BLACK_LIST;
	
	for(i=0;i < 1024; i++)
	{	
		IapReadBytes(AddrBase + i*6, ucCardNo, 6);

		if(ucCardNo[0] == 0xFF 
			&& ucCardNo[1] == 0xFF 
			&& ucCardNo[2] == 0xFF )
			{
		 		return NOINBLACKLIST;
			}
		
		if( ucCardNo[0] == list[0]
			&& ucCardNo[1] == list[1]
			&& ucCardNo[2] == list[2] )
		{
			*pData = ucCardNo[5];
			if(ucCardNo[4] == 0x00)
				return INBLACKLIST;
			
			return BLACKLISTSTATUS;
		}
	}
	return NOINBLACKLIST;
}


/**********************************************************

**************************************************************/
//uchar CheckReverseData(uchar iType, uchar *list, uchar ucData, uchar *pCheckData)
//{
//	uint  i=0;
//	uchar  temp[6];
//	uint  AddrBase = BLACK_LIST;

//	if(iType == MANAGER_CARD)
//		AddrBase = MGR_BLACK_LIST;
//	
//	for(i=0;i < 1024; i++)
//	{
//		IapReadBytes(AddrBase + 6*i,temp,6);
//		
//		if(temp[0] == 0xFF 
//			&&temp[1] == 0xFF 
//			&&temp[2] == 0xFF )
//			return REVERSE_CHECK_OK;
//		
//		if(temp[0] == list[0] 
//			&& temp[1] == list[1]
//			&& temp[2] == list[2])
//		{
//			*pCheckData = temp[5];
//			if(temp[5] == ucData)
//				return REVERSE_CHECK_OK;
//			return REVERSE_CHECK_ERROR;
//		}
//	}
//	return REVERSE_CHECK_ERROR;
//}


/*----------------------------
扇区擦除
----------------------------*/
void IapEraseSector(uint addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}


/* 
//	写数据进数据Flash存储器(EEPROM),  只在同一个扇区内写，
//	保留同一扇区中不需修改的数据    */
/*   begin_addr,被写数据Flash开始地址；
//	counter,连续写多少个字节；
//	array[]，数据来源       */
//uchar write_flash_with_protect_in_one_sector(WORD begin_addr, WORD counter, BYTE array[])
//{
//    WORD i = 0;
//    WORD in_sector_begin_addr = 0;
//    WORD sector_addr = 0;
//    WORD byte_addr = 0;

//    /* 判是否是有效范围,此函数不允许跨扇区操作 */
//    if(counter > USED_BYTE_QTY_IN_ONE_SECTOR)
//        return ERROR;
//    in_sector_begin_addr = begin_addr & 0x01ff;
//	
//    /* 假定从扇区的第0个字节开始，到USED_BYTE_QTY_IN_ONE_SECTOR-1个字节结束,后面部分不用,程序易编写 */
//    if((in_sector_begin_addr + counter) > USED_BYTE_QTY_IN_ONE_SECTOR)
//        return ERROR;

//    /* 将该扇区数据 0 - (USED_BYTE_QTY_IN_ONE_SECTOR-1) 字节数据读入缓冲区保护 */
//    sector_addr = (begin_addr & 0xfe00);
//    byte_addr = sector_addr;

//    for(i = 0; i < USED_BYTE_QTY_IN_ONE_SECTOR; i++)
//    {
//        protect_buffer[i] = IapReadByte(byte_addr++);
//    }

//    /* 将要写入的数据写入保护缓冲区的相应区域,其余部分保留 */
//    for(i = 0; i < counter; i++)
//    {
//        protect_buffer[in_sector_begin_addr++] = array[i];
//    }

//    /* 擦除 要修改/写入 的扇区 */
//    IapEraseSector(sector_addr);

//    /* 将保护缓冲区的数据写入 Data Flash, EEPROM */
//    byte_addr = sector_addr;
//    for(i = 0; i< USED_BYTE_QTY_IN_ONE_SECTOR; i++)
//    {
//        /* 写一个字节 */
//        IapProgramByte(byte_addr, protect_buffer[i]);
//        /*  比较对错 */
      //  if (SendData(IapReadByte(begin_addr)) != protect_buffer[i])
      // {
      //      IapIdle();
      //      return ERROR;
      //  }
//        byte_addr++;
//    }
//    IapIdle();
//    return OK;
//}


/******************************************************
//写偏移数据

//*******************************************************/

//uchar WriteOffset(uchar chData)
//{
//	if(IapReadByte(OFFSET_ADDR)==0xff)
//	{
//		 IapProgramByte(OFFSET_ADDR, chData);
//		 return 1;
//	}
//	return 0;
//}


/******************************************************
//读偏移数据

//*******************************************************/

//uchar ReadOffset()
//{
//	uint i=0;
//	uchar temp;
//	temp
//	if(IapReadByte(OFFSET_ADDR)==0xff)
//	{
//		return 0;
//	}
//	return 0;
//}	 



