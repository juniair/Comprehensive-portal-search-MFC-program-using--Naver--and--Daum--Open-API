// WebBorwerDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "mfc_xml2.h"
#include "WebBorwerDlg.h"
#include "afxdialogex.h"


// CWebBorwerDlg ��ȭ �����Դϴ�.

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


// CWebBorwerDlg �޽��� ó�����Դϴ�.


void CWebBorwerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CRect rect(10, 10, cx-10, cy-10);
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_WEB);

	if(pEdit->GetSafeHwnd())
	{
		pEdit->MoveWindow(rect);
	}
}
