
// AgentMgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AgentMgr.h"
#include "AgentMgrDlg.h"
#include "afxdialogex.h"
#include "DlgAgentInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAgentMgrDlg 对话框




CAgentMgrDlg::CAgentMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAgentMgrDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAgentMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AGENT, m_listAgentCtrl);
}

BEGIN_MESSAGE_MAP(CAgentMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_ADD, &CAgentMgrDlg::OnBnClickedAdd)
END_MESSAGE_MAP()

const CString szColumnName[] = {"编号","姓名","联系电话","代理权限","代理编码"};
const CString szAuthority[] = {"超级权限","管理员","一般权限"};
// CAgentMgrDlg 消息处理程序

BOOL CAgentMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	// TODO: 在此添加额外的初始化代码
	LONG lStyle;
	lStyle = GetWindowLong(m_listAgentCtrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listAgentCtrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listAgentCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listAgentCtrl.SetExtendedStyle(dwStyle); //设置扩展风格

	m_listAgentCtrl.InsertColumn(0,"编号",LVCFMT_LEFT,50); //50为列宽
	m_listAgentCtrl.InsertColumn(1,"姓名",LVCFMT_LEFT,100); //50为列宽
	m_listAgentCtrl.InsertColumn(2,"联系电话",LVCFMT_LEFT,150); //50为列宽
	m_listAgentCtrl.InsertColumn(3,"代理权限",LVCFMT_LEFT,150); //50为列宽
	m_listAgentCtrl.InsertColumn(4,"代理编码",LVCFMT_LEFT,350); //50为列宽

	Load();
	CString szIndex;
	for (int i=0; i<m_Agents.GetSize(); i++)
	{
		T_Agent* ptAgent = m_Agents.GetAt(i);
		szIndex.Format("%d", ptAgent->iIndex);
		m_listAgentCtrl.InsertItem(i, szIndex);
		m_listAgentCtrl.SetItemText(i,1,ptAgent->szName);
		m_listAgentCtrl.SetItemText(i,2,ptAgent->szTel);
		m_listAgentCtrl.SetItemText(i,3,szAuthority[ptAgent->dwAuthority]);
		m_listAgentCtrl.SetItemText(i,4,ptAgent->szAgentCode);
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAgentMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAgentMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAgentMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAgentMgrDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgAgentInfo dlg;
	dlg.m_AgentID = m_Agents.GetSize();
	if (dlg.DoModal() == IDOK)
	{
		T_Agent* ptAgent = new T_Agent;
		ptAgent->iIndex = dlg.m_AgentID;
		ptAgent->szName = dlg.m_AgentName;
		ptAgent->szTel = dlg.m_AgentTel;
		ptAgent->dwAuthority = dlg.m_iAuthority;
		ptAgent->szAgentCode = dlg.m_szCode;

		m_Agents.Add(ptAgent);

		int nCount = m_listAgentCtrl.GetItemCount();
		CString szIndex;
		szIndex.Format("%d", ptAgent->iIndex);
		m_listAgentCtrl.InsertItem(nCount, szIndex);
		m_listAgentCtrl.SetItemText(nCount,1,ptAgent->szName);
		m_listAgentCtrl.SetItemText(nCount,2,ptAgent->szTel);
		m_listAgentCtrl.SetItemText(nCount,3,szAuthority[ptAgent->dwAuthority]);
		m_listAgentCtrl.SetItemText(nCount,4,ptAgent->szAgentCode);
	}
}

void CAgentMgrDlg::Save()
{
	CFile file;
	CString FileName="data.bat";
	try
	{
		if(!file.Open(FileName,CFile::modeCreate | CFile::modeWrite))
		{
			return;
		}
		CArchive ar(&file,CArchive::store);
		int iVesion = 0x000001;
		int iCount = m_Agents.GetSize();
		ar << iVesion;
		ar << iCount;
		for (int i=0; i<iCount; i++)
		{
			T_Agent* p = m_Agents.GetAt(i);
			ar << p->iIndex;
			ar << p->szName;
			ar << p->szTel;
			ar << p->dwAuthority;
			ar << p->szAgentCode;
		}
	}
	catch(...)
	{
		MessageBox("保存文件失败","错误", MB_OK);
		return;
	}
}
void CAgentMgrDlg::Load()
{
	CFile file;
	CString FileName="data.bat";
	try
	{
		if(!file.Open(FileName,CFile::modeReadWrite))
		{
			return;
		}
		CArchive ar(&file,CArchive::load);
		int iVesion = 0x000001;
		int iCount = 0;
		ar >> iVesion;
		ar >> iCount;
		for (int i=0; i<iCount; i++)
		{
			T_Agent* p = new T_Agent;
			ar >> p->iIndex;
			ar >> p->szName;
			ar >> p->szTel;
			ar >> p->dwAuthority;
			ar >> p->szAgentCode;
			m_Agents.Add(p);
		}
	}
	catch(...)
	{
		MessageBox("保存文件失败","错误", MB_OK);
		return;
	}
}

void CAgentMgrDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	Save();

	CDialogEx::OnOK();
}


void CAgentMgrDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	Save();
	CDialogEx::OnCancel();
}
