// CustomerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "CustomerDlg.h"
#include "afxdialogex.h"
#include "comm\Yonghuset.h"
#include "CustermerInfoDlg.h"
#include "QurryDlg.h"
#include "DelOkDlg.h"
// CCustomerDlg 对话框


extern CDatabase db;

IMPLEMENT_DYNAMIC(CCustomerDlg, CDialogEx)

CCustomerDlg::CCustomerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustomerDlg::IDD, pParent)
	, m_strKeyQurry(_T(""))
	, m_strComboxQurry(_T(""))
{

}

CCustomerDlg::~CCustomerDlg()
{
}

void CCustomerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FLIED_LIST2, m_CustomerList);
	DDX_Text(pDX, IDC_EDIT2, m_strKeyQurry);
	DDX_CBString(pDX, IDC_COMBO_C, m_strComboxQurry);
	DDX_Control(pDX, IDC_COMBO_C, m_cComboxQurry);
}


BEGIN_MESSAGE_MAP(CCustomerDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CUSTOMER_ADD, &CCustomerDlg::OnBnClickedCustomerAdd)
	ON_BN_CLICKED(IDC_BUTTON6, &CCustomerDlg::OnBnClickedCusterQurry)
	ON_BN_CLICKED(IDC_CUSTOMER_MOD, &CCustomerDlg::OnBnClickedCustomerMod)
	ON_NOTIFY(NM_DBLCLK, IDC_FLIED_LIST2, &CCustomerDlg::OnNMDblclkFliedList2)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CCustomerDlg::OnBnClickedBtnRefresh)
	ON_BN_CLICKED(IDC_CUSTOMER_DEL, &CCustomerDlg::OnBnClickedCustomerDel)
	ON_BN_CLICKED(IDC_CUSTOMER_READCARD, &CCustomerDlg::OnBnClickedCustomerReadcard)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_READUSERINFO, &CCustomerDlg::OnBnClickedBtnReaduserinfo)
END_MESSAGE_MAP()


// CCustomerDlg 消息处理程序

BOOL CCustomerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_CustomerList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  在此添加额外的初始化
	m_CustomerList.InsertColumn(0,"NO.");
	m_CustomerList.InsertColumn(1,"卡号");
	m_CustomerList.InsertColumn(2,"业主名称");
	m_CustomerList.InsertColumn(3,"业主门牌");
	m_CustomerList.InsertColumn(4,"可乘电梯");
	m_CustomerList.InsertColumn(5,"有效期");
	m_CustomerList.InsertColumn(6,"SN");
	m_CustomerList.InsertColumn(7,"状态");
	RECT rect;
	m_CustomerList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left -35)/7;
	m_CustomerList.SetColumnWidth(0,35);
	m_CustomerList.SetColumnWidth(1,wid-30);
	m_CustomerList.SetColumnWidth(2,wid-30);
	m_CustomerList.SetColumnWidth(3,wid+20);
	m_CustomerList.SetColumnWidth(4,wid-30);
	m_CustomerList.SetColumnWidth(5,wid+70);
	m_CustomerList.SetColumnWidth(6,wid-10);
	m_CustomerList.SetColumnWidth(7,wid-10);
	m_CustomerList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	OnBnClickedBtnRefresh();

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL    CCustomerDlg::ShowTable(CArray<CYonghuset*,CYonghuset*> &arr)
{
	m_CustomerList.DeleteAllItems();

	int i=0;
	long      iCode = 0;
	CYonghuset *pYonghuset = NULL;  

	for (int k = 0 ; k < arr.GetCount();k++)
	{
		pYonghuset  = arr.GetAt(k); 
		ASSERT(pYonghuset);

		if (!pYonghuset->m_bSave)
			continue;
	
		CString Str,str2,str3;
		Str.Format("%d",i+ 1);
		m_CustomerList.InsertItem(i,Str);

		Str.Format("%d",pYonghuset->m_yzkh);
		m_CustomerList.SetItemText(i,1,Str);
		m_CustomerList.SetItemText(i,2,pYonghuset->m_yzmc);
		m_CustomerList.SetItemText(i,3,pYonghuset->m_yzmp);

		Str="";
		if(pYonghuset->m_kydt1> 0)
		{
			str2.Format("%d,",pYonghuset->m_kydt1);
			Str=str2;
		}
		if(pYonghuset->m_kydt2>0)
		{
			str2.Format("%d,",pYonghuset->m_kydt2);
			Str+=str2;
		}
		if(pYonghuset->m_kydt3>0)
		{
			str2.Format("%d,",pYonghuset->m_kydt3);
			Str+=str2;
		}

		if(pYonghuset->m_kydt4>0)
		{
			str2.Format("%d,",pYonghuset->m_kydt4);
			Str+=str2;
		}

		m_CustomerList.SetItemText(i,4,Str);
		m_CustomerList.SetItemText(i,5,pYonghuset->m_qssj+" "+pYonghuset->m_jzsj);

		m_CustomerList.SetItemText(i,6,pYonghuset->m_sn);
		
		if(pYonghuset->m_status == 1)
			m_CustomerList.SetItemText(i,7,"禁用");
		else if(pYonghuset->m_status == 3)
			m_CustomerList.SetItemText(i,7,"补卡");
		else
			m_CustomerList.SetItemText(i,7,"正常");

		i++;  
	}

	return TRUE;
}

