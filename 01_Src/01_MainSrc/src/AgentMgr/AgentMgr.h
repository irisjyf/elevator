
// AgentMgr.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAgentMgrApp:
// �йش����ʵ�֣������ AgentMgr.cpp
//

class CAgentMgrApp : public CWinApp
{
public:
	CAgentMgrApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAgentMgrApp theApp;