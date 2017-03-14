#include "StdAfx.h"
#include "OperatingCtrl.h"
#include "AVAnalysisToolsDlg.h"

COperatingCtrl::COperatingCtrl(CAVAnalysisToolsDlg *pToolDlg):m_pToolDlg(pToolDlg)
{
	InitializeCriticalSection(&m_csDeleteItem);
}


COperatingCtrl::~COperatingCtrl(void)
{
}
BEGIN_MESSAGE_MAP(COperatingCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &COperatingCtrl::OnNMCustomdraw)
END_MESSAGE_MAP()


void COperatingCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	*pResult = 0;
	// ָ���б������ǰ������Ϣ   
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;	
		

	//	*pResult = CDRF_DODEFAULT;
	
	}
	else if (pLVCD->nmcd.dwDrawStage == (CDDS_ITEMPREPAINT | CDDS_SUBITEM))
	{
		int iItem = pLVCD->nmcd.dwItemSpec;
		int iSubItem = pLVCD->iSubItem;
			
		if (0 != pLVCD->nmcd.lItemlParam)
		{
			ITEMLPARAM * pItemParam = (ITEMLPARAM *)pLVCD->nmcd.lItemlParam;		
			if (NULL != pItemParam)
			{
				if (NULL != pItemParam->clrText)
				{
					pLVCD->clrText = pItemParam->clrText;
				}
				if(NULL != pItemParam->clrTextBk)
				{
					pLVCD->clrTextBk = pItemParam->clrTextBk;
				}
			}
		}		
		
		*pResult = CDRF_DODEFAULT;
	}
}


void COperatingCtrl::AddItem(LPCTSTR strItemData)
{
	int index = InsertItem(GetItemCount(), "");
	ITEMLPARAM * pItemParam = new ITEMLPARAM();
	pItemParam->nRowIndex = 0;
	pItemParam->clrText = RGB(255,0,0);
	pItemParam->clrTextBk =  RGB(0, 77, 80);
	SetItemData(index, (DWORD_PTR)pItemParam);
	SetItemText(index, 0, "123");
	SetItemText(index, 1, "123");

}