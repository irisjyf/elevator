// ManagerProxyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ManagerProxyDlg.h"
#include "afxdialogex.h"


// CManagerProxyDlg �Ի���

IMPLEMENT_DYNAMIC(CManagerProxyDlg, CDialogEx)

CManagerProxyDlg::CManagerProxyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerProxyDlg::IDD, pParent)
	, m_dlsmc(_T(""))
	, m_sjhm(_T(""))
	, m_ID(1)
	, m_dlsbh(1)
	, m_bzxx(_T(""))
	, m_sn(_T(""))
	, m_bAgentFlag(FALSE)
	, m_bRecode(FALSE)
{

}

CManagerProxyDlg::~CManagerProxyDlg()
{
}

void CManagerProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PROXY_NAME, m_dlsmc);
	DDX_Text(pDX, IDC_EDIT1_PROXY_MOBILE, m_sjhm);
	DDX_Text(pDX, IDC_EDIT_PROXY_ID, m_dlsbh);
	DDX_Text(pDX, IDC_EDIT_PROXY_INFO, m_bzxx);
	DDX_Text(pDX, IDC_EDIT_PROXY_INFO2, m_sn);
	DDX_Check(pDX, IDC_CHK_AGENT_ENABLE, m_bAgentFlag);
	DDX_Check(pDX, IDC_CHK_RECODE, m_bRecode);
}


BEGIN_MESSAGE_MAP(CManagerProxyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CManagerProxyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CManagerProxyDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_WRITECARD, &CManagerProxyDlg::OnBnClickedBtnWritecard)
	ON_BN_CLICKED(IDC_BTN_GET_SERIAL, &CManagerProxyDlg::OnBnClickedBtnGetSerial)
	ON_BN_CLICKED(IDC_BTN_WRITECARDER, &CManagerProxyDlg::OnBnClickedBtnWritecarder)
END_MESSAGE_MAP()


BOOL CManagerProxyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_cType == ADD_TYPE)
		SetWindowText("������ҵ����");
	else
		SetWindowText("�޸���ҵ����");

	LPDBManage->GetProxyList();

	SetPara2(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

BOOL  CManagerProxyDlg::SetPara2(BOOL bSave)
{
	UpdateData(TRUE);
	CProxySet *pProxySet = LPDBManage->GetProxyByID(m_ID);
	CString strTemp;
	if (bSave)
	{
		pProxySet->m_dlsbh    =   m_dlsbh;
		pProxySet->m_dlsmc    =   m_dlsmc;
		pProxySet->m_sjhm     =   m_sjhm;
		pProxySet->m_bzxx     =   m_bzxx;
		pProxySet->m_sn       =   m_sn;
		pProxySet->m_dlsid.Format("%d",m_dlsbh);
	}
	else
	{
		m_dlsbh       =  pProxySet->m_dlsbh;
		m_dlsmc       =  pProxySet->m_dlsmc;
		m_sjhm        =  pProxySet->m_sjhm;
		m_bzxx        =  pProxySet->m_bzxx;
		m_sn          =  pProxySet->m_sn;
	}

	UpdateData(FALSE);
	return TRUE;
}

void CManagerProxyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	if(m_ID != m_dlsbh)
	{
		LPDBManage->RemoveProxyOfID(m_ID);
		m_ID = m_dlsbh;
	}

	SetPara2(TRUE);
	
	CProxySet *pProxySet = LPDBManage->GetProxyByID(m_ID);
	
	if (LPDBManage->OperProxySet(pProxySet,m_cType))
	{
		m_cType  =  MOD_TYPE;;
	}

	CDialogEx::OnOK();
}


void CManagerProxyDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CProxySet *pProxySet = LPDBManage->GetProxyByID(m_ID);
	if (m_cType == ADD_TYPE )
	{
		LPDBManage->OperProxySet(pProxySet,DEL_TYPE);
	}

	CDialogEx::OnCancel();
}

void CManagerProxyDlg::OnBnClickedBtnWritecard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString szMsg;
	DWORD dwAgentID = m_dlsbh;
	BOOL bRet  = CRadioCardProtocal::GetRadioCardProtocal()->WriteAgentIDCard(dwAgentID, m_bAgentFlag);
	if(!bRet)
		szMsg.Format("��ҵ����ID:%d����ʧ��", dwAgentID);
	else
		szMsg.Format("��ҵ����ID:%d���ɳɹ�", dwAgentID);
	
	log_info(szMsg);

	AfxMessageBox(szMsg);

}


void CManagerProxyDlg::OnBnClickedBtnGetSerial()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char chBuf[100] = {0};
	DWORD dwRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadSerialNo();
	if(dwRet > 0)
	{
		_ultoa(dwRet, chBuf, 10);
		m_sn.Format("%s", chBuf);
	}
	UpdateData(FALSE);
}


void CManagerProxyDlg::OnBnClickedBtnWritecarder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	UpdateData();
	CString szMsg;
	DWORD dwAgentID = m_dlsbh;
	BOOL bRet  = CRadioCardProtocal::GetRadioCardProtocal()->WriteAgentID(dwAgentID);
	if(!bRet)
		szMsg.Format("д����ID:%d����ʧ��", dwAgentID);
	else
		szMsg.Format("д����ID:%d���ɳɹ�", dwAgentID);
	log_info(szMsg);

	AfxMessageBox(szMsg);
}
