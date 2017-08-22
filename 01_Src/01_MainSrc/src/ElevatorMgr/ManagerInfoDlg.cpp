// ManagerInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "ManagerInfoDlg.h"
#include "afxdialogex.h"
#include "ManagerDlg.h"

#include "FloorDlg.h"
// CManagerInfoDlg 对话框
unsigned char dtkycxznum1[4][64];

IMPLEMENT_DYNAMIC(CManagerInfoDlg, CDialogEx)

CManagerInfoDlg::CManagerInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CManagerInfoDlg::IDD, pParent)
	, m_glymc(_T(""))
	, m_glykh(10)
	, m_sycs(500)
	, m_tmfrom(COleDateTime::GetCurrentTime())
	, m_tmto(COleDateTime::GetCurrentTime())
	, m_dtkyc1(_T(""))
	, m_dtkyc2(_T(""))
	, m_dtkyc3(_T(""))
	, m_dtkyc4(_T(""))
	, m_strElv1(_T(""))
	, m_strElv2(_T(""))
	, m_strElv3(_T(""))
	, m_strElv4(_T(""))
	, m_strOutput(_T(""))
	, m_xzms(0)
	, m_ctqxms(0)
	, m_sjhm(_T(""))
	, m_pParent(NULL)
	, m_bUpdateData(FALSE)
	, m_ID(1)
	,m_bReadCardFlag(FALSE)
{
	m_sn.Empty();
}

CManagerInfoDlg::~CManagerInfoDlg()
{
}

void CManagerInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_glymc);
	DDX_Text(pDX, IDC_EDIT12, m_glykh);
	DDX_Text(pDX, IDC_EDIT7, m_sycs);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_tmfrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_tmto);
	DDX_Text(pDX, IDC_EDIT4, m_dtkyc1);
	DDX_Text(pDX, IDC_EDIT5, m_dtkyc2);
	DDX_Text(pDX, IDC_EDIT6, m_dtkyc3);
	DDX_Text(pDX, IDC_EDIT18, m_dtkyc4);
	DDX_Control(pDX, IDC_COMBO1, m_cElv1);
	DDX_CBString(pDX, IDC_COMBO1, m_strElv1);
	DDX_Control(pDX, IDC_COMBO2, m_cElv2);
	DDX_CBString(pDX, IDC_COMBO2, m_strElv2);
	DDX_Control(pDX, IDC_COMBO3, m_cElv3);
	DDX_CBString(pDX, IDC_COMBO3, m_strElv3);
	DDX_Control(pDX, IDC_COMBO4, m_cElv4);
	DDX_CBString(pDX, IDC_COMBO4, m_strElv4);
	DDX_Text(pDX, IDC_EDIT_CUSTOMER_SN, m_sn);
	DDX_Text(pDX, IDC_EDIT14, m_strOutput);
	DDX_Radio(pDX, IDC_RADIO4, m_xzms);
	DDX_Radio(pDX, IDC_RADIO1, m_ctqxms);
	DDX_Text(pDX, IDC_EDIT2, m_sjhm);
}


BEGIN_MESSAGE_MAP(CManagerInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDD_MANAGER_FLOOR_CHOICE, &CManagerInfoDlg::OnBnClickedManagerFloorChoice)
	ON_BN_CLICKED(IDD_SAVEDATA, &CManagerInfoDlg::OnBnClickedSavedata)
	ON_BN_CLICKED(IDD_MANAGER_FLOOR_CHOICE2, &CManagerInfoDlg::OnBnClickedManagerFloorChoice2)
	ON_BN_CLICKED(IDD_MANAGER_FLOOR_CHOICE3, &CManagerInfoDlg::OnBnClickedManagerFloorChoice3)
	ON_BN_CLICKED(IDD_MANAGER_FLOOR_CHOICE4, &CManagerInfoDlg::OnBnClickedManagerFloorChoice4)
	ON_BN_CLICKED(IDD_REPAIR_CRAD3, &CManagerInfoDlg::OnBnClickedRepairCrad3)
	ON_BN_CLICKED(IDOK, &CManagerInfoDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CManagerInfoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDD_USERINFO_CARD_SN2, &CManagerInfoDlg::OnBnClickedUserinfoCardSn2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO4, &CManagerInfoDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO3, &CManagerInfoDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO5, &CManagerInfoDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO1, &CManagerInfoDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CManagerInfoDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDD_BTN_REPLACE, &CManagerInfoDlg::OnBnClickedBtnReplace)
