#pragma once


// CFloorDlg �Ի���

class CFloorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloorDlg)

public:
	CFloorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFloorDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FLOOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
