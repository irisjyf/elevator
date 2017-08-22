#include "StdAfx.h"
#include "SerialProtocol.h"
#include "..\Define.h"
#include "..\ElevatorMgr.h"

//////////////////////////////////////////////////////////////////////
// CSerialProtocol class - 串行口通讯协议
//////////////////////////////////////////////////////////////////////
CSerialProtocol* CSerialProtocol::m_pSerial = NULL;
CSerialProtocol::CSerialProtocol()
{
	m_hComDev = INVALID_HANDLE_VALUE;
	m_nerrnum = 0;

	memset(m_pRecvBufs, 0 , BUFFER_LENGTH * sizeof(char));
	memset(m_pWriteBufs, 0 , BUFFER_LENGTH * sizeof(char));
	
	//m_config.Read();
}
CSerialProtocol::~CSerialProtocol()
{
	Disconnect();
}

CSerialProtocol *   CSerialProtocol::GetSerialProtocol()
{
	if(m_pSerial)
		return m_pSerial;
	else
		m_pSerial = new CSerialProtocol;
	return m_pSerial;
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
BOOL CSerialProtocol::Connect(CConfigInfo &config)
{
	//if (hComDev != INVALID_HANDLE_VALUE)
	//	Disconnect();

	HANDLE hComDev = ::CreateFile(config.m_szComPort, 
		GENERIC_READ | GENERIC_WRITE,
		0,                    // exclusive access
		NULL,                 // no security attrs
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL ); 
	if (hComDev == INVALID_HANDLE_VALUE)
		return FALSE;//CreateFile通信口失败！

	COMMTIMEOUTS  CommTimeOuts ;
	DCB dcb;
	COMMCONFIG cfg;

	cfg.dcb.DCBlength = sizeof( DCB ) ;
	BOOL bRet = FALSE;
	bRet = ::GetCommState( hComDev, &(cfg.dcb) ) ;

	::SetupComm( hComDev, 4096, 4096 ) ;

	::PurgeComm( hComDev, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR ) ; //清空缓冲
	dcb.DCBlength = sizeof( DCB ) ;

	bRet = ::GetCommState( hComDev, &dcb ) ;
	if(!bRet)
	{
		TRACE("GetCommState error!\n");
		return FALSE;
	}
	dcb.BaudRate	= config.m_dwBaudRate;
	dcb.ByteSize	= config.m_cByteSize;
	dcb.Parity		= config.m_cParity;
	dcb.StopBits	= config.m_cStopBits;

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
	int nReadConstant = config.m_nReadTimeout - 128 * ntm;
	if(nReadConstant < 0)
		nReadConstant = 0;
	CommTimeOuts.ReadIntervalTimeout			=	3;//字符间超时3毫秒,
	CommTimeOuts.ReadTotalTimeoutMultiplier		=	ntm;//wzq: 3
	CommTimeOuts.ReadTotalTimeoutConstant		=	nReadConstant;//静态超时 wzq:2
	CommTimeOuts.WriteTotalTimeoutMultiplier	=   ntm;//wzq:3
	CommTimeOuts.WriteTotalTimeoutConstant		=	100;//静态100毫秒

	if(!::SetCommTimeouts(hComDev , &CommTimeOuts ))
	{
		TRACE("SetCommTimeouts error!\n");
		return FALSE;
	}
	if (!::SetCommState( hComDev, &dcb ))
	{
		TRACE("SetCommState error!\n");
		return FALSE;//
	}

	if (hComDev != INVALID_HANDLE_VALUE)
	{
		::CloseHandle(hComDev);
		hComDev = INVALID_HANDLE_VALUE;
	}

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
		//先关闭串口
		if(IsConnect())
			Disconnect();

		if (Connect(config))
		{
			bOK = TRUE;
			//AfxMessageBox(_T("连接测试成功！"), MB_OK | MB_ICONINFORMATION);
		}
		else 
		{
			//AfxMessageBox(_T("连接测试失败！"), MB_OK | MB_ICONINFORMATION);
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
	{       
		return shCS;      
	}

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


void CSerialProtocol::Packet(unsigned char chType, unsigned int len, unsigned char *pbuf)
{
	unsigned char i;
	unsigned int sum = 0;
	unsigned char bao[80];

	for(i = 0;i< len - 2;i++)
	{
		bao[i]  =  pbuf[i];
	}
	pbuf[0]  =  0xef;
	pbuf[1]  =  0x01;

	pbuf[2]  =  chType;

	pbuf[3]  =  len / 256;
	pbuf[4]  =  len % 256;

	for(i  =  0;i<len-2;i++)
	{
		pbuf[5+i]  =  bao[i];
		sum  =  sum + bao[i];
	}
	sum = sum + len + chType;
	pbuf[4 + len - 1] = sum / 256;
	pbuf[4 + len] = sum % 256;
}
int CSerialProtocol::Send(unsigned char chPacketType, unsigned int iLength, unsigned char* pDatas)
{
	int iRet = 0;
	
	memset(m_pWriteBufs, 0, BUFFER_LENGTH);

	memcpy(m_pWriteBufs, pDatas, iLength);

	Packet(chPacketType, iLength + 2, m_pWriteBufs);

	if(IsConnect())
		iRet = SendData((BYTE *)m_pWriteBufs, iLength + 2 + 5);
	return iRet;
}
//通讯组包,并发送
//BOOL CSerialProtocol::Send(char chPacketType, short shLength, char * pDatas/*, CallBackRecv pCallbackRecv*/)
//{
//	//m_pfnCallbackRecv = pCallbackRecv;
//	int iLength =  shLength + sizeof(T_FRAMEHEAD) + 2;
//	short shCrc;
//	LPFRAMEHEAD lpFrame = (LPFRAMEHEAD) m_pWriteBufs;
//	lpFrame->chHead[0] = 0xef;
//	lpFrame->chHead[1] = 0x01;
//	lpFrame->chPacketType = chPacketType;
//	//lpFrame->chSectionOffset = 0x02;
//
//	//lpFrame->chAgentID[0] = 0xff;
//	//lpFrame->chAgentID[1] = 0xff;
//	lpFrame->chLength[0] = (shLength) / 256;
//	lpFrame->chLength[1] = (shLength) % 256;
//	BYTE *p = m_pWriteBufs + sizeof(T_FRAMEHEAD);
//	
//	shCrc = shLength 
//		+ chPacketType;
//		//+ lpFrame->chSectionOffset 
//		//+ lpFrame->chAgentID[0] * 256
//		//+ lpFrame->chAgentID[1];
//
//
//	for (int i=0; i<shLength; i++)
//	{
//		p[i] = pDatas[i];
//	}
//
//
//	short shRet = CalaCS((BYTE *)pDatas, shLength);
//
//	shCrc += shRet;
//	
//	p = m_pWriteBufs + sizeof(T_FRAMEHEAD) + shLength;
//	
//	p[0] = shCrc / 256;
//	p[1] = shCrc % 256;
//
//	if(IsConnect())
//		SendData((BYTE *)m_pWriteBufs, shLength + sizeof(T_FRAMEHEAD) + 2);
//
//	return TRUE;
//}


CString CSerialProtocol::GetConfigInfo()
{
	CString szInfo;
	szInfo.Format("通讯口：%s, 波特率:%d", m_config.m_szComPort, 
											m_config.m_dwBaudRate);
	return szInfo;
}

void CSerialProtocol::InitComm()
{
	m_config.Read();
	SetConfig(m_config);
	Connect();
}


void CSerialProtocol::stringToBytes(CString str1,unsigned char *dat)
{
	if (str1.IsEmpty())
		return;

	int pos;
	CString str=str1;
	for(int i=0;i<64; i++)
	{
		dat[i]=0;
	}

	for(int i=0;i<64;i++)
	{
		pos=str.Find(',');
		if(pos==-1)
		{//MessageBox(str);
			dat[atoi(str)-1]=1;
			//str=str.Right(pos+1);
			break;
		}
		//	MessageBox(str.Left(pos));
		dat[atoi(str.Left(pos))-1]=1;
		str=str.Mid(pos+1,str.GetLength());
	}
}

void CSerialProtocol::charToBytes(unsigned char *charArray,unsigned char *bitArray)
{
	for(int i=0;i<8;i++)
	{
		bitArray[i]=charToBin(charArray+i*8);
	}
} 

unsigned char CSerialProtocol::charToBin(unsigned char *dat) 
{
	unsigned char temp=0;
	for(int i=0;i<8;i++)
	{
		temp>>=1;
		if(dat[i]==1)
		{
			temp|=0x80;
		}
	}
	return temp;
}