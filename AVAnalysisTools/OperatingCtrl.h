#pragma once
#include "afxcmn.h"
#include "ItemMgr.h"

typedef struct _ITEMLPARAM
{
	COLORREF clrText;
	COLORREF clrTextBk;
	void *pTagData;
	int nRowIndex;
	int nLength;
	char chFlag[8];
	_ITEMLPARAM()
	{
		clrText   = NULL;
		clrTextBk = NULL;
		pTagData  = NULL;
		memset(chFlag, 0, 8);
		nRowIndex = 0;
		nLength   = 0;
	}

	~_ITEMLPARAM()
	{
		clrText   = NULL;
		clrTextBk = NULL;
		memset(chFlag, 0, 8);
		if (NULL != pTagData)
		{
			free(pTagData);
			pTagData = NULL;
		}
		nLength   = 0;
		nRowIndex = 0;
	}
}ITEMLPARAM, * PITEMLPARAM;

class CPanelList;
class COperatingCtrl : public CListCtrl
{
public:
	COperatingCtrl(CPanelList *pListDlg);
	~COperatingCtrl(void);

public:
	void AddItem(TAG *tag, int nIndex);
	void AddItem(NALU_t *naul, int nIndex);

	void parseFirstByte(TAG *tag, char *buff);
private:
	CPanelList *m_pListDlg;
	CButton button;
	
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
};