END_MESSAGE_MAP()


// CManagerInfoDlg 消息处理程序
void   CManagerInfoDlg::ChoiceElv(CString strElv,CString &strDtkyc,CString &strDtkycxz)
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

BOOL CManagerInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//if (m_cType == ADD_TYPE)
	//	SetWindowText("管理员卡");
	//else
		SetWindowText("管理员卡");
// 
// 	CArray<CSuoset*,CSuoset*> arr;
// 	LPDBManage->GetElevatorList(arr);
	if(!m_bUpdateData)
	{
		SetPara2(FALSE);
		long lStatus = ADD_TYPE;
		Cquset *pQuset = LPDBManage->GetManagerByID(m_ID, lStatus);
	}
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
	//CSuoset *pSuoset = NULL; long lCode = 0;
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
	//SetTimer(1, 500, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CManagerInfoDlg::SetPara(char cType, long lID)
{
	m_ID    = lID;
	m_cType = cType;
}
BOOL  CManagerInfoDlg::SetPara2(BOOL bSave)
{
	long lStatus = ADD_TYPE;
	Cquset *pQuset = LPDBManage->GetManagerByID(m_ID, lStatus);
	CString strTemp;
	if (bSave)
	{
		UpdateData(TRUE);
		pQuset->m_ID      =   m_ID;
		pQuset->m_glykh    =  m_glykh;
		pQuset->m_glymc    =  m_glymc;
		pQuset->m_xzms    =   m_xzms;
		pQuset->m_sycs    =   m_sycs;
		 
		pQuset->m_ctqxms    =  m_ctqxms;;

		pQuset->m_qssj    =  m_tmfrom.Format("%y-%m-%d %H:%M:%S");
		pQuset->m_jzsj    =  m_tmto.Format("%y-%m-%d %H:%M:%S");
		//pYonghuset->m_tmto      =  m_tmto;

		pQuset->m_sn      =  m_sn;
		pQuset->m_sjhm    =  m_sjhm;

		pQuset->m_dtkyc1    =  m_dtkyc1;
		pQuset->m_dtkyc2    =  m_dtkyc2;
		pQuset->m_dtkyc3    =  m_dtkyc3;
		pQuset->m_dtkyc4    =  m_dtkyc4;

		pQuset->m_dtkycxz1    =  m_dtkycxz1;
		pQuset->m_dtkycxz2    =  m_dtkycxz2;
		pQuset->m_dtkycxz3    =  m_dtkycxz3;
		pQuset->m_dtkycxz4    =  m_dtkycxz4;


		if (!m_strElv1.IsEmpty())
		{
			pQuset->m_kydt1    =  LPDBManage->GetElevatorByName(m_strElv1)->m_dtbh;
		}

		if (!m_strElv2.IsEmpty())
		{
			pQuset->m_kydt2    =  LPDBManage->GetElevatorByName(m_strElv2)->m_dtbh;
		}

		if (!m_strElv3.IsEmpty())
		{
			pQuset->m_kydt3    =  LPDBManage->GetElevatorByName(m_strElv3)->m_dtbh;
		}

		if (!m_strElv4.IsEmpty())
		{
			pQuset->m_kydt4    =  LPDBManage->GetElevatorByName(m_strElv4)->m_dtbh;
		}
	}
	else
	{
		m_ID       =  pQuset->m_ID;
		m_glykh    =  pQuset->m_glykh;
		m_glymc    =  pQuset->m_glymc;
		m_xzms     =  pQuset->m_xzms;;
		m_sycs    =  pQuset->m_sycs;
		m_ctqxms   = pQuset->m_ctqxms;

		COleVariant vtime1(pQuset->m_qssj);
		vtime1.ChangeType(VT_DATE);
		m_tmfrom = vtime1;

		COleVariant vtime2(pQuset->m_jzsj);
		vtime2.ChangeType(VT_DATE);
		m_tmto = vtime2;

		m_sn        =  pQuset->m_sn;
		m_sjhm      =  pQuset->m_sjhm;

		m_dtkyc1    =  pQuset->m_dtkyc1;
		m_dtkyc2    =  pQuset->m_dtkyc2;
		m_dtkyc3    =  pQuset->m_dtkyc3;
		m_dtkyc4    =  pQuset->m_dtkyc4;


		m_dtkycxz1    =  pQuset->m_dtkycxz1;
		m_dtkycxz2    =  pQuset->m_dtkycxz2;
		m_dtkycxz3    =  pQuset->m_dtkycxz3;
		m_dtkycxz4    =  pQuset->m_dtkycxz4;

		m_strElv1 = LPDBManage->GetElevatorNameByID(pQuset->m_kydt1);
		m_strElv2 = LPDBManage->GetElevatorNameByID(pQuset->m_kydt2);
		m_strElv3 = LPDBManage->GetElevatorNameByID(pQuset->m_kydt3);
		m_strElv4 = LPDBManage->GetElevatorNameByID(pQuset->m_kydt4);

		UpdateData(FALSE);
	}
	return TRUE;
}

