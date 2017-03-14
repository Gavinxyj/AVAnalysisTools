
// AVAnalysisToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AVAnalysisTools.h"
#include "AVAnalysisToolsDlg.h"
#include "afxdialogex.h"
#include "ParserFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAVAnalysisToolsDlg 对话框




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


// CAVAnalysisToolsDlg 消息处理程序

BOOL CAVAnalysisToolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CParserFormat::getInstance()->parserFlvFile("E:\\workSpace\\ffmpegStudy\\ffmpegStudy\\cuc_ieschool.flv");

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAVAnalysisToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAVAnalysisToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CAVAnalysisToolsDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	RECT rect = {0};
	GetClientRect(&rect);

	m_Lbutton.Create("格式解析", BS_GROUPBOX|WS_VISIBLE, CRect(2, 60, (rect.right - rect.left) / 2, rect.bottom - rect.top), this, 1024);
	m_RUpButton.Create("文件头信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 60, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), this, 1025);
	m_RDownButton.Create("详细信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), this, 1026);

	m_Lbutton.GetClientRect(&rect);
	m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
						CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
						&m_Lbutton, 
						1);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0,"序号",LVCFMT_LEFT, 40);
	m_ListCtrl.InsertColumn(1,"类型",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(2,"大小",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(3,"时间戳",LVCFMT_LEFT, 80);
	m_ListCtrl.InsertColumn(4,"Tag Data首字节",LVCFMT_LEFT, 220);
	

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

	// TODO: 在此处添加消息处理程序代码
}


void CAVAnalysisToolsDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ListCtrl.AddItem("123");
}
