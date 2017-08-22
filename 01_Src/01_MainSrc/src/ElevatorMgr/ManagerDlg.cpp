// ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ManagerDlg.h"
#include "afxdialogex.h"
#include "ManagerInfoDlg.h"
#include "QurryDlg.h"
#include "Comm/quset.h"

// CManagerDlg �Ի���

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


// CManagerDlg ��Ϣ�������


void CManagerDlg::OnBnClickedManagerAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CManagerInfoDlg dlg;
	dlg.SetPara(ADD_TYPE,LPDBManage->GetManagerID());
	dlg.DoModal();
	OnBnClickedBtnRefresh();
}

void CManagerDlg::OnBnClickedManagerMod()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_ManagerList.InsertColumn(0,"NO.");
	m_ManagerList.InsertColumn(1,"����");
	m_ManagerList.InsertColumn(2,"����Ա����");
	m_ManagerList.InsertColumn(3,"�ɳ˵���");
	m_ManagerList.InsertColumn(4,"SN");
	m_ManagerList.InsertColumn(5,"״̬");
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
	// �쳣: OCX ����ҳӦ���� FALSE
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
			m_ManagerList.SetItemText(i,5,"����");
		else if(pQuset->m_status == 3)
			m_ManagerList.SetItemText(i,5,"����");
		else
			m_ManagerList.SetItemText(i,5,"����");
		i++;  
	}

	return TRUE;
}


void CManagerDlg::OnNMDblclkFliedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	OnBnClickedManagerMod();
}


void CManagerDlg::OnBnClickedManagerDel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int iIndex = m_ManagerList.GetNextItem(-1,LVNI_SELECTED);
	//if(iIndex < 0)  return;

	//CString  strID = m_ManagerList.GetItemText(iIndex,1);
	//long lID  = atoi(strID);

	//if(MessageBox("ȷ��ɾ����ѡ������","��ʾ",MB_OKCANCEL)==IDOK)
	//{
	//	long lStatus = ADD_TYPE;
	//	Cquset *pQuset  = LPDBManage->GetManagerByID(lID, lStatus);
	//	if (LPDBManage->OperManager(pQuset,DEL_TYPE))
	//	{
	//		OnBnClickedBtnRefresh();
	//	}
	//}


	POSITION pos = m_ManagerList.GetFirstSelectedItemPosition();

	if(pos && MessageBox("ȷ��ɾ����ѡ������","��ʾ",MB_OKCANCEL)==IDOK)
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CArray<Cquset*,Cquset*> arr;
	LPDBManage->GetManagerList(arr);
	ShowTable(arr);
}


void CManagerDlg::OnBnClickedBtnManagerQurry()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CQurryDlg dlg;
	dlg.m_arrFiled.Add("����");
	dlg.m_arrFiled.Add("����Ա����");
	dlg.m_arrFiled.Add("�ֻ�����");

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
	// TODO: �ڴ˴������Ϣ����������
}

void CManagerDlg::ReSize()  
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
	// TODO: �ڴ����ר�ô����/����û���
	return;
	CDialogEx::OnOK();
}


void CManagerDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	return;
	CDialogEx::OnCancel();
}


void CManagerDlg::OnBnClickedBtnReadCard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	unsigned char buf[80];
	memset(buf, 0, sizeof(buf));
	/////////////////////
	buf[0] = READ;  //д������
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	buf[4] = 0xff; //����
	buf[5] = TYPE_CARD_MGR; //������
	buf[6] = 0x00; //�ӿ�����

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
			AfxMessageBox("��ȡ����,�����¶�ȡ��");
			return;
		}
		if( pMgrCardData->dataType[0] == TYPE_USER)
		{
			AfxMessageBox("�ÿ�ƬΪҵ����������ҵ�������ô���ȡ�޸ģ�");
			return;
		}
		if( pMgrCardData->dataType[0] == TYPE_FUN)
		{
			AfxMessageBox("�ÿ�ƬΪ���ܿ������ڹ��ܿ����ô���ȡ�޸ģ�");
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
			//��ʼʱ��
			iYear = pMgrCardData->btStartYear / 16 * 10 + pMgrCardData->btStartYear % 16 + 2000;
			iMonth = pMgrCardData->btStartMonth;
			iDay = pMgrCardData->btStartDay;
			iHour = pMgrCardData->btStartHour;
			iMinute = pMgrCardData->btStartMinute;

			QusetData.m_qssj.Format("%4d-%02d-%02d %02d:%02d:00", iYear, iMonth, iDay, iHour, iMinute);

			//����ʱ��
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

			dlg.SetMgrData(QusetData);//�޸�
			
			dlg.m_bReadCardFlag = TRUE;
			dlg.m_strOutput = dlg.GetCardInfo(NULL);

			dlg.DoModal();
			return;
		}
	}
	AfxMessageBox("��ȡ����Ϣʧ�ܣ�");
}
