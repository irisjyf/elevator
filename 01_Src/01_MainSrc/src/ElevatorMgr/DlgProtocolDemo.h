#pragma once


// CDlgProtocolDemo �Ի���

class CDlgProtocolDemo : public CDialog
{
	DECLARE_DYNAMIC(CDlgProtocolDemo)

public:
	CDlgProtocolDemo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProtocolDemo();

// �Ի�������
	enum { IDD = IDD_DIALOG_PORTDemo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnReadcard();
	BYTE mss;
};
