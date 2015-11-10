#pragma once


// Tabelle-Dialogfeld

class Tabelle : public CDialog
{
	DECLARE_DYNAMIC(Tabelle)

public:
	Tabelle(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Tabelle();
	int colums;

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABELLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()

private:
	int actpos;
	int maxpos;
	CScrollBar sbar;
	CRect scrollrect;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};
