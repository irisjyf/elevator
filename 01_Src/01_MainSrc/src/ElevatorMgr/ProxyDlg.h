#pragma once
#include "afxcmn.h"


// CProxyDlg �Ի���

class CProxyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProxyDlg)

public:
	CProxyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProxyDlg();
	CListCtrl m_cList;
	POINT	  m_old;

	void		ReSize();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	BOOL          ShowTable();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedProxyAdd();
	afx_msg void OnBnClickedProxyMod();
	afx_msg void OnBnClickedProxyDel();
	afx_msg void OnNMDblclkAuthList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
