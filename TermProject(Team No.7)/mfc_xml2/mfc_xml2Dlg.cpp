
// mfc_xml2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "mfc_xml2.h"
#include "mfc_xml2Dlg.h"
#include "afxdialogex.h"
#include "WebBorwerDlg.h"	// 자식 다이얼로그 헤더파일

//XmlTextReader를 사용하기 위한 설정 시작
#include <tchar.h>
//#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>

using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Net;
//XmlTextReader를 사용하기 위한 설정 끝

// MySql 연동을 위해 추가한 내용 시작
#include <winsock2.h> 
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define MYSQL_HOST  "localhost"	// mysql 호스명
#define MYSQL_USER  "root"		// mysql 사용자명
#define MYSQL_PWD   "nhk9138"	// mysql 사용자 비밀번호
#define MYSQL_DB "mysql"		// mysql 해당 DB
#define MYSQL_PORT 3306			// mysql 포트번호
// MySql 연동을 위해 추가한 내용 끝

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern CWebBorwerDlg *newDlg = NULL;	// 자식 다이얼로그를 전역 변수로 선언

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_xml2Dlg 대화 상자




Cmfc_xml2Dlg::Cmfc_xml2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmfc_xml2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_word = _T("");
	//  m_selCategory = 0;
	//  m_selSort = 0;
	m_selCategory = 0;
}

void Cmfc_xml2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Searches, m_word);
	//  DDX_Control(pDX, IDC_lstNaver, m_clstNaver);
	//  DDX_Control(pDX, IDC_lstDaum, m_clstDaum);
	DDX_Control(pDX, IDC_lstDaum, m_cListDaum);
	DDX_Control(pDX, IDC_lstNaver, m_cListNaver);
	//  DDX_Radio(pDX, IDC_RADIO5, m_selCategory);
	//  DDX_Radio(pDX, IDC_RADIO6, m_selSort);
	//  DDX_Radio(pDX, IDC_RADIO6, m_selSort);
	DDX_Radio(pDX, IDC_RADIO1, m_selCategory);
	DDX_Control(pDX, IDC_lstMyWord, m_cLstMyWord);
}

BEGIN_MESSAGE_MAP(Cmfc_xml2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc_xml2Dlg::OnBnClickedButton1)
//	ON_BN_CLICKED(IDC_BUTTON2, &Cmfc_xml2Dlg::OnBnClickedButton2)
ON_BN_CLICKED(IDC_btnSerch, &Cmfc_xml2Dlg::OnBnClickedBtnSerch)
ON_NOTIFY(NM_CLICK, IDC_lstNaver, &Cmfc_xml2Dlg::OnNMClickLstNaver)
ON_NOTIFY(NM_CLICK, IDC_lstDaum, &Cmfc_xml2Dlg::OnNMClickLstDaum)
//ON_BN_CLICKED(IDC_bntMyWord, &Cmfc_xml2Dlg::OnBnClickedbntmyword)
ON_BN_CLICKED(IDC_bntMyWord, &Cmfc_xml2Dlg::OnClickedBntMyWord)
ON_NOTIFY(NM_CLICK, IDC_lstMyWord, &Cmfc_xml2Dlg::OnNMClicklstMyWord)
ON_BN_CLICKED(IDC_RADIO1, &Cmfc_xml2Dlg::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &Cmfc_xml2Dlg::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_RADIO3, &Cmfc_xml2Dlg::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO4, &Cmfc_xml2Dlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO5, &Cmfc_xml2Dlg::OnBnClickedRadio5)
ON_BN_CLICKED(IDC_btnDeleteMyWord, &Cmfc_xml2Dlg::OnBnClickedbtndeletemyword)
//ON_BN_SETFOCUS(IDC_RADIO1, &Cmfc_xml2Dlg::OnBnSetFocusRadio1)
ON_BN_CLICKED(IDC_btnDeleteALL, &Cmfc_xml2Dlg::OnBnClickedbtndeleteall)
ON_BN_CLICKED(IDC_btnNextPageNaver, &Cmfc_xml2Dlg::OnBnClickedbtnnextpagenaver)
ON_BN_CLICKED(IDC_btnPrevPageNaver, &Cmfc_xml2Dlg::OnBnClickedbtnprevpagenaver)
ON_BN_CLICKED(IDC_btnPrevPageDaum, &Cmfc_xml2Dlg::OnBnClickedbtnprevpagedaum)
ON_BN_CLICKED(IDC_btnNextPageDaum, &Cmfc_xml2Dlg::OnBnClickedbtnnextpagedaum)
END_MESSAGE_MAP()


