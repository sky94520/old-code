
// Ex_SDI1.h : Ex_SDI1 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CEx_SDI1App:
// �йش����ʵ�֣������ Ex_SDI1.cpp
//

class CEx_SDI1App : public CWinAppEx
{
public:
	CEx_SDI1App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEx_SDI1App theApp;
