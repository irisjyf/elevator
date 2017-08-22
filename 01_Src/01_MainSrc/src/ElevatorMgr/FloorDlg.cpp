// FloorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "FloorDlg.h"
#include "afxdialogex.h"
#include "FloorCodeDlg.h"

int checkid[64]={
	IDC_CHECK1, IDC_CHECK2, IDC_CHECK3, IDC_CHECK4, IDC_CHECK5, IDC_CHECK6, IDC_CHECK7, IDC_CHECK8,
	IDC_CHECK9, IDC_CHECK10,IDC_CHECK11,IDC_CHECK12,IDC_CHECK13,IDC_CHECK14,IDC_CHECK15,IDC_CHECK16,
	IDC_CHECK17,IDC_CHECK18,IDC_CHECK19,IDC_CHECK20,IDC_CHECK21,IDC_CHECK22,IDC_CHECK23,IDC_CHECK24,
	IDC_CHECK25,IDC_CHECK26,IDC_CHECK27,IDC_CHECK28,IDC_CHECK29,IDC_CHECK30,IDC_CHECK31,IDC_CHECK32,
	IDC_CHECK33,IDC_CHECK34,IDC_CHECK35,IDC_CHECK36,IDC_CHECK37,IDC_CHECK38,IDC_CHECK39,IDC_CHECK40,
	IDC_CHECK41,IDC_CHECK42,IDC_CHECK43,IDC_CHECK44,IDC_CHECK45,IDC_CHECK46,IDC_CHECK47,IDC_CHECK48,
	IDC_CHECK49,IDC_CHECK50,IDC_CHECK51,IDC_CHECK52,IDC_CHECK53,IDC_CHECK54,IDC_CHECK55,IDC_CHECK56,
	IDC_CHECK57,IDC_CHECK58,IDC_CHECK59,IDC_CHECK60,IDC_CHECK61,IDC_CHECK62,IDC_CHECK63,IDC_CHECK64				 
};
// CFloorDlg 对话框

IMPLEMENT_DYNAMIC(CFloorDlg, CDialogEx)

CFloorDlg::CFloorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFloorDlg::IDD, pParent)
{
	sumlc=0;
	kylc=_T("");
	dtkycxz=_T("");
	qslc=0;
	gglc=0;
}

CFloorDlg::~CFloorDlg()
{
}

void CFloorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFloorDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFloorDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK65, &CFloorDlg::OnBnClickedCheck65)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK1, IDC_CHECK64, OnButtonClicked)        
END_MESSAGE_MAP()


// CFloorDlg 消息处理程序

#define  ELV_MAX_NUM  64

BOOL CFloorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CButton *pWnd;
	CString str=kylc,str2,str3;

	int a[ELV_MAX_NUM] = {0};
	int iTemp = 0 ,pos = 0;

	for(int i=0;i<ELV_MAX_NUM;i++)
	{
		if (str.IsEmpty()) break;


		pos=str.Find(',');
		if(pos==-1)
		{
			a[atoi(str)-1]=1;
			break;
		}
		a[atoi(str.Left(pos))-1]=1;
		str=str.Mid(pos+1,str.GetLength());
	}

	CSuoset *pQuset = LPDBManage->GetElevatorByID(m_id);

	if(sumlc>ELV_MAX_NUM)  
		sumlc=ELV_MAX_NUM;

	for(int i=0;i<sumlc;i++)
	{
		pWnd =(CButton *) GetDlgItem( checkid[i]);     //获取控件指针，IDC_EDIT为控件ID号
		pWnd->ShowWindow( SW_SHOW );     //隐藏控件

		if(qslc<0&&qslc+i>=0)
			str2.Format("%d",qslc+i+1);
		else
		{
			str2.Format("%d",qslc+i);
		}

		pWnd->SetWindowText(str2);

		CString strShow;
		if (pQuset->m_mapElvCode.Lookup(str2,strShow))
		{
			if (!strShow.IsEmpty())
			{
				pWnd->SetWindowText(strShow);
			}
		}

		pWnd->SetCheck(a[i]);
	}	

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CFloorDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CButton *pWnd;
	CString str="",str1="";

	kylc="";
	for(int i=0;i<sumlc;i++)
	{
		pWnd=(CButton *) GetDlgItem( checkid[i]);
		if(pWnd->GetCheck()==TRUE)
		{
			str1.Format("%d",i+1);
			dtkycxz=dtkycxz+str1+",";
			pWnd->GetWindowText(str);
			kylc+=str+",";
		}
		else
		{
			;//dtkycxznum[i]=0;
		}
	}
	//dtkycxz=dtkycxz.Left(kylc.GetLength()-1);
	dtkycxz=dtkycxz.Left(dtkycxz.GetLength()-1);
	kylc=kylc.Left(kylc.GetLength()-1);
	CDialogEx::OnOK();
}


void CFloorDlg::OnBnClickedCheck65()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton *pWnd;
	if(((CButton *)GetDlgItem( IDC_CHECK65))->GetCheck()==TRUE)
	{
		for(int i=0;i<sumlc;i++)
		{
			pWnd =(CButton *) GetDlgItem( checkid[i]);     //获取控件指针，IDC_EDIT为控件ID号
			pWnd->SetCheck(true);
		}
	}
	else
	{
		for(int i=0;i<sumlc;i++)
		{
			pWnd =(CButton *) GetDlgItem( checkid[i]);     //获取控件指针，IDC_EDIT为控件ID号
			pWnd->SetCheck(false);
		}
	}
}

void   CFloorDlg::OnButtonClicked(UINT  uId)
{
	if (m_cType != FLOOR_CODE)
		return;

	CSuoset *pQuset = LPDBManage->GetElevatorByID(m_id);

	CString strFloor;
	CButton *pWnd =(CButton *)GetDlgItem( uId);
	pWnd->GetWindowTextA(strFloor);
	CFloorCodeDlg dlg;
	dlg.m_strFloor      = strFloor;
	dlg.m_strFloorCode	= strFloor;

	pQuset->m_mapElvCode.Lookup(strFloor,dlg.m_strFloorCode);
	
	if (IDOK == dlg.DoModal())
	{  
		if(!dlg.m_strFloorCode.IsEmpty())
		{
			pQuset->ElvCodeAdd(dlg.m_strFloor,dlg.m_strFloorCode);
			pWnd->SetWindowTextA(dlg.m_strFloorCode);
		}
	}

	UpdateData(TRUE);
} 