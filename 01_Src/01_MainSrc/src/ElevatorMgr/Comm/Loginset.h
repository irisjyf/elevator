#if !defined(AFX_LOGINSET_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_)
#define AFX_LOGINSET_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Loginset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginset recordset

class CLoginset : public CRecordset
{
public:
	CLoginset(CDatabase* pDatabase = NULL);
	CLoginset(CLoginset* pLoginset);
	~CLoginset()  {}
	DECLARE_DYNAMIC(CLoginset)

// Field/Param Data
	//{{AFX_FIELD(CLoginset, CRecordset)
	CString	m_column1;
	CString	m_column2;
	CString	m_column3;
	CString	m_column4;
	CString	m_column5;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	void     SetLoginset(CLoginset* pLoginset);

	CLoginset& CLoginset::operator=(const CLoginset& vv ) //÷ÿ‘ÿ=∑˚∫≈
	{
		m_column1 =  vv.m_column1;
		m_column2 =  vv.m_column2;
		m_column3 =  vv.m_column3;
		m_column4 =  vv.m_column4;
		m_column5 =  vv.m_column5;

		return *this;
	}


// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINSET_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_)
