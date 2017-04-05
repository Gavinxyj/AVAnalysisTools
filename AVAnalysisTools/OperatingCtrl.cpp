#include "StdAfx.h"
#include "OperatingCtrl.h"
#include "AVAnalysisToolsDlg.h"
#include "./H264/h264_stream.h"
COperatingCtrl::COperatingCtrl(CPanelList *pListDlg):m_pListDlg(pListDlg)
{
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

void COperatingCtrl::AddItem(NALU_t *nalu, int nIndex)
{
	int index = InsertItem(GetItemCount(), "");

	SetRedraw(FALSE);
	char szId[8] = {0};
	itoa(nIndex, szId, 10);

	ITEMLPARAM * pItemParam = new ITEMLPARAM();
	pItemParam->nRowIndex = index;
	pItemParam->pTagData  = nalu;
	strncpy(pItemParam->chFlag, "H264", sizeof("H264"));
	SetItemData(index, (DWORD_PTR)pItemParam);
	SetItemText(index, 0, szId);

	switch(nalu->nal_reference_idc >> 5)
	{
	case NAL_REF_IDC_PRIORITY_DISPOSABLE:
		{
			SetItemText(index, 1, "DISPOSABLE");
			break;
		}
	case NAL_REF_IDC_PRIORITY_LOW:
		{
			SetItemText(index, 1, "LOW");
			break;
		}
	case NAL_REF_IDC_PRIORITY_HIGH:
		{
			SetItemText(index, 1, "HIGH");
			break;
		}
	case NAL_REF_IDC_PRIORITY_HIGHEST:
		{
			SetItemText(index, 1, "HIGHEST");
			break;
		}
	default:
		{
			SetItemText(index, 1, "OTHER");
			break;
		}
	}
	
	switch(nalu->nal_unit_type)
	{
	case NAL_UNIT_TYPE_CODED_SLICE_NON_IDR:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "SLICE");
			break;
		}
	case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "DPA");
			break;
		}
	case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "DPB");
			break;
		}
	case NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "DPC");
			break;
		}
	case NAL_UNIT_TYPE_CODED_SLICE_IDR:
		{
			pItemParam->clrTextBk =  RGB(255, 114, 86);
			SetItemText(index, 2, "IDR_SLICE");
			break;
		}
	case NAL_UNIT_TYPE_SEI:
		{
			pItemParam->clrTextBk =  RGB(240, 128, 128);
			SetItemText(index, 2, "SEI");
			break;
		}
	case NAL_UNIT_TYPE_SPS:
		{
			pItemParam->clrTextBk =  RGB(205, 181, 205);
			SetItemText(index, 2, "SPS");
			break;
		}
	case NAL_UNIT_TYPE_PPS:
		{
			pItemParam->clrTextBk =  RGB(238, 106, 80);
			SetItemText(index, 2, "PPS");
			break;
		}
	case NAL_UNIT_TYPE_AUD:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "AUD");
			break;
		}
	case NAL_UNIT_TYPE_END_OF_SEQUENCE:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "END_SEQUENCE");
			break;
		}
	case NAL_UNIT_TYPE_END_OF_STREAM:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "END_STREAM");
			break;
		}
	case NAL_UNIT_TYPE_FILLER:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "FILLER_DATA");
			break;
		}
	case NAL_UNIT_TYPE_SPS_EXT:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "SPS_EXT");
			break;
		}
	case NAL_UNIT_TYPE_CODED_SLICE_AUX:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "AUXILIARY_SLICE");
			break;
		}
	default:
		{
			pItemParam->clrTextBk =  RGB(250, 235, 215);
			SetItemText(index, 2, "OTHER");
			break;
		}
	}
	
	CString strLen;
	strLen.Format("%d", nalu->len);
	SetItemText(index, 3, strLen);

	SetRedraw(TRUE);
}

void COperatingCtrl::AddItem(TAG *tag, int nIndex)
{
	int index = InsertItem(GetItemCount(), "");
	
	SetRedraw(FALSE);
	char szId[8] = {0};
	itoa(nIndex, szId, 10);
	
	ITEMLPARAM * pItemParam = new ITEMLPARAM();
	pItemParam->nRowIndex = index;
	pItemParam->pTagData  = tag->pTagData;
	strncpy(pItemParam->chFlag, "FLV", sizeof("FLV"));
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
		if (strncmp(pItemParam->chFlag, "FLV", sizeof("FLV")) == 0)
		{
			unsigned char *p = (unsigned char*)pItemParam->pTagData;
			m_pListDlg->m_DetailCtrl.DeleteAllItems();
			//算出有多少行每行16个字节
			int nCount = pItemParam->nLength / 16;
			for (int nLoop = 0; nLoop < nCount; nLoop ++)
			{
				m_pListDlg->m_DetailCtrl.InsertItem(nLoop, "");
				for (int index = 0; index < 16; index ++)
				{	
					strTemp.Format("%02X", *p);
					m_pListDlg->m_DetailCtrl.SetItemText(nLoop, index, strTemp);

					p ++;
				}	
			}
			//算出剩余的字节
			nCount = pItemParam->nLength % 16;
			int nRow = m_pListDlg->m_DetailCtrl.GetItemCount();

			m_pListDlg->m_DetailCtrl.InsertItem(nRow, "");
			for (int nLoop = 0; nLoop < nCount; nLoop ++)
			{
				strTemp.Format("%02X", *p);	
				m_pListDlg->m_DetailCtrl.SetItemText(nRow, nLoop, strTemp);
				p ++;
			}

			m_pListDlg->m_DetailCtrl.SetTextBkColor(RGB(205, 181, 205));
		}
		else if (strncmp(pItemParam->chFlag, "H264", sizeof("H264")) == 0)
		{
			NALU_t *pNaluItem = (NALU_t*)pItemParam->pTagData;
			unsigned char *p = (unsigned char*)pNaluItem->buf;
			m_pListDlg->m_DetailCtrl.DeleteAllItems();
			//算出有多少行每行16个字节
			int nCount = pNaluItem->len / 16;
			for (int nLoop = 0; nLoop < nCount; nLoop ++)
			{
				m_pListDlg->m_DetailCtrl.InsertItem(nLoop, "");
				for (int index = 0; index < 16; index ++)
				{	
					strTemp.Format("%02X", *p);
					m_pListDlg->m_DetailCtrl.SetItemText(nLoop, index, strTemp);

					p ++;
				}	
			}
			//算出剩余的字节
			nCount = pNaluItem->len % 16;
			int nRow = m_pListDlg->m_DetailCtrl.GetItemCount();

			m_pListDlg->m_DetailCtrl.InsertItem(nRow, "");
			for (int nLoop = 0; nLoop < nCount; nLoop ++)
			{
				strTemp.Format("%02X", *p);	
				m_pListDlg->m_DetailCtrl.SetItemText(nRow, nLoop, strTemp);
				p ++;
			}
			m_pListDlg->m_DetailCtrl.SetTextBkColor(RGB(205, 181, 205));

			m_pListDlg->m_FileHeaderCtrl.DeleteAllItems();

			m_pListDlg->m_FileHeaderCtrl.InsertItem(0, "");
			strResult.Format("%02X",*pNaluItem->buf);
			m_pListDlg->m_FileHeaderCtrl.SetItemText(0,0,"NALU首字节");
			m_pListDlg->m_FileHeaderCtrl.SetItemText(0,1,strResult);

			int nRet = 0;
			m_pListDlg->m_FileHeaderCtrl.InsertItem(1, "");
			sscanf_s(strResult.GetBuffer(), "%X", &nRet);
			CString F, NRI, TYPE;
			F.Format("%d", *pNaluItem->buf >> 7);
			m_pListDlg->m_FileHeaderCtrl.SetItemText(1,0,"禁止位（F）");
			m_pListDlg->m_FileHeaderCtrl.SetItemText(1,1,F);

			m_pListDlg->m_FileHeaderCtrl.InsertItem(2, "");
			int n = (*pNaluItem->buf & 0x60);
			NRI.Format("%d", (*pNaluItem->buf & 0x60) >>  5);
			m_pListDlg->m_FileHeaderCtrl.SetItemText(2,0,"重要级别（NRI）");
			m_pListDlg->m_FileHeaderCtrl.SetItemText(2,1,NRI);

			m_pListDlg->m_FileHeaderCtrl.InsertItem(3, "");
			TYPE.Format("%d", (*pNaluItem->buf & 0x1f));
			m_pListDlg->m_FileHeaderCtrl.SetItemText(3,0,"NALU类型（TYPE）");
			m_pListDlg->m_FileHeaderCtrl.SetItemText(3,1,TYPE);

			m_pListDlg->m_FileHeaderCtrl.SetTextBkColor(RGB(205, 181, 205));
		}
		
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
