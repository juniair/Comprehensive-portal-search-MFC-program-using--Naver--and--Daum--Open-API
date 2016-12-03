#pragma once
#include "web.h"


// CWebBorwerDlg 대화 상자입니다.

class CWebBorwerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWebBorwerDlg)

public:
	CWebBorwerDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CWebBorwerDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_WEB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnSize(UINT nType, int cx, int cy);
	CWeb m_webBrower;
};
