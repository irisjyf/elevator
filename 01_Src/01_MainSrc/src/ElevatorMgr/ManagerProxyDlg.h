#pragma once


// CManagerProxyDlg �Ի���

class CManagerProxyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerProxyDlg)

public:
	CManagerProxyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CManagerProxyDlg();
	BOOL    SetPara2(BOOL bSave);
	void    SetPara(char cType, long lID)
	{
		m_ID    = lID;
		m_cType = cType;
	}

	char    m_cType;
	long    m_ID;
	CString m_dlsmc;
	CString m_sjhm;
	int     m_dlsbh;
	CString m_bzxx;
	CString m_sn;
	BOOL m_bAgentFlag;
	// ���� ��д����
	BOOL m_bRecode;
// �Ի�������
	enum { IDD = IDD_DIALOG_MANAGERPROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnWritecard();
	afx_msg void OnBnClickedBtnGetSerial();
	afx_msg void OnBnClickedBtnWritecarder();
};