// Cmfc_xml2Dlg 메시지 처리기

BOOL Cmfc_xml2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 비트맵 생성
	// 네이버 로고

	// 파일에서 이미지를 비트맵 타입으로 읽어온다.
	// 현재는 current 경로에 존재하므로 전체 경로를 넣지 않았지만.
	// 실행파일과 다른 경로에 존재한다면 절대 경로를 넣어야한다.
	// 전달되는 인자값은 MSDN에 자세히 설명이 나와있다.
	HANDLE handle = ::LoadImage(AfxGetInstanceHandle(), "Naver.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// 화면의 픽처 컨트롤을 임시로 CStatic 컨트롤로 받아들인다.
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_NAVER);

	// 이미지 핸들과 스태틱 컨트롤이 제대로 값을 가지고 있다면
	if(handle && pStatic)
		// 컨트롤에 비트맵을 연결시킨다.
		pStatic->SetBitmap((HBITMAP)handle);
	
	// 다음 로고
	handle = ::LoadImage(AfxGetInstanceHandle(), "Daum.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// 화면의 픽처 컨트롤을 임시로 CStatic 컨트롤로 받아들인다.
	pStatic = (CStatic*)GetDlgItem(IDC_DAUM);

	// 이미지 핸들과 스태틱 컨트롤이 제대로 값을 가지고 있다면
	if(handle && pStatic)
		// 컨트롤에 비트맵을 연결시킨다.
		pStatic->SetBitmap((HBITMAP)handle);


	// 리스트 컨트롤 초기화
	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;
	m_lItem.mask = LVIF_TEXT;
	
	m_lCol.pszText = "제목";
	m_lCol.cx = 300;
	m_cListNaver.InsertColumn(0, &m_lCol);
	m_cListDaum.InsertColumn(0, &m_lCol);
	
	m_lCol.pszText = "내용";
	m_lCol.cx = 500;
	m_cListNaver.InsertColumn(1, &m_lCol);
	m_cListDaum.InsertColumn(1, &m_lCol);

	m_lCol.pszText = "사이트 명";
	m_lCol.cx = 200;
	m_cListNaver.InsertColumn(3, &m_lCol);
	m_cListDaum.InsertColumn(3, &m_lCol);

	m_lCol.pszText = "URL";
	m_lCol.cx = 800;
	m_cListNaver.InsertColumn(4, &m_lCol);
	m_cListDaum.InsertColumn(4, &m_lCol);

	m_lCol.pszText = "내 검색어";
	m_lCol.cx = 100;
	m_cLstMyWord.InsertColumn(0, &m_lCol);
	m_lCol.pszText = "카테고리";
	m_cLstMyWord.InsertColumn(1, &m_lCol);
	
	// 행과 열 구분
	m_cListNaver.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cListDaum.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cLstMyWord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// 리스트 컨트롤 초기화(끝)


	// 비모달로 하나의 창만 열기 위해 작성(다중으로 하기 위해서는 moveWeb()에 작성 하면 됨)
	newDlg = new CWebBorwerDlg();
	newDlg->Create(IDD_WEB);

	// sql과 mfc를 연동시켜 내검색어를 추가

	//mfc sql 연결
	MYSQL mysql;
	 mysql_init(&mysql);
	 if (!mysql_real_connect(&mysql, MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	 {
	       AfxMessageBox(mysql_error(&mysql),MB_OK);
	 }
	else
	 {
	      mysql_query(&mysql,"set names euckr"); //한글인식
	 }
	 // mysql 데이터베이스의 user테이블 정보 중에 host, user 정보를 보자.
	CString sql;
	MYSQL_ROW recordSet;	// mysql 의 행을 맡는다.
	MYSQL_RES *m_res; // mysql의 결과를 받아온다
	 
	sql.Format("select keyword,category from termproject_db.key_word");
	// 쿼리 요청
	if(mysql_query(&mysql,sql)){
		return -1;
	}
	if((m_res=mysql_store_result(&mysql))==NULL){
		return -1;
	}
	int index = 0;

	m_cLstMyWord.DeleteAllItems();

	while((recordSet=mysql_fetch_row(m_res))!=NULL)
	{
		LVITEM data;
		// 1컬럼
		data.mask=LVIF_TEXT;
		data.iItem=index;
		data.pszText=(LPTSTR)(LPCSTR)recordSet[0];
		data.iSubItem=0;

		m_cLstMyWord.InsertItem(&data);
		// 
		// 2컬럼
		data.pszText=(LPTSTR)(LPCSTR)recordSet[1];
		data.iSubItem=1;

		m_cLstMyWord.SetItem(&data);

		index++;
	}
	mysql_close(&mysql);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Cmfc_xml2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cmfc_xml2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cmfc_xml2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 카테고리 선택
void Cmfc_xml2Dlg::selectCategory()
{
	switch(m_selCategory)
	{
	case 0:
		categoryWithNaver = L"webkr";
		categoryWithDaum = L"web";
		categoryWithMyWord = L"웹문서";
		break;
	case 1:
		categoryWithNaver = L"blog";
		categoryWithDaum = L"blog";
		categoryWithMyWord = L"블로그";
		break;
	case 2:
		categoryWithNaver = L"cafearticle";
		categoryWithDaum = L"cafe";
		categoryWithMyWord = L"카페";
		break;
	case 3:
		categoryWithNaver = L"encyc";
		categoryWithDaum = L" ";
		categoryWithMyWord = L"백과사전";
		break;
	case 4:
		categoryWithNaver = L"kin";
		categoryWithDaum = L"knowledge";
		categoryWithMyWord = L"지식인";
		break;
	}
}
// 네이버 검색
void Cmfc_xml2Dlg::NaverSearch()
{
	XmlReaderSettings^ settings = gcnew XmlReaderSettings;
	settings->IgnoreComments = true;
	settings->IgnoreProcessingInstructions = true;
	settings->IgnoreWhitespace = true;

	XmlUrlResolver^ resolver = gcnew XmlUrlResolver;
	resolver->Credentials = System::Net::CredentialCache::DefaultCredentials;
	// Set the reader settings object to use the resolver.
	settings->XmlResolver = resolver;
	// Create the XmlReader object.
	

	CString result=_T(""), temp;
	CString str;
	int extraValue = 0;	// 불필요한 값
	int title = 0;
	int info = 0;
	int webSite = 0;
	int webPage = 0;
	//네이버
	CString targetLink;	// 게시물 주소
	CString linkName;	// 해당 게시물 명
	CurrentPage.Format("%d",indexPageWithNaver);	// 문자열 형식으로 페이지의 타입을 전환 한다.
	if(categoryWithNaver.CompareNoCase("blog") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");		// 해당 블로그 게시물의 실제 주소
		linkName.Format("%s", "bloggername");	// 블로그명
	}
	else if(categoryWithNaver.CompareNoCase("cafearticle") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// 카페 게시물의 실제 주소
		linkName.Format("%s", "cafename");	// 카페 명
	}
	else if(categoryWithNaver.CompareNoCase("kin") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// 카페 게시물의 실제 주소
	}
	else if(categoryWithNaver.CompareNoCase("encyc") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// 카페 게시물의 실제 주소
	}
	else if(categoryWithNaver.CompareNoCase("webkr") == 0)
	{
		URLt += ( NaverTaget + NaverDisplay);
		targetLink.Format("%s", "link");	// 카페 게시물의 실제 주소
	}
	else
	{
		result.Format("%s", "해당 카테고리는 지원하지않습니다.");
		m_lItem.pszText = result.GetBuffer(result.GetLength());
		m_lItem.iItem = 0;
		m_lItem.iSubItem = 0;
		m_cListNaver.InsertItem(&m_lItem);
		return;
	}
	

	String^ url = gcnew String(URLt);

	XmlReader^ reader = XmlReader::Create(url, settings );

	//xml을 한줄 읽는다.
    while (reader->Read()) 
    {
		// 메인 컴퓨팅(네이버)
		// reader의 Type이 Elemen일때 그 다음 가르키는 것은 Element에 관련된 Text이므로 reader를 2번 읽는다.
		if(reader->NodeType == XmlNodeType::Element)
		{
			temp.Format("%s", reader->Name);	// 어떤 Elemnet를 읽었는지 확인

			// 총 사용 가능한 페이지 확인
			if(temp.CompareNoCase("total") == 0)
			{
				reader->Read();
				temp.Format("%s", reader->Value);	// 총 검색 결과의 개수를 읽는다.
				totalPage = _ttoi(temp)/100;	// 우리는 한번에 100개에 결과를 출력하기 때문에 총 검색 결과의 개수를 100으로 나누면 총 페이지가 된다.
				if((_ttoi(temp)%100) !=0) // 그런데 100으로 나눴을때 나머지가 있을수 있으므로 그 경우 한페이지를 더 추가 한다.
					totalPage++;
			}

			// 해당 Element가 우리가 필요한 카테고리와 관련 된 Element일 경우 수행< title : 게시물 제목, description : 해당 게시물의 일부 내용>
			if(temp.CompareNoCase(linkName) == 0 || temp.CompareNoCase(LINK) == 0 || temp.CompareNoCase(TITLE) == 0 || temp.CompareNoCase(DESCRIPTION) == 0)
			{
				if(extraValue>=3)	// 처음 읽을때 Open API에 대한 정보는 필요 없기 때문데 처음 3번 나오는 것은 무시한다.
				{
					if(temp.CompareNoCase(TITLE) == 0)
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						// 필요없는 문자 제거
						for(int extraStr = 0; extraStr<temp.GetLength(); extraStr++)
						{
							switch(temp.GetAt(extraStr))	// <b> 혹은 </b>로 강조하는 것은 현시스템에서 안되므로 제거 시키고 띄어쓰기로 바꿔서 출력한다.
							{
							case '<':
							case '/':
							case 'b':
								break;
							case '>':
								str += " ";
								break;
							default:
								str += temp.GetAt(extraStr);
								break;
							}
						}
						result = str;
						str.Empty();
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = title++;
						m_lItem.iSubItem = 0;
						m_cListNaver.InsertItem(&m_lItem);
					}
					else if(temp.CompareNoCase(DESCRIPTION) == 0)
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						for(int extraStr = 0; extraStr<temp.GetLength(); extraStr++)
						{			
							switch(temp.GetAt(extraStr))
							{
							case '<':
							case '/':
							case 'b':
								break;
							case '>':
								str += " ";
								break;
							default:
								str += temp.GetAt(extraStr);
								break;
							}
						}
						result = str;
						str.Empty();
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = info++;
						m_lItem.iSubItem = 1;
						m_cListNaver.SetItem(&m_lItem);
					}
					else if(temp.CompareNoCase(linkName) == 0)
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						result=temp;
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = webSite++;
						m_lItem.iSubItem = 2;
						m_cListNaver.SetItem(&m_lItem);
					}
					else if(temp.CompareNoCase(LINK) == 0)
					{
						if(categoryWithNaver.CompareNoCase("kin") == 0)
						{
							m_lItem.pszText = (LPTSTR)(LPCSTR)"네이버 지식iN - 지식과 내가 함께 커가는 곳";
							m_lItem.iItem = webSite++;
							m_lItem.iSubItem = 2;
							m_cListNaver.SetItem(&m_lItem);
						}
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						result=temp;
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = webPage++;
						m_lItem.iSubItem = 3;
						m_cListNaver.SetItem(&m_lItem);
					}
				}
				else
				{
					extraValue++;
				}
			}
		}
    }
}
// 다음 검색
void Cmfc_xml2Dlg::DaumSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	XmlReaderSettings^ settings = gcnew XmlReaderSettings;
	settings->IgnoreComments = true;
	settings->IgnoreProcessingInstructions = true;
	settings->IgnoreWhitespace = true;

	XmlUrlResolver^ resolver = gcnew XmlUrlResolver;
	resolver->Credentials = System::Net::CredentialCache::DefaultCredentials;
	// Set the reader settings object to use the resolver.
	settings->XmlResolver = resolver;
	// Create the XmlReader object.

	CString result=_T(""), temp;
	CString str;
	int extraValue = 0;	// 불필요한 값
	int title = 0;
	int info = 0;
	int webSite = 0;
	int webPage = 0;
	//다음
	CString linkName;
	CurrentPage.Format("%d",indexPageWithDaum);	// 문자열 형식으로 페이지의 타입을 전환 한다.
	if(categoryWithDaum.CompareNoCase("blog") == 0)
	{
		URLt += DaumDisplay;
		linkName.Format("%s", "author");	// 블로그명
	}
	else if(categoryWithDaum.CompareNoCase("cafe") == 0)
	{
		URLt += DaumDisplay;
		linkName.Format("%s", "cafeName");	// 카페 명
	}
	else if(categoryWithDaum.CompareNoCase("knowledge") == 0)
	{
		URLt += DaumDisplay;
	}
	else if(categoryWithDaum.CompareNoCase("web") == 0)
	{
		URLt += DaumDisplay;
	}
	else
	{
		result.Format("%s", "해당 카테고리는 지원하지않습니다.");
		m_lItem.pszText = result.GetBuffer(result.GetLength());
		m_lItem.iItem = 0;
		m_lItem.iSubItem = 0;
		m_cListDaum.InsertItem(&m_lItem);
		return;
	}
	

	String^ url = gcnew String(URLt);

	XmlReader^ reader = XmlReader::Create(url, settings );

    //xml을 한줄 읽는다.
    while (reader->Read()) 
    {
		// 메인 컴퓨팅(다음)
		// reader의 Type이 Elemen일때 그 다음 가르키는 것은 Element에 관련된 Text이므로 reader를 2번 읽는다.
		if(reader->NodeType == XmlNodeType::Element)
		{
			temp.Format("%s", reader->Name);	// 어떤 Elemnet를 읽었는지 확인

			// 총 사용 가능한 페이지 확인
			if(temp.CompareNoCase("pageCount") == 0)
			{
				reader->Read();
				temp.Format("%s", reader->Value);	// 총 검색 결과의 개수를 읽는다.
				totalPage = _ttoi(temp)/20;	// 우리는 한번에 20개에 결과를 출력하기 때문에 총 검색 결과의 개수를 20으로 나누면 총 페이지가 된다.
				if((_ttoi(temp)%20) !=0) // 그런데 20으로 나눴을때 나머지가 있을수 있으므로 그 경우도 하나의 페이지이기 때문에 한 페이지를 더 추가 한다.
					totalPage++;
			}

			// 해당 Element가 우리가 필요한 카테고리와 관련 된 Element일 경우 수행 title : 게시물 제목, description : 해당 게시물의 일부 내용
			if(temp.CompareNoCase(linkName) == 0 || temp.CompareNoCase(LINK) == 0 || temp.CompareNoCase(TITLE) == 0 || temp.CompareNoCase(DESCRIPTION) == 0)
			{
				if(extraValue>=3)	// 처음 읽을때 Open API에 대한 정보는 필요 없기 때문데 처음 3번 나오는 것은 무시한다.
				{
					if(temp.CompareNoCase("title") == 0)	// 게시물 제목
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						for(int extraStr = 0; extraStr<temp.GetLength(); extraStr++)
						{
							switch(temp.GetAt(extraStr))
							{
							case '<':
							case '/':
							case 'b':
								break;
							case '>':
								str += " ";
								break;
							default:
								str += temp.GetAt(extraStr);
								break;
							}
						}
						result = str;
						str.Empty();
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = title++;
						m_lItem.iSubItem = 0;
						m_cListDaum.InsertItem(&m_lItem);
					}
					else if(temp.CompareNoCase(DESCRIPTION) == 0)	// 내용
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						for(int extraStr = 0; extraStr<temp.GetLength(); extraStr++)
						{
							switch(temp.GetAt(extraStr))
							{
							case '<':
							case '/':
							case 'b':
								break;
							case '>':
								str += " ";
								break;
							default:
								str += temp.GetAt(extraStr);
								break;
							}
						}
						result = str;
						str.Empty();
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = info++;
						m_lItem.iSubItem = 1;
						m_cListDaum.SetItem(&m_lItem);
					}
					else if(temp.CompareNoCase(linkName) == 0)	// 게시물 주소
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						result=temp;
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = webSite++;
						m_lItem.iSubItem = 2;
						m_cListDaum.SetItem(&m_lItem);
					}
					else if(temp.CompareNoCase(LINK) == 0)
					{
						reader->Read();	// xml을 한번 더 읽어서 Text를 읽는다.
						temp.Format("%s", reader->Value);	// Text의 값과 Text가 어디에 관련있는 Element인지를 저장한다.
						result=temp;
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = webPage++;
						m_lItem.iSubItem = 3;
						m_cListDaum.SetItem(&m_lItem);
					}
				}
				else
				{
					extraValue++;
				}
			}
		}
    }
   //*/

} // 다음 검색(끝)

