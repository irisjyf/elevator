#pragma once


// CDlgMakeCardInfo 对话框

class CDlgMakeCardInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMakeCardInfo)

public:
	CDlgMakeCardInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMakeCardInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG_MAKECARDINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMakeCardTime;
	int m_iNum;
	CString m_szUser;
	CString m_szNote;
};