void CCustomerDlg::OnBnClickedCusterQurry()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CQurryDlg dlg;
	dlg.m_arrFiled.Add("卡号");
	dlg.m_arrFiled.Add("业主姓名");
	dlg.m_arrFiled.Add("业主门牌");
	dlg.m_arrFiled.Add("手机号码");

	if (dlg.DoModal()== IDOK)
	{
		CArray<CYonghuset*,CYonghuset*> arr;
		LPDBManage->QurryCustomer(dlg.m_strQurryBox,dlg.m_strQurryKey,arr);
		ShowTable(arr);
	}
}

void CCustomerDlg::OnBnClickedCustomerAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CCustermerInfoDlg dlg(this);
	dlg.SetPara(ADD_TYPE,LPDBManage->GetCustermerID());
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}


void CCustomerDlg::OnBnClickedCustomerMod()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_CustomerList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strID = m_CustomerList.GetItemText(iIndex,1);
	long lID  = atoi(strID);

	CCustermerInfoDlg dlg(this);

	dlg.SetParemtDlg(this);

	dlg.SetPara(MOD_TYPE,lID);
	
	dlg.DoModal();
	
	OnBnClickedBtnRefresh();
}


void CCustomerDlg::OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	OnBnClickedCustomerMod();
}


void CCustomerDlg::OnBnClickedBtnRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	CArray<CYonghuset*,CYonghuset*> arr;
	LPDBManage->GetCustermerList(arr);
	ShowTable(arr);
}
void CCustomerDlg::OnBnClickedCustomerDel()
{
	// TODO: 在此添加控件通知处理程序代码
	//int iIndex = m_CustomerList.GetNextItem(-1,LVNI_SELECTED);
	//if(iIndex < 0)  return;

	//CString  strID = m_CustomerList.GetItemText(iIndex,1);
	//long lID  = atoi(strID);

	//CDelOkDlg dlg;
	//if (dlg.DoModal() !=IDOK)
	//	return;

	//if ( 0 != LPDBManage->m_USERINFO.m_strPsw.CompareNoCase(dlg.m_strPsw))
	//{
	//	AfxMessageBox("密码不正确,请重新输入!");
	//	return;
	//}


	POSITION pos = m_CustomerList.GetFirstSelectedItemPosition();

	if(pos && MessageBox("确定删除所选内容吗？","提示",MB_OKCANCEL)==IDOK)
	{

		CDelOkDlg dlg;
		if (dlg.DoModal() !=IDOK)
			return;

		if ( 0 != LPDBManage->m_USERINFO.m_strPsw.CompareNoCase(dlg.m_strPsw))
		{
			AfxMessageBox("密码不正确,请重新输入!");
			return;
		}

		while(pos)
		{
			int nSelectItem = m_CustomerList.GetNextSelectedItem(pos);
			if (nSelectItem >= 0 && nSelectItem <m_CustomerList.GetItemCount())
			{
				CString  strID = m_CustomerList.GetItemText(nSelectItem,1);
				long lID  = atoi(strID);

				long lStatus = ADD_TYPE;
				CYonghuset *pCYonghuset  = LPDBManage->GetCustermerByID(lID, lStatus);
				LPDBManage->OpereCustomer(pCYonghuset,DEL_TYPE);
			}
		}
		OnBnClickedBtnRefresh();
	}

	//		
	//if(MessageBox("确定删除所选业主卡吗？","提示",MB_OKCANCEL)==IDOK)
	//{
	//	long lStatus = ADD_TYPE;
	//	CYonghuset *pCYonghuset  = LPDBManage->GetCustermerByID(lID, lStatus);
	//	if (LPDBManage->OpereCustomer(pCYonghuset,DEL_TYPE))
	//	{
	//		OnBnClickedBtnRefresh();
	//	}
	//}
}

