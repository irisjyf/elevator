#include "StdAfx.h"
#include "ProxySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuoset

IMPLEMENT_DYNAMIC(CProxySet, CRecordset)

	CProxySet::CProxySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSuoset)
	m_dlsbh = 0;
	m_dlsmc = _T("");
	m_sjhm = _T("");
	m_dlsid =_T("");
	m_bzxx   = _T("");
	m_sn     = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CProxySet::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CProxySet::GetDefaultSQL()
{
	return _T("[��������Ϣ]");
}


void CProxySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[���]"), m_dlsbh);
	RFX_Text(pFX, _T("[��������]"), m_dlsmc);
	RFX_Text(pFX, _T("[�ֻ�����]"), m_sjhm);
	RFX_Text(pFX, _T("[����ID]"), m_dlsid);
	RFX_Text(pFX, _T("[SN]"), m_sn);
	RFX_Text(pFX, _T("[��ע]"), m_bzxx);

	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSuoset diagnostics

#ifdef _DEBUG
void CProxySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProxySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
