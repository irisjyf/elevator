// FuncInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "FuncInfoDlg.h"
#include "afxdialogex.h"


// CFuncInfoDlg 对话框

IMPLEMENT_DYNAMIC(CFuncInfoDlg, CDialogEx)

CFuncInfoDlg::CFuncInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFuncInfoDlg::IDD, pParent)
	, m_strOutput(_T(""))
	, m_bChoice1(FALSE)
	, m_bChoice2(FALSE)
	, m_bChoice3(FALSE)
	, m_bChoice4(FALSE)
	, m_bChoice5(FALSE)
	, m_bChoice6(FALSE)
	, m_bChoice7(FALSE)
	, m_bChoice8(FALSE)
	, m_bChoice9(FALSE)
	, m_bChoice10(FALSE)
	, m_bOpenCard(FALSE)
	, m_sn(_T(""))
	, m_klx(FUNC_TYPE_FORBIDEN)
	, m_zklx(FALSE)
{
	m_qjkh1=0;
	m_qjkh2=0;
	m_qjkh3=0;
	m_qjkh4=0;
	m_qjkh5=0;
	m_qjkh6=0;
	m_qjkh7=0;
	m_qjkh8=0;
	m_qjkh9=0;
	m_gnkh =0;
	m_jssj =0;
}

CFuncInfoDlg::~CFuncInfoDlg()
{
}

void CFuncInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT12, m_strOutput);

	DDX_Text(pDX, IDC_EDIT_CARD1, m_qjkh1);
	DDX_Text(pDX, IDC_EDIT_CARD2, m_qjkh2);
	DDX_Text(pDX, IDC_EDIT_CARD3, m_qjkh3);
	DDX_Text(pDX, IDC_EDIT_CARD4, m_qjkh4);
	DDX_Text(pDX, IDC_EDIT_CARD5, m_qjkh5);
	DDX_Text(pDX, IDC_EDIT_CARD6, m_qjkh6);
	DDX_Text(pDX, IDC_EDIT_CARD7, m_qjkh7);
	DDX_Text(pDX, IDC_EDIT_CARD8, m_qjkh8);

	DDX_Check(pDX, IDC_CHECK_GNK1, m_bChoice1);
	DDX_Check(pDX, IDC_CHECK_GNK2, m_bChoice2);
	DDX_Check(pDX, IDC_CHECK_GNK3, m_bChoice3);
	DDX_Check(pDX, IDC_CHECK_GNK4, m_bChoice4);
	DDX_Check(pDX, IDC_CHECK_GNK5, m_bChoice5);
	DDX_Check(pDX, IDC_CHECK_GNK6, m_bChoice6);
	DDX_Check(pDX, IDC_CHECK_GNK7, m_bChoice7);
	DDX_Check(pDX, IDC_CHECK_GNK8, m_bChoice8);

	//DDX_Check(pDX, IDC_CHECK1, m_bOpenCard);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_SN, m_sn);
	DDX_Text(pDX, IDC_EDIT_FUC_CARDNO, m_gnkh);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_jssj);
	DDX_Check(pDX, IDC_CHECK_GNK9, m_zklx);
}


BEGIN_MESSAGE_MAP(CFuncInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDD_SAVEDATA, &CFuncInfoDlg::OnBnClickedSavedata)
	ON_BN_CLICKED(IDD_READ_CARD, &CFuncInfoDlg::OnBnClickedReadCard)
	ON_BN_CLICKED(IDD_REPAIR_CARD, &CFuncInfoDlg::OnBnClickedRepairCard)
	ON_BN_CLICKED(IDCANCEL, &CFuncInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_QUERY_SERIAL, &CFuncInfoDlg::OnBnClickedBtnQuerySerial)
	ON_WM_TIMER()
	//ON_MESSAGE(WM_USER_UPDATEDATE, &CFuncInfoDlg::OnUserUpdateData)
	ON_BN_CLICKED(IDC_RADIO_FORBIDEN, &CFuncInfoDlg::OnBnClickedRadioForbiden)
	ON_BN_CLICKED(IDC_RADIO_CHECKTIME, &CFuncInfoDlg::OnBnClickedRadioChecktime)
	ON_BN_CLICKED(IDC_RADIO_BLACKLIST, &CFuncInfoDlg::OnBnClickedRadioBlacklist)
	ON_BN_CLICKED(IDC_RADIO_INTERPARAM, &CFuncInfoDlg::OnBnClickedRadioInterparam)
	ON_BN_CLICKED(IDC_ENABLECOUNTER, &CFuncInfoDlg::OnBnClickedEnablecounter)
	ON_BN_CLICKED(IDC_DISABLECOUNTER, &CFuncInfoDlg::OnBnClickedDisablecounter)
