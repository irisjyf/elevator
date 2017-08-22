// CustermerInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "CustermerInfoDlg.h"
#include "CustomerDlg.h"
#include "afxdialogex.h"

#include "FloorDlg.h"
// CCustermerInfoDlg 对话框
unsigned char dtkycxznum[4][64]  = {0};

IMPLEMENT_DYNAMIC(CCustermerInfoDlg, CDialogEx)

CCustermerInfoDlg::CCustermerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCustermerInfoDlg::IDD, pParent)	
	, m_yzmc(_T(""))
	, m_sjhm(_T(""))
	, m_fjbh(10000)
	, m_ID(1)
	, m_sycs(0)
	, m_yzmp(_T(""))
	, m_tmfrom(COleDateTime::GetCurrentTime())
	, m_tmto(COleDateTime::GetCurrentTime())
	, m_sn(_T(""))
	, m_dtkyc4(_T(""))
	, m_dtkyc3(_T(""))
	, m_dtkyc2(_T(""))
	, m_dtkyc1(_T(""))

	, m_dtkycxz1(_T(""))
	, m_dtkycxz2(_T(""))
	, m_dtkycxz3(_T(""))
	, m_dtkycxz4(_T(""))

	, m_strOutput(_T(""))
	, m_xzms(0)
	, m_strElv1(_T(""))
	, m_strElv2(_T(""))
	, m_strElv3(_T(""))
	, m_strElv4(_T(""))
	, m_iOperType(0)
	, m_status(FALSE)
	, m_hmdcs(0)
	, m_yzkh(1)
	, m_pProtocal(NULL)
	, m_bUpdateData(FALSE)
	,m_bReadCardFlag(FALSE)
{
	m_sn.Empty();
	m_pProtocal = CRadioCardProtocal::GetRadioCardProtocal();
}

CCustermerInfoDlg::~CCustermerInfoDlg()
{
}

void CCustermerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_yzmc);
	DDX_Text(pDX, IDC_EDIT_MOBILE, m_sjhm);
	DDX_Text(pDX, IDC_EDIT_HOUSE_CODE, m_fjbh);
	DDX_Text(pDX, IDC_EDIT_ID, m_yzkh);
	DDX_Text(pDX, IDC_EDIT4, m_sycs);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_yzmp);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tmfrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_tmto);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_SN, m_sn);
	DDX_Text(pDX, IDC_EDIT_ELV4, m_dtkyc4);
	DDX_Text(pDX, IDC_EDIT_ELV3, m_dtkyc3);
	DDX_Text(pDX, IDC_EDIT_ELV2, m_dtkyc2);
	DDX_Text(pDX, IDC_EDIT_ELV1, m_dtkyc1);
	DDX_Text(pDX, IDC_EDIT1, m_strOutput);
	DDX_Radio(pDX, IDC_RADIO_NUM, m_xzms);
	DDX_CBString(pDX, IDC_COMBO_ELV1, m_strElv1);
	DDX_Control(pDX, IDC_COMBO_ELV1, m_cElv1);
	DDX_Control(pDX, IDC_COMBO_ELV2, m_cElv2);
	DDX_CBString(pDX, IDC_COMBO_ELV2, m_strElv2);
	DDX_Control(pDX, IDC_COMBO_ELV3, m_cElv3);
	DDX_CBString(pDX, IDC_COMBO_ELV3, m_strElv3);
	DDX_Control(pDX, IDC_COMBO_ELV4, m_cElv4);
	DDX_CBString(pDX, IDC_COMBO_ELV4, m_strElv4);
	DDX_Radio(pDX, IDC_RADIO7, m_iOperType);
	DDX_Check(pDX, IDC_CHECK_BLACK, m_status);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_BLACK, m_hmdcs);
}


