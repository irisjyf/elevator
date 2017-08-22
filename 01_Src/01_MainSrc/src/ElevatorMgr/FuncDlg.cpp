// FuncDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "FuncDlg.h"
#include "afxdialogex.h"
#include "QurryDlg.h"
#include "FuncInfoDlg.h"

// CFuncDlg 对话框

IMPLEMENT_DYNAMIC(CFuncDlg, CDialogEx)

CFuncDlg::CFuncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFuncDlg::IDD, pParent)
	, m_strKeyQurry(_T(""))
	, m_strComboxQurry(_T(""))
{

}

CFuncDlg::~CFuncDlg()
{
}

void CFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FLIED_LIST2, m_FuncList);
	DDX_Text(pDX, IDC_EDIT2, m_strKeyQurry);
	DDX_CBString(pDX, IDC_COMBO_F, m_strComboxQurry);
}


BEGIN_MESSAGE_MAP(CFuncDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FUNC_ADD, &CFuncDlg::OnBnClickedFuncAdd)
	ON_BN_CLICKED(IDC_FUNC_MOD, &CFuncDlg::OnBnClickedFuncMod)
	ON_NOTIFY(NM_DBLCLK, IDC_FLIED_LIST2, &CFuncDlg::OnNMDblclkFliedList2)
	ON_BN_CLICKED(IDC_FUNC_READCARD, &CFuncDlg::OnBnClickedFuncReadcard)
	ON_BN_CLICKED(IDC_BUTTON4, &CFuncDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BTN_FUNC_QURRY, &CFuncDlg::OnBnClickedBtnFuncQurry)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CFuncDlg::OnBnClickedBtnRefresh)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CFuncDlg 消息处理程序

BOOL CFuncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_FuncList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  在此添加额外的初始化
	m_FuncList.InsertColumn(0,"No.");
	m_FuncList.InsertColumn(1,"卡号");
	m_FuncList.InsertColumn(2,"功能卡类型");
	m_FuncList.InsertColumn(3,"SN");
	RECT rect;
	m_FuncList.GetWindowRect(&rect);
	int wid = rect.right - rect.left-35;
	m_FuncList.SetColumnWidth(0,50);
	m_FuncList.SetColumnWidth(1,70);
	m_FuncList.SetColumnWidth(2,wid/3);
	m_FuncList.SetColumnWidth(3,wid/3);
	m_FuncList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	OnBnClickedBtnRefresh();

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

 BOOL CFuncDlg::ShowTable(CArray<CKeyinfoset*,CKeyinfoset*> &arr)
 {
 	m_FuncList.DeleteAllItems();
 
 	int i=0;
 	long      iCode = 0;
 	CKeyinfoset*  pQuset= NULL;   
	for (int k = 0 ; k < arr.GetCount();k++)
	{
		pQuset  = arr.GetAt(k); 
		ASSERT(pQuset);

		if (!pQuset->m_bSave)
			continue;

 		CString Str,str2,str3;
 		Str.Format("%d",pQuset->m_id );
 		m_FuncList.InsertItem(i,Str);
 
 		Str.Format("%d",pQuset->m_gnkh);
 		m_FuncList.SetItemText(i,1,Str);

		CString strCard = GetFunctionCardType(pQuset->m_klx);
		m_FuncList.SetItemText(i,2,strCard);
		
		m_FuncList.SetItemText(i,3,pQuset->m_sn);

 		i++;  
 	}
 
 	return TRUE;
 }


void CFuncDlg::OnBnClickedFuncAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CFuncInfoDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetFuncID());
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}

void CFuncDlg::OnBnClickedFuncMod()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_FuncList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;


	CString  strID = m_FuncList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	CFuncInfoDlg dlg;
	dlg.SetPara(MOD_TYPE,lID);
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}


void CFuncDlg::OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedFuncMod();
}


void CFuncDlg::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_FuncList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_FuncList.GetItemText(iIndex,0);
	long lID  = atoi(strID);

	if(MessageBox("确定删除所选功能卡吗？","提示",MB_OKCANCEL)==IDOK)
	{
		int iStatus = ADD_TYPE;
		CKeyinfoset*  pQuset = LPDBManage->GetFuncByID(lID, iStatus);
		if (iStatus == MOD_TYPE && LPDBManage->OperFunc(pQuset,DEL_TYPE))
		{
			OnBnClickedBtnRefresh();
		}
	}
}