void CManagerInfoDlg::SetMgrData(const Cquset& pQusetData)
{
	m_ID       =  pQusetData.m_ID;
	m_glykh    =  pQusetData.m_glykh;
	m_glymc    =  pQusetData.m_glymc;
	m_xzms     =  pQusetData.m_xzms;;
	m_sycs    =  pQusetData.m_sycs;
	m_ctqxms	= pQusetData.m_ctqxms;

	//COleVariant vtime1(pQusetData.m_qssj);
	//vtime1.ChangeType(VT_DATE);	
	//m_tmfrom = vtime1;
	int    nYear,    nMonth,    nDate,    nHour,    nMin,    nSec;   
	CString szTemp = pQusetData.m_qssj;
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
	if(nDate > 30)
		nDate = 30;
	if(nMonth == 2 && nDate > 28)
			nDate = 28;
	m_tmfrom.SetDate(nYear, nMonth, nDate);

	//COleVariant vtime2(pQusetData.m_jzsj);
	//vtime2.ChangeType(VT_DATE);
	//m_tmto = vtime2;
	szTemp = pQusetData.m_jzsj;
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
	if(nDate > 30)
		nDate = 30;
	if(nMonth == 2 && nDate > 28)
		nDate = 28;
	m_tmto.SetDate(nYear, nMonth, nDate);

	m_sn        =  pQusetData.m_sn;
	m_sjhm      =  pQusetData.m_sjhm;

	m_dtkyc1    =  pQusetData.m_dtkyc1;
	m_dtkyc2    =  pQusetData.m_dtkyc2;
	m_dtkyc3    =  pQusetData.m_dtkyc3;
	m_dtkyc4    =  pQusetData.m_dtkyc4;


	m_dtkycxz1    =  pQusetData.m_dtkycxz1;
	m_dtkycxz2    =  pQusetData.m_dtkycxz2;
	m_dtkycxz3    =  pQusetData.m_dtkycxz3;
	m_dtkycxz4    =  pQusetData.m_dtkycxz4;

	m_strElv1 = LPDBManage->GetElevatorNameByID(pQusetData.m_kydt1);
	m_strElv2 = LPDBManage->GetElevatorNameByID(pQusetData.m_kydt2);
	m_strElv3 = LPDBManage->GetElevatorNameByID(pQusetData.m_kydt3);
	m_strElv4 = LPDBManage->GetElevatorNameByID(pQusetData.m_kydt4);

	m_bUpdateData = TRUE;
}
void  CManagerInfoDlg::SetOutPutInfo(CString strInfo)
{
	UpdateData(TRUE);

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


void CManagerInfoDlg::OnBnClickedManagerFloorChoice()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv1,m_dtkyc1,m_dtkycxz1);
}

