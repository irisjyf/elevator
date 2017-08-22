#if !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A9__INCLUDED_)
#define AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Suoset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSuoset recordset

class CSuoset : public CRecordset
{
public:
	CSuoset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSuoset)

// Field/Param Data
	//{{AFX_FIELD(CSuoset, CRecordset)
	long	m_dtbh;
	CString	m_dtmc;
	long	m_dtlx;
	long	m_dtcs;
	long	m_qslc;
	long	m_gglc;
	CString	m_dtlcbs;//电梯楼层标识

	BOOL    m_bSave;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuoset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	void    SetSuoset(CSuoset* pSuoset)
	{
		m_dtbh   = pSuoset->m_dtbh;
		m_dtmc = pSuoset->m_dtmc;
		m_dtlx = pSuoset->m_dtlx;
		m_dtcs = pSuoset->m_dtcs;
		m_qslc = pSuoset->m_qslc;
		m_gglc = pSuoset->m_gglc;
		m_dtlcbs = pSuoset->m_dtlcbs;

		ElvCodeParse();
		//}}AFX_FIELD_INIT
		m_nDefaultType = pSuoset->m_nDefaultType;
	}

	CMap<CString,LPCTSTR,CString,LPCTSTR>        m_mapElvCode;// 电梯编码关系 比如1楼用S标识

	void  ElvCodeParse()
	{
		if (m_dtlcbs.IsEmpty())
			return;
		int iIndex = 0;
		CString strFrom,strTo;
		while(GetParaTag(m_dtlcbs,strFrom,strTo))
		{
			if (!m_mapElvCode.Lookup(strFrom,strTo))
			{
				m_mapElvCode.SetAt(strFrom,strTo);
			}
			//异常处理，防止意外情况下的死循环 
			if ( iIndex++ > 64)	
				break;
		}
	}

	void  ElvCodeAdd(CString strFrom,CString strTo)
	{
		if (0 ==strTo.CompareNoCase(strFrom)||strTo.IsEmpty())
			return;
		m_mapElvCode.SetAt(strFrom,strTo);
	}

	CString ElvCodeMake()
	{
		CString strPara,strFrom,strTo;

		POSITION pos = m_mapElvCode.GetStartPosition();
		while(pos)
		{
			m_mapElvCode.GetNextAssoc(pos,strFrom,strTo);

			if (0 ==strTo.CompareNoCase(strFrom))
				continue;
		
			strPara = strPara+ strFrom +","+strTo+";";
		}

		return strPara;
	}

	bool GetParaTag(CString &strPara,CString &strFrom,CString &strTo)
	{
		strTo   = _T("");
		strFrom = _T("");
		if (strPara.IsEmpty())
			return false;

		strPara.Trim();
		int iPos = strPara.Find(',');
		if (iPos < 0)
		{
			return false;
		}

		strFrom = strPara.Left(iPos);
		strPara = strPara.Right(strPara.GetLength() -iPos - 1);
		iPos = strPara.Find(";");
		if (iPos < 0)
		{
			return false;
		}

		strTo = strPara.Left(iPos);
		strPara = strPara.Right(strPara.GetLength() -strTo.GetLength() - 1);

		return true;
	}
// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUOSET_H__CD79D781_7B93_43D7_BFB7_14909110B9A9__INCLUDED_)
