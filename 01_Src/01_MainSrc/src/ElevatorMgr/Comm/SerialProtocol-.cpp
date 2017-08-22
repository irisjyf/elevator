#include "StdAfx.h"
#include "SerialProtocol.h"
#include "..\testskin.h"
#include "..\Define.h"

//////////////////////////////////////////////////////////////////////
// CSerialProtocol class - 串行口通讯协议
//////////////////////////////////////////////////////////////////////
CSerialProtocol::CSerialProtocol()
{
	m_hComDev = INVALID_HANDLE_VALUE;
	m_nerrnum = 0;

	m_config.Read();
}

CSerialProtocol::~CSerialProtocol()
{
	Disconnect();
}
CSerialProtocol *   CSerialProtocol::GetSerialProtocol()
{
	return &theApp.m_SerialProtocol;
}

BOOL CSerialProtocol::IsConnect()
{
	return (m_hComDev != INVALID_HANDLE_VALUE);
}

BOOL CSerialProtocol::Connect()
{
	if (m_hComDev != INVALID_HANDLE_VALUE)
		Disconnect();

	m_hComDev = ::CreateFile(m_config.m_szComPort, 
		GENERIC_READ | GENERIC_WRITE,
		0,                    // exclusive access
		NULL,                 // no security attrs
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL ); 
	if (m_hComDev == INVALID_HANDLE_VALUE)
		return FALSE;//CreateFile通信口失败！
	
	COMMTIMEOUTS  CommTimeOuts ;
	DCB dcb;
	COMMCONFIG cfg;
	
	cfg.dcb.DCBlength = sizeof( DCB ) ;
	BOOL bRet = FALSE;
	bRet = ::GetCommState( m_hComDev, &(cfg.dcb) ) ;
	
	::SetupComm( m_hComDev, 4096, 4096 ) ;
    
	::PurgeComm( m_hComDev, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR ) ; //清空缓冲
	dcb.DCBlength = sizeof( DCB ) ;
	
	bRet = ::GetCommState( m_hComDev, &dcb ) ;
	if(!bRet)
	{
		TRACE("GetCommState error!\n");
		return FALSE;
	}
	dcb.BaudRate	= m_config.m_dwBaudRate;
	dcb.ByteSize	= m_config.m_cByteSize;
	dcb.Parity		= m_config.m_cParity;
	dcb.StopBits	= m_config.m_cStopBits;
	
	// setup hardware flow control硬件流控制无
	dcb.fDtrControl = DTR_CONTROL_DISABLE ;// 485转接器用DTR_CONTROL_ENABLE
	dcb.fOutxCtsFlow = FALSE ;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
	
	// setup software flow control软件流控制无
	dcb.fInX = dcb.fOutX = FALSE ;
	
	// other various settings
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;
	
	// set up for overlapped I/O
	int ntm = (2*9600)/dcb.BaudRate;
	if(ntm <= 0)
		ntm = 1;
	int nReadConstant = m_config.m_nReadTimeout - 128 * ntm;
	if(nReadConstant < 0)
		nReadConstant = 0;
	CommTimeOuts.ReadIntervalTimeout			=	3;//字符间超时3毫秒,
	CommTimeOuts.ReadTotalTimeoutMultiplier		=	ntm;//wzq: 3
	CommTimeOuts.ReadTotalTimeoutConstant		=	nReadConstant;//静态超时 wzq:2
	CommTimeOuts.WriteTotalTimeoutMultiplier	=   ntm;//wzq:3
	CommTimeOuts.WriteTotalTimeoutConstant		=	100;//静态100毫秒
	
	if(!::SetCommTimeouts(m_hComDev , &CommTimeOuts ))
	{
		TRACE("SetCommTimeouts error!\n");
		return FALSE;
	}
	if (!::SetCommState( m_hComDev, &dcb ))
	{
		TRACE("SetCommState error!\n");
		return FALSE;//
	}
	m_nerrnum = 0;
	return TRUE;
}

