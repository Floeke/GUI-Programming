#pragma once
#include "afxwin.h"
#define ABSTAND_RAND 15
#define ABSTAND_RAND_OBEN 15


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
	afx_msg void OnCbnSelchangeReihe();
	CRect rahmen;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedLinien();
	afx_msg void OnBnClickedSaeulen();
	afx_msg void OnBnClickedXraster();
	afx_msg void OnBnClickedYraster();
};
