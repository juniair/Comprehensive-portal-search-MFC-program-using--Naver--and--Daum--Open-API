
// mfc_xml2Dlg.h : ��� ����
//
#include "WebBorwerDlg.h"
#pragma once

// ����
#define TITLE "title"	// �Խù� ���� title�� ���� �Ǿ� �ִ�.
#define DESCRIPTION "description"	// �Խù��� ������ description���� ���� �Ǿ� �ִ�.
#define LINK "link"

// ���̹��� �������� �⺻������ �ۼ� �ؾߵǴ� ���ڿ�
#define NaverNecessity "http://openapi.naver.com/search?key=5adf2b1235b71879fdc2c5387e75bfd0&query=" + m_word	// �׻� Ű�� �������� �˻���´�.
#define DaumNecessity "http://apis.daum.net/search/" + categoryWithDaum +"?q=" + m_word // �׻� ī�װ� ������ �˻�� �´�.

// ���̹�
#define NaverTaget "&target=" + categoryWithNaver
#define NaverDisplay "&start=" + CurrentPage + "&display=100"
// ����
#define DaumDisplay "&result=20&pageno=" + CurrentPage + "&apikey=5b75a5d5cf481693198150d46860338c6a047616"	// �׻� ���������� Ű���� �´�.


// Cmfc_xml2Dlg ��ȭ ����
class Cmfc_xml2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	Cmfc_xml2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MFC_XML2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	// �˻� ��ư Ŭ���� �˻��� �Ǵ� �̺�Ʈ
	afx_msg void OnBnClickedBtnSerch();

	// �ش� ī�װ� ��ưŬ���� �˻� �Ǵ� �̺�Ʈ
	afx_msg void OnBnClickedRadio1();	// ������
	afx_msg void OnBnClickedRadio2();	// ��α�
	afx_msg void OnBnClickedRadio3();	// ī��
	afx_msg void OnBnClickedRadio4();	// �������
	afx_msg void OnBnClickedRadio5();	// ������
	
	
	
	CString m_word;	// �˻���
	void selectCategory();	// ī�װ� ���� ��ư
	int m_selCategory;
	CString categoryWithNaver;	// ���̹� ���� ī�װ���
	CString categoryWithDaum;	// ���� ���� ī�װ���	
	
	// ����Ʈ ��Ʈ�� ���� ����
	LV_COLUMN m_lCol;
	LV_ITEM m_lItem;
	// ����Ʈ ��Ʈ�� ���� ����

	CString URLt;	// �� ī�װ��� �ش� �Ǵ� URL �ӽ� ����
	CListCtrl m_cListNaver;
	void NaverSearch();	// ���̹��� �˻� ����� ����ϴ� ��� �Լ�
	
	CListCtrl m_cListDaum;
	void DaumSearch();	// ������ �˻� ����� ����ϴ� ��� �Լ�
	// void test(); // �ش� ī�װ��� ���� xml�м��� ���� �׽�Ʈ���α׷�

	

	// ������Ʈ �̵� ����Լ�
	afx_msg void OnNMClickLstNaver(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLstDaum(NMHDR *pNMHDR, LRESULT *pResult);
	void moveWeb(CWebBorwerDlg *newDlg, CString link, CString linkName);

		
	CListCtrl m_cLstMyWord;
	CString categoryWithMyWord;
	int indexWithMyWord;
	afx_msg void OnClickedBntMyWord();	// �� �˻��� �߰� �̺�Ʈ
	afx_msg void OnBnClickedbtndeletemyword();	// �� �˻��� ���� �̺�Ʈ
	afx_msg void OnBnClickedbtndeleteall();	// �� �˻��� ���� ���� �̺�Ʈ
	afx_msg void OnNMClicklstMyWord(NMHDR *pNMHDR, LRESULT *pResult);
	
	CString CurrentPage;	// ���� ������ ��ȣ
	int indexPageWithNaver;	// ������ �̵�(���̹�)
	int indexPageWithDaum;	// ������ �̵�(����)
	int totalPage;	// �ִ� ������
	afx_msg void OnBnClickedbtnnextpagenaver();	// ���� ������ ���� �̺�Ʈ(���̹�)
	afx_msg void OnBnClickedbtnprevpagenaver();	// ���� ������ ���� �̺�Ʈ(���̹�)
	afx_msg void OnBnClickedbtnprevpagedaum();	// ���� ������ ���� �̺�Ʈ(����)
	afx_msg void OnBnClickedbtnnextpagedaum();	// ���� ������ ���� �̺�Ʈ(����)
};