// 라디오 버튼 클릭시 검색하게 하는 기능들
//웹문서
void Cmfc_xml2Dlg::OnBnClickedRadio1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}

// 블로그
void Cmfc_xml2Dlg::OnBnClickedRadio2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}

// 카페
void Cmfc_xml2Dlg::OnBnClickedRadio3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}

// 백과사전
void Cmfc_xml2Dlg::OnBnClickedRadio4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}
// 지식인
void Cmfc_xml2Dlg::OnBnClickedRadio5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}
// 라디오 버튼 클릭시 검색하게 하는 기능들(끝)

// 검색버튼을 눌렀을 경우 시작
void Cmfc_xml2Dlg::OnBnClickedBtnSerch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver = 1;
	indexPageWithDaum = 1;
	selectCategory();
	m_cListNaver.DeleteAllItems();
	m_cListDaum.DeleteAllItems();
	URLt = NaverNecessity;
	NaverSearch();
	URLt = DaumNecessity;
	DaumSearch();
	//test();
	UpdateData(false);
}

void Cmfc_xml2Dlg::OnNMClickLstNaver(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = pNMItemActivate -> iItem;
	
	LVITEM temp_item;
	temp_item.mask = LVIF_STATE; // 상태변경을 위해 사용함을 지정합니다.
    // 여러가지 상태중에서 자신이 관심이 있는 상태를 명시합니다.
    // 이 값을 설정하지 않으면 .state 항목에 값을 설정해도 무시됩니다.
    temp_item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    // 해당 항목에 설정하고 싶은 상태를 명시합니다.
    temp_item.state = LVIS_SELECTED | LVIS_FOCUSED;
    // 사용자의 리스트 컨트롤에 상태를 설정합니다.
    m_cListNaver.SetItemState(index, &temp_item);

	// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	CString link, linkName;
	linkName.Format("%s : 네이버",m_cListDaum.GetItemText(index, 2));
	link.Format("%s", m_cListNaver.GetItemText(index, 3));
	moveWeb(newDlg, link, linkName);

	*pResult = 0;
}

