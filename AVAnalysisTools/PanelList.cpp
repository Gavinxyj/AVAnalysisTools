// PanelList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AVAnalysisTools.h"
#include "PanelList.h"
#include "afxdialogex.h"


// CPanelList �Ի���

IMPLEMENT_DYNAMIC(CPanelList, CDialogEx)

CPanelList::CPanelList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPanelList::IDD, pParent),m_ListCtrl(this),m_FileHeaderCtrl(this),m_DetailCtrl(this)
{
	m_bFlag = false;
}

CPanelList::~CPanelList()
{
}

void CPanelList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPanelList, CDialogEx)
END_MESSAGE_MAP()


// CPanelList ��Ϣ�������
