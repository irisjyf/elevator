#pragma once


// CManagerProxyDlg 对话框

class CManagerProxyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerProxyDlg)

public:
	CManagerProxyDlg(CWnd* pParent = NULL);   // 标准构造函数
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
	// 加密 反写工能
	BOOL m_bRecode;
// 对话框数据
	enum { IDD = IDD_DIALOG_MANAGERPROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnWritecard();
	afx_msg void OnBnClickedBtnGetSerial();
	afx_msg void OnBnClickedBtnWritecarder();
};