END_MESSAGE_MAP()


// CFuncInfoDlg 消息处理程序


BOOL CFuncInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_cType == ADD_TYPE)
		SetWindowText("增加功能卡");
	else
		SetWindowText("修改功能卡");

	//CArray<CSuoset*,CSuoset*> arr;
	//LPDBManage->GetElevatorList(arr);

	CDateTimeCtrl *pCtrl = (CDateTimeCtrl *)GetDlgItem(IDC_DATETIMEPICKER1);
	pCtrl->SetFormat("yyy-MM-dd  HH:mm");
	int lStatus = 0;
	CKeyinfoset* pset = LPDBManage->GetFuncByID(m_id, lStatus);

	m_klx = pset->m_klx;
	//m_FuncType = pset->m_klx;

	switch(m_klx)
	{
	case FUNC_TYPE_FORBIDEN:
		((CButton*)GetDlgItem(IDC_RADIO_FORBIDEN))->SetCheck(TRUE);
		break;
	case FUNC_TYPE_CHECK_TIME:
		((CButton*)GetDlgItem(IDC_RADIO_CHECKTIME))->SetCheck(TRUE);
		break;
	case FUNC_TYPE_Check:
		((CButton*)GetDlgItem(IDC_RADIO_INTERPARAM))->SetCheck(TRUE);
		break;
	case FUNC_TYPE_CLEARBLACKLIST:
		((CButton*)GetDlgItem(IDC_RADIO_BLACKLIST))->SetCheck(TRUE);
		break;
	}

	// TODO:  在此添加额外的初始化
	SetPara2(FALSE);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL    CFuncInfoDlg::SetPara2(BOOL bSave)
{
	int iStatus = ADD_TYPE;
	CKeyinfoset *pYonghuset = LPDBManage->GetFuncByID(m_id, iStatus);
	CString strTemp;
	if (bSave)
	{
		UpdateData(TRUE);
		pYonghuset->m_id      =  m_id;
		//pYonghuset->m_klx     =  m_klx + 1 ;
		pYonghuset->m_klx     =  m_klx;
		pYonghuset->m_gnkh    =  m_gnkh;
		pYonghuset->m_zklx    =  m_zklx;
		pYonghuset->m_sycs    =  m_sycs;

		pYonghuset->m_qjkh1    =  m_qjkh1;
		pYonghuset->m_qjbz1    =  m_bChoice1;

		pYonghuset->m_qjkh2    =  m_qjkh2;
		pYonghuset->m_qjbz2    =  m_bChoice2;

		pYonghuset->m_qjkh3    =  m_qjkh3;
		pYonghuset->m_qjbz3    =  m_bChoice3;

		pYonghuset->m_qjkh4    =  m_qjkh4;
		pYonghuset->m_qjbz4    =  m_bChoice4;

		pYonghuset->m_qjkh5    =  m_qjkh5;
		pYonghuset->m_qjbz5    =  m_bChoice5;

		pYonghuset->m_qjkh6    =  m_qjkh6;
		pYonghuset->m_qjbz6    =  m_bChoice6;

		pYonghuset->m_qjkh7    =  m_qjkh7;
		pYonghuset->m_qjbz7    =  m_bChoice7;

		pYonghuset->m_qjkh8    =  m_qjkh8;
		pYonghuset->m_qjbz8    =  m_bChoice8;

		pYonghuset->m_jssj    =   m_jssj.Format("%y-%m-%d %H:%M");
		pYonghuset->m_status  =  m_status;

		pYonghuset->m_sn  =  m_sn;
	}
	else
	{
		m_id    = pYonghuset->m_id;
		//m_klx   = pYonghuset->m_klx & 0x0f - 1; //pYonghuset->m_klx;
		m_klx   = pYonghuset->m_klx;
		m_gnkh = pYonghuset->m_gnkh;
		m_zklx = pYonghuset->m_zklx;
		m_sycs = pYonghuset->m_sycs;

		m_qjkh1 = pYonghuset->m_qjkh1;
		m_bChoice1 = pYonghuset->m_qjbz1;

		m_qjkh2 = pYonghuset->m_qjkh2;
		m_bChoice2 = pYonghuset->m_qjbz2;

		m_qjkh3 = pYonghuset->m_qjkh3;
		m_bChoice3 = pYonghuset->m_qjbz3;

		m_qjkh4 = pYonghuset->m_qjkh4;
		m_bChoice4= pYonghuset->m_qjbz4;

		m_qjkh5 = pYonghuset->m_qjkh5;
		m_bChoice5 = pYonghuset->m_qjbz5;

		m_qjkh6 = pYonghuset->m_qjkh6;
		m_bChoice6= pYonghuset->m_qjbz6;

		m_qjkh7 = pYonghuset->m_qjkh7;
		m_bChoice7 = pYonghuset->m_qjbz7;

		m_qjkh8 = pYonghuset->m_qjkh8;
		m_bChoice8 = pYonghuset->m_qjbz8;

		CTime   ct = ::time(NULL);
		m_jssj    =  ct;


		m_status  = pYonghuset->m_status;
		m_sn      = pYonghuset->m_sn;

	}

	this->Invalidate(TRUE);

	UpdateData(FALSE);
	return TRUE;
}


