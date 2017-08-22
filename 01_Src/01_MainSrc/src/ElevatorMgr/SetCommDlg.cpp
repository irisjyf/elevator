// SetCommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "SetCommDlg.h"
#include "afxdialogex.h"

// CSetCommDlg 对话框

IMPLEMENT_DYNAMIC(CSetCommDlg, CDialogEx)

CSetCommDlg::CSetCommDlg(CSerialProtocol* pSerialProtocol,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetCommDlg::IDD, pParent)
	, m_szComPort(_T("\\\\.\\com1"))
	, m_dwBaudRate(9600)
	, m_cParity(1)
	, m_cByteSize(1)
	, m_cStopBits(1)
{
	m_pSerialProtocol = pSerialProtocol;
}

CSetCommDlg::~CSetCommDlg()
{
}

void CSetCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_ctrlStopBits);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_ctrlParity);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_ctrlComPort);
	DDX_Control(pDX, IDC_COMBO_BYTESIZE, m_ctrlByteSize);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_ctrlBaudRate);


	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_szComPort);
	DDX_CBIndex(pDX, IDC_COMBO_BAUDRATE, m_dwBaudRate);
	DDX_CBIndex(pDX, IDC_COMBO_PARITY, m_cParity);
	DDX_CBIndex(pDX, IDC_COMBO_BYTESIZE, m_cByteSize);
	DDX_CBIndex(pDX, IDC_COMBO_STOPBITS, m_cStopBits);
}


BEGIN_MESSAGE_MAP(CSetCommDlg, CDialogEx)
	ON_STN_CLICKED(IDC_STATIC_PARAM_HINT_TEXT, &CSetCommDlg::OnStnClickedStaticParamHintText)
	ON_BN_CLICKED(IDD_COMM_SAVE, &CSetCommDlg::OnBnClickedCommSave)
	ON_BN_CLICKED(ID_TEST_LINK2, &CSetCommDlg::OnBnClickedTestLink2)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSetCommDlg 消息处理程序


void CSetCommDlg::OnStnClickedStaticParamHintText()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CSetCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetPara(FALSE);


	CRect rc(0,0,0,0);
	GetClientRect(rc);
	m_old.x=rc.right-rc.left;  
	m_old.y=rc.bottom-rc.top;  

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

BOOL    CSetCommDlg::SetPara(BOOL bSave)
{
	ASSERT(LPSerialProtocol);

	UpdateData(TRUE);

	CString strTemp;
	if (bSave)
	{
		m_ctrlComPort.GetWindowText(strTemp);
		LPSerialProtocol->m_config.m_szComPort  = strTemp;

		m_ctrlBaudRate.GetWindowText(strTemp);
		LPSerialProtocol->m_config.m_dwBaudRate  = (DWORD)_ttol(strTemp);

		m_ctrlByteSize.GetWindowText(strTemp);
		LPSerialProtocol->m_config.m_cByteSize  = (DWORD)_ttol(strTemp);

		LPSerialProtocol->m_config.m_cParity   = m_ctrlParity.GetCurSel();

	    LPSerialProtocol->m_config.m_cStopBits  = m_ctrlStopBits.GetCurSel();

		LPSerialProtocol->m_config.Save();
	}
	else
	{
		strTemp = LPSerialProtocol->m_config.m_szComPort;
		int nIndex = m_ctrlComPort.FindStringExact(0, strTemp);
		if (nIndex == -1) nIndex = 0;
		m_ctrlComPort.SetCurSel(nIndex);


		strTemp.Format(_T("%d"), LPSerialProtocol->m_config.m_dwBaudRate);
		nIndex = m_ctrlBaudRate.FindStringExact(0, strTemp);
		if (nIndex == -1) nIndex = 0;
		m_ctrlBaudRate.SetCurSel(nIndex);

		if (LPSerialProtocol->m_config.m_cByteSize == 7)
			m_ctrlByteSize.SetCurSel(0);
		else
			m_ctrlByteSize.SetCurSel(1);

		m_ctrlParity.SetCurSel( LPSerialProtocol->m_config.m_cParity);
		m_ctrlStopBits.SetCurSel(LPSerialProtocol->m_config.m_cStopBits);
	}
	
	Invalidate(TRUE);
	return TRUE;
}

void CSetCommDlg::OnBnClickedCommSave()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara(TRUE);
	LPSerialProtocol->SetConfig(LPSerialProtocol->m_config);
	LPSerialProtocol->Disconnect();
	if(LPSerialProtocol->Connect())
		AfxMessageBox("通讯参数保存成功");
}


void CSetCommDlg::OnBnClickedTestLink2()
{
	// TODO: 在此添加控件通知处理程序代码
	SetPara(TRUE);
	BOOL bRet = LPSerialProtocol->TestConnect(LPSerialProtocol->m_config);
	if(bRet)
	{
		LPSerialProtocol->Connect();
		BOOL bRet = CRadioCardProtocal::GetRadioCardProtocal()->ConnectTest();
		if(bRet)
			AfxMessageBox(_T("连接测试成功！"), MB_OK | MB_ICONINFORMATION);
		else 
			AfxMessageBox(_T("连接测试失败！"), MB_OK | MB_ICONINFORMATION);
		LPSerialProtocol->Disconnect();
		return;
	}
	AfxMessageBox(_T("连接测试失败！"), MB_OK | MB_ICONINFORMATION);
}


void CSetCommDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (nType==SIZE_RESTORED||nType==SIZE_MAXIMIZED)  
	{  
		//ReSize();  
	}
	// TODO: 在此处添加消息处理程序代码
}