void CManagerInfoDlg::OnBnClickedManagerFloorChoice2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv2,m_dtkyc2,m_dtkycxz2);
}


void CManagerInfoDlg::OnBnClickedManagerFloorChoice3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv3,m_dtkyc3,m_dtkycxz3);
}


void CManagerInfoDlg::OnBnClickedManagerFloorChoice4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	ChoiceElv(m_strElv4,m_dtkyc4,m_dtkycxz4);
}

void CManagerInfoDlg::OnBnClickedSavedata()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara2(TRUE);

	long lStatus = ADD_TYPE;

	Cquset *pQuset  = LPDBManage->GetManagerByID(m_ID, lStatus);

	BOOL bWriteRet = WirteIC(pQuset);
	BOOL bDatabaseRet = FALSE;
	if(bWriteRet)
	{
		bDatabaseRet = LPDBManage->OperManager(pQuset,m_cType);
		if(!bDatabaseRet)
		{
			bDatabaseRet = LPDBManage->OperManager(pQuset,lStatus);
		}
	}

	CString strMsg;
	//if (LPDBManage->OperManager(pQuset,m_cType) && WirteIC(pQuset) )
	if(bWriteRet && bDatabaseRet)
	{
		if(m_cType == ADD_TYPE)
			strMsg.Format("新增管理员%s卡成功!\r\n", pQuset->m_glymc);
		else
			strMsg.Format("修改管理员%s卡成功!\r\n", pQuset->m_glymc);


		//m_strOutput = GetCardInfo(pQuset);

		//m_strOutput = strMsg + m_strOutput;

		SetOutPutInfo(strMsg);
		AfxMessageBox(strMsg);
		if(m_cType == ADD_TYPE)
		{
			m_ID = LPDBManage->GetManagerID();
			pQuset = LPDBManage->GetManagerByID(m_ID, lStatus);
			m_glykh = m_ID;
			//ResetDlgData();
		}
		//刷新下界面
		if(m_pParent)
			m_pParent->OnBnClickedBtnRefresh();
	}
	else
	{
		strMsg.Format("修改管理员%s卡失败!", pQuset->m_glymc);
		SetOutPutInfo(strMsg);
	}
	UpdateData(FALSE);
}

void CManagerInfoDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	long lStatus = ADD_TYPE;

	Cquset *pQuset  = LPDBManage->GetManagerByID(m_ID, lStatus);
	if (m_cType == ADD_TYPE )
	{
		LPDBManage->OperManager(pQuset,DEL_TYPE);
	}
	CDialogEx::OnCancel();
}


void CManagerInfoDlg::OnBnClickedRepairCrad3()
{
	// TODO: 在此添加控件通知处理程序代码
	SetOutPutInfo("补卡保存失败！");
}


void CManagerInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	SetOutPutInfo("读卡保存失败！");
	CDialogEx::OnOK();
}