void   CFuncInfoDlg::SetPara(char cType, long lID)
{
	m_id    = lID;
	m_cType = cType;
}

void  CFuncInfoDlg::SetOutPutInfo(CString strInfo)
{
	UpdateData(TRUE);
	CString strTemp;

	strTemp = strInfo +"\r\n";
	m_strOutput = strTemp + m_strOutput;

	UpdateData(FALSE);
}


void CFuncInfoDlg::OnBnClickedSavedata()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara2(TRUE);
	CString strMsg;
	int lStatus = ADD_TYPE;
	CKeyinfoset *pYonghuset = LPDBManage->GetFuncByID(m_id, lStatus);

	//CKeyinfoset *pYonghuset = LPDBManage->GetFuncByID(m_id);
	BOOL bWriteRet = WirteIC();

	BOOL bRetDatabase = FALSE;
	if(bWriteRet)
	{
		bRetDatabase = LPDBManage->OperFunc(pYonghuset,m_cType);
		if(!bRetDatabase)
		{
			bRetDatabase = LPDBManage->OperFunc(pYonghuset,lStatus);
		}
	}
	CString szCard = GetFunctionCardType(m_klx);
	if (bWriteRet && bRetDatabase)
		strMsg.Format( "%s写卡成功！\r\n", szCard);
	else
		strMsg.Format( "%s写卡失败！\r\n", szCard);

	SetOutPutInfo(strMsg);

	log_info(strMsg);

	if(m_cType == ADD_TYPE)
	{
		m_id = LPDBManage->GetFuncID();
		pYonghuset = LPDBManage->GetFuncByID(m_id, lStatus);
		m_gnkh = m_id;
		//ResetDlgData();
	}

	//m_strOutput  = GetCardInfo();
	//m_strOutput = strMsg + m_strOutput;

	UpdateData(FALSE);
}

void CFuncInfoDlg::OnBnClickedReadCard()
{
	// TODO: 在此添加控件通知处理程序代码
	SetOutPutInfo("读卡保存失败！");
}


void CFuncInfoDlg::OnBnClickedRepairCard()
{
	// TODO: 在此添加控件通知处理程序代码
	SetOutPutInfo("补卡保存失败！");
}

void CFuncInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