BEGIN_MESSAGE_MAP(CCustermerInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDD_FLOOR_CHOICE, &CCustermerInfoDlg::OnBnClickedFloorChoice)
	ON_BN_CLICKED(IDC_RADIO_NUM, &CCustermerInfoDlg::OnBnClickedRadioNum)
	ON_BN_CLICKED(IDC_RADIO_TIME, &CCustermerInfoDlg::OnBnClickedRadioNum)
	ON_BN_CLICKED(IDC_RADIO_ALL, &CCustermerInfoDlg::OnBnClickedRadioNum)
	ON_BN_CLICKED(IDC_BUTTON_FIN, &CCustermerInfoDlg::OnBnClickedButtonFin)
	ON_BN_CLICKED(IDD_FLOOR_CHOICE2, &CCustermerInfoDlg::OnBnClickedFloorChoice2)
	ON_BN_CLICKED(IDD_FLOOR_CHOICE3, &CCustermerInfoDlg::OnBnClickedFloorChoice3)
	ON_BN_CLICKED(IDD_FLOOR_CHOICE4, &CCustermerInfoDlg::OnBnClickedFloorChoice4)
	ON_BN_CLICKED(IDD_REPAIR_CARD2, &CCustermerInfoDlg::OnBnClickedRepairCard2)
	ON_BN_CLICKED(IDCANCEL, &CCustermerInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDD_USERINFO_CARD_SN, &CCustermerInfoDlg::OnBnClickedUserinfoCardSn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO7, &CCustermerInfoDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO16, &CCustermerInfoDlg::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_BTN_REPLACE, &CCustermerInfoDlg::OnBnClickedBtnReplace)
	ON_BN_CLICKED(IDC_BTN_READCARD, &CCustermerInfoDlg::OnBnClickedBtnReadcard)
END_MESSAGE_MAP()


// CCustermerInfoDlg 消息处理程序

BOOL    CCustermerInfoDlg::SetPara2(BOOL bSave)
{
	UpdateData(TRUE);

	long lStatus = ADD_TYPE;
	CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(m_ID, lStatus);
	CString strTemp;
	if (bSave)
	{
		pYonghuset->m_ID      =  m_ID;
		pYonghuset->m_yzkh    =  m_yzkh;
		pYonghuset->m_yzmc    =  m_yzmc;
		pYonghuset->m_sjhm    =  m_sjhm;
		pYonghuset->m_fjbh    =  m_fjbh;
		pYonghuset->m_sycs    =  m_sycs;
		pYonghuset->m_yzmp    =  m_yzmp;
		pYonghuset->m_xzms    =  m_xzms;

		pYonghuset->m_qssj    =  m_tmfrom.Format("%y-%m-%d %H:%M");
		pYonghuset->m_jzsj    =  m_tmto.Format("%y-%m-%d %H:%M");
		//pYonghuset->m_tmto      =  m_tmto;

		pYonghuset->m_sn    =  m_sn;

		pYonghuset->m_dtkyc1    =  m_dtkyc1;
		pYonghuset->m_dtkyc2    =  m_dtkyc2;
		pYonghuset->m_dtkyc3    =  m_dtkyc3;
		pYonghuset->m_dtkyc4    =  m_dtkyc4;

		pYonghuset->m_dtkycxz1    =  m_dtkycxz1;
		pYonghuset->m_dtkycxz2    =  m_dtkycxz2;
		pYonghuset->m_dtkycxz3    =  m_dtkycxz3;
		pYonghuset->m_dtkycxz4    =  m_dtkycxz4;

		if (!m_strElv1.IsEmpty())
		{
			pYonghuset->m_kydt1    =  LPDBManage->GetElevatorByName(m_strElv1)->m_dtbh;
		}
	
		if (!m_strElv2.IsEmpty())
		{
			pYonghuset->m_kydt2    =  LPDBManage->GetElevatorByName(m_strElv2)->m_dtbh;
		}

		if (!m_strElv3.IsEmpty())
		{
			pYonghuset->m_kydt3    =  LPDBManage->GetElevatorByName(m_strElv3)->m_dtbh;
		}

		if (!m_strElv4.IsEmpty())
		{
			pYonghuset->m_kydt4    =  LPDBManage->GetElevatorByName(m_strElv4)->m_dtbh;
		}
		
		pYonghuset->m_czfs       =  m_iOperType;
		pYonghuset->m_status     =  m_status;
		pYonghuset->m_hmdcs      =  m_hmdcs;
	}
	else
	{
		m_ID      =  pYonghuset->m_ID;
		m_yzkh    =  pYonghuset->m_yzkh;
		m_yzmc    =  pYonghuset->m_yzmc;
		m_sjhm    =  pYonghuset->m_sjhm;
		m_fjbh    =  pYonghuset->m_fjbh;
		m_sycs    =  pYonghuset->m_sycs;
		m_yzmp    =  pYonghuset->m_yzmp;
		m_xzms    =  pYonghuset->m_xzms;

		COleVariant vtime1(pYonghuset->m_qssj);
		vtime1.ChangeType(VT_DATE);
		m_tmfrom = vtime1;

		COleVariant vtime2(pYonghuset->m_jzsj);
		vtime2.ChangeType(VT_DATE);
		m_tmto= vtime2;

		m_sn        =  pYonghuset->m_sn;

		m_dtkyc1    =  pYonghuset->m_dtkyc1;
		m_dtkyc2    =  pYonghuset->m_dtkyc2;
		m_dtkyc3    =  pYonghuset->m_dtkyc3;
		m_dtkyc4    =  pYonghuset->m_dtkyc4;


		m_dtkycxz1    =  pYonghuset->m_dtkycxz1;
		m_dtkycxz2    =  pYonghuset->m_dtkycxz2;
		m_dtkycxz3    =  pYonghuset->m_dtkycxz3;
		m_dtkycxz4    =  pYonghuset->m_dtkycxz4;
	
		m_strElv1 = LPDBManage->GetElevatorNameByID(pYonghuset->m_kydt1);
		m_strElv2 = LPDBManage->GetElevatorNameByID(pYonghuset->m_kydt2);
		m_strElv3 = LPDBManage->GetElevatorNameByID(pYonghuset->m_kydt3);
		m_strElv4 = LPDBManage->GetElevatorNameByID(pYonghuset->m_kydt4);

		m_iOperType    =  pYonghuset->m_czfs;

		m_status    =  pYonghuset->m_status;
		m_hmdcs    =  pYonghuset->m_hmdcs;
		UpdateData(FALSE);
	}

	return TRUE;
}


