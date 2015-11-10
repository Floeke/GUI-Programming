#pragma once
#include "afxwin.h"


// EinReihe-Dialogfeld

class EinReihe : public CDialog
{
	DECLARE_DYNAMIC(EinReihe)

public:
	EinReihe(CWnd* pParent = NULL, int row_number = 1);   // Standardkonstruktor
	virtual ~EinReihe();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATENREIHE_BEARBEITEN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	int datenreihe;
	CString name;
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedSpeichern();
	afx_msg void OnBnClickedChange();
	CButton plus;
	CButton minus;
	virtual BOOL OnInitDialog();

private:
	void on_row_changed(int row);
};
