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
	int selX;
	int selY;
	CScrollBar sbar;
	CRect scrollrect;
	void change_name();
	void change_reihe(int z, int name, int farbe);
	void change_wert(int z, int s);
	void change_all(int rnamen, int farben, int werte);
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
