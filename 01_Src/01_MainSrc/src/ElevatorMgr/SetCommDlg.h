#pragma once

#include "Comm\SerialProtocol.h"

// CSetCommDlg 对话框

class CSetCommDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetCommDlg)

public:
	CSetCommDlg(CSerialProtocol* pSerialProtocol,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetCommDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET_COMM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaticParamHintText();
public:
	CSerialProtocol      * m_pSerialProtocol; //串口操作

	CString m_szComPort;
	int     m_dwBaudRate;
	int     m_cParity;
	int     m_cByteSize;
	int     m_cStopBits;

	CComboBox	m_ctrlStopBits;
	CComboBox	m_ctrlParity;
	CComboBox	m_ctrlComPort;
	CComboBox	m_ctrlByteSize;
	CComboBox	m_ctrlBaudRate;

	virtual BOOL OnInitDialog();
	BOOL    SetPara(BOOL bSave);
	afx_msg void OnBnClickedCommSave();
	afx_msg void OnBnClickedTestLink2();
	afx_msg void OnSize(UINT nType, int cx, int cy);


	POINT	  m_old;
	void ReSize()  
	{  
		float fsp[2];  
		POINT Newp; //获取现在对话框的大小  
		CRect recta;      
		GetClientRect(&recta);     //取客户区大小    
		Newp.x=recta.right-recta.left;  
		Newp.y=recta.bottom-recta.top;  
		fsp[0]=(float)Newp.x/m_old.x;  
		fsp[1]=(float)Newp.y/m_old.y;  
		CRect Rect;  
		int woc;  
		CPoint OldTLPoint,TLPoint; //左上角  
		CPoint OldBRPoint,BRPoint; //右下角  
		HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //列出所有控件    
		while(hwndChild)      
		{      
			woc=::GetDlgCtrlID(hwndChild);//取得ID  
			GetDlgItem(woc)->GetWindowRect(Rect);    
			ScreenToClient(Rect);    
			OldTLPoint = Rect.TopLeft();    
			TLPoint.x = long(OldTLPoint.x*fsp[0]);    
			TLPoint.y = long(OldTLPoint.y*fsp[1]);    
			OldBRPoint = Rect.BottomRight();    
			BRPoint.x = long(OldBRPoint.x *fsp[0]);    
			BRPoint.y = long(OldBRPoint.y *fsp[1]);    
			Rect.SetRect(TLPoint,BRPoint);    
			GetDlgItem(woc)->MoveWindow(Rect,TRUE);  
			hwndChild=::GetWindow(hwndChild, GW_HWNDNEXT);      
		}  
		m_old=Newp;  
	}  

};