BOOL CCustermerInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//if (m_cType == ADD_TYPE)
	//	SetWindowText("增加业主卡");
	//else
		SetWindowText("业主卡");

	//CArray<CSuoset*,CSuoset*> arr;
	//LPDBManage->GetElevatorList(arr);

	if(!m_bUpdateData)
	{
		SetPara2(FALSE);

		long lStatus = ADD_TYPE;
		CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(m_ID, lStatus);
	}

	CSuoset *pSuoset = NULL; 
	long lCode = 0;

	CArray<CSuoset*, CSuoset*> arr;
	LPDBManage->GetElevatorList(arr);
	for (int i=0; i<arr.GetSize(); i++)
	{
		CSuoset* pSuoset = arr.GetAt(i);
		ASSERT(pSuoset);
		m_cElv1.AddString(pSuoset->m_dtmc);
		m_cElv2.AddString(pSuoset->m_dtmc);
		m_cElv3.AddString(pSuoset->m_dtmc);
		m_cElv4.AddString(pSuoset->m_dtmc);
	}

	if(m_cType == ADD_TYPE)
	{
		((CButton*)GetDlgItem(IDC_BTN_READCARD))->ShowWindow(SW_HIDE);
	}
	//POSITION  pos= LPDBManage->m_mapElevator.GetStartPosition();
	//while(pos)
	//{
	//	LPDBManage->m_mapElevator.GetNextAssoc(pos,lCode,pSuoset);
	//	ASSERT(pSuoset);
	//	m_cElv1.AddString(pSuoset->m_dtmc);
	//	m_cElv2.AddString(pSuoset->m_dtmc);
	//	m_cElv3.AddString(pSuoset->m_dtmc);
	//	m_cElv4.AddString(pSuoset->m_dtmc);
	//}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void   CCustermerInfoDlg::SetPara(char cType, long lID)
{
	m_ID    = lID;
	m_cType = cType;
}

