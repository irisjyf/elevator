#pragma once
#include "afxcmn.h"


// CMakeCardDlg 对话框

class CMakeCardDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMakeCardDlg)

public:
	CMakeCardDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMakeCardDlg();
	BOOL         ShowTable(CMap<CString,LPCTSTR,CMakeCardSet*,CMakeCardSet*> &mapMakeCardSet);
	long m_iMakeNum;
	CString m_strTime;
	CListCtrl m_cList;
	BOOL	m_bStartFlag;

// 对话框数据
	enum { IDD = IDD_DIALOG_MAKECARD };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnMakecardStart();
	afx_msg void OnBnClickedBtnMakecardEnd();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnMakecardModify();
	afx_msg void OnBnClickedBtnMakecardDell();
	afx_msg void OnBnClickedBtnEnableVerityflag();
	afx_msg void OnBnClickedBtnDisableVerityflag();
	afx_msg void OnBnClickedBtnMakecardClearpsw();
};
