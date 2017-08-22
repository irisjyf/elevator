// ElevatorMgr.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


#include "log4cpp/Portability.hh"
#include <iostream>
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
//#include "log4cpp/SyslogAppender.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/NDC.hh"
// CElevatorMgrApp:
// 有关此类的实现，请参阅 ElevatorMgr.cpp
//

class CElevatorMgrApp : public CWinApp
{
public:
	CElevatorMgrApp();

	void	log(CString szLog);
	void	Warning(CString szLog);
	void	Debugging(CString szLog);
	void	Erroring(CString szLog);
	void	Infor(CString szLog);
	BOOL	IsAgented();
	void	SetAgentID(DWORD idata);

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();


// 实现
	log4cpp::Appender* appender;

	log4cpp::Appender* syslogAppender;

	log4cpp::Category* m_pCategory;

	DECLARE_MESSAGE_MAP()
public:
	DWORD					m_dwAgentID;
	CString					m_szAgentDes;
	CDBManage				m_DBManage; 
	CRadioCardProtocal*		m_pRadioCardProtocol;
	CSerialProtocol *		m_pSerialProtocol;
	static  char			m_cData[BUFFER_SIZE];
};

extern CElevatorMgrApp theApp;

void log_info(CString szLog);
void log_Debug(CString szLog);
void log_Warning(CString szLog);
void log_Error(CString szLog);

extern void log_info(CString szLog);
extern void log_Debug(CString szLog);
extern void log_Warning(CString szLog);
extern void log_Error(CString szLog);