#pragma once


// CAuthModDlg 对话框

class CAuthModDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthModDlg)

public:
	CAuthModDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAuthModDlg();
	CString m_strUser;
	CString m_strPsw;
	CString m_strOldPsw;
	CString m_strPsw2;
	CString m_strAuth;
	CString m_strRealPsw;

// 对话框数据
	enum { IDD = IDD_DIALOG_LOGIN_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};
