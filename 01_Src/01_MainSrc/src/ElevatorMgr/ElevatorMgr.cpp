// ElevatorMgr.cpp : ����Ӧ�ó��������Ϊ��
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


// CElevatorMgrApp ����

CElevatorMgrApp::CElevatorMgrApp()
	:syslogAppender(NULL)
	,appender(NULL)
	,m_pCategory(NULL)
	,m_dwAgentID(0)
	,m_szAgentDes("")
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance 
	//memset(m_cData,0,BUFFER_SIZE);
}


// Ψһ��һ�� CElevatorMgrApp ����

CElevatorMgrApp theApp;
char CElevatorMgrApp::m_cData[BUFFER_SIZE] = {0};

// CElevatorMgrApp ��ʼ��

BOOL CElevatorMgrApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


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

	m_pCategory->info("��ʼ��ִ�г���!");
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

	//��¼����
	CLoginDlg loginDlg ;


	m_pCategory->info("��ʼ��¼!");

 	if (IDOK!=loginDlg.DoModal())
 		return FALSE;

	CElevatorMgrDlg dlg;
	CString strLog;

	strLog.Format("��¼�û���%s", loginDlg.m_strUser);
	m_pCategory->info(strLog);
	// ��������
	LPDBManage->OpenDB();
	if (!LPDBManage->Login(loginDlg.m_strUser,loginDlg.m_strPsw))
	{
		strLog.Format("��¼ʧ�ܣ��û���%s", loginDlg.m_strUser);
		m_pCategory->info(strLog);
	    return FALSE;
	}

	m_pCategory->info("��¼�ɹ�!");

	LPDBManage->ReadAgentID(m_dwAgentID,m_szAgentDes);

	m_pSerialProtocol = CSerialProtocol::GetSerialProtocol();
	m_pSerialProtocol->InitComm();

	m_pRadioCardProtocol = new CRadioCardProtocal(m_pSerialProtocol);


	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


int CElevatorMgrApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
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
