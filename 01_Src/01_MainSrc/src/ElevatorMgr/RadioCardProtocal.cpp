#include "StdAfx.h"
#include "ElevatorMgr.h"
#include "RadioCardProtocal.h"

CRadioCardProtocal::CRadioCardProtocal(void)
	:m_pCom(NULL)
{
}

CRadioCardProtocal::CRadioCardProtocal(CSerialProtocol *pSieral)
	:m_pCom(pSieral)
{

}
CRadioCardProtocal::~CRadioCardProtocal(void)
{
}

CRadioCardProtocal*  CRadioCardProtocal::GetRadioCardProtocal()
{
	return theApp.m_pRadioCardProtocol;
}
DWORD CRadioCardProtocal::ReadSerialNo()
{
	unsigned char chBuf[20] = {0};
	chBuf[0] = READ;
	chBuf[1] = SERIALID;
	BYTE chRecvBuf[500] = {0};
	LPSerialProtocol->Send(IC_CMD_GETSERIAL, 3, chBuf/*, NULL*/);	
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet ==0)
			return 0;
	}
	DWORD dwSerialNo = GetCardSerialNo(chRecvBuf, iRet);
	return dwSerialNo;
}

BOOL	CRadioCardProtocal::WriteUserData(BYTE*p, unsigned int length)
{
	if(NULL == m_pCom)
		return FALSE;
	BYTE chRecvBuf[500] = {0};
	m_pCom->Send(IC_CMD_CUSTOMER, length,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = m_pCom->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = m_pCom->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return FALSE;
	}
	DWORD dwRet = GetWriteUserResult(chRecvBuf, iRet);
	if(dwRet == Do_False)
		return FALSE;
	return TRUE;
}


