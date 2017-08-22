// FloorCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ElevatorMgr.h"
#include "FloorCodeDlg.h"
#include "afxdialogex.h"


// CFloorCodeDlg 对话框

IMPLEMENT_DYNAMIC(CFloorCodeDlg, CDialogEx)

CFloorCodeDlg::CFloorCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFloorCodeDlg::IDD, pParent)
	, m_strFloor(_T(""))
	, m_strFloorCode(_T(""))
{

}

CFloorCodeDlg::~CFloorCodeDlg()
{
}

void CFloorCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FLOOR, m_strFloor);
	DDX_Text(pDX, IDC_EDIT_FLOOR_CODE, m_strFloorCode);
}


BEGIN_MESSAGE_MAP(CFloorCodeDlg, CDialogEx)
END_MESSAGE_MAP()


// CFloorCodeDlg 消息处理程序
