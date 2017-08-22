// DlgProtocolDemo.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "DlgProtocolDemo.h"
#include "afxdialogex.h"


// CDlgProtocolDemo 对话框

IMPLEMENT_DYNAMIC(CDlgProtocolDemo, CDialog)

CDlgProtocolDemo::CDlgProtocolDemo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProtocolDemo::IDD, pParent)
	, mss(0)
{

}

CDlgProtocolDemo::~CDlgProtocolDemo()
{
}

void CDlgProtocolDemo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProtocolDemo, CDialog)
	ON_BN_CLICKED(IDC_BTN_READCARD, &CDlgProtocolDemo::OnBnClickedBtnReadcard)
END_MESSAGE_MAP()


// CDlgProtocolDemo 消息处理程序


BOOL CDlgProtocolDemo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgProtocolDemo::OnBnClickedBtnReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
}
