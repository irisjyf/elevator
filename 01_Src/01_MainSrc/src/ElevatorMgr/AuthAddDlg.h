#pragma once


// CAuthAddDlg �Ի���

class CAuthAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAuthAddDlg)

public:
	CAuthAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAuthAddDlg();
	CString m_strUser;
	CString m_strPsw;
	CString m_strPsw2;
	CString m_strAuth;

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
