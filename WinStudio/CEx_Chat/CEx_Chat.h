
// CEx_Chat.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCEx_ChatApp:
// �йش����ʵ�֣������ CEx_Chat.cpp
//

class CCEx_ChatApp : public CWinApp
{
public:
	CCEx_ChatApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCEx_ChatApp theApp;