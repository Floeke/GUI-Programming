#pragma once
#include "Daten.h"



// Grafik-Dialogfeld

class Grafik : public CDialog
{
	DECLARE_DYNAMIC(Grafik)

public:
	Grafik(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Grafik();
	int isSelected(int row);

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAFIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	void onAnzeigen();
	void onGlMinus();
	void onGlPlus();

	DECLARE_MESSAGE_MAP()

private:
	CButton anzeigen;
	CButton glgroup;
	CButton glplus;
	CButton glminus;
	CButton vbgroup;
	CEdit von;
	CEdit bis;
	CListBox auswahl;
	CRect drawable;
	int von_value;
	int bis_value;
	int highlighted[MAX_ZEILEN];
	CSize drawable_height;
	CSize value_height;
	CSize drawable_width;
	CSize value_width;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
