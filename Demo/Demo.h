
// Demo.h: Hauptheaderdatei für die Demo-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CDemoApp:
// Siehe Demo.cpp für die Implementierung dieser Klasse
//

class CDemoApp : public CWinApp
{
public:
	CDemoApp();


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDemoApp theApp;
