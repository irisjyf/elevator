
// AgentMgrDlg.h : ͷ�ļ�
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

// CAgentMgrDlg �Ի���
class CAgentMgrDlg : public CDialogEx
{
// ����
public:
	CAgentMgrDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AGENTMGR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void Save();
	void Load();

public:
	CListCtrl m_listAgentCtrl;
	CArrayAgent m_Agents;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedAdd();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
	virtual void OnCancel();
};
