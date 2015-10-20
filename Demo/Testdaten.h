#pragma once


// Testdaten-Dialogfeld

class Testdaten : public CDialog
{
	DECLARE_DYNAMIC(Testdaten)

public:
	Testdaten(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Testdaten();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TESTDATEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int minimum;
	int maximum;
	int abweichung;
	afx_msg void OnBnClickedOk();
	BOOL check_name;
	BOOL check_farben;
	BOOL check_werte;
};
