// OffsetRecord.h : COffsetRecord ���ʵ��



// COffsetRecord ʵ��

// ���������� 2016��12��31��, 18:15

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Int(pFX, _T("[Offset]"), m_Offset);
	RFX_Int(pFX, _T("[Recode]"), m_Recode);

}
/////////////////////////////////////////////////////////////////////////////
// COffsetRecord ���

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


