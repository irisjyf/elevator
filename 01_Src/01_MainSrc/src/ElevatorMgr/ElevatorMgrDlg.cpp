// ElevatorMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ElevatorMgrDlg.h"

//////////////////////////////////////////////////////////////////////////
#include "BlackListDlg.h"
#include "CustomerDlg.h"
#include "SetDBDlg.h"
#include "SetCommDlg.h"
#include "ManagerDlg.h"
#include "FuncDlg.h"
#include "ElevatorDlg.h"
#include "HelpDlg.h"
#include "SetAuthDlg.h"
#include "DlgProtocolDemo.h"
#include "CustermerInfoDlg.h"
#include "ManagerInfoDlg.h"
#include "FuncInfoDlg.h"
#include "MakeCardDlg.h"
#include "ProxyDlg.h"

//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CElevatorMgrDlg �Ի���
CElevatorMgrDlg::CElevatorMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CElevatorMgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CElevatorMgrDlg::~CElevatorMgrDlg()
{
	for (int i= 0; i < m_arrWnd.GetSize(); i++ )
	{
		CWnd *pWnd = m_arrWnd.GetAt(i);

		if (pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
	}
}

void CElevatorMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CElevatorMgrDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDI_ICON1,CElevatorMgrDlg::OnBnClkSysSet)
	ON_COMMAND(IDI_ICON2,CElevatorMgrDlg::OnBnClkCustomer)
	ON_COMMAND(IDI_ICON3,&CElevatorMgrDlg::OnBnClkManager)
	ON_COMMAND(IDI_ICON4,&CElevatorMgrDlg::OnBnClkFunction)
	ON_COMMAND(IDI_ICON5,&CElevatorMgrDlg::OnBnClkElevator)
	ON_COMMAND(IDI_ICON6,&CElevatorMgrDlg::OnBnClkHelp)
	ON_COMMAND(IDI_ICON7,&CElevatorMgrDlg::OnBnClkExit)
	ON_COMMAND(IDI_ICON8,&CElevatorMgrDlg::OnBnClkAdvanced)
	ON_BN_CLICKED(IDC_BTN_COMDlg, &CElevatorMgrDlg::OnBnClickedBtnComdlg)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CElevatorMgrDlg ��Ϣ�������

#define  yPos   75

BOOL CElevatorMgrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	CSize sz = CSize(rc.Width(),rc.Height()-20);

	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	
	CenterWindow();

	// ��ʼ��������
	InitToolBar();

	// ��ʼ��TABҳ
	InitTabCtrl();

	CenterWindow();
	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd)
	{
		pWnd->SetFont(GetFont()); 
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,yPos,sz.cx,sz.cy+48,SWP_NOZORDER);

	SetTimer(1,1000,NULL);//������ʱ��1,��ʱʱ����1��

	CenterWindow();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CElevatorMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CElevatorMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CElevatorMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//   ��ʼ��������
BOOL  CElevatorMgrDlg::InitToolBar()
{
	m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP );
	m_ToolBar.LoadToolBar(IDR_TOOLBAR1); //���ع�������Դ
	m_ToolBar.ShowWindow(SW_SHOW);


	//����ͼ���б�
	m_ImageList.Create(66,66,ILC_COLOR24|ILC_MASK,1,1);
	//��ͼ���б������ͼ��
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));

	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
	{
		m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));
	}
	
	UINT array[TAB_NUM];
	for(int i= 0;i< TAB_NUM;i++)        //��ʼ��������ID
	{
// 		if(i==1|| i==5)
// 			array[i]= ID_SEPARATOR; //��3��6����ťΪ�ָ���
/*		else*/
			array[i]= i+143;
	}

	m_ToolBar.SetButtons(array,TAB_NUM);
	//����ͼ���б�
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);

	m_ToolBar.SetSizes(CSize(73,73),CSize(66,67));//���ð�ť��ͼ��Ĵ�С

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	return TRUE;
}