BOOL	CRadioCardProtocal::WriteManagerData(BYTE*p, unsigned int length)
{
	BYTE chRecvBuf[500] = {0};
	LPSerialProtocol->Send(IC_CMD_MANAGER, length,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	DWORD dwRet = GetWriteMgrResult(chRecvBuf, iRet);
	if(dwRet == Do_False)
		return FALSE;
	return TRUE;
}


BOOL	CRadioCardProtocal::WriteFuncData(BYTE*p, unsigned int length)
{
	BYTE chRecvBuf[500] = {0};	
	LPSerialProtocol->Send(IC_CMD_FUNC, length, (unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	DWORD dwRet = GetWriteFuncResult(chRecvBuf, iRet);
	if(dwRet == Do_False)
		return FALSE;
	return TRUE;
}


BOOL CRadioCardProtocal::WriteOffsetPswCard(BYTE btData[], int nLen)
{
	BYTE chData[72] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = 2;  //写命令字
	chData[1] = 0xff;
	chData[2] = 0xff;
	chData[3] = 0xff;
	chData[4] = 0xff; //卡号
	chData[5] = 0x03; //卡类型
	chData[6] = FUNC_TYPE_OFFSET; //子卡类型
	memcpy(chData + 7, btData, nLen);
	
	LPSerialProtocol->Send(IC_CMD_FUNC, 72, (unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	DWORD dwRet = GetWriteFuncResult(chRecvBuf, iRet);
	if(dwRet == Do_False)
		return FALSE;
	return TRUE;
}


BOOL CRadioCardProtocal::WriteOffsetPsw(BYTE btData[], int nLen)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = WRITE;  //写命令字
	memcpy(chData + 1, btData, nLen);
	LPSerialProtocol->Send(IC_CMD_OFFSET, nLen + 1,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return FALSE;
	}
	unsigned iOffset = 0;
	iRet = GetWriterOffsetResult(chRecvBuf,iOffset, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}

BOOL CRadioCardProtocal::WriteOffsetCard(BYTE btData[], int nLen)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = 2;  //写命令字
	chData[1] = 0xff;
	chData[2] = 0xff;
	chData[3] = 0xff;
	chData[4] = 0xff; //卡号
	chData[5] = 0x03; //卡类型
	chData[6] = FUNC_TYPE_OFFSET; //子卡类型
	chData[7] = btData[0]; //子卡类型
	chData[8] = btData[1]; //子卡类型
	chData[9] = btData[2]; //子卡类型
	chData[10] = btData[3]; //子卡类型
	chData[11] = btData[4]; //子卡类型

	LPSerialProtocol->Send(IC_CMD_FUNC, 72,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}

BOOL CRadioCardProtocal::WriteOffset(BYTE btOffset)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = WRITE;  //写命令字
	chData[1] = btOffset;
	chData[2] = 0;
	LPSerialProtocol->Send(IC_CMD_OFFSET, 3,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	unsigned iOffset = 0;
	iRet = GetWriterOffsetResult(chRecvBuf,iOffset, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
BOOL CRadioCardProtocal::WriteAgentIDCard(DWORD dwAgentID, BOOL bUseAgent)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = 2;  //写命令字
	chData[1] = 0xff;
	chData[2] = 0xff;
	chData[3] = 0xff;
	chData[4] = 0xff; //卡号
	chData[5] = 0x03; //卡类型
	chData[6] = FUNC_TYPE_AGENT; //子卡类型
	chData[7] = (dwAgentID >> 24) & 0xff;
	chData[8] = (dwAgentID >> 16) & 0xff;
	chData[9] = (dwAgentID >> 8)  & 0xff;
	chData[10] = dwAgentID & 0xff;
	chData[11] = 0;
	if(bUseAgent)
		chData[11] = 0xAA;
	LPSerialProtocol->Send(IC_CMD_FUNC, 72,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
BOOL CRadioCardProtocal::WriteAgentID(DWORD dwAgentID)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = WRITE;  //写命令字
	chData[1] = (dwAgentID >> 24) & 0xff;
	chData[2] = (dwAgentID >> 16) & 0xff;
	chData[3] = (dwAgentID >> 8)  & 0xff;
	chData[4] = (dwAgentID >> 0) & 0xff;
	chData[5] = 0;
	LPSerialProtocol->Send(IC_CMD_AGENT, 6,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetWriteAgentResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
BOOL  CRadioCardProtocal::StartPruduceIC(void)
{
	BYTE p[] = { START_PRODUCE_CMD,0x0F, 0xF0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 4,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}


BOOL  CRadioCardProtocal::StopPruduceIC(void)
{
	//开始生产 g_ucProductFlag == 0xFF
	//停止生产条件 g_ucProductFlag != 0xFF
	BYTE p[] = {STOP_PRODUCE_CMD, 0x0A, 0xB0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 4,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
BOOL CRadioCardProtocal::EnableVerityPruduceFlag(void)
{
	BYTE p[] = {ENABLE_PRODUCE_VERITY, 0x0A, 0xB0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 4,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
BOOL CRadioCardProtocal::DisableVerityPruduceFlag(void)
{
	BYTE p[] = {DISABLE_PRODUCE_VERITY, 0x0A, 0xB0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 4,(unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}

void	CRadioCardProtocal::ClearCardPsw()
{

	BYTE p[] = { START_PRODUCE_CMD,0x0A, 0xA0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 4,(unsigned char *)p/*, NULL*/);

}
BOOL	CRadioCardProtocal::WriteProxySerialNo(short shNum)
{
	//g_ucProductFlag == 0xAA  开始生产
	//g_ucProductFlag != 0xAA  
	BYTE p[] = {0x0A, 0xA0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 3, (unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = GetProduceFuncResult(chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}

BOOL	CRadioCardProtocal::ReadInterParam(T_Data &tData)
{
	BYTE p[] = {0x0A, 0xA0, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	LPSerialProtocol->Send(IC_CMD_GET_CHECK, 3, (unsigned char *)p/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return FALSE;
	}
	if(iRet < sizeof(T_FRAME_RET_HEAD))
		return FALSE;

	//数据检验
	if(!CheckCrc(chRecvBuf, iRet))
		return FALSE;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) chRecvBuf;
	if(lpFrameHead->chPacketType != IC_CMD_GET_CHECK)
		return FALSE;

	BYTE *pData = NULL;
	pData = chRecvBuf + sizeof(T_FRAME_RET_HEAD);
	if(pData[0] != Do_True && pData[1] != IC_CMD_GET_CHECK)
		return FALSE;
	pData += 2;

	tData.uiOffset = pData[0];
	if((pData[1] & AGENTCHECK) == AGENTCHECK)
		tData.szIsAgentCheck = "是";
	else
		tData.szIsAgentCheck = "否";


	if(pData[1] != 0xFF && (pData[1] & DISABLECOUNTER) == DISABLECOUNTER)
		tData.szDisableCounter = "无效";
	else
		tData.szDisableCounter = "有效";

	DWORD dwAgentNo = 0;

	dwAgentNo += (pData[2]<<24);
	dwAgentNo += (pData[3]<<16);
	dwAgentNo += (pData[4]<<8);
	dwAgentNo += pData[5];
	if(dwAgentNo == 0xFFFFFFFF)
		dwAgentNo = 0;
	tData.dwAgentNo = dwAgentNo;

	tData.uiElevatorID = pData[6];

	int iYear = (pData[7] >> 4 & 0x0f) * 10 + (pData[7] & 0xf) + 2000;
	int iMonth = (pData[8] >> 4 & 0x0f) * 10 + (pData[8] & 0xf);
	int iDay = (pData[9] >> 4 & 0x0f) * 10 + (pData[9] & 0xf);
	int iHour = (pData[10] >> 4 & 0x0f) * 10 + (pData[10] & 0xf);
	int iMinute = (pData[11] >> 4) * 10 + (pData[11] & 0xf);
	int iSecond = (pData[12] >> 4) * 10 + (pData[12] & 0xf);

	tData.szElevatorTime.Format("%d-%d-%d %d:%d:%d", 
		iYear,
		iMonth,
		iDay,
		iHour,
		iMinute,
		iSecond);

	if(pData[14] == DO_REVERSE)
		tData.szReverseRecord = "防复制开启";
	else if(pData[14] == DIS_REVERSE)
		tData.szReverseRecord = "防复制关闭";
	tData.btPassword[0] = pData[16];
	tData.btPassword[1] = pData[16 + 1];
	tData.btPassword[2] = pData[16 + 2];
	tData.btPassword[3] = pData[16 + 3];
	return TRUE;
}

BOOL	CRadioCardProtocal::ReadWriterOffset(int& iOffset)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = READ;  //写命令字
	chData[1] = 0;
	chData[2] = 0;
	LPSerialProtocol->Send(IC_CMD_OFFSET, 3,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = ReadWriteOffsetData(iOffset, chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}

BOOL CRadioCardProtocal::ReadWriterID(DWORD& dwData, BYTE& byProduceFlag, BYTE& byReverseFlag)
{
	BYTE chData[71] = {0};
	BYTE chRecvBuf[500] = {0};
	chData[0] = READ;  //写命令字
	chData[1] = 0;
	chData[2] = 0;
	LPSerialProtocol->Send(IC_CMD_AGENT, 3,(unsigned char *)chData/*, NULL*/);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	iRet = ReadWriterAgentID(dwData, byProduceFlag, byReverseFlag, chRecvBuf, 500);
	if(iRet == Do_True)
		return TRUE;
	return FALSE;
}
DWORD	CRadioCardProtocal::GetCardSerialNo(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_GETSERIAL)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return 0;
	DWORD *pdwSerial = (DWORD *)(p + 2);
	return *pdwSerial;
}

DWORD	CRadioCardProtocal::GetWriteDataResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;
	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;
	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_WRITE)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}

DWORD CRadioCardProtocal::GetWriteUserResult(BYTE* pDatas, unsigned int length)
{

	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;
	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;
	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_CUSTOMER)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}
DWORD CRadioCardProtocal::GetWriteFuncResult(BYTE* pDatas, unsigned int length)
{
	if(NULL == pDatas || length < sizeof(T_FRAME_RET_HEAD))
		return 0;
	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_FUNC)
		return 0;
	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}
DWORD CRadioCardProtocal::GetWriteMgrResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;
	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;
	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_MANAGER)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}
DWORD CRadioCardProtocal::GetProduceFuncResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_FUNC)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}

DWORD CRadioCardProtocal::GetWriteOffsetCardResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_FUNC)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}
DWORD CRadioCardProtocal::GetWriterOffsetResult(BYTE* pDatas, unsigned int& iOffset, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_OFFSET)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	iOffset = p[2];

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}

DWORD CRadioCardProtocal::ReadWriteOffsetData(int &iOffset, BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_OFFSET)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	iOffset = p[2];

	if(p[0] != Do_True)
		return Do_False;
	iOffset = p[2];

	return Do_True;
}


DWORD CRadioCardProtocal::GetWriteAgentResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_AGENT)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != Do_True)
		return Do_False;
	return Do_True;
}


BOOL CRadioCardProtocal::CheckProduceData()
{
	BYTE chRecvBuf[30];
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 30);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 30);
		if(iRet == 0)
			return 0;
	}
	if(iRet < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(chRecvBuf, iRet))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) chRecvBuf;
	if(lpFrameHead->chPacketType != IC_CMD_PRODUCT)
		return 0;

	BYTE *p = NULL;
	p = chRecvBuf + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != 0x01 || p[1] != 0x10)
		return Do_False;
	return Do_True;
}

