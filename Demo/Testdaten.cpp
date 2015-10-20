// Testdaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Testdaten.h"
#include "afxdialogex.h"
#include "Loeschwarnung.h"


// Testdaten-Dialogfeld

IMPLEMENT_DYNAMIC(Testdaten, CDialog)

Testdaten::Testdaten(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_TESTDATEN, pParent)
	, minimum(0)
	, maximum(0)
	, abweichung(0)
	, check_name(FALSE)
	, check_farben(FALSE)
	, check_werte(FALSE)
{

}

Testdaten::~Testdaten()
{
}

void Testdaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MIN, minimum);
	DDV_MinMaxInt(pDX, minimum, -50, 50);
	DDX_Text(pDX, IDC_EDIT_MAX, maximum);
	DDV_MinMaxInt(pDX, maximum, -50, 50);
	DDX_Text(pDX, IDC_EDIT_ABWEICHUNG, abweichung);
	DDV_MinMaxInt(pDX, abweichung, 0, 100);
	DDX_Check(pDX, IDC_CHECK_NAME, check_name);
	DDX_Check(pDX, IDC_CHECK_FARBEN, check_farben);
	DDX_Check(pDX, IDC_CHECK_WERTE, check_werte);
}


BEGIN_MESSAGE_MAP(Testdaten, CDialog)
	ON_BN_CLICKED(IDOK, &Testdaten::OnBnClickedOk)
END_MESSAGE_MAP()





void Testdaten::OnBnClickedOk()
{
	if (!UpdateData(TRUE))
		return;
	if (GetParentFrame()->GetActiveDocument()->IsModified())
	{
		Loeschwarnung lw;
		if (lw.DoModal() != IDOK)
			return;
	}
	CDialog::OnOK();
}
