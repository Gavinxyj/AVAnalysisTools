
// AVAnalysisToolsDlg.h : ͷ�ļ�
//

#pragma once

#include "GdipButton.h"
#include "afxwin.h"
#include "PanelList.h"
// CAVAnalysisToolsDlg �Ի���
#define MAX_CHILDWND 16
enum {FLV, H264};


class CAVAnalysisToolsDlg : public CDialogEx
{
// ����
public:
	CAVAnalysisToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AVANALYSISTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	void InitFlvListCtrl(bool bFlag);
	void InitH264ListCtrl(bool bFlag);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
