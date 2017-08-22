	  
/*********************************************************/
//头文件
#include <intrins.h>
#include <string.h>
#include "STC15Fxxxx.h"
#include "Time.h"
#include "EEPROM.h"
#include "io.h"
#include "HYM8563.H"
#include "mfrc522.h"
#include "cc1101.h"
#include "api.h"

#define  BUFINLEN 90


//#define WRITE_TYPE 0x01
//#define READ_TYPE 0x02
//#define USER_TYPE 0x03
//#define MGRE_TYPE 0x04
//#define FUNC_TYPE 0x05

//#define SERI_TYPE 0x06 //序列号

#define IC_CMD_WRITE		0x01
#define IC_CMD_READ			0x02
#define IC_CMD_CUSTOMER		0x03
#define IC_CMD_MANAGER		0x04
#define IC_CMD_FUNC			0x05
#define IC_CMD_MODIFY_TIME	0x07
#define IC_CMD_GET_TIME		0x08
#define IC_CMD_AGENT		0x09
#define IC_CMD_PRODUCT		0x0A
#define IC_CMD_OFFSET		0x0B
#define IC_CMD_GETSERIAL	0x0C
#define IC_CMD_GET_CHECK	0x0D
#define IC_CMD_TEST			0x0E


#define STOP_PRODUCE_CMD 		0x00
#define START_PRODUCE_CMD 		0x01
#define ENABLE_PRODUCE_VERITY 	0x02
#define DISABLE_PRODUCE_VERITY 	0x03
#define WRITE_PRODUCE_PSW 		0x04
#define READ_PRODUCE_PSW 		0x05


#define FUNC_TYPE_FORBIDEN 		0x01
#define FUNC_TYPE_CHECK_TIME 	0x02
#define FUNC_TYPE_SWITCH 		0x03
#define FUNC_TYPE_OFFSET 		0x04
#define FUNC_TYPE_AGENT 		0x05
#define FUNC_TYPE_Check 		0x06
#define FUNC_TYPE_CLEARBLACKLIST 		0x07



sbit LED =P5^4;
sbit FMQ =P0^5;

#define FOSC  11059200L
#define BAUD  9600
#define TM	(65536-(FOSC/4/BAUD))

#define LEDOFF {LED=1;FMQ=0;}
#define LEDON {LED=0;FMQ=1;}

#define FMQON   {FMQ=1;}
#define FMQOFF  {FMQ=0;}


#define TIMEOUT           -1
#define TIMEOUT_ALL           5
#define CC1101            0X00
#define BT_UART           0X01
#define MSG_OPEN          0X01
#define MSG_CLOSE         0X02
#define MSG_OBTAIN_STATUS 0X03

#define READ		0x01
#define WRITE		0x02


