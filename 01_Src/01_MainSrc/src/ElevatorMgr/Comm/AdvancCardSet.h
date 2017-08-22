
#if !defined(AFX_SUOSET_H__CD79D781_7B9311_43D7_BFB777_14909110B9A91__INCLUDED_)
#define AFX_SUOSET_H__CD79D781_7B9311_43D7_BFB777_14909110B9A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CAdvancCardSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProxySet recordset

class CAdvancCardSet : public CRecordset
{
public:
	CAdvancCardSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAdvancCardSet)

	// Field/Param Data

	long  	m_ID;             //ID
	CString	m_ckr;            //持卡人
	CString m_sjhm;           //手机号码
	CString m_SN;             //SN
	CString m_bz;             //备注
    CString m_cCklc;          //持卡类型
	//}}AFX_FIELD

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuoset)
public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	void    SetProxySet(CAdvancCardSet* pAdvancCardSet)
	{
		m_ID             = pAdvancCardSet->m_ID;
		m_ckr            = pAdvancCardSet->m_ckr;
		m_sjhm           = pAdvancCardSet->m_sjhm;
		m_SN             = pAdvancCardSet->m_SN;
		m_bz             = pAdvancCardSet->m_bz;
		m_cCklc          = pAdvancCardSet->m_cCklc;
		//}}AFX_FIELD_INIT
		m_nDefaultType = pAdvancCardSet->m_nDefaultType;
	}

	// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUOSET_H__CD79D781_7B9311_43D7_BFB777_14909110B9A91__INCLUDED_)