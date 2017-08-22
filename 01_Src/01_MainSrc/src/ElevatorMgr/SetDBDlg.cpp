// SetDBDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "SetDBDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>

using namespace std;
// CSetDBDlg 对话框

IMPLEMENT_DYNAMIC(CSetDBDlg, CDialogEx)

CSetDBDlg::CSetDBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDBDlg::IDD, pParent)
	, m_strSectionType(_T(""))
	, m_strDBPath(_T(""))
	, m_iAgentID(0)
	, m_szAgentDes(_T(""))
	, m_szReverseRecord(_T(""))
	, m_uiElevatorID(0)
	, m_szElevatorTime(_T(""))
	, m_uiOffset(0)
	, m_dwAgentNo(0)
	, m_szIsAgentCheck(_T(""))
	, m_szOffset(_T(""))
	, m_btPsw1(255)
	, m_btPsw2(255)
	, m_btPsw3(255)
	, m_btPsw4(255)
	, m_bSectionPsw(FALSE)
	, m_bAgent(FALSE)
	, m_dwWriterID(0xFFFFFFFF)
	, m_bReverseWrite(FALSE)
	, m_bProduceFlag(FALSE)
	//, m_bDisCounter(FALSE)
	, m_szDisableCounter(_T(""))
	, m_szPassword(_T(""))
{

}

CSetDBDlg::~CSetDBDlg()
{
}

void CSetDBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_SECTION, m_SectionType);
	//DDX_Text(pDX, IDC_EDIT_PARAM, m_strDBPath);
	DDX_Text(pDX, IDC_AGENT_IDDES, m_szAgentDes);
	DDX_Text(pDX, IDC_REVERSE_RECORD, m_szReverseRecord);
	DDX_Text(pDX, IDC_ELEVATOR_NO, m_uiElevatorID);
	DDX_Text(pDX, IDC_ELEVATOR_TIME, m_szElevatorTime);
	DDX_Text(pDX, IDC_OFFSET_DATA, m_uiOffset);
	DDX_Text(pDX, IDC_AGENT_ID_NUM, m_dwAgentNo);
	DDX_Text(pDX, IDC_AGENT_CHECK, m_szIsAgentCheck);
	DDX_Text(pDX, IDC_EDIT_WRITER, m_szOffset);
	DDX_Text(pDX, IDC_EDIT_PSW1, m_btPsw1);
	DDV_MinMaxByte(pDX, m_btPsw1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PSW2, m_btPsw2);
	DDV_MinMaxByte(pDX, m_btPsw2, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PSW3, m_btPsw3);
	DDV_MinMaxByte(pDX, m_btPsw3, 0, 255);
	DDX_Text(pDX, IDC_EDIT_PSW4, m_btPsw4);
	DDV_MinMaxByte(pDX, m_btPsw4, 0, 255);
	DDX_Check(pDX, IDC_CHK_PSW, m_bSectionPsw);
	DDX_Text(pDX, IDC_WRITER_ID, m_dwWriterID);
	DDX_Check(pDX, IDC_CHK_REVERSE, m_bReverseWrite);
	DDX_Check(pDX, IDC_CHK_PRODUCE, m_bProduceFlag);
	//DDX_Check(pDX, IDC_CHK_DISCOUNT, m_bDisCounter);
	DDX_Text(pDX, IDC_DISABLECOUNTER, m_szDisableCounter);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
}


BEGIN_MESSAGE_MAP(CSetDBDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDBDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CSetDBDlg::OnBnClickedBtnExport)
	ON_CBN_KILLFOCUS(IDC_COMBO_COMPORT, &CSetDBDlg::OnCbnKillfocusComboComport)
	ON_CBN_KILLFOCUS(IDC_COMBO_COMPORT2, &CSetDBDlg::OnCbnKillfocusComboComport2)
	ON_BN_CLICKED(IDC_BTN_SETOFFSET, &CSetDBDlg::OnBnClickedBtnSetoffset)
	//ON_BN_CLICKED(IDC_BTN_AGENT_RECORD, &CSetDBDlg::OnBnClickedBtnAgentRecord)
	ON_BN_CLICKED(IDC_BTN_READ_ELEVATORPARAM, &CSetDBDlg::OnBnClickedBtnReadElevatorparam)
	ON_BN_CLICKED(IDC_BTN_CHECK_WRITER, &CSetDBDlg::OnBnClickedBtnCheckWriter)
	ON_BN_CLICKED(IDC_BTN_WRITER_AGENTID, &CSetDBDlg::OnBnClickedBtnWriterAgentid)
	ON_BN_CLICKED(IDC_BTN_DB_EXPORT, &CSetDBDlg::OnBnClickedBtnDbExport)
	ON_BN_CLICKED(IDC_BTN_DB_INPORT, &CSetDBDlg::OnBnClickedBtnDbInport)
	ON_BN_CLICKED(IDC_BTN_INPORT_ELEVATOR, &CSetDBDlg::OnBnClickedBtnInportElevator)
	ON_BN_CLICKED(IDC_BTN_INPORT_FUNC, &CSetDBDlg::OnBnClickedBtnInportFunc)
	ON_BN_CLICKED(IDC_BTN_INPORT_MGR, &CSetDBDlg::OnBnClickedBtnInportMgr)
	ON_BN_CLICKED(IDC_BTN_CHK_PSW, &CSetDBDlg::OnBnClickedBtnChkPsw)
	ON_BN_CLICKED(IDC_BTN_CHK_AGENT, &CSetDBDlg::OnBnClickedBtnChkAgent)
END_MESSAGE_MAP()


// CSetDBDlg 消息处理程序

BOOL    CSetDBDlg::SetPara(BOOL bSave)
{
	CString strTemp;
	if (bSave)
	{
		LPSerialProtocol->m_config.m_strEncryp  = strTemp;

		m_SectionType.GetWindowText(strTemp);
		LPSerialProtocol->m_config.m_strSectionType  = strTemp;

		LPSerialProtocol->m_config.m_strDBPath  = m_strDBPath;
		LPSerialProtocol->m_config.Save();
	}
	else
	{
		strTemp = LPSerialProtocol->m_config.m_strEncryp;

		strTemp = LPSerialProtocol->m_config.m_strSectionType;
		int nIndex = m_SectionType.FindStringExact(0, strTemp);
		if (nIndex == -1) nIndex = 0;
		m_SectionType.SetCurSel(nIndex);


		m_strDBPath = LPSerialProtocol->m_config.m_strDBPath;
	}

	Invalidate(TRUE);
	return TRUE;
}


void CSetDBDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"Access数据库文件|*.mdb||",NULL);

	dlgFile.m_ofn.lpstrTitle = "指定文件名称";
	if (IDOK != dlgFile.DoModal())
		return ;

	m_strDBPath = dlgFile.GetPathName();

	m_strDBPath.TrimLeft();
	m_strDBPath.TrimRight();

	UpdateData(FALSE);
}


void CSetDBDlg::OnBnClickedBtnExport()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CSetDBDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetPara(FALSE);

	CString strData;
	m_SectionType.AddString("不偏移");
	for (int i=1; i<30; i++)
	{
		strData.Format("偏移%d", i);
		m_SectionType.AddString(strData);
	}
	int iOffset = 0, iRecode = 0;
	LPDBManage->ReadOffset(iOffset, iRecode);

#ifdef MGR_USER
	//((CWnd*)GetDlgItem(IDC_STATIC_AGENT8))->ShowWindow(SW_HIDE);
	//((CWnd*)GetDlgItem(IDC_WRITER_ID))->ShowWindow(SW_HIDE);
	//((CWnd*)GetDlgItem(IDC_BTN_CHK_AGENT))->ShowWindow(SW_HIDE);
	((CEdit*)GetDlgItem(IDC_WRITER_ID))->SetReadOnly();
	((CWnd*)GetDlgItem(IDC_BTN_SETOFFSET))->ShowWindow(SW_HIDE);
#elif MGR_AGENT
	((CEdit*)GetDlgItem(IDC_WRITER_ID))->SetReadOnly();
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CSetDBDlg::OnCbnKillfocusComboComport()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara(TRUE);
}


void CSetDBDlg::OnCbnKillfocusComboComport2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara(TRUE);
}


void CSetDBDlg::OnBnClickedBtnSetoffset()
{
	// TODO: 在此添加控件通知处理程序代码	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	BYTE btValue = 0;
	int iIndex = m_SectionType.GetCurSel();
	BYTE btData[14]= {0};
	//版本号
	btData[0] = 4;
	if(iIndex <= 0)
		iIndex = 0;
	
	btData[1] = iIndex & 0xFF;
	if(m_bSectionPsw)
		btData[2] = 0x1;

	btData[3] = 1;
	//if(m_bDisCounter)
	//	btData[3] |= 0x2;

	if(!m_bSectionPsw)
		m_btPsw1 = m_btPsw2 = m_btPsw3 = m_btPsw4 = 0xFF;
	
	btData[4] = m_btPsw1 & 0xFF;
	btData[5] = m_btPsw2 & 0xFF;
	btData[6] = m_btPsw3 & 0xFF;
	btData[7] = m_btPsw4 & 0xFF;


	//if(!m_bAgent)
	//	m_dwWriterID = 0xFFFFFFFF;

	if(m_dwWriterID == 0)
		m_dwWriterID = 0xFFFFFFFF;

	btData[8] = (m_dwWriterID >> 24) & 0xFF;
	btData[9] = (m_dwWriterID >> 16)  & 0xFF;
	btData[10] = (m_dwWriterID >> 8)  & 0xFF;
	btData[11] = m_dwWriterID & 0xFF;

	if(m_bProduceFlag)
		btData[12] = 0x01;
	if(m_bReverseWrite)
		btData[13] = 0x01;

	BOOL bRet = CRadioCardProtocal::GetRadioCardProtocal()->WriteOffsetPswCard(btData, 14);
	Sleep(500);
	BOOL bRet2 = CRadioCardProtocal::GetRadioCardProtocal()->WriteOffsetPsw(btData, 14);

	int iRecode = 0;

	LPDBManage->RecordOffset(iIndex, iRecode);
	CString szMsgCard, szMsgCarder, szMsg;
	if(bRet == TRUE)
		szMsgCard.Format("状态卡生成成功");

	if(bRet2 == TRUE)
		szMsg.Format("写卡器生成成功");
	szMsg.Format("%s %s", szMsgCard, szMsgCarder);
	AfxMessageBox(szMsg);
}


