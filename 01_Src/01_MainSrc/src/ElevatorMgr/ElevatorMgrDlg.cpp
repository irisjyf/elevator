// ElevatorMgrDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CElevatorMgrDlg 对话框
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


// CElevatorMgrDlg 消息处理程序

#define  yPos   75

BOOL CElevatorMgrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	CRect rc(0,0,0,0);
	GetClientRect(rc);
	CSize sz = CSize(rc.Width(),rc.Height()-20);

	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	
	CenterWindow();

	// 初始化工具栏
	InitToolBar();

	// 初始化TAB页
	InitTabCtrl();

	CenterWindow();
	CWnd *pWnd = GetWindow(GW_CHILD);
	while(pWnd)
	{
		pWnd->SetFont(GetFont()); 
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}
	::SetWindowPos(this->m_hWnd,HWND_BOTTOM,0,yPos,sz.cx,sz.cy+48,SWP_NOZORDER);

	SetTimer(1,1000,NULL);//启动定时器1,定时时间是1秒

	CenterWindow();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CElevatorMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CElevatorMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//   初始化工具栏
BOOL  CElevatorMgrDlg::InitToolBar()
{
	m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP );
	m_ToolBar.LoadToolBar(IDR_TOOLBAR1); //加载工具栏资源
	m_ToolBar.ShowWindow(SW_SHOW);


	//创建图像列表
	m_ImageList.Create(66,66,ILC_COLOR24|ILC_MASK,1,1);
	//向图像列表中添加图标
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));

	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
	{
		m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON8));
	}
	
	UINT array[TAB_NUM];
	for(int i= 0;i< TAB_NUM;i++)        //初始化工具栏ID
	{
// 		if(i==1|| i==5)
// 			array[i]= ID_SEPARATOR; //第3、6个按钮为分隔条
/*		else*/
			array[i]= i+143;
	}

	m_ToolBar.SetButtons(array,TAB_NUM);
	//关联图像列表
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);

	m_ToolBar.SetSizes(CSize(73,73),CSize(66,67));//设置按钮和图标的大小

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

//   初始化TAB页面
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

		if (m_pTabCtrl[i].m_iIcon == IDI_ICON1 )      //系统设置
		{
			pDlg = new CSetAuthDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_AUTH,"       用户管理      ",sz);
			
			pDlg = new CSetCommDlg(LPSerialProtocol);
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_COMM,"      通讯参数      ",sz);

			if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
			{
				pDlg = new CSetDBDlg;
				CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_SET_DB,"       高级配置      ",sz);
			}
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON2 ) //业主卡
		{
			pDlg = new CCustomerDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_CUSTOMER,"      业主资料管理      ",sz);;
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON3 ) // 管理卡 
		{
			pDlg = new CManagerDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_MANAGER,"      管理卡管理      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON4 ) //功能卡
		{
			pDlg = new CFuncDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_FUNC,"      功能卡管理      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON5 ) //电梯管理
		{
			pDlg = new CElevatorDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_ELEVATOR,"      电梯管理      ",sz);;
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON6 ) //帮助
		{
			pDlg = new CHelpDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_HELP,"      帮助信息      ",sz);
		}
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON7 ) //高级功能
		{
			;
		}
#ifndef MGR_USER
		else if (m_pTabCtrl[i].m_iIcon == IDI_ICON8 ) //高级功能
		{
			pDlg = new CMakeCardDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_MAKECARD,"      制卡管理      ",sz);

			pDlg = new CProxyDlg;
			CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_PROXY,"      物业管理      ",sz);

			//pDlg = new COtheCardDlg;
			//CreateDlg(&m_pTabCtrl[i],pDlg,IDD_DIALOG_ADANC,"      其他功能      ",sz);
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
	//if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
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
	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
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

//系统设置 
void CElevatorMgrDlg::OnBnClkSysSet()
{
	SetShowState(0);
}

//业主卡
void CElevatorMgrDlg::OnBnClkCustomer()
{
	SetShowState(1);
}

//管理卡
void CElevatorMgrDlg::OnBnClkManager()
{
	SetShowState(2);
}

//功能卡
void CElevatorMgrDlg::OnBnClkFunction()
{
	SetShowState(3);
}

//电梯管理
void CElevatorMgrDlg::OnBnClkElevator()
{
	SetShowState(4);
}

//帮助 
void CElevatorMgrDlg::OnBnClkHelp()
{
	SetShowState(5);
}

//退出 
void CElevatorMgrDlg::OnBnClkExit()
{
	SetShowState(6);
	CDialog::OnCancel();
}

