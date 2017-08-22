#if !defined(AFX_AGENTIDRECORD_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_)
#define AFX_AGENTIDRECORD_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Loginset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoginset recordset

class CAgentIDRecord : public CRecordset
{
public:
	CAgentIDRecord(CDatabase* pDatabase = NULL);
	CAgentIDRecord(CAgentIDRecord* pLoginset);
	~CAgentIDRecord()  {}
	DECLARE_DYNAMIC(CAgentIDRecord)

// Field/Param Data
	//{{AFX_FIELD(CLoginset, CRecordset)
	int	 m_iID;
	long	m_lAgentID;
	CString	m_szAgentDes;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgentIDRecord)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	void     SetLoginset(CAgentIDRecord* pLoginset);

	CAgentIDRecord& CAgentIDRecord::operator=(const CAgentIDRecord& vv ) //÷ÿ‘ÿ=∑˚∫≈
	{
		m_iID =  vv.m_iID;
		m_lAgentID =  vv.m_lAgentID;
		m_szAgentDes =  vv.m_szAgentDes;

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

#endif // !defined(AFX_AGENTIDRECORD_H__FFD01432_6A13_4A43_A558_2A2449303C1F__INCLUDED_)
