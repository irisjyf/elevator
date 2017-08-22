#pragma once
#include "afxwin.h"


// CDelOkDlg 对话框

class CDelOkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelOkDlg)

public:
	CDelOkDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDelOkDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DELOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPsw;
};
