
// AVAnalysisToolsDlg.h : ͷ�ļ�
//

#pragma once
#include "OperatingCtrl.h"
#include "GdipButton.h"
#include "afxwin.h"
// CAVAnalysisToolsDlg �Ի���
class COperatingCtrl;
class CAVAnalysisToolsDlg : public CDialogEx
{
// ����
public:
	CAVAnalysisToolsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AVANALYSISTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

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
