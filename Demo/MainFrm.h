
// MainFrm.h: Schnittstelle der Klasse CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // Nur aus Serialisierung erstellen
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attribute
public:

// Vorgänge
public:

// Überschreibungen
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementierung
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // Eingebettete Member der Steuerleiste
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CDialogBar		  dialogbar_ein;

// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEingabeName();
	afx_msg void OnUpdateEingabeName(CCmdUI *pCmdUI);
	afx_msg void OnEingabeDatenreihe();
	afx_msg void OnUpdateEingabeDatenreihe(CCmdUI *pCmdUI);
	afx_msg void OnEingabeDaten();
	afx_msg void OnUpdateEingabeDaten(CCmdUI *pCmdUI);
	afx_msg void OnEingabeTestdatren();
	afx_msg void OnUpdateEingabeTestdatren(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeDatenreihe();
	afx_msg void OnUpdateAusgabeDatenreihe(CCmdUI *pCmdUI);
	afx_msg void OnAnsichtEingabeleiste();
	afx_msg void OnUpdateAnsichtEingabeleiste(CCmdUI *pCmdUI);
	afx_msg void OnFileNew();
	afx_msg void OnUpdateFileNew(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeLegende();
	afx_msg void OnUpdateAusgabeLegende(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeDaten();
	afx_msg void OnUpdateAusgabeDaten(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeGrafik();
	afx_msg void OnUpdateAusgabeGrafik(CCmdUI *pCmdUI);
	afx_msg void OnAusgabeAnimation();
	afx_msg void OnUpdateAusgabeAnimation(CCmdUI *pCmdUI);
	afx_msg void OnAnsichtSymbolleiste();
	afx_msg void OnUpdateAnsichtSymbolleiste(CCmdUI *pCmdUI);
	afx_msg void OnAnsichtStatusleiste();
	afx_msg void OnUpdateAnsichtStatusleiste(CCmdUI *pCmdUI);
	afx_msg void OnAnsichtAusgabeleiste();
	afx_msg void OnUpdateAnsichtAusgabeleiste(CCmdUI *pCmdUI);
	afx_msg void OnAnsichtHintergrund();
	afx_msg void OnUpdateAnsichtHintergrund(CCmdUI *pCmdUI);
};


