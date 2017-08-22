// ElevatorMgrDlg.h : 头文件
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

// CElevatorMgrDlg 对话框
class CElevatorMgrDlg : public CDialog
{
// 构造
public:
	CElevatorMgrDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CElevatorMgrDlg();


// 对话框数据
	enum { IDD = IDD_TESTSKIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
    CToolBar  m_ToolBar;
	CStatusBar m_wndStatusBar;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClkSysSet();   //系统设置 
	afx_msg void OnBnClkCustomer(); //业主卡
	afx_msg void OnBnClkManager();  //管理卡 
	afx_msg void OnBnClkFunction(); //功能卡 
	afx_msg void OnBnClkElevator(); //电梯管理 
	afx_msg void OnBnClkHelp();     //帮助 
	afx_msg void OnBnClkExit();     //退出 
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
	CXTabCtrl	        m_pTabCtrl[TAB_NUM]; //TAB页控件;
	CArray<CWnd*,CWnd*> m_arrWnd;    //用于对话框资源析构
	POINT				m_old;

	BOOL	InitToolBar();
	BOOL	CreateDlg(CXTabCtrl *pTabCtrl,CDialogEx *pDlg,UINT iRes,CString strTitle,CSize sz);
	BOOL	InitTabCtrl();
	BOOL	SetShowState(UINT uID);
	BOOL	OpenComPort();
	BOOL	CloseComPort();
	void	ReSize();
	//读取通讯参数线程
	//static  DWORD WINAPI FunOnDataOk(HWND hWnd, BYTE* pDatas, long shLength);		
public:
};
