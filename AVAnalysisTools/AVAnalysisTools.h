
// AVAnalysisTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAVAnalysisToolsApp:
// �йش����ʵ�֣������ AVAnalysisTools.cpp
//

class CAVAnalysisToolsApp : public CWinApp
{
public:
	CAVAnalysisToolsApp();
	ULONG_PTR m_gdiplusToken;
// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAVAnalysisToolsApp theApp;