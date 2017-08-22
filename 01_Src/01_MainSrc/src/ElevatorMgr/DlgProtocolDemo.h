#pragma once


// CDlgProtocolDemo 对话框

class CDlgProtocolDemo : public CDialog
{
	DECLARE_DYNAMIC(CDlgProtocolDemo)

public:
	CDlgProtocolDemo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgProtocolDemo();

// 对话框数据
	enum { IDD = IDD_DIALOG_PORTDemo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnReadcard();
	BYTE mss;
};
