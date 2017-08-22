// MakeCardDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "MakeCardDlg.h"
#include "afxdialogex.h"
#include "DlgMakeCardInfo.h"


// CMakeCardDlg 对话框

IMPLEMENT_DYNAMIC(CMakeCardDlg, CDialogEx)

CMakeCardDlg::CMakeCardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMakeCardDlg::IDD, pParent)
	, m_iMakeNum(0)
	, m_strTime(_T(""))
	, m_bStartFlag(FALSE)
{

}

CMakeCardDlg::~CMakeCardDlg()
{
}

void CMakeCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_NUM, m_iMakeNum);
	DDX_Text(pDX, IDC_STATIC_TIME, m_strTime);
	DDX_Control(pDX, IDC_FLIED_LIST2, m_cList);
}


BEGIN_MESSAGE_MAP(CMakeCardDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MAKECARD_START, &CMakeCardDlg::OnBnClickedBtnMakecardStart)
	ON_BN_CLICKED(IDC_BTN_MAKECARD_END, &CMakeCardDlg::OnBnClickedBtnMakecardEnd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_MAKECARD_DELL, &CMakeCardDlg::OnBnClickedBtnMakecardDell)
	ON_BN_CLICKED(IDC_BTN_ENABLE_VERITYFLAG, &CMakeCardDlg::OnBnClickedBtnEnableVerityflag)
	ON_BN_CLICKED(IDC_BTN_DISABLE_VERITYFLAG, &CMakeCardDlg::OnBnClickedBtnDisableVerityflag)
	ON_BN_CLICKED(IDC_BTN_MAKECARD_CLEARPSW, &CMakeCardDlg::OnBnClickedBtnMakecardClearpsw)
END_MESSAGE_MAP()


// CMakeCardDlg 消息处理程序


#define  TIMER_PRODUCE 100


BOOL CMakeCardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CImageList m_image; 
	m_image.Create(1,18,ILC_COLOR32,1,0); 
	m_cList.SetImageList(&m_image, LVSIL_SMALL);

	// TODO:  在此添加额外的初始化
	m_cList.InsertColumn(0,"No.");
	m_cList.InsertColumn(1,"制卡时间");
	m_cList.InsertColumn(2,"制卡数量");
	RECT rect;
	m_cList.GetWindowRect(&rect);
	int wid = rect.right - rect.left-40;
	m_cList.SetColumnWidth(0,40);
	m_cList.SetColumnWidth(1,wid / 2);
	m_cList.SetColumnWidth(2,wid / 2 - 5);
	m_cList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	// TODO:  在此添加额外的初始化
	CTime tm  = ::time(NULL);
	m_strTime  = tm.Format("%Y-%m-%d %H:%M:%d");


	LPDBManage->GetMakeCardList();
	ShowTable(LPDBManage->m_mapMakeCard);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL    CMakeCardDlg::ShowTable(CMap<CString,LPCTSTR,CMakeCardSet*,CMakeCardSet*> &mapMakeCardSet)
{
	m_cList.DeleteAllItems();

	int i=0;
	CString      strMakecrdTime;
	CMakeCardSet *pMakeCardSet = NULL;  

	POSITION pos = mapMakeCardSet.GetStartPosition();
	while(pos)
	{
		mapMakeCardSet.GetNextAssoc(pos,strMakecrdTime,pMakeCardSet);
		ASSERT(pMakeCardSet);

		CString Str,str2,str3;
		Str.Format("%d",i+ 1);
		m_cList.InsertItem(i,Str);

		m_cList.SetItemText(i,1,pMakeCardSet->m_strMakecrdTime);

		Str.Format("%d",pMakeCardSet->m_iMakecrdNum);
		m_cList.SetItemText(i,2,Str);

		//m_cList.SetItemText(i,3,pYonghuset->m_yzmp);

		i++;  
	}

	return TRUE;
}

void CMakeCardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(TIMER_PRODUCE == nIDEvent)
	{
		if(CRadioCardProtocal::GetRadioCardProtocal()->CheckProduceData())
			m_iMakeNum++;
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CMakeCardDlg::OnBnClickedBtnMakecardModify()
{
	// TODO: 在此添加控件通知处理程序代码
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strTime = m_cList.GetItemText(iIndex,1);

	if(MessageBox("确定删除所选记录？","提示",MB_OKCANCEL)==IDOK)
	{
		CMakeCardSet*  pQuset = LPDBManage->GetMakeCardByName(strTime);
		
		CDlgMakeCardInfo dlg;
		dlg.m_strMakeCardTime = pQuset->m_strMakecrdTime;
		dlg.m_iNum = pQuset->m_iMakecrdNum;
		dlg.m_szUser = pQuset->m_strUser;
		dlg.m_szNote = pQuset->m_strDes;
		if(dlg.DoModal() == IDOK)
		{
			CMakeCardSet* pNewQuset = new CMakeCardSet;
			pNewQuset->m_ID = pQuset->m_ID;
			pNewQuset->m_strMakecrdTime = dlg.m_strMakeCardTime;
			pNewQuset->m_iMakecrdNum = dlg.m_iNum;
			pNewQuset->m_strUser = dlg.m_szUser;
			pNewQuset->m_strDes = dlg.m_szNote;
			if (LPDBManage->OperMakeCard(pNewQuset,MOD_TYPE))
			{
				CString strContent;
				strContent.Format("%d",dlg.m_iNum);
				m_cList.SetItemText(iIndex, 2, strContent);
			}
			else
			{
				AfxMessageBox("修改内容失败");
			}
		}
	}
}


void CMakeCardDlg::OnBnClickedBtnMakecardDell()
{
	// TODO: 在此添加控件通知处理程序代码

	POSITION pos = m_cList.GetFirstSelectedItemPosition();

	if(pos && MessageBox("确定删除所选内容？","提示",MB_OKCANCEL)==IDOK)
	{
		while(pos)
		{
			int nSelectItem = m_cList.GetNextSelectedItem(pos);
			if (nSelectItem >= 0 && nSelectItem <m_cList.GetItemCount())
			{
				CString  strTime = m_cList.GetItemText(nSelectItem,1);
				CMakeCardSet*  pQuset = LPDBManage->GetMakeCardByName(strTime);
				if (LPDBManage->OperMakeCard(pQuset,DEL_TYPE))
				{
					LPDBManage->GetMakeCardList();
				}
			}
		}
	}
	ShowTable(LPDBManage->m_mapMakeCard);
	/*
	int iIndex = m_cList.GetNextItem(-1,LVNI_SELECTED);
	if(iIndex < 0)  return;

	CString  strTime = m_cList.GetItemText(iIndex,1);

	if(MessageBox("确定删除所选记录？","提示",MB_OKCANCEL)==IDOK)
	{
	CMakeCardSet*  pQuset = LPDBManage->GetMakeCardByName(strTime);
	if (LPDBManage->OperMakeCard(pQuset,DEL_TYPE))
	{
	LPDBManage->GetMakeCardList();
	ShowTable(LPDBManage->m_mapMakeCard);
	}
	}*/
}


void CMakeCardDlg::OnBnClickedBtnMakecardStart()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!m_bStartFlag)
	{
		BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->StartPruduceIC();
		SetTimer(TIMER_PRODUCE, 5, NULL);

		m_bStartFlag = TRUE;
	}
}


void CMakeCardDlg::OnBnClickedBtnMakecardEnd()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bStartFlag)
	{
		BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->StopPruduceIC();
		KillTimer(TIMER_PRODUCE);

		CMakeCardSet makeCardSet;
		CTime tmMakeCard  = ::time(NULL);
		makeCardSet.m_strMakecrdTime = tmMakeCard.Format("%Y-%m-%d %H:%M:%S");
		makeCardSet.m_iMakecrdNum = m_iMakeNum;
		CString strInfo;
		strInfo.Format("制卡操作员为：%s", LPDBManage->GetCurrentUser() );
		makeCardSet.m_strDes = strInfo;
		LPDBManage->OperMakeCard(&makeCardSet, ADD_TYPE);

		CString Str,str2,str3;
		Str.Format("%d", makeCardSet.m_ID );
		int iCount = m_cList.GetItemCount();
		m_cList.InsertItem(iCount,Str);

		m_cList.SetItemText(iCount, 1, makeCardSet.m_strMakecrdTime);

		Str.Format("%d",makeCardSet.m_iMakecrdNum);
		m_cList.SetItemText(iCount, 2, Str);

		m_bStartFlag = FALSE;
	}
}

void CMakeCardDlg::OnBnClickedBtnEnableVerityflag()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->EnableVerityPruduceFlag();
	if(bRet)
		AfxMessageBox("使能改写卡器必须选用指定卡");
}


void CMakeCardDlg::OnBnClickedBtnDisableVerityflag()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->DisableVerityPruduceFlag();
	if(bRet)
		AfxMessageBox("关闭改写卡器必须选用指定卡");
}


void CMakeCardDlg::OnBnClickedBtnMakecardClearpsw()
{
	// TODO: 在此添加控件通知处理程序代码
	CRadioCardProtocal::GetRadioCardProtocal()->ClearCardPsw();
}
