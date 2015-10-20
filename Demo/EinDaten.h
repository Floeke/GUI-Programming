#pragma once
#include "afxwin.h"


// EinDaten-Dialogfeld

class EinDaten : public CDialog
{
	DECLARE_DYNAMIC(EinDaten)

public:
	EinDaten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~EinDaten();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EINDATEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CComboBox combobox;
	int auswahl;
	int nummer;
	CScrollBar scrollbar;
	int wert;
	virtual BOOL OnInitDialog();

private:
	void scroll_to(int pos);
public:
	afx_msg void OnCbnSelchangeAuswahl();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedSpeichern();
	afx_msg void OnBnClickedLoeschen();
};
