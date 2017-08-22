// ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "ManagerInfoDlg.h"
#include "QurryDlg.h"
#include "Comm/quset.h"

// CManagerDlg 对话框

IMPLEMENT_DYNAMIC(CManagerDlg, CDialogEx)

CManagerDlg::CManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerDlg::IDD, pParent)
	, m_strComboxQurry(_T(""))
	, m_strKeyQurry(_T(""))
{

}

CManagerDlg::~CManagerDlg()
{
}

void CManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FLIED_LIST2, m_ManagerList);
	DDX_CBString(pDX, IDC_COMBO_M, m_strComboxQurry);
	DDX_Text(pDX, IDC_EDIT12, m_strKeyQurry);
}


BEGIN_MESSAGE_MAP(CManagerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MANAGER_ADD, &CManagerDlg::OnBnClickedManagerAdd)
	ON_BN_CLICKED(IDC_BUTTON3, &CManagerDlg::OnBnClickedManagerMod)
	ON_NOTIFY(NM_DBLCLK, IDC_FLIED_LIST2, &CManagerDlg::OnNMDblclkFliedList2)
	ON_BN_CLICKED(IDC_MANAGER_DEL, &CManagerDlg::OnBnClickedManagerDel)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CManagerDlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_MANAGER_QURRY, &CManagerDlg::OnBnClickedBtnManagerQurry)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_READ_CARD, &CManagerDlg::OnBnClickedBtnReadCard)
END_MESSAGE_MAP()


// CManagerDlg 消息处理程序


void CManagerDlg::OnBnClickedManagerAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CManagerInfoDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetManagerID());
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}

void CManagerDlg::OnBnClickedManagerMod()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_ManagerList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_ManagerList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	CManagerInfoDlg dlg;
	
	dlg.SetPara(MOD_TYPE,lID);
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}

BOOL CManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_ManagerList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  在此添加额外的初始化
	m_ManagerList.InsertColumn(0,"NO.");
	m_ManagerList.InsertColumn(1,"卡号");
	m_ManagerList.InsertColumn(2,"管理员名称");
	m_ManagerList.InsertColumn(3,"可乘电梯");
	m_ManagerList.InsertColumn(4,"SN");
	m_ManagerList.InsertColumn(5,"状态");
	//	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	RECT rect;
	m_ManagerList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left - 35)/5;
	m_ManagerList.SetColumnWidth(0,35);
	m_ManagerList.SetColumnWidth(1,wid);
	m_ManagerList.SetColumnWidth(2,wid);
	m_ManagerList.SetColumnWidth(3,wid);
	m_ManagerList.SetColumnWidth(4,wid-10);
	m_ManagerList.SetColumnWidth(5,wid-10);
	m_ManagerList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	OnBnClickedBtnRefresh();

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL    CManagerDlg::ShowTable(CArray<Cquset*,Cquset*> &arr)
{
	m_ManagerList.DeleteAllItems();

	int i=0;
	long      iCode = 0;
	Cquset*  pQuset= NULL;  

	for (int k = 0 ; k < arr.GetCount();k++)
	{
		pQuset  = arr.GetAt(k);
		ASSERT(pQuset);

		if (!pQuset->m_bSave)
			continue;

		CString Str,str2,str3;
		Str.Format("%d",i+ 1);
		m_ManagerList.InsertItem(i,Str);

		Str.Format("%d",pQuset->m_glykh);
		m_ManagerList.SetItemText(i,1,Str);

		m_ManagerList.SetItemText(i,2,pQuset->m_glymc);

		Str="";
		if(pQuset->m_kydt1>0)
		{
			str2.Format("%d,",pQuset->m_kydt1);
			Str=str2;
		}
		if(pQuset->m_kydt2>0)
		{
			str2.Format("%d,",pQuset->m_kydt2);
			Str+=str2;
		}
		if(pQuset->m_kydt3>0)
		{
			str2.Format("%d,",pQuset->m_kydt3);
			Str+=str2;
		}

		if(pQuset->m_kydt4>0)
		{
			str2.Format("%d,",pQuset->m_kydt4);
			Str+=str2;
		}

		m_ManagerList.SetItemText(i,3,Str);

		if(pQuset->m_status==0)
			m_ManagerList.SetItemText(i,4,"0");
		else
			m_ManagerList.SetItemText(i,4,"1");

		if(pQuset->m_status == 1)
			m_ManagerList.SetItemText(i,5,"禁用");
		else if(pQuset->m_status == 3)
			m_ManagerList.SetItemText(i,5,"补卡");
		else
			m_ManagerList.SetItemText(i,5,"正常");
		i++;  
	}

	return TRUE;
}


