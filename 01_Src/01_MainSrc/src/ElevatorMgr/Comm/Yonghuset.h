#if !defined(AFX_YONGHUSET_H__E646C97D_1951_43B6_AA23_3D2DF8DFC031__INCLUDED_)
#define AFX_YONGHUSET_H__E646C97D_1951_43B6_AA23_3D2DF8DFC031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Yonghuset.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CYonghuset recordset

class CYonghuset : public CRecordset
{
public:
	CYonghuset(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CYonghuset)

// Field/Param Data
	//{{AFX_FIELD(CYonghuset, CRecordset)
	long m_ID;
	CString	m_yzmc; //业主名称
	long	m_fjbh;

	CString m_sjhm;//
	CString m_sn;  //序列号
	CString	m_yzmp; //业主门牌
	long	m_yzkh;//卡号
	long    m_xzms; //限制模式 1次数限制，2时间显示 3两者都限制
	long	m_sycs;
	CString m_qssj;
	CString m_jzsj;
	long    m_kydt1; //可用电梯
	CString m_dtkyc1;
	CString m_dtkycxz1;
	long    m_kydt2; //可用电梯
	CString m_dtkyc2;
	CString m_dtkycxz2;
	long    m_kydt3; //可用电梯
	CString m_dtkyc3;
	CString m_dtkycxz3;
	long    m_kydt4; //可用电梯
	CString m_dtkyc4;
	CString m_dtkycxz4;
	long    m_status;


	long    m_czfs;  //操作方式，手动自动切换
	long	m_hmdcs; //黑名单次数
	//}}AFX_FIELD

	BOOL    m_bSave;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYonghuset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support

	void     SetYonghuset(CYonghuset* pYonghuset);
	CYonghuset& copy (const CYonghuset& customerData);
	CYonghuset& operator= (const CYonghuset& customerData); 
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YONGHUSET_H__E646C97D_1951_43B6_AA23_3D2DF8DFC031__INCLUDED_)
