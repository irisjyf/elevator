#pragma once
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxsock.h>		// MFC socket extensions
#include <afxmt.h>
#include <afxtempl.h> //ģ��֧��

// ͨѶЭ�鶨��
#define COM_TYPE_COM		0x01	// ���п�
#define COM_TYPE_UDP		0x02	// UDP ClientЭ��
#define COM_TYPE_UDPSERV	0x04	// UDP ServerЭ��
#define COM_TYPE_TCP		0x08	// TCP ClientЭ��
#define COM_TYPE_TCPSERV	0x10	// TCP ServerЭ��
#define COM_TYPE_DB		    0x20	// ODBC DB
#define COM_TYPE_FILE		0x40	// �ļ�����
///////////////////////////////////////////////////////////////////

#define BUF_LENGTH_SERIAL	4096
#define BUF_LENGTH_TCP		8192
#define BUF_LENGTH_UDP		65536

#define UPDATEVALTAGS		2000	// ÿ�������±�ǩ��

// ����ϵͳ�����룬��ø�ʽ���Ĵ�����Ϣ��dwErrorCodeһ����GetLastError()�������
CString GetSystemErrorMessage(DWORD dwErrorCode);


class CConfigInfo
{
public:
	CConfigInfo();
	virtual ~CConfigInfo();
	void Serialize(CArchive& ar, DWORD dwVersion);
	CString  GetModPath();
	BOOL Save();
	BOOL Read();
public:	
	BOOL IsModified() { return m_bModified; }

	CConfigInfo& operator=(const CConfigInfo& config);
	BOOL operator==( const CConfigInfo& config);
	BOOL operator!=( const CConfigInfo& config);
	CString GetConnectString();

	void CalcTimeOffset() {
		m_nTimeOffset = m_nTimeBias * 3600;
	}
public:
	static CString m_szHelpFile;	   // �������ð����ļ����ƣ�����·���������ļ���������̬�����һ�����Ϊ res://1234 ��ʽ����ʾ����Դ�м�����ԴIDΪ1234��TEXT��Դ��ʾ���û�
	static CString m_szParamDisplayName; // ���Ӳ�����ʾ��
	static CString m_szParamHintText;	// ���Ӳ�������ʾ�ı�

	static BOOL	m_bSelectFileName;		// �����ļ�·�������ļ�������
	static CString m_szSelectFileFilter;		// ���ļ�������
	static CString m_szSelectFileHint;	// ��Ŀ¼��ʾ�ı�

	BOOL		m_bModified;
	
	WORD		m_wComType;			// ͨѶЭ������

	// TCP/UDPͨѶ����
	CString		m_szIP;				// TCP/UDP������IP��ַ�������COM_TYPE_TCPSERV��ʽ��������
	WORD	    m_wPort;			// TCP/UDP����˿�
	CString		m_szTcpUdpParam;	// TCP/UDP���Ӳ��������������ͨѶЭ�飬һ�㲻��
	
	// ���п�ͨѶ����
	CString		m_szComPort;		// �˿�������"\\\\.\\com1","\\\\.\\com2"
	DWORD		m_dwBaudRate;		// ������,CBR_1200,CBR_2400,CBR_4800,CBR_9600,
									// CBR_14400,CBR_19200,CBR_38400,CBR_57600,CBR_115200,
									// CBR_14400,CBR_19200,CBR_38400,CBR_57600,CBR_115200,
	BYTE		m_cByteSize;		// ����λ number of bits/byte, 4-8
	BYTE		m_cParity;			// 0-4��Ӧno,odd,even,mark,space 
	BYTE		m_cStopBits;		// 0,1,2 ��Ӧ 1, 1.5, 2
	CString		m_szComParam;		// ���п����Ӳ��������������ͨѶЭ�飬һ�㲻��

	// ���ܷ�ʽ������
	CString    m_strSectionType;
	CString    m_strEncryp;
	CString    m_strDBPath;
   
	//odbc����
	CString		m_szID;
	CString		m_szPsw;
	CString		m_szDataSource;

	// File��ʽ����
	CString		m_szFileName;		// �ļ���
	BOOL		m_bAutoDeleteFile;	// �Ƿ��ڶ�ȡ���ݺ��Զ�ɾ���ļ�����
	CString		m_szFileParam;		// ����չ�ļ�����

	// �������ò���
	int			m_nReadTimeout;		//����ʱ
	int			m_nWriteTimeout;	//����ʱ
	int			m_nUpdateSec;       //�ɼ����ڣ�����
	int			m_nTimeBias;		//ʱ��ƫ����
	BOOL		m_bDebug;           //������Ϣ��¼
	BOOL		m_bLocalTime;		//�Ƿ�ʹ�ñ���ʱ�꣬�������Э���в�����ʱ�꣬����Ը�����



protected:	
	long		m_nTimeOffset;
};

