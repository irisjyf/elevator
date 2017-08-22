#include "StdAfx.h"
#include "MakeCardSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuoset

IMPLEMENT_DYNAMIC(CMakeCardSet, CRecordset)

CMakeCardSet::CMakeCardSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSuoset)
	m_ID     = 0;
	m_strMakecrdTime = _T("");
	m_iMakecrdNum     = 0;
	m_strDes          = _T("");
	m_nFields = 4;
	m_nDefaultType = snapshot;
	//}}AFX_FIELD_INIT
}


CString CMakeCardSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CMakeCardSet::GetDefaultSQL()
{
	return _T("[制卡信息]");
}


void CMakeCardSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[编号]"), m_ID);
	RFX_Text(pFX, _T("[制卡时间]"), m_strMakecrdTime);
	RFX_Long(pFX, _T("[制卡数量]"), m_iMakecrdNum);
	RFX_Text(pFX, _T("[备注]"), m_strDes);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSuoset diagnostics

#ifdef _DEBUG
void CMakeCardSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMakeCardSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG