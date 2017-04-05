
// AVAnalysisToolsDlg.cpp : ʵ���ļ�
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
	
	CRect dlgRect = NULL;
	GetClientRect(&dlgRect);
	for (int nLoop = 0; nLoop < MAX_CHILDWND; nLoop ++)
	{
		m_pPanelDlg[nLoop] = new CPanelList();
		m_pPanelDlg[nLoop]->Create(IDD_DIALOG_PANEL, this);
		m_pPanelDlg[nLoop]->ShowWindow(SW_SHOW);
		m_pPanelDlg[nLoop]->MoveWindow(0, 60, dlgRect.Width(), dlgRect.Height() - 60);
	}
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
	
	
	
	return 0;
}

void CAVAnalysisToolsDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
}


void CAVAnalysisToolsDlg::OnBnClickedFlv()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	TCHAR szFilter[] = _T("Flash�ļ�(*.flv)|*.flv");
	CFileDialog fileDlg(TRUE, _T("FLV"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
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
	m_pPanelDlg[FLV]->m_Lbutton.Create("��ʽ����", BS_GROUPBOX|WS_VISIBLE, CRect(0, 0, (rect.right - rect.left) / 2, rect.bottom - rect.top), m_pPanelDlg[FLV], 1024);
	m_pPanelDlg[FLV]->m_RUpButton.Create("�ļ�ͷ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 0, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), m_pPanelDlg[FLV], 1025);
	m_pPanelDlg[FLV]->m_RDownButton.Create("��ϸ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), m_pPanelDlg[FLV], 1026);

	m_pPanelDlg[FLV]->m_Lbutton.GetClientRect(&rect);
	m_pPanelDlg[FLV]->m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
										CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
										&m_pPanelDlg[FLV]->m_Lbutton, 
										1);

	m_pPanelDlg[FLV]->m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(0,"���",LVCFMT_LEFT, 40);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(1,"����",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(2,"��С",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(3,"ʱ���",LVCFMT_LEFT, 80);
	m_pPanelDlg[FLV]->m_ListCtrl.InsertColumn(4,"Tag Data���ֽ�",LVCFMT_LEFT, 220);


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
	m_pPanelDlg[H264]->m_Lbutton.Create("��ʽ����", BS_GROUPBOX|WS_VISIBLE, CRect(0, 0, (rect.right - rect.left) / 2, rect.bottom - rect.top), m_pPanelDlg[H264], 1024);
	m_pPanelDlg[H264]->m_RUpButton.Create("�ļ�ͷ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, 0, (rect.right - rect.left) , (rect.bottom - rect.top) / 2 - 50), m_pPanelDlg[H264], 1025);
	m_pPanelDlg[H264]->m_RDownButton.Create("��ϸ��Ϣ", BS_GROUPBOX|WS_VISIBLE, CRect((rect.right - rect.left) / 2 + 1, (rect.bottom - rect.top) / 2 - 48, (rect.right - rect.left) , (rect.bottom - rect.top)), m_pPanelDlg[H264], 1026);

	m_pPanelDlg[H264]->m_Lbutton.GetClientRect(&rect);
	m_pPanelDlg[H264]->m_ListCtrl.Create(	WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS, 
											CRect(2, 20, (rect.right - rect.left) - 2, rect.bottom - rect.top - 2), 
											&m_pPanelDlg[H264]->m_Lbutton, 
											1);

	m_pPanelDlg[H264]->m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_GRIDLINES);
	m_pPanelDlg[H264]->m_ListCtrl.InsertColumn(0,"���",LVCFMT_LEFT, 40);
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("Flash�ļ�(*.h264)|*.h264");
	CFileDialog fileDlg(TRUE, _T("FLV"), NULL, 0, szFilter, this);   
	CString strFilePath;   
	if (IDOK == fileDlg.DoModal())   
	{   
		// ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetPathName();   

	}   
	if (strFilePath.IsEmpty()) return;

	InitH264ListCtrl(m_pPanelDlg[H264]->m_bFlag);

	h264_nal_parse(this, strFilePath.GetBuffer());
}
