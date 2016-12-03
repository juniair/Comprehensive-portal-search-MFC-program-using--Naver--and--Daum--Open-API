// WebBorwerDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "mfc_xml2.h"
#include "WebBorwerDlg.h"
#include "afxdialogex.h"


// CWebBorwerDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CWebBorwerDlg, CDialogEx)

CWebBorwerDlg::CWebBorwerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWebBorwerDlg::IDD, pParent)
{

}

CWebBorwerDlg::~CWebBorwerDlg()
{
}

void CWebBorwerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WEB, m_webBrower);
}


BEGIN_MESSAGE_MAP(CWebBorwerDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CWebBorwerDlg 메시지 처리기입니다.


void CWebBorwerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rect(10, 10, cx-10, cy-10);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_WEB);

	if(pEdit->GetSafeHwnd())
	{
		pEdit->MoveWindow(rect);
	}
}
