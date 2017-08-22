// ddclib.cpp: implementation of the CDDCDrvObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ConfigInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DRVCFG_VERSION		(DRVCFG_VERSION_USER + 4)


CString GetSystemErrorMessage(DWORD dwErrorCode)
{
	TCHAR *pBuffer = NULL;

	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dwErrorCode,
				0,
				(LPTSTR)&pBuffer,
				0,
				NULL);

	CString szMsg;
	if (pBuffer)
	{
		szMsg = pBuffer;
		::LocalFree(pBuffer);
	}
	else {
		szMsg = _T("��ȡ������Ϣʧ��");
	}

	return szMsg;
}


//////////////////////////////////////////////////////////////////////
// CConfigInfo class Construction/Destruction
//////////////////////////////////////////////////////////////////////
CConfigInfo::CConfigInfo()
	: m_bModified(FALSE)
	, m_wComType(COM_TYPE_COM)
	, m_szIP(_T("127.0.0.1"))
	, m_wPort(10000)
	, m_szComPort(_T("\\\\.\\com1"))
	, m_dwBaudRate(CBR_9600)
	, m_cByteSize( 8)
	, m_cParity(0)
	, m_cStopBits(0)
	, m_nReadTimeout(200)
	, m_nWriteTimeout(200)
	, m_bDebug(FALSE)
	, m_nUpdateSec(1000)
	, m_bLocalTime(FALSE)
	, m_nTimeBias(0)
	, m_nTimeOffset(0)
	, m_bAutoDeleteFile(FALSE)
	, m_strSectionType(_T("����1"))
	, m_strEncryp(_T("������"))
	, m_strDBPath(_T(""))
{
}

CConfigInfo::~CConfigInfo()
{

}

void CConfigInfo::Serialize(CArchive& ar, DWORD dwVersion)
{
	if (ar.IsLoading())
	{
		ar >> m_wComType >> m_szIP >> m_wPort >> m_szComPort >> m_dwBaudRate >> 
			m_cByteSize >> m_cParity >> m_cStopBits >> m_nReadTimeout >> 
			m_nWriteTimeout >> m_nUpdateSec >> m_bDebug;

			ar >> m_bLocalTime >> m_nTimeBias;

			ar >> m_strSectionType >> m_strEncryp;//ar >> m_szTcpUdpParam >> m_szComParam;

			ar >> m_szDataSource >> m_szPsw >> m_szID;
			
			ar >> m_strDBPath;
			CalcTimeOffset();
	}
	else {
		ar << m_wComType << m_szIP << m_wPort << m_szComPort << m_dwBaudRate << 
			m_cByteSize << m_cParity << m_cStopBits << m_nReadTimeout << 
			m_nWriteTimeout << m_nUpdateSec << m_bDebug;

		// 2010-07-19��������
		ar << m_bLocalTime << m_nTimeBias;

		ar << m_strSectionType << m_strEncryp;//ar << m_szTcpUdpParam << m_szComParam;

		ar << m_szDataSource << m_szPsw << m_szID;

		ar << m_strDBPath;
	}
	m_bModified = FALSE;
}	
	
CConfigInfo& CConfigInfo::operator=(const CConfigInfo& config)
{
	if (&config != this)
	{		
		m_bModified		= config.m_bModified;
		m_wComType		= config.m_wComType;	
		m_szIP			= config.m_szIP;
		m_wPort			= config.m_wPort;
		m_szTcpUdpParam	= config.m_szTcpUdpParam;
		m_szComPort		= config.m_szComPort;
		m_dwBaudRate	= config.m_dwBaudRate;
		m_cByteSize		= config.m_cByteSize;
		m_cParity		= config.m_cParity;
		m_cStopBits		= config.m_cStopBits;
		m_szComParam	= config.m_szComParam;
		m_nReadTimeout	= config.m_nReadTimeout;
		m_nWriteTimeout = config.m_nWriteTimeout;
		m_nUpdateSec	= config.m_nUpdateSec;
		m_bDebug		= config.m_bDebug;
		m_bLocalTime	= config.m_bLocalTime;
		m_nTimeBias		= config.m_nTimeBias;

		m_szDataSource	= config.m_szDataSource;
		m_szPsw			= config.m_szPsw;
		m_szID			= config.m_szID;

		m_szFileName	= config.m_szFileName;
		m_bAutoDeleteFile = config.m_bAutoDeleteFile;
		m_szFileParam	= config.m_szFileParam;

		CalcTimeOffset();
	}

	Save();

	return *this;
}

