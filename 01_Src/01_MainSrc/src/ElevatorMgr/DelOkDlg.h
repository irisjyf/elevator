#pragma once
#include "afxwin.h"


// CDelOkDlg �Ի���

class CDelOkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDelOkDlg)

public:
	CDelOkDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDelOkDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELOK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strPsw;
};
