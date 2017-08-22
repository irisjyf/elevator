
// AgentMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AgentMgr.h"
#include "AgentMgrDlg.h"
#include "afxdialogex.h"
#include "DlgAgentInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAgentMgrDlg �Ի���




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

const CString szColumnName[] = {"���","����","��ϵ�绰","����Ȩ��","�������"};
const CString szAuthority[] = {"����Ȩ��","����Ա","һ��Ȩ��"};
// CAgentMgrDlg ��Ϣ�������

BOOL CAgentMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	LONG lStyle;
	lStyle = GetWindowLong(m_listAgentCtrl.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_listAgentCtrl.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listAgentCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listAgentCtrl.SetExtendedStyle(dwStyle); //������չ���

	m_listAgentCtrl.InsertColumn(0,"���",LVCFMT_LEFT,50); //50Ϊ�п�
	m_listAgentCtrl.InsertColumn(1,"����",LVCFMT_LEFT,100); //50Ϊ�п�
	m_listAgentCtrl.InsertColumn(2,"��ϵ�绰",LVCFMT_LEFT,150); //50Ϊ�п�
	m_listAgentCtrl.InsertColumn(3,"����Ȩ��",LVCFMT_LEFT,150); //50Ϊ�п�
	m_listAgentCtrl.InsertColumn(4,"�������",LVCFMT_LEFT,350); //50Ϊ�п�

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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAgentMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAgentMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAgentMgrDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("�����ļ�ʧ��","����", MB_OK);
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
		MessageBox("�����ļ�ʧ��","����", MB_OK);
		return;
	}
}

void CAgentMgrDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	Save();

	CDialogEx::OnOK();
}


void CAgentMgrDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	Save();
	CDialogEx::OnCancel();
}
