// Loginset.cpp : implementation file
//

#include "stdafx.h"
#include "Loginset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginset

IMPLEMENT_DYNAMIC(CLoginset, CRecordset)

CLoginset::CLoginset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLoginset)
	m_column1 = _T("");
	m_column2 = _T("");
	m_column3 = _T("");
	m_column4 = _T("");
	m_column5 = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

void CLoginset::SetLoginset(CLoginset* pLoginset)
{
	m_column1 = pLoginset->m_column1;
	m_column2 = pLoginset->m_column2;
	m_column3 = pLoginset->m_column3;
	m_column4 = pLoginset->m_column4;
	m_column5 = pLoginset->m_column5;;
	m_nFields = 5;
}

CString CLoginset::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CLoginset::GetDefaultSQL()
{
	return _T("[登录管理]");
}

void CLoginset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLoginset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[用户名]"), m_column1);
	RFX_Text(pFX, _T("[密码]"), m_column2);
	RFX_Text(pFX, _T("[权限]"), m_column3);
	RFX_Text(pFX, _T("[找回密码]"), m_column4);
	RFX_Text(pFX, _T("[密码提示问题]"), m_column5);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLoginset diagnostics

#ifdef _DEBUG
void CLoginset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLoginset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
