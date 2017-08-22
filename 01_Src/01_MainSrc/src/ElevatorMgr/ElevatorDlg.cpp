// ElevatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ElevatorDlg.h"
#include "afxdialogex.h"

#include "ElevatorInfoDlg.h"
#include "QurryDlg.h"
// CElevatorDlg 对话框

IMPLEMENT_DYNAMIC(CElevatorDlg, CDialogEx)

CElevatorDlg::CElevatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CElevatorDlg::IDD, pParent)
	, m_strComboxQurry(_T(""))
	, m_strKeyQurry(_T(""))
{

}

CElevatorDlg::~CElevatorDlg()
{
}

void CElevatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FLIED_LIST2, m_ElevatorList);
	DDX_CBString(pDX, IDC_COMBO_E, m_strComboxQurry);
	DDX_Text(pDX, IDC_EDIT12, m_strKeyQurry);
}


BEGIN_MESSAGE_MAP(CElevatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ELEVATOR_ADD, &CElevatorDlg::OnBnClickedElevatorAdd)
	ON_BN_CLICKED(IDC_ELEVATOR_MOD, &CElevatorDlg::OnBnClickedElevatorMod)
	ON_NOTIFY(NM_DBLCLK, IDC_FLIED_LIST2, &CElevatorDlg::OnNMDblclkFliedList2)
	ON_BN_CLICKED(IDC_BUTTON4, &CElevatorDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CElevatorDlg::OnBnClickedBtnRefresh)
	ON_WM_SIZE()
	//ON_BN_CLICKED(IDC_BTN_QUERY, &CElevatorDlg::OnBnClickedBtnQuery)
	ON_NOTIFY(NM_CLICK, IDC_FLIED_LIST2, &CElevatorDlg::OnNMClickFliedList2)
END_MESSAGE_MAP()


// CElevatorDlg 消息处理程序

BOOL CElevatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_ElevatorList.SetImageList(&m_image, LVSIL_SMALL);

	//m_ElevatorList.SetExtendedStyle(m_ElevatorList.GetExtendedStyle() & ~LVS_SINGLESEL);

	m_ElevatorList.InsertColumn(0,"序号",LVCFMT_CENTER,50,-1);
	m_ElevatorList.InsertColumn(1,"编号",LVCFMT_CENTER,50,-1);
	m_ElevatorList.InsertColumn(2,"电梯名称",LVCFMT_CENTER,200,-1);
	m_ElevatorList.InsertColumn(3,"电梯类型",LVCFMT_CENTER,50,-1);
	m_ElevatorList.InsertColumn(4,"总层数",LVCFMT_CENTER,50,-1);
	m_ElevatorList.InsertColumn(5,"起始楼层",LVCFMT_CENTER,50,-1);
	m_ElevatorList.InsertColumn(6,"公共楼层",LVCFMT_CENTER,50,-1);
	m_ElevatorList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	RECT rect;
	m_ElevatorList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left- 35)/5;
	m_ElevatorList.SetColumnWidth(0,35);
	m_ElevatorList.SetColumnWidth(1,60);
	m_ElevatorList.SetColumnWidth(2,wid / 2 * 3);
	m_ElevatorList.SetColumnWidth(3,wid / 2);
	m_ElevatorList.SetColumnWidth(4,wid / 2);
	m_ElevatorList.SetColumnWidth(5,wid / 2-10);

	LPDBManage->GetElevatorList(m_arrElevator);

	ShowTable(m_arrElevator);

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CElevatorDlg::ShowTable(CArray<CSuoset*,CSuoset*> &arr)
{
	m_ElevatorList.DeleteAllItems();

	int i=0;
	long      iCode = 0;
	CSuoset*  pQuset= NULL;  

	for (int k = 0 ; k < arr.GetCount();k++)
	{
		pQuset  = arr.GetAt(k); 
		ASSERT(pQuset);

		if (!pQuset->m_bSave)
			continue;

		CString strTemp;
		strTemp.Format("%d",i+1);
		m_ElevatorList.InsertItem(i,strTemp);

		strTemp.Format("%d", pQuset->m_dtbh);
		m_ElevatorList.SetItemText(i,1,strTemp);
		m_ElevatorList.SetItemText(i,2,pQuset->m_dtmc);

		if(pQuset->m_dtlx==0)
			m_ElevatorList.SetItemText(i,3,"普通电梯");
		else
			m_ElevatorList.SetItemText(i,3,"贯通门电梯");

		strTemp.Format("%d",pQuset->m_dtcs);
		m_ElevatorList.SetItemText(i, 4, strTemp);

		strTemp.Format("%d",pQuset->m_qslc);
		m_ElevatorList.SetItemText(i,5,strTemp);

		strTemp.Format("%d",pQuset->m_gglc);
		m_ElevatorList.SetItemText(i,6,strTemp);
		i++;  
	}

	return TRUE;
}

