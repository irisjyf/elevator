#pragma once
#include "afxwin.h"
#include "RadioCardProtocal.h"

// CCustermerInfoDlg 对话框
class CCustomerDlg;
class CCustermerInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustermerInfoDlg)

public:
	CRadioCardProtocal *m_pProtocal;
	CCustermerInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCustermerInfoDlg();

	void   SetPara(char cType, long lID);
	BOOL   SetPara2(BOOL bSave);

	void	SetCustomerData(const CYonghuset& customerdata);
	void	SetOutPutInfo(CString strInfo);
	void	ChoiceElv(CString strElv,CString &strDtkyc,CString &strDtkycxz);
	BOOL	WirteIC(CYonghuset *pYonghuset, UINT iStatus = 0, UINT iForbidenID = 0);
	void	OnBnClickedBtnQuerycard();
	void	ResetDlgData();
	void	SetParemtDlg(CCustomerDlg* pParent);
	CString	GetCardInfo(CYonghuset *pYonghuset);

	CCustomerDlg* m_pParent;

	CString m_yzmc;
	CString m_sjhm;
	long    m_fjbh;
	long    m_ID;
	long    m_yzkh;
	long    m_sycs;
	CString m_yzmp;
	COleDateTime m_tmfrom;
	COleDateTime m_tmto;
	CString     m_sn;
	CString m_dtkyc4;
	CString m_dtkyc3;
	CString m_dtkyc2;
	CString m_dtkyc1;

	CString m_dtkycxz1;
	CString m_dtkycxz2;
	CString m_dtkycxz3;
	CString m_dtkycxz4;

	char       m_cType;
	CString    m_strOutput;
	int        m_xzms; //有效期

	CString m_strElv1;
	CComboBox m_cElv1;
	CComboBox m_cElv2;
	CString m_strElv2;
	CComboBox m_cElv3;
	CString m_strElv3;
	CComboBox m_cElv4;
	CString m_strElv4;
	int     m_iOperType; //其他信息的手自动
	BOOL m_status;
	int m_hmdcs;

	BOOL	m_bUpdateData;
	BOOL	m_bReadCardFlag;
// 对话框数据
	enum { IDD = IDD_DIALOG_CUSTMER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFloorChoice();
	afx_msg void OnBnClickedRadioNum();
	afx_msg void OnBnClickedButtonFin();
	afx_msg void OnBnClickedFloorChoice2();
	afx_msg void OnBnClickedFloorChoice3();
	afx_msg void OnBnClickedFloorChoice4();
	afx_msg void OnBnClickedRepairCard2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedUserinfoCardSn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio16();
	afx_msg void OnBnClickedBtnReplace();
	afx_msg void OnBnClickedBtnReadcard();
};