unsigned char xdata sendnum;
unsigned char xdata cardtyp[2];
unsigned char xdata cardnum[4];
unsigned char xdata cardsize[1];
unsigned char xdata cardkey[6]			={0xff,0xff,0xff,0xff,0xff,0xff};//0x01,0x02,0x03,0x04,0x05,0x06
unsigned char xdata newkey[16]			={0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned char xdata card_new_key[16]	={0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
unsigned char xdata Password_Data[4] 	={0xff,0xff,0xff,0xff};

unsigned char xdata cardknum[16];
//unsigned char xdata cardwdata[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x17,0x15,0x16};
//unsigned char xdata cardwdata[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
//unsigned char xdata timere=0;
//unsigned char xdata timecard=510;
unsigned char xdata *p;

char xdata cardtypstu;
char xdata cardnumstu;
char xdata cardsizestu;
char xdata cardcheckstu;
char xdata cardknumstu;
char xdata cardwdatastu;

unsigned char xdata bufini=0,bufino;
unsigned char xdata maincmd[BUFINLEN];
unsigned char xdata bt_data[BUFINLEN];
unsigned int idata counter2=0;

bit  idata internal2=0;
unsigned char xdata g_chPackageFlag = 0; 
unsigned char xdata g_chOffsetSecton = 0;

unsigned char xdata g_chProduceFlag = 0;
unsigned char xdata g_chVerifyProduceFlag = 0;
unsigned char xdata g_chVerifyAgentFlag = 0;
unsigned char xdata g_chPasswordFlag = 0;
unsigned char xdata g_chReversCheckFlag = 0;
unsigned long xdata g_ulAgentID = 0xffffffff;
unsigned char xdata chAgentIDBuf[4];

uchar *pp2;
unsigned char xdata bt_buf[BUFINLEN];

void UART_init (void)
{
	//EA = 1; //允许总中断（如不使用中断，可用//屏蔽）
	
 	SCON=0x50;
	
//	S2CON=0x50; 		//8位数据,可变波特率
//	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	
	T2L = TM;		//设定定时初值
	T2H = TM>>8;		//设定定时初值
	
	//RL_T2H=0XAA;
	//RL_T2L=0XFA;
	
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
//	AUXR |= 0x10;		//启动定时器2 
//	IE2 |= 1; //允许UART2串口的中断
	
	ES = 1; //允许UART1串口的中断
}
void Send(uchar *str,uint len)
{
	pp2 = str;
	counter2 = len;
	internal2 = 1;
	SBUF = *pp2++;
	while(internal2); 
}


void Beep(void)
{
	FMQ=1;
	Delay1();
	Delay1();
	Delay1();
	FMQ=0;
	Delay1();
	Delay1();
	Delay1();
}

void Flash()
{
	LED = 1;
	FMQ = 1;
	Delay1();
	Delay1();
	Delay1();
	FMQ = 0;
	LED = 0;
}

void Sounds(unsigned long uCount)
{
	uchar xdata i;
	for(i=0; i<uCount; i++){
		Beep();		
		}
}


//void LongBeep()
//{
//	unsigned char i;
//	FMQON
//	for(i = 0; i < 255; i++)
//			Delay1();
//	FMQOFF
//}

void MakeResult(uchar errOkFlag)
{
	if(errOkFlag == Do_True)
	{
		 maincmd[0] = Do_True;
		 Flash();
	}
	else
	{
		 maincmd[0] = Do_False;
		 Sounds(2);
	}
}


//
/****************************************
函数功能:将bao中的数据组包到sendbao内存中

*****************************************/
void Make(unsigned char chType,unsigned int len,unsigned char *sendbao)
{
	uchar xdata i;
	uint xdata sum;

	uchar xdata bao[80];
	sum=0;

	for(i=0;i < len - 2;i++)		
	{
		bao[i] = sendbao[i];
	}
	sendbao[0] = 0xef;
	sendbao[1] = 0x01;

	sendbao[2] = chType;
	sendbao[3] = len >> 8;
	sendbao[4] = len & 0xFF;
	
	for(i=0;i < len - 2; i++)
	{
		sendbao[5+i] = bao[i];
		sum = sum+bao[i];
	}
	
	sum = sum + len + chType;
	
	sendbao[4 + len - 1] = sum >> 8;
	sendbao[4 + len] = sum & 0xFF;
}


/****************************************
函数功能：拷贝src内存的数据到 des内存内，拷贝大小为len

*****************************************/

//void memcopy(unsigned char *des,unsigned char *src,unsigned char len)
//{
//	unsigned char i ;
//	for(i=0;i<len;i++)
//	{
//		*des++=*src++;
//	}
//	if(len<16)
//	for(i=len;i<16;i++)
//		*des=0;	
//}


//获取卡的序列号
uchar GetCardSerial(uchar* ucSerial, uchar ucLength)
{
	uchar xdata ucRet = MI_ERR;
	if(ucLength < 4 || NULL == ucSerial)
		return Do_False;
	
	ucRet = PcdRequest(0x52, cardtyp);				//寻卡
	if(ucRet != MI_OK)
	{	
		ucRet = PcdRequest(0x52, cardtyp);
		if(ucRet != MI_OK)
		{
			return Do_False;
		}
	}	
	ucRet = PcdAnticoll(ucSerial);					//获取卡的卡号
	
	if(ucRet != MI_OK)
		return Do_False;
	return Do_True;
}


///////////////////////////////////////////////////////////////////////////////////////
///////////
///////////	计算每个扇区号与块号的对应关系,本处所用非绝对对地址块/////////////////////
///////////	入口:  每个扇区对应的块号,范围:块0~块3
//////////////////////////////////////////////////////////////////////////////////////


uchar GeneratePsw(void)     //密钥处理函数 一卡一密钥，不同扇区不密钥也不同
{
	uchar xdata i;
	uchar xdata ucRet = 0;
	uchar xdata ucCardSerial[4] = {0};

	for(i = 0; i < 4; i++)
		card_new_key[1 + i] = Password_Data[i];  //cardwdata 定义密钥暂存数组 长度6个字节  ，chData 存放序列号的，序列号为4个字节

	//card_new_key[0] = 0xFF;         	//这个值你可自己定义
	//card_new_key[5] = 0xFF;			//这个值是块号 ，即每个扇区的控制块号值是不同的 	
	
	memcpy(newkey,card_new_key,16);
	
	return Do_True;
}


uchar RecoverPsw()     //密钥处理函数 一卡一密钥，不同扇区不密钥也不同
{
	uchar xdata i;

	for(i = 0; i < 4; i++)
		card_new_key[1 + i] = 0xFF;  //cardwdata 定义密钥暂存数组 长度6个字节  ，chData 存放序列号的，序列号为4个字节

	//card_new_key[0] = 0xFF;         	//这个值你可自己定义
	//card_new_key[5] = 0xFF;			//这个值是块号 ，即每个扇区的控制块号值是不同的 	
	
	memcpy(newkey,card_new_key,16);
	
	return Do_True;
}

unsigned char GetCommand(unsigned char chType,unsigned char*bufino,unsigned char bufini)
{
	unsigned char xdata *combuf,*dat;
	unsigned char xdata i,j,len2,k;
	unsigned int xdata crc;
	
	if(chType == BT_UART)
	{
		combuf =bt_buf;
		dat =bt_data;
	}
	
	i = *bufino;
	
rescan1:
	if(bufini==i) 
		return 0;
	
	if((combuf[i++])!=0xef) 
	{
		if(i >= BUFINLEN) 
			i = 0;  
		*bufino = i; 
		goto rescan1;
	}
	if(i >= BUFINLEN) 
		i = 0;
	if(bufini == i) 
		return 0;
	if((combuf[i++])!=0x01) 
	{
		if(i >= BUFINLEN) 
			i = 0; 
		*bufino = i; 
		goto rescan1;
	}
	if(i >= BUFINLEN) 
		i=0;
	
	if(bufini == i) 
		return 0;
		
	g_chPackageFlag = combuf[i++];
	
	if(i >= BUFINLEN) 
		i = 0;
	
	if(bufini == i) 
		return 0;

	i++; 
	
	if(i >= BUFINLEN) 
		i=0;
	if(bufini==i) 
		return 0;

	len2=combuf[i++]; 
	
	if(i>=BUFINLEN) 
		i=0;
	if(bufini==i) 
		return 0;

//	len0=len1*256+len2;
	if(len2<=2||len2>=200) 
	{
		*bufino=i; 
		goto rescan1;
	} 

	crc = g_chPackageFlag + len2;
	j=0;
	
	while(len2-2)
	{
		if(bufini==i) 
			return 0;
		k = dat[j++] = combuf[i++];
		
		if(i >= BUFINLEN) 
			i=0;
		crc += k;
		len2--;
	}
	if(bufini == i) 
		return 0;
	crc -= (unsigned int) combuf[i++]*256;
	
	if(i>=BUFINLEN) 
		i=0;	
	if(bufini == i) 
		return 0;
	
	crc -= combuf[i++];
	
	if(i >= BUFINLEN) 
		i = 0;

	if(crc) 
	{
		*bufino=i; 
		//Sounds(2);
		//maincmd[0] = crc % 255;
		//Make(9,4,maincmd);
		//Send(maincmd, 9);
		goto rescan1;
	}
	else
	{
		*bufino=i; 
		return 1;
	}
}


/****************************************
函数功能:
	读功能卡，将数据保存到maincmd中
描述:

读卡扇区0~~~~7中的数据，
并报数据保存到maincmd 中
返回值:	0 失败
			1 成功
*****************************************/

uchar ReadFuntionCard(uchar chOffset)
{	
	uchar xdata temp[16];
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_0 + chOffset,temp))
		return Do_False;

	memcpy(maincmd+2,temp,11);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_1 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 13,temp,12);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_2 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 25,temp,2);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_3 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 27,temp,1);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_4 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 28,temp,16);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_5 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 44,temp,16);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_6 + chOffset,temp))
		return Do_False;

	memcpy(maincmd + 60,temp,8);
	if(MI_RD_OK != readDataFromIc(newkey,SECTION_7 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 68,temp,5);
	return Do_True;
}


