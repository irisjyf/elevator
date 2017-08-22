#pragma once
#include "afxcmn.h"
#include "Comm/Suoset.h"

// CElevatorDlg �Ի���

class CElevatorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CElevatorDlg)

public:
	CElevatorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CElevatorDlg();
	void	OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult);
	void	ReSize();
	BOOL	ShowTable(CArray<CSuoset*,CSuoset*> &arr);
	void	ModifyElevatorInfo(int iIndex);
	void	UpdataTable();
// �Ի�������
	enum { IDD = IDD_DIALOG_ELEVATOR };

	CListCtrl m_ElevatorList;
	POINT	  m_old;
	CString m_strComboxQurry;
	CString m_strKeyQurry;
	CArray<CSuoset*,CSuoset*> m_arrElevator;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedElevatorAdd();
	afx_msg void OnBnClickedElevatorMod();
	afx_msg void OnBnClickedDel();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnNMClickFliedList2(NMHDR *pNMHDR, LRESULT *pResult);
};
