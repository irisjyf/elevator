
/*********************************************************/
//头文件
#include <intrins.h>
#include <string.h>
#include "STC15Fxxxx.h"
#include "Time.h"
#include "EEPROM.h"
#include "74HC595.H"
#include "HYM8563.H"
#include "mfrc522.h"

#define  BUFINLEN 50
sbit LED  = P2^2;
sbit fmq = P0^7;
sbit bt0  = P0^1;
sbit bt1  = P0^0;
sbit bt2  = P4^6;
sbit bt3  = P4^5;
sbit bt4  = P2^7;
sbit bt5  = P2^6;
sbit bt6  = P2^5;
sbit bt7  = P2^4;
//#define FOSC  11059200L
#define FOSC  24000000L

#define BAUD  9600
#define TM	(65536-(FOSC/4/BAUD))

#define RESET_PIN P13

#define LEDON {LED = 0;}
#define LEDOFF {LED = 1;}
#define TIMEOUT           -1
#define TIMEOUT_ALL           5
#define CC1101            0x00
#define BT_UART           0x01
#define MSG_OPEN          0x01
#define MSG_CLOSE         0x02
#define MSG_OBTAIN_STATUS 0x03
#define FMQON   {P0M0 |= 0x80;P0M1 &= 0x7F;}
#define FMQOFF  {P0M0 |= 0x80;P0M1 |= 0x80;}

#define LEDCARD_ON {P15 = 0;}
#define LEDCARD_OFF {P15 = 1;}


#define COUNTLIMIT        0x01
#define DATELIMIT         0x02

#define TYPE_CARD_CUSTMER	0x01
#define TYPE_CARD_MGR		0x02
#define TYPE_CARD_FUNC		0x03


#define FUNC_TYPE_FORBIDEN 		0x01
#define FUNC_TYPE_CHECK_TIME 	0x02
#define FUNC_TYPE_SWITCH 		0x03
#define FUNC_TYPE_OFFSET 		0x04
#define FUNC_TYPE_AGENT 		0x05
#define FUNC_TYPE_Check 		0x06
#define FUNC_TYPE_CLEARBLACKLIST 		0x07
#define FUNC_TYPE_ENABLECOUNTER 	0x08
#define FUNC_TYPE_DISABLECOUNTER 	0x09


uchar xdata sendnum;
uchar xdata cardtyp[2];
uchar xdata cardnum[4];
uchar xdata cardsize[1];
uchar xdata cardkey[6] = {0xff,0xff,0xff,0xff,0xff,0xff};//
uchar xdata newkey[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uchar xdata card_new_key[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	
uchar xdata cardknum[16];
uchar xdata cardwdata[16] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x17,0x15,0x16};
//uchar xdata cardwdata[16] = {0xff,0xff,0xff,0xff,0xff,0xff,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uchar code ENABLEALL[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
uchar code a[8] = {0,0,0,0,0x00,0x00,0x00,0x00};
uchar code b[8] = {0,0,0x00,0x00,0x00,0x00,0x00,0x00};
uchar code c[8] = {255,255,255,255,255,255,255,255};
uchar xdata Password_Data[4] = {0xff,0xff,0xff,0xff};
uchar xdata Agent_Data[4] = {0xff,0xff,0xff,0xff};

uchar xdata timere = 0;
uchar xdata timecard = 510;
uchar xdata *p;
char xdata cardtypstu;
char xdata cardnumstu;
char xdata cardsizestu;
char xdata cardcheckstu;
char xdata cardknumstu;
char xdata cardwdatastu;
uchar xdata bufini = 0,bufino;
uchar xdata maincmd[BUFINLEN];
uchar xdata g_chOffset = 0;
ulong xdata g_ulAgentID = 0;

uchar xdata bt_data[BUFINLEN];
uint  idata counter2 = 0;

bit  idata internal2 = 0;
uchar xdata g_ucPackageFlag = 0;
uchar xdata g_ucEnableFlag = 0;
uchar xdata g_chPasswordFlag = 0;
uchar xdata g_ucAgentVerifyFlag = DIS_VERIFY_AGENT;
uchar xdata g_ucReverseFlag = DIS_REVERSE;
uchar xdata g_ucElevatorID = 0;
uchar xdata g_ucEnableSwitch = 0;
uchar xdata g_ucDisCounter = 0;
uchar xdata tmElevator[7] = {0};



uchar *pp2;
uchar xdata bt_buf[BUFINLEN];


char IsReset(void)
{
	uchar chData = 0;
	uchar uData2 = 0;
	chData = P1;
	
	if( (chData | 0xEF) == 0xEF)
	{
		delay_10ms(100);
		chData |= P1;
		delay_10ms(100);
		chData |= P1;
		delay_10ms(100);
		chData |= P1;
		delay_10ms(100);
		chData |= P1;
		delay_10ms(100);	
		chData |= P1;
		if((chData | 0xEF) == 0xEF)
			return TRUE;
	}
	return FALSE;
}


uchar IsDisableOutput(void)
{
	uchar chData = 0;
	uchar uData2 = 0;
	chData = P1;
	
	if( (chData | 0xF7) == 0xF7)
	{
		delay_10ms(100);
		chData |= P1;
		if((chData | 0xF7) == 0xF7)
			return TRUE;
	}
	return FALSE;
}


void UART_init (void)
{
	//EA  =  1; //允许总中断（如不使用中断，可用//屏蔽）

	SCON = 0x50;
	//	S2CON = 0x50; 		//8位数据,可变波特率
	//	AUXR | =  0x04;		//定时器2时钟为Fosc,即1T
	T2L  =  TM;		//设定定时初值
	T2H  =  TM>>8;		//设定定时初值
	//RL_T2H = 0XAA;
	//RL_T2L = 0XFA;
	AUXR |=  0x01;		//串口1选择定时器2为波特率发生器
	//	AUXR | =  0x10;		//启动定时器2 
	//   IE2 | =  1; //允许UART2串口的中断
	ES  =  1; //允许UART1串口的中断
}

void Send(uchar *str,uint len)
{
	pp2 = str;
	counter2 = len;
	internal2 = 1;
	SBUF = *pp2++;
	while(internal2); 
}
uchar GetCommand(uchar chType, uchar*bufino, uchar bufini)
{
	uchar xdata *combuf,*dat;
	uchar  i,j,len2,k;
	uint crc;

	if(chType == BT_UART)
	{
		combuf = bt_buf;
		dat = bt_data; 
	}
	i = *bufino;
rescan1:
	if(bufini == i) 
		return 0;

	if((combuf[i++]) != 0xef) 
	{
		if(i >= BUFINLEN) i = 0;  
		*bufino = i; 
		goto rescan1;
	}

	if(i >= BUFINLEN) 
		i = 0;

	if(bufini == i) 
		return 0;

	if((combuf[i++]) != 0x01) 
	{
		if(i >= BUFINLEN) i = 0;  
		*bufino = i; 
		goto rescan1;
	}
	if(i >= BUFINLEN) 
		i = 0;
	if(bufini == i) 
		return 0;

	g_ucPackageFlag = combuf[i++];

	if(i >= BUFINLEN) 
		i = 0;
	if(bufini == i) 
		return 0;

	i++; 

	if(i >= BUFINLEN) 
		i = 0;
	if(bufini == i) 
		return 0;

	len2 = combuf[i++]; 
	if(i >= BUFINLEN) 
		i = 0;
	if(bufini == i) 
		return 0;

	//	len0 = len1*256+len2;
	if(len2 <= 2 || len2 >= 200) {
		*bufino = i; 
		goto rescan1;
	} 

	crc = g_ucPackageFlag+len2;
	j = 0;

	while(len2-2)
	{
		if(bufini == i) 
			return 0;
		k = dat[j++] = combuf[i++];

		if(i >= BUFINLEN) 
			i = 0;
		crc += k;

		len2--;
	}

	if(bufini == i) 
		return 0;

	crc -= (unsigned int)combuf[i++]*256;

	if(i >= BUFINLEN) 
		i = 0;

	if(bufini == i) 
		return 0;

	crc -= combuf[i++];

	if(i >= BUFINLEN) 
		i = 0;

	if(crc) 
	{
		*bufino = i; 
		goto rescan1;
	}
	else 
	{
		*bufino = i; 
		return 1;
	}
}


void Make(uchar bbs,unsigned int len,uchar *sendbao)
{
	uchar i;
	uint  sum;

	uchar xdata bao[80];
	sum = 0;

	for(i = 0;i<len-2;i++)
	{
		bao[i]  =  sendbao[i];
	}
	sendbao[0]  =  0xef;
	sendbao[1]  =  0x01;

	sendbao[2]  =  bbs;
	sendbao[3]  =  len/256;
	sendbao[4]  =  len%256;

	for(i  =  0;i<len-2;i++)
	{
		sendbao[5+i]  =  bao[i];
		sum  =  sum + bao[i];
	}
	sum = sum+len+bbs;
	sendbao[4+len-1] = sum/256;
	sendbao[4+len] = sum%256;
}


void memcopy(uchar *des,uchar *src,uchar len)
{
	uchar i ;
	for(i = 0;i<len;i++)
	{
		*des++ = *src++;
	}
	if(len<16)
	{
		for(i = len;i<16;i++)
			*des = 0;
	}
}	



uchar GetElevatorID()
{
	uchar dat = 0;
	dat |= (uchar)bt7;
	dat <<= 1;
	dat |= (uchar)bt6;
	dat <<= 1;
	dat |= (uchar)bt5;
	dat <<= 1;
	dat |= (uchar)bt4;
	dat <<= 1;
	dat |= (uchar)bt3;
	dat <<= 1;
	dat |= (uchar)bt2;
	dat <<= 1;
	dat |= (uchar)bt1;
	dat <<= 1;
	dat |= (uchar)bt0;
	return dat;
}

uchar ConfirmByte(uchar dat)
{
	uchar  i = 0;
	uchar  temp = dat;
	uchar  count = 0;
	for(i = 0;i<8;i++)
	{
		if(temp&0x80)
		{
			count++;
		}
		temp <<= 1;
	}
	return count;
}
bit ConfirmSingleOrMulti(uchar *dat)
{
	uchar  i = 0;
	uchar  count = 0;
	for(i = 0;i<8;i++)
	{
		count += ConfirmByte(dat[i]);	
	}
	if(count>2)
		return 1;
	else
		return 0;
}


uchar ReadFuntionCard(uchar chOffset)
{	
	uchar temp[16];
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_0 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+2,temp,11);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_1 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+13,temp,12);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_2 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+25,temp,2);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_3 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+27,temp,1);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_4 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+28,temp,16);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_5 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+44,temp,16);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_6 + chOffset,temp))
		return Do_False;

	memcopy(maincmd+60,temp,8);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_7 + chOffset,temp))
		return Do_False;
	memcopy(maincmd+68,temp,5);
	return Do_True;
}


