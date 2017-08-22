// quset.cpp : implementation file
//

#include "stdafx.h"
#include "quset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cquset

IMPLEMENT_DYNAMIC(Cquset, CRecordset)

Cquset::Cquset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Cquset)
	m_ID = 0;
    m_glykh=0;
    m_glymc="";
	m_xzms=0;
	m_sycs=500;

	//m_qssj=_T("16-01-01 00:00:00");
	//m_jzsj=_T("17-01-01 00:00:00");
	CTime tmNow = ::time(NULL);
	//m_qssj = _T("17-01-01 00:00:00");
	m_qssj.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		tmNow.GetYear(), 
		tmNow.GetMonth(), 
		tmNow.GetDay(), 
		tmNow.GetHour(), 
		tmNow.GetMinute(),
		tmNow.GetSecond());//_T("17-01-01 00:00:00");
	//m_jzsj=_T("18-01-01 00:00:00");
	m_jzsj.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		tmNow.GetYear() + 1, 
		tmNow.GetMonth(), 
		tmNow.GetDay(), 
		tmNow.GetHour(), 
		tmNow.GetMinute(),
		tmNow.GetSecond());//_T("17-01-01 00:00:00");
	m_ctqxms=0;
	m_kydt1=0;
	m_kydt2=0;
	m_kydt3=0;
	m_kydt4=0;
	m_dtkyc1="";
	m_dtkyc2="";
	m_dtkyc3="";
	m_dtkyc4="";
	m_dtkycxz1="";
	m_dtkycxz2="";
	m_dtkycxz3="";
	m_dtkycxz4="";
	m_status=0;
	m_sjhm =""; 
    m_sn   =""; 
    m_nFields = 23;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_bSave = FALSE;
}


CString Cquset::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString Cquset::GetDefaultSQL()
{
	return _T("[管理卡信息]");
}

void Cquset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Cquset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[编号]"), m_ID);
	RFX_Long(pFX, _T("[卡号]"),m_glykh);
	RFX_Text(pFX, _T("[管理员名称]"), m_glymc);
	RFX_Text(pFX, _T("[手机号码]"),m_sjhm);
	RFX_Text(pFX, _T("[SN]"),m_sn);
    RFX_Long(pFX, _T("[限制模式]"),m_xzms);
	RFX_Long(pFX, _T("[使用次数]"),m_sycs);

	RFX_Text(pFX, _T("[起始日期]"), m_qssj);
	RFX_Text(pFX, _T("[截至日期]"), m_jzsj);
	RFX_Long(pFX, _T("[乘梯权限模式]"),m_ctqxms);
	RFX_Long(pFX, _T("[可用电梯一]"),m_kydt1);
	RFX_Text(pFX, _T("[电梯一可用层]"), m_dtkyc1);
	RFX_Text(pFX, _T("[电梯一可用层下载]"), m_dtkycxz1);
	RFX_Long(pFX, _T("[可用电梯二]"),m_kydt2);
	RFX_Text(pFX, _T("[电梯二可用层]"), m_dtkyc2);
	RFX_Text(pFX, _T("[电梯二可用层下载]"), m_dtkycxz2);
	RFX_Long(pFX, _T("[可用电梯三]"),m_kydt3);
	RFX_Text(pFX, _T("[电梯三可用层]"), m_dtkyc3);
	RFX_Text(pFX, _T("[电梯三可用层下载]"), m_dtkycxz3);
	RFX_Long(pFX, _T("[可用电梯四]"),m_kydt4);
	RFX_Text(pFX, _T("[电梯四可用层]"), m_dtkyc4);
	RFX_Text(pFX, _T("[电梯四可用层下载]"), m_dtkycxz4);
	RFX_Long(pFX, _T("[卡状态]"),m_status);
	//}}AFX_FIELD_MAP
}



void Cquset::SetQuset(Cquset* pQuset)
{
	if(!pQuset)
		return;
	m_ID   = pQuset->m_ID;
	m_glykh = pQuset->m_glykh;
	m_glymc = pQuset->m_glymc;
	m_xzms = pQuset->m_xzms;
	m_sycs = pQuset->m_sycs;

	m_qssj = pQuset->m_qssj;
	m_jzsj   = pQuset->m_jzsj;

	m_ctqxms = pQuset->m_ctqxms;
	m_kydt1 = pQuset->m_kydt1;
	m_kydt2 = pQuset->m_kydt2;
	m_kydt3 = pQuset->m_kydt3;
	m_kydt4 = pQuset->m_kydt4;

	m_dtkyc1 = pQuset->m_dtkyc1;
	m_dtkyc2 = pQuset->m_dtkyc2;
	m_dtkyc3 = pQuset->m_dtkyc3;
	m_dtkyc4 = pQuset->m_dtkyc4;

	m_dtkycxz1 = pQuset->m_dtkycxz1;
	m_dtkycxz2 = pQuset->m_dtkycxz2;
	m_dtkycxz3 = pQuset->m_dtkycxz3;
	m_dtkycxz4 = pQuset->m_dtkycxz4;

	m_status = pQuset->m_status;

	m_sn   = pQuset->m_sn;
	m_sjhm = pQuset->m_sjhm;

	//}}AFX_FIELD_INIT
	m_nDefaultType = pQuset->m_nDefaultType;
}

void Cquset::copy(const Cquset& data)
{
	m_ID   = data.m_ID;
	m_glykh = data.m_glykh;
	m_glymc = data.m_glymc;
	m_xzms = data.m_xzms;
	m_sycs = data.m_sycs;

	m_qssj = data.m_qssj;
	m_jzsj   = data.m_jzsj;

	m_ctqxms = data.m_ctqxms;
	m_kydt1 = data.m_kydt1;
	m_kydt2 = data.m_kydt2;
	m_kydt3 = data.m_kydt3;
	m_kydt4 = data.m_kydt4;

	m_dtkyc1 = data.m_dtkyc1;
	m_dtkyc2 = data.m_dtkyc2;
	m_dtkyc3 = data.m_dtkyc3;
	m_dtkyc4 = data.m_dtkyc4;

	m_dtkycxz1 = data.m_dtkycxz1;
	m_dtkycxz2 = data.m_dtkycxz2;
	m_dtkycxz3 = data.m_dtkycxz3;
	m_dtkycxz4 = data.m_dtkycxz4;


	m_sn   = data.m_sn;
	m_sjhm = data.m_sjhm;

	//}}AFX_FIELD_INIT
	m_nDefaultType = data.m_nDefaultType;
}

/////////////////////////////////////////////////////////////////////////////
// Cquset diagnostics

#ifdef _DEBUG
void Cquset::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cquset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