void CElevatorMgrDlg::OnBnClkAdvanced()
{
	if ( 0 != LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
	{
		return;
	}

	SetShowState(7);
}


void CElevatorMgrDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	AfxMessageBox("请及时备份数据");
	CDialog::OnClose();
}

void CElevatorMgrDlg::OnBnClickedBtnComdlg()
{
	// TODO: 在此添加控件通知处理程序代码
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
//	if (pDatas[11]  == 1)//业主卡
//	{
//		str="开类型：业主卡\r\n\r\n";
//		str+="卡号：";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+=temp+"\r\n\r\n";
//		str+="房间号：";
//		temp.Format("%d",pDatas[16]*256+pDatas[17]);
//		str+=temp+"\r\n\r\n";
//		str+="限制模式：";
//		if(pDatas[18]==1){
//			temp.Format("%d",pDatas[30]*256+pDatas[31]);
//			str+="次数限制,还剩余"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[18]==2){ temp.Format("%d-%d-%d至%d-%d-%d",
//			pDatas[20]/16*10+pDatas[20]%16,
//			pDatas[21]/16*10+pDatas[21]%16,
//			pDatas[22]/16*10+pDatas[22]%16,
//			pDatas[25]/16*10+pDatas[25]%16,
//			pDatas[26]/16*10+pDatas[26]%16,
//			pDatas[27]/16*10+pDatas[27]%16);
//		str+="日期限制，有效期为"+temp;
//		str+="\r\n\r\n";
//		}
//		str+="";
//
//		CCustermerInfoDlg dlg;
//		dlg.m_strOutput  = str;
//		dlg.SetPara(MOD_TYPE,iCardNo);
//		dlg.DoModal();
//	}
//	else if (pDatas[11] == 2) //管理员卡
//	{
//		str="开类型：管理员卡\r\n\r\n";
//		str+="卡号：";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+=temp+"\r\n\r\n";
//
//		str+="限制模式：";
//		if(pDatas[18]==1){
//			temp.Format("%d",pDatas[30]*256+pDatas[31]);
//			str+="次数限制,还剩余"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[18]==2){temp.Format("%d-%d-%d至%d-%d-%d",
//			pDatas[20]/16*10+pDatas[20]%16,
//			pDatas[21]/16*10+pDatas[21]%16,
//			pDatas[22]/16*10+pDatas[22]%16,
//			pDatas[25]/16*10+pDatas[25]%16,
//			pDatas[26]/16*10+pDatas[26]%16,
//			pDatas[27]/16*10+pDatas[27]%16);
//		str+="日期限制，有效期为"+temp;
//		str+="\r\n\r\n";
//		}
//		if(pDatas[18]==0){
//
//			str+="不限制";
//			str+="\r\n\r\n";
//		}
//		str+="";
//
//		CManagerInfoDlg dlg;
//		dlg.m_strOutput  = str;
//		dlg.SetPara(MOD_TYPE,iCardNo);
//		dlg.DoModal();
//	}
//	else if (pDatas[11] == 3) //功能卡
//	{
//		str="开类型：功能卡\r\n\r\n";
//
//		str+="卡号：";
//		temp.Format("%d",pDatas[13]*65536+pDatas[14]*256+pDatas[15]);
//		iCardNo = atoi(temp);
//		str+="\r\n\r\n";
//
//		if(pDatas[12]==1){
//
//			str+="启禁卡";
//			str+="\r\n\r\n";
//
//			for(int i=0;i<8;i++)
//			{
//				temp.Format("%d",pDatas[32+i*4]*65536+pDatas[33+i*4]*256+pDatas[34+i*4]);
//				str+="卡号："+temp;
//				if(pDatas[35+i*4]==1){
//					str+="禁用";
//				}
//				else
//					str+="启用";
//				str+="\r\n\r\n";
//			}
//		}
//		if(pDatas[12]==2){
//
//			str+="校时卡"+temp;
//			str+="\r\n\r\n";
//		}
//		if(pDatas[12]==3){
//
//			str+="开关卡";
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
//		//AfxMessageBox("读卡失败, 卡类型错误");
//	}
//	return 0;
//}


void CElevatorMgrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDialog::DestroyWindow();
}


void CElevatorMgrDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

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
		Rect.SetRect(TLPoint,BRPoint);    
		GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
		hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
	}  
	
	//int  iNum = TAB_NUM_USER;  //7
	int  iNum = TAB_NUM;
	if ( 0 == LPDBManage->m_USERINFO.m_strAuth.CompareNoCase("管理员"))
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