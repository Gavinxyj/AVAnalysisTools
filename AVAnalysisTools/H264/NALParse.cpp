/* 
 * H.264 ������
 * H.264 Analysis
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 * 
 * H.264������������
 * H.264 Stream Analysis Tools
 *
 */

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "NAL.h"
#include "NALParse.h"
#include "../AVAnalysisToolsDlg.h"
#include "../ItemMgr.h"


FILE *bits = NULL;                //!< the bit stream file
static int FindStartCode2 (unsigned char *Buf);//���ҿ�ʼ�ַ�0x000001
static int FindStartCode3 (unsigned char *Buf);//���ҿ�ʼ�ַ�0x00000001
//static bool flag = true;
static int info2=0, info3=0;

NALU_HEADER		*nalu_hdr;
FU_INDICATOR	*fu_ind;
FU_HEADER		*fu_hdr;
//-------------------


//ΪNALU_t�ṹ������ڴ�ռ�
NALU_t *AllocNALU(int buffersize)
{
  NALU_t *n;

  if ((n = (NALU_t*)calloc (1, sizeof (NALU_t))) == NULL)
  {
	  printf("AllocNALU: n");
	  exit(0);
  }

  n->max_size=buffersize;

  if ((n->buf = (unsigned char*)calloc (buffersize, sizeof (unsigned char))) == NULL)
  {
    free (n);
    printf ("AllocNALU: n->buf");
	exit(0);
  }

  return n;
}
//�ͷ�
void FreeNALU(NALU_t *n)
{
  if (n)
  {
    if (n->buf)
    {
      free(n->buf);
      n->buf=NULL;
    }
    free (n);
  }
}

void OpenBitstreamFile (char *fn)
{
  if (NULL == (bits=fopen(fn, "r+b")))
  {
	  printf("open file error\n");
	  exit(0);
  }
}
//�����������Ϊһ��NAL�ṹ�壬��Ҫ����Ϊ�õ�һ��������NALU��������NALU_t��buf�У���ȡ���ĳ��ȣ����F,IDC,TYPEλ��
//���ҷ���������ʼ�ַ�֮�������ֽ�������������ǰ׺��NALU�ĳ���
int GetAnnexbNALU (NALU_t *nalu)
{
  int pos = 0;
  int StartCodeFound, rewind;
  unsigned char *Buf;
    
  if ((Buf = (unsigned char*)calloc (nalu->max_size , sizeof(char))) == NULL) 
	  printf ("GetAnnexbNALU: Could not allocate Buf memory\n");

  nalu->startcodeprefix_len=3;//��ʼ���������еĿ�ʼ�ַ�Ϊ3���ֽ�
  
   if (3 != fread (Buf, 1, 3, bits))//�������ж�3���ֽ�
	   {
		free(Buf);
		return 0;
	   }
   info2 = FindStartCode2 (Buf);//�ж��Ƿ�Ϊ0x000001 
   if(info2 != 1) 
   {
	//������ǣ��ٶ�һ���ֽ�
    if(1 != fread(Buf+3, 1, 1, bits))//��һ���ֽ�
		{
		 free(Buf);
		 return 0;
		}
    info3 = FindStartCode3 (Buf);//�ж��Ƿ�Ϊ0x00000001
    if (info3 != 1)//������ǣ�����-1
		{ 
		 free(Buf);
		 return -1;
		}
    else 
		{
		//�����0x00000001,�õ���ʼǰ׺Ϊ4���ֽ�
		 pos = 4;
		 nalu->startcodeprefix_len = 4;
		}
   }
   
   else
	   {
	   //�����0x000001,�õ���ʼǰ׺Ϊ3���ֽ�
		nalu->startcodeprefix_len = 3;
		pos = 3;
	   }
   //������һ����ʼ�ַ��ı�־λ
   StartCodeFound = 0;
   info2 = 0;
   info3 = 0;
  
  while (!StartCodeFound)
  {
    if (feof (bits))//�ж��Ƿ����ļ�β
    {
      nalu->len = (pos-1)-nalu->startcodeprefix_len;
      memcpy (nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);     
      nalu->forbidden_bit = nalu->buf[0] & 0x80; //1 bit
	  nalu->nal_reference_idc = nalu->buf[0] & 0x60; // 2 bit
	  nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;// 5 bit
      free(Buf);
      return pos-1;
    }
    Buf[pos++] = fgetc (bits);//��һ���ֽڵ�BUF��
    info3 = FindStartCode3(&Buf[pos-4]);//�ж��Ƿ�Ϊ0x00000001
    if(info3 != 1)
      info2 = FindStartCode2(&Buf[pos-3]);//�ж��Ƿ�Ϊ0x000001
    StartCodeFound = (info2 == 1 || info3 == 1);
  }
  

 
  // Here, we have found another start code (and read length of startcode bytes more than we should
  // have.  Hence, go back in the file
  rewind = (info3 == 1)? -4 : -3;

  if (0 != fseek (bits, rewind, SEEK_CUR))//���ļ�ָ��ָ��ǰһ��NALU��ĩβ
  {
    free(Buf);
	printf("GetAnnexbNALU: Cannot fseek in the bit stream file");
  }

  // Here the Start code, the complete NALU, and the next start code is in the Buf.  
  // The size of Buf is pos, pos+rewind are the number of bytes excluding the next
  // start code, and (pos+rewind)-startcodeprefix_len is the size of the NALU excluding the start code

  nalu->len = (pos+rewind)-nalu->startcodeprefix_len;
  memcpy (nalu->buf, &Buf[nalu->startcodeprefix_len], nalu->len);//����һ������NALU����������ʼǰ׺0x000001��0x00000001
  nalu->forbidden_bit = nalu->buf[0] & 0x80; //1 bit
  nalu->nal_reference_idc = nalu->buf[0] & 0x60; // 2 bit
  nalu->nal_unit_type = (nalu->buf[0]) & 0x1f;// 5 bit
  free(Buf);
 
  return (pos+rewind);//����������ʼ�ַ�֮�������ֽ�������������ǰ׺��NALU�ĳ���
}
//���NALU���Ⱥ�TYPE
void dump(NALU_t *n)
{
	if (!n)return;
	//printf("a new nal:");
	//printf(" len: %d  ", n->len);
	//printf("nal_unit_type: %d\n", n->nal_unit_type);
	//��ȡ����
//	dlg->AppendNLInfo(n->nal_reference_idc,n->nal_unit_type,n->len,n->len+n->startcodeprefix_len,n->data_offset);
}

