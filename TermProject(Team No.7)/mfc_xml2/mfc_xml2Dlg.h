
// mfc_xml2Dlg.h : 헤더 파일
//
#include "WebBorwerDlg.h"
#pragma once

// 공통
#define TITLE "title"	// 게시물 명은 title로 정의 되어 있다.
#define DESCRIPTION "description"	// 게시물의 내용은 description으로 정의 되어 있다.
#define LINK "link"

// 네이버와 다음에서 기본적으로 작성 해야되는 문자열
#define NaverNecessity "http://openapi.naver.com/search?key=5adf2b1235b71879fdc2c5387e75bfd0&query=" + m_word	// 항상 키값 다음에는 검색어가온다.
#define DaumNecessity "http://apis.daum.net/search/" + categoryWithDaum +"?q=" + m_word // 항상 카테고리 선택후 검색어가 온다.

// 네이버
#define NaverTaget "&target=" + categoryWithNaver
#define NaverDisplay "&start=" + CurrentPage + "&display=100"
// 다음
#define DaumDisplay "&result=20&pageno=" + CurrentPage + "&apikey=5b75a5d5cf481693198150d46860338c6a047616"	// 항상 마지막에는 키값이 온다.


// Cmfc_xml2Dlg 대화 상자
class Cmfc_xml2Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cmfc_xml2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MFC_XML2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	// 검색 버튼 클릭시 검색이 되는 이벤트
	afx_msg void OnBnClickedBtnSerch();

	// 해당 카테고리 버튼클릭시 검색 되는 이벤트
	afx_msg void OnBnClickedRadio1();	// 웹문서
	afx_msg void OnBnClickedRadio2();	// 블로그
	afx_msg void OnBnClickedRadio3();	// 카페
	afx_msg void OnBnClickedRadio4();	// 백과사전
	afx_msg void OnBnClickedRadio5();	// 지식인
	
	
	
	CString m_word;	// 검색어
	void selectCategory();	// 카테고리 라디오 버튼
	int m_selCategory;
	CString categoryWithNaver;	// 네이버 전용 카테고리명
	CString categoryWithDaum;	// 다음 전용 카테고리명	
	
	// 리스트 컨트롤 관련 변수
	LV_COLUMN m_lCol;
	LV_ITEM m_lItem;
	// 리스트 컨트롤 관련 변수

	CString URLt;	// 각 카테고리에 해당 되는 URL 임시 보관
	CListCtrl m_cListNaver;
	void NaverSearch();	// 네이버의 검색 결과를 출력하는 멤버 함수
	
	CListCtrl m_cListDaum;
	void DaumSearch();	// 다음의 검색 결과를 출력하는 멤버 함수
	// void test(); // 해당 카테고리에 대한 xml분석을 위한 테스트프로그램

	

	// 웹사이트 이동 멤버함수
	afx_msg void OnNMClickLstNaver(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickLstDaum(NMHDR *pNMHDR, LRESULT *pResult);
	void moveWeb(CWebBorwerDlg *newDlg, CString link, CString linkName);

		
	CListCtrl m_cLstMyWord;
	CString categoryWithMyWord;
	int indexWithMyWord;
	afx_msg void OnClickedBntMyWord();	// 내 검색어 추가 이벤트
	afx_msg void OnBnClickedbtndeletemyword();	// 내 검색어 삭제 이벤트
	afx_msg void OnBnClickedbtndeleteall();	// 내 검색어 전제 삭제 이벤트
	afx_msg void OnNMClicklstMyWord(NMHDR *pNMHDR, LRESULT *pResult);
	
	CString CurrentPage;	// 현재 페이지 번호
	int indexPageWithNaver;	// 페이지 이동(네이버)
	int indexPageWithDaum;	// 페이지 이동(다음)
	int totalPage;	// 최대 페이지
	afx_msg void OnBnClickedbtnnextpagenaver();	// 다음 페이지 보는 이벤트(네이버)
	afx_msg void OnBnClickedbtnprevpagenaver();	// 이전 페이지 보는 이벤트(네이버)
	afx_msg void OnBnClickedbtnprevpagedaum();	// 다음 페이지 보는 이벤트(다음)
	afx_msg void OnBnClickedbtnnextpagedaum();	// 이전 페이지 보는 이벤트(다음)
};
