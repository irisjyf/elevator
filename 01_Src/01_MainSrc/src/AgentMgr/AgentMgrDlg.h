
// AgentMgrDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

typedef struct _t_agent{
	int iIndex;
	CString szName;
	CString szTel;
	DWORD	dwAuthority;
	CString szAgentCode;
}T_Agent;

typedef CArray<T_Agent*, T_Agent*> CArrayAgent;

// CAgentMgrDlg 对话框
class CAgentMgrDlg : public CDialogEx
{
// 构造
public:
	CAgentMgrDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AGENTMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void Save();
	void Load();

public:
	CListCtrl m_listAgentCtrl;
	CArrayAgent m_Agents;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedAdd();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
};