void CManagerDlg::OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedManagerMod();
}


void CManagerDlg::OnBnClickedManagerDel()
{
	// TODO: 在此添加控件通知处理程序代码
	//int iIndex = m_ManagerList.GetNextItem(-1,LVNI_SELECTED);
	//if(iIndex < 0)  return;

	//CString  strID = m_ManagerList.GetItemText(iIndex,1);
	//long lID  = atoi(strID);

	//if(MessageBox("确定删除所选管理卡吗？","提示",MB_OKCANCEL)==IDOK)
	//{
	//	long lStatus = ADD_TYPE;
	//	Cquset *pQuset  = LPDBManage->GetManagerByID(lID, lStatus);
	//	if (LPDBManage->OperManager(pQuset,DEL_TYPE))
	//	{
	//		OnBnClickedBtnRefresh();
	//	}
	//}


	POSITION pos = m_ManagerList.GetFirstSelectedItemPosition();

	if(pos && MessageBox("确定删除所选内容吗？","提示",MB_OKCANCEL)==IDOK)
	{
		while(pos)
		{
			int nSelectItem = m_ManagerList.GetNextSelectedItem(pos);
			if (nSelectItem >= 0 && nSelectItem <m_ManagerList.GetItemCount())
			{
				CString  strID = m_ManagerList.GetItemText(nSelectItem,1);
				long lID  = atoi(strID);

				long lStatus = ADD_TYPE;
				Cquset *pQuset  = LPDBManage->GetManagerByID(lID, lStatus);
				LPDBManage->OperManager(pQuset,DEL_TYPE);
			}
		}
		OnBnClickedBtnRefresh();
	}
}


void CManagerDlg::OnBnClickedBtnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	CArray<Cquset*,Cquset*> arr;
	LPDBManage->GetManagerList(arr);
	ShowTable(arr);
}


void CManagerDlg::OnBnClickedBtnManagerQurry()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CQurryDlg dlg;
	dlg.m_arrFiled.Add("卡号");
	dlg.m_arrFiled.Add("管理员名称");
	dlg.m_arrFiled.Add("手机号码");

	if (dlg.DoModal()== IDOK)
	{
		CArray<Cquset*,Cquset*> arr;
		LPDBManage->QurryManager(m_strComboxQurry,m_strKeyQurry,arr);
		ShowTable(arr);
	}
}


void CManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
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
			if (IDC_COMBO_M == woc)
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
	// TODO: 在此处添加消息处理程序代码
}

void CManagerDlg::ReSize()  
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
		if (IDC_COMBO_M == woc)
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


void CManagerDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CManagerDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnCancel();
}