void Cmfc_xml2Dlg::OnNMClickLstDaum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = pNMItemActivate -> iItem;

	LVITEM temp_item;
	temp_item.mask = LVIF_STATE; // 상태변경을 위해 사용함을 지정합니다.
    // 여러가지 상태중에서 자신이 관심이 있는 상태를 명시합니다.
    // 이 값을 설정하지 않으면 .state 항목에 값을 설정해도 무시됩니다.
    temp_item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    // 해당 항목에 설정하고 싶은 상태를 명시합니다.
    temp_item.state = LVIS_SELECTED | LVIS_FOCUSED;
    // 사용자의 리스트 컨트롤에 상태를 설정합니다.
    m_cListDaum.SetItemState(index, &temp_item);

	// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	CString link, linkName;
	linkName.Format("%s : 다음",m_cListDaum.GetItemText(index, 2));
	link.Format("%s", m_cListDaum.GetItemText(index, 3));
	moveWeb(newDlg, link, linkName);
	*pResult = 0;
}

void Cmfc_xml2Dlg::moveWeb(CWebBorwerDlg *newDlg, CString link, CString linkName)
{
	// 부모 다이얼로그에 입력된 값을 자식 다이얼로그 멤버변수로 전달
	newDlg->m_webBrower.Navigate(link,NULL,NULL,NULL,NULL);

	// 자식 다이얼로그의 멤버변수로 전달한 값을 자식 다이얼로의 컨트롤러로 전달
	newDlg->ShowWindow(SW_SHOW);
	// 보여주고 자식 다이얼로그의 캡션 값을 수정 한다.(해당 사이트가 어디서 검색 되었는지 알기 위해서이다.)
	newDlg->UpdateWindow();
	newDlg->SetWindowText(linkName);
}

