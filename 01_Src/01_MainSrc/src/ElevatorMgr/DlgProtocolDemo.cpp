// DlgProtocolDemo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "DlgProtocolDemo.h"
#include "afxdialogex.h"


// CDlgProtocolDemo �Ի���

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


// CDlgProtocolDemo ��Ϣ�������


BOOL CDlgProtocolDemo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgProtocolDemo::OnBnClickedBtnReadcard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