void CFuncDlg::OnBnClickedFuncReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnRefresh();
}

void CFuncDlg::OnBnClickedBtnFuncQurry()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CQurryDlg dlg;
	dlg.m_arrFiled.Add("卡号");
	dlg.m_arrFiled.Add("卡类型");

	if (dlg.DoModal()== IDOK)
	{
		CArray<CKeyinfoset*,CKeyinfoset*> arr;
		LPDBManage->QurryFunc(m_strComboxQurry,m_strKeyQurry,arr);
		ShowTable(arr);
	}
}


void CFuncDlg::OnBnClickedBtnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	CArray<CKeyinfoset*,CKeyinfoset*> arr;
	LPDBManage->GetFuncList(arr);
	ShowTable(arr);
}


void CFuncDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		//ReSize();  	
		float fsp[2];  
		POINT Newp; //获取现在对话框的大小  
		CRect recta;      
		GetClientRect(&recta);     //取客户区大小    
		Newp.x=recta.right-recta.left;  
		Newp.y=recta.bottom-recta.top;  
		fsp[0]=(float)Newp.x/m_old.x;  
		fsp[1]=(float)Newp.y/m_old.y;  
		CRect Rect;  
		int woc;  
		CPoint OldTLPoint,TLPoint; //左上角  
		CPoint OldBRPoint,BRPoint; //右下角  
		HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
		while(hwndChild)      
		{      
			woc=::GetDlgCtrlID(hwndChild);//取得ID  
			GetDlgItem(woc)->GetWindowRect(Rect);    
			ScreenToClient(Rect);    
			OldTLPoint = Rect.TopLeft();    
			TLPoint.x = long(OldTLPoint.x*fsp[0]);    
			TLPoint.y = long(OldTLPoint.y*fsp[1]);    
			OldBRPoint = Rect.BottomRight();    
			BRPoint.x = long(OldBRPoint.x *fsp[0]);    
			BRPoint.y = long(OldBRPoint.y *fsp[1]);    
			if (IDC_COMBO_F == woc)
			{
				CRect rc(CPoint(TLPoint.x,TLPoint.y),CPoint(BRPoint.x,Rect.Height()));
				GetDlgItem(woc)->MoveWindow(rc,TRUE);
			}
			else
			{
				Rect.SetRect(TLPoint,BRPoint);    
				GetDlgItem(woc)->MoveWindow(Rect,TRUE);
			} 
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
		}  
		m_old=Newp;  
	}
}

void CFuncDlg::ReSize()  
{  
	float fsp[2];  
	POINT Newp; //获取现在对话框的大小  
	CRect recta;      
	GetClientRect(&recta);     //取客户区大小    
	Newp.x=recta.right-recta.left;  
	Newp.y=recta.bottom-recta.top;  
	fsp[0]=(float)Newp.x/m_old.x;  
	fsp[1]=(float)Newp.y/m_old.y;  
	CRect Rect;  
	int woc;  
	CPoint OldTLPoint,TLPoint; //左上角  
	CPoint OldBRPoint,BRPoint; //右下角  
	HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
	while(hwndChild)      
	{      
		woc=::GetDlgCtrlID(hwndChild);//取得ID  
		GetDlgItem(woc)->GetWindowRect(Rect);    
		ScreenToClient(Rect);    
		OldTLPoint = Rect.TopLeft();    
		TLPoint.x = long(OldTLPoint.x*fsp[0]);    
		TLPoint.y = long(OldTLPoint.y*fsp[1]);    
		OldBRPoint = Rect.BottomRight();    
		BRPoint.x = long(OldBRPoint.x *fsp[0]);    
		BRPoint.y = long(OldBRPoint.y *fsp[1]);    
		if (IDC_COMBO_F == woc)
		{
			CRect rc(CPoint(TLPoint.x,TLPoint.y),CPoint(BRPoint.x,Rect.Height()));
			GetDlgItem(woc)->MoveWindow(rc,TRUE);
		}
		else
		{
			Rect.SetRect(TLPoint,BRPoint);    
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);
		} 
		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
	}  
	m_old=Newp;  
}

void CFuncDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CFuncDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnCancel();
}
