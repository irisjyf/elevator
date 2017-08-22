// AuthModDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "AuthModDlg.h"
#include "afxdialogex.h"


// CAuthModDlg �Ի���

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


// CAuthModDlg ��Ϣ�������


void CAuthModDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	BOOL bResult = TRUE;
	if(m_strRealPsw != m_strOldPsw)
	{
		AfxMessageBox("�������ԭʼ���벻ƥ�䣬����������!");
		return;
	}
	if(m_strPsw.GetLength() < 6)
	{
		AfxMessageBox("���볤��С��6������������!");
		return;
	}
	if(m_strPsw2 != m_strPsw)
	{
		AfxMessageBox("�������ȷ�����벻��ͬ������������!");
		return;
	}
	CDialogEx::OnOK();
}
