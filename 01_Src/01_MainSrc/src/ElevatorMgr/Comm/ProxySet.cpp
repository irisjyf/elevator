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
	return _T("[代理商信息]");
}


void CProxySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[编号]"), m_dlsbh);
	RFX_Text(pFX, _T("[代理名称]"), m_dlsmc);
	RFX_Text(pFX, _T("[手机号码]"), m_sjhm);
	RFX_Text(pFX, _T("[代理ID]"), m_dlsid);
	RFX_Text(pFX, _T("[SN]"), m_sn);
	RFX_Text(pFX, _T("[备注]"), m_bzxx);

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
