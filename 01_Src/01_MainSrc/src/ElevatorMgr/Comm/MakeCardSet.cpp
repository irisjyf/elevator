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
	return _T("[�ƿ���Ϣ]");
}


void CMakeCardSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[���]"), m_ID);
	RFX_Text(pFX, _T("[�ƿ�ʱ��]"), m_strMakecrdTime);
	RFX_Long(pFX, _T("[�ƿ�����]"), m_iMakecrdNum);
	RFX_Text(pFX, _T("[��ע]"), m_strDes);

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