#ifndef H8563_H
#define H8563_H
/*#include <intrins.h>
#include <string.h>
#include "STC15Fxxxx.h"
//******************************************************8563 iic
#define delay5us {_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();}
sbit SDA=P3^6;//时钟数据
sbit SCL=P3^7;//时钟的时钟
#define MIN 0x02
#define SEC 0x03
#define HOUR 0x04
#define DAY 0x05
#define WEEK 0x06
#define MONTH 0x07
#define YEAR 0x08
#define read_ADD 0xa3		//写器件地址
#define write_ADD 0xa2		//读器件地址
//unsigned char code c8563_Store[4]={0x08,0x59,0x07,0x01};//写入时间初值，周一07:59:00
unsigned char code c8563_Store[7]={0x4,0x6,0x5,0x02,0x01,0x01,0x07};//写入时间初值，周一11:39:00 07 01 01
bit bdata SystemError;				//从机错误标志位
void iic_start(void)				//启动IIC总线子程序
{
//	EA=0;
	delay5us;
	SDA=1;
///delay5us;
	SCL=1;
	delay5us;
	SDA=0;
	delay5us;
	SCL=0;
//////////////delay5us;
}

void iic_stop(void)				//停止IIC总线数据传送子程序
{
	SDA=0;
///delay5us;
	SCL=1;
	delay5us;
	SDA=1;
	delay5us;
	SCL=0;
///delay5us;
//	EA=1;
	delay5us;
}

//void slave_ACK(void)				//从机发送应答位子程序/////////////////////////////////////////////////////////////
//{
//	SDA=0;
///	delay5us;
//	SCL=1;
//	delay5us;
//	SCL=0;
//	SDA=1;

///delay5us;

///delay5us;
//}

void slave_NOACK(void)				//从机发送非应答位子程序，迫使数据传输过程结束//////////////////////////////////////////////////////
{
	SDA=1;
///	delay5us;
	SCL=1;
	delay5us;

///delay5us;
	SCL=0;
	SDA=0;

/////////////////delay5us;
}

void check_ACK(void)				//主机应答位检查子程序，迫使数据传输过程结束
{
	SDA=1;
///delay5us;
	SCL=1;
///delay5us;
	F0=0;
	if(SDA==1) F0=1;				//惹SDA=1表明非应答，置位非应答标志F0
//	SDA=0;
///delay5us;
	SCL=0;
///delay5us;
}

void IICSendByte(unsigned char ch)		//发送一个字节///////////////////////////////////////////////
{
	unsigned char idata n=8;
	while(n--)
	{
		if((ch&0x80)==0x80)
		{
			SDA=1;
///delay5us;
			SCL=1;
		delay5us;
			SCL=0;		
			SDA=0;

///delay5us;

///delay5us;
		}
		else
		{
			SDA=0;
///		delay5us;
			SCL=1;
			delay5us;
			SCL=0;
///			delay5us;
		}
		ch=ch<<1;
	}
}

unsigned char IICreceiveByte(void)		//接收一个字节
{
	unsigned char idata n=8;
	unsigned char tdata;
	while(n--)
	{
		SDA=1;
	delay5us;
		SCL=1;
		tdata=tdata<<1;
		if(SDA==1)
			tdata=tdata|0x01;
		else
			tdata=tdata&0xfe;
		SCL=0;
	delay5us;
		}
	return(tdata);
}	*/

/*void write_CFGbyte(unsigned char CFG_add,unsigned char CFG_data)		//发送N位数据子程序
{
EA=0;
	iic_start();
	IICSendByte(write_ADD);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return;
	}
	IICSendByte(CFG_add);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return;
	}
	IICSendByte(CFG_data);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return;
	}
	iic_stop();
	EA=1;
}

void write_CFGNbyte(unsigned char CFG_add,unsigned char *CFG_data2)		//发送N位寄存器数据子程序
{
	unsigned char i;
	EA=0;
	iic_start();
	IICSendByte(write_ADD);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return;
	}
	IICSendByte(CFG_add);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return;
	}
	for(i=0;i<7;i++)
	{
	IICSendByte(CFG_data2[i]);
//	_nop_();

	check_ACK();
	if(F0==1)
		{
		SystemError=1;
		return;
		}
	}
//	slave_NOACK();
	iic_stop();
	EA=1;
}


unsigned char receive_CFGbyte(unsigned char  CFG_add)		//接收某个寄存器数据子程序
{
	unsigned char idata receive_da;
	EA=0;
	iic_start();
	IICSendByte(write_ADD);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return(0);
	}
	IICSendByte(CFG_add);
	check_ACK();
	if(F0==1)
	{
		SystemError=1;
		return(0);
	}
	iic_start();
	IICSendByte(read_ADD);
	check_ACK();/////////////////////////
	if(F0==1)
	{
		SystemError=1;
		return(0);
	}

	receive_da=IICreceiveByte();
	slave_NOACK();
	iic_stop();
		EA=1;
	return(receive_da);
	
}
void receive_CFGNbyte(unsigned char *buff)		//接收N个寄存器数据子程序
{
	EA=0;
	buff[6]=receive_CFGbyte(0x08);
	buff[5]=receive_CFGbyte(0x07);
	buff[4]=receive_CFGbyte(0x06);
	buff[3]=receive_CFGbyte(0x05);
	buff[2]=receive_CFGbyte(0x04);
	buff[1]=receive_CFGbyte(0x03);
	buff[0]=receive_CFGbyte(0x02);
    EA=1;
}
void P8563_Readtime(unsigned char*g8563_Store)
	{
	unsigned char time[7];
	receive_CFGNbyte(time);
	g8563_Store[0]=time[0]&0x7f;
	g8563_Store[1]=time[1]&0x7f;
	g8563_Store[2]=time[2]&0x3f;
	g8563_Store[3]=time[3]&0x3f;
	g8563_Store[4]=time[4]&0x07;
	g8563_Store[5]=time[5]&0x1f;
	g8563_Store[6]=time[6]&0xff;
	}
void P8563_settime(unsigned char *g8563_Store)				//写时间修改值
	{
	write_CFGNbyte(MIN,g8563_Store);
	}*/
#endif