BOOL CManagerInfoDlg::WirteIC(Cquset *pQuset, UINT iSatus/* = 0*/, UINT iForbidenID/* = 0*/)
{
	unsigned char buf[80] = {0};
	long timeout=0;

	//m_tmfrom=time;
	/////////////////////
	buf[0]=2;  //写命令字
	buf[1]=0xff;
	buf[2]=0xff;
	buf[3]=0xff;
	buf[4]=0xff; //卡号
	buf[5]=0x02; //卡类型
	//buf[6]=0x00; //子卡类型
	buf[6]=iSatus & 0xFF; //子卡类型
	buf[7]=m_glykh / 65536;
	buf[8]=m_glykh % 65536 / 256;
	buf[9]=m_glykh % 65536 % 256;
	buf[10]=0;//m_fjbh/256;
	buf[11]=0;//m_fjbh%256;
	buf[12]=m_xzms;
	buf[13]=m_ctqxms;//乘梯权限模式

	buf[14]=(m_tmfrom.GetYear()-2000)/10*16+(m_tmfrom.GetYear()-2000)%10;
	buf[15]=m_tmfrom.GetMonth()/10*16+m_tmfrom.GetMonth()%10;
	buf[16]=m_tmfrom.GetDay()/10*16+m_tmfrom.GetDay()%10;
	buf[17]=m_tmfrom.GetHour()/10*16+m_tmfrom.GetHour()%10;
	buf[18]=m_tmfrom.GetMinute()/10*16+m_tmfrom.GetMinute()%10;

	buf[19]=(m_tmto.GetYear()-2000)/10*16+(m_tmto.GetYear()-2000)%10;
	buf[20]=m_tmto.GetMonth()/10*16+m_tmto.GetMonth()%10;
	buf[21]=m_tmto.GetDay()/10*16+m_tmto.GetDay()%10;
	buf[22]=m_tmto.GetHour()/10*16+m_tmto.GetHour()%10;
	buf[23]=m_tmto.GetMinute()/10*16+m_tmto.GetMinute()%10;

	buf[24]=m_sycs/256;
	buf[25]=m_sycs%256;
	buf[26]=pQuset->m_kydt1;
	LPSerialProtocol->stringToBytes(m_dtkycxz1,dtkycxznum1[0]);
	LPSerialProtocol->charToBytes(dtkycxznum1[0],buf+27);
	buf[35]=pQuset->m_kydt2;
	LPSerialProtocol->stringToBytes(m_dtkycxz2,dtkycxznum1[1]);
	LPSerialProtocol->charToBytes(dtkycxznum1[1],buf+36);
	buf[44]=pQuset->m_kydt3;
	LPSerialProtocol->stringToBytes(m_dtkycxz3,dtkycxznum1[2]);
	LPSerialProtocol->charToBytes(dtkycxznum1[2],buf+45);
	buf[53]=pQuset->m_kydt4;
	LPSerialProtocol->stringToBytes(m_dtkycxz4,dtkycxznum1[3]);
	LPSerialProtocol->charToBytes(dtkycxznum1[3],buf+54);

	//禁止的卡号
	buf[62] = 0x03;
	buf[63] = (iForbidenID >> 16 ) & 0xFF;
	buf[64] = (iForbidenID >> 8 ) & 0xFF;
	buf[65] = iForbidenID  & 0xFF;
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->WriteManagerData(buf, 66);
	return bRet;
}


void CManagerInfoDlg::OnBnClickedUserinfoCardSn2()
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


void CManagerInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 1)
	{
		UpdateData(FALSE);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CManagerInfoDlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
}


void CManagerInfoDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_xzms = 1;
}



void CManagerInfoDlg::OnBnClickedRadio5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_xzms = 2;
}


void CManagerInfoDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctqxms = 0;
}


void CManagerInfoDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ctqxms = 1;
}

