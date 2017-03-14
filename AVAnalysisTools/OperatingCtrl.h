#pragma once
#include "afxcmn.h"

typedef struct _ITEMLPARAM
{
	COLORREF clrText;
	COLORREF clrTextBk;
	unsigned char *pTagData;
	int nRowIndex;

	_ITEMLPARAM()
	{
		clrText   = NULL;
		clrTextBk = NULL;
		pTagData  = NULL;
		nRowIndex = 0;
	}

	~_ITEMLPARAM()
	{
		clrText   = NULL;
		clrTextBk = NULL;
		if (NULL != pTagData)
		{
			free(pTagData);
			pTagData = NULL;
		}
		
		nRowIndex = 0;
	}
}ITEMLPARAM, * PITEMLPARAM;

class CAVAnalysisToolsDlg;
class COperatingCtrl : public CListCtrl
{
public:
	COperatingCtrl(CAVAnalysisToolsDlg *pToolDlg);
	~COperatingCtrl(void);

public:
	void AddItem(LPCTSTR strItemData);
private:
	CAVAnalysisToolsDlg *m_pToolDlg;
	CRITICAL_SECTION	m_csDeleteItem;
	CButton button;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
};