//处理的使用限制
void CCustermerInfoDlg::OnBnClickedRadioNum()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CCustermerInfoDlg::OnBnClickedButtonFin()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara2(TRUE);
	CString strMsg;
	long lStatus = ADD_TYPE;
	CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(m_ID, lStatus);
	
	BOOL bWriteRet = WirteIC(pYonghuset);
	
	BOOL bRetDatabase = FALSE;
	if(bWriteRet)
	{
		bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,m_cType);
		if(!bRetDatabase)
		{
			bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,lStatus);
		}
	}

	//if (LPDBManage->OpereCustomer(pYonghuset,m_cType) && WirteIC(pYonghuset) )
	if (bWriteRet && bRetDatabase )
	{
		
		if(m_cType == ADD_TYPE)
			strMsg.Format("新增业主%s卡成功!\r\n", pYonghuset->m_yzmc);
		else
			strMsg.Format("修改业主%s卡成功!\r\n", pYonghuset->m_yzmc);

		strMsg.Format("业主%s卡生成成功!\r\n", pYonghuset->m_yzmc);


		SetOutPutInfo(strMsg);

		//m_strOutput = GetCardInfo(pYonghuset);
		//m_strOutput = strMsg + m_strOutput;

		log_info(strMsg);

		AfxMessageBox(strMsg);
		if(m_cType == ADD_TYPE)
		{
			m_ID = LPDBManage->GetCustermerID();
			pYonghuset = LPDBManage->GetCustermerByID(m_ID, lStatus);
			m_yzkh = m_ID;
			//ResetDlgData();
		}
		//if(m_pParent)
		//	m_pParent->OnBnClickedBtnRefresh();
	}
	else
	{
		strMsg.Format("业主%s卡生成失败!", pYonghuset->m_yzmc);
		SetOutPutInfo(strMsg);		
	}
	UpdateData(FALSE);
	return;
}

BOOL  CCustermerInfoDlg::WirteIC(CYonghuset *pYonghuset, UINT iStatus/* = 0*/, UINT iForbidenID/* = 0*/)
{
	if(NULL == pYonghuset)
		return FALSE;
	unsigned char buf[80] = {0};
	memset(buf, 0, sizeof(buf));
	/////////////////////
	buf[0] = 2;  //写命令字
	buf[1] = 0xff;
	buf[2] = 0xff;
	buf[3] = 0xff;
	buf[4] = 0xff; //卡号
	buf[5] = 0x01; //卡类型
	//buf[6] = 0x00; //子卡类型
	buf[6] = iStatus & 0xFF; //子卡类型
	buf[7] = (pYonghuset->m_ID >> 16) & 0xff;
	buf[8] = (pYonghuset->m_ID >> 8) & 0xff;
	buf[9] = pYonghuset->m_ID & 0xff;
	buf[10] = pYonghuset->m_fjbh / 256;
	buf[11] = pYonghuset->m_fjbh % 256;
	buf[12] = pYonghuset->m_xzms + 1;
	buf[13] = 0;//乘梯权限模式

	buf[14] = (m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	buf[15] = m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	buf[16] = m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	buf[17] = m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	buf[18] = m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;

	buf[19] = (m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	buf[20] = m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	buf[21] = m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	buf[22] = m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	buf[23] = m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;
	
	buf[24] = m_sycs/256;
	buf[25] = m_sycs%256;

	buf[26] = pYonghuset->m_kydt1;
	LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz1,dtkycxznum[0]);
	LPSerialProtocol->charToBytes(dtkycxznum[0],buf+27);
	buf[35] = pYonghuset->m_kydt2;
	LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz2,dtkycxznum[1]);
	LPSerialProtocol->charToBytes(dtkycxznum[1],buf+36);
	buf[44] = pYonghuset->m_kydt3;
	LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz3,dtkycxznum[2]);
	LPSerialProtocol->charToBytes(dtkycxznum[2],buf+45);
	buf[53] = pYonghuset->m_kydt4;
	LPSerialProtocol->stringToBytes(pYonghuset->m_dtkycxz4,dtkycxznum[3]);
	LPSerialProtocol->charToBytes(dtkycxznum[3],buf+54);

	buf[62] = 0x03;
	buf[63] = (iForbidenID >> 16 ) & 0xFF;
	buf[64] = (iForbidenID >> 8 ) & 0xFF;
	buf[65] = iForbidenID  & 0xFF;
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->WriteUserData(buf, 66);
	return bRet;
}