void CManagerDlg::OnBnClickedBtnReadCard()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char buf[80];
	memset(buf, 0, sizeof(buf));
	/////////////////////
	buf[0] = READ;  //写命令字
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	buf[4] = 0xff; //卡号
	buf[5] = TYPE_CARD_MGR; //卡类型
	buf[6] = 0x00; //子卡类型

	LPSerialProtocol->Send(IC_CMD_MANAGER, 7, buf);
	Sleep(300);
	BYTE pDatas[80] = {0};
	int nRet = LPSerialProtocol->ReadData(pDatas, 80);
	if(nRet <= 60)
	{
		Sleep(300);
		nRet = LPSerialProtocol->ReadData(pDatas, 80);
	}

	if(nRet < sizeof(T_FRAME_RET_HEAD))
	{
		LPSerialProtocol->Send(IC_CMD_MANAGER, 7, buf);
		Sleep(100);
		BYTE pDatas[80] = {0};
		int nRet = LPSerialProtocol->ReadData(pDatas, 80);
		if(nRet <= 0)
		{
			Sleep(100);
			nRet = LPSerialProtocol->ReadData(pDatas, 80);
		}
	}

	if(nRet > sizeof(T_FRAME_RET_HEAD))
	{
		LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
		LPT_MgrCardData pMgrCardData = (LPT_MgrCardData)(pDatas + sizeof(T_FRAME_RET_HEAD) + 2);
		if(lpFrameHead->chPacketType != IC_CMD_MANAGER)
		{
			AfxMessageBox("读取错误,请重新读取！");
			return;
		}
		if( pMgrCardData->dataType[0] == TYPE_USER)
		{
			AfxMessageBox("该卡片为业主卡，请在业主卡设置处读取修改！");
			return;
		}
		if( pMgrCardData->dataType[0] == TYPE_FUN)
		{
			AfxMessageBox("该卡片为功能卡，请在功能卡设置处读取修改！");
			return;
		}
		if( pMgrCardData->dataType[0] == TYPE_ADMIN)
		{
			CManagerInfoDlg dlg; 
			long nID = (pMgrCardData->btCardNo[0]<<16) + (pMgrCardData->btCardNo[1]<<8) + pMgrCardData->btCardNo[2];

			long lStatus = ADD_TYPE;
			Cquset *pset = LPDBManage->GetManagerByID(nID, lStatus);

			Cquset QusetData;
			QusetData.copy(*pset);
			dlg.SetPara(lStatus, nID);

			QusetData.m_xzms = pMgrCardData->btLimitType;
			QusetData.m_sycs = (pMgrCardData->btCounts[0] << 8) + pMgrCardData->btCounts[1];
			
			QusetData.m_sycs = (pMgrCardData->btCounts[0]<<8) + pMgrCardData->btCounts[1];
			int iYear, iMonth, iDay, iHour, iMinute;
			//起始时间
			iYear = pMgrCardData->btStartYear / 16 * 10 + pMgrCardData->btStartYear % 16 + 2000;
			iMonth = pMgrCardData->btStartMonth;
			iDay = pMgrCardData->btStartDay;
			iHour = pMgrCardData->btStartHour;
			iMinute = pMgrCardData->btStartMinute;

			QusetData.m_qssj.Format("%4d-%02d-%02d %02d:%02d:00", iYear, iMonth, iDay, iHour, iMinute);

			//截至时间
			iYear = pMgrCardData->btEndYear / 16 * 10 + pMgrCardData->btEndYear % 16 + 2000;
			iMonth = pMgrCardData->btEndMonth;
			iDay = pMgrCardData->btEndDay;
			iHour = pMgrCardData->btEndHour;
			iMinute = pMgrCardData->btEndMinute;
			QusetData.m_jzsj.Format("%4d-%02d-%02d %02d:%02d:00", iYear, iMonth, iDay, iHour, iMinute);

			QusetData.m_ctqxms = pMgrCardData->btAuthorityType;

			QusetData.m_kydt1 = pMgrCardData->btElevator_1;

			QusetData.m_kydt2 = pMgrCardData->btElevator_2;
			QusetData.m_kydt3 = pMgrCardData->btElevator_3;
			QusetData.m_kydt4 = pMgrCardData->btElevator_4;

			dlg.SetMgrData(QusetData);//修改
			
			dlg.m_bReadCardFlag = TRUE;
			dlg.m_strOutput = dlg.GetCardInfo(NULL);

			dlg.DoModal();
			return;
		}
	}
	AfxMessageBox("获取卡信息失败！");
}