int h264_nal_parse(LPVOID lparam,char *fileurl)
{
	OpenBitstreamFile(fileurl);//��264�ļ��������ļ�ָ�븳��bits,�ڴ��޸��ļ���ʵ�ִ򿪱��264�ļ���
	NALU_t *n;
	char* nalu_payload;  
	char sendbuf[1500];
	
	unsigned short seq_num =0;
	int	bytes=0;

	float framerate=15;
	unsigned int timestamp_increse=0,ts_current=0;
	timestamp_increse=(unsigned int)(90000.0 / framerate); //+0.5);

	
	//------------------
	int data_offset=0;
	//��ֵ-----------------
	CAVAnalysisToolsDlg *dlg =(CAVAnalysisToolsDlg *)lparam;
	//----------
	int nal_num=0;
	//----------
	while(!feof(bits)) 
	{
		n = AllocNALU(409600);//Ϊ�ṹ��nalu_t�����Աbuf����ռ䡣����ֵΪָ��nalu_t�洢�ռ��ָ��
		int data_lenth;
		data_lenth=GetAnnexbNALU(n);//ÿִ��һ�Σ��ļ���ָ��ָ�򱾴��ҵ���NALU��ĩβ����һ��λ�ü�Ϊ�¸�NALU����ʼ��0x000001
		n->data_offset=data_offset;
		data_offset=data_offset+data_lenth;

		dump(n);//���NALU���Ⱥ�TYPE
		//�ж��Ƿ�ѡ���ˡ�ֻ����5000���������ѡ���˾Ͳ��ٷ�����
		/*if(dlg->m_vh264nallistmaxnum.GetCheck()==1&&nal_num>5000){
			break;
		}*/
		nal_num++;
		dlg->m_pPanelDlg[H264]->m_ListCtrl.AddItem(n, nal_num);
	}
	FreeNALU(n);
	return 0;
}

static int FindStartCode2 (unsigned char *Buf)
{
 if(Buf[0]!=0 || Buf[1]!=0 || Buf[2] !=1) return 0; //�ж��Ƿ�Ϊ0x000001,����Ƿ���1
 else return 1;
}

static int FindStartCode3 (unsigned char *Buf)
{
 if(Buf[0]!=0 || Buf[1]!=0 || Buf[2] !=0 || Buf[3] !=1) return 0;//�ж��Ƿ�Ϊ0x00000001,����Ƿ���1
 else return 1;
}
