#ifndef __74HC595_H__
#define	__74HC595_H__
//#include "config.h"
#include "STC15Fxxxx.h"
sbit ray =P2^2;
#define RELAYON  {P2M0|=0X04;P2M1&=0XFB;ray=1;}
#define RELAYOFF {P2M0|=0X04;P2M1|=0X04;ray=0;}
//#include	"MyType.h"
/*
sbit SDAA=P2^4;	//����
sbit OEA =P2^5;  //595ʹ��
sbit STRA=P2^6;	 //����
sbit SCKA=P2^7;	//ʱ��

sbit SDAB=P2^0;	//����
sbit OEB =P2^1;  //595ʹ��
sbit STRB=P2^2;	 //����
sbit SCKB=P2^3;	//ʱ��

sbit SDAC=P3^4;	//����
sbit OEC =P3^0;  //����595ʹ��
sbit STRC=P3^6;	 //����
sbit SCKC=P3^7;	//ʱ��

sbit OED =P4^4;  //����595ʹ��

sbit LED0=P4^5;	  //ƽ����ȦLED
sbit LED1=P3^1;	  //������ȦLED

*/
sbit B_20=P4^3;	//ʱ��
sbit sdaa=P3^6;
sbit oea=P3^7;
sbit stra =P4^1;
sbit scka =P4^2;

sbit sdab=P4^3;
sbit oeb=P4^4;
sbit strb =P2^0;
sbit sckb =P2^1;



#define SDAA(flag) {sdaa=flag;}//{/*P3M0|=0X40;if(flag){P3M1&=(0Xff^0X40);}else{P3M1|=0X40;}*/}
#define OEA(flag)  {oea=flag;}//{P3M0|=0X80;if(flag){P3M1&=(0Xff^0x80);}else{P3M1|=0x80;}}
#define STRA(flag) {stra=flag;}//{P4M0|=0X02;if(flag){P4M1&=(0Xff^0x02);}else{P4M1|=0x02;}}
#define SCKA(flag) {scka=flag;}//{P4M0|=0X04;if(flag){P4M1&=(0Xff^0x04);}else{P4M1|=0x04;}}
                             
#define SDAB(flag) {sdab=flag;}//{P4M0|=0X08;if(flag){P4M1&=(0Xff^0x08);B_20=1;}else{P4M1|=0x08;B_20=0;}}
#define OEB(flag)  {oeb=flag;}//{P4M0|=0X10;if(flag){P4M1&=(0Xff^0x10);}else{P4M1|=0x10;}}
#define STRB(flag) {strb=flag;}//{P2M0|=0X01;if(flag){P2M1&=(0Xff^0x01);}else{P2M1|=0x01;}}
#define SCKB(flag) {sckb=flag;}//{P2M0|=0X02;if(flag){P2M1&=(0Xff^0x02);}else{P2M1|=0x02;}}
/*
sbit SDAA=P4^1;	//����	   
sbit OEA =P4^2;  //595ʹ��
sbit STRA=P4^3;	 //����
sbit SCKA=P4^4;	//ʱ��

sbit SDAB=P2^0;	//����
sbit OEB =P2^1;  //595ʹ��
sbit STRB=P2^2;	 //����
sbit SCKB=P2^3;	//ʱ�� */

//sbit SDAC=P3^4;	//����
sbit OEC =P4^0;  //����595ʹ��
//sbit STRC=P3^6;	 //����
//sbit SCKC=P3^7;	//ʱ��

//sbit OED =P4^4;  //����595ʹ��

sbit LED0=P4^5;	  //ƽ����ȦLED
sbit LED1=P0^5;	  //������ȦLED
sbit LED2=P4^7;	  //������ȦLED



void enableKey(unsigned char *dat);
void pressKey(unsigned char *dat);

extern void Send_data_A(uchar dat1/*,uchar dat2*/);
extern void Send_data_B(uchar temp1/*,uchar temp2*/);
//extern void start(void);
extern void dis_open(void);
extern void dis_close(void);
extern void delay(void);

#endif