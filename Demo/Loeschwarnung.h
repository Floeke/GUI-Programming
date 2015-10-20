#pragma once


// Loeschwarnung-Dialogfeld

class Loeschwarnung : public CDialog
{
	DECLARE_DYNAMIC(Loeschwarnung)

public:
	Loeschwarnung(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Loeschwarnung();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOESCHWARNUNG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
};
