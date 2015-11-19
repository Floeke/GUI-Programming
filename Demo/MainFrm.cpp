
// MainFrm.cpp: Implementierung der Klasse CMainFrame
//

#include "stdafx.h"
#include "Demo.h"
#include "Daten.h"
#include "MainFrm.h"
#include "DatenNeu.h"
#include "Name.h"
#include "Testdaten.h"
#include "EinDaten.h"
#include "EinReihe.h"
#include "AusReihe.h"
#include "draw.h"
#include "Legende.h"
#include "Tabelle.h"
#include "Grafik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_EINGABE_NAME, &CMainFrame::OnEingabeName)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_NAME, &CMainFrame::OnUpdateEingabeName)
	ON_COMMAND(ID_EINGABE_DATENREIHE, &CMainFrame::OnEingabeDatenreihe)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_DATENREIHE, &CMainFrame::OnUpdateEingabeDatenreihe)
	ON_COMMAND(ID_EINGABE_DATEN, &CMainFrame::OnEingabeDaten)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_DATEN, &CMainFrame::OnUpdateEingabeDaten)
	ON_COMMAND(ID_EINGABE_TESTDATREN, &CMainFrame::OnEingabeTestdatren)
	ON_UPDATE_COMMAND_UI(ID_EINGABE_TESTDATREN, &CMainFrame::OnUpdateEingabeTestdatren)
	ON_COMMAND(ID_AUSGABE_DATENREIHE, &CMainFrame::OnAusgabeDatenreihe)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_DATENREIHE, &CMainFrame::OnUpdateAusgabeDatenreihe)
	ON_COMMAND(ID_ANSICHT_EINGABELEISTE, &CMainFrame::OnAnsichtEingabeleiste)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_EINGABELEISTE, &CMainFrame::OnUpdateAnsichtEingabeleiste)
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, &CMainFrame::OnUpdateFileNew)
	ON_COMMAND(ID_AUSGABE_LEGENDE, &CMainFrame::OnAusgabeLegende)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_LEGENDE, &CMainFrame::OnUpdateAusgabeLegende)
	ON_COMMAND(ID_AUSGABE_DATEN, &CMainFrame::OnAusgabeDaten)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_DATEN, &CMainFrame::OnUpdateAusgabeDaten)
	ON_COMMAND(ID_AUSGABE_GRAFIK, &CMainFrame::OnAusgabeGrafik)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_GRAFIK, &CMainFrame::OnUpdateAusgabeGrafik)
	ON_COMMAND(ID_AUSGABE_ANIMATION, &CMainFrame::OnAusgabeAnimation)
	ON_UPDATE_COMMAND_UI(ID_AUSGABE_ANIMATION, &CMainFrame::OnUpdateAusgabeAnimation)
	ON_COMMAND(ID_ANSICHT_SYMBOLLEISTE, &CMainFrame::OnAnsichtSymbolleiste)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_SYMBOLLEISTE, &CMainFrame::OnUpdateAnsichtSymbolleiste)
	ON_COMMAND(ID_ANSICHT_STATUSLEISTE, &CMainFrame::OnAnsichtStatusleiste)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_STATUSLEISTE, &CMainFrame::OnUpdateAnsichtStatusleiste)
	ON_COMMAND(ID_ANSICHT_AUSGABELEISTE, &CMainFrame::OnAnsichtAusgabeleiste)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_AUSGABELEISTE, &CMainFrame::OnUpdateAnsichtAusgabeleiste)
	ON_COMMAND(ID_ANSICHT_HINTERGRUND, &CMainFrame::OnAnsichtHintergrund)
	ON_UPDATE_COMMAND_UI(ID_ANSICHT_HINTERGRUND, &CMainFrame::OnUpdateAnsichtHintergrund)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame-Erstellung/Zerstörung

