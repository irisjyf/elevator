// SetAuthDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "SetAuthDlg.h"
#include "afxdialogex.h"

#include "AuthAddDlg.h"
#include "AuthModDlg.h"
// CSetAuthDlg 对话框

IMPLEMENT_DYNAMIC(CSetAuthDlg, CDialogEx)

CSetAuthDlg::CSetAuthDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetAuthDlg::IDD, pParent)
{

}

CSetAuthDlg::~CSetAuthDlg()
{
}

void CSetAuthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUTH_LIST, m_AuthList);
}


BEGIN_MESSAGE_MAP(CSetAuthDlg, CDialogEx)
	ON_BN_CLICKED(IDC_AUTH_ADD, &CSetAuthDlg::OnBnClickedAuthAdd)
	ON_BN_CLICKED(IDC_AUTH_MOD, &CSetAuthDlg::OnBnClickedAuthMod)
	ON_BN_CLICKED(IDC_AUTH_DEL, &CSetAuthDlg::OnBnClickedAuthDel)
	ON_NOTIFY(NM_DBLCLK, IDC_AUTH_LIST, &CSetAuthDlg::OnNMDblclkAuthList)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSetAuthDlg 消息处理程序



void CSetAuthDlg::OnBnClickedAuthAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	CAuthAddDlg dlg;
	if (IDOK!=dlg.DoModal())	
		return ;
	CString szMsg;

	if (!LPDBManage->AddUser(dlg.m_strUser,dlg.m_strPsw,dlg.m_strAuth))
	{
		szMsg.Format("添加用户失败 %s", dlg.m_strUser);
		log_info(szMsg);
		return;
	}
	szMsg.Format("添加用户成功 %s", dlg.m_strUser);
	log_info(szMsg);

	ShowTable();
}


void CSetAuthDlg::OnBnClickedAuthMod()
{
	// TODO: 在此添加控件通知处理程序代码

	int iIndex = m_AuthList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strUser = m_AuthList.GetItemText(iIndex,1);
	strUser.MakeUpper();

	CAuthModDlg dlg;
	dlg.m_strUser = strUser;
	CLoginset *pLoginset = NULL;  
	if (LPDBManage->m_mapLoginset.Lookup(strUser,pLoginset))
	{
		dlg.m_strUser = pLoginset->m_column1;
		dlg.m_strAuth = pLoginset->m_column3;
		dlg.m_strRealPsw = pLoginset->m_column2;
	}

	if (IDOK!=dlg.DoModal())	
		return ;
	CString szMsg;
	if (!LPDBManage->OPerUser(dlg.m_strUser,dlg.m_strPsw,dlg.m_strPsw2,dlg.m_strAuth,dlg.m_strOldPsw))
	{	
		szMsg.Format("修改用户失败 %s", dlg.m_strUser);
		log_info(szMsg);
		return ;
	}
	szMsg.Format("修改用户成功 %s", dlg.m_strUser);
	log_info(szMsg);
}


BOOL CSetAuthDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_AuthList.SetImageList(&m_image, LVSIL_SMALL);


	// TODO:  在此添加额外的初始化
	m_AuthList.InsertColumn(0,"NO.");
	m_AuthList.InsertColumn(1,"用户名称");
	m_AuthList.InsertColumn(2,"用户权限");
;
	//	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	RECT rect;
	m_AuthList.GetWindowRect(&rect);
	int wid = (rect.right - rect.left - 30)/2;
	m_AuthList.SetColumnWidth(0,30);
	m_AuthList.SetColumnWidth(1,wid);
	m_AuthList.SetColumnWidth(2,wid-5);

	m_AuthList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	ShowTable();


	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL  CSetAuthDlg::ShowTable()
{
	m_AuthList.DeleteAllItems();

	CLoginset *pLoginset = NULL;
	CString strName(""),strTemp;

	int i=0;
	LPDBManage->GetUserList();
	POSITION pos = LPDBManage->m_mapLoginset.GetStartPosition();
	while(pos)
	{
		LPDBManage->m_mapLoginset.GetNextAssoc(pos,strName,pLoginset);
		ASSERT(pLoginset);

		if(pLoginset->m_column1 == "root")
			continue;

		strTemp.Format("%d",i+ 1);
		m_AuthList.InsertItem(i,strTemp);

		m_AuthList.SetItemText(i,1,pLoginset->m_column1);
		m_AuthList.SetItemText(i,2,pLoginset->m_column3);

		i++;  
	}


	Invalidate(TRUE);
	return TRUE;
}

void CSetAuthDlg::OnBnClickedAuthDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_AuthList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	if (IDYES == MessageBox("请确认是否删除该用户信息?","注意",MB_YESNO|MB_ICONQUESTION))
	{

		CString  strUser = m_AuthList.GetItemText(iIndex,1);

		LPDBManage->DelUser(strUser);
		CString szMsg;
		szMsg.Format("删除用户 %s", strUser);
		log_info(szMsg);

		ShowTable();
	}
	return;
}

void CSetAuthDlg::OnNMDblclkAuthList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	OnBnClickedAuthMod();
}

void CSetAuthDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		ReSize();  
	}
	// TODO: 在此处添加消息处理程序代码
}


void CSetAuthDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnOK();
}


void CSetAuthDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	return;
	CDialogEx::OnCancel();
}
