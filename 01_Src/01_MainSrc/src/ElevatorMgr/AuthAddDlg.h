#pragma once


// CAuthAddDlg 对话框

class CAuthAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthAddDlg)

public:
	CAuthAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuthAddDlg();
	CString m_strUser;
	CString m_strPsw;
	CString m_strPsw2;
	CString m_strAuth;

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
