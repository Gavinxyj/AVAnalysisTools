#pragma once

#include "OperatingCtrl.h"
// CPanelList 对话框
class CPanelList : public CDialogEx
{
	DECLARE_DYNAMIC(CPanelList)

public:
	CPanelList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPanelList();

// 对话框数据
	enum { IDD = IDD_DIALOG_PANEL };
public:
	CButton m_Lbutton;
	CButton m_RUpButton;
	CButton m_RDownButton;
	COperatingCtrl m_ListCtrl;
	COperatingCtrl m_FileHeaderCtrl;
	COperatingCtrl m_DetailCtrl;
	bool m_bFlag;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
