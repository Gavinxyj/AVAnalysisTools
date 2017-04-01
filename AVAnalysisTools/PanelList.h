#pragma once

#include "OperatingCtrl.h"
// CPanelList �Ի���
class CPanelList : public CDialogEx
{
	DECLARE_DYNAMIC(CPanelList)

public:
	CPanelList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPanelList();

// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