void CSetDBDlg::OnBnClickedBtnAgentRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData();
	//DWORD dwAgentID = m_iAgentID;
	//CString szMsg;
	//if(LPDBManage->RecordAgentID(dwAgentID,m_szAgentDes))
	//{
	//	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->WriteAgentID(dwAgentID);

	//	if(!bRet)
	//	{
	//		LPDBManage->ClearAgentID();
	//		szMsg.Format("物业身份ID设置失败,请检查或者再试一次!");
	//	}
	//	else
	//	{
	//		((CWnd*)GetDlgItem(IDC_STATIC_AGENT))->ShowWindow(SW_HIDE);
	//		((CWnd*)GetDlgItem(IDC_AGENT_ID))->ShowWindow(SW_HIDE);
	//		((CWnd*)GetDlgItem(IDC_BTN_AGENT_RECORD))->ShowWindow(SW_HIDE);
	//		((CWnd*)GetDlgItem(IDC_STATIC_AGENT_DES))->ShowWindow(SW_HIDE);
	//		((CWnd*)GetDlgItem(IDC_AGENT_IDDES))->ShowWindow(SW_HIDE);
	//		theApp.SetAgentID(dwAgentID);

	//		szMsg.Format("物业身份ID设置成功");
	//	}

	//	AfxMessageBox(szMsg);
	//}
}


void CSetDBDlg::OnBnClickedBtnReadElevatorparam()
{
	// TODO: 在此添加控件通知处理程序代码
	T_Data tData;
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->ReadInterParam(tData);
	if(bRet)
	{
		m_szReverseRecord = tData.szReverseRecord;
		m_uiElevatorID = tData.uiElevatorID;
		m_szElevatorTime = tData.szElevatorTime;
		m_uiOffset = tData.uiOffset;
		m_dwAgentNo = tData.dwAgentNo;
		m_szIsAgentCheck = tData.szIsAgentCheck;
		m_szDisableCounter = tData.szDisableCounter;
		m_szPassword.Format("%d,%d,%d,%d", 
			tData.btPassword[0], 
			tData.btPassword[1], 
			tData.btPassword[2], 
			tData.btPassword[3]);		
	}
	UpdateData(FALSE);
}


void CSetDBDlg::OnBnClickedBtnCheckWriter()
{
	// TODO: 在此添加控件通知处理程序代码
	int iOffset = 0;
	BOOL bRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadWriterOffset(iOffset);
	if(bRet)
		m_szOffset.Format("%d", iOffset);

	UpdateData(FALSE);
}


void CSetDBDlg::OnBnClickedBtnWriterAgentid()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwID;
	BYTE byProduceFlag = 0;
	BYTE byReverseFlag = 0;
	BOOL bRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadWriterID(dwID, byProduceFlag, byReverseFlag);
	if(bRet)
		m_dwWriterID = dwID;
	if((byProduceFlag & 0x01) == 0x01)
		m_bProduceFlag = TRUE;
	if((byReverseFlag & 0x01) == 0x01)
		m_bReverseWrite = TRUE;

	UpdateData(FALSE);
}

void CSetDBDlg::OnBnClickedBtnDbExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;  
	filter="Data Files (*.csv;*.txt)|*.csv; *.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{  
		CString str;  
		CString szPathName = dlg.GetPathName();  
		int iPos = szPathName.ReverseFind('.');
		str = szPathName;
		if(iPos > 0)
			str = szPathName.Left(iPos);
		CTime tmNow = ::time(NULL);
		CString strTime;
		strTime.Format("%d%d%d_%d%d%d", 
			tmNow.GetYear(), 
			tmNow.GetMonth(),
			tmNow.GetDay(),
			tmNow.GetHour(),
			tmNow.GetMinute(),
			tmNow.GetSecond());

		//导出用户数据
		CString strFile;
		strFile.Format("%s_CustomerData_%s.csv", str, strTime);
		ExportCustomerData(strFile);

		strFile.Format("%s_ManagerData_%s.csv", str, strTime);
		ExportManagerData(strFile);
		
		strFile.Format("%s_FuncData_%s.csv", str, strTime);
		ExportFuncCardData(strFile);
		
		strFile.Format("%s_ElevatorData_%s.csv", str, strTime);
		ExportElevatorData(strFile);
	}  
	AfxMessageBox("导出数据完成，请及时备份");
}


void CSetDBDlg::OnBnClickedBtnDbInport()
{
	// TODO: 在此添加控件通知处理程序代码	
	CString filter;  
	filter="Data Files (*.csv;*.txt)|*.csv; *.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{  
		CString str;  
		CString szPathName = dlg.GetPathName();  
		ImportCustomerData(szPathName);
	}  
}

