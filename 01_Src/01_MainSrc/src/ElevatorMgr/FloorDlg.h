#pragma once


// CFloorDlg 对话框

class CFloorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloorDlg)

public:
	CFloorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFloorDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FLOOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck65();
	void         OnButtonClicked(UINT   uId) ;

public:
	int sumlc;
	int qslc;
	int gglc;
	CString dtkycxz;
	CString kylc;
	unsigned char dtkycxznum[3][64];

	char      m_cType;
	long      m_id;
	void      SetPara(char cType, long lID)
	{
		m_id    = lID;
		m_cType = cType;
	}

};
