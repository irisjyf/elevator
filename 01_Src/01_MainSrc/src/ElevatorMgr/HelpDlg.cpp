// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// CHelpDlg �Ի���

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


// CHelpDlg ��Ϣ�������


BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CHelpDlg::LoadHelpInfo(CString &szResID)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState()); //��Դ�л�
	szResID.Delete(0, 6); // ɾ��_T("res://")
	DWORD dwResID = (DWORD)atol(szResID);

	HINSTANCE hi = AfxGetResourceHandle( );
	HRSRC hRsrc = FindResource(hi, MAKEINTRESOURCE(dwResID), TEXT("TEXT"));

	if (NULL == hRsrc)
		return;

	//��ȡ��Դ�Ĵ�С
	int nsize = (int)SizeofResource(hi, hRsrc); 
	if (0 == nsize)		
		return;

	//������Դ
	HGLOBAL hGlobal = LoadResource(hi, hRsrc); 
	if (NULL == hGlobal)
		return;

	//������Դ
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
