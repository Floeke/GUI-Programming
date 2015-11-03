#pragma once


// NeuerWert-Dialogfeld

class NeuerWert : public CDialog
{
	DECLARE_DYNAMIC(NeuerWert)

public:
	NeuerWert(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~NeuerWert();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEUER_WERT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int new_value;
	virtual BOOL OnInitDialog();
};
