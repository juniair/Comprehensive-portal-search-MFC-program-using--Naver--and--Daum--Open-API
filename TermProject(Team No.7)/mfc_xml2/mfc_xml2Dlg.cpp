
// mfc_xml2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "mfc_xml2.h"
#include "mfc_xml2Dlg.h"
#include "afxdialogex.h"
#include "WebBorwerDlg.h"	// �ڽ� ���̾�α� �������

//XmlTextReader�� ����ϱ� ���� ���� ����
#include <tchar.h>
//#using <mscorlib.dll>
#using <System.dll>
#using <System.Xml.dll>

using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Net;
//XmlTextReader�� ����ϱ� ���� ���� ��

// MySql ������ ���� �߰��� ���� ����
#include <winsock2.h> 
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")
#pragma comment(lib, "ws2_32.lib")

#define MYSQL_HOST  "localhost"	// mysql ȣ����
#define MYSQL_USER  "root"		// mysql ����ڸ�
#define MYSQL_PWD   "nhk9138"	// mysql ����� ��й�ȣ
#define MYSQL_DB "mysql"		// mysql �ش� DB
#define MYSQL_PORT 3306			// mysql ��Ʈ��ȣ
// MySql ������ ���� �߰��� ���� ��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern CWebBorwerDlg *newDlg = NULL;	// �ڽ� ���̾�α׸� ���� ������ ����

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// Cmfc_xml2Dlg ��ȭ ����




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


// Cmfc_xml2Dlg �޽��� ó����

