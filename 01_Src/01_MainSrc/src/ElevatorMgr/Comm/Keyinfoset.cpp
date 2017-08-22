// Keyinfoset.cpp : implementation file
//

#include "stdafx.h"
#include "Keyinfoset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyinfoset

IMPLEMENT_DYNAMIC(CKeyinfoset, CRecordset)

CKeyinfoset::CKeyinfoset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CKeyinfoset)
		m_id=0;
//	long    m_column2;
        m_klx=0;
	    m_gnkh=0;
	    m_sycs=500;
	    m_zklx = 0;
	    m_qjkh1=0;
	    m_qjbz1=0;
	    m_qjkh2=0;
	    m_qjbz2=0;
	    m_qjkh3=0;
	    m_qjbz3=0;
	    m_qjkh4=0;
	    m_qjbz4=0;
	    m_qjkh5=0;
	    m_qjbz5=0;
	    m_qjkh6=0;
	    m_qjbz6=0;
	    m_qjkh7=0;
	    m_qjbz7=0;
	    m_qjkh8=0;
	    m_qjbz8=0;
	    m_qjkh9=0;
	    m_qjbz9=0;
	    m_qjkh10=0;
	    m_qjbz10=0;
	    m_jssj=_T("16-01-01 00:00");
		m_status=0;
		m_sn  =_T("");
	    m_nFields = 28;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_bSave =  FALSE;
}


CString CKeyinfoset::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CKeyinfoset::GetDefaultSQL()
{
	return _T("[功能卡信息]");
}

void CKeyinfoset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKeyinfoset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[编号]"), m_id);
	RFX_Long(pFX, _T("[卡类型]"), m_klx);
	RFX_Long(pFX, _T("[卡号]"), m_gnkh);
	RFX_Long(pFX, _T("[使用次数]"), m_sycs);
	RFX_Long(pFX, _T("[子卡类型]"), m_zklx);
	RFX_Long(pFX, _T("[启禁卡号一]"), m_qjkh1);
	RFX_Long(pFX, _T("[启禁标志一]"), m_qjbz1);
	RFX_Long(pFX, _T("[启禁卡号二]"), m_qjkh2);
	RFX_Long(pFX, _T("[启禁标志二]"), m_qjbz2);
	RFX_Long(pFX, _T("[启禁卡号三]"), m_qjkh3);
	RFX_Long(pFX, _T("[启禁标志三]"), m_qjbz3);
	RFX_Long(pFX, _T("[启禁卡号四]"), m_qjkh4);
	RFX_Long(pFX, _T("[启禁标志四]"), m_qjbz4);
	RFX_Long(pFX, _T("[启禁卡号五]"), m_qjkh5);
	RFX_Long(pFX, _T("[启禁标志五]"), m_qjbz5);
	RFX_Long(pFX, _T("[启禁卡号六]"), m_qjkh6);
	RFX_Long(pFX, _T("[启禁标志六]"), m_qjbz6);
	RFX_Long(pFX, _T("[启禁卡号七]"), m_qjkh7);
	RFX_Long(pFX, _T("[启禁标志七]"), m_qjbz7);
	RFX_Long(pFX, _T("[启禁卡号八]"), m_qjkh8);
	RFX_Long(pFX, _T("[启禁标志八]"), m_qjbz8);
	RFX_Long(pFX, _T("[启禁卡号九]"), m_qjkh9);
	RFX_Long(pFX, _T("[启禁标志九]"), m_qjbz9);
	RFX_Long(pFX, _T("[启禁卡号十]"), m_qjkh10);
	RFX_Long(pFX, _T("[启禁标志十]"), m_qjbz10);
	RFX_Text(pFX, _T("[校时时间]"),   m_jssj  );
	RFX_Long(pFX, _T("[卡状态]"),     m_status);
	RFX_Text(pFX, _T("[SN]"),     m_sn);


	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CKeyinfoset diagnostics

#ifdef _DEBUG
void CKeyinfoset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CKeyinfoset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
