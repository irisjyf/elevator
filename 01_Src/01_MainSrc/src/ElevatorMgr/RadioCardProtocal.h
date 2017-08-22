#pragma once
#include "Comm/SerialProtocol.h"

//#define WRITE_TYPE 0x01
//#define READ_TYPE 0x02
//#define USER_TYPE 0x03
//#define MGRE_TYPE 0x04
//#define FUNC_TYPE 0x05


//写卡器对卡的操作命令
#define READ		0x01
#define WRITE		0x02

//子卡类型定义
#define TYPE_CARD_CUSTMER	0x01
#define TYPE_CARD_MGR		0x02
#define TYPE_CARD_FUNC		0x03

//功能卡中子类型定义
#define FUNC_TYPE_FORBIDEN 		0x01
#define FUNC_TYPE_CHECK_TIME 	0x02
#define FUNC_TYPE_SWITCH 		0x03
#define FUNC_TYPE_OFFSET 		0x04
#define FUNC_TYPE_AGENT 		0x05
#define FUNC_TYPE_Check 		0x06
#define FUNC_TYPE_CLEARBLACKLIST 	0x07
#define FUNC_TYPE_ENABLECOUNTER 	0x08
#define FUNC_TYPE_DISABLECOUNTER 	0x09


//写卡器命令定义
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
//#define IC_CMD_GET_ID		0x0E

#define READ		0x01
#define WRITE		0x02


#define STOP_PRODUCE_CMD 		0x00
#define START_PRODUCE_CMD 		0x01
#define ENABLE_PRODUCE_VERITY 	0x02
#define DISABLE_PRODUCE_VERITY 	0x03
#define WRITE_PRODUCE_PSW 		0x04
#define READ_PRODUCE_PSW 		0x05


#define TIMER_READ_USER_CARD 100
#define TIMER_READ_MGR_CARD 101
#define TIMER_READ_FUNC_CARD 102

#define  TYPE_USER	0x01
#define  TYPE_ADMIN	0x02
#define  TYPE_FUN	0x03


typedef struct _t_UserCardData
{

	BYTE dataHead[4];
	BYTE dataType[2];
	BYTE btCardNo[3];
	BYTE roomNum[2];//房间编号
	//buf[10] = pYonghuset->m_fjbh / 256;
	//buf[11] = pYonghuset->m_fjbh%256;
	BYTE limitType;// = pYonghuset->m_xzms + 1;限制模式
	BYTE authorType;//乘梯权限模式
	BYTE btStartYear;// = (m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	BYTE btStartMonth;// = m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	BYTE btStartDay;// = m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	BYTE btStartHour;// = m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	BYTE btStartMinute;// = m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;
	BYTE btEndYear;// = (m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	BYTE btEndMonth;// = m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	BYTE btEndDay;// = m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	BYTE btEndHour;// = m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	BYTE btEndMinute;// = m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;
	BYTE btCounts[2];// = m_sycs/256;
	//BYTE buf[25] = m_sycs%256;
	BYTE btElevator_1;//可用电梯1 = pYonghuset->m_kydt1;
	BYTE btFloor_1[8];//电梯1的楼层
	BYTE btElevator_2;//可用电梯1 = pYonghuset->m_kydt1;
	BYTE btFloor_2[8];//电梯1的楼层
	BYTE btElevator_3;//可用电梯1 = pYonghuset->m_kydt1;
	BYTE btFloor_3[8];//电梯1的楼层
	BYTE btElevator_4;//可用电梯1 = pYonghuset->m_kydt1;
	BYTE btFloor_4[8];//电梯1的楼层
	//buf[35] = pYonghuset->m_kydt2;
	//LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz2,dtkycxznum[1]);
	//LPSerialProtocol->charToBytes(dtkycxznum[1],buf+36);
	//buf[44] = pYonghuset->m_kydt3;
	//LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz3,dtkycxznum[2]);
	//LPSerialProtocol->charToBytes(dtkycxznum[2],buf+45);
}T_UserCardData, *LPT_UserCardData;


