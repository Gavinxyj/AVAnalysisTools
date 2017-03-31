// H264ListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "AVAnalysisTools.h"
#include "H264ListCtrl.h"
#include "AVAnalysisToolsDlg.h"

// CH264ListCtrl

IMPLEMENT_DYNAMIC(CH264ListCtrl, CListCtrl)

CH264ListCtrl::CH264ListCtrl(CAVAnalysisToolsDlg *pToolDlg): m_pToolDlg(pToolDlg)
{

}

CH264ListCtrl::~CH264ListCtrl()
{
}


BEGIN_MESSAGE_MAP(CH264ListCtrl, CListCtrl)
END_MESSAGE_MAP()



// CH264ListCtrl 消息处理程序