BOOL   CFuncInfoDlg::WirteIC(void)
{
	unsigned char buf[80] = {0};

	/////////////////////
	buf[0] = 2;  //写命令字
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	buf[4] = 0xff; //卡号
	buf[5] = 0x03; //卡类型
	//buf[6] = m_klx + 1; //子卡类型
	buf[6] = m_klx; //子卡类型
	buf[7] = m_gnkh  /  65536 & 0xff;
	buf[8] = m_gnkh % 65536 / 256;
	buf[9] = m_gnkh % 65536%256;
	buf[10] = 0;//m_fjbh/256;
	buf[11] = 0;//m_fjbh%256;
	buf[12] = 0;
	buf[13] = 0;//乘梯权限模式
	buf[14] = 0;//(m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	buf[15] = 0;//m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	buf[16] = 0;//m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	buf[17] = 0;//m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	buf[18] = 0;//m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;
	buf[19] = 0;//(m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	buf[20] = 0;//m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	buf[21] = 0;//m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	buf[22] = 0;//m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	buf[23] = 0;//m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;
	buf[24] = m_sycs / 256;
	buf[25] = m_sycs % 256;
	//buf[26] = m_kydt;
	buf[26] = m_zklx;
	//buf[27] = m_qjkh1 / 65536;
	//buf[28] = m_qjkh1 % 65536/256;
	//buf[29] = m_qjkh1 % 65536%256;
	//buf[30] = m_qjbz1;
	//buf[31] = m_qjkh2 / 65536;
	//buf[32] = m_qjkh2 % 65536 /256;
	//buf[33] = m_qjkh2 % 65536 % 256;
	//buf[34] = m_qjbz2;
	//buf[35] = m_qjkh3 / 65536;
	//buf[36] = m_qjkh3 % 65536 / 256;
	//buf[37] = m_qjkh3 % 65536 % 256;
	//buf[38] = m_qjbz3;
	//buf[39] = m_qjkh4 / 65536;
	//buf[40] = m_qjkh4 % 65536 / 256;
	//buf[41] = m_qjkh4 % 65536 % 256;
	//buf[42] = m_qjbz4;
	//buf[43] = m_qjkh5/65536;
	//buf[44] = m_qjkh5%65536/256;
	//buf[45] = m_qjkh5%65536%256;
	//buf[46] = m_qjbz5;
	//buf[47] = m_qjkh6/65536;
	//buf[48] = m_qjkh6%65536/256;
	//buf[49] = m_qjkh6%65536%256;
	//buf[50] = m_qjbz6;
	//buf[51] = m_qjkh7/65536;
	//buf[52] = m_qjkh7%65536/256;
	//buf[53] = m_qjkh7%65536%256;
	//buf[54] = m_qjbz7;
	//buf[55] = m_qjkh8/65536;
	//buf[56] = m_qjkh8%65536/256;
	//buf[57] = m_qjkh8%65536%256;
	//buf[58] = m_qjbz8;
	//buf[59] = m_qjkh9/65536;
	//buf[60] = m_qjkh9%65536/256;
	//buf[61] = m_qjkh9%65536%256;
	//buf[62] = m_qjbz9;
	//buf[63] = m_qjkh10/65536;
	//buf[64] = m_qjkh10%65536/256;
	//buf[65] = m_qjkh10%65536%256;
	//buf[66] = m_qjbz10;

	buf[27] = m_qjkh1 >> 16;
	buf[28] = (m_qjkh1 >> 8) & 0xFF;
	buf[29] = m_qjkh1 & 0xFF;
	buf[30] = m_bChoice1 & 0xFF;
	buf[31] = m_qjkh2 >> 16;
	buf[32] = (m_qjkh2 >> 8) & 0xFF;
	buf[33] = m_qjkh2 & 0xFF;
	buf[34] = m_bChoice2 & 0xFF;
	buf[35] = m_qjkh3 >> 16;
	buf[36] = (m_qjkh3 >> 8) & 0xFF;
	buf[37] = m_qjkh3 & 0xFF;
	buf[38] = m_bChoice3 & 0xFF;
	buf[39] = m_qjkh4 >> 16;
	buf[40] = (m_qjkh4 >> 8) & 0xFF;
	buf[41] = m_qjkh4 & 0xFF;
	buf[42] = m_bChoice4 & 0xFF;

	buf[43] = m_qjkh5 >> 16;
	buf[44] = (m_qjkh5 >> 8) & 0xFF;
	buf[45] = m_qjkh5 & 0xFF;
	buf[46] = m_bChoice5 & 0xFF;
	buf[47] = m_qjkh6 >> 16;
	buf[48] = (m_qjkh6 >> 8) & 0xFF;
	buf[49] = m_qjkh6 & 0xFF;
	buf[50] = m_bChoice6 & 0xFF;
	buf[51] = m_qjkh7 >> 16;
	buf[52] = (m_qjkh7 >> 8) & 0xFF;
	buf[53] = m_qjkh7 & 0xFF;
	buf[54] = m_bChoice7 & 0xFF;
	buf[55] = m_qjkh8 >> 16;
	buf[56] = (m_qjkh8 >> 8) & 0xFF;
	buf[57] = m_qjkh8 & 0xFF;
	buf[58] = m_bChoice8 & 0xFF;
	buf[59] = m_qjkh9 >> 16;
	buf[60] = (m_qjkh9 >> 8) & 0xFF;
	buf[61] = m_qjkh9 & 0xFF;
	buf[62] = m_bChoice9 & 0xFF;
	buf[63] = m_qjkh10 >> 16;
	buf[64] = (m_qjkh10 >> 8) & 0xFF;
	buf[65] = m_qjkh10 & 0xFF;
	buf[66] = m_bChoice10 & 0xFF;

	//int iYear = m_jssj.GetYear()-2000;
	//iYear = iYear / 10 *16 + iYear %10;
	buf[67] = (m_jssj.GetYear()-2000)/10*16+(m_jssj.GetYear()-2000)%10;
	buf[68] = m_jssj.GetMonth()/10*16+m_jssj.GetMonth()%10;
	buf[69] = m_jssj.GetDay()/10*16+m_jssj.GetDay()%10;
	buf[70] = m_jssj.GetHour()/10*16+m_jssj.GetHour()%10;
	buf[71] = m_jssj.GetMinute()/10*16+m_jssj.GetMinute()%10;

	//LPSerialProtocol->Send(5,72,(char *)buf, CallbackFuncInfo);
	BOOL bRet  = CRadioCardProtocal::GetRadioCardProtocal()->WriteFuncData(buf, 72);
	return bRet;
}


