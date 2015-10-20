#pragma once


// Name-Dialogfeld

class Name : public CDialog
{
	DECLARE_DYNAMIC(Name)

public:
	Name(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~Name();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CString datenname;
};
