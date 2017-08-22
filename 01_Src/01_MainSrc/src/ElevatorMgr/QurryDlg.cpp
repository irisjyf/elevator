// QurryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "QurryDlg.h"
#include "afxdialogex.h"


// CQurryDlg 对话框

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


// CQurryDlg 消息处理程序


BOOL CQurryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	for (int i= 0;i < m_arrFiled.GetCount();i++)
	{
		m_cQurryBox.AddString(m_arrFiled.GetAt(i));
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
