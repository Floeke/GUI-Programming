#pragma once



// Grafik-Dialogfeld

class Grafik : public CDialog
{
	DECLARE_DYNAMIC(Grafik)

public:
	Grafik(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Grafik();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAFIK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

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
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