void CSetDBDlg::OnBnClickedBtnInportElevator()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;  
	filter="Data Files (*.csv;*.txt)|*.csv; *.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{  
		CString str;  
		CString szPathName = dlg.GetPathName();  
		ImportElevatorData(szPathName);
	}  
}


void CSetDBDlg::OnBnClickedBtnInportFunc()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;  
	filter="Data Files (*.csv;*.txt)|*.csv; *.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{  
		CString str;  
		CString szPathName = dlg.GetPathName();  
		ImportFuncCardData(szPathName);
	}  
}


void CSetDBDlg::OnBnClickedBtnInportMgr()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;  
	filter="Data Files (*.csv;*.txt)|*.csv; *.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);  
	if(dlg.DoModal()==IDOK)  
	{  
		CString str;  
		CString szPathName = dlg.GetPathName();  
		ImportManagerData(szPathName);
	}  
}

int CSetDBDlg::ExportCustomerData(CString szPathName)
{
	CArray<CYonghuset*,CYonghuset*> arrCustermers;
	LPDBManage->GetCustermerList(arrCustermers);
	TRY
	{
		std::string szFileName, szData;
		szFileName = szPathName.GetBuffer(0);
		szPathName.ReleaseBuffer();
		ofstream ar(szFileName);

		if(!ar.is_open())
		{
			CString szMsg;
			szMsg.Format("文件%s创建失败!", szFileName.c_str());
			AfxMessageBox(szMsg);
			return -1;
		}
		CString strData;
		int iVer = 1;
		ar << "CustomerData data\n";
		ar << iVer << "\n";
		int iCount = arrCustermers.GetSize();
		ar << iCount << "\n";
		ar << "编号, 业主姓名,手机号码,SN,房间编号,业主门牌,卡号,限制模式,使用次数,起始日期,截至日期,可用电梯一,电梯一可用层,电梯一可用层下载,可用电梯二,电梯二可用层,电梯二可用层下载,可用电梯三,电梯三可用层,电梯三可用层下载,可用电梯四,电梯四可用层,电梯四可用层下载,卡状态,操作方式,黑名单次数";
		ar << "\n";
		for (int i=0; i<iCount; i++)
		{
			CYonghuset *pYonghuset = arrCustermers.GetAt(i);
			if(NULL == pYonghuset)
				continue;
			strData.Format("%d,%s,%s,%s,%d,%s,%d,%d,%d,%s,%s,%d,%s,%s,%d,%s,%s,%d,%s,%s,%d,%s,%s,%d,%d,%d", 
				pYonghuset->m_ID,
				pYonghuset->m_yzmc,
				pYonghuset->m_sjhm,
				pYonghuset->m_sn,
				pYonghuset->m_fjbh,
				pYonghuset->m_yzmp,
				pYonghuset->m_yzkh,
				pYonghuset->m_xzms,
				pYonghuset->m_sycs,
				pYonghuset->m_qssj,
				pYonghuset->m_jzsj,
				pYonghuset->m_kydt1,
				pYonghuset->m_dtkyc1,
				pYonghuset->m_dtkycxz1,
				pYonghuset->m_kydt2,
				pYonghuset->m_dtkyc2,
				pYonghuset->m_dtkycxz2,
				pYonghuset->m_kydt3,
				pYonghuset->m_dtkyc3,
				pYonghuset->m_dtkycxz3,
				pYonghuset->m_kydt4,
				pYonghuset->m_dtkyc4,
				pYonghuset->m_dtkycxz4,
				pYonghuset->m_status,
				pYonghuset->m_czfs,
				pYonghuset->m_hmdcs);
			szData = strData.GetBuffer(strData.GetLength());
			strData.ReleaseBuffer();
			ar << szData << std::endl;
		}
		ar.close();
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}


int CSetDBDlg::ExportManagerData(CString szPathName)
{
	CArray<Cquset*,Cquset*> arrManagers;
	LPDBManage->GetManagerList(arrManagers);
	//CFile file;
	TRY
	{

		std::string szFileName, szData;
		szFileName = szPathName.GetBuffer(0);
		szPathName.ReleaseBuffer();
		ofstream ar(szFileName);

		if(!ar.is_open())
		{
			CString szMsg;
			szMsg.Format("文件%s创建失败!", szFileName.c_str());
			AfxMessageBox(szMsg);
			return -1;
		}
		CString strData;
		// 	strData.Format("CustomerData data");
		// 	file.Write(strData, strData.GetLength());
		int iVer = 1;
		ar << "ManagerData Data\n";
		ar << iVer << "\n";
		int iCount = arrManagers.GetSize();
		ar << iCount << "\n";
		ar << "编号,卡号,管理员名称,手机号码,SN,限制模式,使用次数,起始日期,截至日期,乘梯权限模式,可用电梯一,电梯一可用层,电梯一可用层下载,可用电梯二,电梯二可用层,电梯二可用层下载,可用电梯三,电梯三可用层,电梯三可用层下载,可用电梯四,电梯四可用层,电梯四可用层下载,卡状态";
		ar << "\n";
		for (int i=0; i<iCount; i++)
		{
			Cquset *pQuset = arrManagers.GetAt(i);
			if(NULL == pQuset)
				continue;
			strData.Format("%d,%d,%s,%s,%s,%d,%d,%s,%s,%d,%d,%s,%s,%d,%s,%s,%d,%s,%s,%d,%s,%s,%d", 
				pQuset->m_ID,
				pQuset->m_glykh,
				pQuset->m_glymc,
				pQuset->m_sjhm,
				pQuset->m_sn,
				pQuset->m_xzms,
				pQuset->m_sycs,
				pQuset->m_qssj,
				pQuset->m_jzsj,
				pQuset->m_ctqxms,
				pQuset->m_kydt1,
				pQuset->m_dtkyc1,
				pQuset->m_dtkycxz1,
				pQuset->m_kydt2,
				pQuset->m_dtkyc2,
				pQuset->m_dtkycxz2,
				pQuset->m_kydt3,
				pQuset->m_dtkyc3,
				pQuset->m_dtkycxz3,
				pQuset->m_kydt4,
				pQuset->m_dtkyc4,
				pQuset->m_dtkycxz4,
				pQuset->m_status);
			ar << strData << "\n";
		}
		ar.close();
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}


int CSetDBDlg::ExportFuncCardData(CString szPathName)
{
	CArray<CKeyinfoset*,CKeyinfoset*> arrFunctionDatas;
	LPDBManage->GetFuncList(arrFunctionDatas);
	//CFile file;
	TRY
	{
		std::string szFileName, szData;
		szFileName = szPathName.GetBuffer(0);
		szPathName.ReleaseBuffer();
		ofstream ar(szFileName);

		if(!ar.is_open())
		{
			CString szMsg;
			szMsg.Format("文件%s创建失败!", szFileName.c_str());
			AfxMessageBox(szMsg);
			return -1;
		}

		CString strData;
		// 	strData.Format("CustomerData data");
		// 	file.Write(strData, strData.GetLength());
		int iVer = 1;
		ar << "FunctionData data\n";
		ar << iVer << "\n";
		int iCount = arrFunctionDatas.GetSize();
		ar << iCount << "\n";
		ar << "编号,卡类型,卡号,使用次数,子卡类型,启禁卡号一,启禁标志一,启禁卡号二,启禁标志二,启禁卡号三,启禁标志三,启禁卡号四,启禁标志四,启禁卡号五,启禁标志五,启禁卡号六,启禁标志六,启禁卡号七,启禁标志七,启禁卡号八,启禁标志八,启禁卡号九,启禁标志九,启禁卡号十,启禁标志十,校时时间,卡状态,SN";
		ar << "\n";

		for (int i=0; i<arrFunctionDatas.GetSize(); i++)
		{
			CKeyinfoset *pKeyinfoset = arrFunctionDatas.GetAt(i);
			if(NULL == pKeyinfoset)
				continue;
			strData.Format("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%d,%s",
				pKeyinfoset->m_id,
				pKeyinfoset->m_klx,
				pKeyinfoset->m_gnkh,
				pKeyinfoset->m_sycs,
				pKeyinfoset->m_zklx,
				pKeyinfoset->m_qjkh1,
				pKeyinfoset->m_qjbz1,
				pKeyinfoset->m_qjkh2,
				pKeyinfoset->m_qjbz2,
				pKeyinfoset->m_qjkh3,
				pKeyinfoset->m_qjbz3,
				pKeyinfoset->m_qjkh4,
				pKeyinfoset->m_qjbz4, 
				pKeyinfoset->m_qjkh5,   
				pKeyinfoset->m_qjbz5,  
				pKeyinfoset->m_qjkh6,   
				pKeyinfoset->m_qjbz6,  
				pKeyinfoset->m_qjkh7,   
				pKeyinfoset->m_qjbz7,  
				pKeyinfoset->m_qjkh8,   
				pKeyinfoset->m_qjbz8,
				pKeyinfoset->m_qjkh9,   
				pKeyinfoset->m_qjbz9,
				pKeyinfoset->m_qjkh10,   
				pKeyinfoset->m_qjbz10, 
				pKeyinfoset->m_jssj,
				pKeyinfoset->m_status,
				pKeyinfoset->m_sn);
			ar << strData << "\n";
		}
		ar.close();
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
		return 0;
}


int CSetDBDlg::ExportElevatorData(CString szPathName)
{
	CArray<CSuoset*,CSuoset*> arrElevators;
	LPDBManage->GetElevatorList(arrElevators);
	//CFile file;
	TRY
	{
		std::string szFileName, szData;
		szFileName = szPathName.GetBuffer(0);
		szPathName.ReleaseBuffer();
		ofstream ar(szFileName);

		if(!ar.is_open())
		{
			CString szMsg;
			szMsg.Format("文件%s创建失败!", szFileName.c_str());
			AfxMessageBox(szMsg);
			return -1;
		}

		CString strData;
		int iVer = 1;
		ar << "Elevator data\n";
		ar << iVer << "\n";		int iCount = arrElevators.GetSize();
		ar << iCount << "\n";
		ar << "电梯编号,电梯名称,电梯类型,总层数,起始楼层,公共楼层,楼层标识";
		ar << "\n";

		for (int i=0; i<arrElevators.GetSize(); i++)
		{
			CSuoset *pSuoset = arrElevators.GetAt(i);
			if(NULL == pSuoset)
				continue;
			strData.Format("%d,%s,%d,%d,%d,%d,%s", 
				pSuoset->m_dtbh,
				pSuoset->m_dtmc,
				pSuoset->m_dtlx,
				pSuoset->m_dtcs,
				pSuoset->m_qslc,
				pSuoset->m_gglc,
				pSuoset->m_dtlcbs);
			ar << strData << "\r\n";
		}
		ar.close();
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}

int CSetDBDlg::ImportCustomerData(CString szPathName)
{
	//CFile file;
	TRY
	{
		string szFile = szPathName.GetBuffer(szPathName.GetLength());
		szPathName.ReleaseBuffer();

		CStringArray datas;
		CString strTemp;
		ifstream ar(szFile);
		CString strData;
		string szData;
		char pData[1024];
		int iVer = 1;
		ar.getline(pData, 1024);// szData;
		strData = pData;

		SplitString(strData, ',', datas);
		strData = datas.GetAt(0);

		if(strData.CompareNoCase("CustomerData data") != 0)
		{
			AfxMessageBox("不是业主数据文件,请检查!");
			return -1;
		}
		ar >> iVer;
		int iCount = 0;
		ar >> iCount;

		ar.getline(pData, 1024);
		ar.getline(pData, 1024);

		CYonghuset Yonghuset;
		for (int i=0; i<iCount; i++)
		{
			ar.getline(pData, 1024);
			strData = pData;

			SplitString(strData, ',', datas);
			if(datas.GetSize() < 26)
				continue;

			strTemp = datas.GetAt(0);
			Yonghuset.m_ID = atoi((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_yzmc = datas.GetAt(1);
			Yonghuset.m_sjhm = datas.GetAt(2);
			Yonghuset.m_sn = datas.GetAt(3);

			strTemp = datas.GetAt(4);
			Yonghuset.m_fjbh = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_yzmp = datas.GetAt(5);
			strTemp = datas.GetAt(6);
			Yonghuset.m_yzkh = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(7);
			Yonghuset.m_xzms = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(8);
			Yonghuset.m_sycs = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_qssj = datas.GetAt(9);
			Yonghuset.m_jzsj = datas.GetAt(10);
			strTemp = datas.GetAt(11);
			Yonghuset.m_kydt1 = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_dtkyc1 = datas.GetAt(12);
			Yonghuset.m_dtkycxz1 = datas.GetAt(13);

			strTemp = datas.GetAt(14);
			Yonghuset.m_kydt2 = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_dtkyc2 = datas.GetAt(15);
			Yonghuset.m_dtkycxz2 = datas.GetAt(16);

			strTemp = datas.GetAt(17);
			Yonghuset.m_kydt3 = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_dtkyc3 = datas.GetAt(18);
			Yonghuset.m_dtkycxz3 = datas.GetAt(19);

			strTemp = datas.GetAt(20);
			Yonghuset.m_kydt4 = atol((LPSTR)(LPCTSTR)strTemp);
			Yonghuset.m_dtkyc4 = datas.GetAt(21);
			Yonghuset.m_dtkycxz4 = datas.GetAt(22);

			strTemp = datas.GetAt(23);
			Yonghuset.m_status = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(24);
			Yonghuset.m_czfs = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(25);
			Yonghuset.m_hmdcs = atol((LPSTR)(LPCTSTR)strTemp);

			BOOL bRet = LPDBManage->OpereCustomer(&Yonghuset, ADD_TYPE);
			if(!bRet)
			{
				bRet = LPDBManage->OpereCustomer(&Yonghuset, MOD_TYPE);
			}				
		}
		ar.close();
		AfxMessageBox("更新数据完成,请重新启动管理器");
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
 	{  
 		switch (e->m_cause)  
 		{  
 		case CFileException::accessDenied:  
 			TRACE("File Access Denied\n");  
 			break;  
 		case CFileException::badPath:  
 			TRACE("Invalid Path\n");  
 			break;  
 		case CFileException::diskFull:  
 			TRACE("Disk Full\n");  
 			break;  
 		case CFileException::fileNotFound:  
 			TRACE("File Not Found\n");  
 			break;  
 		case CFileException::hardIO:  
 			TRACE("Hardware Error\n");  
 			break;  
 		case CFileException::lockViolation:  
 			TRACE("Attemp to lock region already locked \n");  
 			break;  
 		case CFileException::sharingViolation:  
 			TRACE("Sharing Violation -load share.exe\n");  
 			break;  
 		case CFileException::tooManyOpenFiles:  
 			TRACE("Too Many Open Files\n");  
 			break;  
 		}  
 	}  

	END_CATCH
	return 0;
}
int CSetDBDlg::ImportManagerData(CString szPathName)
{	
	TRY
	{
		string szFile = szPathName.GetBuffer(szPathName.GetLength());
		szPathName.ReleaseBuffer();

		CStringArray datas;
		CString strTemp;
		ifstream ar(szFile);
		CString strData;
		string szData;
		char pData[1024];
		int iVer = 1;
		ar.getline(pData, 1024);// szData;
		strData = pData;

		SplitString(strData, ',', datas);
		strData = datas.GetAt(0);

		if(strData.CompareNoCase("ManagerData Data") != 0)
		{
			AfxMessageBox("不是业主数据文件,请检查!");
			return -1;
		}
		ar >> iVer;
		int iCount = 0;
		ar >> iCount;
		ar.getline(pData, 1024);

		Cquset Suoset;

		for (int i=0; i<iCount; i++)
		{
			ar.getline(pData, 1024);
			strData = pData;

			SplitString(strData, ',', datas);

			if(datas.GetSize() < 24)
				continue;

			strTemp = datas.GetAt(0);
			Suoset.m_ID = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(1);
			Suoset.m_glykh = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_glymc = datas.GetAt(2);
			Suoset.m_sjhm = datas.GetAt(3);
			Suoset.m_sn = datas.GetAt(4);
			strTemp = datas.GetAt(5);
			Suoset.m_xzms = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(6);
			Suoset.m_sycs = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_qssj = datas.GetAt(7);
			Suoset.m_jzsj = datas.GetAt(8);
			strTemp = datas.GetAt(9);
			Suoset.m_ctqxms = atol((LPSTR)(LPCTSTR)strTemp);

			strTemp = datas.GetAt(10);
			Suoset.m_kydt1 = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_dtkyc1 = datas.GetAt(11);
			Suoset.m_dtkycxz1 = datas.GetAt(12);

			strTemp = datas.GetAt(13);
			Suoset.m_kydt2 = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_dtkyc2 = datas.GetAt(14);
			Suoset.m_dtkycxz2 = datas.GetAt(15);

			strTemp = datas.GetAt(16);
			Suoset.m_kydt3 = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_dtkyc3 = datas.GetAt(17);
			Suoset.m_dtkycxz3 = datas.GetAt(18);

			strTemp = datas.GetAt(19);
			Suoset.m_kydt4 = atol((LPSTR)(LPCTSTR)strTemp);
			Suoset.m_dtkyc4 = datas.GetAt(20);
			Suoset.m_dtkycxz4 = datas.GetAt(21);

			strTemp = datas.GetAt(22);
			Suoset.m_status = atol((LPSTR)(LPCTSTR)strTemp);

			BOOL bRet = LPDBManage->OperManager(&Suoset, ADD_TYPE);
			if(!bRet)
				LPDBManage->OperManager(&Suoset, MOD_TYPE);
		}
		ar.close();
		AfxMessageBox("更新数据完成,请重新启动管理器");
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}
int CSetDBDlg::ImportFuncCardData(CString szPathName)
{
	//CFile file;
	TRY
	{
		string szFile = szPathName.GetBuffer(szPathName.GetLength());
		szPathName.ReleaseBuffer();

		CStringArray datas;
		CString strTemp;
		ifstream ar(szFile);
		CString strData;
		string szData;
		char pData[1024];
		int iVer = 1;
		ar.getline(pData, 1024);// szData;
		strData = pData;

		SplitString(strData, ',', datas);
		strData = datas.GetAt(0);

		if(strData.CompareNoCase("FunctionData data") != 0)
		{
			AfxMessageBox("不是业主数据文件,请检查!");
			return -1;
		}
		ar >> iVer;
		int iCount = 0;
		ar >> iCount;
		ar.getline(pData, 1024);

		CKeyinfoset Keyinfoset;
		for (int i=0; i<iCount; i++)
		{
			//ar >> strData;		
			ar.getline(pData, 1024);
			strData = pData;

			SplitString(strData, ',', datas);
			if(datas.GetSize() < 28)
				continue;

			strTemp = datas.GetAt(0);
			Keyinfoset.m_id = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(1);
			Keyinfoset.m_klx = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(2);
			Keyinfoset.m_gnkh = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(3);
			Keyinfoset.m_sycs = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(4);
			Keyinfoset.m_zklx = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(5);
			Keyinfoset.m_qjkh1 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(6);
			Keyinfoset.m_qjbz1 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(7);
			Keyinfoset.m_qjkh2 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(8);
			Keyinfoset.m_qjbz2 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(9);
			Keyinfoset.m_qjkh3 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(1);
			Keyinfoset.m_qjbz3 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(11);
			Keyinfoset.m_qjkh4 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(12);
			Keyinfoset.m_qjbz4 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(13);
			Keyinfoset.m_qjkh5 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(14);   
			Keyinfoset.m_qjbz5 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(15); 
			Keyinfoset.m_qjkh6 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(16);  
			Keyinfoset.m_qjbz6 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(17); 
			Keyinfoset.m_qjkh7 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(18);  
			Keyinfoset.m_qjbz7 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(19); 
			Keyinfoset.m_qjkh8 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(20); 
			Keyinfoset.m_qjbz8 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(21);
			Keyinfoset.m_qjkh9 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(22);  
			Keyinfoset.m_qjbz9 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(23);
			Keyinfoset.m_qjkh10 = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(24);
			Keyinfoset.m_qjbz10 = atol((LPSTR)(LPCTSTR)strTemp);			
			Keyinfoset.m_jssj = datas.GetAt(25);
			strTemp = datas.GetAt(26);
			Keyinfoset.m_status = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(27);
			Keyinfoset.m_sn = strTemp;

			BOOL bRet = LPDBManage->OperFunc(&Keyinfoset, ADD_TYPE);
			if(!bRet)
				LPDBManage->OperFunc(&Keyinfoset, MOD_TYPE);
		}
		ar.close();
		AfxMessageBox("更新数据完成,请重新启动管理器");
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}
int CSetDBDlg::ImportElevatorData(CString szPathName)
{
	CFile file;
	TRY
	{
		string szFile = szPathName.GetBuffer(szPathName.GetLength());
		szPathName.ReleaseBuffer();

		CStringArray datas;
		CString strTemp;
		ifstream ar(szFile);
		CString strData;
		string szData;
		char pData[1024];
		int iVer = 1;
		ar.getline(pData, 1024);// szData;
		strData = pData;

		SplitString(strData, ',', datas);
		strData = datas.GetAt(0);

		if(strData.CompareNoCase("Elevator data") != 0)
		{
			AfxMessageBox("不是电梯数据文件,请检查!");
			return -1;
		}
		ar >> iVer;
		int iCount = 0;
		ar >> iCount;
		ar.getline(pData, 1024);
		ar.getline(pData, 1024);

		CSuoset Suoset;
		for (int i=0; i<iCount; i++)
		{
			//ar >> strData;
			ar.getline(pData, 1024);
			strData = pData;

			SplitString(strData, ',', datas);
			if(datas.GetSize() < 7)
				continue;
			strTemp = datas.GetAt(0);
			Suoset.m_dtbh = atol((LPSTR)(LPCTSTR)strTemp);	
			strTemp = datas.GetAt(1);
			Suoset.m_dtmc = strTemp;
			strTemp = datas.GetAt(2);
			Suoset.m_dtlx = atol((LPSTR)(LPCTSTR)strTemp);	
			strTemp = datas.GetAt(3);
			Suoset.m_dtcs = atol((LPSTR)(LPCTSTR)strTemp);	
			strTemp = datas.GetAt(4);
			Suoset.m_qslc = atol((LPSTR)(LPCTSTR)strTemp);
			strTemp = datas.GetAt(5);	
			Suoset.m_gglc = atol((LPSTR)(LPCTSTR)strTemp);	
			Suoset.m_dtlcbs = datas.GetAt(6);
			BOOL bRet = LPDBManage->OperElevator(&Suoset, ADD_TYPE);
			if(!bRet)
				LPDBManage->OperElevator(&Suoset, MOD_TYPE);
		}
		ar.close();
		AfxMessageBox("更新数据完成,请重新启动管理器");
		//ar.Close();
		//file.Close();
	}    
	CATCH (CFileException, e)  
	{  
		switch (e->m_cause)  
		{  
		case CFileException::accessDenied:  
			TRACE("File Access Denied\n");  
			break;  
		case CFileException::badPath:  
			TRACE("Invalid Path\n");  
			break;  
		case CFileException::diskFull:  
			TRACE("Disk Full\n");  
			break;  
		case CFileException::fileNotFound:  
			TRACE("File Not Found\n");  
			break;  
		case CFileException::hardIO:  
			TRACE("Hardware Error\n");  
			break;  
		case CFileException::lockViolation:  
			TRACE("Attemp to lock region already locked \n");  
			break;  
		case CFileException::sharingViolation:  
			TRACE("Sharing Violation -load share.exe\n");  
			break;  
		case CFileException::tooManyOpenFiles:  
			TRACE("Too Many Open Files\n");  
			break;  
		}  
	}  

	END_CATCH
	return 0;
}



void CSetDBDlg::OnBnClickedBtnChkPsw()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char pData[5];
	int iLen;
	BOOL bRet =CRadioCardProtocal::GetRadioCardProtocal()->ReadSectionPassword(pData, iLen);
	if(bRet)
	{		
		m_btPsw1 = pData[0];
		m_btPsw2 = pData[1];
		m_btPsw3 = pData[2];
		m_btPsw4 = pData[3];
	}
	if((pData[4] & 0x01) == 0x01)
		m_bSectionPsw = TRUE;

	UpdateData(FALSE);
}



void CSetDBDlg::OnBnClickedBtnChkAgent()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwID;
	BYTE byProduceFlag = 0;
	BYTE byReverseFlag = 0;
	BOOL bRet = CRadioCardProtocal::GetRadioCardProtocal()->ReadWriterID(dwID, byProduceFlag, byReverseFlag);
	if(bRet)
		m_dwWriterID = dwID;
	if((byProduceFlag & 0x01) == 0x01)
		m_bProduceFlag = TRUE;
	if((byReverseFlag & 0x01) == 0x01)
		m_bReverseWrite = TRUE;
	UpdateData(FALSE);
}

