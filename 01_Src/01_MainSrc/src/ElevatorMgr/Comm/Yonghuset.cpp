// Yonghuset.cpp : implementation file
//

#include "stdafx.h"
#include "Yonghuset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYonghuset

IMPLEMENT_DYNAMIC(CYonghuset, CRecordset)

CYonghuset::CYonghuset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CYonghuset)
    m_ID=0;
	m_yzmc =_T("");
	m_fjbh=0;
	m_yzmp=_T("");
	m_yzkh=1;
	m_xzms=0;
	m_sycs=500;
	
	CTime tmNow = ::time(NULL);
	////m_qssj = _T("17-01-01 00:00:00");
	//m_qssj.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
	//	tmNow.GetYear(), 
	//	tmNow.GetMonth(), 
	//	tmNow.GetDay(), 
	//	tmNow.GetHour(), 
	//	tmNow.GetMinute(),
	//	tmNow.GetSecond());//_T("17-01-01 00:00:00");

	m_qssj = _T("17-01-01 00:00:00");
	//m_jzsj=_T("18-01-01 00:00:00");
	m_jzsj.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		tmNow.GetYear() + 1, 
		tmNow.GetMonth(), 
		tmNow.GetDay(), 
		tmNow.GetHour(), 
		tmNow.GetMinute(),
		tmNow.GetSecond());//_T("17-01-01 00:00:00");

	m_kydt1=-1;
	m_dtkyc1=_T("");
	m_kydt2=-1;
	m_dtkyc2=_T("");
	m_kydt3=-1;
	m_dtkyc3=_T("");
	m_kydt4=0;
	m_dtkyc4=_T("");

	m_dtkycxz1=_T("");
	m_dtkycxz2=_T("");
	m_dtkycxz3=_T("");
	m_dtkycxz4=_T("");

	m_status=0;
	//	m_column4 = 0;
	//	m_column5 = FALSE;
	m_nFields = 26;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;

	m_sjhm  =_T("");
	m_czfs  =0; //操作方式，手动自动切换
	m_hmdcs =0;//黑名单次数

	m_bSave = FALSE;
}


CString CYonghuset::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString CYonghuset::GetDefaultSQL()
{
	return _T("[业主卡信息]");
}

void CYonghuset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CYonghuset)

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX,_T("[编号]"),m_ID);
	RFX_Text(pFX, _T("[业主姓名]"), m_yzmc);
	RFX_Text(pFX, _T("[手机号码]"), m_sjhm);//
	RFX_Text(pFX, _T("[SN]"), m_sn);//
	RFX_Long(pFX, _T("[房间编号]"), m_fjbh);
	RFX_Text(pFX, _T("[业主门牌]"), m_yzmp);
	RFX_Long(pFX, _T("[卡号]"), m_yzkh);
	RFX_Long(pFX,_T("[限制模式]"),m_xzms);
	RFX_Long(pFX, _T("[使用次数]"), m_sycs);
	RFX_Text(pFX, _T("[起始日期]"), m_qssj);
	RFX_Text(pFX, _T("[截止日期]"), m_jzsj);
	RFX_Long(pFX, _T("[可用电梯一]"), m_kydt1);
	RFX_Text(pFX, _T("[电梯一可用层]"), m_dtkyc1);
	RFX_Text(pFX, _T("[电梯一可用层下载]"), m_dtkycxz1);
	RFX_Long(pFX, _T("[可用电梯二]"), m_kydt2);
	RFX_Text(pFX, _T("[电梯二可用层]"), m_dtkyc2);
	RFX_Text(pFX, _T("[电梯二可用层下载]"), m_dtkycxz2);
	RFX_Long(pFX, _T("[可用电梯三]"), m_kydt3);
	RFX_Text(pFX, _T("[电梯三可用层]"), m_dtkyc3);
	RFX_Text(pFX, _T("[电梯三可用层下载]"), m_dtkycxz3);
	RFX_Long(pFX, _T("[可用电梯四]"), m_kydt4);//
	RFX_Text(pFX, _T("[电梯四可用层]"), m_dtkyc4);//
	RFX_Text(pFX, _T("[电梯四可用层下载]"), m_dtkycxz4);//
	RFX_Long(pFX, _T("[卡状态]"), m_status);
	RFX_Long(pFX, _T("[操作方式]"), m_czfs);//
	RFX_Long(pFX, _T("[黑名单次数]"), m_hmdcs);//
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CYonghuset diagnostics