void CFuncInfoDlg::OnBnClickedBtnQuerySerial()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DWORD dwRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadSerialNo();
	if(dwRet > 0)
		m_sn.Format("%u", dwRet);
	UpdateData(FALSE);
}


void CFuncInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CFuncInfoDlg::OnUserUpdateData(WPARAM wParam,LPARAM lParam)
{
	UpdateData(FALSE);
	return 0;
}

void CFuncInfoDlg::OnBnClickedRadioForbiden()
{
	// TODO: 在此添加控件通知处理程序代码
	m_klx = FUNC_TYPE_FORBIDEN;
}


void CFuncInfoDlg::OnBnClickedRadioChecktime()
{
	// TODO: 在此添加控件通知处理程序代码

	m_klx = FUNC_TYPE_CHECK_TIME;
}


void CFuncInfoDlg::OnBnClickedRadioBlacklist()
{
	// TODO: 在此添加控件通知处理程序代码

	m_klx = FUNC_TYPE_CLEARBLACKLIST;
}


void CFuncInfoDlg::OnBnClickedRadioInterparam()
{
	// TODO: 在此添加控件通知处理程序代码
	m_klx = FUNC_TYPE_Check;
}


void CFuncInfoDlg::OnBnClickedEnablecounter()
{
	// TODO: 在此添加控件通知处理程序代码
	m_klx = FUNC_TYPE_ENABLECOUNTER;
}


void CFuncInfoDlg::OnBnClickedDisablecounter()
{
	// TODO: 在此添加控件通知处理程序代码
	m_klx = FUNC_TYPE_DISABLECOUNTER;
}

CString	CFuncInfoDlg::GetCardInfo()
{
	CString szInfo, strTemp;
	if(m_klx == FUNC_TYPE_FORBIDEN)
	{
		if(m_zklx == 1)
			strTemp.Format("功能卡类型：\r\n  管理员起禁卡 \r\n");
		else
			strTemp.Format("功能卡类型：\r\n  业主卡起禁卡 \r\n");

		szInfo += strTemp;


		CString strForbiden;
		if(m_qjkh1 != 0)
		{
			if(m_bChoice1 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh1);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh1);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh2 != 0)
		{
			if(m_bChoice2 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh2);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh2);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh3 != 0)
		{
			if(m_bChoice3 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh3);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh3);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh4 != 0)
		{
			if(m_bChoice4 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh4);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh4);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh5 != 0)
		{
			if(m_bChoice5 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh5);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh5);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh6 != 0)
		{
			if(m_bChoice6 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh6);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh6);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh7 != 0)
		{
			if(m_bChoice7 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh7);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh7);
			strTemp =  strTemp + strForbiden;
		}
		if(m_qjkh8 != 0)
		{
			if(m_bChoice8 == TRUE)
				strForbiden.Format("  卡号：%d 禁用\r\n", m_qjkh8);
			else
				strForbiden.Format("  卡号：%d 启用\r\n", m_qjkh8);
			strTemp =  strTemp + strForbiden;
		}
		szInfo +=  strTemp;
	}
	else if(m_klx == FUNC_TYPE_Check)
	{
		strTemp.Format("功能卡类型：\r\n  获取内部参数卡\r\n");
		szInfo +=  strTemp;
	}
	else if(m_klx == FUNC_TYPE_SWITCH)
	{
		strTemp.Format("功能卡类型：\r\n  开关卡\r\n");
		szInfo +=  strTemp;
	}
	else if(m_klx == FUNC_TYPE_CLEARBLACKLIST)
	{
		strTemp.Format("功能卡类型：\r\n  清楚黑名单");
		szInfo +=  strTemp;
	}
	else if(m_klx == FUNC_TYPE_CHECK_TIME)
	{
		strTemp.Format("功能卡类型：\r\n  校时卡\r\n  设定时间：%d-%d-%d", 
			m_jssj.GetYear(),
			m_jssj.GetMonth(),
			m_jssj.GetDay());
		szInfo +=  strTemp;
	}
	return szInfo;
}