CString	CCustermerInfoDlg::GetCardInfo(CYonghuset *p)
{
	CString szInfo, szTemp;
	szInfo.Format("卡片类型：业主卡\r\n");

	szTemp.Format("业主卡卡号：%d\r\n", m_yzkh);
	szInfo += szTemp;

	szTemp.Format("业主名称：%s\r\n", m_yzmc);
	szInfo += szTemp;

	szTemp.Format("手机号码：%s\r\n", m_sjhm);
	szInfo += szTemp;

	szTemp.Format("房间编号：%d\r\n", m_fjbh);
	szInfo += szTemp;
	
	if(m_xzms == 0)
	{
		szTemp.Format("限制模式：次数限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用次数：%d\r\n", m_sycs);
		szInfo += szTemp;
	}
	else if(m_xzms == 1)
	{
		szTemp.Format("限制模式：时间限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用时间：从%d-%d-%d \r\n     到 %d-%d-%d\r\n", 
			m_tmfrom.GetYear(), 
			m_tmfrom.GetMonth(), 
			m_tmfrom.GetDay(),
			m_tmto.GetYear(), 
			m_tmto.GetMonth(), 
			m_tmto.GetDay());
		szInfo += szTemp;
	}
	else if(m_xzms == 2)
	{
		szTemp.Format("限制模式：次数和时间\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用次数：%d\r\n", m_sycs);
		szInfo += szTemp;
		szTemp.Format("   使用时间：从%d-%d-%d \r\n     到 %d-%d-%d\r\n", 
			m_tmfrom.GetYear(), 
			m_tmfrom.GetMonth(), 
			m_tmfrom.GetDay(),
			m_tmto.GetYear(), 
			m_tmto.GetMonth(), 
			m_tmto.GetDay());
		szInfo += szTemp;

	}

	if(!m_strElv1.IsEmpty())
	{
		szTemp.Format("可用电梯1：%s\r\n", m_strElv1);
		szInfo += szTemp;
		if(!m_dtkyc1.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", m_dtkyc1);
			szInfo += szTemp;
		}
	}

	if(!m_strElv2.IsEmpty())
	{
		szTemp.Format("可用电梯2：%s\r\n", m_dtkyc2);
		szInfo += szTemp;
		if(!m_dtkyc2.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n", m_dtkyc2);
			szInfo += szTemp;
		}
	}
	if(!m_strElv3.IsEmpty())
	{
		szTemp.Format("可用电梯3：%s\r\n", m_dtkyc3);
		szInfo += szTemp;
		if(!m_dtkyc3.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n",  m_dtkyc3);
			szInfo += szTemp;
		}
	}
	if(!m_strElv4.IsEmpty())
	{
		szTemp.Format("可用电梯4：%s\r\n", m_strElv4);
		szInfo += szTemp;
		if(!m_dtkyc4.IsEmpty())
		{
			szTemp.Format("  可用层：%s\r\n",  m_dtkyc4);
			szInfo += szTemp;
		}
	}
	return szInfo;
}

void  CCustermerInfoDlg::SetOutPutInfo(CString strInfo)
{
	CString strTemp;

	if(m_bReadCardFlag)
	{
		m_strOutput = "";
		m_bReadCardFlag = FALSE;
	}

	strTemp = strInfo +"\r\n";
	m_strOutput = strTemp + m_strOutput;

	UpdateData(FALSE);
}

void   CCustermerInfoDlg::ChoiceElv(CString strElv,CString &strDtkyc,CString &strDtkycxz)
{
	if (strElv.IsEmpty())
	{
		MessageBox("请先选择所乘坐的电梯！");
		return ;
	}

	CSuoset *pSuoset = LPDBManage->GetElevatorByName(strElv);

	CFloorDlg dlg;
	dlg.SetPara(FLOOR_CHIOCE,pSuoset->m_dtbh);
	dlg.sumlc= pSuoset->m_dtcs;
	dlg.qslc = pSuoset->m_qslc;
	dlg.gglc = pSuoset->m_gglc;
	dlg.kylc= strDtkycxz;

	if(dlg.DoModal()==IDOK)
	{
		strDtkyc  = dlg.kylc;
		strDtkycxz =dlg.dtkycxz;
		UpdateData(FALSE);
	}
}

void CCustermerInfoDlg::OnBnClickedFloorChoice()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv1,m_dtkyc1,m_dtkycxz1);
}

void CCustermerInfoDlg::OnBnClickedFloorChoice2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv2,m_dtkyc2,m_dtkycxz2);
}


void CCustermerInfoDlg::OnBnClickedFloorChoice3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv3,m_dtkyc3,m_dtkycxz3);
}


void CCustermerInfoDlg::OnBnClickedFloorChoice4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv4,m_dtkyc4,m_dtkycxz4);
}


void CCustermerInfoDlg::OnBnClickedRepairCard2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetOutPutInfo("补卡保存失败！");
}


void CCustermerInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CCustermerInfoDlg::OnBnClickedBtnQuerycard()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(TRUE);
	char chBuf[100] = {0};
	DWORD dwRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadSerialNo();
	if(dwRet > 0)
	{
		_ultoa(dwRet, chBuf, 10);
		m_sn.Format("%s", chBuf);
	}
	UpdateData(FALSE);
}

void CCustermerInfoDlg::OnBnClickedUserinfoCardSn()
{
	// TODO: 在此添加控件通知处理程序代码	
	UpdateData(TRUE);
	char chBuf[100] = {0};
	DWORD dwRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadSerialNo();
	if(dwRet > 0)
	{
		_ultoa(dwRet, chBuf, 10);
		m_sn.Format("%s", chBuf);
	}
	UpdateData(FALSE);
}


void CCustermerInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CCustermerInfoDlg::OnBnClickedRadio7()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CCustermerInfoDlg::OnBnClickedRadio16()
{
	// TODO: 在此添加控件通知处理程序代码
	m_iOperType=1;
}
void CCustermerInfoDlg::SetCustomerData(const CYonghuset& customerData)
{
	m_ID      =  customerData.m_ID;
	m_yzkh    =  customerData.m_yzkh;
	m_yzmc    =  customerData.m_yzmc;
	m_sjhm    =  customerData.m_sjhm;
	m_fjbh    =  customerData.m_fjbh;
	m_sycs    =  customerData.m_sycs;
	m_yzmp    =  customerData.m_yzmp;
	m_xzms    =  customerData.m_xzms;

	//COleVariant vtime1(customerData.m_qssj);
	//vtime1.ChangeType(VT_DATE);
	//m_tmfrom = vtime1;

	//COleVariant vtime2(customerData.m_jzsj);
	//vtime2.ChangeType(VT_DATE);
	//m_tmto= vtime2;
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	CString szTemp = customerData.m_qssj;
	sscanf(szTemp.GetBuffer(0), "%d-%d-%d %d:%d:%d",
		&nYear,
		&nMonth,
		&nDate,
		&nHour,
		&nMin,
		&nSec);   
	szTemp.ReleaseBuffer();
	if(nMonth == 0)
		nMonth = 1;
	if(nDate == 0)
		nDate = 1;
	if(nDate > 31)
		nDate = 31;
	m_tmfrom.SetDate(nYear, nMonth, nDate);

	//COleVariant vtime2(pQusetData.m_jzsj);
	//vtime2.ChangeType(VT_DATE);
	//m_tmto = vtime2;
	szTemp = customerData.m_jzsj;
	sscanf(szTemp.GetBuffer(0), "%d-%d-%d %d:%d:%d",
		&nYear,
		&nMonth,
		&nDate,
		&nHour,
		&nMin,
		&nSec);   
	szTemp.ReleaseBuffer();
	if(nMonth == 0)
		nMonth = 1;
	if(nDate == 0)
		nDate = 1;
	if(nDate > 31)
		nDate = 31;
	m_tmto.SetDate(nYear, nMonth, nDate);
	m_sn        =  customerData.m_sn;

	m_dtkyc1    =  customerData.m_dtkyc1;
	m_dtkyc2    =  customerData.m_dtkyc2;
	m_dtkyc3    =  customerData.m_dtkyc3;
	m_dtkyc4    =  customerData.m_dtkyc4;


	m_dtkycxz1    =  customerData.m_dtkycxz1;
	m_dtkycxz2    =  customerData.m_dtkycxz2;
	m_dtkycxz3    =  customerData.m_dtkycxz3;
	m_dtkycxz4    =  customerData.m_dtkycxz4;

	m_strElv1 = LPDBManage->GetElevatorNameByID(customerData.m_kydt1);
	m_strElv2 = LPDBManage->GetElevatorNameByID(customerData.m_kydt2);
	m_strElv3 = LPDBManage->GetElevatorNameByID(customerData.m_kydt3);
	m_strElv4 = LPDBManage->GetElevatorNameByID(customerData.m_kydt4);

	m_iOperType    =  customerData.m_czfs;

	m_status    =  customerData.m_status;
	m_hmdcs    =  customerData.m_hmdcs;

	m_bUpdateData = TRUE;
}