void Cmfc_xml2Dlg::OnClickedBntMyWord()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);

	indexWithMyWord = m_cLstMyWord.GetItemCount();

	MYSQL mysql;
	CString CommandLine;
	mysql_init(&mysql);
	 if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	 {
	       AfxMessageBox(mysql_error(&mysql),MB_OK);
	 }
	else
	 {
	      mysql_query(&mysql,"set names euckr"); //한글인식
	 }
	 // mysql 데이터베이스의 user테이블 정보 중에 host, user 정보를 보자.
	MYSQL_RES *m_res; // mysql의 결과를 받아온다

	selectCategory();
	CommandLine.Format("INSERT INTO word.key_word VALUES ('%s', '%s')", m_word, categoryWithMyWord);
	for(int i = 0; i <= indexWithMyWord; i++)
	{
		if( m_word.CompareNoCase("") == 0)
		{
			MessageBox("검색어를 입력하십시오.");
			m_cLstMyWord.SetCheck(-1,1);
			mysql_close(&mysql);
			UpdateData(false);
			return;
		}
		else if( m_word.CompareNoCase(m_cLstMyWord.GetItemText(i, 0)) == 0 && categoryWithMyWord.CompareNoCase(m_cLstMyWord.GetItemText(i, 1)) == 0)
		{
			MessageBox("검색어와 카테고리가 일치하는 항목이 있습니다.");
			m_cLstMyWord.SetCheck(-1,1);
			mysql_close(&mysql);
			UpdateData(false);
			return;
		}
	}
	m_lItem.pszText = m_word.GetBuffer(m_word.GetLength());
	m_lItem.iItem = indexWithMyWord;
	m_lItem.iSubItem = 0;
	m_cLstMyWord.InsertItem(&m_lItem);
	selectCategory();
	m_lItem.pszText = categoryWithMyWord.GetBuffer(categoryWithMyWord.GetLength());
	m_lItem.iItem = indexWithMyWord;
	m_lItem.iSubItem = 1;
	m_cLstMyWord.SetItem(&m_lItem);

	if(mysql_query(&mysql,CommandLine))
		return;

	if((m_res=mysql_store_result(&mysql))==NULL)
		return;

	// 쿼리 요청
	UpdateData(false);
	m_cLstMyWord.SetCheck(-1,1);
	mysql_close(&mysql);
}

