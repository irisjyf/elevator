
#if !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB777_14909110B9A91__INCLUDED_)
#define AFX_SUOSET_H__CD79D781_7B93_43D7_BFB777_14909110B9A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMakeCardSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProxySet recordset

class CMakeCardSet : public CRecordset
{
public:
	CMakeCardSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMakeCardSet)

	// Field/Param Data

	long  	m_ID;             //ID
	CString	m_strMakecrdTime;//制卡时间
	long   	m_iMakecrdNum;   //制卡数量
	CString m_strDes;        //备注信息
	CString m_strUser;		 //制卡人
	//}}AFX_FIELD

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuoset)
public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	void    SetProxySet(CMakeCardSet* pMakeCardSet)
	{
		m_ID             = pMakeCardSet->m_ID;
		m_strMakecrdTime = pMakeCardSet->m_strMakecrdTime;
		m_iMakecrdNum    = pMakeCardSet->m_iMakecrdNum;
		m_strDes    = pMakeCardSet->m_strDes;
		//}}AFX_FIELD_INIT
		m_nDefaultType = pMakeCardSet->m_nDefaultType;
	}

	// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB777_14909110B9A91__INCLUDED_)