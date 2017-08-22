// ProxyCardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ProxyCardDlg.h"
#include "afxdialogex.h"


// CProxyCardDlg 对话框

IMPLEMENT_DYNAMIC(CProxyCardDlg, CDialogEx)

CProxyCardDlg::CProxyCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProxyCardDlg::IDD, pParent)
	, m_ID(0)
	, m_ckr(_T(""))
	, m_sjhm(_T(""))
	, m_SN(_T(""))
	, m_bz(_T(""))
	, m_cklx(_T(""))
	, m_strOutput(_T(""))
{

}

CProxyCardDlg::~CProxyCardDlg()
{
}

void CProxyCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROXY_NAME2, m_ID);
	DDX_Text(pDX, IDC_EDIT_PROXY_NAME, m_ckr);
	DDX_Text(pDX, IDC_EDIT_PROXY_MOBILE, m_sjhm);
	DDX_Text(pDX, IDC_EDIT_PROXY_SN, m_SN);
	DDX_Text(pDX, IDC_EDIT_PROXY_DES, m_bz);
	DDX_Control(pDX, IDC_COMBO_PROXY_CARD_TYPE, m_cCklc);
	DDX_CBString(pDX, IDC_COMBO_PROXY_CARD_TYPE, m_cklx);
	DDX_Text(pDX, IDC_EDIT12, m_strOutput);
}


BEGIN_MESSAGE_MAP(CProxyCardDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProxyCardDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDD_REPAIR_CARD, &CProxyCardDlg::OnBnClickedRepairCard)
END_MESSAGE_MAP()


// CProxyCardDlg 消息处理程序

void   CProxyCardDlg::SetPara(char cType, long lID)
{
	m_ID    = lID;
	m_cType = cType;
}

BOOL    CProxyCardDlg::SetPara2(BOOL bSave)
{
	UpdateData(TRUE);
	CAdvancCardSet *pMakeCardSet = LPDBManage->GetAdvancCardByID(m_ID);
	CString strTemp;
	if (bSave)
	{
		pMakeCardSet->m_ID      =  m_ID;
		pMakeCardSet->m_ckr    =  m_ckr;
		pMakeCardSet->m_sjhm    =  m_sjhm;
		pMakeCardSet->m_SN    =  m_SN;
		pMakeCardSet->m_bz    =  m_bz;
		pMakeCardSet->m_cCklc    =  m_cklx;
	}
	else
	{
		m_ID      =  pMakeCardSet->m_ID;
		m_ckr     =  pMakeCardSet->m_ckr;
		m_sjhm    =  pMakeCardSet->m_sjhm;
		m_SN      =  pMakeCardSet->m_SN;
		m_bz      =  pMakeCardSet->m_bz;
		m_cklx      =  pMakeCardSet->m_cCklc;
	}

	UpdateData(FALSE);
	return TRUE;
}

BOOL CProxyCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	if (m_cType == ADD_TYPE)
	{
		SetWindowText("增加高级卡");
	}
	else
	{
		SetWindowText("修改高级卡");
	}

	SetPara2(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void  CProxyCardDlg::SetOutPutInfo(CString strInfo)
{
	UpdateData(TRUE);

	CString strTemp;

	m_strOutput = "\r\n" + m_strOutput ;
	strTemp = strTemp + strInfo +"\r\n";

	m_strOutput = strTemp + m_strOutput;

	UpdateData(FALSE);
}

void CProxyCardDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara2(TRUE);
	CAdvancCardSet *pMakeCardSet = LPDBManage->GetAdvancCardByID(m_ID);


	/*if (WirteIC(pMakeCardSet))
	{
		SetOutPutInfo("数据写卡成功！");
	}
	else
	{
		SetOutPutInfo("数据写卡失败！");
		return;
	}*/

	if (LPDBManage->OperAdvancCard(pMakeCardSet,m_cType))
	{
		SetOutPutInfo("数据保存成功！");
		m_cType  =  MOD_TYPE;
	}
	else
		SetOutPutInfo("数据保存失败！");
}

void CProxyCardDlg::OnBnClickedRepairCard()
{
	// TODO: 在此添加控件通知处理程序代码
}
