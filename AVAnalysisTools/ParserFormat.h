#pragma once

#include "ItemMgr.h"
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>
using namespace log4cxx;
const int TAG_TYPE_AUDIO	= 0x08;
const int TAG_TYPE_VIDEO	= 0x09;
const int TAG_TYPE_SCRIPT	= 0x12;

enum script_type
{
	Number = 0,
	Boolean,
	String,
	Object,
	MovieClip,
	Null,
	Undefined,
	Reference,
	ECMA_ARRAY,
	Object_end_marker,
	Strict_array,
	Date,
	Long_string
};
class CParserFormat
{
private:
	CParserFormat(void);
	static CParserFormat* m_pInstance;
public:
	~CParserFormat(void);
	LoggerPtr logger;
	std::vector<char*>m_vecMeta;
	std::vector<PTAG>m_vecTag;
public:
	bool parserFlvFile(const char *fileName);
	bool parserMetaData(const unsigned char *buffer, int nLen);
	bool parserVideoTag(const unsigned char *buffer);
public:
	static CParserFormat* getInstance();
	int getString(const unsigned char *buff);
	int getBoolean(const unsigned char *buff);
	int getNumber(const unsigned char *buff);
	int getStrictArray(const unsigned char *buff);
};