BOOL CElevatorMgrDlg::CreateDlg(CXTabCtrl *pTabCtrl,CDialogEx *pDlg,UINT iRes,CString strTitle,CSize sz)
{
	ASSERT(pDlg);

	pTabCtrl->ModifyStyleEx( TCS_HOTTRACK,0,SWP_DRAWFRAME);

	pDlg->Create(iRes,pTabCtrl);
	pDlg->MoveWindow(0,yPos,sz.cx,sz.cy);
	pDlg->CenterWindow();

	char    *szName = strTitle.GetBuffer(strTitle.GetLength() + 1);
	pTabCtrl->AddTab(pDlg,szName,0);
	m_arrWnd.Add(pDlg);

	m_pTabCtrl->MoveWindow(0,yPos,sz.cx+5,sz.cy +20);
	pTabCtrl->ShowWindow(FALSE);

	return TRUE;
}

//   ��ʼ��TABҳ��
BOOL  CElevatorMgrDlg::InitTabCtrl()
{	
	/////////////////////////////////////////////

	CDialogEx  *pDlg  = NULL;
	CRect rc(0,0,0,0);
	GetClientRect(rc);
	CSize sz = CSize(rc.Width(),rc.Height()-20);

	for (int i = 0; i < TAB_NUM ; i++)
	{	
		m_pTabCtrl[i].m_iIcon =  i+143;
		m_pTabCtrl[i].Create(TCS_FOCUSNEVER|WS_VISIBLE|TCS_OWNERDRAWFIXED ,rc,this,IDD_TESTSKIN_DIALOG);
		m_pTabCtrl[i].ModifyStyleEx( TCS_HOTTRACK,0,SWP_DRAWFRAME);

		if (m_pTabCtrl[i].m_iIcon == IDI_ICON1 )      //ϵͳ����
		{
			pDlg = new CSetAuthDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_AUTH,"       �û�����      ",sz);
			
			pDlg = new CSetCommDlg(LPSerialProtocol);
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_COMM,"      ͨѶ����      ",sz);

			if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
			{
				pDlg = new CSetDBDlg;
				CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_DB,"       �߼�����      ",sz);
			}
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON2 ) //ҵ����
		{
			pDlg = new CCustomerDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_CUSTOMER,"      ҵ�����Ϲ���      ",sz);;
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON3 ) // ���� 
		{
			pDlg = new CManagerDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_MANAGER,"      ��������      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON4 ) //���ܿ�
		{
			pDlg = new CFuncDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_FUNC,"      ���ܿ�����      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON5 ) //���ݹ���
		{
			pDlg = new CElevatorDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_ELEVATOR,"      ���ݹ���      ",sz);;
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON6 ) //����
		{
			pDlg = new CHelpDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_HELP,"      ������Ϣ      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON7 ) //�߼�����
		{
			;
		}
#ifndef MGR_USER
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON8 ) //�߼�����
		{
			pDlg = new CMakeCardDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_MAKECARD,"      �ƿ�����      ",sz);

			pDlg = new CProxyDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_PROXY,"      ��ҵ����      ",sz);

			//pDlg = new COtheCardDlg;
			//CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_ADANC,"      ��������      ",sz);
		}
#endif
		m_pTabCtrl[i].MoveWindow(0,yPos,sz.cx+5,sz.cy +20);
	}

	SetShowState(1);

	return TRUE;
}

BOOL CElevatorMgrDlg::SetShowState(UINT uID)
{
	CToolBar *pBar=&m_ToolBar;
	UINT nStyle = pBar->GetButtonStyle(uID);
	nStyle |=TBBS_CHECKED;/*pBar->SetButtonStyle(uID, nStyle);*/
	pBar->SetButtonStyle(uID, nStyle);

	//int  iNum = TAB_NUM_USER;  //7
	//int  iNum = TAB_NUM;
	//if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
	//{
	//	iNum = TAB_NUM;
	//}

	//for (int i = 0; i < TAB_NUM ; i++)
	//{
	//	if (i == uID)
	//	{
	//		m_pTabCtrl[i].ShowWindow(TRUE);	
	//	}
	//	else
	//	{
	//	    m_pTabCtrl[i].ShowWindow(FALSE);
	//		pBar->SetButtonStyle(i, 0);
	//	}
	//}

	int  iNum = TAB_NUM;
	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
	{
		iNum = TAB_NUM;
	}

	for (int i = 0; i < TAB_NUM ; i++)
	{
		if (i == uID)
		{
			m_pTabCtrl[i].ShowWindow(TRUE);	
		}
		else
		{
			m_pTabCtrl[i].ShowWindow(FALSE);
			pBar->SetButtonStyle(i, 0);
		}
	}
	Invalidate(TRUE);

	return TRUE;
}

