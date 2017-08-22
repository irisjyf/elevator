// OffsetRecord.h : COffsetRecord 类的实现



// COffsetRecord 实现

// 代码生成在 2016年12月31日, 18:15

#include "stdafx.h"
#include "OffsetRecord.h"
IMPLEMENT_DYNAMIC(COffsetRecord, CRecordset)

COffsetRecord::COffsetRecord(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_Offset = 0;
	m_Recode = 0;
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString COffsetRecord::GetDefaultConnect()
{
	return _T("ODBC;DSN=dzs");
}

CString COffsetRecord::GetDefaultSQL()
{
	return _T("[Offset_Section]");
}

void COffsetRecord::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Int(pFX, _T("[Offset]"), m_Offset);
	RFX_Int(pFX, _T("[Recode]"), m_Recode);

}
/////////////////////////////////////////////////////////////////////////////
// COffsetRecord 诊断

#ifdef _DEBUG
void COffsetRecord::AssertValid() const
{
	CRecordset::AssertValid();
}

void COffsetRecord::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


