#pragma once


// Legende-Dialogfeld

class Legende : public CDialog
{
	DECLARE_DYNAMIC(Legende)

public:
	Legende(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Legende();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEGENDE };
#endif
private:
	void change_name();
	void change_reihe(int z, int name, int farbe);
	void change_wert(int z, int s);
	void change_all(int rnamen, int farben, int werte);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
