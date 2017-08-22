#pragma once


// CFuncInfoDlg 对话框

class CFuncInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncInfoDlg)
public:
	CFuncInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFuncInfoDlg();
	void      SetPara(char cType, long lID);
	BOOL      SetPara2(BOOL bSave);
	void      SetOutPutInfo(CString strInfo);
	BOOL      WirteIC(void);
	CString		GetCardInfo();
// 对话框数据
	enum { IDD = IDD_DIALOG_FUNC_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedSavedata();
	afx_msg void OnBnClickedReadCard();
	afx_msg void OnBnClickedRepairCard();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnQuerySerial();
	afx_msg LRESULT OnUserUpdateData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadioForbiden();
	afx_msg void OnBnClickedRadioChecktime();
	afx_msg void OnBnClickedRadioBlacklist();
	afx_msg void OnBnClickedRadioInterparam();

public:
	CString m_strOutput;
	long m_sycs;
	long m_id;
	int  m_klx;
	long m_qjkh1;
	long m_qjkh2;
	long m_qjkh3;
	long m_qjkh4;
	long m_qjkh5;
	long m_qjkh6;
	long m_qjkh7;
	long m_qjkh8;
	long m_qjkh9;
	long m_qjkh10;

	//long m_qjbz1;
	//long m_qjbz2;
	//long m_qjbz3;
	//long m_qjbz4;
	//long m_qjbz5;
	//long m_qjbz6;
	//long m_qjbz7;
	//long m_qjbz8;
	//long m_qjbz9;
	//long m_qjbz10;

	//long	m_kydt;
	CTime	m_jssj;
	long	m_status;
	long	m_gnkh;

	BOOL m_bChoice1;
	BOOL m_bChoice2;
	BOOL m_bChoice3;
	BOOL m_bChoice4;
	BOOL m_bChoice5;
	BOOL m_bChoice6;
	BOOL m_bChoice7;
	BOOL m_bChoice8;
	BOOL m_bChoice9;
	BOOL m_bChoice10;
	BOOL m_bOpenCard;
	CString m_sn;
	char       m_cType;
	int m_zklx;
	afx_msg void OnBnClickedEnablecounter();
	afx_msg void OnBnClickedDisablecounter();
};
