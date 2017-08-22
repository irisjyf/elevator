#ifndef __IO__
#define __IO__

#include <intrins.h>
#include <string.h>
#include "STC15Fxxxx.h"
sbit SEL1 =P4^1;
sbit SEL2 =P4^2;
sbit SEL3 =P4^3;
sbit SEL4 =P4^4;

sbit LEDA =P2^0;
sbit LEDB =P2^1;
sbit LEDC =P2^2;
sbit LEDD =P2^3;
sbit LEDE =P2^4;
sbit LEDF =P2^5;
sbit LEDG =P2^6;
sbit LEDH =P2^7;
sbit JDQ  =P4^5;
sbit audio1=P0^2;
#define JDQON {P4M0|=0X20;P4M1&=0XDF;}
#define JDQOFF{P4M0|=0X20;P4M1|=0X20;}
#endif

