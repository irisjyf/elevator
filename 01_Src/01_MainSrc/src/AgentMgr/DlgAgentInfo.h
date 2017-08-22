#pragma once
#include "afxwin.h"


// CDlgAgentInfo �Ի���

class CDlgAgentInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAgentInfo)

public:
	CDlgAgentInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAgentInfo();

// �Ի�������
	enum { IDD = IDD_DLG_AGENTINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	long m_AgentID;
	CString m_AgentName;
	CString m_AgentTel;
	CString m_szCode;
	int m_iAuthority;
	CComboBox m_cmbAgentAuthority;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCmbAuthorty();
	afx_msg void OnBnClickedBtnGetagentcode();
};
