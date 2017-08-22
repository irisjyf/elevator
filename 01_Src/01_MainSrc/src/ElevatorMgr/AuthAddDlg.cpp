// AuthAddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "AuthAddDlg.h"
#include "afxdialogex.h"


// CAuthAddDlg �Ի���

IMPLEMENT_DYNAMIC(CAuthAddDlg, CDialogEx)

CAuthAddDlg::CAuthAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAuthAddDlg::IDD, pParent)
	, m_strUser(_T(""))
	, m_strPsw(_T(""))
	, m_strPsw2(_T(""))
	, m_strAuth(_T(""))
{

}

CAuthAddDlg::~CAuthAddDlg()
{
}

void CAuthAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT13, m_strUser);
	DDX_Text(pDX, IDC_EDIT2, m_strPsw);
	DDX_Text(pDX, IDC_EDIT12, m_strPsw2);
	DDX_CBString(pDX, IDC_COMBO_USRNAME2, m_strAuth);
}


BEGIN_MESSAGE_MAP(CAuthAddDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CAuthAddDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CAuthAddDlg ��Ϣ�������


void CAuthAddDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
