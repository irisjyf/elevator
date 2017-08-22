#pragma once
#include "afxcmn.h"
#include "Comm/quset.h"

// CManagerDlg 对话框

class CManagerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerDlg)

public:
	CManagerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManagerDlg();
	CListCtrl m_ManagerList;
	CString m_strComboxQurry;
	CString m_strKeyQurry;
	POINT	  m_old;

// 对话框数据
	enum { IDD = IDD_DIALOG_MANAGER };

protected:
	BOOL	ShowTable(CArray<Cquset*,Cquset*> &arr);
	void	ReSize()  ;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedManagerAdd();
	afx_msg void OnBnClickedManagerMod();
	afx_msg void OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedManagerDel();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnManagerQurry();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnReadCard();
};