// 검색어 추가
void Cmfc_xml2Dlg::OnNMClicklstMyWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	indexWithMyWord = pNMItemActivate -> iItem;
	UpdateData(true);
	m_word = m_cLstMyWord.GetItemText(indexWithMyWord, 0);
	categoryWithMyWord.Format("%s", m_cLstMyWord.GetItemText(indexWithMyWord, 1));
	if(categoryWithMyWord.CompareNoCase("웹문서") == 0)
	{
		m_selCategory = 0;
	}
	else if(categoryWithMyWord.CompareNoCase("블로그") == 0)
	{
		m_selCategory = 1;
	}
	else if(categoryWithMyWord.CompareNoCase("카페") == 0)
	{
		m_selCategory = 2;
	}
	else if(categoryWithMyWord.CompareNoCase("백과사전") == 0)
	{
		m_selCategory = 3;
	}
	else if(categoryWithMyWord.CompareNoCase("지식인") == 0)
	{
		m_selCategory = 4;
	}
	UpdateData(false);
	*pResult = 0;
}

// 하나의 검색어 삭제
void Cmfc_xml2Dlg::OnBnClickedbtndeletemyword()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MYSQL mysql;
	CString CommandLine;
	MYSQL_RES *m_res; // mysql의 결과를 받아온다
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(mysql_error(&mysql),MB_OK);
	}
	else
	{
		mysql_query(&mysql,"set names euckr"); //한글인식
	}

	CommandLine.Format("delete from word.key_word where keyword = '%s' AND category = '%s'", m_word, categoryWithMyWord);
	m_cLstMyWord.DeleteItem(indexWithMyWord);
	
	//CommandLine.Format(("DELETE FROM word.key_word WHERE keyword = '%s' AND category = '%s"), m_word, categoryWithMyWord);
	
	// 명령이 성공적으로 전달 되지 못할시 이벤트 종료
	if(mysql_query(&mysql,CommandLine))
		return;
	if((m_res=mysql_store_result(&mysql))==NULL)
		return;
	UpdateData(false);
	// 쿼리 요청
	mysql_close(&mysql);
}

