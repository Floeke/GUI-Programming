
// Demo.h: Hauptheaderdatei f�r die Demo-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"       // Hauptsymbole


// CDemoApp:
// Siehe Demo.cpp f�r die Implementierung dieser Klasse
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp();


// �berschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDemoApp theApp;
