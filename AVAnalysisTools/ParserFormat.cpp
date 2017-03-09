#include "StdAfx.h"
#include "ParserFormat.h"
#include "ItemMgr.h"
#include <stdio.h>

static bool bFlag = false;
CParserFormat* CParserFormat::m_pInstance = NULL;
CParserFormat::CParserFormat(void)
{
	PropertyConfigurator::configure("C:\\DriverAdaptor\\config.properties");
	logger = Logger::getLogger("debugLogger");
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
		LOG4CXX_ERROR(logger, "�ļ���"<< fileName << "��ʧ�ܣ�");
		return false;
	}
	PFLVHEADER pFlvHeader = new FLVHEADER;
	
	//��ȡFLV�ļ�ͷ��Ϣ
	fread((char*)pFlvHeader, 1, sizeof(FLVHEADER), file);
	
	if (*pFlvHeader->flags == 0x05)
	{
		LOG4CXX_ERROR(logger, "�ļ���"<< fileName << "��������Ƶ��");
	}
	else if (*pFlvHeader->flags == 0x04)
	{
		LOG4CXX_ERROR(logger, "�ļ���"<< fileName << "ֻ������Ƶ��");
	}
	else
	{
		LOG4CXX_ERROR(logger, "�ļ���"<< fileName << "ֻ������Ƶ��");
	}

	PTAG pTag = new TAG;

	//��ȡPrevious Tag size
	fread((char*)pTag->preTagSize, 1, 4, file);

	//��ȡTag Header��Ϣ
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
			unsigned char *buffer = (unsigned char *)malloc(sizeof(unsigned char) * nLen);
			memset(buffer, 0, nLen);

			fread(buffer, 1, nLen, file);
			
			this->parserMetaData(buffer, nLen);
		}

	}
	else if(*pTagHeader->type == TAG_TYPE_VIDEO)
	{

	}
	else if (*pTagHeader->type == TAG_TYPE_AUDIO)
	{

	}

	fclose(file);
	return true;
}

bool CParserFormat::parserMetaData(const unsigned char *buffer, int nLen)
{
	unsigned char buff[32] = {0};
	int  nSize = 0;
	int  nPos  = 0;
	CString strForamt;
	const unsigned char *p = buffer;
	
	if (nLen <= 0)
	{
		return true;
	}
	switch(*p)
	{
		case Number:
			break;
		case Boolean:
			parserMetaData(buffer + nPos + 1,1);
			break;
		case String:				
			strForamt.Format("%02x%02x", *(p + 1), *(p + 2));
			sscanf_s(strForamt.GetBuffer(), "%x", &nPos);
			p = buffer + 3 + nPos;
			if (bFlag)
			{
				strForamt.Format("%02x%02x", *p, *(p + 1));
				sscanf_s(strForamt.GetBuffer(), "%x", &nPos);
				p = p + nPos + 3;
				parserMetaData(p, nLen - nPos - 3);
			}
			else
			{
				parserMetaData(p, nLen - nPos - 3);
			}
			
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
			//��ȡMetaData����Ԫ�ظ���
			strForamt.Format("%02x%02x%02x%02x", *(p + 1), *(p + 2),*(p + 3),*(p + 4));
			sscanf_s(strForamt.GetBuffer(), "%x", &nPos);
			p = buffer + 4;
			strForamt.Format("%02x%02x", *(p + 1), *(p + 2));
			sscanf_s(strForamt.GetBuffer(), "%x", &nPos);
			memset(buff, 0, 32);
			memcpy(buff, p + 3, nPos);
			p = p + nPos + 3;
			bFlag = true;
			parserMetaData(p, nLen - nPos - 3);
			break;
		case Object_end_marker:
			break;
		case Strict_array:
			break;
		case Date:
			break;
		case Long_string:
			break;
		default:
			break;
	}
	return true;
}