// 모든 내 검색어 삭제
void Cmfc_xml2Dlg::OnBnClickedbtndeleteall()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MYSQL mysql;
	CString CommandLine;	// MYSQL에게 명령을 내리는 변수
	MYSQL_RES *m_res; // mysql의 결과를 받아온다
	mysql_init(&mysql);

	// 가끔 한글 인식을 못해 테이블의 데이터가 깨지는 것을 방지
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(mysql_error(&mysql),MB_OK);
	}
	else
	{
		mysql_query(&mysql,"set names euckr"); //한글인식
	}

	CommandLine.Format("delete from word.key_word");
	m_cLstMyWord.DeleteAllItems();
	
	//CommandLine.Format(("DELETE FROM word.key_word WHERE keyword = '%s' AND category = '%s"), m_word, categoryWithMyWord);
	
	// 명령이 성공적으로 전달 되지 못할시 이벤트 종료
	if(mysql_query(&mysql,CommandLine))
		return;
	if((m_res=mysql_store_result(&mysql))==NULL)
		return;
	
	mysql_close(&mysql);
}

// 다음페이지 보기(네이버)
void Cmfc_xml2Dlg::OnBnClickedbtnnextpagenaver()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver++;
	if(indexPageWithNaver <= totalPage)	// 페이지 번호는 최종 페이지 번호를 넘을 수 없으므로 indexPageWithNaver가 totalPage보다 클 경우 기능을 검색 하지 않는다.
	{	
		m_cListNaver.DeleteAllItems();	// 현재 리스트 컨트롤의 아이템을 모두 제거 한다.
		URLt = NaverNecessity;
		NaverSearch();
	}
	UpdateData(false);

}

