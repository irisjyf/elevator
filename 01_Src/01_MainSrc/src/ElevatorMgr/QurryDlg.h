#pragma once
#include "afxwin.h"


// CQurryDlg �Ի���

class CQurryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CQurryDlg)

public:
	CQurryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CQurryDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_QURRY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cQurryBox;
	CString m_strQurryBox;
	CString m_strQurryKey;
	CStringArray  m_arrFiled;
	virtual BOOL OnInitDialog();
};
