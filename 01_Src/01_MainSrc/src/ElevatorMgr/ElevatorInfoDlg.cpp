// ElevatorInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ElevatorInfoDlg.h"
#include "afxdialogex.h"
#include "FloorDlg.h"

// CElevatorInfoDlg 对话框

IMPLEMENT_DYNAMIC(CElevatorInfoDlg, CDialogEx)

CElevatorInfoDlg::CElevatorInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CElevatorInfoDlg::IDD, pParent)
	, m_dtlx(0)
	, m_iFlootCount(0)
	, m_iStartFloor(-2)
	, m_iCommonFloor(0)
{

}

CElevatorInfoDlg::~CElevatorInfoDlg()
{
}

void CElevatorInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dtbh);
	DDX_Text(pDX, IDC_EDIT2, m_dtmc);
	DDX_Radio(pDX, IDC_RADIO1, m_dtlx);
	DDX_Text(pDX, IDC_FLOOR_COUNT, m_iFlootCount);
	DDX_Text(pDX, IDC_START_FLOOR, m_iStartFloor);
	DDV_MinMaxInt(pDX, m_iStartFloor, -100, 500);
	DDX_Text(pDX, IDC_COMMON_FLOOR, m_iCommonFloor);
}


BEGIN_MESSAGE_MAP(CElevatorInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CElevatorInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CElevatorInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_FLOOR_CODE, &CElevatorInfoDlg::OnBnClickedFloorCode)
END_MESSAGE_MAP()


// CElevatorInfoDlg 消息处理程序


BOOL CElevatorInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_cType == ADD_TYPE)
		SetWindowText("增加电梯");
	else
		SetWindowText("修改电梯数据");

	// TODO:  在此添加额外的初始化
	CArray<CSuoset*,CSuoset*> arr;
	LPDBManage->GetElevatorList(arr);

	SetPara2(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void   CElevatorInfoDlg::SetPara(char cType, long lID)
{
	m_id    = lID;
	m_cType = cType;
}

BOOL  CElevatorInfoDlg::SetPara2(BOOL bSave)
{
	UpdateData(TRUE);
	
	CSuoset *pQuset = LPDBManage->GetElevatorByID(m_id);

	CString strTemp;
	if (bSave)
	{
		pQuset->m_dtmc    =   m_dtmc;
		pQuset->m_dtlx    =  m_dtlx;
		pQuset->m_dtbh    =  m_dtbh;
		pQuset->m_dtcs    =   m_iFlootCount;
		pQuset->m_qslc    =   m_iStartFloor;
		pQuset->m_gglc    =  m_iCommonFloor;
		//pQuset->m_dtcs    =   m_dtcs;
		//pQuset->m_qslc    =   m_qslc;
		//pQuset->m_gglc    =  m_gglc;

		pQuset->m_dtlcbs  = pQuset->ElvCodeMake();
	}
	else
	{
		m_dtmc    =  pQuset->m_dtmc;
		m_dtlx    =  pQuset->m_dtlx;
		m_dtbh    =  pQuset->m_dtbh;
		m_iFlootCount    =  pQuset->m_dtcs;;
		m_iStartFloor    =  pQuset->m_qslc;
		m_iCommonFloor    =  pQuset->m_gglc;
		//m_dtcs    =  pQuset->m_dtcs;;
		//m_qslc    =  pQuset->m_qslc;
		//m_gglc    =  pQuset->m_gglc;

		pQuset->ElvCodeParse();
	}

	UpdateData(FALSE);
	return TRUE;
}


void CElevatorInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_id != m_dtbh)
	{
		LPDBManage->RemoveElevatorofID(m_id);
		m_id = m_dtbh;
	}
	SetPara2(TRUE);

	CSuoset *pQuset = LPDBManage->GetElevatorByID(m_id);

	if (LPDBManage->OperElevator(pQuset,m_cType))
	{
		m_cType  =  MOD_TYPE;;
	}

	CDialogEx::OnOK();
}


void CElevatorInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CSuoset *pQuset = LPDBManage->GetElevatorByID(m_id);
	if (m_cType == ADD_TYPE )
	{
		LPDBManage->OperElevator(pQuset,DEL_TYPE);
	}

	CDialogEx::OnCancel();
}


void CElevatorInfoDlg::OnBnClickedFloorCode()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_dtmc.IsEmpty()|| m_iCommonFloor < 1)
	{
		MessageBox("请先设置所乘坐的电梯！");
		return ;
	}

	CFloorDlg dlg;
	dlg.SetPara(FLOOR_CODE,m_id);

	dlg.sumlc= m_iFlootCount;
	dlg.qslc = m_iStartFloor;
	dlg.gglc = m_iCommonFloor; 

	if(dlg.DoModal()==IDOK)
	{
		UpdateData(FALSE);
	}
}