// 이전 페이지 보기(네이버)
void Cmfc_xml2Dlg::OnBnClickedbtnprevpagenaver()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithNaver--;
	if(indexPageWithNaver > 0)	// 페이지 번호가 0이 될 수 없으므로 indexPageWithDaum가 0이 되면 아무런 기능을 안한다.
	{
		m_cListNaver.DeleteAllItems();
		URLt = NaverNecessity;
		NaverSearch();
	}
	UpdateData(false);
}


void Cmfc_xml2Dlg::OnBnClickedbtnprevpagedaum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithDaum--;
	if(indexPageWithDaum > 0)	// 페이지 번호가 0이 될 수 없으므로 indexPageWithDaum가 0이 되면 아무런 기능을 안한다.
	{
		m_cListDaum.DeleteAllItems();
		URLt = DaumNecessity;
		DaumSearch();
	}
	UpdateData(false);
}


void Cmfc_xml2Dlg::OnBnClickedbtnnextpagedaum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	indexPageWithDaum++;
	if(indexPageWithDaum <= totalPage)	// 페이지 번호는 최종 페이지 번호를 넘을 수 없으므로 indexPageWithDaum가 totalPage보다 클 경우 기능을 검색 하지 않는다.
	{	
		m_cListDaum.DeleteAllItems();	// 현재 리스트 컨트롤의 아이템을 모두 제거 한다.
		URLt = DaumNecessity;
		DaumSearch();
	}
	UpdateData(false);
}
