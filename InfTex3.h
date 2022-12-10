
// InfTex3.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CInfTex3App:
// Сведения о реализации этого класса: InfTex3.cpp
//

class CInfTex3App : public CWinApp
{
public:
	CInfTex3App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CInfTex3App theApp;