/****************************************
函数功能:
	写功能卡
描述:

写卡扇区0~~~~7中的数据，
并报数据保存到maincmd 中
返回值:	0 失败
			1 成功
*****************************************/
uchar WriteFunctionCard(uchar chOffset)
{
	uchar xdata temp[16];
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 1,11);	
	if(writeDataToIc(newkey,SECTION_0 + chOffset,temp)  !=  MI_WR_OK)	
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 12,12);
	if(writeDataToIc(newkey,SECTION_1 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 24,2);
	if(writeDataToIc(newkey,SECTION_2 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 26,1);
	if(writeDataToIc(newkey,SECTION_3 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 27,16);
	if(writeDataToIc(newkey,SECTION_4 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 43,16);
	if(writeDataToIc(newkey,SECTION_5 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 59,8);
	if(writeDataToIc(newkey,SECTION_6 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 67,5);
	if(writeDataToIc(newkey,SECTION_7 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	return  Do_True;
}

uchar WriteOffsetPswCard()
{
	uchar xdata temp[16] = {0};
	memcpy(temp,bt_data + 1,11);	
	if(writeDataToIc(newkey,SECTION_0,temp)  !=  MI_WR_OK)	
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 12,12);
	
	if(g_ulAgentID != 0xFFFFFFFF)
	{
		temp[3] = (g_ulAgentID >> 0x24) & 0xFF;
		temp[4] = (g_ulAgentID >> 0x16) & 0xFF;
		temp[5] = (g_ulAgentID >> 0x8) & 0xFF;
		temp[6] = g_ulAgentID & 0xFF;
	}
	
	if(writeDataToIc(newkey,SECTION_1,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 24,2);
	if(writeDataToIc(newkey,SECTION_2,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 26,1);
	if(writeDataToIc(newkey,SECTION_3,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 27,16);
	if(writeDataToIc(newkey,SECTION_4,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 43,16);
	if(writeDataToIc(newkey,SECTION_5,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 59,8);
	if(writeDataToIc(newkey,SECTION_6,temp)  !=  MI_WR_OK)
		return Do_False;
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 67,5);
	if(writeDataToIc(newkey,SECTION_7,temp)  !=  MI_WR_OK)
		return Do_False;
	return  Do_True;
}

///****************************************
//函数功能：
//读卡扇区0~~~~5中的数据，
//并报数据保存到maincmd 中
//返回值:	0 失败
//			1 成功
//*****************************************/


uchar ReadUserCard(unsigned char chOffset)
{
	uchar xdata temp[16];
	uchar i = 0;
	memset(maincmd, 0, BUFINLEN);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_0 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 2, temp, 11);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_1 + chOffset,temp))
		return Do_False;
	
	for(i = 2; i < 12; i++ )
		temp[i] = temp[i] - i;
	
	memcpy(maincmd + 13, temp, 12);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_2 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 25, temp, 2);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_3 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 27, temp, 9);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_4 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 36, temp, 9);
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_5 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 45, temp, 9);
	
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_6 + chOffset,temp))
		return Do_False;
	memcpy(maincmd + 54, temp, 13);
	//errOkFlag = 1;
	return Do_True;
}


uchar WriteUserCard(uchar chOffset)
{	
	uchar xdata temp[16];
	uchar i = 0;
	
	memcpy(temp, bt_data + 1,11);
	if(writeDataToIc(newkey,SECTION_0 + chOffset,temp) != MI_WR_OK)	
		return Do_False;

	memcpy(temp,bt_data + 12,12);

	for(i = 2; i < 12; i++ )
		temp[i] = temp[i] + i;
	if(writeDataToIc(newkey,SECTION_1 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcpy(temp,bt_data + 24,2);
	
	if(writeDataToIc(newkey,SECTION_2 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memset(temp, 0, 16);
	memcpy(temp,bt_data + 26,9);
	if(writeDataToIc(newkey,SECTION_3 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memset(temp, 0, 16);
	memcpy(temp,bt_data + 35,9);
	if(writeDataToIc(newkey,SECTION_4 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memset(temp, 0, 16);
	memcpy(temp,bt_data + 44,9);
	if(writeDataToIc(newkey,SECTION_5 + chOffset,temp) != MI_WR_OK)
		return Do_False;
	
	memset(temp, 0, 16);
	memcpy(temp,bt_data + 53,13);
	if(writeDataToIc(newkey,SECTION_6 + chOffset,temp) != MI_WR_OK)
		return Do_False;
	return  Do_True;
}




//uchar ReadOffset()
//{
//	uchar ucData = 0;
//	ucData = IapReadByte(OFFSET_ADDR);
// 	if(ucData == 0xff)
//		return 0;
// 	return ucData;
//}

//uchar WriteOffset(uchar chOffset)
//{
//	int i=0;
//	uchar ucData = 0;
//	IapEraseSector(OFFSET_ADDR);
//	for(i=0; i<512; i++){
//		ucData = IapReadByte(OFFSET_ADDR);
//		if(ucData != 0xFF)
//			return Do_False;
//	}
//	IapProgramByte(OFFSET_ADDR, chOffset);
//	return Do_True;
//}


void WriteFrcCardPsw(uchar ucOffset)
{
	uchar xdata uIndexArea = 0;
	uchar xdata ucRet[3] = {0,0,0};
	uchar xdata uSection = ucOffset + SECTION_46;
	uchar xdata i = 0;
	uchar xdata iSectionCount = 3;

	
	GeneratePsw();
	//计算扇区索引
	uIndexArea = CalcAreaofSection(uSection);

	if(g_chReversCheckFlag == DO_REVERSE)
		iSectionCount = 8;
	
	for(i = 0; i < iSectionCount; i++)
		writePassword(cardkey, uIndexArea + i, card_new_key);
}



void ClearFrcCardPsw(uchar ucOffset)
{
	uchar xdata uIndexArea = 0;
	uchar xdata uSection = ucOffset + SECTION_46;
	uchar xdata i = 0;
	uchar xdata ucPsw[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

	uchar xdata ucCardSerial[4] = {0};

	uchar xdata ucRet = GetCardSerial(ucCardSerial, 4);;
	
	if(ucRet != Do_True)
		return;
	
	if(cardnum[0] == ucCardSerial[0] 
		&& cardnum[1] == ucCardSerial[1] 
		&& cardnum[2] == ucCardSerial[2] 
		&& cardnum[3] == ucCardSerial[3] )
		return;	

	
	//计算扇区索引
	uIndexArea = CalcAreaofSection(uSection);
	
	for(i = 0; i < 3; i++)
	{
		writePassword(cardkey, uIndexArea + i, ucPsw);
	}
	
	memcpy(cardnum, ucCardSerial, 4);

	
	Sounds(1);
}


unsigned char WriteProductCode(uchar ucOffset)
{
	uchar xdata ucRet = MI_ERR;	
	uchar xdata uIndexArea = 0;
	
	uchar xdata chProductCode[16]={0x01, 0x02, 0x03, 0x04, 0x05, 
											0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 
											0x12, 0x13, 0x17, 0x15, 0x16};
	uchar xdata ucCardSerial[4] = {0};
	uchar xdata i = 0;

	ucRet = GetCardSerial(ucCardSerial, 4);
	
	if(ucRet != Do_True)
		return Do_False;
	
	if(cardnum[0] == ucCardSerial[0] 
		&& cardnum[1] == ucCardSerial[1] 
		&& cardnum[2] == ucCardSerial[2] 
		&& cardnum[3] == ucCardSerial[3] )
		return Do_True;	
	
	
	if(g_chPasswordFlag == DO_PASSWORD)
		WriteFrcCardPsw(ucOffset);	
	
	//计算生产数据
	chProductCode[14] = ucCardSerial[2];
	chProductCode[15] = ucCardSerial[3];
	
	chProductCode[4] = 0xA0;

	chProductCode[5] = ucCardSerial[0];
	chProductCode[6] = ucCardSerial[1];
	chProductCode[7] = ucCardSerial[2];
	chProductCode[8] = ucCardSerial[3];
	//写生产数值
	//ucRet = writeDataToIc(card_new_key, SECTION_46 + ucOffset, chProductCode);
	//使用新密码校验
	if(g_chPasswordFlag == DO_PASSWORD)
		ucRet = writeDataToIc(card_new_key, SECTION_46 + ucOffset, chProductCode);
	else
		ucRet = writeDataToIc(cardkey, SECTION_46 + ucOffset, chProductCode);
	
	if(ucRet == MI_WR_OK)
	{	
		memcpy(cardnum, ucCardSerial, 4);

		Sounds(1);
		
		maincmd[0] = 0x01;
		maincmd[1] = 0x10;
		Make(IC_CMD_PRODUCT, 4,maincmd);
		Send(maincmd, 9);
				
		return Do_True;
	}
	
	Sounds(2);
	return Do_False;
}


unsigned char WriteAgentIDToCard(uchar ucOffset)
{
	uchar ucRet = MI_ERR;	
	uchar xdata ucCardSerial[4] = {0};
	unsigned char xdata temp[16]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_46 + ucOffset,temp))
		//return Do_False;
		return 3;
	
	ucRet = GetCardSerial(ucCardSerial, 4);					//获取卡的卡号
	
	if(ucRet != Do_True)
		//return Do_False;	
		return 4;
	
	temp[0] = (g_ulAgentID >> 24 ) & 0xFF;
	temp[1] = (g_ulAgentID >> 16 ) & 0xFF;
	temp[2] = (g_ulAgentID >> 8 ) & 0xFF;
	temp[3] = g_ulAgentID  & 0xFF;
	
		
	temp[4] = 0xA0;
	
	temp[5] = ucCardSerial[0];
	temp[6] = ucCardSerial[1];
	temp[7] = ucCardSerial[2];
	temp[8] = ucCardSerial[3];
	
	//写生产数值
	ucRet = writeDataToIc(newkey, SECTION_46 + ucOffset, temp);
	
	if(ucRet != MI_WR_OK)
		//return Do_False;
		return 5;
	
	return Do_True;
}


//uchar GetVersion()
//{
//	uchar ucRet = MI_ERR;
//	memset(cardknum, 0, 16);
//	//读生产数值
//	ucRet = readDataFromIc(newkey, SECTION_46, cardknum);
//	
//	if(ucRet != MI_RD_OK)
//		return 0;
//	
//	return cardknum[4];
//}

//uchar WriteSerial(uchar ucOffset)
//{
//	uchar xdata ucRet = 0;
//	uchar xdata ucCardSerial[4];
//	uchar xdata ucTemp[16];

//	ucRet = readDataFromIc(newkey, SECTION_46 + ucOffset, ucTemp);
//	if(MI_RD_OK != ucRet)
//		return Do_False;
//		
//	ucRet = PcdAnticoll(ucCardSerial);					//获取卡的卡号
//	
//	if(ucRet != MI_OK)
//		return Do_False;	
//		
//	ucTemp[4] = 0xA0;
//	
//	ucTemp[5] = ucCardSerial[0];
//	ucTemp[6] = ucCardSerial[1];
//	ucTemp[7] = ucCardSerial[2];
//	ucTemp[8] = ucCardSerial[3];
//	//写生产数值
//	ucRet = writeDataToIc(newkey, SECTION_46 + ucOffset, ucTemp);
//	
//	if(ucRet == MI_WR_OK)
//		return Do_True;
//	return Do_False;
//}

// 校验生产码
unsigned char VerifyProduceCode(uchar ucOffset)
{
	uchar ucRet = MI_RD_OK;
	char cRet = MI_OK;

//	cRet = PcdRequest(0x52, cardtyp);				//寻卡
//	if(cRet != MI_OK)
//	{
//		cRet = PcdRequest(0x52, cardtyp);
//		if(cRet != MI_OK)
//			return 3;
//	}
//	
//	cRet = PcdAnticoll(cardnum);					//获取卡的卡号

	cRet = GetCardSerial(cardnum ,4);
	
	if(cRet != Do_True)
		return 4;
	
	memset(cardknum, 0, 16);
	//读生产数值
	ucRet = readDataFromIc(newkey, SECTION_46 + ucOffset, cardknum);
	
	if(ucRet != MI_RD_OK)
		return 5;
	
	if(cardknum[14] == cardnum[2] 
		&& cardknum[15] == cardnum[3])
		return Do_True;
	//Sounds(3);

	memcpy(maincmd, cardknum, 16);
	maincmd[16] = ucOffset;
		
	return 6;
}


unsigned char ReadInterParam(uchar* pBuf)
{	
	unsigned char xdata temp[32];
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_16,temp))	
		return Do_False;
	memcpy(pBuf, temp, 16);
	
	if(MI_RD_OK  !=  readDataFromIc(newkey,SECTION_16 + 1,temp))	
		return Do_False;
	
	memcpy(pBuf + 16, temp, 16);
	
	return Do_True;
}


//unsigned char RecordInterParam(uchar chOffset)
//{	
//	unsigned char xdata temp[16];
//	unsigned char xdata tmData[7];
//	//数据偏移量
//	temp[0] = chOffset;
//	//启用代理商检验
//	temp[1] = g_ucAgentVerifyFlag;

//	//代理商ID
//	temp[2] = (g_ulAgentID >> 24) & 0xFF;
//	temp[3] = (g_ulAgentID >> 16) & 0xFF;
//	temp[4] = (g_ulAgentID >> 8) & 0xFF;
//	temp[5] = g_ulAgentID & 0xFF;

//	//电梯号
//	temp[6] = GetElevatorID();
//	//电梯时间
//	readtime(tmData);
//	temp[7] = tmData[0];
//	temp[8] = tmData[1];
//	temp[9] = tmData[2];
//	temp[10] = tmData[3];
//	temp[11] = tmData[4];
//	temp[12] = tmData[5];
//	temp[13] = tmData[6];
//	temp[14] = tmData[7];
//	
//	if(writeDataToIc(card_new_key,SECTION_0 + chOffset + 1,temp) != MI_WR_OK)	
//		return Do_False;

//	return  Do_True;
//}


//void DeodeFrcCard(void)
//{

//}

/****************************************
函数功能：解析从串口接收到的数据

*****************************************/
void ScanCommand()
{
	uchar i=0,j=0;
	uchar errOkFlag=0;
	uchar ErrAgentCard = 0;
	uchar ErrWriteSerial = Do_False; 
	uchar ucPswFlag = DIS_PASSWORD;
	if(1 != GetCommand(BT_UART,&bufino,bufini))
	{
		return;
	}
	
	switch(g_chPackageFlag)
	{
	case(IC_CMD_WRITE):         //写
		if(bt_data[0] == WRITE)
		{
			j=0;
			maincmd[0]=0;
			for(i=0;i<16;i++)
			{
				maincmd[i+1]=0;
				if(writePassword(cardkey,i,newkey)!=MI_WR_OK)
				{
					maincmd[i + 1]=1;
					maincmd[0]=1;
				}
			}
			Make(1,19,maincmd);
			Send(maincmd,24);	
		}
		break;
	case(IC_CMD_READ): 
	
		if(g_chPasswordFlag == DO_PASSWORD)
			GeneratePsw();
		for(i=0;i<47;i++)
		{
			if(MI_RD_OK == readDataFromIc(newkey,i,cardknum))
			{	
				Send(cardknum,16);
			} 
		}
		if(g_chPasswordFlag == DO_PASSWORD)
			RecoverPsw();
			
		break;
	case(IC_CMD_CUSTOMER):	  //上位机写业主卡信息
		errOkFlag=0;
		if(bt_data[0] == READ)
		{
		
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();
			//读用户数据
			errOkFlag = ReadUserCard(g_chOffsetSecton);	
			
			if(g_chPasswordFlag == DO_PASSWORD)
				RecoverPsw();
			
			MakeResult(errOkFlag);			
			maincmd[1] = READ;
			Make(IC_CMD_CUSTOMER,66,maincmd);
			Send(maincmd,71); 
		}
		
		else if(bt_data[0] == WRITE)
		{ 	
			if(g_chVerifyProduceFlag == DO_VERIFY)
			{				
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();
				
				maincmd[2] = VerifyProduceCode(g_chOffsetSecton);
				
				if(g_chPasswordFlag == DO_PASSWORD)
					RecoverPsw();
				
				if(Do_True != maincmd[2])
				{
					maincmd[0] = g_chVerifyProduceFlag;
					maincmd[1] = WRITE;

					maincmd[3] = 0xFA;
					maincmd[4] = 0xFA;
					maincmd[5] = g_chOffsetSecton;
					
					Make(IC_CMD_CUSTOMER, 7, maincmd);
					Send(maincmd, 12);
					Sounds(2);
					return;
				}
			}
			
			//构建密码
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();

			//写用户数据	
			errOkFlag = WriteUserCard(g_chOffsetSecton);			
			ErrAgentCard = WriteAgentIDToCard(g_chOffsetSecton);
			//ErrWriteSerial = WriteSerial(g_chOffsetSecton);
			
			//恢复密码
			if(g_chPasswordFlag == DO_PASSWORD)
				RecoverPsw();
			
			MakeResult(errOkFlag);
			maincmd[1] = WRITE;
			maincmd[2] = ErrAgentCard;
			maincmd[3] = ErrWriteSerial;
			maincmd[4] = g_chOffsetSecton;
			
			Make(IC_CMD_CUSTOMER, 7, maincmd);
			Send(maincmd, 12);
		}
		break;		
	case(IC_CMD_MANAGER):	  //上位机读写管理员卡
		errOkFlag=0;
		//读管理员卡
		if(bt_data[0] == READ)
		{
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();

			errOkFlag = ReadUserCard(g_chOffsetSecton);

			if(g_chPasswordFlag == DO_PASSWORD)
				RecoverPsw();
			
			MakeResult(errOkFlag);
			maincmd[1] = READ;
			Make(IC_CMD_MANAGER, 66, maincmd);
			Send(maincmd,71); 
		}
		//写管理员卡
		else if(bt_data[0] == WRITE)
		{
			if(g_chVerifyProduceFlag == DO_VERIFY)
			{
				
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();
				
				maincmd[2] = VerifyProduceCode(g_chOffsetSecton);
				
				if(g_chPasswordFlag == DO_PASSWORD)
					RecoverPsw();
				
				if(Do_True != maincmd[2])
				{
					maincmd[0] = g_chVerifyProduceFlag;
					maincmd[1] = WRITE;

					maincmd[3] = 0xFA;
					maincmd[4] = 0xFA;
					
					Make(IC_CMD_MANAGER, 7, maincmd);
					Send(maincmd, 12);
					Sounds(2);
					return;
				}
			}
		
			//构建密码
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();
			
			errOkFlag = WriteUserCard(g_chOffsetSecton);
			ErrAgentCard = WriteAgentIDToCard(g_chOffsetSecton);
			//ErrWriteSerial = WriteSerial(g_chOffsetSecton);
			
			//恢复密码
			if(g_chPasswordFlag == DO_PASSWORD)
				RecoverPsw();

			MakeResult(errOkFlag);
			maincmd[1] = WRITE;
			maincmd[2] = ErrAgentCard;
			maincmd[3] = ErrWriteSerial;
			Make(IC_CMD_MANAGER, 6, maincmd);
			Send(maincmd, 11);
		}		
		break;
	case(IC_CMD_FUNC):	  //上位机读写功能卡
		errOkFlag=0;
		//读功能卡
		if(bt_data[0] == READ)
		{
			errOkFlag = ReadFuntionCard(g_chOffsetSecton);
			MakeResult(errOkFlag);
			maincmd[1] = READ;
			Make(IC_CMD_FUNC,75,maincmd);
			Send(maincmd,80);
			
		}
		//写功能卡
		else if(bt_data[0] == WRITE)
		{
			if(bt_data[6] == FUNC_TYPE_OFFSET)
			{				
				RecoverPsw();				
				
				errOkFlag = WriteOffsetPswCard();			
				ErrAgentCard = WriteAgentIDToCard(0);
				//ErrWriteSerial = WriteSerial(0);
					
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();				
			}
			else if(bt_data[6] == FUNC_TYPE_Check)
			{	
				RecoverPsw();
								
				errOkFlag = WriteFunctionCard(g_chOffsetSecton);			
				ErrAgentCard = WriteAgentIDToCard(g_chOffsetSecton);
				
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();				
			}
			else
			{			
				//构建密码	
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();
				
				errOkFlag = WriteFunctionCard(g_chOffsetSecton);			
				ErrAgentCard = WriteAgentIDToCard(g_chOffsetSecton);
				
				//恢复密码
				if(g_chPasswordFlag == DO_PASSWORD)
					RecoverPsw();	
			}
			
			MakeResult(errOkFlag);
			maincmd[1] = WRITE;
			maincmd[2] = ErrAgentCard;
			maincmd[3] = ErrWriteSerial;
			Make(IC_CMD_FUNC,5,maincmd);
			Send(maincmd,10);
		}				
		break;
	case(IC_CMD_MODIFY_TIME):
		break;
	case(IC_CMD_GET_TIME):
		break;
	case(IC_CMD_AGENT):
		errOkFlag = 0;
		if(bt_data[0] == READ)
		{
			g_ulAgentID = ReadAgentID();
			MakeResult(Do_True);
			maincmd[1] = READ;
			maincmd[2] = (g_ulAgentID >> 24) & 0xff;
			maincmd[3] = (g_ulAgentID >> 16) & 0xff;
			maincmd[4] = (g_ulAgentID >> 8) & 0xff;
			maincmd[5] = g_ulAgentID  & 0xff;	
			maincmd[6] = g_chProduceFlag;
			maincmd[7] = g_chReversCheckFlag;		
			Make(IC_CMD_AGENT, 10, maincmd);
			Send(maincmd, 15);
		}		
		if(bt_data[0] == WRITE)//写
		{
			chAgentIDBuf[0]  = bt_data[1];
			chAgentIDBuf[1]  = bt_data[2];
			chAgentIDBuf[2]  = bt_data[3];
			chAgentIDBuf[3]  = bt_data[4];
			
			//errOkFlag = WriteAgentID(chAgentIDBuf);
			g_ulAgentID = ReadAgentID();
			//ErrWriteSerial = WriteSerial(g_chOffsetSecton);
			MakeResult(errOkFlag);
			maincmd[0] = Do_True;			
			maincmd[1] = WRITE;
			maincmd[2] = (g_ulAgentID >> 24) & 0xff;
			maincmd[3] = (g_ulAgentID >> 16) & 0xff;
			maincmd[4] = (g_ulAgentID >> 8) & 0xff;
			maincmd[5] = g_ulAgentID  & 0xff;
			maincmd[6] = ErrWriteSerial;						

			Make(IC_CMD_AGENT,9,maincmd);
			Send(maincmd,14);
		}
		break;
	case(IC_CMD_PRODUCT):
		maincmd[0] = Do_False;
		if(bt_data[0] == START_PRODUCE_CMD)
		{
			g_chProduceFlag = bt_data[1] + bt_data[2];	
			MakeResult(Do_True);
			if(0xFF == g_chProduceFlag)
				Sounds(2);
			else if(0xAA == g_chProduceFlag)
			{
				Sounds(1);
				delay_10ms(1000);
				delay_10ms(1000);
				delay_10ms(1000);
				delay_10ms(1000);
				Sounds(1);				
			}
			maincmd[1] = g_chProduceFlag;
			maincmd[2] = g_chProduceFlag;
			Make(IC_CMD_PRODUCT, 5, maincmd);
			Send(maincmd, 10);
		}
		else if(bt_data[0] == STOP_PRODUCE_CMD)
		{
			g_chProduceFlag = 0x00;
			maincmd[0] = Do_True;
			maincmd[1] = 0;
			maincmd[2] = 0;
			Sounds(1);
			Make(IC_CMD_PRODUCT, 5, maincmd);
			Send(maincmd, 10);
		}
		else if(bt_data[0] == ENABLE_PRODUCE_VERITY)
		{
			maincmd[0] = WriteVerifyProduceFlag(0x01);
			maincmd[1] = 0;
			maincmd[2] = 0;
			g_chVerifyProduceFlag = DO_VERIFY;
			Sounds(1);
			Make(IC_CMD_PRODUCT, 5, maincmd);
			Send(maincmd, 10);
		}
		else if(bt_data[0] == DISABLE_PRODUCE_VERITY)
		{
			maincmd[0] = WriteVerifyProduceFlag(0xFF);
			maincmd[1] = 0;
			maincmd[2] = 0;
			g_chVerifyProduceFlag = DIS_VERIFY;
			Sounds(1);
			Make(IC_CMD_PRODUCT, 5, maincmd);
			Send(maincmd, 10);
		}
		else if(bt_data[0] == WRITE_PRODUCE_PSW)
		{
			memcpy(Password_Data, bt_data + 1, 4);
			
			maincmd[0] = WRITE_PRODUCE_PSW;
			//maincmd[1] = WriteSectionPsw(Password_Data);
			memcpy(maincmd + 2, Password_Data, 4);
			ReadSectionPsw(Password_Data);
			memcpy(maincmd + 6, Password_Data, 4);
			Sounds(1);
			Make(IC_CMD_PRODUCT, 12, maincmd);
			Send(maincmd, 17);
		}		
		else if(bt_data[0] == READ_PRODUCE_PSW)
		{
			maincmd[0] = READ_PRODUCE_PSW;
			ReadSectionPsw(Password_Data);		
			memcpy(maincmd + 1, Password_Data, 4);
			maincmd[5] = g_chPasswordFlag;
			Sounds(1);
			Make(IC_CMD_PRODUCT, 8, maincmd);
			Send(maincmd, 13);
		}
		break;
	case(IC_CMD_OFFSET):
		errOkFlag = 0;
		if(bt_data[0] == READ)
		{  
			maincmd[0] = TRUE;
			maincmd[1] = READ;
			maincmd[2] = ReadOffset();
			
			Make(IC_CMD_OFFSET,5,maincmd);
			Send(maincmd,10);
		}
		if(bt_data[0] == WRITE)//写
		{					
			memcpy(maincmd, bt_data + 1, 14);
			WriteFlagDatas(maincmd,14);
						
//			WriteOffset(bt_data[1]);
//			WritePasswordFlag(bt_data[2]);
//			WriteSectionPsw(bt_data + 4);	
//			WriteAgentID(bt_data + 8);
//			ErrWriteSerial = WriteSerial(g_chOffsetSecton);	
			
			MakeResult(Do_True);
			maincmd[1] = WRITE;
			maincmd[2] = ReadOffset();
			maincmd[3] = ErrWriteSerial;
			
			Make(IC_CMD_OFFSET,6,maincmd);
			Send(maincmd,11);
			
			//Sounds(g_chOffsetSecton);
		}		
		Sounds(1);
		break;
	case(IC_CMD_GETSERIAL):
		errOkFlag=0;
		memset(maincmd, 0, 10);
		errOkFlag = GetCardSerial(bt_data, 4);
		MakeResult(errOkFlag);
		maincmd[1] = IC_CMD_GETSERIAL;		
		memcpy(maincmd + 2, bt_data, 4);
		Make(IC_CMD_GETSERIAL, 8, maincmd);
		Send(maincmd, 13);
		break;
		
	case(IC_CMD_GET_CHECK):
		errOkFlag=0;
		memset(maincmd, 0, BUFINLEN);
		
		if(g_chPasswordFlag == DO_PASSWORD)
			RecoverPsw();
		
		errOkFlag = ReadInterParam(bt_data);
		
		if(g_chPasswordFlag == DO_PASSWORD)
			GeneratePsw();
		
		MakeResult(errOkFlag);
		maincmd[1] = IC_CMD_GET_CHECK;		
		memcpy(maincmd + 2, bt_data, 32);
		Make(IC_CMD_GET_CHECK, 34, maincmd);
		Send(maincmd, 39);
		break;
	
	case(IC_CMD_TEST):
		Sounds(1);
		if(bt_data[0] == 0x01)
		{
			for(i=1; i<6; i++)
				maincmd[i] = 0xEE;
			maincmd[0] = Do_True;
			Make(IC_CMD_TEST, 9,maincmd);
			Send(maincmd, 14);
			
		}
		break;		
	}
}

void Uart1(void) interrupt 4 using 2
{  
	if(RI)
	{
		SCON =SCON & 0xfe;
		
		bt_buf[bufini++]=SBUF;
		
		if (bufini>=BUFINLEN) 
			bufini=0;
	}
	else if(TI)
	{
		SCON =SCON & 0xFd;
		
		if(internal2)
		{
			if(!(--counter2))
				internal2=0; 
			else 
				SBUF=*pp2++;//SBUF=XBYTE[pn++];
		}
	}
}
void Uart2(void) interrupt 8 using 2
{  
//	xmtime=0;
	
	if(RI2)
	{
		S2CON =S2CON & 0xfe;
		
		bt_buf[bufini++]=S2BUF;
			
		if (bufini>=BUFINLEN) 
			bufini=0;
	}
	else if(TI2)
	{
		S2CON =S2CON & 0xFd;
		
		if(internal2)
		{
			if(!(--counter2))
				internal2=0; 
			else 
				S2BUF=*pp2++;//SBUF=XBYTE[pn++];
		}		
	}
}
//系统主函数
void main (void)
{
	unsigned int look_status_time=0;
	unsigned int test=0;
	Time_init();	  //两个定时器初始化
	UART_init() ;
	EA=1;
	//IapProgramByte(0, 45);
	PcdReset();
	//关闭天线
	PcdAntennaOff();
	//打开天线
	PcdAntennaOn();  
	//设置工作方式
	M500PcdConfigISOType( 'A' );
	//halRfReceivePacket(RxBuf, &leng) ;
	LEDON
	
	Delay1();
	P0M1&=0XDF;
	P0M0|=0X20;
	
	Sounds(1);	
	g_chOffsetSecton = ReadOffset();

	g_chVerifyProduceFlag = ReadVerifyProduceFlag();

	g_ulAgentID = ReadAgentID();

	ReadSectionPsw(Password_Data);

	g_chPasswordFlag = ReadPasswordFlag();
	g_chReversCheckFlag = ReadReverseCheckFlag();
	
	maincmd[0] = g_chOffsetSecton;
	maincmd[1] = g_chVerifyProduceFlag;
	
	maincmd[2] = (g_ulAgentID >> 24) & 0xff;
	maincmd[3] = (g_ulAgentID >> 16) & 0xff;
	maincmd[4] = (g_ulAgentID >> 8) & 0xff;
	maincmd[5] = g_ulAgentID & 0xff;

	maincmd[6] = Password_Data[0];
	maincmd[7] = Password_Data[1];
	maincmd[8] = Password_Data[2];
	maincmd[9] = Password_Data[3];
	
	maincmd[10] = g_chReversCheckFlag;
	
	Make(0xFC, 13, maincmd);
	Send(maincmd, 18);
	
	ReadFlagDatas(maincmd);
	Make(0xFC,18,maincmd);
	Send(maincmd,23);
		
	if(g_chPasswordFlag == DO_PASSWORD)
	{
		GeneratePsw();
		
		memcpy(maincmd,newkey,16);
		Make(0xF9,18,maincmd);
		Send(maincmd,23); 
	}
	
	while(TRUE)
	{ 
		if(bufini != bufino) 
			ScanCommand();
		
		if(g_chProduceFlag == 0xFF)
			WriteProductCode(g_chOffsetSecton);		
		
		else if(g_chProduceFlag == 0xAA)
			ClearFrcCardPsw(g_chOffsetSecton);	
	}
}


