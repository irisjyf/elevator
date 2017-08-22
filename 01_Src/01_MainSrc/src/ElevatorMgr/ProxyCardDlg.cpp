// ProxyCardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ProxyCardDlg.h"
#include "afxdialogex.h"


// CProxyCardDlg �Ի���

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


// CProxyCardDlg ��Ϣ�������

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (m_cType == ADD_TYPE)
	{
		SetWindowText("���Ӹ߼���");
	}
	else
	{
		SetWindowText("�޸ĸ߼���");
	}

	SetPara2(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetPara2(TRUE);
	CAdvancCardSet *pMakeCardSet = LPDBManage->GetAdvancCardByID(m_ID);


	/*if (WirteIC(pMakeCardSet))
	{
		SetOutPutInfo("����д���ɹ���");
	}
	else
	{
		SetOutPutInfo("����д��ʧ�ܣ�");
		return;
	}*/

	if (LPDBManage->OperAdvancCard(pMakeCardSet,m_cType))
	{
		SetOutPutInfo("���ݱ���ɹ���");
		m_cType  =  MOD_TYPE;
	}
	else
		SetOutPutInfo("���ݱ���ʧ�ܣ�");
}

void CProxyCardDlg::OnBnClickedRepairCard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
