#pragma once
#include "afxwin.h"


// CProxyCardDlg 对话框

class CProxyCardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProxyCardDlg)

public:
	CProxyCardDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProxyCardDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROXY_CARD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	void   SetPara(char cType, long lID);
	BOOL   SetPara2(BOOL bSave);
	void   SetOutPutInfo(CString strInfo);

	long m_ID;
	CString m_ckr;
	CString m_sjhm;
	CString m_SN;
	CString m_bz;
	CComboBox m_cCklc;
	CString m_cklx;

	char m_cType;
	virtual BOOL OnInitDialog();
	CString m_strOutput;
	afx_msg void OnBnClickedRepairCard();
};
