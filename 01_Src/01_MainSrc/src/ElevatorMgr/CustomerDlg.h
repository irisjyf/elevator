#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CCustomerDlg �Ի���

class CCustomerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomerDlg)

public:
	CCustomerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCustomerDlg();
	void   ReSize();
	BOOL   ShowTable(CArray<CYonghuset*,CYonghuset*> &arr);
	CString GetCardInfo(LPT_UserCardData pUserCardData, CYonghuset& customerData);
	
	CListCtrl m_CustomerList;
	CString   m_strKeyQurry;
	CString   m_strComboxQurry;
	CComboBox m_cComboxQurry;
	POINT	  m_old;

// �Ի�������
	enum { IDD = IDD_DIALOG_CUSTOMER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
