#pragma once


// CFloorCodeDlg �Ի���

class CFloorCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloorCodeDlg)

public:
	CFloorCodeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFloorCodeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_FLOOR_CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFloor;
	CString m_strFloorCode;
};
