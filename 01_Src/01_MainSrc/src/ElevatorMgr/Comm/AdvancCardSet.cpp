#include "StdAfx.h"
#include "AdvancCardSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuoset

IMPLEMENT_DYNAMIC(CAdvancCardSet, CRecordset)

	CAdvancCardSet::CAdvancCardSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSuoset)
	m_ID     = 0;
	m_ckr    = _T("");
	m_sjhm   = _T("");
	m_SN     = _T("");
	m_bz     = _T("");
	m_cCklc  = _T("");

	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CAdvancCardSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CAdvancCardSet::GetDefaultSQL()
{
	return _T("[高级卡信息]");
}


void CAdvancCardSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[编号]"), m_ID);
	RFX_Text(pFX, _T("[持卡人]"), m_ckr);
	RFX_Text(pFX, _T("[手机号码]"), m_sjhm);
	RFX_Text(pFX, _T("[SN]"), m_SN);
	RFX_Text(pFX, _T("[持卡类型]"), m_cCklc);
	RFX_Text(pFX, _T("[备注]"), m_bz);;

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSuoset diagnostics

#ifdef _DEBUG
void CAdvancCardSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAdvancCardSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG