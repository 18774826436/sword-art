
// Sword  Art.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSwordArtApp:
// �йش����ʵ�֣������ Sword  Art.cpp
//

class CSwordArtApp : public CWinApp
{
public:
	CSwordArtApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSwordArtApp theApp;