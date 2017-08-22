#pragma once


// CFloorCodeDlg 对话框

class CFloorCodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFloorCodeDlg)

public:
	CFloorCodeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFloorCodeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FLOOR_CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strFloor;
	CString m_strFloorCode;
};
