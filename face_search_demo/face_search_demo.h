
// face_search_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cface_search_demoApp: 
// �йش����ʵ�֣������ face_search_demo.cpp
//

class Cface_search_demoApp : public CWinApp
{
public:
	Cface_search_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cface_search_demoApp theApp;