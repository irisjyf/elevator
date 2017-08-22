// ElevatorMgrDlg.h : ͷ�ļ�
//

#pragma once

#include "XTabCtrl.h"
#include "Comm\DBManage.h"
#include "Comm\SerialProtocol.h"

#ifdef MGR_USER
#define TAB_NUM      7
#elif MGR_ANGENT
#define TAB_NUM      8
#else
#define TAB_NUM      8
#endif // MGRUSER

//#define TAB_NUM_USER      7

// CElevatorMgrDlg �Ի���
class CElevatorMgrDlg : public CDialog
{
// ����
public:
	CElevatorMgrDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CElevatorMgrDlg();


// �Ի�������
	enum { IDD = IDD_TESTSKIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
    CToolBar  m_ToolBar;
	CStatusBar m_wndStatusBar;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClkSysSet();   //ϵͳ���� 
	afx_msg void OnBnClkCustomer(); //ҵ����
	afx_msg void OnBnClkManager();  //���� 
	afx_msg void OnBnClkFunction(); //���ܿ� 
	afx_msg void OnBnClkElevator(); //���ݹ��� 
	afx_msg void OnBnClkHelp();     //���� 
	afx_msg void OnBnClkExit();     //�˳� 
	afx_msg void OnBnClkAdvanced();  
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnComdlg();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

public:
	CImageList          m_ImageList;
	CXTabCtrl	        m_pTabCtrl[TAB_NUM]; //TABҳ�ؼ�;
	CArray<CWnd*,CWnd*> m_arrWnd;    //���ڶԻ�����Դ����
	POINT				m_old;

	BOOL	InitToolBar();
	BOOL	CreateDlg(CXTabCtrl *pTabCtrl,CDialogEx *pDlg,UINT iRes,CString strTitle,CSize sz);
	BOOL	InitTabCtrl();
	BOOL	SetShowState(UINT uID);
	BOOL	OpenComPort();
	BOOL	CloseComPort();
	void	ReSize();
	//��ȡͨѶ�����߳�
	//static  DWORD WINAPI FunOnDataOk(HWND hWnd, BYTE* pDatas, long shLength);		
public:
};
