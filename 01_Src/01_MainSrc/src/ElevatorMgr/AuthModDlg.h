#pragma once


// CAuthModDlg �Ի���

class CAuthModDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthModDlg)

public:
	CAuthModDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuthModDlg();
	CString m_strUser;
	CString m_strPsw;
	CString m_strOldPsw;
	CString m_strPsw2;
	CString m_strAuth;
	CString m_strRealPsw;

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN_MOD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
};