BOOL CConfigInfo::operator==( const CConfigInfo& config)
{
	return  (m_wComType			== config.m_wComType)		&&
			(m_szIP				== config.m_szIP)			&&
			(m_wPort			== config.m_wPort)			&&
			(m_szTcpUdpParam	== config.m_szTcpUdpParam)	&&
			(m_szComPort		== config.m_szComPort)		&&
			(m_dwBaudRate		== config.m_dwBaudRate)		&&
			(m_cByteSize		== config.m_cByteSize)		&&
			(m_cParity			== config.m_cParity)		&&
			(m_cStopBits		== config.m_cStopBits)		&&
			(m_szComParam		== config.m_szComParam)		&&
			(m_nReadTimeout		== config.m_nReadTimeout)	&&
			(m_nWriteTimeout	== config.m_nWriteTimeout)	&&
			(m_nUpdateSec		== config.m_nUpdateSec)		&&
			(m_bDebug			== config.m_bDebug)			&&
			(m_bLocalTime		== config.m_bLocalTime)		&&
			(m_nTimeBias		== config.m_nTimeBias)		&&

			(m_szFileName		== config.m_szFileName)		&&
			(m_bAutoDeleteFile		== config.m_bAutoDeleteFile)&&
			(m_szFileParam		== config.m_szFileParam)	&&

			(m_szDataSource     == config.m_szDataSource)   &&
			(m_szPsw			== config.m_szPsw)          &&
			(m_szID				== config.m_szID)			;
}

BOOL CConfigInfo::operator!=( const CConfigInfo& config)
{
	return  (m_wComType		!= config.m_wComType)		||
		(m_szIP				!= config.m_szIP)			||
		(m_wPort			!= config.m_wPort)			||
		(m_szTcpUdpParam	!= config.m_szTcpUdpParam)	||
		(m_szComPort		!= config.m_szComPort)		||
		(m_dwBaudRate		!= config.m_dwBaudRate)		||
		(m_cByteSize		!= config.m_cByteSize)		||
		(m_cParity			!= config.m_cParity)		||
		(m_cStopBits		!= config.m_cStopBits)		||
		(m_szComParam		!= config.m_szComParam)		||
		(m_nReadTimeout		!= config.m_nReadTimeout)	||
		(m_nWriteTimeout	!= config.m_nWriteTimeout)	||
		(m_nUpdateSec		!= config.m_nUpdateSec)		||
		(m_bDebug			!= config.m_bDebug)			||
		(m_bLocalTime		!= config.m_bLocalTime)		||
		(m_nTimeBias		!= config.m_nTimeBias)		||

		(m_szFileName		!= config.m_szFileName)		||
		(m_bAutoDeleteFile		!= config.m_bAutoDeleteFile)||
		(m_szFileParam		!= config.m_szFileParam)	||

		(m_szDataSource     != config.m_szDataSource)   ||
		(m_szPsw			!= config.m_szPsw)          ||
		(m_szID				!= config.m_szID)			;
}

CString CConfigInfo::GetConnectString()
{
	CString szt;
	switch(m_wComType)
	{
	case COM_TYPE_COM:		
		szt.Format(_T("ͨѶЭ�飺COM���˿ڣ�%s�������ʣ�%ld������λ��%d����żУ�飺%d��ֹͣλ��%d���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_szComPort, m_dwBaudRate, m_cByteSize, m_cParity, m_cStopBits, m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_UDP:	
		szt.Format(_T("ͨѶЭ�飺UDP��IP��ַ��%s���˿ڣ�%d���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_szIP, m_wPort, m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_UDPSERV:
		szt.Format(_T("ͨѶЭ�飺UDP Server���˿ڣ�%d���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_wPort, m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_TCP:
		szt.Format(_T("ͨѶЭ�飺TCP Client��IP��ַ��%s���˿ڣ�%d���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_szIP, m_wPort, m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_TCPSERV:
		szt.Format(_T("ͨѶЭ�飺TCP Server���˿ڣ�%d���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_wPort, m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_DB:
		szt.Format(_T("ODBC����Դ��%s���û�����%s�����룺%s���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_szDataSource,m_szID,m_szPsw,
			m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	case COM_TYPE_FILE:
		szt.Format(_T("�ļ�����%s���Զ�ɾ����%s���������ڣ�%d ms������ʱ�꣺%s��ʱ��ƫ�ƣ�%d"), 
			m_szFileName, (m_bAutoDeleteFile)?_T("yes"):_T("no"),  m_nUpdateSec, (m_bLocalTime)?_T("yes"):_T("no"), m_nTimeBias);
		break;
	default:
		szt = _T("Unknown");
	}

	return szt;
}

CString  CConfigInfo::GetModPath()
{
	TCHAR szFilePath[MAX_PATH + 1]={0};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);

	CString strTemp,strTemp2;
	strTemp.Format("%s",szFilePath);
	int iPos = strTemp.ReverseFind(_T('\\'));
	strTemp = strTemp.Left(iPos);

	strTemp2.Format(_T("%s\\setpara.cfg"),strTemp);
	return strTemp2;
}

BOOL CConfigInfo::Save()
{
	CString strFilePath  =  GetModPath();

	CFile fl;
	if (fl.Open(strFilePath, CFile::modeCreate | CFile::modeWrite))
	{
		CArchive ar(&fl, CArchive::store);
		Serialize(ar,0);
		ar.Close();
	}

	return TRUE;
}

BOOL CConfigInfo::Read()
{
	CString strFilePath  =  GetModPath();

	CFile fl;
	if (fl.Open(strFilePath, CFile::modeRead))
	{
		CArchive ar(&fl, CArchive::load);

		Serialize(ar,0);
		ar.Close();
	}
	return TRUE;
}