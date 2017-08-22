#pragma once
#include "afxwin.h"


// CSetDBDlg 对话框

class CSetDBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetDBDlg)

public:
	CSetDBDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDBDlg();

	CString m_strSectionType;
	CComboBox m_SectionType;
	CString m_strDBPath;
	int m_iAgentID;
	CString m_szAgentDes;

	CString m_szReverseRecord;
	int m_uiElevatorID;
	CString m_szElevatorTime;
	int m_uiOffset;
	DWORD m_dwAgentNo;
	CString m_szIsAgentCheck;

	CString m_szOffset;
	// 写卡器物业ID

	BYTE m_btPsw1;
	BYTE m_btPsw2;
	BYTE m_btPsw3;
	BYTE m_btPsw4;
	BOOL m_bSectionPsw;
	BOOL m_bAgent;
	// 写卡器中的物业ID
	DWORD m_dwWriterID;
	BOOL m_bReverseWrite;
	BOOL m_bProduceFlag;
	CString m_szDisableCounter;
	CString m_szPassword;
	//BOOL m_bDisCounter;

	int ExportCustomerData(CString szPathName);
	int ExportManagerData(CString szPathName);
	int ExportFuncCardData(CString szPathName);
	int ExportElevatorData(CString szPathName);
	int ImportCustomerData(CString szPathName);
	int ImportManagerData(CString szPathName);
	int ImportFuncCardData(CString szPathName);
	int ImportElevatorData(CString szPathName);
	BOOL     SetPara(BOOL bSave);

// 对话框数据
	enum { IDD = IDD_DIALOG_SET_DB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnExport();
	afx_msg void OnCbnKillfocusComboComport();
	afx_msg void OnCbnKillfocusComboComport2();
	afx_msg void OnBnClickedBtnSetoffset();
	afx_msg void OnBnClickedBtnAgentRecord();
	afx_msg void OnBnClickedBtnReadElevatorparam();
	afx_msg void OnBnClickedBtnCheckWriter();
	afx_msg void OnBnClickedBtnWriterAgentid();
	afx_msg void OnBnClickedBtnDbExport();
	afx_msg void OnBnClickedBtnDbInport();
	afx_msg void OnBnClickedBtnInportElevator();
	afx_msg void OnBnClickedBtnInportFunc();
	afx_msg void OnBnClickedBtnInportMgr();
	afx_msg void OnBnClickedBtnChkPsw();
public:
	afx_msg void OnBnClickedBtnChkAgent();
};
