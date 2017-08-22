// ElevatorMgr.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ElevatorMgrDlg.h"

#include "LoginDlg.h"
#include "Comm\DBManage.h"

#include <string>
#include <ostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CElevatorMgrApp

BEGIN_MESSAGE_MAP(CElevatorMgrApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CElevatorMgrApp 构造

CElevatorMgrApp::CElevatorMgrApp()
	:syslogAppender(NULL)
	,appender(NULL)
	,m_pCategory(NULL)
	,m_dwAgentID(0)
	,m_szAgentDes("")
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 
	//memset(m_cData,0,BUFFER_SIZE);
}


// 唯一的一个 CElevatorMgrApp 对象

CElevatorMgrApp theApp;
char CElevatorMgrApp::m_cData[BUFFER_SIZE] = {0};

// CElevatorMgrApp 初始化

BOOL CElevatorMgrApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));


	if(!syslogAppender)
	{
		log4cpp::PatternLayout* pLayout1 = new log4cpp::PatternLayout();
		pLayout1->setConversionPattern("%d: %p %c%x: %m%n");

		log4cpp::Appender* fileAppender = new log4cpp::FileAppender("fileAppender","Elevator.log");
		fileAppender->setLayout(pLayout1);

		m_pCategory = &log4cpp::Category::getRoot().getInstance("RootName");
		m_pCategory->addAppender(fileAppender);
		m_pCategory->setPriority(log4cpp::Priority::DEBUG);


	}

	m_pCategory->info("初始化执行程序!");
	//m_pCategory->warn("Hello log4cpp in aWarning Message!");

	TCHAR szFilePath[MAX_PATH + 1]={0};
	GetModuleFileName(NULL, szFilePath, MAX_PATH);

	CString strTemp,strTemp2;
	strTemp.Format("%s",szFilePath);
	int iPos = strTemp.ReverseFind(_T('\\'));
	strTemp = strTemp.Left(iPos);

	strTemp2.Format(_T("%s\\MAC.ssk"),strTemp);

	//BOOL  bSuccess = skinppLoadSkin(_T("MAC.ssk"));
	BOOL  bSuccess = skinppLoadSkin(strTemp2.GetBuffer());

	//登录界面
	CLoginDlg loginDlg ;


	m_pCategory->info("开始登录!");

 	if (IDOK!=loginDlg.DoModal())
 		return FALSE;

	CElevatorMgrDlg dlg;
	CString strLog;

	strLog.Format("登录用户名%s", loginDlg.m_strUser);
	m_pCategory->info(strLog);
	// 数据连接
	LPDBManage->OpenDB();
	if (!LPDBManage->Login(loginDlg.m_strUser,loginDlg.m_strPsw))
	{
		strLog.Format("登录失败，用户名%s", loginDlg.m_strUser);
		m_pCategory->info(strLog);
	    return FALSE;
	}

	m_pCategory->info("登录成功!");

	LPDBManage->ReadAgentID(m_dwAgentID,m_szAgentDes);

	m_pSerialProtocol = CSerialProtocol::GetSerialProtocol();
	m_pSerialProtocol->InitComm();

	m_pRadioCardProtocol = new CRadioCardProtocal(m_pSerialProtocol);


	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


int CElevatorMgrApp::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if(m_pRadioCardProtocol)
	{
		delete m_pRadioCardProtocol;
		m_pRadioCardProtocol = NULL;
	}

	if(m_pSerialProtocol)
	{
		m_pSerialProtocol->Disconnect();
		delete m_pSerialProtocol;
		m_pSerialProtocol = NULL;
	}


	log4cpp::Category::shutdown();

	return CWinApp::ExitInstance();
}

BOOL CElevatorMgrApp::IsAgented()
{
	if(m_dwAgentID > 0)
		return TRUE;
	return FALSE;
}

void CElevatorMgrApp::SetAgentID(DWORD idata)
{
	m_dwAgentID = idata;
}

void CElevatorMgrApp::log(CString szLog)
{
	m_pCategory->warn(szLog.GetBuffer(szLog.GetLength()));
	szLog.ReleaseBuffer();
}
void CElevatorMgrApp::Warning(CString szLog)
{
	m_pCategory->warn(szLog.GetBuffer(szLog.GetLength()));
	szLog.ReleaseBuffer();
}
void CElevatorMgrApp::Debugging(CString szLog)
{
	m_pCategory->debug(szLog.GetBuffer(szLog.GetLength()));
	szLog.ReleaseBuffer();
}
void CElevatorMgrApp::Erroring(CString szLog)
{
	m_pCategory->error(szLog.GetBuffer(szLog.GetLength()));
	szLog.ReleaseBuffer();
}
void CElevatorMgrApp::Infor(CString szLog)
{
	m_pCategory->info(szLog.GetBuffer(szLog.GetLength()));
	szLog.ReleaseBuffer();
}
void log_info(CString szLog)
{
	theApp.Infor(szLog);
}
void log_Debug(CString szLog)
{
	theApp.Debugging(szLog);
}
void log_Warning(CString szLog)
{
	theApp.Warning(szLog);
}
void log_Error(CString szLog)
{
	theApp.Erroring(szLog);
}
