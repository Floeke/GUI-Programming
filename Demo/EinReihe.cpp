// EinReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "EinReihe.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"


// EinReihe-Dialogfeld

IMPLEMENT_DYNAMIC(EinReihe, CDialog)

EinReihe::EinReihe(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DATENREIHE_BEARBEITEN, pParent)
	, datenreihe(0)
	, name(_T(""))
{

}

EinReihe::~EinReihe()
{
}

void EinReihe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATENREIHE, datenreihe);
	DDX_Text(pDX, IDC_NAME, name);
	DDX_Control(pDX, IDC_PLUS, plus);
	DDX_Control(pDX, IDC_MINUS, minus);
}


BEGIN_MESSAGE_MAP(EinReihe, CDialog)
	ON_BN_CLICKED(IDC_PLUS, &EinReihe::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MINUS, &EinReihe::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_SPEICHERN, &EinReihe::OnBnClickedSpeichern)
	ON_BN_CLICKED(IDC_CHANGE, &EinReihe::OnBnClickedChange)
END_MESSAGE_MAP()


// EinReihe-Meldungshandler


void EinReihe::OnBnClickedPlus()
{
	on_row_changed(datenreihe+ 1);
}


void EinReihe::OnBnClickedMinus()
{
	on_row_changed(datenreihe -1 );
}


void EinReihe::OnBnClickedSpeichern()
{
	UpdateData(TRUE);
	DemoData.set_rname(datenreihe -1, name);
}


void EinReihe::OnBnClickedChange()
{
	CColorDialog cd(DemoData.get_farbe(datenreihe-1));

	if (cd.DoModal() == IDOK)
	{
		DemoData.set_farbe(datenreihe - 1, cd.GetColor());
		stdbrush.setall();
		stdpen.setall();
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}
}


BOOL EinReihe::OnInitDialog()
{
	CDialog::OnInitDialog();

	datenreihe = 1;
	name = DemoData.get_rname(datenreihe-1);
	minus.EnableWindow(FALSE);


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}


void EinReihe::on_row_changed(int row)
{
	UpdateData(TRUE);
	plus.EnableWindow(TRUE);
	minus.EnableWindow(TRUE);
	if (row +1 > DemoData.get_anz_z())
	{
		datenreihe = DemoData.get_anz_z();
		name = DemoData.get_rname(datenreihe - 1);
	}
	else if (row < 0)
	{
		datenreihe = 1;
		name = DemoData.get_rname(datenreihe - 1);
	}
	else {
		datenreihe = row;
		name = DemoData.get_rname(datenreihe - 1);
	}

	UpdateData(FALSE);

	if (datenreihe == DemoData.get_anz_z())
	{
		plus.EnableWindow(FALSE);
		return;
	}

	if (datenreihe == 1)
	{
		minus.EnableWindow(FALSE);
		return;
	}
}
