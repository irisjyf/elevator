// Suoset.cpp : implementation file
//

#include "stdafx.h"
#include "Suoset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuoset

IMPLEMENT_DYNAMIC(CSuoset, CRecordset)

CSuoset::CSuoset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSuoset)
	m_dtbh = 0;
	m_dtmc = _T("");
	m_dtlx = 0 ;
	m_dtcs = 0;
	m_qslc = 0;
	m_gglc = 0;
	m_dtlcbs = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_bSave = 0;
}


CString CSuoset::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CSuoset::GetDefaultSQL()
{
	return _T("[������Ϣ]");
}

void CSuoset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSuoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[���ݱ��]"), m_dtbh);
	RFX_Text(pFX, _T("[��������]"), m_dtmc);
	RFX_Long(pFX, _T("[��������]"), m_dtlx);
	RFX_Long(pFX, _T("[�ܲ���]"),   m_dtcs);
	RFX_Long(pFX, _T("[��ʼ¥��]"), m_qslc);
	RFX_Long(pFX, _T("[����¥��]"), m_gglc);
	RFX_Text(pFX, _T("[¥���ʶ]"), m_dtlcbs);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSuoset diagnostics

#ifdef _DEBUG
void CSuoset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSuoset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
