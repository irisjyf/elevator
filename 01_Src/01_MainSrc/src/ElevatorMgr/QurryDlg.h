#pragma once
#include "afxwin.h"


// CQurryDlg 对话框

class CQurryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQurryDlg)

public:
	CQurryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CQurryDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_QURRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cQurryBox;
	CString m_strQurryBox;
	CString m_strQurryKey;
	CStringArray  m_arrFiled;
	virtual BOOL OnInitDialog();
};
