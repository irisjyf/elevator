#pragma once
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxsock.h>		// MFC socket extensions
#include <afxmt.h>
#include <afxtempl.h> //模版支持

// 通讯协议定义
#define COM_TYPE_COM		0x01	// 串行口
#define COM_TYPE_UDP		0x02	// UDP Client协议
#define COM_TYPE_UDPSERV	0x04	// UDP Server协议
#define COM_TYPE_TCP		0x08	// TCP Client协议
#define COM_TYPE_TCPSERV	0x10	// TCP Server协议
#define COM_TYPE_DB		    0x20	// ODBC DB
#define COM_TYPE_FILE		0x40	// 文件类型
///////////////////////////////////////////////////////////////////

#define BUF_LENGTH_SERIAL	4096
#define BUF_LENGTH_TCP		8192
#define BUF_LENGTH_UDP		65536

#define UPDATEVALTAGS		2000	// 每次最大更新标签数

// 根据系统错误码，获得格式化的错误信息，dwErrorCode一般由GetLastError()函数获得
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
	static CString m_szHelpFile;	   // 驱动配置帮助文件名称，不带路径名，该文件和驱动动态库放在一起，如果为 res://1234 格式，表示从资源中加载资源ID为1234的TEXT资源显示给用户
	static CString m_szParamDisplayName; // 连接参数显示名
	static CString m_szParamHintText;	// 连接参数的提示文本

	static BOOL	m_bSelectFileName;		// 配置文件路径还是文件名？？
	static CString m_szSelectFileFilter;		// 打开文件过滤器
	static CString m_szSelectFileHint;	// 打开目录提示文本

	BOOL		m_bModified;
	
	WORD		m_wComType;			// 通讯协议类型

	// TCP/UDP通讯参数
	CString		m_szIP;				// TCP/UDP服务器IP地址，如果是COM_TYPE_TCPSERV方式，则该项不用
	WORD	    m_wPort;			// TCP/UDP服务端口
	CString		m_szTcpUdpParam;	// TCP/UDP连接参数，除非特殊的通讯协议，一般不用
	
	// 串行口通讯参数
	CString		m_szComPort;		// 端口名，如"\\\\.\\com1","\\\\.\\com2"
	DWORD		m_dwBaudRate;		// 波特率,CBR_1200,CBR_2400,CBR_4800,CBR_9600,
									// CBR_14400,CBR_19200,CBR_38400,CBR_57600,CBR_115200,
									// CBR_14400,CBR_19200,CBR_38400,CBR_57600,CBR_115200,
	BYTE		m_cByteSize;		// 数据位 number of bits/byte, 4-8
	BYTE		m_cParity;			// 0-4对应no,odd,even,mark,space 
	BYTE		m_cStopBits;		// 0,1,2 对应 1, 1.5, 2
	CString		m_szComParam;		// 串行口连接参数，除非特殊的通讯协议，一般不用

	// 加密方式和扇区
	CString    m_strSectionType;
	CString    m_strEncryp;
	CString    m_strDBPath;
   
	//odbc参数
	CString		m_szID;
	CString		m_szPsw;
	CString		m_szDataSource;

	// File格式参数
	CString		m_szFileName;		// 文件名
	BOOL		m_bAutoDeleteFile;	// 是否在读取数据后自动删除文件？？
	CString		m_szFileParam;		// 可扩展文件参数

	// 驱动配置参数
	int			m_nReadTimeout;		//读超时
	int			m_nWriteTimeout;	//读超时
	int			m_nUpdateSec;       //采集周期，毫秒
	int			m_nTimeBias;		//时区偏移量
	BOOL		m_bDebug;           //调试信息记录
	BOOL		m_bLocalTime;		//是否使用本地时标，如果驱动协议中不包含时标，则忽略该配置



protected:	
	long		m_nTimeOffset;
};

