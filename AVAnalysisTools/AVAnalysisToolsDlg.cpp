
// AVAnalysisToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AVAnalysisTools.h"
#include "AVAnalysisToolsDlg.h"
#include "afxdialogex.h"
#include "ParserFormat.h"
#include "./H264/NALParse.h"
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
	: CDialogEx(CAVAnalysisToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CAVAnalysisToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FLV, m_FlvButton);
}

BEGIN_MESSAGE_MAP(CAVAnalysisToolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_FLV, &CAVAnalysisToolsDlg::OnBnClickedFlv)
	ON_BN_CLICKED(IDC_BUTTON_H264, &CAVAnalysisToolsDlg::OnBnClickedButtonH264)
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
	
	CRect dlgRect = NULL;
	GetClientRect(&dlgRect);
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pPanelDlg[nLoop] = new CPanelList();
		m_pPanelDlg[nLoop]->Create(IDD_DIALOG_PANEL, this);
		m_pPanelDlg[nLoop]->ShowWindow(SW_SHOW);
		m_pPanelDlg[nLoop]->MoveWindow(0, 60, dlgRect.Width(), dlgRect.Height() - 60);
	}
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
	
	
	
	return 0;
}

void CAVAnalysisToolsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
}


void CAVAnalysisToolsDlg::OnBnClickedFlv()
{
	// TODO: 在此添加控件通知处理程序代码
	
	TCHAR szFilter[] = _T("Flash文件(*.flv)|*.flv");
	CFileDialog fileDlg(TRUE, _T("FLV"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{   
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();   
		
	}   
	if (strFilePath.IsEmpty()) return;

	InitFlvListCtrl(m_pPanelDlg[FLV]->m_bFlag);
	CParserFormat::getInstance()->parserFlvFile(strFilePath);

	m_pPanelDlg[FLV]->m_FileHeaderCtrl.DeleteAllItems();
	char chTemp[10] = {0};
	strncpy(chTemp, (const char*)CParserFormat::getInstance()->m_flvHeader.signature, 3);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertItem(0, "");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(0, 0, "Signature");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(0, 1, chTemp);

	int nVersion = 0;
	memset(chTemp, 0, 10);
	CString strForamt;
	strForamt.Format("%02x",CParserFormat::getInstance()->m_flvHeader.version[0]);
	sscanf_s(strForamt.GetBuffer(), "%x", &nVersion);
	itoa(nVersion, chTemp, 10);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertItem(1, "");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(1, 0, "Version");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(1, 1, chTemp);

	int nFlag = 0;
	memset(chTemp, 0, 10);
	strForamt.Format("%02x",CParserFormat::getInstance()->m_flvHeader.flags[0]);
	sscanf_s(strForamt.GetBuffer(), "%x", &nFlag);
	itoa(nFlag, chTemp, 10);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertItem(2, "");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(2, 0, "Flags");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(2, 1, chTemp);

	int nHeadSize = 0;
	memset(chTemp, 0, 10);
	strForamt.Format("%02x%02x%02x%02x",CParserFormat::getInstance()->m_flvHeader.headSize[0],
										CParserFormat::getInstance()->m_flvHeader.headSize[1],
										CParserFormat::getInstance()->m_flvHeader.headSize[2],
										CParserFormat::getInstance()->m_flvHeader.headSize[3]);
	sscanf_s(strForamt.GetBuffer(), "%x", &nHeadSize);
	itoa(nHeadSize, chTemp, 10);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertItem(3, "");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(3, 0, "HeaderSize");
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetItemText(3, 1, chTemp);

	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetTextBkColor(RGB(205, 181, 205));
	std::vector<PTAG>::iterator iter = CParserFormat::getInstance()->m_vecTag.begin();
	
	m_pPanelDlg[FLV]->m_ListCtrl.DeleteAllItems();
	int nIndex = 0;
	for (;iter != CParserFormat::getInstance()->m_vecTag.end(); iter ++)
	{
		nIndex ++;
		m_pPanelDlg[FLV]->m_ListCtrl.AddItem(*iter, nIndex);
	}
	
	for (;iter != CParserFormat::getInstance()->m_vecTag.end(); iter ++)
	{
		delete *iter;
		*iter = NULL;
	}
	CParserFormat::getInstance()->m_vecTag.clear();
}

void CAVAnalysisToolsDlg::InitFlvListCtrl(bool bFlag)
{
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pPanelDlg[nLoop]->ShowWindow(SW_HIDE);	
	}
	m_pPanelDlg[FLV]->ShowWindow(SW_SHOW);

	if (m_pPanelDlg[FLV]->m_bFlag) return;
	
	RECT rect = {0};
	m_pPanelDlg[FLV]->GetClientRect(&rect);
	m_pPanelDlg[FLV]->m_Lbutton.Create("格式解析", BS_GROUPBOX|WS_VISIBLE, CRect(0, 0, (rect.right - rect.left) / 2, rect.bottom - rect.top), m_pPanelDlg[FLV], 1024);
	m_pPanelDlg[FLV]->m_RUpButton.Create("文件头信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 0, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), m_pPanelDlg[FLV], 1025);
	m_pPanelDlg[FLV]->m_RDownButton.Create("详细信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), m_pPanelDlg[FLV], 1026);

	m_pPanelDlg[FLV]->m_Lbutton.GetClientRect(&rect);
	m_pPanelDlg[FLV]->m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
										CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
										&m_pPanelDlg[FLV]->m_Lbutton, 
										1);

	m_pPanelDlg[FLV]->m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(0,"序号",LVCFMT_LEFT, 40);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(1,"类型",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(2,"大小",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(3,"时间戳",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(4,"Tag Data首字节",LVCFMT_LEFT, 220);


	m_pPanelDlg[FLV]->m_RUpButton.GetClientRect(&rect);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
							CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
							&m_pPanelDlg[FLV]->m_RUpButton, 
							2);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertColumn(0,"Name",LVCFMT_LEFT, (rect.right - rect.left) / 2);
	m_pPanelDlg[FLV]->m_FileHeaderCtrl.InsertColumn(1,"Value",LVCFMT_LEFT, (rect.right - rect.left) / 2);

	m_pPanelDlg[FLV]->m_RDownButton.GetClientRect(&rect);
	m_pPanelDlg[FLV]->m_DetailCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_AUTOARRANGE, 
							CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
							&m_pPanelDlg[FLV]->m_RDownButton, 
							2);
	m_pPanelDlg[FLV]->m_DetailCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(0,"0",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(1,"1",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(2,"2",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(3,"3",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(4,"4",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(5,"5",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(6,"6",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(7,"7",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(8,"8",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(9,"9",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(10,"A",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(11,"B",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(12,"C",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(13,"D",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(14,"E",LVCFMT_LEFT, 30);
	m_pPanelDlg[FLV]->m_DetailCtrl.InsertColumn(15,"F",LVCFMT_LEFT, 30);

	m_pPanelDlg[FLV]->m_bFlag = true;
}

void CAVAnalysisToolsDlg::InitH264ListCtrl(bool bFlag)
{
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pPanelDlg[nLoop]->ShowWindow(SW_HIDE);	
	}
	m_pPanelDlg[H264]->ShowWindow(SW_SHOW);
	if (m_pPanelDlg[H264]->m_bFlag) return;
	
	RECT rect = {0};
	m_pPanelDlg[H264]->GetClientRect(&rect);
	m_pPanelDlg[H264]->m_Lbutton.Create("格式解析", BS_GROUPBOX|WS_VISIBLE, CRect(0, 0, (rect.right - rect.left) / 2, rect.bottom - rect.top), m_pPanelDlg[H264], 1024);
	m_pPanelDlg[H264]->m_RUpButton.Create("文件头信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 0, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), m_pPanelDlg[H264], 1025);
	m_pPanelDlg[H264]->m_RDownButton.Create("详细信息", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), m_pPanelDlg[H264], 1026);

	m_pPanelDlg[H264]->m_Lbutton.GetClientRect(&rect);
	m_pPanelDlg[H264]->m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
											CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
											&m_pPanelDlg[H264]->m_Lbutton, 
											1);

	m_pPanelDlg[H264]->m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[H264]->m_ListCtrl.InsertColumn(0,"序号",LVCFMT_LEFT, 40);
	m_pPanelDlg[H264]->m_ListCtrl.InsertColumn(1,"nal_reference_idc",LVCFMT_LEFT, 160);
	m_pPanelDlg[H264]->m_ListCtrl.InsertColumn(2,"nal_type",LVCFMT_LEFT, 150);
	m_pPanelDlg[H264]->m_ListCtrl.InsertColumn(3,"nal_len",LVCFMT_LEFT, 150);


	m_pPanelDlg[H264]->m_RUpButton.GetClientRect(&rect);
	m_pPanelDlg[H264]->m_FileHeaderCtrl.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
												CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
												&m_pPanelDlg[H264]->m_RUpButton, 
												2);
	m_pPanelDlg[H264]->m_FileHeaderCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[H264]->m_FileHeaderCtrl.InsertColumn(0,"Name",LVCFMT_LEFT, (rect.right - rect.left) / 2);
	m_pPanelDlg[H264]->m_FileHeaderCtrl.InsertColumn(1,"Value",LVCFMT_LEFT, (rect.right - rect.left) / 2);

	m_pPanelDlg[H264]->m_RDownButton.GetClientRect(&rect);
	m_pPanelDlg[H264]->m_DetailCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_AUTOARRANGE, 
											CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
											&m_pPanelDlg[H264]->m_RDownButton, 
											2);

	m_pPanelDlg[H264]->m_DetailCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(0,"0",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(1,"1",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(2,"2",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(3,"3",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(4,"4",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(5,"5",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(6,"6",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(7,"7",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(8,"8",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(9,"9",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(10,"A",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(11,"B",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(12,"C",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(13,"D",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(14,"E",LVCFMT_LEFT, 30);
	m_pPanelDlg[H264]->m_DetailCtrl.InsertColumn(15,"F",LVCFMT_LEFT, 30);
	
	m_pPanelDlg[H264]->m_bFlag = true;
}
void CAVAnalysisToolsDlg::OnBnClickedButtonH264()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("Flash文件(*.h264)|*.h264");
	CFileDialog fileDlg(TRUE, _T("FLV"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{   
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();   

	}   
	if (strFilePath.IsEmpty()) return;

	InitH264ListCtrl(m_pPanelDlg[H264]->m_bFlag);

	h264_nal_parse(this, strFilePath.GetBuffer());
}
