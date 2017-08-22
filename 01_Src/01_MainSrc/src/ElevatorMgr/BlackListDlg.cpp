// CustomerBlackListt.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "BlackListDlg.h"
#include "afxdialogex.h"
#include "ProxyCardDlg.h"

// BlackListDlg 对话框

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

// COtheCardDlg 消息处理程序


void COtheCardDlg::OnBnClickedBlackQurry()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL COtheCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_cList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  在此添加额外的初始化
	m_cList.InsertColumn(0,"NO.");
	m_cList.InsertColumn(1,"卡号");
	m_cList.InsertColumn(2,"持卡人");
	m_cList.InsertColumn(3,"卡类型");
	//m_BlackList.InsertColumn(4,"黑名单次数");
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
	// 异常: OCX 属性页应返回 FALSE
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
	// TODO: 在此添加控件通知处理程序代码
	CProxyCardDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetAdvancCardID());
	dlg.DoModal();
	FreshTable();
}


void COtheCardDlg::OnBnClickedProxyMod()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_cList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	if(MessageBox("确定删除所选业主卡吗？","提示",MB_OKCANCEL)==IDOK)
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此处添加消息处理程序代码
}