BOOL Cmfc_xml2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	// ��Ʈ�� ����
	// ���̹� �ΰ�

	// ���Ͽ��� �̹����� ��Ʈ�� Ÿ������ �о�´�.
	// ����� current ��ο� �����ϹǷ� ��ü ��θ� ���� �ʾ�����.
	// �������ϰ� �ٸ� ��ο� �����Ѵٸ� ���� ��θ� �־���Ѵ�.
	// ���޵Ǵ� ���ڰ��� MSDN�� �ڼ��� ������ �����ִ�.
	HANDLE handle = ::LoadImage(AfxGetInstanceHandle(), "Naver.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	// ȭ���� ��ó ��Ʈ���� �ӽ÷� CStatic ��Ʈ�ѷ� �޾Ƶ��δ�.
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_NAVER);

	// �̹��� �ڵ�� ����ƽ ��Ʈ���� ����� ���� ������ �ִٸ�
	if(handle && pStatic)
		// ��Ʈ�ѿ� ��Ʈ���� �����Ų��.
		pStatic->SetBitmap((HBITMAP)handle);
	
	// ���� �ΰ�
	handle = ::LoadImage(AfxGetInstanceHandle(), "Daum.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	// ȭ���� ��ó ��Ʈ���� �ӽ÷� CStatic ��Ʈ�ѷ� �޾Ƶ��δ�.
	pStatic = (CStatic*)GetDlgItem(IDC_DAUM);

	// �̹��� �ڵ�� ����ƽ ��Ʈ���� ����� ���� ������ �ִٸ�
	if(handle && pStatic)
		// ��Ʈ�ѿ� ��Ʈ���� �����Ų��.
		pStatic->SetBitmap((HBITMAP)handle);


	// ����Ʈ ��Ʈ�� �ʱ�ȭ
	m_lCol.mask = LVCF_TEXT | LVCF_WIDTH;
	m_lItem.mask = LVIF_TEXT;
	
	m_lCol.pszText = "����";
	m_lCol.cx = 300;
	m_cListNaver.InsertColumn(0, &m_lCol);
	m_cListDaum.InsertColumn(0, &m_lCol);
	
	m_lCol.pszText = "����";
	m_lCol.cx = 500;
	m_cListNaver.InsertColumn(1, &m_lCol);
	m_cListDaum.InsertColumn(1, &m_lCol);

	m_lCol.pszText = "����Ʈ ��";
	m_lCol.cx = 200;
	m_cListNaver.InsertColumn(3, &m_lCol);
	m_cListDaum.InsertColumn(3, &m_lCol);

	m_lCol.pszText = "URL";
	m_lCol.cx = 800;
	m_cListNaver.InsertColumn(4, &m_lCol);
	m_cListDaum.InsertColumn(4, &m_lCol);

	m_lCol.pszText = "�� �˻���";
	m_lCol.cx = 100;
	m_cLstMyWord.InsertColumn(0, &m_lCol);
	m_lCol.pszText = "ī�װ�";
	m_cLstMyWord.InsertColumn(1, &m_lCol);
	
	// ��� �� ����
	m_cListNaver.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cListDaum.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_cLstMyWord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	// ����Ʈ ��Ʈ�� �ʱ�ȭ(��)


	// ���޷� �ϳ��� â�� ���� ���� �ۼ�(�������� �ϱ� ���ؼ��� moveWeb()�� �ۼ� �ϸ� ��)
	newDlg = new CWebBorwerDlg();
	newDlg->Create(IDD_WEB);

	// sql�� mfc�� �������� ���˻�� �߰�

	//mfc sql ����
	MYSQL mysql;
	 mysql_init(&mysql);
	 if (!mysql_real_connect(&mysql, MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	 {
	       AfxMessageBox(mysql_error(&mysql),MB_OK);
	 }
	else
	 {
	      mysql_query(&mysql,"set names euckr"); //�ѱ��ν�
	 }
	 // mysql �����ͺ��̽��� user���̺� ���� �߿� host, user ������ ����.
	CString sql;
	MYSQL_ROW recordSet;	// mysql �� ���� �ô´�.
	MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�
	 
	sql.Format("select keyword,category from termproject_db.key_word");
	// ���� ��û
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
		// 1�÷�
		data.mask=LVIF_TEXT;
		data.iItem=index;
		data.pszText=(LPTSTR)(LPCSTR)recordSet[0];
		data.iSubItem=0;

		m_cLstMyWord.InsertItem(&data);
		// 
		// 2�÷�
		data.pszText=(LPTSTR)(LPCSTR)recordSet[1];
		data.iSubItem=1;

		m_cLstMyWord.SetItem(&data);

		index++;
	}
	mysql_close(&mysql);


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void Cmfc_xml2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR Cmfc_xml2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// ī�װ� ����
void Cmfc_xml2Dlg::selectCategory()
{
	switch(m_selCategory)
	{
	case 0:
		categoryWithNaver = L"webkr";
		categoryWithDaum = L"web";
		categoryWithMyWord = L"������";
		break;
	case 1:
		categoryWithNaver = L"blog";
		categoryWithDaum = L"blog";
		categoryWithMyWord = L"��α�";
		break;
	case 2:
		categoryWithNaver = L"cafearticle";
		categoryWithDaum = L"cafe";
		categoryWithMyWord = L"ī��";
		break;
	case 3:
		categoryWithNaver = L"encyc";
		categoryWithDaum = L" ";
		categoryWithMyWord = L"�������";
		break;
	case 4:
		categoryWithNaver = L"kin";
		categoryWithDaum = L"knowledge";
		categoryWithMyWord = L"������";
		break;
	}
}
// ���̹� �˻�
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
	int extraValue = 0;	// ���ʿ��� ��
	int title = 0;
	int info = 0;
	int webSite = 0;
	int webPage = 0;
	//���̹�
	CString targetLink;	// �Խù� �ּ�
	CString linkName;	// �ش� �Խù� ��
	CurrentPage.Format("%d",indexPageWithNaver);	// ���ڿ� �������� �������� Ÿ���� ��ȯ �Ѵ�.
	if(categoryWithNaver.CompareNoCase("blog") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");		// �ش� ��α� �Խù��� ���� �ּ�
		linkName.Format("%s", "bloggername");	// ��α׸�
	}
	else if(categoryWithNaver.CompareNoCase("cafearticle") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// ī�� �Խù��� ���� �ּ�
		linkName.Format("%s", "cafename");	// ī�� ��
	}
	else if(categoryWithNaver.CompareNoCase("kin") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// ī�� �Խù��� ���� �ּ�
	}
	else if(categoryWithNaver.CompareNoCase("encyc") == 0)
	{
		URLt +=( NaverDisplay + NaverTaget);
		targetLink.Format("%s", "link");	// ī�� �Խù��� ���� �ּ�
	}
	else if(categoryWithNaver.CompareNoCase("webkr") == 0)
	{
		URLt += ( NaverTaget + NaverDisplay);
		targetLink.Format("%s", "link");	// ī�� �Խù��� ���� �ּ�
	}
	else
	{
		result.Format("%s", "�ش� ī�װ��� ���������ʽ��ϴ�.");
		m_lItem.pszText = result.GetBuffer(result.GetLength());
		m_lItem.iItem = 0;
		m_lItem.iSubItem = 0;
		m_cListNaver.InsertItem(&m_lItem);
		return;
	}
	

	String^ url = gcnew String(URLt);

	XmlReader^ reader = XmlReader::Create(url, settings );

	//xml�� ���� �д´�.
    while (reader->Read()) 
    {
		// ���� ��ǻ��(���̹�)
		// reader�� Type�� Elemen�϶� �� ���� ����Ű�� ���� Element�� ���õ� Text�̹Ƿ� reader�� 2�� �д´�.
		if(reader->NodeType == XmlNodeType::Element)
		{
			temp.Format("%s", reader->Name);	// � Elemnet�� �о����� Ȯ��

			// �� ��� ������ ������ Ȯ��
			if(temp.CompareNoCase("total") == 0)
			{
				reader->Read();
				temp.Format("%s", reader->Value);	// �� �˻� ����� ������ �д´�.
				totalPage = _ttoi(temp)/100;	// �츮�� �ѹ��� 100���� ����� ����ϱ� ������ �� �˻� ����� ������ 100���� ������ �� �������� �ȴ�.
				if((_ttoi(temp)%100) !=0) // �׷��� 100���� �������� �������� ������ �����Ƿ� �� ��� ���������� �� �߰� �Ѵ�.
					totalPage++;
			}

			// �ش� Element�� �츮�� �ʿ��� ī�װ��� ���� �� Element�� ��� ����< title : �Խù� ����, description : �ش� �Խù��� �Ϻ� ����>
			if(temp.CompareNoCase(linkName) == 0 || temp.CompareNoCase(LINK) == 0 || temp.CompareNoCase(TITLE) == 0 || temp.CompareNoCase(DESCRIPTION) == 0)
			{
				if(extraValue>=3)	// ó�� ������ Open API�� ���� ������ �ʿ� ���� ������ ó�� 3�� ������ ���� �����Ѵ�.
				{
					if(temp.CompareNoCase(TITLE) == 0)
					{
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
						// �ʿ���� ���� ����
						for(int extraStr = 0; extraStr<temp.GetLength(); extraStr++)
						{
							switch(temp.GetAt(extraStr))	// <b> Ȥ�� </b>�� �����ϴ� ���� ���ý��ۿ��� �ȵǹǷ� ���� ��Ű�� ����� �ٲ㼭 ����Ѵ�.
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
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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
							m_lItem.pszText = (LPTSTR)(LPCSTR)"���̹� ����iN - ���İ� ���� �Բ� Ŀ���� ��";
							m_lItem.iItem = webSite++;
							m_lItem.iSubItem = 2;
							m_cListNaver.SetItem(&m_lItem);
						}
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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
// ���� �˻�
void Cmfc_xml2Dlg::DaumSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	int extraValue = 0;	// ���ʿ��� ��
	int title = 0;
	int info = 0;
	int webSite = 0;
	int webPage = 0;
	//����
	CString linkName;
	CurrentPage.Format("%d",indexPageWithDaum);	// ���ڿ� �������� �������� Ÿ���� ��ȯ �Ѵ�.
	if(categoryWithDaum.CompareNoCase("blog") == 0)
	{
		URLt += DaumDisplay;
		linkName.Format("%s", "author");	// ��α׸�
	}
	else if(categoryWithDaum.CompareNoCase("cafe") == 0)
	{
		URLt += DaumDisplay;
		linkName.Format("%s", "cafeName");	// ī�� ��
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
		result.Format("%s", "�ش� ī�װ��� ���������ʽ��ϴ�.");
		m_lItem.pszText = result.GetBuffer(result.GetLength());
		m_lItem.iItem = 0;
		m_lItem.iSubItem = 0;
		m_cListDaum.InsertItem(&m_lItem);
		return;
	}
	

	String^ url = gcnew String(URLt);

	XmlReader^ reader = XmlReader::Create(url, settings );

    //xml�� ���� �д´�.
    while (reader->Read()) 
    {
		// ���� ��ǻ��(����)
		// reader�� Type�� Elemen�϶� �� ���� ����Ű�� ���� Element�� ���õ� Text�̹Ƿ� reader�� 2�� �д´�.
		if(reader->NodeType == XmlNodeType::Element)
		{
			temp.Format("%s", reader->Name);	// � Elemnet�� �о����� Ȯ��

			// �� ��� ������ ������ Ȯ��
			if(temp.CompareNoCase("pageCount") == 0)
			{
				reader->Read();
				temp.Format("%s", reader->Value);	// �� �˻� ����� ������ �д´�.
				totalPage = _ttoi(temp)/20;	// �츮�� �ѹ��� 20���� ����� ����ϱ� ������ �� �˻� ����� ������ 20���� ������ �� �������� �ȴ�.
				if((_ttoi(temp)%20) !=0) // �׷��� 20���� �������� �������� ������ �����Ƿ� �� ��쵵 �ϳ��� �������̱� ������ �� �������� �� �߰� �Ѵ�.
					totalPage++;
			}

			// �ش� Element�� �츮�� �ʿ��� ī�װ��� ���� �� Element�� ��� ���� title : �Խù� ����, description : �ش� �Խù��� �Ϻ� ����
			if(temp.CompareNoCase(linkName) == 0 || temp.CompareNoCase(LINK) == 0 || temp.CompareNoCase(TITLE) == 0 || temp.CompareNoCase(DESCRIPTION) == 0)
			{
				if(extraValue>=3)	// ó�� ������ Open API�� ���� ������ �ʿ� ���� ������ ó�� 3�� ������ ���� �����Ѵ�.
				{
					if(temp.CompareNoCase("title") == 0)	// �Խù� ����
					{
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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
					else if(temp.CompareNoCase(DESCRIPTION) == 0)	// ����
					{
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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
					else if(temp.CompareNoCase(linkName) == 0)	// �Խù� �ּ�
					{
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
						result=temp;
						m_lItem.pszText = result.GetBuffer(result.GetLength());
						m_lItem.iItem = webSite++;
						m_lItem.iSubItem = 2;
						m_cListDaum.SetItem(&m_lItem);
					}
					else if(temp.CompareNoCase(LINK) == 0)
					{
						reader->Read();	// xml�� �ѹ� �� �о Text�� �д´�.
						temp.Format("%s", reader->Value);	// Text�� ���� Text�� ��� �����ִ� Element������ �����Ѵ�.
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

} // ���� �˻�(��)

// ���� ��ư Ŭ���� �˻��ϰ� �ϴ� ��ɵ�
//������
void Cmfc_xml2Dlg::OnBnClickedRadio1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

// ��α�
void Cmfc_xml2Dlg::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

// ī��
void Cmfc_xml2Dlg::OnBnClickedRadio3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

// �������
void Cmfc_xml2Dlg::OnBnClickedRadio4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// ������
void Cmfc_xml2Dlg::OnBnClickedRadio5()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
// ���� ��ư Ŭ���� �˻��ϰ� �ϴ� ��ɵ�(��)

// �˻���ư�� ������ ��� ����
void Cmfc_xml2Dlg::OnBnClickedBtnSerch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = pNMItemActivate -> iItem;
	
	LVITEM temp_item;
	temp_item.mask = LVIF_STATE; // ���º����� ���� ������� �����մϴ�.
    // �������� �����߿��� �ڽ��� ������ �ִ� ���¸� ����մϴ�.
    // �� ���� �������� ������ .state �׸� ���� �����ص� ���õ˴ϴ�.
    temp_item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    // �ش� �׸� �����ϰ� ���� ���¸� ����մϴ�.
    temp_item.state = LVIS_SELECTED | LVIS_FOCUSED;
    // ������� ����Ʈ ��Ʈ�ѿ� ���¸� �����մϴ�.
    m_cListNaver.SetItemState(index, &temp_item);

	// ���õ� �����۰��� �������� (0,1 ... n ��° �ε���) �Ѱ� �����´�.
	CString link, linkName;
	linkName.Format("%s : ���̹�",m_cListDaum.GetItemText(index, 2));
	link.Format("%s", m_cListNaver.GetItemText(index, 3));
	moveWeb(newDlg, link, linkName);

	*pResult = 0;
}

void Cmfc_xml2Dlg::OnNMClickLstDaum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = pNMItemActivate -> iItem;

	LVITEM temp_item;
	temp_item.mask = LVIF_STATE; // ���º����� ���� ������� �����մϴ�.
    // �������� �����߿��� �ڽ��� ������ �ִ� ���¸� ����մϴ�.
    // �� ���� �������� ������ .state �׸� ���� �����ص� ���õ˴ϴ�.
    temp_item.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
    // �ش� �׸� �����ϰ� ���� ���¸� ����մϴ�.
    temp_item.state = LVIS_SELECTED | LVIS_FOCUSED;
    // ������� ����Ʈ ��Ʈ�ѿ� ���¸� �����մϴ�.
    m_cListDaum.SetItemState(index, &temp_item);

	// ���õ� �����۰��� �������� (0,1 ... n ��° �ε���) �Ѱ� �����´�.
	CString link, linkName;
	linkName.Format("%s : ����",m_cListDaum.GetItemText(index, 2));
	link.Format("%s", m_cListDaum.GetItemText(index, 3));
	moveWeb(newDlg, link, linkName);
	*pResult = 0;
}

void Cmfc_xml2Dlg::moveWeb(CWebBorwerDlg *newDlg, CString link, CString linkName)
{
	// �θ� ���̾�α׿� �Էµ� ���� �ڽ� ���̾�α� ��������� ����
	newDlg->m_webBrower.Navigate(link,NULL,NULL,NULL,NULL);

	// �ڽ� ���̾�α��� ��������� ������ ���� �ڽ� ���̾���� ��Ʈ�ѷ��� ����
	newDlg->ShowWindow(SW_SHOW);
	// �����ְ� �ڽ� ���̾�α��� ĸ�� ���� ���� �Ѵ�.(�ش� ����Ʈ�� ��� �˻� �Ǿ����� �˱� ���ؼ��̴�.)
	newDlg->UpdateWindow();
	newDlg->SetWindowText(linkName);
}

void Cmfc_xml2Dlg::OnClickedBntMyWord()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	      mysql_query(&mysql,"set names euckr"); //�ѱ��ν�
	 }
	 // mysql �����ͺ��̽��� user���̺� ���� �߿� host, user ������ ����.
	MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�

	selectCategory();
	CommandLine.Format("INSERT INTO word.key_word VALUES ('%s', '%s')", m_word, categoryWithMyWord);
	for(int i = 0; i <= indexWithMyWord; i++)
	{
		if( m_word.CompareNoCase("") == 0)
		{
			MessageBox("�˻�� �Է��Ͻʽÿ�.");
			m_cLstMyWord.SetCheck(-1,1);
			mysql_close(&mysql);
			UpdateData(false);
			return;
		}
		else if( m_word.CompareNoCase(m_cLstMyWord.GetItemText(i, 0)) == 0 && categoryWithMyWord.CompareNoCase(m_cLstMyWord.GetItemText(i, 1)) == 0)
		{
			MessageBox("�˻���� ī�װ��� ��ġ�ϴ� �׸��� �ֽ��ϴ�.");
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

	// ���� ��û
	UpdateData(false);
	m_cLstMyWord.SetCheck(-1,1);
	mysql_close(&mysql);
}

// �˻��� �߰�
void Cmfc_xml2Dlg::OnNMClicklstMyWord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	indexWithMyWord = pNMItemActivate -> iItem;
	UpdateData(true);
	m_word = m_cLstMyWord.GetItemText(indexWithMyWord, 0);
	categoryWithMyWord.Format("%s", m_cLstMyWord.GetItemText(indexWithMyWord, 1));
	if(categoryWithMyWord.CompareNoCase("������") == 0)
	{
		m_selCategory = 0;
	}
	else if(categoryWithMyWord.CompareNoCase("��α�") == 0)
	{
		m_selCategory = 1;
	}
	else if(categoryWithMyWord.CompareNoCase("ī��") == 0)
	{
		m_selCategory = 2;
	}
	else if(categoryWithMyWord.CompareNoCase("�������") == 0)
	{
		m_selCategory = 3;
	}
	else if(categoryWithMyWord.CompareNoCase("������") == 0)
	{
		m_selCategory = 4;
	}
	UpdateData(false);
	*pResult = 0;
}

// �ϳ��� �˻��� ����
void Cmfc_xml2Dlg::OnBnClickedbtndeletemyword()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL mysql;
	CString CommandLine;
	MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(mysql_error(&mysql),MB_OK);
	}
	else
	{
		mysql_query(&mysql,"set names euckr"); //�ѱ��ν�
	}

	CommandLine.Format("delete from word.key_word where keyword = '%s' AND category = '%s'", m_word, categoryWithMyWord);
	m_cLstMyWord.DeleteItem(indexWithMyWord);
	
	//CommandLine.Format(("DELETE FROM word.key_word WHERE keyword = '%s' AND category = '%s"), m_word, categoryWithMyWord);
	
	// ����� ���������� ���� ���� ���ҽ� �̺�Ʈ ����
	if(mysql_query(&mysql,CommandLine))
		return;
	if((m_res=mysql_store_result(&mysql))==NULL)
		return;
	UpdateData(false);
	// ���� ��û
	mysql_close(&mysql);
}

// ��� �� �˻��� ����
void Cmfc_xml2Dlg::OnBnClickedbtndeleteall()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	MYSQL mysql;
	CString CommandLine;	// MYSQL���� ����� ������ ����
	MYSQL_RES *m_res; // mysql�� ����� �޾ƿ´�
	mysql_init(&mysql);

	// ���� �ѱ� �ν��� ���� ���̺��� �����Ͱ� ������ ���� ����
	if (!mysql_real_connect(&mysql,MYSQL_HOST,MYSQL_USER,MYSQL_PWD,MYSQL_DB, MYSQL_PORT, 0, 0))
	{
		AfxMessageBox(mysql_error(&mysql),MB_OK);
	}
	else
	{
		mysql_query(&mysql,"set names euckr"); //�ѱ��ν�
	}

	CommandLine.Format("delete from word.key_word");
	m_cLstMyWord.DeleteAllItems();
	
	//CommandLine.Format(("DELETE FROM word.key_word WHERE keyword = '%s' AND category = '%s"), m_word, categoryWithMyWord);
	
	// ����� ���������� ���� ���� ���ҽ� �̺�Ʈ ����
	if(mysql_query(&mysql,CommandLine))
		return;
	if((m_res=mysql_store_result(&mysql))==NULL)
		return;
	
	mysql_close(&mysql);
}

// ���������� ����(���̹�)
void Cmfc_xml2Dlg::OnBnClickedbtnnextpagenaver()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	indexPageWithNaver++;
	if(indexPageWithNaver <= totalPage)	// ������ ��ȣ�� ���� ������ ��ȣ�� ���� �� �����Ƿ� indexPageWithNaver�� totalPage���� Ŭ ��� ����� �˻� ���� �ʴ´�.
	{	
		m_cListNaver.DeleteAllItems();	// ���� ����Ʈ ��Ʈ���� �������� ��� ���� �Ѵ�.
		URLt = NaverNecessity;
		NaverSearch();
	}
	UpdateData(false);

}

// ���� ������ ����(���̹�)
void Cmfc_xml2Dlg::OnBnClickedbtnprevpagenaver()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	indexPageWithNaver--;
	if(indexPageWithNaver > 0)	// ������ ��ȣ�� 0�� �� �� �����Ƿ� indexPageWithDaum�� 0�� �Ǹ� �ƹ��� ����� ���Ѵ�.
	{
		m_cListNaver.DeleteAllItems();
		URLt = NaverNecessity;
		NaverSearch();
	}
	UpdateData(false);
}


void Cmfc_xml2Dlg::OnBnClickedbtnprevpagedaum()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	indexPageWithDaum--;
	if(indexPageWithDaum > 0)	// ������ ��ȣ�� 0�� �� �� �����Ƿ� indexPageWithDaum�� 0�� �Ǹ� �ƹ��� ����� ���Ѵ�.
	{
		m_cListDaum.DeleteAllItems();
		URLt = DaumNecessity;
		DaumSearch();
	}
	UpdateData(false);
}


void Cmfc_xml2Dlg::OnBnClickedbtnnextpagedaum()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(true);
	indexPageWithDaum++;
	if(indexPageWithDaum <= totalPage)	// ������ ��ȣ�� ���� ������ ��ȣ�� ���� �� �����Ƿ� indexPageWithDaum�� totalPage���� Ŭ ��� ����� �˻� ���� �ʴ´�.
	{	
		m_cListDaum.DeleteAllItems();	// ���� ����Ʈ ��Ʈ���� �������� ��� ���� �Ѵ�.
		URLt = DaumNecessity;
		DaumSearch();
	}
	UpdateData(false);
}
