// DelOkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "DelOkDlg.h"
#include "afxdialogex.h"


// CDelOkDlg 对话框

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


// CDelOkDlg 消息处理程序
