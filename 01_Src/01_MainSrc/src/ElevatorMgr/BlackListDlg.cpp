// CustomerBlackListt.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "BlackListDlg.h"
#include "afxdialogex.h"
#include "ProxyCardDlg.h"

// BlackListDlg �Ի���

IMPLEMENT_DYNAMIC(COtheCardDlg, CDialogEx)

COtheCardDlg::COtheCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COtheCardDlg::IDD, pParent)
{

}

COtheCardDlg::~COtheCardDlg()
{
}

void COtheCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTH_LIST, m_cList);
}


BEGIN_MESSAGE_MAP(COtheCardDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BLACK_QURRY, &COtheCardDlg::OnBnClickedBlackQurry)
	ON_BN_CLICKED(IDC_PROXY_ADD, &COtheCardDlg::OnBnClickedProxyAdd)
	ON_BN_CLICKED(IDC_PROXY_MOD, &COtheCardDlg::OnBnClickedProxyMod)
	ON_BN_CLICKED(IDC_PROXY_DEL, &COtheCardDlg::OnBnClickedProxyDel)
	ON_NOTIFY(NM_DBLCLK, IDC_AUTH_LIST, &COtheCardDlg::OnDblclkAuthList)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COtheCardDlg ��Ϣ�������


void COtheCardDlg::OnBnClickedBlackQurry()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL COtheCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_cList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cList.InsertColumn(0,"NO.");
	m_cList.InsertColumn(1,"����");
	m_cList.InsertColumn(2,"�ֿ���");
	m_cList.InsertColumn(3,"������");
	//m_BlackList.InsertColumn(4,"����������");
	m_cList.InsertColumn(4,"SN");
	RECT rect;
	m_cList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left -35)/4;
	m_cList.SetColumnWidth(0,35);
	m_cList.SetColumnWidth(1,wid);
	m_cList.SetColumnWidth(2,wid);
	m_cList.SetColumnWidth(3,wid);
	m_cList.SetColumnWidth(4,wid);
	//m_BlackList.SetColumnWidth(5,wid);

	m_cList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	FreshTable();

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top; 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void    COtheCardDlg::FreshTable()
{
	CArray<CAdvancCardSet*,CAdvancCardSet*> arr;
	LPDBManage->GetAdvancCardList(arr);
	ShowTable(arr);
}


BOOL    COtheCardDlg::ShowTable(CArray<CAdvancCardSet*,CAdvancCardSet*> &arr)
{
	m_cList.DeleteAllItems();

	int i=0;
	long      iCode = 0;
	CAdvancCardSet *pAdvancCardSet = NULL;  

	for (int i = 0 ; i < arr.GetCount();i++)
	{
		pAdvancCardSet  = arr.GetAt(i); 
		ASSERT(pAdvancCardSet);

		CString Str,str2,str3;
		Str.Format("%d",i+ 1);
		m_cList.InsertItem(i,Str);

		Str.Format("%d",pAdvancCardSet->m_ID);
		m_cList.SetItemText(i,1,Str);

		m_cList.SetItemText(i,2,pAdvancCardSet->m_ckr);

		m_cList.SetItemText(i,3,pAdvancCardSet->m_cCklc);

		m_cList.SetItemText(i,4,pAdvancCardSet->m_SN);
	}

	return TRUE;
}

void COtheCardDlg::OnBnClickedProxyAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CProxyCardDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetAdvancCardID());
	dlg.DoModal();
	FreshTable();
}


void COtheCardDlg::OnBnClickedProxyMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_cList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	CProxyCardDlg dlg;
	dlg.SetPara(MOD_TYPE,lID);
	dlg.DoModal();
	FreshTable();
}


void COtheCardDlg::OnBnClickedProxyDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_cList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	if(MessageBox("ȷ��ɾ����ѡҵ������","��ʾ",MB_OKCANCEL)==IDOK)
	{
		CAdvancCardSet *pAdvancCardSet  = LPDBManage->GetAdvancCardByID(lID);
		if (LPDBManage->OperAdvancCard(pAdvancCardSet,DEL_TYPE))
		{
			;
		}
	}
}


void COtheCardDlg::OnDblclkAuthList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	OnBnClickedProxyMod();
}


void COtheCardDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		ReSize();  
	}
	// TODO: �ڴ˴������Ϣ����������
}
