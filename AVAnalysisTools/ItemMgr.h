#pragma once
#include <iostream>
#include <vector>

typedef struct
{
	int startcodeprefix_len;      //! 4 for parameter sets and first slice in picture, 3 for everything else (suggested)
	unsigned int len;                 //! Length of the NAL unit (Excluding the start code, which does not belong to the NALU)
	unsigned int max_size;            //! Nal Unit Buffer size
	int forbidden_bit;            //! should be always FALSE
	int nal_reference_idc;        //! NALU_PRIORITY_xxxx
	int nal_unit_type;            //! NALU_TYPE_xxxx    
	unsigned char *buf;                    //! contains the first byte followed by the EBSP
	unsigned short lost_packets;  //! true, if packet loss is detected
	int data_offset;
} NALU_t;


/************************************************************************/
/* FLV��Ƶ����ʽ����������ɣ�Flv header,Flv body                            */
/************************************************************************/
typedef struct _FLVHEADER
{
	unsigned char signature[3];	//�ļ���ʶ
	unsigned char version[1];	//�汾��
	unsigned char flags[1];		//ǰ5λ����������λ0����6λ��ʾ�Ƿ������ƵTag,��7λ����λ����λ0����8λ��ʾ�Ƿ������ƵTag	
	unsigned char headSize[4];	//��ʾ��File header ��ʼ��File body ǰ���ֽ��������ڰ汾1��˵����Ϊ9

	_FLVHEADER()
	{
		memset(signature, 0, 3);
		memset(headSize, 0, 4);
		memset(flags, 0, 1);
		memset(version, 0, 1);
	}

	~_FLVHEADER()
	{
		memset(signature, 0, 4);
		memset(headSize, 0, 5);
		memset(flags, 0, 2);
		memset(version, 0, 2);
	}
}FLVHEADER, *PFLVHEADER;

typedef struct _TAGHEADER
{
	
	unsigned char type[1];			//��ʾTag���ͣ�������Ƶ(0x08),��Ƶ(0x09)��script data(0x12)
	unsigned char dataSize[3];		//��ʾTag Data���ֵĴ�С
	unsigned char timeStamp[3];		//��ʾʱ���
	unsigned char timeStampEx[1];	//��ʾʱ�������չ�ֽڣ���24λ��ֵ�����ǣ����ֶ���Ϊ���λ��ʱ�����չλ32λ����ֵ
	unsigned char streamId[3];		
	_TAGHEADER()
	{
		
		memset(dataSize, 0, 3);
		memset(timeStamp, 0, 3);
		memset(streamId, 0, 3);
		timeStampEx[0] = '\0';
		type[0] = '\0';
	}

	~_TAGHEADER()
	{
		memset(dataSize, 0, 3);
		memset(timeStamp, 0, 3);
		memset(streamId, 0, 3);
		timeStampEx[0] = '\0';
		type[0] = '\0';
	}
}TAGHEADER, *PTAGHEADER;

typedef struct _TAG
{
	unsigned char preTagSize[4];	//��ʾǰһ��Tag�Ĵ�С
	PTAGHEADER pTagHeader;
	unsigned char *pTagData;	//����Ƶ���ݣ���ͬ���͵�Tag������data���ֵĽӿ�Ҳ��һ��

	_TAG()
	{
		memset(preTagSize, 0, 4);
		pTagData	= NULL;
		pTagHeader  = NULL;
	}

	~_TAG()
	{
		memset(preTagSize, 0, 4);
		if (NULL != pTagData)
		{
			delete pTagData;
			pTagData = NULL;
		}

		if (NULL != pTagHeader)
		{
			delete pTagHeader;
			pTagHeader = NULL;
		}
	}
}TAG, *PTAG;

typedef struct _FLVBODY
{
	std::vector<PTAG>vecTag;

	_FLVBODY()
	{
		vecTag.clear();
	}
	
	~_FLVBODY()
	{
		if (0 != vecTag.size())
		{
			std::vector<PTAG>::iterator iter = vecTag.begin();
			for (; iter != vecTag.end(); iter ++)
			{
				delete *iter;
				*iter = NULL;
			}
			vecTag.clear();
		}
	}
}FLVBODY,*PFLVBODY;



class CItemMgr
{
public:
	CItemMgr(void);
	~CItemMgr(void);
};

