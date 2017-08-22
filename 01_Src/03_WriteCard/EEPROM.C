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

/*----------------------------
软件延时
----------------------------*/
void Delay1() //延时程序
{
    uint i;
    uint d=10;
    while (d--)
    {
        i=1000;
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
		lAgentID = (datas[0] << 24) + (datas[1] << 16) + (datas[2] << 8) + datas[3];
	}
	return lAgentID;
}


//uchar WriteAgentID(uchar datas[])
//{	
//	//unsigned long ulData = 0;
//	uchar temp[16] = {0};
//	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

//	temp[2] = datas[0];
//	temp[3] = datas[1];
//	temp[4] = datas[2];
//	temp[5] = datas[3];
//	IapEraseSector(DEVICE_STATUS_ADDR);
//	
//	IapProgramBytes(DEVICE_STATUS_ADDR, temp, 16);

//	IapReadBytes(AGENT_ADDR, temp, 4);

//	if(temp[0] == datas[0] 
//		&& temp[1] == datas[1] 
//		&& temp[2] == datas[2] 
//		&& temp[3] == datas[3])
//		
//		return Do_True;
//	
//	return Do_False;
//}

uchar ReadVerifyProduceFlag(void)
{
	uchar temp = 0;
	temp = IapReadByte(VERIFY_PRODUCE_ADDR);
	if(0x01 == temp)
		return DO_VERIFY;
	else
		return DIS_VERIFY;
}
uchar WriteVerifyProduceFlag(uchar ucData)
{
	uchar ucFlag;
	uchar xdata temp[16] = {0};
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	temp[VERIFY_PRODUCE_ADDR] = ucData;
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(DEVICE_STATUS_ADDR, temp, 16);
	
	ucFlag = IapReadByte(VERIFY_PRODUCE_ADDR);

	if(ucFlag == ucData )		
		return Do_True;
	
	return Do_False;
}



uchar ReadOffset()
{
	uchar ucData = 0;
	ucData = IapReadByte(OFFSET_ADDR);
 	if(ucData == 0xff)
		return 0;
 	return ucData;
}

void ReadSectionPsw(uchar* pdatas)
{	
	IapReadBytes(PSW_DATA_ADDR, pdatas, 4);
}

uchar ReadPasswordFlag(void)
{
	uchar chFlag = 0;
	chFlag = IapReadByte(OFFSET_FLAG_ADDR);
	if(chFlag  == 1)
		return DO_PASSWORD;
	return DIS_PASSWORD;
}

uchar WriteFlagDatas(uchar* pdatas, uint uLen)
{
	uchar temp[16] = {0};
	
	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

	memcpy(temp + 1,pdatas, uLen);
		
	IapEraseSector(DEVICE_STATUS_ADDR);
	
	IapProgramBytes(DEVICE_STATUS_ADDR, temp, 16);

	memcpy(pdatas, temp + 1, uLen);
	
	return Do_True;
}

uchar ReadFlagDatas(uchar* ucDatas)
{
	IapReadBytes(DEVICE_STATUS_ADDR, ucDatas, 16);
	
	return Do_True;
}

uchar ReadReverseCheckFlag(void)
{
	uchar chFlag = 0;
	chFlag = IapReadByte(REVERSE_FLAG_ADDR);
	if(chFlag == 1)
		return DO_REVERSE;
	return DIS_REVERSE;
}

//uchar ReadVerifyAgentFlag(void)
//{
//	char temp = 0;
//	temp = IapReadByte(VERIFY_AGENT_FLAG_ADDR);
//	if(temp == 0xff)
//		return DIS_VERIFY_AGENT;
//	else
//		return DO_VERIFY_AGENT;
//}
//uchar WriteVerifyAgentFlag(uchar ucData)
//{
//	unsigned char ucFlag;
//	uchar temp[16] = {0};
//	IapReadBytes(DEVICE_STATUS_ADDR, temp, 16);

//	temp[VERIFY_AGENT_FLAG_ADDR] = ucData;
//	IapEraseSector(DEVICE_STATUS_ADDR);
//	
//	ucFlag = IapReadByte(VERIFY_AGENT_FLAG_ADDR);

//	if(ucFlag == ucData )
//		
//		return Do_True;
//	
//	return Do_False;
//}



