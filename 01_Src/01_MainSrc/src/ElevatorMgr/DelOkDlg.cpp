// DelOkDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "DelOkDlg.h"
#include "afxdialogex.h"


// CDelOkDlg �Ի���

IMPLEMENT_DYNAMIC(CDelOkDlg, CDialogEx)

CDelOkDlg::CDelOkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDelOkDlg::IDD, pParent)
	, m_strPsw(_T(""))
{

}

CDelOkDlg::~CDelOkDlg()
{
}

void CDelOkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEL_KEY, m_strPsw);
}


BEGIN_MESSAGE_MAP(CDelOkDlg, CDialogEx)
END_MESSAGE_MAP()


// CDelOkDlg ��Ϣ�������
