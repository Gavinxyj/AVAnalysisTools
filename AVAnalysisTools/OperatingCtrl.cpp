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
	ON_NOTIFY_REFLECT(NM_CLICK, &COperatingCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &COperatingCtrl::OnLvnGetdispinfo)
END_MESSAGE_MAP()


void COperatingCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pLVCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	*pResult = 0;
	// 指定列表项绘制前后发送消息   
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


void COperatingCtrl::AddItem(TAG *tag, int nIndex)
{
	int index = InsertItem(GetItemCount(), "");
	SetItemCount(1024);
	SetRedraw(FALSE);
	char szId[8] = {0};
	itoa(nIndex, szId, 10);
	
	ITEMLPARAM * pItemParam = new ITEMLPARAM();
	pItemParam->nRowIndex = index;
	pItemParam->pTagData  = tag->pTagData;
	SetItemData(index, (DWORD_PTR)pItemParam);
	SetItemText(index, 0, szId);

	
	if (*tag->pTagHeader->type == 0x12)
	{
		pItemParam->clrTextBk =  RGB(255, 114, 86);
		SetItemText(index, 1, "Script");
	}
	else if (*tag->pTagHeader->type == 0x08)
	{
		pItemParam->clrTextBk =  RGB(205, 181, 205);
		SetItemText(index, 1, "Audio");
	}
	else if (*tag->pTagHeader->type == 0x09)
	{
		pItemParam->clrTextBk =  RGB(238, 106, 80);
		SetItemText(index, 1, "Video");
	}

	//Tag Data长度
	int nLen = 0;
	char szLen[8] = {0};
	CString strForamt;
	strForamt.Format("%02X%02X%02X",tag->pTagHeader->dataSize[0],tag->pTagHeader->dataSize[1],tag->pTagHeader->dataSize[2]);
	sscanf_s(strForamt.GetBuffer(), "%X", &nLen);
	itoa(nLen,   szLen, 10);
	SetItemText(index, 2, szLen);
	pItemParam->nLength = nLen;
	//时间戳
	char szTime[16] = {0};
	strForamt.Format("%02X%02X%02X%02X",tag->pTagHeader->timeStampEx[0], tag->pTagHeader->timeStamp[0],tag->pTagHeader->timeStamp[1],tag->pTagHeader->timeStamp[2]);
	sscanf_s(strForamt.GetBuffer(), "%X", &nLen);
	itoa(nLen,   szTime, 10);
	SetItemText(index, 3, szTime);
	
	//首字节类型解析
	char szBuff[256] = {0};
	parseFirstByte(tag, szBuff);
	SetItemText(index, 4, szBuff);

	SetRedraw(TRUE);

}

void COperatingCtrl::parseFirstByte(TAG *tag, char *buff)
{
	if (*tag->pTagHeader->type == 0x08)
	{
		int bit = (*tag->pTagData >> 4) & 0x0F;
		switch(bit)
		{
		case 0:
			strncpy(buff, "Linear PCM，platform endian| ", sizeof("Linear PCM，platform endian|"));
			break;
		case 1:
			strncpy(buff, "ADPCM|", sizeof("ADPCM|"));
			break;
		case 2:
			strncpy(buff, "MP3|", sizeof("MP3|"));
			break;
		case 3:
			strncpy(buff, "Linear PCM，little endian|", sizeof("Linear PCM，little endian|"));
			break;
		case 4:
			strncpy(buff, "Nellymoser 16-kHz mono|", sizeof("Nellymoser 16-kHz mono|"));
			break;
		case 5:
			strncpy(buff, "Nellymoser 8-kHz mono|", sizeof("Nellymoser 8-kHz mono|"));
			break;
		case 6:
			strncpy(buff, "Nellymoser|", sizeof(" Nellymoser|"));
			break;
		case 7:
			strncpy(buff, "G.711 A-law logarithmic PCM|", sizeof("G.711 A-law logarithmic PCM|"));
			break;
		case 8:
			strncpy(buff, "G.711 mu-law logarithmic PCM|", sizeof("G.711 mu-law logarithmic PCM|"));
			break;
		case 9:
			strncpy(buff, "reserved|", sizeof("reserved|"));
			break;
		case 10:
			strncpy(buff, "AAC|", sizeof("AAC|"));
			break;
		case 14:
			strncpy(buff, "MP3 8-Khz|", sizeof("MP3 8-Khz|"));
			break;
		case 15:
			strncpy(buff, "Device-specific sound|", sizeof("Device-specific sound|"));
			break;
		default:
			break;
		}
		bit = (*tag->pTagData & 0x0F) >> 2;

		switch(bit)
		{
		case 0:
			strcat(buff, "5.5kHz|");
			break;
		case 1:
			strcat(buff, "11kHz|");
			break;
		case 2:
			strcat(buff, "22kHz|");
			break;
		case 3:
			strcat(buff, "44kHz|");
		default:
			break;
		}

		bit = *tag->pTagData & 0x02;

		if (bit == 0)
		{
			strcat(buff, "8bits|");
		}
		else
		{
			strcat(buff, "16bits|");
		}

		bit = *tag->pTagData & 0x01;

		if (bit == 0)
		{
			strcat(buff, "sndMono");
		}
		else
		{
			strcat(buff, "sndStereo");
		}
	}
	else if (*tag->pTagHeader->type == 0x09)
	{
		int bit = (*tag->pTagData >> 4) & 0x0F;

		switch(bit)
		{
		case 1:
			strncpy(buff, "keyframe|", sizeof("keyframe|"));
			break;
		case 2:
			strncpy(buff, "inter frame|", sizeof("inter frame|"));
			break;
		case 3:
			strncpy(buff, "disposable inter frame|", sizeof("disposable inter frame|"));
			break;
		case 4:
			strncpy(buff, "generated keyframe|", sizeof("generated keyframe|"));
			break;
		case 5:
			strncpy(buff, "video info/command frame|", sizeof("video info/command frame|"));
			break;
		default:
			break;
		}

		bit = *tag->pTagData & 0x0F;

		switch(bit)
		{
		case 1:
			strcat(buff, "JPEG");
			break;
		case 2:
			strcat(buff, "Sorenson H.263");
			break;
		case 3:
			strcat(buff, "Sorenson H.263");
			break;
		case 4:
			strcat(buff, "On2 VP6");
			break;
		case 5:
			strcat(buff, "On2 VP6 with alpha channel");
			break;
		case 6:
			strcat(buff, "Screen video version 2");
			break;
		case 7:
			strcat(buff, "AVC");
			break;
		default:
			break;
		}
	}
}

void COperatingCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMItemActivate = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pNMItemActivate->iItem == -1) return;
	
	ITEMLPARAM * pItemParam = (ITEMLPARAM*)GetItemData(pNMItemActivate->iItem);
	CString strTemp, strResult;
	
	if (NULL != pItemParam)
	{
		unsigned char *p = pItemParam->pTagData;
		m_pToolDlg->m_DetailCtrl.DeleteAllItems();
		//算出有多少行每行16个字节
		int nCount = pItemParam->nLength / 16;
		for (int nLoop = 0; nLoop < nCount; nLoop ++)
		{
			m_pToolDlg->m_DetailCtrl.InsertItem(nLoop, "");
			for (int index = 0; index < 16; index ++)
			{	
				strTemp.Format("%02X", *p);
				m_pToolDlg->m_DetailCtrl.SetItemText(nLoop, index, strTemp);
				
				p ++;
			}	
		}
		//算出剩余的字节
		nCount = pItemParam->nLength % 16;
		int nRow = m_pToolDlg->m_DetailCtrl.GetItemCount();

		m_pToolDlg->m_DetailCtrl.InsertItem(nRow, "");
		for (int nLoop = 0; nLoop < nCount; nLoop ++)
		{
			strTemp.Format("%02X", *p);	
			m_pToolDlg->m_DetailCtrl.SetItemText(nRow, nLoop, strTemp);
			p ++;
		}

		m_pToolDlg->m_DetailCtrl.SetTextBkColor(RGB(205, 181, 205));
	}
	*pResult = 0;
}


void COperatingCtrl::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	//NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;

	*pResult = 0;
}
