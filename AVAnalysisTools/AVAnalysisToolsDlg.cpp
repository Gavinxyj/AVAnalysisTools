
// AVAnalysisToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AVAnalysisTools.h"
#include "AVAnalysisToolsDlg.h"
#include "afxdialogex.h"
#include "ParserFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CAVAnalysisToolsDlg �Ի���




CAVAnalysisToolsDlg::CAVAnalysisToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAVAnalysisToolsDlg::IDD, pParent),m_ListCtrl(this),m_FileHeaderCtrl(this),m_DetailCtrl(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAVAnalysisToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAVAnalysisToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CAVAnalysisToolsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAVAnalysisToolsDlg ��Ϣ�������

BOOL CAVAnalysisToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CParserFormat::getInstance()->parserFlvFile("E:\\workSpace\\ffmpegStudy\\ffmpegStudy\\cuc_ieschool.flv");

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAVAnalysisToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAVAnalysisToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAVAnalysisToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CAVAnalysisToolsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	RECT rect = {0};
	GetClientRect(&rect);

	m_Lbutton.Create("��ʽ����", BS_GROUPBOX|WS_VISIBLE, CRect(2, 60, (rect.right - rect.left) / 2, rect.bottom - rect.top), this, 1024);
	m_RUpButton.Create("�ļ�ͷ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 60, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), this, 1025);
	m_RDownButton.Create("��ϸ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), this, 1026);

	m_Lbutton.GetClientRect(&rect);
	m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
						CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
						&m_Lbutton, 
						1);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0,"���",LVCFMT_LEFT, 40);
	m_ListCtrl.InsertColumn(1,"����",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(2,"��С",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(3,"ʱ���",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(4,"Tag Data���ֽ�",LVCFMT_LEFT, 220);
	

/*	m_RUpButton.GetClientRect(&rect);
	m_FileHeaderCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS, 
								CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
								&m_RUpButton, 
								2);
	m_FileHeaderCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_FileHeaderCtrl.InsertColumn(0,"name",LVCFMT_LEFT, (rect.right - rect.left) / 2);
	m_FileHeaderCtrl.InsertColumn(1,"value",LVCFMT_LEFT, (rect.right - rect.left) / 2);

	m_RDownButton.GetClientRect(&rect);
	m_DetailCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS, 
		CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
		&m_RDownButton, 
		2);
	m_DetailCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);*/
	//m_DetailCtrl.InsertColumn(0,"name",LVCFMT_LEFT, (rect.right - rect.left) / 2);
	//m_DetailCtrl.InsertColumn(1,"value",LVCFMT_LEFT, (rect.right - rect.left) / 2);
	return 0;
}

void CAVAnalysisToolsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}


void CAVAnalysisToolsDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ListCtrl.AddItem("123");
}
