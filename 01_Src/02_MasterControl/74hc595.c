
#include "74HC595.H"

//全局变量定义

/*********************************************/
//void Send_data_A(u8 temp)	  /*从串口发送数据*/
//{
//     SBUF=temp;
//	  while(TI==0);       //等待发送完毕
//      TI=0;
//	  STRA=1;
//	  STRA=0;
//}
/****************************************************************
函数名：LED显示用延时函数
调  用：delay();
参  数：无
返回值：无
结  果：占用CPU方式延时500微秒时间
备  注：晶振24.0m 1T模式，每个机器周期为0.06254US；
/****************************************************************/
void delay(void)   //误差 -0.46875us
{
    uchar a,b;
    for(b=200;b>0;b--)
        for(a=20;a>0;a--);
}
/****************发送数据A*************************/
void Send_data_A(uchar dat1/*,uchar dat2*/)	  
{
	uchar i; 
	for(i=0;i<8;i++)//一个字节8位 发送给595
   {
     SCKA(0);//=0; //上升沿移位595			   
	   SDAA((bit)((~dat1)&0x80));//通过IO口送一个位给 595
       dat1=dat1<<1;  //字节移位 准备送下一位
	   delay();			   
       SCKA(1);
	   delay();
   }
/*   for(i=0;i<8;i++)//一个字节8位 发送给595
   {
       SCKA(1); //上升沿移位595			   
	   SDAA((bit)(dat2&0x80));//通过IO口送一个位给 595
       dat2=dat2<<1;  //字节移位 准备送下一位
	   delay();				   
       SCKA(0);
	   delay();
   }  */

   
}
/****************发送数据B**********************/
void Send_data_B(uchar temp1/*,uchar temp2*/)	 
{
   uchar  i; 
	for(i=0;i<8;i++)//一个字节8位 发送给595
   {
       SCKB(0); //上升沿移位595			   
	   SDAB((bit)((~temp1)&0x80));//通过IO口送一个位给 595	
       temp1=temp1<<1;  //字节移位 准备送下一位
	   
	   delay();			   
       SCKB(1);
	   delay();
   }
/*   
	 for(i=0;i<8;i++)//一个字节8位 发送给595
   {
     SCKB(1); //上升沿移位595			   
	   SDAB((bit)(temp2&0x80));//通过IO口送一个位给 595	
       temp2=temp2<<1;  //字节移位 准备送下一位
	   
	   delay();			   
       SCKB(0);
	   delay();
   } 
*/
}
/**********************************************
按键使能函数

**********************************************/
void enableKey(unsigned char *dat)
{
	unsigned char i=0;
	unsigned char  relayEnable=0;
	for(i=0;i<8;i++)
	{
		Send_data_A(dat[7-i]);
		if(dat[7-i])
		relayEnable=1;
			
	}
	STRA(0);
	delay();	
	STRA(1);
	if(relayEnable)
	{
		RELAYOFF
	}
	else
	{
		RELAYON
	}
}
/**********************************************
模拟按键函数

**********************************************/
void pressKey(unsigned char *dat)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		Send_data_B(dat[7-i]);	
	}
	STRB(0);
	delay();	
	STRB(1);
	delay();
}

///
//****************打开595显示***************
void dis_open( )
{
	OEA(0);
	OEB(0);//=OEC =0;
}
/*
void dis_close( )
{
	OEA=OEB=OEC =1;
}

********************************/


