
// CEx_BMP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCEx_BMPApp:
// �йش����ʵ�֣������ CEx_BMP.cpp
//

class CCEx_BMPApp : public CWinApp
{
public:
	CCEx_BMPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCEx_BMPApp theApp;