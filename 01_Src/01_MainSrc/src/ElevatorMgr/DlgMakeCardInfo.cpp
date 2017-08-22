// DlgMakeCardInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "DlgMakeCardInfo.h"
#include "afxdialogex.h"


// CDlgMakeCardInfo 对话框

IMPLEMENT_DYNAMIC(CDlgMakeCardInfo, CDialogEx)

CDlgMakeCardInfo::CDlgMakeCardInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMakeCardInfo::IDD, pParent)
	, m_strMakeCardTime(_T(""))
	, m_iNum(0)
	, m_szUser(_T(""))
	, m_szNote(_T(""))
{

}

CDlgMakeCardInfo::~CDlgMakeCardInfo()
{
}

void CDlgMakeCardInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strMakeCardTime);
	DDX_Text(pDX, IDC_EDIT2, m_iNum);
	DDX_Text(pDX, IDC_EDIT12, m_szUser);
	DDX_Text(pDX, IDC_EDIT14, m_szNote);
}


BEGIN_MESSAGE_MAP(CDlgMakeCardInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgMakeCardInfo 消息处理程序
