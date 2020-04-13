
// ClipboardDemo.h : main header file for the ClipboardDemo application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CClipboardDemoApp:
// See ClipboardDemo.cpp for the implementation of this class
//

class CClipboardDemoApp : public CWinApp
{
public:
	CClipboardDemoApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CClipboardDemoApp theApp;
