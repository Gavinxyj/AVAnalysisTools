#include "StdAfx.h"
#include "ParserFormat.h"

#include <stdio.h>

static bool bFlag = false;
CParserFormat* CParserFormat::m_pInstance = NULL;
CParserFormat::CParserFormat(void)
{
	PropertyConfigurator::configure("C:\\DriverAdaptor\\config.properties");
	logger = Logger::getLogger("debugLogger");
	m_vecMeta.clear();
	m_vecTag.clear();
}


CParserFormat::~CParserFormat(void)
{
}

CParserFormat* CParserFormat::getInstance()
{
	if (NULL == m_pInstance)
	{
		m_pInstance = new CParserFormat();
	}
	return m_pInstance;
}

bool CParserFormat::parserFlvFile(const char *fileName)
{
	if (NULL == fileName) return false;
	
	FILE *file = fopen(fileName, "rb");


	if (NULL == file)
	{
		LOG4CXX_ERROR(logger, "文件："<< fileName << "打开失败！");
		return false;
	}
	PFLVHEADER pFlvHeader = new FLVHEADER;
	
	//读取FLV文件头信息
	fread((char*)pFlvHeader, 1, sizeof(FLVHEADER), file);
	
	if (*pFlvHeader->flags == 0x05)
	{
		LOG4CXX_ERROR(logger, "文件："<< fileName << "包含音视频流");
	}
	else if (*pFlvHeader->flags == 0x04)
	{
		LOG4CXX_ERROR(logger, "文件："<< fileName << "只包含音频流");
	}
	else
	{
		LOG4CXX_ERROR(logger, "文件："<< fileName << "只包含视频流");
	}

	

	while (!feof(file))
	{
		PTAG pTag = new TAG;

		//读取Previous Tag size
		fread((char*)pTag->preTagSize, 1, 4, file);

		//读取Tag Header信息
		PTAGHEADER pTagHeader = new TAGHEADER;
		fread((char*)pTagHeader, 1, sizeof(TAGHEADER), file);

		pTag->pTagHeader = pTagHeader;

		if (*pTagHeader->type == TAG_TYPE_SCRIPT)
		{
			int nLen = 0;
			CString strForamt;
			strForamt.Format("%02x%02x%02x",pTagHeader->dataSize[0],pTagHeader->dataSize[1],pTagHeader->dataSize[2]);
			sscanf_s(strForamt.GetBuffer(), "%x", &nLen);		

			if (0 != nLen)
			{
				unsigned char *tagData = (unsigned char *)malloc(sizeof(unsigned char) * nLen + 1);
				memset(tagData, 0, nLen + 1);

				fread(tagData, 1, nLen, file);

				this->parserMetaData(tagData, nLen);
			}

		}
		else if(*pTagHeader->type == TAG_TYPE_VIDEO)
		{
			int nLen = 0;
			CString strForamt;
			strForamt.Format("%02x%02x%02x",pTagHeader->dataSize[0],pTagHeader->dataSize[1],pTagHeader->dataSize[2]);
			sscanf_s(strForamt.GetBuffer(), "%x", &nLen);		

			if (0 != nLen)
			{
				unsigned char *tagData = (unsigned char *)malloc(sizeof(unsigned char) * nLen + 1);
				memset(tagData, 0, nLen + 1);

				fread(tagData, 1, nLen, file);
				this->parserVideoTag(tagData);
				
				pTag->pTagData = tagData;
			}
		}
		else if (*pTagHeader->type == TAG_TYPE_AUDIO)
		{
			int nLen = 0;
			CString strForamt;
			strForamt.Format("%02x%02x%02x",pTagHeader->dataSize[0],pTagHeader->dataSize[1],pTagHeader->dataSize[2]);
			sscanf_s(strForamt.GetBuffer(), "%x", &nLen);		

			if (0 != nLen)
			{
				unsigned char *tagData = (unsigned char *)malloc(sizeof(unsigned char) * nLen + 1);
				memset(tagData, 0, nLen + 1);
				fread(tagData, 1, nLen, file);			
				pTag->pTagData = tagData;
			}
		}

		m_vecTag.push_back(pTag);
	}
	

	fclose(file);
	return true;
}

bool CParserFormat::parserMetaData(const unsigned char *buffer, int nLen)
{
	CString strFormat;
	int nPos = 0;
	bool bFlag = false;
	unsigned char chTemp[32] = {0};
	//读取metaData信息
	strFormat.Format("%02x%02x", *(buffer + 1), *(buffer + 2));
	sscanf_s(strFormat.GetBuffer(), "%x", &nPos);
	memcpy(chTemp, buffer + 3, nPos);
	m_vecMeta.push_back((char *)chTemp);

	//读取数组中的键值对信息
	int arrayLen = 0;
	buffer = buffer + nPos + 3;
	strFormat.Format("%02x%02x%02x%02x", *(buffer + 1), *(buffer + 2),*(buffer + 3),*(buffer + 4));
	sscanf_s(strFormat.GetBuffer(), "%x", &arrayLen);

	buffer = buffer + 4;
	for (int nLoop = 0; nLoop < arrayLen * 2; nLoop ++)
	{
		int offset = getString(buffer);
		buffer = buffer + offset;
		switch(*buffer)
		{
		case Number:
			offset = getNumber(buffer);
			buffer = buffer + offset;
			break;
		case Boolean:
			offset = getBoolean(buffer);
			buffer = buffer + offset;
			break;
		case String:	
			offset = getString(buffer);
			buffer = buffer + offset - 1;
			break;
		case Object:
			break;
		case MovieClip:
			break;
		case Null:		
			break;
		case Undefined:
			break;
		case Reference:
			break;
		case ECMA_ARRAY:
			break;
		case Object_end_marker:
			
			break;
		case Strict_array:
			bFlag = true;
			break;
		case Date:
			break;
		case Long_string:
			break;
		default:
			break;
		}

		if (bFlag) break;
		
	}

	
	return true;
}

int CParserFormat::getString(const unsigned char *buff)
{
	CString strFormat;
    char *chTemp = new char[32];
	memset(chTemp, 0, 32);
	int nPos = 0;
	strFormat.Format("%02x%02x", *(buff + 1), *(buff + 2));
	sscanf_s(strFormat.GetBuffer(), "%x", &nPos);
	memcpy(chTemp, buff + 3, nPos);
	m_vecMeta.push_back(chTemp);
	return nPos + 3;
}

int CParserFormat::getBoolean(const unsigned char *buff)
{
	m_vecMeta.push_back((char*)(buff + 1));
	return 1;
}

int CParserFormat::getNumber(const unsigned char *buff)
{
	CString strFormat;
	char *chTemp = new char[32];
	memset(chTemp, 0, 32);
	int nPos = 0;
	strFormat.Format("%02x%02x%02x%02x%02x%02x%02x%02x", 
					  *(buff + 1), *(buff + 2),
					  *(buff + 3), *(buff + 4),
					  *(buff + 5), *(buff + 6),
					  *(buff + 7), *(buff + 8));
	//sscanf_s(strFormat.GetBuffer(), "%x", &nPos);
	memcpy(chTemp, buff + 1, 8);
	m_vecMeta.push_back(chTemp);
	return nPos + 8;
}

int CParserFormat::getStrictArray(const unsigned char *buff)
{
	return 0;
}

bool CParserFormat::parserVideoTag(const unsigned char *buffer)
{

	return true;
}