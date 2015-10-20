// EinDaten.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "EinDaten.h"
#include "afxdialogex.h"
#include "Daten.h"


// EinDaten-Dialogfeld

IMPLEMENT_DYNAMIC(EinDaten, CDialog)

EinDaten::EinDaten(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EINDATEN, pParent)
	, auswahl(0)
	, nummer(0)
	, wert(0)
{

}

EinDaten::~EinDaten()
{
}

void EinDaten::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AUSWAHL, combobox);
	DDX_CBIndex(pDX, IDC_AUSWAHL, auswahl);
	DDX_Text(pDX, IDC_NUMMER, nummer);
	DDX_Control(pDX, IDC_SCROLL, scrollbar);
	DDX_Text(pDX, IDC_WERT, wert);
}


BEGIN_MESSAGE_MAP(EinDaten, CDialog)
	ON_CBN_SELCHANGE(IDC_AUSWAHL, &EinDaten::OnCbnSelchangeAuswahl)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SPEICHERN, &EinDaten::OnBnClickedSpeichern)
	ON_BN_CLICKED(IDC_LOESCHEN, &EinDaten::OnBnClickedLoeschen)
END_MESSAGE_MAP()


// EinDaten-Meldungshandler


BOOL EinDaten::OnInitDialog()
{
	CDialog::OnInitDialog();

	for (int i = 0; i < DemoData.get_anz_z(); i++)
		combobox.InsertString(i, DemoData.get_rname(i));

	auswahl = 0;
	
	scrollbar.SetScrollRange(1, DemoData.get_anz_s());
	scroll_to(1);

	UpdateData(FALSE); //Wir aktualisieren aus der Bildschirmdarstellung unsere Membervariablen

	GotoDlgCtrl(GetDlgItem(IDC_WERT)); //Input-Fokus wird auf das Eingabefeld (selektiertes Editierfeld)

	return TRUE;  // return TRUE unless you set the focus to a control
				  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void EinDaten::scroll_to(int pos)
{
	if (pos > DemoData.get_anz_s()) 
		pos = DemoData.get_anz_s();
	if (pos < 1)
		pos = 1;
	nummer = pos; //Nummer = Sicht des Nutzers. Nummer-1 = interne Ansicht

	scrollbar.SetScrollPos(nummer);
	wert = DemoData.get_wert(auswahl, nummer - 1);

	UpdateData(FALSE);
}


void EinDaten::OnCbnSelchangeAuswahl()
{
	UpdateData(TRUE); //Daten im Dialog werden aktualisert
	wert = DemoData.get_wert(auswahl, nummer - 1);
	UpdateData(FALSE); //Update der Nutzeroberfläche
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
}


//nSBCode = gedrückte 'Buttons' der Scrollbar (Dreieck rechts/links, etc.), pScrollBar = Zeiger auf den Scrollbar
void EinDaten::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);
	if (pScrollBar == &scrollbar)
	{
		switch (nSBCode)
		{
		case SB_LEFT: //Ganz links
			scroll_to(1);
			break;
		case SB_RIGHT: //Ganz rechts
			scroll_to(DemoData.get_anz_s());
			break;
		case SB_LINELEFT: //Dreieck links
			scroll_to(nummer - 1);
			break;
		case SB_LINERIGHT: //Dreieck rechts
			scroll_to(nummer + 1);
			break;
		case SB_PAGELEFT: //Zwischenfeld links
			scroll_to(nummer - 5);
			break;
		case SB_PAGERIGHT: //Zwischenfeld rechts
			scroll_to(nummer + 5);
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK: //Positionsänderung
			scroll_to(nPos);
			break;
		case SB_ENDSCROLL:
			break;

		}

		GotoDlgCtrl(GetDlgItem(IDC_WERT));
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void EinDaten::OnBnClickedSpeichern()
{
	UpdateData(TRUE);
	if (DemoData.get_wert(auswahl, nummer - 1) != wert)
	{
		DemoData.set_wert(auswahl, nummer - 1, wert);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}

	scroll_to(nummer + 1);
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
}


void EinDaten::OnBnClickedLoeschen()
{
	UpdateData(TRUE);
	if (DemoData.get_wert(auswahl, nummer - 1) != 0)
	{
		DemoData.set_wert(auswahl, nummer - 1, 0);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}

	scroll_to(nummer + 1);
	GotoDlgCtrl(GetDlgItem(IDC_WERT));
}