unsigned WriteFunctionCard(uchar chOffset)
{
	uchar  temp[16];
	memcopy(temp,bt_data+1,11);	
	if(writeDataToIc(cardkey,SECTION_0 + chOffset,temp)  !=  MI_WR_OK)	
		return Do_False;
	memcopy(temp,bt_data+12,12);
	if(writeDataToIc(cardkey,SECTION_1 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+24,2);
	if(writeDataToIc(cardkey,SECTION_2 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+26,1);
	if(writeDataToIc(cardkey,SECTION_3 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+27,16);
	if(writeDataToIc(cardkey,SECTION_4 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+43,16);
	if(writeDataToIc(cardkey,SECTION_5 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+59,8);
	if(writeDataToIc(cardkey,SECTION_6 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	memcopy(temp,bt_data+67,5);
	if(writeDataToIc(cardkey,SECTION_7 + chOffset,temp)  !=  MI_WR_OK)
		return Do_False;
	return  Do_True;
}



uchar ReverseWriteData2Card(uchar ucData)
{
	uchar xdata temp[16];
	uchar  ucSectionIndex = 0;
	uchar  ucOffset = 0;
	
	ucSectionIndex = g_ucElevatorID >> 4;
	ucOffset = g_ucElevatorID & 0x0F;

	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_7 + ucSectionIndex,temp))
		return Do_False;
	
	temp[ucOffset] = ucData; //记录小时
	
	if(MI_WR_OK != writeDataToIc(cardkey,SECTION_7 + ucSectionIndex,temp))
		return Do_False;
	
	return  Do_True;
}


uchar ReadCardReverseData(uchar* pucData)
{
	//uchar xdata ucElevatorID = 0;
	uchar xdata temp[16];
	//uchar xdata ucTimes[7];
	uchar  ucSectionIndex = 0;
	uchar  ucOffset = 0;
	
	//ucElevatorID = GetElevatorID();
	
	//readtime(ucTimes);
	
//	ucSectionIndex = ucElevatorID / 16;
//	ucOffset = ucElevatorID % 16;

	ucSectionIndex = g_ucElevatorID >> 4;
	ucOffset = g_ucElevatorID & 0xF;

	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_7 + ucSectionIndex,temp))
			return Do_False;
		
	*pucData = temp[ucOffset];
		
	return  Do_True;
}


char ReadUserCard(uchar chOffset)
{
	uchar temp[16];
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_0 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 2, temp, 11);
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_1 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 13, temp, 12);
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_2 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 25, temp, 2);
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_3 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 27, temp, 9);
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_4 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 36, temp, 9);
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_5 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 45, temp, 9);

	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_6 + chOffset,temp))
		return Do_False;
	memcopy(maincmd + 53, temp, 13);
	//errOkFlag = 1;
	return Do_True;
}

