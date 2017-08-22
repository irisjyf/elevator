#ifndef __74HC595_H__
#define	__74HC595_H__
//#include "config.h"
#include "STC15Fxxxx.h"
sbit ray =P2^2;
#define RELAYON  {P2M0|=0X04;P2M1&=0XFB;ray=1;}
#define RELAYOFF {P2M0|=0X04;P2M1|=0X04;ray=0;}
//#include	"MyType.h"
/*
sbit SDAA=P2^4;	//数据
sbit OEA =P2^5;  //595使能
sbit STRA=P2^6;	 //锁存
sbit SCKA=P2^7;	//时钟

sbit SDAB=P2^0;	//数据
sbit OEB =P2^1;  //595使能
sbit STRB=P2^2;	 //锁存
sbit SCKB=P2^3;	//时钟

sbit SDAC=P3^4;	//数据
sbit OEC =P3^0;  //侧面595使能
sbit STRC=P3^6;	 //锁存
sbit SCKC=P3^7;	//时钟

sbit OED =P4^4;  //侧面595使能

sbit LED0=P4^5;	  //平面外圈LED
sbit LED1=P3^1;	  //侧面外圈LED

*/
sbit B_20=P4^3;	//时钟
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
sbit SDAA=P4^1;	//数据	   
sbit OEA =P4^2;  //595使能
sbit STRA=P4^3;	 //锁存
sbit SCKA=P4^4;	//时钟

sbit SDAB=P2^0;	//数据
sbit OEB =P2^1;  //595使能
sbit STRB=P2^2;	 //锁存
sbit SCKB=P2^3;	//时钟 */

//sbit SDAC=P3^4;	//数据
sbit OEC =P4^0;  //侧面595使能
//sbit STRC=P3^6;	 //锁存
//sbit SCKC=P3^7;	//时钟

//sbit OED =P4^4;  //侧面595使能

sbit LED0=P4^5;	  //平面外圈LED
sbit LED1=P0^5;	  //侧面外圈LED
sbit LED2=P4^7;	  //侧面外圈LED



void enableKey(unsigned char *dat);
void pressKey(unsigned char *dat);

extern void Send_data_A(uchar dat1/*,uchar dat2*/);
extern void Send_data_B(uchar temp1/*,uchar temp2*/);
//extern void start(void);
extern void dis_open(void);
extern void dis_close(void);
extern void delay(void);

#endif