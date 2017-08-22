// QurryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "QurryDlg.h"
#include "afxdialogex.h"


// CQurryDlg �Ի���

IMPLEMENT_DYNAMIC(CQurryDlg, CDialogEx)

CQurryDlg::CQurryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQurryDlg::IDD, pParent)
	, m_strQurryBox(_T(""))
	, m_strQurryKey(_T(""))
{

}

CQurryDlg::~CQurryDlg()
{
}

void CQurryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_QURRY_FILED, m_cQurryBox);
	DDX_CBString(pDX, IDC_COMBO_QURRY_FILED, m_strQurryBox);
	DDX_Text(pDX, IDC_EDIT_QURRY_KEY, m_strQurryKey);
}


BEGIN_MESSAGE_MAP(CQurryDlg, CDialogEx)
END_MESSAGE_MAP()


// CQurryDlg ��Ϣ�������


BOOL CQurryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	for (int i= 0;i < m_arrFiled.GetCount();i++)
	{
		m_cQurryBox.AddString(m_arrFiled.GetAt(i));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
