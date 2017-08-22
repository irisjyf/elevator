#pragma once

#define BUFFER_SIZE     1024

#define	 ADD_TYPE   0
#define	 MOD_TYPE   1
#define	 DEL_TYPE   2

#define  FLOOR_CODE    1  
#define  FLOOR_CHIOCE  2  



#define	 CARD_CUSTERMER_TYPE   1
#define	 CARD_MANAGER_TYPE     2
#define	 CARD_FUNCTION_TYPE    3

#define MSG_READ_CUSTOMER_INFO  3 //读取用户信息 




#pragma pack(1)
typedef struct tagDATAHEADER //报头结构
{
	BYTE btFlag1;          //报文标识EF
	BYTE btFlag2;          //报文标识01
	BYTE btCode;           // 功能码
	short  shLen;          // 长度
}DATAHEADER, *LPDATAHEADER;

typedef struct tagDATAHEADEREX //报头结构
{
	BYTE btFlag1;               //报文标识EF
	BYTE btFlag2;               //报文标识01
	BYTE btPacketType;          //包类型
	BYTE btSectionBase;         //扇区号
	short  shLen;               // 长度
}DATAHEADEREX, *LPDATAHEADEREX;


typedef struct frameHead
{
	char chHead[2];
	char chPacketType;
	//char chSectionOffset;
	//char chAgentID[2];
	char chLength[2];
}T_FRAMEHEAD, *LPFRAMEHEAD;


typedef struct frameRetHead
{
	char chHead[2];
	char chPacketType;
	char chLength[2];
}T_FRAME_RET_HEAD, *LPFRAME_RET_HEAD;

typedef struct tagDATAEND //报头结构
{
	short  shCS;          // 校验 （除了包头）
}DATAEND, *LPDATAEND;



#pragma pack()




#define	 ADD_TYPE   0
#define	 MOD_TYPE   1
#define	 DEL_TYPE   2


#define	 CARD_CUSTERMER_TYPE   1
#define	 CARD_MANAGER_TYPE     2
#define	 CARD_FUNCTION_TYPE    3

#define SERIALID		0x01

#define READ		0x01
#define WRITE		0x02

/////////////////////////////////数据库信息///////////////////////////////////////////
#include <afxdb.h>
#include <odbcinst.h>

#define  DB_NAME  "dzs"
#define  DB_PSW   "fingerlock"