uchar WriteUserCard( uchar chOffset)
{	
	uchar temp[16];
	memcopy(temp,bt_data+1,11);	
	if(writeDataToIc(cardkey,SECTION_0 + chOffset,temp) != MI_WR_OK)	
		return Do_False;

	memcopy(temp,bt_data+12,12);
	if(writeDataToIc(cardkey,SECTION_1 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcopy(temp,bt_data+24,2);
	if(writeDataToIc(cardkey,SECTION_2 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcopy(temp,bt_data+26,9);
	if(writeDataToIc(cardkey,SECTION_3 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcopy(temp,bt_data+35,9);
	if(writeDataToIc(cardkey,SECTION_4 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcopy(temp,bt_data+44,9);
	if(writeDataToIc(cardkey,SECTION_5 + chOffset,temp) != MI_WR_OK)
		return Do_False;

	memcopy(temp,bt_data+53,13);
	if(writeDataToIc(cardkey,SECTION_6 + chOffset,temp) != MI_WR_OK)
		return Do_False;
	return  Do_True;
}


uchar RecordInterParam(uchar chOffset)
{	
	uchar temp[16];
	uchar xdata tmData[7];
	//数据偏移量
	temp[0] = chOffset;
	//启用代理商检验
	temp[1] = ReadAgentFlagData();

	//代理商ID
	temp[2] = (g_ulAgentID >> 24) & 0xFF;
	temp[3] = (g_ulAgentID >> 16) & 0xFF;
	temp[4] = (g_ulAgentID >> 8) & 0xFF;
	temp[5] = g_ulAgentID & 0xFF;

	//电梯号
	temp[6] = GetElevatorID();
	//电梯时间
	readtime(tmData);
	temp[7] = tmData[0];
	temp[8] = tmData[1];
	temp[9] = tmData[2];
	temp[10] = tmData[3];
	temp[11] = tmData[4];
	temp[12] = tmData[5];
	temp[13] = tmData[6];
	
	temp[14] = ReadReverseCheckFlag();
	
	if(writeDataToIc(cardkey,SECTION_16,temp) != MI_WR_OK)	
		return Do_False;

	memset(temp, 0, 16);
	temp[0] = Password_Data[0];
	temp[1] = Password_Data[1];
	temp[2] = Password_Data[2];
	temp[3] = Password_Data[3];
	
	if(writeDataToIc(cardkey,SECTION_16 + 1,temp) != MI_WR_OK)	
		return Do_False;
	
	maincmd[0] = tmData[0];
	maincmd[1] = tmData[1];
	maincmd[2] = tmData[2];
	maincmd[3] = tmData[3];
	maincmd[4] = tmData[4];
	maincmd[5] = tmData[5];
	maincmd[6] = tmData[6];

	Make(0xFD, 9, maincmd);
	Send(maincmd, 14);

	return  Do_True;
}

void ScanCommand()
{
	uchar i = 0,j = 0;
	uchar errOkFlag = 0;
	//uchar xdata temp[16];
	if(bufini != bufino) 
	{
		if(Do_True == GetCommand(BT_UART,&bufino,bufini))
		{
			switch(g_ucPackageFlag)
			{
			case(1)://写
				if(bt_data[0] == 0x02)
				{
					j = 0;
					maincmd[0] = 0;
					for(i = 0;i<16;i++)
					{	
						maincmd[i+1] = 0;
						if(writePassword(cardkey,i,newkey) != MI_WR_OK)
						{
							maincmd[i+1] = 1;
							maincmd[0] = 1;
						}
						//break;
					}
					//maincmd[0] = 1;
					Make(1,19,maincmd);
					Send(maincmd,24);
				}
				break;
			case(2):         //读
				for(i = 0;i<47;i++)
				{
					if(MI_RD_OK == readDataFromIc(cardkey,i,cardknum))
					{	
						Send(cardknum,16);
					} 
				}
				break;
			case(3):	  //上位机写业主卡信息
				errOkFlag = 0;
				if(bt_data[0] == 1)
				{
					errOkFlag  =  ReadUserCard(g_chOffset);
					if(errOkFlag == 1)
						maincmd[0] = 0;
					else
						maincmd[0] = 1;
					maincmd[1] = 1;
					Make(3,55,maincmd);
					Send(maincmd,60); 
				}
				if(bt_data[0] == 2)
				{
					errOkFlag  =  WriteUserCard(g_chOffset);
					if(errOkFlag == 1)
						maincmd[0] = 0;
					else
						maincmd[0] = 1;
					maincmd[1] = 2;
					Make(3,4,maincmd);
					Send(maincmd,9);
				}
				break;
			case(4):	  //上位机读写管理员卡
				errOkFlag = 0;
				if(bt_data[0] == 1)
				{
					errOkFlag  =  ReadUserCard(g_chOffset);
						if(errOkFlag == 1)
							maincmd[0] = 0;
						else
							maincmd[0] = 1;
					maincmd[1] = 1;
					Make(4,55,maincmd);
					Send(maincmd,60); 
				}
				if(bt_data[0] == 2)
				{
					errOkFlag  =  WriteUserCard(g_chOffset);
					if(errOkFlag == 1)					   		
						maincmd[0] = 0;
					else
						maincmd[0] = 1;
					maincmd[1] = 2;
					Make(4,4,maincmd);
					Send(maincmd,9);
				}

				break;
			case(5):	  //上位机读写功能卡
				errOkFlag = 0;
				if(bt_data[0] == 1)//写
				{
					errOkFlag  =  ReadFuntionCard(g_chOffset);
					if(errOkFlag == 1)
						maincmd[0] = 0;
					else
						maincmd[0] = 1;
					maincmd[1] = 1;
					Make(5,69,maincmd);
					Send(maincmd,74); 
				}
				if(bt_data[0] == 2)//读
				{
					errOkFlag  =  WriteFunctionCard(g_chOffset);
					if(errOkFlag == 1)					   		
						maincmd[0] = 0;
					else
						maincmd[0] = 1;
					maincmd[1] = 2;
					Make(5,4,maincmd);
					Send(maincmd,9);
				}

				break;
			case (7):
				maincmd[6] = bt_data[0];
				maincmd[5] = bt_data[1];
				maincmd[3] = bt_data[2];
				maincmd[2] = bt_data[3];
				maincmd[1] = bt_data[4];
				maincmd[0] = bt_data[5];
				maincmd[4] = bt_data[6];
				P8563_settime(maincmd);
				maincmd[0] = 0;
				Make(7,3,maincmd);
				Send(maincmd,8);
				break;
			case(8):	  //
				readtime(maincmd);
				Make(8,9,maincmd) ;
				Send(maincmd,14);
				break;
			}
		}
	}
} 

void Beep(void)
{
	uchar i;
	FMQON
	for(i = 0;i<100;i++)
		Delay1();
	FMQOFF
}

void LongBeep(void)
{
	uchar i;	
	for(i = 0;i<100;i++)
			Delay1();
	FMQON
	for(i = 0;i<200;i++)
			Delay1();
	FMQOFF
}


/*
* 函数功能: 多次响声
*参数:		
*		uchar ucCount: 相声次数
*
*返回值:无
*
*/

void Sounds(uchar ucCount)
{
	uchar i = 0;
	for(i=0; i < ucCount - 1; i++)
	{
		Beep();
		delay_10ms(30000);
	}
	Beep();
}

void flash(uchar ucCount)
{
	uchar i;
	for(i=0; i < ucCount - 1; i++)
	{		
		LED = ~LED;
		delay_10ms(1200);
	}
	LEDON;
}

void PressButton(uchar *dat)
{	  
	uchar i;
	pressKey(dat);	
	//pressKey(0xff);
	for(i = 0;i<100;i++)
		Delay1();
	pressKey(b);
	//pressKey(0x00);
	//Beep();
}


//uchar GetVersion(uchar ucOffset)
//{
//	uchar ucRet = MI_ERR;
//	memset(cardknum, 0, 16);
//	//读生产数值
//	ucRet = readDataFromIc(cardkey, SECTION_46 + ucOffset, cardknum);
//	
//	if(ucRet != MI_RD_OK)
//		return 0;
//	
//	return cardknum[4];
//}

//uchar CheckSerial(uchar ucOffset)
//{
//	uchar ucRet = 0;
//	uchar ucCardSerial[4];
//	uchar ucTemp[16];

//	ucRet = readDataFromIc(cardkey, SECTION_46 + ucOffset, ucTemp);
//	if(MI_RD_OK != ucRet)
//		return Do_False;
//		
//	ucRet = PcdAnticoll(ucCardSerial);					//获取卡的卡号
//	
//	if(ucRet != MI_OK)
//		return Do_False;	
//		
//	if(	ucTemp[5] == ucCardSerial[0]
//		&& ucTemp[6] == ucCardSerial[1]
//		&& ucTemp[7] == ucCardSerial[2]
//		&& ucTemp[8] == ucCardSerial[3]
//		)
//		return Do_True;
//	return Do_False;

//}

//uchar WriteSerial()
//{
//	uchar ucRet = 0;
//	uchar ucCardSerial[4];
//	uchar ucTemp[16];

//	ucRet = readDataFromIc(cardkey, SECTION_46, ucTemp);
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
//	ucRet = writeDataToIc(cardkey, SECTION_46, ucTemp);
//	
//	if(ucRet == MI_WR_OK)
//		return Do_True;
//	return Do_False;
//}



/*
	函数功能：
	参数
	返回值：
*/
uchar DoBlackList(uchar iType, uchar *pData, uchar chLength)
{
	uchar xdata i = 0;
	char xdata iCount  =  chLength / 4;
	
	for(i = 0; i<iCount; i++)
	{
		if(pData[i*4] != 0 || pData[i*4+1] != 0 || pData[i*4+2] != 0)
		{
			if(pData[i*4+3] == 0)
				//deleteBlackList(iType, pData+i*4);
				DeleteBlackList(iType, pData+i*4);
			else
				//AddBlackList(iType, pData+i*4);
				Record2BlackList(iType, pData + i*4);
		}

		maincmd[0] = iType;
		maincmd[1] = pData[i*4];
		maincmd[2] = pData[i*4+1];
		maincmd[3] = pData[i*4+2];
		
		Make(0xFE, 6, maincmd);
		Send(maincmd, 11);
	}
	return 1;
}

/*
*函数功能:
			检查使用次数
*参数:
*			char *pCount,返回使用次数
*返回值:
			Do_True:使用次数在范围内
*			Do_False:执行错误或者使用次数已经为0
*/
uchar CheckUseCount(uint  *pCount, uchar  chOffset)
{
	uchar xdata temp1[16];
	uint  leave_count = 0;
	
	if( MI_RD_OK != readDataFromIc(cardkey,SECTION_2 + chOffset,temp1) )
		return Do_False;
	
	leave_count = (temp1[0] << 8) + temp1[1] ;
	
	if(leave_count <= 0)
		return Do_False;
	
	if(g_ucDisCounter == ENABLE_COUNTER)
		leave_count--;
	
	temp1[0] = (leave_count >> 8) & 0xFF;
	temp1[1] = leave_count & 0xFF;

	writeDataToIc(cardkey,SECTION_2 + chOffset,temp1);
	*pCount = leave_count;
	
	return Do_True;
}
/*
	函数功能：
	参数
	返回值：
*/
uchar DoFunctionEnableInfo(uchar chOffset)
{
	uchar  temp1[16];
	uint  count  =  0;
	uchar  chType = 0;
	
//	if(Do_True != CheckUseCount( &count, 0 ))
//		return Do_False;

	if( MI_RD_OK != readDataFromIc(cardkey,SECTION_3 + chOffset,temp1))
		return Do_False;

	chType = temp1[0];
	
//	if(GetElevatorID() != temp1[0])  //是本电梯
//		return Do_False;

	if( MI_RD_OK != readDataFromIc(cardkey,SECTION_4 + chOffset,temp1))
		return Do_False;
	
	DoBlackList(chType, temp1, 16);
	
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_5 + chOffset,temp1))
		return Do_False;	
	DoBlackList(chType, temp1, 16);

	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_6 + chOffset,temp1))
		return Do_False;
	DoBlackList(chType, temp1, 8);

	//Beep();
	return Do_True;
}

//操作电梯按钮
void DealElevatorBtn(uchar p[])
{		
	if(0==ConfirmSingleOrMulti(p + 1))
	{
		Beep();
		enableKey(p + 1);
		PressButton(p + 1);
	}
	else
	{
		enableKey(p + 1);
		//PcdHalt();
		Beep();
	}
}
//
/*
* 函数功能: 处理扇区中指定的电梯，操作电梯按钮
*参数:		
*		uchar chIndex:  扇区编号
*返回值:无
*
*/

uchar DealElevatorIndex(uchar chIndex)
{
	uchar xdata temp1[16];
	if( MI_RD_OK != readDataFromIc(cardkey, chIndex, temp1))
		return Do_False;

	//匹配电梯号
	if(GetElevatorID() != temp1[0])
		return Do_False;

	//操作电梯按钮
	DealElevatorBtn(temp1);


	return Do_True;
}


/*
* 函数功能: 处理电梯
*参数:		
*		uchar nType:  1 : 不指定楼梯
*					0 : 指定楼梯
*返回值:无
*
*/

void DealElevator(uchar nType)
{
	if(nType & 0x01==1) //不指定楼梯
	{		
		Sounds(1);
		enableKey(ENABLEALL); //使能按钮
	}
	else
	{
		DealElevatorIndex(SECTION_3 + g_chOffset);
		DealElevatorIndex(SECTION_4 + g_chOffset);
		DealElevatorIndex(SECTION_5 + g_chOffset);
		DealElevatorIndex(SECTION_6 + g_chOffset);
	}
}

//uchar WriteOffsetPsw(uchar* pdatas)
//{
//	if(Do_True != WriteOffset(pdatas[0]))
//		return Do_False;
//	if(Do_True != WriteSectionPsw(pdatas + 1))
//		return Do_False;
//	return Do_True;
//}

unsigned long GetCardAgentID(uchar ucOffset)
{
	ulong xdata lAgentID = 0xffffffff;
	uchar xdata temp1[16];
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_46 + ucOffset,temp1))
		return Do_False;
	lAgentID = (temp1[0]<<24) + (temp1[1]<<16) + (temp1[2]<<8) + temp1[3];
	return lAgentID;
}


///////////////////////////////////////////////////////////////////////////////////////
///////////
///////////	计算每个扇区号与块号的对应关系,本处所用非绝对对地址块/////////////////////
///////////	入口:  每个扇区对应的块号,范围:块0~块3
//////////////////////////////////////////////////////////////////////////////////////


uchar GeneratePsw()     //密钥处理函数 一卡一密钥，不同扇区不密钥也不同
{
	uchar  i;

	for(i = 0; i < 4; i++)
		card_new_key[1 + i] = Password_Data[i];  //cardwdata 定义密钥暂存数组 长度6个字节  ，chData 存放序列号的，序列号为4个字节

	card_new_key[0] = 0xFF;         	//这个值你可自己定义
	card_new_key[5] = 0xFF;			//这个值是块号 ，即每个扇区的控制块号值是不同的 	

	
	memcpy(newkey,card_new_key,16);
	
	memcpy(cardkey,card_new_key,6);
	


	return Do_True;
}


uchar RecoverPsw()     //密钥处理函数 一卡一密钥，不同扇区不密钥也不同
{
	uchar  i;

	for(i = 0; i < 4; i++)
		card_new_key[1 + i] = 0xFF;  //cardwdata 定义密钥暂存数组 长度6个字节  ，chData 存放序列号的，序列号为4个字节

	card_new_key[0] = 0xFF;         	//这个值你可自己定义
	card_new_key[5] = 0xFF;			//这个值是块号 ，即每个扇区的控制块号值是不同的 	
	
	memcpy(newkey,card_new_key,16);
	
	memcpy(cardkey,card_new_key,6);
	
	return Do_True;
}


uchar ReadCardStatusData(uchar chOffset)
{	
	uchar xdata temp[16];
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_0 + chOffset,temp))
		return Do_False;

	memcopy(maincmd, temp + 6, 5);
	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_1 + chOffset,temp))
		return Do_False;

	memcopy(maincmd + 5, temp, 16);
	return Do_True;
}