void CElevatorDlg::OnBnClickedElevatorAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CElevatorInfoDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetElevatorID());
	if(dlg.DoModal() == IDOK )
	{
		LPDBManage->GetElevatorList(m_arrElevator);
		UpdataTable();
	}
}


void CElevatorDlg::OnBnClickedElevatorMod()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_ElevatorList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  
		return;

	ModifyElevatorInfo(iIndex);

	UpdataTable();
}
void CElevatorDlg::UpdataTable()
{
	ShowTable(m_arrElevator);
}
void CElevatorDlg::OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMItemActivate->iItem < 0)
		return;
	ModifyElevatorInfo(pNMItemActivate->iItem);
	UpdataTable();
}

void CElevatorDlg::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码

	POSITION pos = m_ElevatorList.GetFirstSelectedItemPosition();

	if(pos && MessageBox("确定删除所选电梯吗？","提示",MB_OKCANCEL)==IDOK)
	{
		while(pos)
		{
			int nSelectItem = m_ElevatorList.GetNextSelectedItem(pos);
			if (nSelectItem >= 0 && nSelectItem <m_ElevatorList.GetItemCount())
			{
				CSuoset* pSuoset = m_arrElevator.GetAt(nSelectItem);
				if(!pSuoset)
					return;

				if (LPDBManage->OperElevator(pSuoset,DEL_TYPE))
				{
					m_arrElevator.RemoveAt(nSelectItem);

				}
			}
		}
	}
	UpdataTable();
	//int iIndex = m_ElevatorList.GetNextItem(-1,LVNI_SELECTED);
	//if(iIndex < 0)  
	//	return;

	//CSuoset* pSuoset = m_arrElevator.GetAt(iIndex);
	//if(!pSuoset)
	//	return;

	//if(MessageBox("确定删除所选电梯吗？","提示",MB_OKCANCEL)==IDOK)
	//{
	//	if (LPDBManage->OperElevator(pSuoset,DEL_TYPE))
	//	{
	//		m_arrElevator.RemoveAt(iIndex);
	//		UpdataTable();
	//	}
	//}
}

void CElevatorDlg::OnBnClickedBtnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdataTable();
}


void CElevatorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	CDialogEx::OnSize(nType, cx, cy);
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		ReSize();  
	} 
	// TODO: 在此处添加消息处理程序代码
}


void CElevatorDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CElevatorDlg::ModifyElevatorInfo(int iIndex)
{

	CSuoset* pSuoset = m_arrElevator.GetAt(iIndex);
	if(!pSuoset)
		return;

	CElevatorInfoDlg dlg;
	dlg.SetPara(MOD_TYPE,pSuoset->m_dtbh);
	if(dlg.DoModal() == IDOK)
	{
		pSuoset->m_dtbh = dlg.m_dtbh;
		pSuoset->m_dtmc = dlg.m_dtmc;
		pSuoset->m_dtlx = dlg.m_dtlx;
		pSuoset->m_dtcs = dlg.m_iFlootCount;
		pSuoset->m_qslc = dlg.m_iStartFloor;
		pSuoset->m_gglc = dlg.m_iCommonFloor;
	}
}

void CElevatorDlg::ReSize()  
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
		if (IDC_COMBO_E == woc)
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

void CElevatorDlg::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码

	CQurryDlg dlg;
	dlg.m_arrFiled.Add("电梯名称");
	dlg.m_arrFiled.Add("电梯类型");

	if (dlg.DoModal()== IDOK)
	{
		CArray<CSuoset*,CSuoset*> arr;
		LPDBManage->QurryElevator(m_strComboxQurry,m_strKeyQurry,arr);
		ShowTable(arr);
	}
}


void CElevatorDlg::OnNMClickFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
