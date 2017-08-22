#pragma once
#include "afxcmn.h"
#include "Comm/Keyinfoset.h"

// CFuncDlg �Ի���

class CFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncDlg)

public:
	CFuncDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFuncDlg();
	CListCtrl	m_FuncList;
	POINT		m_old;
	CString		m_strKeyQurry;
	CString		m_strComboxQurry;

// �Ի�������
	enum { IDD = IDD_DIALOG_FUNC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	// DDX/DDV ֧��
	afx_msg void OnBnClickedFuncAdd();
	afx_msg void OnBnClickedFuncMod();
	afx_msg void OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedFuncReadcard();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedBtnFuncQurry();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	BOOL    ShowTable(CArray<CKeyinfoset*,CKeyinfoset*> &arr);
	void	ReSize();
};
