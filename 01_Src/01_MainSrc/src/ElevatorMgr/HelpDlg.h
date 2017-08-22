#pragma once


// CHelpDlg 对话框

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHelpDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_HELP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void    LoadHelpInfo(CString &szResID);
};
