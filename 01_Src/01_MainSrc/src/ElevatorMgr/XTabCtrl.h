/**************************************************
* Copyright (c) 北京和利时系统工程有限公司
* All rights reserved.
* 文件名称: EnumType.h
* 摘    要：接口文件，添加4个tap页
* 当前版本：3.0
* 作    者：hn
* 创建日期：2010.9
**************************************************/
#if !defined(AFX_XTABCTRL_H__34CE6B8D_C11F_49A7_BD19_C7AF3BDA0C0C__INCLUDED_)
#define AFX_XTABCTRL_H__34CE6B8D_C11F_49A7_BD19_C7AF3BDA0C0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XTabCtrl.h : header file
//

#define  USER_SELCHANGE_MSG WM_USER + 1100
/////////////////////////////////////////////////////////////////////////////
// CXTabCtrl window
#include <afxtempl.h>
#include <afxcmn.h>
class CXTabCtrl : public CTabCtrl
{
public:
	CArray<BOOL, BOOL> m_arrayStatusTab; //** enabled Y\N
	
	POINT m_ptTabs;
	COLORREF m_crSelected;
	COLORREF m_crDisabled;
	COLORREF m_crNormal;
	COLORREF m_crMouseOver;

	int  m_iIcon;
	
	int m_iSelectedTab;
	
	int m_iIndexMouseOver;
	
	bool m_bMouseOver;
	bool m_bColorMouseOver;
	bool m_bColorNormal;
	bool m_bColorDisabled;
	bool m_bColorSelected;
// Construction
public:
	CXTabCtrl();

// Attributes
public:

// Operations
public:
	void AddTab(CWnd* pWnd, LPTSTR lpszCaption, int iImage =0);
	void EnableTab(int iIndex, BOOL bEnable = TRUE);
	BOOL SelectTab(int iIndex);
	void DeleteAllTabs();
	void DeleteTab(int iIndex);
	void SetTopLeftCorner(CPoint pt);
	BOOL IsTabEnabled(int iIndex);
	
	void SetDisabledColor(COLORREF cr);
	void SetSelectedColor(COLORREF cr);
	void SetNormalColor(COLORREF cr);
	void SetMouseOverColor(COLORREF cr);
	BOOL SelectNextTab(BOOL bForward);
	BOOL SelectTabByName(LPCTSTR lpszTabCaption);
	void ChangeTab(int iIndex, CWnd* pNewTab, LPTSTR lpszCaption, int iImage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTabCtrl)
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();

	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CXTabCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XTABCTRL_H__34CE6B8D_C11F_49A7_BD19_C7AF3BDA0C0C__INCLUDED_)