void CCustomerDlg::OnBnClickedCustomerReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	char data[100] = {0} ;

	// 上位机读业主卡信息
	/*if (!LPSerialProtocol->Send(MSG_READ_CUSTOMER_INFO,2,data))*/
	{
		MessageBox("读卡失败, 请检查通讯设置！","错误",MB_YESNO);
		return;
	}
}

void CCustomerDlg::ReSize()  
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

		if (IDC_COMBO_C == woc)
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

void CCustomerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		ReSize();  
	}
	// TODO: 在此处添加消息处理程序代码
}


void CCustomerDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CCustomerDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnCancel();
}


void CCustomerDlg::OnBnClickedBtnReaduserinfo()
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
	buf[5] = TYPE_CARD_CUSTMER; //卡类型
	buf[6] = 0x00; //子卡类型
	
	LPSerialProtocol->Send(IC_CMD_CUSTOMER, 7, buf);
	Sleep(300);
	BYTE pDatas[80] = {0};
	int nRet = LPSerialProtocol->ReadData(pDatas, 80);
	if(nRet <= 60)
	{
		Sleep(300);
		nRet = LPSerialProtocol->ReadData(pDatas, 80);
	}


	if(nRet < 60)
	{
		LPSerialProtocol->Send(IC_CMD_CUSTOMER, 7, buf);
		Sleep(300);
		BYTE pDatas[80] = {0};
		int nRet = LPSerialProtocol->ReadData(pDatas, 80);
		if(nRet <= 0)
		{
			Sleep(300);
			nRet = LPSerialProtocol->ReadData(pDatas, 80);
		}
	}

	if(nRet > sizeof(T_FRAME_RET_HEAD))
	{
		LPFRAME_RET_HEAD lpFrameHead = (LPFRAME_RET_HEAD) pDatas;
		LPT_UserCardData pUserCardData = (LPT_UserCardData)(pDatas + sizeof(T_FRAME_RET_HEAD) + 2);
		if(lpFrameHead->chPacketType != IC_CMD_CUSTOMER)
		{
			AfxMessageBox("读取错误,请重新读取！");
			return;
		}
		if( pUserCardData->dataType[0] == TYPE_ADMIN)
		{
			AfxMessageBox("该卡片为管理员卡片，请在管理员卡设置处读取修改！");
			return;
		}
		if( pUserCardData->dataType[0] == TYPE_FUN)
		{
			AfxMessageBox("该卡片为功能卡，请在功能卡设置处读取修改！");
			return;
		}
		if(pUserCardData->dataType[0] == TYPE_USER)
		{
			CCustermerInfoDlg dlg(this);
			long nID = (pUserCardData->btCardNo[0]<<16) + (pUserCardData->btCardNo[1]<<8) + pUserCardData->btCardNo[2];

			long lStatus = ADD_TYPE;
			CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(nID, lStatus);

			dlg.SetPara(lStatus, nID);
			CYonghuset customerData;
			customerData.copy(*pYonghuset);
			//customerData.m_sycs = (pUserCardData->btCounts[0]<<8) + pUserCardData->btCounts[1];
			int iYear, iMonth, iDay, iHour, iMinute;
			//起始时间
			iYear = (pUserCardData->btStartYear / 16 * 10) + (pUserCardData->btStartYear % 16) + 2000;
			iMonth = pUserCardData->btStartMonth  / 16 * 10 + pUserCardData->btStartMonth % 16;
			iDay = pUserCardData->btStartDay / 16 * 10 + pUserCardData->btStartDay % 16;
			iHour = pUserCardData->btStartHour / 16 * 10 + pUserCardData->btStartHour % 16;
			iMinute = pUserCardData->btStartMinute / 16 * 10 + pUserCardData->btStartMinute % 16;

			customerData.m_qssj.Format("%4d-%02d-%02d", iYear, iMonth, iDay);

			//截至时间
			iYear = pUserCardData->btEndYear / 16 * 10 + pUserCardData->btEndYear % 16 + 2000;
			iMonth = pUserCardData->btEndMonth / 16 * 10 + pUserCardData->btEndMonth % 16;
			iDay = pUserCardData->btEndDay / 16 * 10 + pUserCardData->btEndDay % 16;
			iHour = pUserCardData->btEndHour / 16 * 10 + pUserCardData->btEndHour % 16;
			iMinute = pUserCardData->btEndMinute / 16 * 10 + pUserCardData->btEndMinute % 16;
			customerData.m_jzsj.Format("%4d-%02d-%02d", iYear, iMonth, iDay);

			//customerData.m_xzms = pUserCardData->limitType - 1;
			//customerData.m_kydt1 = pUserCardData->btElevator_1;
			//customerData.m_kydt2 = pUserCardData->btElevator_2;
			//customerData.m_kydt3 = pUserCardData->btElevator_3;
			//customerData.m_kydt4 = pUserCardData->btElevator_4;

			dlg.m_bReadCardFlag = TRUE;
			dlg.SetCustomerData(customerData);

			CString szInfo, szTemp;
			szInfo.Format("卡片类型：业主卡\r\n");

			szTemp.Format("业主卡卡号：%d\r\n", (pUserCardData->btCardNo[0] << 16) 
				+ (pUserCardData->btCardNo[1] << 8) 
				+ pUserCardData->btCardNo[2] );
			szInfo += szTemp;

			szTemp.Format("业主名称：%s\r\n", customerData.m_yzmc);
			szInfo += szTemp;

			szTemp.Format("手机号码：%s\r\n", customerData.m_sjhm);
			szInfo += szTemp;

			szTemp.Format("房间编号：%d\r\n", customerData.m_fjbh);
			szInfo += szTemp;

			if(pUserCardData->limitType == 1)
			{
				szTemp.Format("限制模式：次数限制\r\n");
				szInfo += szTemp;
				szTemp.Format("   剩余次数：%d\r\n", 
					(pUserCardData->btCounts[0] << 8) + pUserCardData->btCounts[1]);
				szInfo += szTemp;
			}
			else if(pUserCardData->limitType == 2)
			{
				szTemp.Format("限制模式：时间限制\r\n");
				szInfo += szTemp;
				szTemp.Format("   起始时间：%s \r\n     截至时间: %s\r\n", 
					customerData.m_qssj, 
					customerData.m_jzsj);
				szInfo += szTemp;
			}
			else if(pUserCardData->limitType == 3)
			{
				szTemp.Format("限制模式：两者都限制\r\n");
				szInfo += szTemp;
				szTemp.Format("   剩余次数：%d\r\n", 
					(pUserCardData->btCounts[0] << 8) + pUserCardData->btCounts[1]);
				szInfo += szTemp;
				szTemp.Format("   起始时间：%s \r\n   截至时间: %s\r\n", 
					customerData.m_qssj, 
					customerData.m_jzsj);
				szInfo += szTemp;
			}

			if(pUserCardData->btElevator_1 > 0  
				&& pUserCardData->btElevator_1 < 255)
			{

				CSuoset* p = LPDBManage->GetElevatorByID(pUserCardData->btElevator_1);
				//szTemp.Format("可用电梯1：%d\r\n", pUserCardData->btElevator_1);

				szTemp.Format("可用电梯1：%s\r\n", p->m_dtmc);
				szInfo += szTemp;

				szTemp.Empty();
				for (int i=0; i<8; i++)
				{
					CString szFloor = 
						ParseElevatorFloor(pUserCardData->btFloor_1[i], i, p->m_qslc);
					if(!szFloor.IsEmpty())
					{
						szTemp += szFloor;
					}
				}
				szTemp += "\r\n";
				szInfo += szTemp;
			}

			if(pUserCardData->btElevator_2 > 0
				&& pUserCardData->btElevator_2 < 255)
			{
				CSuoset* p = LPDBManage->GetElevatorByID(pUserCardData->btElevator_2);
				
				szTemp.Format("可用电梯2：%s\r\n", p->m_dtmc);
				szInfo += szTemp;

				szTemp.Empty();
				for (int i=0; i<8; i++)
				{
					CString szFloor = 
						ParseElevatorFloor(pUserCardData->btFloor_2[i], i, p->m_qslc);
					if(!szFloor.IsEmpty())
					{
						szTemp += szFloor;
					}
				}
				szTemp += "\r\n";
				szInfo += szTemp;
			}
			if(pUserCardData->btElevator_3 > 0
				&& pUserCardData->btElevator_3 < 255)
			{

				CSuoset* p = LPDBManage->GetElevatorByID(pUserCardData->btElevator_3);
				
				szTemp.Format("可用电梯3：%s\r\n", p->m_dtmc);
				szInfo += szTemp;

				szTemp.Empty();
				for (int i=0; i<8; i++)
				{
					CString szFloor = ParseElevatorFloor(pUserCardData->btFloor_3[i], i, p->m_qslc);
					if(!szFloor.IsEmpty())
					{
						szTemp += szFloor;
					}
				}
				szTemp += "\r\n";
				szInfo += szTemp;

			}
			if(pUserCardData->btElevator_4 > 0
				&& pUserCardData->btElevator_4 < 255)
			{

				CSuoset* p = LPDBManage->GetElevatorByID(pUserCardData->btElevator_4);

				szTemp.Format("可用电梯4：%s\r\n", p->m_dtmc);
				szInfo += szTemp;

				szTemp.Empty();
				for (int i=0; i<8; i++)
				{
					CString szFloor = ParseElevatorFloor(pUserCardData->btFloor_4[i], i, p->m_qslc);
					if(!szFloor.IsEmpty())
					{
						szTemp += szFloor;
					}
				}
				szTemp += "\r\n";
				szInfo += szTemp;
			}
			dlg.m_strOutput = szInfo;
			//dlg.m_strOutput = dlg.GetCardInfo(NULL);

			dlg.DoModal();
		}
	}
	else
		AfxMessageBox("获取用户卡信息失败！");
}
CString CCustomerDlg::GetCardInfo(LPT_UserCardData pUserCardData, CYonghuset& customerData)
{
	CString szInfo, szTemp;
	szInfo.Format("卡片类型：业主卡\r\n");

	szTemp.Format("业主卡卡号：%d\r\n", pUserCardData->btCardNo);
	szInfo += szTemp;

	szTemp.Format("业主名称：%s\r\n", customerData.m_yzmc);
	szInfo += szTemp;

	szTemp.Format("手机号码：%s\r\n", customerData.m_sjhm);
	szInfo += szTemp;

	szTemp.Format("房间编号：%d\r\n", customerData.m_fjbh);
	szInfo += szTemp;

	if(pUserCardData->limitType == 1)
	{
		szTemp.Format("限制模式：次数限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用次数：%d\r\n", customerData.m_sycs);
		szInfo += szTemp;
	}
	else if(pUserCardData->limitType == 2)
	{
		szTemp.Format("限制模式：时间限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   起始时间：%s \r\n     截至时间: %s\r\n", 
			customerData.m_qssj, 
			customerData.m_jzsj);
		szInfo += szTemp;
	}
	else if(pUserCardData->limitType == 3)
	{
		szTemp.Format("限制模式：两者都限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用次数：%d\r\n", customerData.m_sycs);
		szInfo += szTemp;
		szTemp.Format("   起始时间：%s \r\n   截至时间: %s\r\n", 
			customerData.m_qssj, 
			customerData.m_jzsj);
		szInfo += szTemp;
	}

	if(pUserCardData->btElevator_1 > 0)
	{
		CString szInfo;
		szTemp.Format("可用电梯1：%d\r\n", pUserCardData->btElevator_1);
		szInfo += szTemp;

		LPSerialProtocol->stringToBytes(szInfo, pUserCardData->btFloor_1);
		if(!szInfo.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", szInfo);
			szInfo += szTemp;
		}
	}

	if(pUserCardData->btElevator_2 > 0)
	{
		CString szInfo;
		szTemp.Format("可用电梯2：%d\r\n", pUserCardData->btElevator_2);
		szInfo += szTemp;

		LPSerialProtocol->stringToBytes(szInfo, pUserCardData->btFloor_2);
		if(!szInfo.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", szInfo);
			szInfo += szTemp;
		}
	}
	if(pUserCardData->btElevator_3 > 0)
	{
		CString szInfo;
		szTemp.Format("可用电梯3：%d\r\n", pUserCardData->btElevator_3);
		szInfo += szTemp;

		LPSerialProtocol->stringToBytes(szInfo, pUserCardData->btFloor_3);
		if(!szInfo.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", szInfo);
			szInfo += szTemp;
		}
	}
	if(pUserCardData->btElevator_4 > 0)
	{
		CString szInfo;
		szTemp.Format("可用电梯4：%d\r\n", pUserCardData->btElevator_4);
		szInfo += szTemp;

		LPSerialProtocol->stringToBytes(szInfo, pUserCardData->btFloor_4);
		if(!szInfo.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", szInfo);
			szInfo += szTemp;
		}
	}
	return szInfo;
}
