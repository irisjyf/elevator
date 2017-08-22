
#include "74HC595.H"

//ȫ�ֱ�������

/*********************************************/
//void Send_data_A(u8 temp)	  /*�Ӵ��ڷ�������*/
//{
//     SBUF=temp;
//	  while(TI==0);       //�ȴ��������
//      TI=0;
//	  STRA=1;
//	  STRA=0;
//}
/****************************************************************
��������LED��ʾ����ʱ����
��  �ã�delay();
��  ������
����ֵ����
��  ����ռ��CPU��ʽ��ʱ500΢��ʱ��
��  ע������24.0m 1Tģʽ��ÿ����������Ϊ0.06254US��
/****************************************************************/
void delay(void)   //��� -0.46875us
{
    uchar a,b;
    for(b=200;b>0;b--)
        for(a=20;a>0;a--);
}
/****************��������A*************************/
void Send_data_A(uchar dat1/*,uchar dat2*/)	  
{
	uchar i; 
	for(i=0;i<8;i++)//һ���ֽ�8λ ���͸�595
   {
     SCKA(0);//=0; //��������λ595			   
	   SDAA((bit)((~dat1)&0x80));//ͨ��IO����һ��λ�� 595
       dat1=dat1<<1;  //�ֽ���λ ׼������һλ
	   delay();			   
       SCKA(1);
	   delay();
   }
/*   for(i=0;i<8;i++)//һ���ֽ�8λ ���͸�595
   {
       SCKA(1); //��������λ595			   
	   SDAA((bit)(dat2&0x80));//ͨ��IO����һ��λ�� 595
       dat2=dat2<<1;  //�ֽ���λ ׼������һλ
	   delay();				   
       SCKA(0);
	   delay();
   }  */

   
}
/****************��������B**********************/
void Send_data_B(uchar temp1/*,uchar temp2*/)	 
{
   uchar  i; 
	for(i=0;i<8;i++)//һ���ֽ�8λ ���͸�595
   {
       SCKB(0); //��������λ595			   
	   SDAB((bit)((~temp1)&0x80));//ͨ��IO����һ��λ�� 595	
       temp1=temp1<<1;  //�ֽ���λ ׼������һλ
	   
	   delay();			   
       SCKB(1);
	   delay();
   }
/*   
	 for(i=0;i<8;i++)//һ���ֽ�8λ ���͸�595
   {
     SCKB(1); //��������λ595			   
	   SDAB((bit)(temp2&0x80));//ͨ��IO����һ��λ�� 595	
       temp2=temp2<<1;  //�ֽ���λ ׼������һλ
	   
	   delay();			   
       SCKB(0);
	   delay();
   } 
*/
}
/**********************************************
����ʹ�ܺ���

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
ģ�ⰴ������

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
//****************��595��ʾ***************
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