typedef struct _t_MgrCardData
{
	BYTE btHead[4];
	BYTE dataType[2];
	//buf[0]=2;  //写命令字
	//buf[1]=0xff;
	//buf[2]=0xff;
	//buf[3]=0xff;
	//buf[4]=0xff; //卡号
	//buf[5]=0x02; //卡类型
	//buf[6]=0x00; //子卡类型
	BYTE btCardNo[3];
	//buf[7]=m_glykh/65536;
	//buf[8]=m_glykh%65536/256;
	//buf[9]=m_glykh%65536%256;
	BYTE btRoomNo[2];
	//buf[10]=0;//m_fjbh/256;
	//buf[11]=0;//m_fjbh%256;
	BYTE btLimitType;//限制模式
	//buf[12]=m_xzms;
	BYTE btAuthorityType;
	//buf[13]=m_ctqxms;//乘梯权限模式
	//BYTE btStartTime[5];
	//buf[14]=(m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	//buf[15]=m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	//buf[16]=m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	//buf[17]=m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	//buf[18]=m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;
	//BYTE btEndTime[5];
	//buf[19]=(m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	//buf[20]=m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	//buf[21]=m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	//buf[22]=m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	//buf[23]=m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;
	BYTE btStartYear;// = (m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	BYTE btStartMonth;// = m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	BYTE btStartDay;// = m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	BYTE btStartHour;// = m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	BYTE btStartMinute;// = m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;
	BYTE btEndYear;// = (m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	BYTE btEndMonth;// = m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	BYTE btEndDay;// = m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	BYTE btEndHour;// = m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	BYTE btEndMinute;// = m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;

	BYTE btCounts[2];
	//buf[24]=m_sycs/256;
	//buf[25]=m_sycs%256;
	BYTE btElevator_1;
	BYTE btFloor_1[8];
	//buf[26]=pQuset->m_kydt1;
	//LPSerialProtocol->stringToBytes(m_dtkycxz1,dtkycxznum1[0]);
	//LPSerialProtocol->charToBytes(dtkycxznum1[0],buf+27);
	BYTE btElevator_2;
	BYTE btFloor_2[8];
	//buf[35]=pQuset->m_kydt2;
	//LPSerialProtocol->stringToBytes(m_dtkycxz2,dtkycxznum1[1]);
	//LPSerialProtocol->charToBytes(dtkycxznum1[1],buf+36);
	BYTE btElevator_3;
	BYTE btFloor_3[8];
	//buf[44]=pQuset->m_kydt3;
	//LPSerialProtocol->stringToBytes(m_dtkycxz3,dtkycxznum1[2]);
	//LPSerialProtocol->charToBytes(dtkycxznum1[2],buf+45);
	BYTE btElevator_4;
	BYTE btFloor_4[8];

}T_MgrCardData, *LPT_MgrCardData;

typedef struct _t_Data
{
	CString szReverseRecord;
	UINT uiElevatorID;
	CString szElevatorTime;
	UINT uiOffset;
	DWORD dwAgentNo;
	CString szIsAgentCheck;
	CString szDisableCounter;
	BYTE	btPassword[4];

}T_Data;

class CRadioCardProtocal
{
public:
	CRadioCardProtocal(void);
	CRadioCardProtocal(CSerialProtocol *pSieral);
	virtual ~CRadioCardProtocal(void);
	static CRadioCardProtocal *  GetRadioCardProtocal();
	DWORD	ReadSerialNo();
	BOOL	WriteUserData(BYTE*p, unsigned int length);
	BOOL	WriteManagerData(BYTE*p, unsigned int length);
	BOOL	WriteFuncData(BYTE*p, unsigned int length);
	BOOL	StartPruduceIC(void);
	BOOL	StopPruduceIC(void);
	BOOL	EnableVerityPruduceFlag(void);
	BOOL	DisableVerityPruduceFlag(void);
	void	ClearCardPsw();
	BOOL	WriteProxySerialNo(short shNum);
	//制作偏置卡
	BOOL	WriteOffsetCard(BYTE btData[], int nLen);
	//将偏置数据写入到写卡器中
	BOOL	WriteOffset(BYTE btOffset);
	BOOL	WriteAgentIDCard(DWORD dwAgentID, BOOL bUseAgent);
	BOOL	WriteAgentID(DWORD dwAgentID);
	BOOL	CheckProduceData();
	BOOL	ReadInterParam(T_Data &tData);
	BOOL	ReadWriterOffset(int& iOffset);
	BOOL	ReadWriterID(DWORD& dwData, BYTE& byProduceFlag, BYTE& byReverseFlag);
	BOOL	ReadSectionPassword(unsigned char chDatas[], int& nLen);
	BOOL	WriteSectionPassword(const unsigned char chDatas[], int nLen);
	BOOL	WriteOffsetPswCard(BYTE btData[], int nLen);
	BOOL	WriteOffsetPsw(BYTE btData[], int nLen);
	BOOL	ConnectTest(void);
private:
	CSerialProtocol *m_pCom;
	DWORD GetCardSerialNo(BYTE* p, unsigned int length);
	DWORD GetWriteDataResult(BYTE* pDatas, unsigned int length);
	DWORD GetWriteUserResult(BYTE* pDatas, unsigned int length);
	DWORD GetWriteMgrResult(BYTE* pDatas, unsigned int length);
	DWORD GetWriteFuncResult(BYTE* pDatas, unsigned int length);
	DWORD GetProduceFuncResult(BYTE* pDatas, unsigned int length);
	DWORD GetWriterOffsetResult(BYTE* pDatas, unsigned int& iOffset, unsigned int length);
	DWORD ReadWriteOffsetData(int &iOffset, BYTE* pDatas, unsigned int length);
	DWORD GetWriteOffsetCardResult(BYTE* pDatas, unsigned int length);
	DWORD GetWriteAgentResult(BYTE* pDatas, unsigned int length);
	DWORD ReadWriterAgentID(DWORD &dwData, 
		BYTE& byProduceFlag, 
		BYTE& byReverseFlag, 
		BYTE* pDatas, unsigned int length);
	BOOL  GetWriteSectionPasswordResult(unsigned char pDatas[], unsigned int length);
	BOOL  GetReadSectionPasswordResult(unsigned char pDatas[], unsigned int length, unsigned char pSectionPsw[], int& iLen);
};