void CSerialProtocol::Disconnect()
{
	if (m_hComDev != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(m_hComDev);
		m_hComDev = INVALID_HANDLE_VALUE;
	}
}

BOOL CSerialProtocol::TestConnect(CConfigInfo &config)
{
	BOOL bOK = FALSE;
	try
	{
		SetConfig(config);
		if (Connect())
		{
			bOK = TRUE;
			Disconnect();
			AfxMessageBox(_T("连接测试成功！"), MB_OK | MB_ICONINFORMATION);
		}
		else {
			AfxMessageBox(_T("连接测试失败！"), MB_OK | MB_ICONINFORMATION);
		}
	}
	catch (...)
	{
		;
	}
	
	// 设置协议处理类实例的相关参数

	return bOK;
}

int	CSerialProtocol::SendData(BYTE *pb, int nsize)
{
	if (!IsConnect())
		return FALSE;

	COMSTAT comstat;
	DWORD dwErrorMask;
	DWORD dwWriteNum = 0;
	BOOL bret = ::WriteFile(
		m_hComDev,      // handle to file
		pb,             // data buffer
		nsize,				// number of bytes to write
		&dwWriteNum,		// number of bytes written
		NULL			// overlapped buffer
		);
	if (!bret)
	{
		::ClearCommError(m_hComDev, &dwErrorMask, &comstat);//清除错误
		::PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);//清空驱动程序中的缓冲区
		
		m_nerrnum++;
		if(m_nerrnum > 10)
		{
			Disconnect();
			Sleep(50);
			Connect();
			m_nerrnum = 0;
		}
		return bret;
	}
	if(dwWriteNum == 0)
		return FALSE;

	m_nerrnum = 0;
	return TRUE;
}


short  CSerialProtocol::CalaCS(BYTE *pData, int iSize)
{
	short shCS = 0;
	if (pData == NULL || iSize <= 0)
	{       return shCS;      }

	for (int i = 0 ; i < iSize; i++ )
	{
		shCS += pData[i];
	}
	return shCS;
}


int	CSerialProtocol::ReadData(BYTE *pb, int nsize)
{
	if (!IsConnect())
		return 0;

	BOOL bret;
	DWORD dwReadNum=0;
	COMSTAT comstat;
	DWORD dwErrorMask;
	//if (nsize > BUF_LENGTH_SERIAL) nsize = BUF_LENGTH_SERIAL;//wzq 20091009
	bret = ::ReadFile(m_hComDev, pb, nsize, &dwReadNum, NULL);
	if (!bret)
	{
		::ClearCommError(m_hComDev, &dwErrorMask, &comstat);//清除错误
		::PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR);//清空驱动程序中的缓冲区
		
		m_nerrnum++;
		if(m_nerrnum > 10)
		{
			Disconnect();
			Sleep(50);
			Connect();
			m_nerrnum = 0;
		}
		return 0;
	}

	m_nerrnum = 0;
	return (int)dwReadNum;
}

BOOL CSerialProtocol::DoRead(BYTE btTypeCode)
{

	return TRUE;
}

BOOL CSerialProtocol::DoSend(BYTE btTypeCode)
{

	BYTE sBuf[BUFFER_SIZE] = {0xEF,0x01,0,0};
	int iMsgLenth = 0;

	if (btTypeCode == MSG_READ_CUSTOMER_INFO)
	{
		DATAHEADER * pDATAHEADER = (DATAHEADER *)sBuf;
		pDATAHEADER->btCode = btTypeCode;
		pDATAHEADER->shLen   = 3;
		DATAEND * pDATAEND = (DATAEND* )(sBuf +sizeof(DATAHEADER) );
		pDATAEND->shCS = CalaCS(sBuf+2,4);
		iMsgLenth  = 8;
	}


	int nsize = SendData(sBuf,iMsgLenth); 
	if (0 == nsize)
		return FALSE;

    Sleep(20);
	return TRUE;

	return TRUE;
}

