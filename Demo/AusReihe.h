#pragma once
#include "afxwin.h"


// AusReihe-Dialogfeld

class AusReihe : public CDialog
{
	DECLARE_DYNAMIC(AusReihe)

public:
	AusReihe(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~AusReihe();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUSREIHE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int m_darstellung;
	CComboBox m_reihe;
	int m_selection;
	BOOL m_xraster;
	BOOL m_yraster;
	afx_msg void OnClose();
};
