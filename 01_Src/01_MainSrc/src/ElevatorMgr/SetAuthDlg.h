#pragma once
#include "afxcmn.h"


// CSetAuthDlg �Ի���

class CSetAuthDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSetAuthDlg)

public:
	CSetAuthDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetAuthDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET_AUTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedAuthAdd();
	afx_msg void OnBnClickedAuthMod();
	CListCtrl m_AuthList;
	virtual BOOL OnInitDialog();
	BOOL      ShowTable();
	afx_msg void OnBnClickedAuthDel();
	afx_msg void OnNMDblclkAuthList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	POINT	  m_old;
	void ReSize()  
	{  
		float fsp[2];  
		POINT Newp; //��ȡ���ڶԻ���Ĵ�С  
		CRect recta;      
		GetClientRect(&recta);     //ȡ�ͻ�����С    
		Newp.x=recta.right-recta.left;  
		Newp.y=recta.bottom-recta.top;  
		fsp[0]=(float)Newp.x/m_old.x;  
		fsp[1]=(float)Newp.y/m_old.y;  
		CRect Rect;  
		int woc;  
		CPoint OldTLPoint,TLPoint; //���Ͻ�  
		CPoint OldBRPoint,BRPoint; //���½�  
		HWND  hwndChild=::GetWindow(m_hWnd,GW_CHILD);  //�г����пؼ�    
		while(hwndChild)      
		{      
			woc=::GetDlgCtrlID(hwndChild);//ȡ��ID  
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
	virtual void OnOK();
	virtual void OnCancel();
};
