#pragma once
#include "atlcomtime.h"
#include "afxwin.h"


// CManagerInfoDlg 对话框
class CManagerDlg;

class CManagerInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManagerInfoDlg)

public:
	CManagerInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CManagerInfoDlg();
	BOOL    SetPara2(BOOL bSave);
	void    SetOutPutInfo(CString strInfo);
	void    ChoiceElv(CString strElv,CString &strDtkyc,CString &strDtkycxz);
	BOOL    WirteIC(Cquset *pQuset, UINT iSatus = 0, UINT iForbidenID = 0);
	void    SetPara(char cType, long lID);
	void	SetMgrData(const Cquset& pQuset);
	void	ResetDlgData();
	void	SetParent(CManagerDlg* pParent);
	CString	GetCardInfo(Cquset *p);

	CString m_glymc;
	long    m_glykh;
	long    m_sycs;
	COleDateTime m_tmfrom;
	COleDateTime m_tmto;
	CString m_dtkyc1;
	CString m_dtkyc2;
	CString m_dtkyc3;
	CString m_dtkyc4;

	CString m_dtkycxz1;
	CString m_dtkycxz2;
	CString m_dtkycxz3;
	CString m_dtkycxz4;

	CComboBox m_cElv1;
	CString m_strElv1;
	CComboBox m_cElv2;
	CString m_strElv2;
	CComboBox m_cElv3;
	CString m_strElv3;
	CComboBox m_cElv4;
	CString m_strElv4;

	CString m_sn;
	long    m_ID;
	int     m_xzms;
	int     m_ctqxms;
	CString m_sjhm;

	CString m_strOutput;
	char    m_cType;

	BOOL	m_bUpdateData;
	BOOL	m_bReadCardFlag;
// 对话框数据
	enum { IDD = IDD_DIALOG_MANAGER_INFO };
private:
	CManagerDlg* m_pParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedManagerFloorChoice();
	afx_msg void OnBnClickedManagerFloorChoice2();
	afx_msg void OnBnClickedManagerFloorChoice3();
	afx_msg void OnBnClickedManagerFloorChoice4();
	afx_msg void OnBnClickedRepairCrad3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSavedata();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedUserinfoCardSn2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedBtnReplace();
};

