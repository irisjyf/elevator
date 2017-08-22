// ProxyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ProxyDlg.h"
#include "afxdialogex.h"
#include "ManagerProxyDlg.h"


// CProxyDlg �Ի���

IMPLEMENT_DYNAMIC(CProxyDlg, CDialogEx)

CProxyDlg::CProxyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProxyDlg::IDD, pParent)
{

}

CProxyDlg::~CProxyDlg()
{
}

void CProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTH_LIST, m_cList);
}


BEGIN_MESSAGE_MAP(CProxyDlg, CDialogEx)
	ON_BN_CLICKED(IDC_PROXY_ADD, &CProxyDlg::OnBnClickedProxyAdd)
	ON_BN_CLICKED(IDC_PROXY_MOD, &CProxyDlg::OnBnClickedProxyMod)
	ON_BN_CLICKED(IDC_PROXY_DEL, &CProxyDlg::OnBnClickedProxyDel)
	ON_NOTIFY(NM_DBLCLK, IDC_AUTH_LIST, &CProxyDlg::OnNMDblclkAuthList)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CProxyDlg ��Ϣ�������

BOOL CProxyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_cList.SetImageList(&m_image, LVSIL_SMALL);


	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_cList.InsertColumn(0,"No.");
	m_cList.InsertColumn(1,"��ҵID");
	m_cList.InsertColumn(2,"��ҵ����");
	m_cList.InsertColumn(3,"�ֻ�����");
	m_cList.InsertColumn(4,"SN");
	m_cList.InsertColumn(5,"��ע");

	RECT rect;
	m_cList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left - 35 - 70)/4;
	m_cList.SetColumnWidth(0,45);
	m_cList.SetColumnWidth(1,70);
	m_cList.SetColumnWidth(2,wid);
	m_cList.SetColumnWidth(3,100);
	m_cList.SetColumnWidth(4,100);
	wid = rect.right - rect.left - 35 - 70 - wid - 200;
	m_cList.SetColumnWidth(5,wid);

	m_cList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	ShowTable();

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top; 

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


BOOL  CProxyDlg::ShowTable()
{
	m_cList.DeleteAllItems();

	CProxySet *pProxySet = NULL;
	CString strName(""),strTemp;
	long lID;

	int i=0;
	LPDBManage->m_mapProxy.RemoveAll();
	LPDBManage->GetProxyList();
	POSITION pos = LPDBManage->m_mapProxy.GetStartPosition();
	while(pos)
	{
		LPDBManage->m_mapProxy.GetNextAssoc(pos,lID,pProxySet);
		ASSERT(pProxySet);

		strTemp.Format("%d",i+1);
		m_cList.InsertItem(i,strTemp);

		strTemp.Format("%d",pProxySet->m_dlsbh);
		m_cList.SetItemText(i,1,strTemp);
		
		m_cList.SetItemText(i,2,pProxySet->m_dlsmc);
		m_cList.SetItemText(i,3,pProxySet->m_sjhm);
		m_cList.SetItemText(i,4,pProxySet->m_sn);
		m_cList.SetItemText(i,5,pProxySet->m_bzxx);

		i++;  
	}

	Invalidate(TRUE);
	return TRUE;
}


void CProxyDlg::OnBnClickedProxyAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CManagerProxyDlg dlg;
	dlg.SetPara(ADD_TYPE, LPDBManage->GetProxyID());
	if (IDOK != dlg.DoModal())	
		return ;
	ShowTable();
}

void CProxyDlg::OnBnClickedProxyMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  
		return;

	CString  strID = m_cList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	CManagerProxyDlg dlg;
	dlg.SetPara(MOD_TYPE,lID);
	if(dlg.DoModal() == IDOK)
		ShowTable();
}

void CProxyDlg::OnBnClickedProxyDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_cList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	if(MessageBox("ȷ��ɾ����ѡ�û���","��ʾ",MB_OKCANCEL)==IDOK)
	{
		CProxySet* pProxySet = LPDBManage->GetProxyByID(lID);
		if (LPDBManage->OperProxySet(pProxySet,DEL_TYPE))
		{
			ShowTable();
		}
	}
}


void CProxyDlg::OnNMDblclkAuthList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	OnBnClickedProxyMod();
}


void CProxyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		ReSize();  
	}
	// TODO: �ڴ˴������Ϣ����������
}


void CProxyDlg::ReSize()  
{  
	float fsp[2];  
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
	CRect recta;      
	GetClientRect(&recta);     //ȡ�ͻ�����С    
	Newp.x=recta.right-recta.left;  
	Newp.y=recta.bottom-recta.top;  
	fsp[0]=(float)Newp.x/m_old.x;  
	fsp[1]=(float)Newp.y/m_old.y;  
	CRect Rect;  
	int woc;  
	CPoint OldTLPoint,TLPoint; //���Ͻ�  
	CPoint OldBRPoint,BRPoint; //���½�  
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�    
	while(hwndChild)      
	{      
		woc=::GetDlgCtrlID(hwndChild);//ȡ��ID  
		GetDlgItem(woc)->GetWindowRect(Rect);    
		ScreenToClient(Rect);    
		OldTLPoint = Rect.TopLeft();    
		TLPoint.x = long(OldTLPoint.x*fsp[0]);    
		TLPoint.y = long(OldTLPoint.y*fsp[1]);    
		OldBRPoint = Rect.BottomRight();    
		BRPoint.x = long(OldBRPoint.x *fsp[0]);    
		BRPoint.y = long(OldBRPoint.y *fsp[1]);    
		Rect.SetRect(TLPoint,BRPoint);    
		GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
	}  
	m_old=Newp;  
} 