#pragma once
#include "web.h"


// CWebBorwerDlg ��ȭ �����Դϴ�.

class CWebBorwerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebBorwerDlg)

public:
	CWebBorwerDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CWebBorwerDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnSize(UINT nType, int cx, int cy);
	CWeb m_webBrower;
};
