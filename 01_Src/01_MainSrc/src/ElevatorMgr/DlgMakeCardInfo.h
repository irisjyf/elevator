#pragma once


// CDlgMakeCardInfo �Ի���

class CDlgMakeCardInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMakeCardInfo)

public:
	CDlgMakeCardInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMakeCardInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG_MAKECARDINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMakeCardTime;
	int m_iNum;
	CString m_szUser;
	CString m_szNote;
};
