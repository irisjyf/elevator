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

#define MSG_READ_CUSTOMER_INFO  3 //��ȡ�û���Ϣ 




#pragma pack(1)
typedef struct tagDATAHEADER //��ͷ�ṹ
{
	BYTE btFlag1;          //���ı�ʶEF
	BYTE btFlag2;          //���ı�ʶ01
	BYTE btCode;           // ������
	short  shLen;          // ����
}DATAHEADER, *LPDATAHEADER;

typedef struct tagDATAHEADEREX //��ͷ�ṹ
{
	BYTE btFlag1;               //���ı�ʶEF
	BYTE btFlag2;               //���ı�ʶ01
	BYTE btPacketType;          //������
	BYTE btSectionBase;         //������
	short  shLen;               // ����
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

typedef struct tagDATAEND //��ͷ�ṹ
{
	short  shCS;          // У�� �����˰�ͷ��
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

/////////////////////////////////���ݿ���Ϣ///////////////////////////////////////////
#include <afxdb.h>
#include <odbcinst.h>

#define  DB_NAME  "dzs"
#define  DB_PSW   "fingerlock"


