// DlgAgentInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "AgentMgr.h"
#include "DlgAgentInfo.h"
#include "afxdialogex.h"


// CDlgAgentInfo 对话框

IMPLEMENT_DYNAMIC(CDlgAgentInfo, CDialogEx)

CDlgAgentInfo::CDlgAgentInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAgentInfo::IDD, pParent)
	, m_AgentID(0)
	, m_AgentName(_T(""))
	, m_AgentTel(_T(""))
	, m_szCode(_T(""))
	, m_iAuthority(2)
{

}

CDlgAgentInfo::~CDlgAgentInfo()
{
}

void CDlgAgentInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_AgentID);
	DDX_Text(pDX, IDC_NAME, m_AgentName);
	DDX_Text(pDX, IDC_TEL, m_AgentTel);
	DDV_MaxChars(pDX, m_AgentTel, 11);
	DDX_Text(pDX, IDC_NAME3, m_szCode);
	DDX_Control(pDX, IDC_CMB_AUTHORTY, m_cmbAgentAuthority);
}


BEGIN_MESSAGE_MAP(CDlgAgentInfo, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CMB_AUTHORTY, &CDlgAgentInfo::OnCbnSelchangeCmbAuthorty)
	ON_BN_CLICKED(IDC_BTN_GETAGENTCODE, &CDlgAgentInfo::OnBnClickedBtnGetagentcode)
END_MESSAGE_MAP()


// CDlgAgentInfo 消息处理程序


BOOL CDlgAgentInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_cmbAgentAuthority.AddString("超级权限");
	m_cmbAgentAuthority.AddString("管理员");
	m_cmbAgentAuthority.AddString("一般权限");

	m_cmbAgentAuthority.SetCurSel(m_iAuthority);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgAgentInfo::OnCbnSelchangeCmbAuthorty()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iAuthority = m_cmbAgentAuthority.GetCurSel();
}

const char* newGUID()  
{  
	static char buf[64] = {0};  
	GUID guid;  
	if (S_OK == ::CoCreateGuid(&guid))  
	{  
		_snprintf(buf, sizeof(buf)  
			, "{%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}"  
			, guid.Data1  
			, guid.Data2  
			, guid.Data3  
			, guid.Data4[0], guid.Data4[1]  
		, guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5]  
		, guid.Data4[6], guid.Data4[7]  
		);  
	}  
	return (const char*)buf;  
}  
void CDlgAgentInfo::OnBnClickedBtnGetagentcode()
{
	// TODO: 在此添加控件通知处理程序代码
	m_szCode = newGUID();
	UpdateData(FALSE);
}
