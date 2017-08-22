#if !defined(AFX_KEYINFOSET_H__1FCEDE62_4223_409D_8A9D_C7DF70F7456F__INCLUDED_)
#define AFX_KEYINFOSET_H__1FCEDE62_4223_409D_8A9D_C7DF70F7456F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Keyinfoset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyinfoset recordset

class CKeyinfoset : public CRecordset
{
public:
	CKeyinfoset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CKeyinfoset)

// Field/Param Data
	//{{AFX_FIELD(CKeyinfoset, CRecordset)
	long	m_id;
//	long    m_column2;
    long    m_klx;
	long    m_gnkh;
	long    m_sycs;
	long    m_zklx;
	long    m_qjkh1;
	long    m_qjbz1;
	long    m_qjkh2;
	long    m_qjbz2;
	long    m_qjkh3;
	long    m_qjbz3;
	long    m_qjkh4;
	long    m_qjbz4;
	long    m_qjkh5;
	long    m_qjbz5;
	long    m_qjkh6;
	long    m_qjbz6;
	long    m_qjkh7;
	long    m_qjbz7;
	long    m_qjkh8;
	long    m_qjbz8;
	long    m_qjkh9;
	long    m_qjbz9;
	long    m_qjkh10;
	long    m_qjbz10;
	CString m_jssj;
	long m_status;

	//}}AFX_FIELD
	CString  m_sn;

	BOOL    m_bSave;

	void    SetKeyinfoset(CKeyinfoset* pQuset)
	{
		m_id   = pQuset->m_id;
		m_klx  = pQuset->m_klx;
		m_gnkh = pQuset->m_gnkh;
		m_zklx = pQuset->m_zklx;
		m_sycs = pQuset->m_sycs;

		m_qjkh1 = pQuset->m_qjkh1;
		m_qjbz1 = pQuset->m_qjbz1;

		m_qjkh2 = pQuset->m_qjkh2;
		m_qjbz2 = pQuset->m_qjbz2;

		m_qjkh3 = pQuset->m_qjkh3;
		m_qjbz3 = pQuset->m_qjbz3;

		m_qjkh3 = pQuset->m_qjkh3;
		m_qjbz3 = pQuset->m_qjbz3;

		m_qjkh4 = pQuset->m_qjkh4;
		m_qjbz4= pQuset->m_qjbz4;

		m_qjkh5 = pQuset->m_qjkh5;
		m_qjbz5 = pQuset->m_qjbz5;

		m_qjkh6 = pQuset->m_qjkh6;
		m_qjbz6= pQuset->m_qjbz6;

		m_qjkh7 = pQuset->m_qjkh7;
		m_qjbz7 = pQuset->m_qjbz7;

		m_qjkh8 = pQuset->m_qjkh8;
		m_qjbz8 = pQuset->m_qjbz8;

		m_jssj   = pQuset->m_jssj;
		m_status  = pQuset->m_status;
		m_sn      = pQuset->m_sn;
		//}}AFX_FIELD_INIT
		m_nDefaultType = pQuset->m_nDefaultType;
	}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyinfoset)
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

#endif // !defined(AFX_KEYINFOSET_H__1FCEDE62_4223_409D_8A9D_C7DF70F7456F__INCLUDED_)
