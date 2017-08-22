// Loginset.cpp : implementation file
//

#include "stdafx.h"
#include "AgentIDRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgentIDRecord

IMPLEMENT_DYNAMIC(CAgentIDRecord, CRecordset)

CAgentIDRecord::CAgentIDRecord(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAgentIDRecord)
	m_iID = 0;
	m_lAgentID = 0;
	m_szAgentDes = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

void CAgentIDRecord::SetLoginset(CAgentIDRecord* pLoginset)
{
	m_iID = pLoginset->m_iID;
	m_lAgentID = pLoginset->m_lAgentID;
	m_szAgentDes = pLoginset->m_szAgentDes;
	m_nFields = 3;
}

CString CAgentIDRecord::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CAgentIDRecord::GetDefaultSQL()
{
	return _T("[AgentInfo]");
}

void CAgentIDRecord::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAgentIDRecord)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ID]"), m_iID);
	RFX_Long(pFX, _T("[AGENTID]"), m_lAgentID);
	RFX_Text(pFX, _T("[AGENTDES]"), m_szAgentDes);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CAgentIDRecord diagnostics

#ifdef _DEBUG
void CAgentIDRecord::AssertValid() const
{
	CRecordset::AssertValid();
}

void CAgentIDRecord::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
