
// AVAnalysisToolsDlg.h : 头文件
//

#pragma once
#include "OperatingCtrl.h"
#include "GdipButton.h"
#include "afxwin.h"
// CAVAnalysisToolsDlg 对话框
class COperatingCtrl;
class CAVAnalysisToolsDlg : public CDialogEx
{
// 构造
public:
	CAVAnalysisToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AVANALYSISTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

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
public:
	COperatingCtrl m_ListCtrl;
	COperatingCtrl m_FileHeaderCtrl;
	COperatingCtrl m_DetailCtrl;
	CButton m_Lbutton;
	CGdipButton m_recodeBtn;
	CButton m_RUpButton;
	CButton m_RDownButton;
	afx_msg void OnBnClickedFlv();
	CButton m_FlvButton;
};