uchar DoReplaceCardForbidenList(uchar iType, uchar chOffset)
{
	uchar xdata temp[16] = {0};
	uchar  chRet = 0;
	uint  uiAddr = BLACK_LIST;
	
	if(iType == MANAGER_CARD)
		uiAddr = MGR_BLACK_LIST;
	
	if(MI_RD_OK  !=  readDataFromIc(cardkey,SECTION_6 + chOffset,temp))
		return Do_False;

	if(temp[9] == 0x03)
	{
		Record2BlackList(iType, temp + 10);		
	}
	return Do_True;
}


uchar ReadProc(void)
{
	uint  count=0;	
	uchar  chError = 0;
	uchar  chRet = 0;
	uchar  chReverseData = 0;
	uchar  chReverseData2 = 0;
	uchar xdata temp[16] = {0};
	uchar xdata temp1[16] = {0};	
	uchar xdata i=0;
	ulong xdata ulAgentID = 0;
	char chData = 0;
	
	
//	if(g_ucAgentVerifyFlag == DO_VERIFY_AGENT)
//	{
//		if(GetVersion(g_chOffset) >= 0xA0)
//		{
//			if(CheckSerial(g_chOffset) != Do_True)
//			{
//				LongBeep();
//				delay_10ms(1000);
//				Sounds(1);
//				return Do_False;
//			}
//		}
//	}

	if(MI_RD_OK != readDataFromIc(cardkey,SECTION_0 + g_chOffset,temp))
	{
		RecoverPsw();
		
		chError = readDataFromIc(cardkey,SECTION_0 + g_chOffset,temp);
		
//		memcpy(maincmd, cardkey, 6);
//		
//		maincmd[6] = chError;
//		maincmd[7] = temp[4];
//		maincmd[8] = temp[5];
//		
//		Make(0xFC,11,maincmd);
//		Send(maincmd, 16);
		
		if(MI_RD_OK != chError 
			|| temp[4] != 3 
			|| (((temp[5] & 0x0F) != FUNC_TYPE_OFFSET) 
				&& ((temp[5] & 0x0F) != FUNC_TYPE_Check))			
			)
		{
			GeneratePsw();
			Sounds(2);
			delay_10ms(50000);
			LongBeep();
			//Sounds(1);
			return Do_False;
		}
		GeneratePsw();
	}

	//readtime(tmElevator);
	
	switch (temp[4]) //卡类型
	{
	case 1://业主卡	
		//判断业主在不在黑名单中
		//if(INBLACKLIST == checkBlackList(CUSTOMER_CARD, temp+6))
		//{
		//	Sounds(4);
		//	return Do_False;
		//}
		
		if(GetDevice() == DISABLE)
		{		
			Sounds(2);
			return Do_False;
		}
		
		chRet = CheckBlackList(CUSTOMER_CARD, temp+6, &chReverseData2);
		if(INBLACKLIST == chRet)
		{			
			Sounds(2);
			delay_10ms(50000);
			Sounds(2);
			return Do_False;
		}
					
		if(g_ucReverseFlag == DO_REVERSE)
		{			
			chError = ReadCardReverseData(&chReverseData);
			chData = (chReverseData - chReverseData2) * (chReverseData2 - chReverseData) * -1;
			
			if(chReverseData != 0xFF 
				&&  chReverseData2 != 0xFF 
				&& (chError != Do_True 
					|| (chRet != NOINBLACKLIST
					//&& chReverseData != chReverseData2))
						&& chData > 2)))
			{
				maincmd[0] = 0 ;
				maincmd[1] = g_ucElevatorID ;
				maincmd[2] = temp[6];
				maincmd[3] = temp[7];
				maincmd[4] = temp[8];
				maincmd[5] = chError;
				maincmd[6] = chRet;
				maincmd[7] = chReverseData;
				maincmd[8] = chReverseData2;
				Make(0xF5,11,maincmd);
				Send(maincmd, 16);				
					
				Sounds(2);
				delay_10ms(50000);
				Sounds(3);
				return Do_False;
			}
				
//			chRet = CheckReverseData( CUSTOMER_CARD, temp + 6, chReverseData, &chReverseData2);
//		
//			if(Do_True != chError || REVERSE_CHECK_OK != chRet)
//			{
//				maincmd[0] = 0 ;
//				maincmd[1] = g_ucElevatorID ;
//				maincmd[2] = temp[6];
//				maincmd[3] = temp[7];
//				maincmd[4] = temp[8];
//				maincmd[5] = chError;
//				maincmd[6] = chRet;
//				maincmd[7] = chReverseData;
//				maincmd[8] = chReverseData2;
//				Make(0xF5,11,maincmd);
//				Send(maincmd, 16);				
//					
//				Sounds(2);
//				delay_10ms(50000);
//				Sounds(3);
//				return Do_False;
//			}

			chReverseData++;
			if(chReverseData == 0xFF)
				chReverseData = 0;
			
			if( Do_True == ReverseWriteData2Card(chReverseData))		
				RecordCardList(CUSTOMER_CARD, temp+6, chReverseData);
			if(Do_False == ReadCardReverseData(&chReverseData))
				RecordCardList(CUSTOMER_CARD, temp+6, 0xFF);			
		}
		
		ulAgentID = GetCardAgentID(g_chOffset);

		if(g_ucAgentVerifyFlag == DO_VERIFY_AGENT 
			&& 0xFFFFFFFF != g_ulAgentID
			&& ulAgentID != g_ulAgentID )
		{
			maincmd[0] = (ulAgentID >> 24) & 0xFF;
			maincmd[1] = (ulAgentID >> 16) & 0xFF;
			maincmd[2] = (ulAgentID >> 8) & 0xFF;
			maincmd[3] = ulAgentID & 0xFF;
			
			maincmd[4] = (g_ulAgentID >> 24) & 0xFF;
			maincmd[5] = (g_ulAgentID >> 16) & 0xFF;
			maincmd[6] = (g_ulAgentID >> 8) & 0xFF;
			maincmd[7] = g_ulAgentID & 0xFF;

			memcopy(maincmd + 8, cardkey, 16);
		
			Make(0xF5,26,maincmd);
			Send(maincmd, 31);
			
			Sounds(4);
			return Do_False;
		}
		if(temp[5] == 3)
			DoReplaceCardForbidenList(CUSTOMER_CARD, g_chOffset);

		
		if(MI_RD_OK != readDataFromIc(cardkey, SECTION_1 + g_chOffset, temp))		
		{			
			Sounds(2);
			return Do_False;
		}
		
		for(i = 2; i < 12; i++ )
			temp[i] = temp[i] - i;
		
		if((temp[0]&0x03) == COUNTLIMIT)
		{
			//查验使用次数
			if( CheckUseCount(&count, g_chOffset) != Do_True)
			{
				Sounds(1);
				delay_10ms(50000);
				Sounds(1);
				return Do_False;
			}
			
			DealElevator(temp[1]);
			
			maincmd[0] = count >> 8;
			maincmd[1] = count & 0xFF;
			maincmd[2] = temp[1];
			maincmd[3] = GetElevatorID();
			Make(5, 6,maincmd);
			Send(maincmd, 11);
		}
		else if((temp[0]&0x03) == DATELIMIT)
		{
			readtime(tmElevator);

			if(Do_True != checkTimeValide(temp+2,temp+7,tmElevator))
			{
				Sounds(1);
				delay_10ms(50000);
				Sounds(2);
				return Do_False;
			}
			DealElevator(temp[1]);
			
			for(i=0;i<7;i++)
				maincmd[i] = tmElevator[i];
			Make(5,9,maincmd);
			Send(maincmd, 14);
		}
		else if((temp[0]&0x03)==(COUNTLIMIT|DATELIMIT))
		{
			if( CheckUseCount( &count , g_chOffset) != Do_True)
			{
				Sounds(1);
				delay_10ms(50000);
				Sounds(1);
				return Do_False;
			}
			readtime(tmElevator);
			if(checkTimeValide(temp+2,temp+7,tmElevator) != Do_True)
			{
				Sounds(1);
				delay_10ms(50000);
				Sounds(2);
				return Do_False;
			}
			
			DealElevator(temp[1]);
		}
		

		break;
	case 2://管理员卡	
		if(GetDevice() == DISABLE)
		{
			Sounds(2);
			return Do_False;
		}
		chRet = CheckBlackList(MANAGER_CARD, temp+6, &chReverseData2);
		if(INBLACKLIST == chRet)
		{					
			Sounds(2);
			delay_10ms(50000);
			Sounds(2);
			return Do_False;
			
		}
		
		//翻写校验
		if(g_ucReverseFlag == DO_REVERSE)
		{
			chReverseData = 0;
			
			chError = ReadCardReverseData(&chReverseData);
			chData = (chReverseData - chReverseData2) * (chReverseData2 - chReverseData) * -1;
			
			if(chReverseData != 0xFF 
				&&  chReverseData2 != 0xFF 
				&& (chError != Do_True 
					|| (chRet != NOINBLACKLIST
					//&& chReverseData != chReverseData2))
						&& chData > 2)))						
			{					
				maincmd[0] = 0 ;
				maincmd[1] = g_ucElevatorID ;
				maincmd[2] = temp[6];
				maincmd[3] = temp[7];
				maincmd[4] = temp[8];
				maincmd[5] = chError;
				maincmd[6] = chRet;
				maincmd[7] = chReverseData;
				maincmd[8] = chReverseData2;
				Make(0xF5,11,maincmd);
				Send(maincmd, 16);				
					
				Sounds(2);
				delay_10ms(50000);
				Sounds(3);
				return Do_False;
			}
		
			//chRet = CheckReverseData( MANAGER_CARD, temp + 6, chReverseData, &chReverseData2);
		
			//if(Do_True != chError || REVERSE_CHECK_OK != chRet)			
			//{					
			//	Sounds(2);
			//	delay_10ms(50000);
			//	Sounds(3);
			//	return Do_False;
			//}

			chReverseData++;
			
			if( Do_True == ReverseWriteData2Card(chReverseData))		
				RecordCardList(MANAGER_CARD, temp+6, chReverseData);	
			if(Do_False == ReadCardReverseData(&chReverseData))
				RecordCardList(MANAGER_CARD, temp+6, 0xFF);
			
		}
			

		ulAgentID = GetCardAgentID(g_chOffset);

		if(g_ucAgentVerifyFlag == DO_VERIFY_AGENT 
			&& 0xFFFFFFFF != g_ulAgentID
			&& ulAgentID != g_ulAgentID )
		{
			maincmd[0] = (ulAgentID >> 24) & 0xFF;
			maincmd[1] = (ulAgentID >> 16) & 0xFF;
			maincmd[2] = (ulAgentID >> 8) & 0xFF;
			maincmd[3] = ulAgentID & 0xFF;
			
			maincmd[4] = (g_ulAgentID >> 24) & 0xFF;
			maincmd[5] = (g_ulAgentID >> 16) & 0xFF;
			maincmd[6] = (g_ulAgentID >> 8) & 0xFF;
			maincmd[7] = g_ulAgentID & 0xFF;

			memcopy(maincmd + 8, cardkey, 16);
		
			Make(0xF5,26,maincmd);
			Send(maincmd, 31);
			
			Sounds(4);
			return Do_False;
		}
		//补卡记录前一个卡号进黑名单
		if(temp[5] == 3)
			DoReplaceCardForbidenList(MANAGER_CARD, g_chOffset);
		
		if(MI_RD_OK != readDataFromIc(cardkey,SECTION_1 + g_chOffset,temp))
			return Do_False;
		
		for(i = 2; i < 12; i++ )
			temp[i] = temp[i] - i;
		
		if((temp[0]&0x03) == COUNTLIMIT)
		{		  						
			//查验使用次数
			if( CheckUseCount( &count, g_chOffset ) != Do_True)
			{					
				Sounds(1);
				delay_10ms(50000);
				Sounds(1);
				return Do_False;
			}
		}
		else if((temp[0]&0x03)==DATELIMIT)
		{
			readtime(tmElevator);
			//for(i=0;i<5;i++)
			//	maincmd[i]=time[i];
			//Make(5,7,maincmd);
			//Send(maincmd,9);
			if(Do_True != checkTimeValide(temp+2,temp+7,tmElevator))
			{
				Sounds(2);
				delay_10ms(50000);
				Sounds(2);
				return Do_False;
			}
		}
		else if((temp[0]&0x03) == (COUNTLIMIT|DATELIMIT))
		{
			if( CheckUseCount( &count, g_chOffset ) != Do_True)
			{
				Sounds(1);
				delay_10ms(50000);
				Sounds(1);
				return Do_False;
			}
			readtime(tmElevator);
			if(checkTimeValide(temp+2,temp+7,tmElevator) != Do_True)
			{
				Sounds(2);
				delay_10ms(50000);
				Sounds(2);
				return Do_False;
			}
		}
		DealElevator(temp[1]);
		
		break;
	case 3://功能卡
		if((temp[5] & 0x0F) == FUNC_TYPE_Check) 
		{
			RecoverPsw();
			
			if(Do_True == RecordInterParam(g_chOffset))
				Sounds(1);
			else				
				Sounds(2);
			
			GeneratePsw();
			
			return Do_True;
		}
		
		//先校验代理ID
		if(g_ucAgentVerifyFlag == DO_VERIFY_AGENT 
			&& (temp[5] & 0x0F) != FUNC_TYPE_OFFSET)
		{
			if(GetCardAgentID(g_chOffset) != g_ulAgentID)
			{				
				g_ulAgentID = GetCardAgentID(g_chOffset);
				maincmd[0] = (g_ulAgentID >> 24) & 0xFF;
				maincmd[1] = (g_ulAgentID >> 16) & 0xFF;
				maincmd[2] = (g_ulAgentID >> 8) & 0xFF;
				maincmd[3] = (g_ulAgentID) & 0xFF;
				
				g_ulAgentID = ReadAgentID();
				maincmd[4] = (g_ulAgentID >> 24) & 0xFF;
				maincmd[5] = (g_ulAgentID >> 16) & 0xFF;
				maincmd[6] = (g_ulAgentID >> 8) & 0xFF;
				maincmd[7] = (g_ulAgentID) & 0xFF;
				Make(0xff, 10, maincmd);
				Send(maincmd, 15);
				
				Sounds(2);
				return Do_False;
			}
		}
		
		if((temp[5] & 0x0F) == FUNC_TYPE_FORBIDEN)	  //启禁卡
		{
			chError = DoFunctionEnableInfo(g_chOffset);
			maincmd[0] = chError;
			maincmd[1] = g_chOffset;
			maincmd[2] = 0;
			
			Make(0xfe, 5, maincmd);
			Send(maincmd, 10);				
			
			if(Do_True == chError)
				Sounds(1);
			else			
				Sounds(2);
			return Do_True;
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_CHECK_TIME) //校时卡
		{  
			if(MI_RD_OK == readDataFromIc(cardkey,SECTION_7 + g_chOffset,temp1))
			{
				maincmd[6]=temp1[0];
				maincmd[5]=temp1[1];
				maincmd[3]=temp1[2];
				maincmd[2]=temp1[3];
				maincmd[1]=temp1[4];
				maincmd[0]=temp1[5];
				maincmd[4]=temp1[6];
				
				P8563_settime(maincmd);	
				Sounds(1);
			}
			else
				Sounds(2);
			return Do_True;
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_SWITCH)  //开关卡
		{			
			
			if(g_ucEnableFlag == 0)//启动
			{
				SetDevice(ENABLE);
				enableKey(a);
				g_ucEnableFlag = 1;
			}
			else
			{
				SetDevice(DISABLE);
				enableKey(ENABLEALL);
				g_ucEnableFlag = 0;
			}
			Sounds(1);
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_OFFSET)  // 偏移卡
		{
			//if(Do_True == WriteOffset( temp[6]))
			//if(Do_True == WriteOffsetPsw(temp + 6))
			//	Sounds(1);
			//else
			//	Sounds(2);
			//maincmd[0] = ReadOffset();
			//ReadSectionPsw(maincmd + 1);

			//if(g_chPasswordFlag == DO_PASSWORD)			
			if(g_chPasswordFlag == DO_PASSWORD)
				RecoverPsw();
			
			if(g_ucEnableSwitch == ENABLESWITCH)
			{				
				RecoverPsw();
			
				ulAgentID = GetCardAgentID(0 + g_chOffset);
				if(g_ulAgentID != GetCardAgentID(0 + g_chOffset))
				{
							
					Sounds(3);
					delay_10ms(50000);
					Sounds(1);
					
					memset(maincmd, 0, 20);
					
					maincmd[0] = (ulAgentID >> 24) & 0xFF;
					maincmd[1] = (ulAgentID >> 16) & 0xFF;
					maincmd[2] = (ulAgentID >> 8) & 0xFF;
					maincmd[3] = ulAgentID & 0xFF;
					
					maincmd[4] = 0;
					
					maincmd[5] = (g_ulAgentID >> 24) & 0xFF;
					maincmd[6] = (g_ulAgentID >> 16) & 0xFF;
					maincmd[7] = (g_ulAgentID >> 8) & 0xFF;
					maincmd[8] = g_ulAgentID & 0xFF;
					
					Make(0xFB, 11, maincmd);
					Send(maincmd, 16);

					if(g_chPasswordFlag == DO_PASSWORD)
						GeneratePsw();
					
					return Do_False;
				}
				
				if(g_ucEnableFlag == 0)//启动
				{
					SetDevice(ENABLE);
					enableKey(a);
					g_ucEnableFlag = 1;
					
					Sounds(1);
				}
				else
				{
					SetDevice(DISABLE);
					enableKey(ENABLEALL);
					g_ucEnableFlag = 0;
					
					Sounds(2);	
				}
				
				if(g_chPasswordFlag == DO_PASSWORD)
					GeneratePsw();
				
				memset(maincmd, 0, 20);
				maincmd[0] = g_ucEnableFlag;
				Make(0xFB, 7, maincmd);
				Send(maincmd, 12);
				
				return Do_True;
			}

			if(Do_True== ReadCardStatusData(g_chOffset))
			{					
				Sounds(3);
				
				WriteStatusData(maincmd);
				//write 2 times, ensuare OK
				WriteStatusData(maincmd);								
				
				g_chOffset = ReadOffset();	
				g_ulAgentID = ReadAgentID();		
				g_ucAgentVerifyFlag = ReadVerifyAgentFlag();
				g_chPasswordFlag = ReadPasswordFlag();
				g_ucReverseFlag = ReadReverseCheckFlag();
				ReadSectionPsw(Password_Data);	
				g_ucEnableSwitch = 0x01;
			}
			else
			{			
				Sounds(3);
				delay_10ms(50000);
				Sounds(2);
			}
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();
			
			memset(maincmd, 0, 16);			
			ReadStatusData(maincmd);			
			Make(0xFC, 16, maincmd);
			Send(maincmd, 21);
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_AGENT)  // 代理商
		{
			//已经授权过的，不能再授权改写了
			if(g_ulAgentID != 0xFFFFFFFF)
			{
				if(g_ucEnableFlag == 0)//启动
				{
					SetDevice(ENABLE);
					enableKey(a);
					g_ucEnableFlag = 1;
					Sounds(1);
				}
				else
				{
					SetDevice(DISABLE);
					enableKey(ENABLEALL);
					g_ucEnableFlag = 0;
					Sounds(2);
				}
				return Do_True;
			}
			
			if(Do_True == WriteAgentID( temp + 6))
			{
				g_ulAgentID = ReadAgentID();
					
				maincmd[0] = g_ucAgentVerifyFlag;
				
				maincmd[1] = (g_ulAgentID >> 24) & 0xFF;
				maincmd[2] = (g_ulAgentID >> 16) & 0xFF;
				maincmd[3] = (g_ulAgentID >> 8) & 0xFF;
				maincmd[4] = (g_ulAgentID) & 0xFF;	
				maincmd[5] = 0;
				maincmd[6] = g_ucReverseFlag;
				Make(0xFF, 9, maincmd);
				Send(maincmd, 14);
				
				//写代理校验标记
				if(temp[10] == 0xAA)
				{
					WriteVerifyAgentFlag(0x01);
					g_ucAgentVerifyFlag = ReadVerifyAgentFlag();
					Sounds(1);
				}		
				
				Sounds(3);
			}
			else
			{
				Sounds(4);
				delay_10ms(200);
				Sounds(1);
			}
		}
		
		else if((temp[5] & 0x0F) == FUNC_TYPE_CLEARBLACKLIST)  //清空黑名单
		{
			//ClearBlackList();
			ClearAllReverseList();
			Sounds(2);
			delay_10ms(200);
			Sounds(2);
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_ENABLECOUNTER)  //开启计数
		{
			g_ucDisCounter = EnableCounter();
			Sounds(1);
		}
		else if((temp[5] & 0x0F) == FUNC_TYPE_DISABLECOUNTER)  //关闭计数
		{
			g_ucDisCounter = DisableCounter();
			Sounds(2);
		}
		else
		{
			LongBeep();
		}
		
		break;
	default:
		{
			RecoverPsw();
				
			chError = readDataFromIc(cardkey,SECTION_0,temp);
			if(chError == Do_True 
				&& temp[4] == 3 
				&& (temp[5] & 0x0F) == FUNC_TYPE_OFFSET)  // 偏移卡
			{
				if(g_ucEnableSwitch == ENABLESWITCH)
				{			
					if(g_ulAgentID != GetCardAgentID(0))
					{
						Sounds(3);
						return Do_False;
					}
					
					if(g_ucEnableFlag == 0)//启动
					{
						SetDevice(ENABLE);
						enableKey(a);
						g_ucEnableFlag = 1;
						Sounds(1);
					}
					else
					{
						SetDevice(DISABLE);
						enableKey(ENABLEALL);
						g_ucEnableFlag = 0;
						Sounds(2);
					}
					memset(maincmd, 3, 20);
					maincmd[0] = g_ucEnableFlag;
					Make(0xFB, 7, maincmd);
					Send(maincmd, 12);
					
					return Do_True;
				}

			}
			else
				Sounds(3);
			
			if(g_chPasswordFlag == DO_PASSWORD)
				GeneratePsw();
		}
		break;			
	}
	
	return Do_True;
}


