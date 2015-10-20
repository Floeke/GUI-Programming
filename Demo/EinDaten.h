#pragma once


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
};