#ifdef _DEBUG
void CYonghuset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CYonghuset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


void CYonghuset::SetYonghuset(CYonghuset* pYonghuset)
{
	m_ID   = pYonghuset->m_ID;
	m_yzmc = pYonghuset->m_yzmc;
	m_fjbh = pYonghuset->m_fjbh;
	m_yzmp = pYonghuset->m_yzmp;
	m_yzkh = pYonghuset->m_yzkh;
	m_xzms = pYonghuset->m_xzms;
	m_sycs = pYonghuset->m_sycs;

	m_qssj = pYonghuset->m_qssj;
	m_jzsj = pYonghuset->m_jzsj;
	m_kydt1=pYonghuset->m_kydt1;
	m_dtkyc1=pYonghuset->m_dtkyc1;
	m_kydt2=pYonghuset->m_kydt2;
	m_dtkyc2=pYonghuset->m_dtkyc2;
	m_kydt3=pYonghuset->m_kydt3;
	m_dtkyc3=pYonghuset->m_dtkyc3;
	m_kydt4=pYonghuset->m_kydt4;
	m_dtkyc4=pYonghuset->m_dtkyc4;

	m_dtkycxz1=pYonghuset->m_dtkycxz1;
	m_dtkycxz2=pYonghuset->m_dtkycxz2;
	m_dtkycxz3=pYonghuset->m_dtkycxz3;
	m_dtkycxz4=pYonghuset->m_dtkycxz4;

	m_status=pYonghuset->m_status;

	m_sjhm    = pYonghuset->m_sjhm;
	m_sn      = pYonghuset->m_sn;
	m_czfs    = pYonghuset->m_czfs;
	m_hmdcs   = pYonghuset->m_hmdcs;
;
	m_nFields = pYonghuset->m_nFields;
	//}}AFX_FIELD_INIT
	m_nDefaultType = pYonghuset->m_nDefaultType;
}

CYonghuset& CYonghuset::copy (const CYonghuset& customerData)
{
	m_ID   = customerData.m_ID;
	m_yzmc =  customerData.m_yzmc;
	m_fjbh =  customerData.m_fjbh;
	m_yzmp =  customerData.m_yzmp;
	m_yzkh = customerData.m_yzkh;
	m_xzms = customerData.m_xzms;
	m_sycs = customerData.m_sycs;

	m_qssj = customerData.m_qssj;
	m_jzsj = customerData.m_jzsj;
	m_kydt1 = customerData.m_kydt1;
	m_dtkyc1 = customerData.m_dtkyc1;
	m_kydt2 = customerData.m_kydt2;
	m_dtkyc2 = customerData.m_dtkyc2;
	m_kydt3 = customerData.m_kydt3;
	m_dtkyc3 = customerData.m_dtkyc3;
	m_kydt4 = customerData.m_kydt4;
	m_dtkyc4 = customerData.m_dtkyc4;

	m_dtkycxz1 = customerData.m_dtkycxz1;
	m_dtkycxz2 = customerData.m_dtkycxz2;
	m_dtkycxz3 = customerData.m_dtkycxz3;
	m_dtkycxz4 = customerData.m_dtkycxz4;

	m_status = customerData.m_status;

	m_sjhm    = customerData.m_sjhm;
	m_sn      = customerData.m_sn;
	m_czfs    = customerData.m_czfs;
	m_hmdcs   = customerData.m_hmdcs;
	;
	m_nFields = customerData.m_nFields;
	//}}AFX_FIELD_INIT
	m_nDefaultType = customerData.m_nDefaultType;
	return *this;
}