// HelpDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg 对话框

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
{

}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
END_MESSAGE_MAP()


// CHelpDlg 消息处理程序


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString szHelpInfo;
	szHelpInfo.Format(_T("res://%d"), IDR_TEXT1);

	LoadHelpInfo(szHelpInfo);

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_HELP);
	if (pEdit)
	{
		pEdit->SetWindowText(szHelpInfo);
		pEdit->SetReadOnly(TRUE);
		pEdit->SetSel(0, 0);
		pEdit->SetFocus();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CHelpDlg::LoadHelpInfo(CString &szResID)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState()); //资源切换
	szResID.Delete(0, 6); // 删除_T("res://")
	DWORD dwResID = (DWORD)atol(szResID);

	HINSTANCE hi = AfxGetResourceHandle( );
	HRSRC hRsrc = FindResource(hi, MAKEINTRESOURCE(dwResID), TEXT("TEXT"));

	if (NULL == hRsrc)
		return;

	//获取资源的大小
	int nsize = (int)SizeofResource(hi, hRsrc); 
	if (0 == nsize)		
		return;

	//加载资源
	HGLOBAL hGlobal = LoadResource(hi, hRsrc); 
	if (NULL == hGlobal)
		return;

	//锁定资源
	LPVOID pBuffer = LockResource(hGlobal); 
	if (NULL == pBuffer)
	{
		FreeResource(hGlobal);
		return;
	}

	char *szText = new char[nsize + 1];
	memcpy(szText, pBuffer, nsize);
	szText[nsize] = '\0';

	szResID = szText;

	delete[] szText;

	FreeResource(hGlobal);
}
