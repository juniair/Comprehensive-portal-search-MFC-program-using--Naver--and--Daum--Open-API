
// mfc_xml2.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cmfc_xml2App:
// �� Ŭ������ ������ ���ؼ��� mfc_xml2.cpp�� �����Ͻʽÿ�.
//

class Cmfc_xml2App : public CWinApp
{
public:
	Cmfc_xml2App();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_xml2App theApp;