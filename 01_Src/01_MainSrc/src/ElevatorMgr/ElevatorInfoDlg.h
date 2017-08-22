#pragma once


// CElevatorInfoDlg �Ի���

class CElevatorInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CElevatorInfoDlg)

public:
	CElevatorInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CElevatorInfoDlg();
	void      SetPara(char cType, long lID);
	BOOL      SetPara2(BOOL bSave);

// �Ի�������
	enum { IDD = IDD_DIALOG_ELEVATOR_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedFloorCode();
public:

	CString	m_dtmc;
	long	m_dtbh;
	//long		m_dtcs;
	//int		m_qslc;
	//int		m_gglc;		
	char      m_cType;
	long      m_id;
	int		m_dtlx;
	int m_iFlootCount;
	int m_iStartFloor;
	int m_iCommonFloor;
};