DWORD CRadioCardProtocal::ReadWriterAgentID(DWORD &dwData, 
	BYTE& byProduceFlag, 
	BYTE& byReverseFlag, 
	BYTE* pDatas, unsigned int length)
{
	if(NULL == pDatas || length < sizeof(T_FRAME_RET_HEAD))
		return 0;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return 0;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_AGENT)
		return 0;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);


	dwData = (p[2] & 0xFF) << 24;
	dwData += (p[3] & 0xFF) << 16; 
	dwData += (p[4] & 0xFF) << 8; 
	dwData += p[5];
	byProduceFlag = p[6];
	byReverseFlag = p[7];
	if (p[0] == Do_True)
		return Do_True;
	return Do_False;
}


BOOL CRadioCardProtocal::ReadSectionPassword(unsigned char chDatas[], int& nLen)
{
	unsigned char p[] = {READ_PRODUCE_PSW, 0x00, 0x00, 0x00, 0x00};
	unsigned char chRecvBuf[500] = {0}; 
	unsigned char chResult[4];
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 5, p);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	BOOL bRet = GetReadSectionPasswordResult(chRecvBuf, 500, chDatas, nLen);
	return bRet;
}


BOOL CRadioCardProtocal::GetReadSectionPasswordResult(unsigned char pDatas[], unsigned int length, unsigned char pSectionPsw[], int& iLen)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return FALSE;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return FALSE;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_PRODUCT)
		return FALSE;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != READ_PRODUCE_PSW)
		return FALSE;
	memcpy(pSectionPsw, p + 1, 5);

	iLen = 4;
	return TRUE;
}

