
#if !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A91__INCLUDED_)
#define AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProxySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProxySet recordset

class CProxySet : public CRecordset
{
public:
	CProxySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CProxySet)

	// Field/Param Data
	//{{AFX_FIELD(CSuoset, CRecordset)
	long	m_dlsbh;//代理编号
	CString	m_dlsmc;//代理名称
	CString	m_sjhm; //手机号码
	CString	m_dlsid;//代理ID
	CString	m_bzxx;  //代理ID
	CString	m_sn;    //代理ID
	//}}AFX_FIELD

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuoset)
public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	void    SetProxySet(CProxySet* pProxySet)
	{
		m_dlsbh = pProxySet->m_dlsbh;
		m_dlsmc = pProxySet->m_dlsmc;
		m_sjhm = pProxySet->m_sjhm;
		m_dlsid = pProxySet->m_dlsid;
		m_bzxx = pProxySet->m_bzxx;
		m_sn    = pProxySet->m_sn;
	
		//}}AFX_FIELD_INIT
		m_nDefaultType = pProxySet->m_nDefaultType;
	}

	// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A91__INCLUDED_)