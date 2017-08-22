#if !defined(AFX_QUSET_H__54088402_1210_4936_9277_8D570DFEAED5__INCLUDED_)
#define AFX_QUSET_H__54088402_1210_4936_9277_8D570DFEAED5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// quset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cquset recordset

class Cquset : public CRecordset
{
public:
	Cquset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cquset)

// Field/Param Data
	//{{AFX_FIELD(Cquset, CRecordset)
	long	m_ID;
    long    m_glykh;
    CString m_glymc;
	long    m_xzms;
	long    m_sycs;

	CString	m_qssj;
	CString	m_jzsj;
    long m_ctqxms;
    long m_kydt1;
	long m_kydt2;
	long m_kydt3;
	long m_kydt4;
	CString m_dtkyc1;
	CString m_dtkyc2;
	CString m_dtkyc3;
	CString m_dtkyc4;
	CString m_dtkycxz1;
	CString m_dtkycxz2;
	CString m_dtkycxz3;
	CString m_dtkycxz4;
	long m_status;
	//}}AFX_FIELD

	CString  m_sn;
	CString  m_sjhm;

	BOOL     m_bSave;

	void    SetQuset(Cquset* pQuset);
	void	copy(const Cquset& data);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cquset)
public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUSET_H__54088402_1210_4936_9277_8D570DFEAED5__INCLUDED_)