void Uart1(void) interrupt 4 using 2
{  
	if(RI)
	{
		SCON  = SCON & 0xfe;

		bt_buf[bufini++] = SBUF;
		if (bufini >= BUFINLEN) 
			bufini = 0;
	}
	else if(TI)
	{
		SCON = SCON & 0xFd;

		if(internal2)
		{
			if(!(--counter2))
				internal2 = 0; 
			else 
				SBUF = *pp2++;//SBUF = XBYTE[pn++];
		}
	}
}
void Uart2(void) interrupt 8 using 2
{  
	if(RI2)
	{
		S2CON  = S2CON & 0xfe;

		bt_buf[bufini++] = S2BUF;
		if (bufini >= BUFINLEN) bufini = 0;
	}
	else if(TI2)
	{
		S2CON  = S2CON & 0xFd;

		if(internal2)
		{
			if(!(--counter2))
				internal2 = 0; 
			else 
				S2BUF = *pp2++;//SBUF = XBYTE[pn++];
		}
	}
} 




//系统主函数
void main (void)
{
	uchar xdata  i;
	bit  init_go = 0;
	unsigned long xdata main_delay = 0;	
	unsigned int xdata test;
	uchar xdata uDisableOutput = 0;
	P3M0 |= 0XC0;P3M1 &= 0x3F;
	P4M0 |= 0x1E;P4M1 &= 0xE1;
	P2M0 |= 0x03;P2M1 &= 0x0C;

	//P0M0 = 0xF4;
	//P0M1 = 0x08;
	//P0M0 = 0xE4;
	//P0M1 = 0x10;	  BLACK_LIST

	Time_init();	  //两个定时器初始化
	UART_init () ;
	EA = 1;
	
	PcdReset();
	PcdAntennaOff(); 
	PcdAntennaOn();  
	M500PcdConfigISOType( 'A' );
	//halRfReceivePacket(RxBuf, &leng);
	LEDON	
	if(IapReadByte(ENABLEORNOTSHANQU) == 0xff)
	{
		IapProgramByte(ENABLEORNOTSHANQU, ENABLE);
	}	
	Sounds(1);
	
	FMQOFF
	
	dis_open();
	//Send_data_A(0xaa,0xaa);
	//Send_data_B(0X55,0X55);
	if(GetDevice() == ENABLE)
	{
		enableKey(a);
		pressKey(b);
	}
	else 
	{
		enableKey(ENABLEALL);
	}
	
	for(i = 0;i<30;i++)
	{
		Delay1();
		Delay1();
		Delay1();
		Delay1();
	} 

	if(TRUE == IsReset())
	{
		LongBeep();
		Sounds(2);
		flash(3);
		
		g_ulAgentID = ReadAgentID();
		for(i =0; i < 16; i++)
			maincmd[i] = 0xFF;

		IapReadBytes(AGENT_DATA_ADDR,Agent_Data,4);
		
		maincmd[AGENT_DATA_ADDR] = Agent_Data[0];
		maincmd[AGENT_DATA_ADDR + 1] = Agent_Data[1];
		maincmd[AGENT_DATA_ADDR + 2] = Agent_Data[2];
		maincmd[AGENT_DATA_ADDR + 3] = Agent_Data[3];

		
		maincmd[INNER_FLAG_ADDR] = 0;
		
		IapEraseSector(DEVICE_STATUS_ADDR);
		
		IapProgramBytes(DEVICE_STATUS_ADDR,maincmd,16);

		ClearAllReverseList();		
		
		IapProgramBytes(DEVICE_STATUS_ADDR,maincmd,16);
			
		Make(0xFA, 18, maincmd);
		Send(maincmd, 23);

		g_ulAgentID = ReadAgentID();
		memset(maincmd, 0, 6);
		maincmd[2] = (g_ulAgentID >> 24) & 0xFF;
		maincmd[3] = (g_ulAgentID >> 16) & 0xFF;
		maincmd[4] = (g_ulAgentID >> 8) & 0xFF;
		maincmd[5] = (g_ulAgentID) & 0xFF;

		Make(0xFA, 6, maincmd);
		Send(maincmd, 11);
	}

	maincmd[0] = ReadInnerFlag();
	if(maincmd[0] != 0xFF && (maincmd[0] & ENABLESWITCH) == ENABLESWITCH)
		g_ucEnableSwitch = ENABLESWITCH;
	
	g_chOffset = ReadOffset();	
	g_ulAgentID = ReadAgentID();		
	g_ucAgentVerifyFlag = ReadVerifyAgentFlag();
	g_chPasswordFlag = ReadPasswordFlag();
	g_ucReverseFlag = ReadReverseCheckFlag();
	ReadSectionPsw(Password_Data);	
	g_ucDisCounter = ReadDisableCounterFlag();
	
	maincmd[0] = g_chOffset;
	maincmd[1] = g_ucAgentVerifyFlag;
	maincmd[2] = (g_ulAgentID >> 24) & 0xFF;
	maincmd[3] = (g_ulAgentID >> 16) & 0xFF;
	maincmd[4] = (g_ulAgentID >> 8) & 0xFF;
	maincmd[5] = (g_ulAgentID) & 0xFF;
	
	maincmd[6] = g_chPasswordFlag;
	memcpy(maincmd + 7, Password_Data, 4);	
	maincmd[11] = g_ucReverseFlag;
	maincmd[12] = g_ucDisCounter;
	
	Make(0xFF, 15, maincmd);
	Send(maincmd, 20);

	if(g_chPasswordFlag == DO_PASSWORD)
	{
		GeneratePsw();
		
		//memcpy(newkey,card_new_key,16);		
		//memcpy(cardkey,card_new_key,6);
		
		memcpy(maincmd,newkey,16);
		Make(0xF9,18,maincmd);
		Send(maincmd,23); 
	}

	g_ucElevatorID = GetElevatorID();

	readtime(tmElevator);
	if(tmElevator[0] < 0x17)
	{
		tmElevator[0] = 0x17;
		tmElevator[1] = 0x1;
		tmElevator[2] = 0x1;
		tmElevator[3] = 0x0;
		tmElevator[4] = 0x0;
		tmElevator[5] = 0x0;
		tmElevator[6] = 0x0;
		
		P8563_settime(tmElevator);
	}
	
	while(1)
	{
		for(i = 0;i<30;i++)
		{
			Delay1();
			Delay1();
			Delay1();
			Delay1();
		}
		
		ScanCommand();

		cardtypstu = PcdRequest( PICC_REQIDL,cardtyp);				//寻卡
		
		if(cardtypstu == MI_OK)
		{	
			LEDCARD_ON
				
			ReadProc();
			init_go = 1;
			test = 0;
			PcdHalt();
			
			LEDCARD_OFF
		}

		
		if(TRUE == IsDisableOutput())
		{		
			if(uDisableOutput == 0)
				Sounds(1);
			uDisableOutput = 1;
			enableKey(ENABLEALL);
		}
		else
		{
			init_go = 1;
		}
		
		if(init_go)
			test++;
		
		if(test > 15)
		{
			init_go = 0;
			test = 0;
			if(GetDevice() == ENABLE && FALSE == IsDisableOutput()) 
			{
				enableKey(a);
				pressKey(b);

				if(uDisableOutput == 1)
					Sounds(1);
				uDisableOutput = 0;
			}
		}
		main_delay++;
		if(main_delay > 600000)
		{
			main_delay = 0;
			PcdReset();
			PcdAntennaOff(); 
			PcdAntennaOn();  
			M500PcdConfigISOType( 'A' );
		}
		/*
		else 
			senduart(&zhuangtai,1);
		
		cardnumstu = PcdAnticoll(cardnum);					//获取卡的卡号防冲突

		if(cardnumstu == MI_OK)
			Send(cardnum,4);
		cardsizestu = PcdSelect(cardnum,cardsize);		//选卡并返回卡容量

		if(cardsizestu == MI_OK)
			Send(cardsize,1);
		cardcheckstu = PcdAuthState(PICC_AUTHENT1A,0x1,cardkey,cardnum);	//块，验证密码

		if(cardcheckstu == MI_OK)
		{
			LEDON;
		}
		cardknumstu = PcdRead(0x1,cardknum);			  //读取验证扇区块的内容

		if(cardknumstu == MI_OK)
		{
			Send(cardknum,16);
		} 
		if(test == 255)
			cardwdatastu = PcdWrite(0x1,cardwdata);		  //验证后重写块内容
		if(cardwdatastu == MI_OK){LEDOFF;}

		cardknumstu = 0;

		cardcheckstu = 0;
		cardtypstu = 0;
		cardnumstu = 0;
		cardsizestu = 0;
		if(test == 255)
			writeDataToIc(cardkey,0,cardwdata);
		*/
	}
}