void CCustermerInfoDlg::ResetDlgData()
{
	m_yzmc.Empty();
	m_sjhm.Empty();
	m_fjbh = 0;
	m_sycs  = 500;
	m_yzmp.Empty();
	m_xzms = 0;

	CTime tmNow = ::time(NULL);
	m_tmfrom.SetDateTime(tmNow.GetYear(), tmNow.GetMonth(), tmNow.GetDay(), tmNow.GetHour(), tmNow.GetMinute(), tmNow.GetSecond());
	m_tmto.SetDateTime(tmNow.GetYear(), tmNow.GetMonth(), tmNow.GetDay(), tmNow.GetHour(), tmNow.GetMinute(), tmNow.GetSecond());

	m_sn.Empty();

	m_dtkyc1.Empty();
	m_dtkyc2.Empty();
	m_dtkyc3.Empty();
	m_dtkyc4.Empty();


	m_dtkycxz1.Empty();
	m_dtkycxz2.Empty();
	m_dtkycxz3.Empty();
	m_dtkycxz4.Empty();

	m_strElv1.Empty();
	m_strElv2.Empty();
	m_strElv3.Empty();
	m_strElv4.Empty();

	m_iOperType = 0;

	m_hmdcs = 50;
}

void CCustermerInfoDlg::SetParemtDlg(CCustomerDlg* pParent)
{
	m_pParent = pParent;
}


void CCustermerInfoDlg::OnBnClickedBtnReplace()
{
	// TODO: 在此添加控件通知处理程序代码	
	SetPara2(TRUE);
	CString strMsg;
	BOOL bRetDatabase = FALSE;
	long lStatus = ADD_TYPE;
	CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(m_ID, lStatus);
	//禁用掉
	pYonghuset->m_status = 1;
	bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,MOD_TYPE);
	if(!bRetDatabase)
		bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,MOD_TYPE);

	//增加新卡
	long lNewID = LPDBManage->GetCustermerID();
	m_yzkh = lNewID;
	pYonghuset->m_ID = lNewID;

	pYonghuset->m_yzkh = lNewID;

	pYonghuset->m_status = 0;

	BOOL bWriteRet = WirteIC(pYonghuset, 3, m_ID);

	if(bWriteRet)
	{
		bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,ADD_TYPE);
		if(!bRetDatabase)
			bRetDatabase = LPDBManage->OpereCustomer(pYonghuset,MOD_TYPE);
	}

	if (bWriteRet && bRetDatabase )
	{
		strMsg.Format("业主%s补卡成功!", pYonghuset->m_yzmc);

		SetOutPutInfo(strMsg);

		log_info(strMsg);

		m_yzkh = lNewID;

		m_ID = lNewID;

		SetOutPutInfo(strMsg);
		//m_strOutput = GetCardInfo(pYonghuset);
		//m_strOutput = strMsg + m_strOutput;

		AfxMessageBox(strMsg);

		//if(m_pParent)
		//	m_pParent->OnBnClickedBtnRefresh();
	}
	else
	{
		strMsg.Format("业主%s补卡失败!", pYonghuset->m_yzmc);
		SetOutPutInfo(strMsg);
	}
	UpdateData(FALSE);
	return;
}

void CCustermerInfoDlg::OnBnClickedBtnReadcard()
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
			long nID = (pUserCardData->btCardNo[0]<<16) + (pUserCardData->btCardNo[1]<<8) + pUserCardData->btCardNo[2];

			long lStatus = ADD_TYPE;
			CYonghuset *pYonghuset = LPDBManage->GetCustermerByID(nID, lStatus);

			SetPara(lStatus, nID);

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

			m_bReadCardFlag = TRUE;
			SetCustomerData(customerData);

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
				szTemp.Format("   剩余次数：%d\r\n", (pUserCardData->btCounts[0] << 8) + pUserCardData->btCounts[1] );
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
				szTemp.Format("   剩余次数：%d\r\n", (pUserCardData->btCounts[0] << 8) + pUserCardData->btCounts[1]);
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
					CString szFloor = ParseElevatorFloor(pUserCardData->btFloor_1[i], i, p->m_qslc);
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
					CString szFloor = ParseElevatorFloor(pUserCardData->btFloor_2[i], i, p->m_qslc);
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
			m_strOutput = szInfo;
			UpdateData(FALSE);
		}
	}
	else
		AfxMessageBox("获取用户卡信息失败！");
}