void CManagerInfoDlg::ResetDlgData()
{
	m_glymc.Empty();
	CTime tmNow = ::time(NULL);
	m_tmfrom.SetDateTime(tmNow.GetYear(), tmNow.GetMonth(), tmNow.GetDay(), tmNow.GetHour(), tmNow.GetMinute(), tmNow.GetSecond());
	m_tmto.SetDateTime(tmNow.GetYear(), tmNow.GetMonth(), tmNow.GetDay(), tmNow.GetHour(), tmNow.GetMinute(), tmNow.GetSecond());
	m_dtkyc1.Empty();
	m_dtkyc2.Empty();
	m_dtkyc3.Empty();
	m_dtkyc4.Empty();

	m_dtkycxz1.Empty();
	m_dtkycxz2.Empty();
	m_dtkycxz3.Empty();
	m_dtkycxz4.Empty();

	m_cElv1.SetCurSel(0);
	m_strElv1.Empty();
	m_cElv2.SetCurSel(0);;
	m_strElv2.Empty();
	m_cElv3.SetCurSel(0);;
	m_strElv3.Empty();
	m_cElv4.SetCurSel(0);;
	m_strElv4.Empty();

	m_sn.Empty();
	m_xzms = 0;
	m_sjhm.Empty();
}

void CManagerInfoDlg::SetParent(CManagerDlg* pParent)
{
	m_pParent = pParent;
}


void CManagerInfoDlg::OnBnClickedBtnReplace()
{
	// TODO: 在此添加控件通知处理程序代码	SetPara2(TRUE);

	SetPara2(TRUE);
	CString strMsg;
	BOOL bRetDatabase = FALSE;
	long lStatus = ADD_TYPE;

	Cquset *pQuset  = LPDBManage->GetManagerByID(m_ID, lStatus);
	//禁用掉
	pQuset->m_status = 1;
	bRetDatabase = LPDBManage->OperManager(pQuset,MOD_TYPE);
	if(!bRetDatabase)
		bRetDatabase = LPDBManage->OperManager(pQuset,MOD_TYPE);

	//增加新卡
	long lNewID = LPDBManage->GetManagerID();

	m_glykh = lNewID;

	pQuset->m_ID = lNewID;

	pQuset->m_glykh = lNewID;

	pQuset->m_status = 0;

	BOOL bWriteRet = WirteIC(pQuset, 3, m_ID);

	if(bWriteRet)
	{
		bRetDatabase = LPDBManage->OperManager(pQuset,ADD_TYPE);
		if(!bRetDatabase)
			bRetDatabase = LPDBManage->OperManager(pQuset,MOD_TYPE);
	}
	
	if(bWriteRet && bRetDatabase)
	{
		strMsg.Format("管理员%s补卡成功!\r\n", pQuset->m_glymc);

		SetOutPutInfo(strMsg);

		m_glykh = lNewID;

		m_ID = lNewID;

		m_strOutput = GetCardInfo(pQuset);

		m_strOutput = strMsg + m_strOutput;

		AfxMessageBox(strMsg);
		//刷新下界面
		if(m_pParent)
			m_pParent->OnBnClickedBtnRefresh();
	}
	else
	{
		strMsg.Format("管理员%s补卡失败!", pQuset->m_glymc);
		SetOutPutInfo(strMsg);
	}
	UpdateData(FALSE);
}

CString	CManagerInfoDlg::GetCardInfo(Cquset *p)
{
	CString szInfo, szTemp;
	szInfo.Format("卡片类型：管理员卡\r\n");

	szTemp.Format("业主卡卡号：%d\r\n", m_glykh);
	szInfo += szTemp;

	szTemp.Format("业主名称：%s\r\n", m_glymc);
	szInfo += szTemp;

	szTemp.Format("手机号码：%s\r\n", m_sjhm);
	szInfo += szTemp;


	if(m_xzms == 0)
	{
		szTemp.Format("限制模式：不限制\r\n");
		szInfo += szTemp;
		szTemp.Format("   使用次数：%d\r\n", m_sycs);
		szInfo += szTemp;
	}
	else if(m_xzms == 1)
	{
		szTemp.Format("限制模式：不限制\r\n");
	}
	else if(m_xzms == 2)
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
	if(m_ctqxms == 0)
	{
		szTemp.Format("可用电梯：所有电梯\r\n");
		szInfo += szTemp;
	}
	else if(m_ctqxms == 1)
	{
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
	}
	return szInfo;
}
