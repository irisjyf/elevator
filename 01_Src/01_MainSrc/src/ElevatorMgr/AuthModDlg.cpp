// AuthModDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "AuthModDlg.h"
#include "afxdialogex.h"


// CAuthModDlg 对话框

IMPLEMENT_DYNAMIC(CAuthModDlg, CDialogEx)

CAuthModDlg::CAuthModDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthModDlg::IDD, pParent)
	, m_strUser(_T(""))
	, m_strPsw(_T(""))
	, m_strPsw2(_T(""))
	, m_strOldPsw(_T(""))
	, m_strAuth(_T(""))
{

}

CAuthModDlg::~CAuthModDlg()
{
}

void CAuthModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT13, m_strUser);
	DDX_Text(pDX, IDC_EDIT2, m_strOldPsw);
	DDX_Text(pDX, IDC_EDIT14, m_strPsw);
	DDX_Text(pDX, IDC_EDIT12, m_strPsw2);
	DDX_CBString(pDX, IDC_COMBO_USRNAME2, m_strAuth);
}


BEGIN_MESSAGE_MAP(CAuthModDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAuthModDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAuthModDlg 消息处理程序


void CAuthModDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	BOOL bResult = TRUE;
	if(m_strRealPsw != m_strOldPsw)
	{
		AfxMessageBox("旧密码和原始密码不匹配，请重新输入!");
		return;
	}
	if(m_strPsw.GetLength() < 6)
	{
		AfxMessageBox("密码长度小于6，请重新输入!");
		return;
	}
	if(m_strPsw2 != m_strPsw)
	{
		AfxMessageBox("新密码和确认密码不相同，请重新输入!");
		return;
	}
	CDialogEx::OnOK();
}
