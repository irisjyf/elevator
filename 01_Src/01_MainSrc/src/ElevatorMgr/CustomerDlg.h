#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCustomerDlg 对话框

class CCustomerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCustomerDlg();
	void   ReSize();
	BOOL   ShowTable(CArray<CYonghuset*,CYonghuset*> &arr);
	CString GetCardInfo(LPT_UserCardData pUserCardData, CYonghuset& customerData);
	
	CListCtrl m_CustomerList;
	CString   m_strKeyQurry;
	CString   m_strComboxQurry;
	CComboBox m_cComboxQurry;
	POINT	  m_old;

// 对话框数据
	enum { IDD = IDD_DIALOG_CUSTOMER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCustomerAdd();
	afx_msg void OnBnClickedCusterQurry();
	afx_msg void OnBnClickedCustomerMod();
	afx_msg void OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedCustomerDel();
	afx_msg void OnBnClickedCustomerReadcard();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnReaduserinfo();
	
};
