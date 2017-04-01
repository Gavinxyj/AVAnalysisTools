
// AVAnalysisToolsDlg.h : 头文件
//

#pragma once

#include "GdipButton.h"
#include "afxwin.h"
#include "PanelList.h"
// CAVAnalysisToolsDlg 对话框
#define MAX_CHILDWND 16
enum {FLV, H264};


class CAVAnalysisToolsDlg : public CDialogEx
{
// 构造
public:
	CAVAnalysisToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AVANALYSISTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
public:
	void InitFlvListCtrl(bool bFlag);
	void InitH264ListCtrl(bool bFlag);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedFlv();
	afx_msg void OnBnClickedButtonH264();
public:
	CMap<int, int, CPanelList*, CPanelList*>m_mapPanelList;
	
	CPanelList *m_pPanelDlg[MAX_CHILDWND];
	CGdipButton m_recodeBtn;
	
	CButton m_FlvButton;
	CButton m_h264;
};
