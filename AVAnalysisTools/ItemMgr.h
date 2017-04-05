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
/* FLV视频流格式有两部分组成，Flv header,Flv body                            */
/************************************************************************/
typedef struct _FLVHEADER
{
	unsigned char signature[3];	//文件标识
	unsigned char version[1];	//版本号
	unsigned char flags[1];		//前5位保留，必须位0，第6位表示是否存在音频Tag,第7位保留位必须位0，第8位表示是否存在视频Tag	
	unsigned char headSize[4];	//表示从File header 开始到File body 前的字节数，对于版本1来说总是为9

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
	
	unsigned char type[1];			//表示Tag类型，包括音频(0x08),视频(0x09)和script data(0x12)
	unsigned char dataSize[3];		//表示Tag Data部分的大小
	unsigned char timeStamp[3];		//表示时间戳
	unsigned char timeStampEx[1];	//表示时间戳的扩展字节，当24位数值不够是，该字段置为最高位将时间戳扩展位32位的数值
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
	unsigned char preTagSize[4];	//表示前一个Tag的大小
	PTAGHEADER pTagHeader;
	unsigned char *pTagData;	//音视频数据，不同类型的Tag，他的data部分的接口也不一样

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

