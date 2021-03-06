#pragma once
#include "afxwin.h"
#include "Daten.h"
#define ABSTAND_RAND 20
#define ABSTAND_RAND_OBEN 15
#define POINT_SIZE 4
#define ANZ_HORIZONTAL_LINES 16


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

private:
	char infoflag[MAX_SPALTEN];
	void change_name();
	void change_reihe(int z, int name, int farbe);
	void change_wert(int z, int s);
	void change_all(int rnamen, int farben, int werte);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