CMainFrame::CMainFrame()
{
	// TODO: Hier Code für die Memberinitialisierung einfügen
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Fehler beim Erstellen der Symbolleiste.\n");
		return -1;      // Fehler beim Erstellen
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Fehler beim Erstellen der Statusleiste.\n");
		return -1;      // Fehler beim Erstellen
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Löschen Sie diese drei Zeilen, wenn Sie nicht möchten, dass die Systemleiste andockbar ist
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	dialogbar_ein.Create(this, IDD_DIALOGBAR_EIN, CBRS_BOTTOM, AFX_IDW_CONTROLBAR_FIRST + 50);
	dialogbar_ein.EnableDocking(CBRS_ALIGN_ANY);
	dialogbar_ein.SetWindowTextW( CString("Eingaben"));
	DockControlBar(&dialogbar_ein, AFX_IDW_DOCKBAR_BOTTOM);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Ändern Sie hier die Fensterklasse oder die Darstellung, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return TRUE;
}

// CMainFrame-Diagnose

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame-Meldungshandler

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}



void CMainFrame::OnEingabeName()
{
	Name n;
	if (n.DoModal() == IDOK)
	{
		DemoData.set_name(n.datenname);
	}
}


void CMainFrame::OnUpdateEingabeName(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeDatenreihe()
{
	EinReihe er;
	er.DoModal();
}


void CMainFrame::OnUpdateEingabeDatenreihe(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeDaten()
{
	EinDaten ed;
	ed.DoModal();
}


void CMainFrame::OnUpdateEingabeDaten(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnEingabeTestdatren()
{
	Testdaten td;
	if (td.DoModal() == IDOK)
	{
		DemoData.testdaten(td.minimum, td.maximum, td.abweichung, td.check_name, td.check_farben, td.check_werte);
		if (td.check_farben)
		{
			stdbrush.setall();
			stdpen.setall();
		}
	}
}


void CMainFrame::OnUpdateEingabeTestdatren(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAusgabeDatenreihe()
{
	new AusReihe; //nicht modaler Aufruf. Klasse selbst greift auf close-Methode zurück
}


void CMainFrame::OnUpdateAusgabeDatenreihe(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(DemoData.get_anz_z());
}


void CMainFrame::OnAnsichtEingabeleiste()
{
	ShowControlBar(&dialogbar_ein, !dialogbar_ein.IsWindowVisible(), TRUE);
}


void CMainFrame::OnUpdateAnsichtEingabeleiste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(dialogbar_ein.IsWindowVisible());
}


void CMainFrame::OnFileNew()
{
	DatenNeu dn;
	dn.datenname = DemoData.get_name();
	dn.anzahl_z = DemoData.get_anz_z();
	dn.anzahl_2 = DemoData.get_anz_s();

	if (dn.DoModal() == IDOK)
	{
		DemoData.init(dn.anzahl_z, dn.anzahl_2, dn.datenname);
		stdbrush.setall();
		stdpen.setall();
		GetActiveDocument()->SetModifiedFlag();
	}
}


void CMainFrame::OnUpdateFileNew(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAusgabeLegende()
{
	new Legende;
}


void CMainFrame::OnUpdateAusgabeLegende(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAusgabeDaten()
{
	new Tabelle;
}


void CMainFrame::OnUpdateAusgabeDaten(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAusgabeGrafik()
{
	new Grafik();
}


void CMainFrame::OnUpdateAusgabeGrafik(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAusgabeAnimation()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CMainFrame::OnUpdateAusgabeAnimation(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAnsichtSymbolleiste()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CMainFrame::OnUpdateAnsichtSymbolleiste(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAnsichtStatusleiste()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CMainFrame::OnUpdateAnsichtStatusleiste(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAnsichtAusgabeleiste()
{
	// TODO: Fügen Sie hier Ihren Befehlsbehandlungscode ein.
}


void CMainFrame::OnUpdateAnsichtAusgabeleiste(CCmdUI *pCmdUI)
{
	// TODO: Fügen Sie hier Ihren Befehlsaktualisierungs-UI-Behandlungscode ein.
}


void CMainFrame::OnAnsichtHintergrund()
{
	DemoData.set_display(!DemoData.get_display());
}


void CMainFrame::OnUpdateAnsichtHintergrund(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(DemoData.get_display());
}