BOOL CRadioCardProtocal::WriteSectionPassword(const unsigned char chDatas[], int nLen)
{
	unsigned char p[] = {WRITE_PRODUCE_PSW, 0x00, 0x00, 0x00, 0x00};
	BYTE chRecvBuf[500] = {0}; 
	memcpy(p + 1, chDatas, 4);
	LPSerialProtocol->Send(IC_CMD_PRODUCT, 5, p);
	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
	if(iRet == 0)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(chRecvBuf, 500);
		if(iRet == 0)
			return 0;
	}
	BOOL bRet  = GetWriteSectionPasswordResult(chRecvBuf, 500);
	
	return bRet;
}

BOOL CRadioCardProtocal::GetWriteSectionPasswordResult(BYTE* pDatas, unsigned int length)
{
	if(length < sizeof(T_FRAME_RET_HEAD))
		return FALSE;

	//数据检验
	if(!CheckCrc(pDatas, length))
		return FALSE;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
	if(lpFrameHead->chPacketType != IC_CMD_PRODUCT)
		return FALSE;

	BYTE *p = NULL;
	p = pDatas + sizeof(T_FRAME_RET_HEAD);

	if(p[0] != WRITE_PRODUCE_PSW)
		return FALSE;
	if(p[1] != Do_True)
		return TRUE;
	return FALSE;
}

BOOL	CRadioCardProtocal::ConnectTest(void)
{
	BOOL bRet = FALSE;
	BYTE byRecvBuf[50];
	unsigned char p[] = {0x01, 0x01, 0x01, 0x01, 0x01};
	LPSerialProtocol->Send(IC_CMD_TEST, 5, p);

	Sleep(300);
	int iRet = LPSerialProtocol->ReadData(byRecvBuf, 50);
	if(iRet <= 5)
	{
		Sleep(300);
		iRet = LPSerialProtocol->ReadData(byRecvBuf, 50);
		if(iRet <= 5)
			return FALSE;
	}

	if(iRet < sizeof(T_FRAME_RET_HEAD))
		return FALSE;

	//数据检验
	if(!CheckCrc(byRecvBuf, iRet))
		return FALSE;

	LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) byRecvBuf;
	if(lpFrameHead->chPacketType != IC_CMD_TEST)
		return FALSE;
	BYTE* pData = byRecvBuf + sizeof(T_FRAME_RET_HEAD);
	for (int i=1; i < 5; i++)
	{
		if(pData[i] != 0xEE)
			return FALSE;
	}
	return TRUE;
}