//ϵͳ���� 
void CElevatorMgrDlg::OnBnClkSysSet()
{
	SetShowState(0);
}

//ҵ����
void CElevatorMgrDlg::OnBnClkCustomer()
{
	SetShowState(1);
}

//����
void CElevatorMgrDlg::OnBnClkManager()
{
	SetShowState(2);
}

//���ܿ�
void CElevatorMgrDlg::OnBnClkFunction()
{
	SetShowState(3);
}

//���ݹ���
void CElevatorMgrDlg::OnBnClkElevator()
{
	SetShowState(4);
}

//���� 
void CElevatorMgrDlg::OnBnClkHelp()
{
	SetShowState(5);
}

//�˳� 
void CElevatorMgrDlg::OnBnClkExit()
{
	SetShowState(6);
	CDialog::OnCancel();
}

void CElevatorMgrDlg::OnBnClkAdvanced()
{
	if ( 0 != LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
	{
		return;
	}

	SetShowState(7);
}


void CElevatorMgrDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	AfxMessageBox("�뼰ʱ��������");
	CDialog::OnClose();
}

void CElevatorMgrDlg::OnBnClickedBtnComdlg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgProtocolDemo dlg;
	
}


//
//DWORD WINAPI CElevatorMgrDlg::FunOnDataOk(HWND hWnd, BYTE* pDatas, long lLength)
//{
//	if (lLength <= sizeof(T_FRAMEHEAD))
//		return 0;
//	memset(CElevatorMgrApp::m_cData, 0, BUFFER_SIZE);
//	if(lLength > BUFFER_SIZE)
//		lLength = BUFFER_SIZE;
//	memcpy(CElevatorMgrApp::m_cData, pDatas, lLength);
//
//	int iCardNo  = 0;
//	CString str,temp;
//	if (pDatas[11]  == 1)//ҵ����
//	{
//		str="�����ͣ�ҵ����\r\n\r\n";
//		str+="���ţ�";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+=temp+"\r\n\r\n";
//		str+="����ţ�";
//		temp.Format("%d",pDatas[16]*256+pDatas[17]);
//		str+=temp+"\r\n\r\n";
//		str+="����ģʽ��";
//		if(pDatas[18]==1){
//			temp.Format("%d",pDatas[30]*256+pDatas[31]);
//			str+="��������,��ʣ��"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[18]==2){ temp.Format("%d-%d-%d��%d-%d-%d",
//			pDatas[20]/16*10+pDatas[20]%16,
//			pDatas[21]/16*10+pDatas[21]%16,
//			pDatas[22]/16*10+pDatas[22]%16,
//			pDatas[25]/16*10+pDatas[25]%16,
//			pDatas[26]/16*10+pDatas[26]%16,
//			pDatas[27]/16*10+pDatas[27]%16);
//		str+="�������ƣ���Ч��Ϊ"+temp;
//		str+="\r\n\r\n";
//		}
//		str+="";
//
//		CCustermerInfoDlg dlg;
//		dlg.m_strOutput  = str;
//		dlg.SetPara(MOD_TYPE,iCardNo);
//		dlg.DoModal();
//	}
//	else if (pDatas[11] == 2) //����Ա��
//	{
//		str="�����ͣ�����Ա��\r\n\r\n";
//		str+="���ţ�";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+=temp+"\r\n\r\n";
//
//		str+="����ģʽ��";
//		if(pDatas[18]==1){
//			temp.Format("%d",pDatas[30]*256+pDatas[31]);
//			str+="��������,��ʣ��"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[18]==2){temp.Format("%d-%d-%d��%d-%d-%d",
//			pDatas[20]/16*10+pDatas[20]%16,
//			pDatas[21]/16*10+pDatas[21]%16,
//			pDatas[22]/16*10+pDatas[22]%16,
//			pDatas[25]/16*10+pDatas[25]%16,
//			pDatas[26]/16*10+pDatas[26]%16,
//			pDatas[27]/16*10+pDatas[27]%16);
//		str+="�������ƣ���Ч��Ϊ"+temp;
//		str+="\r\n\r\n";
//		}
//		if(pDatas[18]==0){
//
//			str+="������";
//			str+="\r\n\r\n";
//		}
//		str+="";
//
//		CManagerInfoDlg dlg;
//		dlg.m_strOutput  = str;
//		dlg.SetPara(MOD_TYPE,iCardNo);
//		dlg.DoModal();
//	}
//	else if (pDatas[11] == 3) //���ܿ�
//	{
//		str="�����ͣ����ܿ�\r\n\r\n";
//
//		str+="���ţ�";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+="\r\n\r\n";
//
//		if(pDatas[12]==1){
//
//			str+="������";
//			str+="\r\n\r\n";
//
//			for(int i=0;i<8;i++)
//			{
//				temp.Format("%d",pDatas[32+i*4]*65536+pDatas[33+i*4]*256+pDatas[34+i*4]);
//				str+="���ţ�"+temp;
//				if(pDatas[35+i*4]==1){
//					str+="����";
//				}
//				else
//					str+="����";
//				str+="\r\n\r\n";
//			}
//		}
//		if(pDatas[12]==2){
//
//			str+="Уʱ��"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[12]==3){
//
//			str+="���ؿ�";
//			str+="\r\n\r\n";
//		}
//		str+="";
//
//		CFuncInfoDlg dlg;
//		dlg.m_strOutput  = str;
//		dlg.SetPara(MOD_TYPE,iCardNo);
//		dlg.DoModal();
//	}
//	else
//	{
//		//AfxMessageBox("����ʧ��, �����ʹ���");
//	}
//	return 0;
//}


void CElevatorMgrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CWnd* pWndRed = GetDlgItem(IDC_STATIC_LINK);
	CWnd* pWndGreen = GetDlgItem(IDC_STATIC_LINK2);

	if(LPSerialProtocol->IsConnect())
	{
		pWndRed->ShowWindow(0);
		pWndGreen->ShowWindow(1);
	}
	else
	{
		pWndRed->ShowWindow(1);
		pWndGreen->ShowWindow(0);
	}

	CDialog::OnTimer(nIDEvent);
}


BOOL CElevatorMgrDlg::DestroyWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	
	return CDialog::DestroyWindow();
}


void CElevatorMgrDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		//ReSize();  
		for (int i= 0; i < m_arrWnd.GetSize(); i++ )
		{
			CWnd *pWnd = m_arrWnd.GetAt(i);
			pWnd->SendMessage(WM_SIZE,NULL,0);
		}
	}
}


void CElevatorMgrDlg::ReSize()  
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
	
	//int  iNum = TAB_NUM_USER;  //7
	int  iNum = TAB_NUM;
	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("����Ա"))
	{
		iNum = TAB_NUM;
	}
	
	for (int i = 0; i < TAB_NUM ; i++)
	{
		if (0==m_pTabCtrl[i].m_hWnd)
		{
			break;
		}

		m_pTabCtrl[i].GetWindowRect(Rect);    
		ScreenToClient(Rect);    
		OldTLPoint = Rect.TopLeft();    
		TLPoint.x = long(OldTLPoint.x*fsp[0]);    
		TLPoint.y = long(OldTLPoint.y*fsp[1]);    
		OldBRPoint = Rect.BottomRight();    
		BRPoint.x = long(OldBRPoint.x *fsp[0]);    
		BRPoint.y = long(OldBRPoint.y *fsp[1]);    
		Rect.SetRect(TLPoint,BRPoint); 
		m_pTabCtrl[i].MoveWindow(Rect,TRUE);   
		m_pTabCtrl[i].AdjustRect(FALSE,&Rect);

		//CRect rc(CPoint(Rect.left,Rect.top-22),CPoint(Rect.right,Rect.bottom));
		//m_pTabCtrl[0].MoveWindow(rc,TRUE);   
		//m_pTabCtrl[0].AdjustRect(FALSE,&rc);
	}

	for (int i= 0; i < m_arrWnd.GetSize(); i++ )
	{
		CWnd *pWnd = m_arrWnd.GetAt(i);
		pWnd->MoveWindow(0,30,Rect.Width(),Rect.Height());

	}

	m_old=Newp; 
} 