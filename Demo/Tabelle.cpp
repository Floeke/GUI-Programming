// Tabelle.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Tabelle.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"



static const int feldhoehe = 16;
static const int feldbreite = 40;
static const int namenbreite = 70;
static const int abstand = 4;
static const int maxcolums = 10;
static const int scrollbarhoehe = 16;

// Tabelle-Dialogfeld

IMPLEMENT_DYNAMIC(Tabelle, CDialog)

Tabelle::Tabelle(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TABELLE, pParent)
{
	int hoehe, breite;
	int as, az;
	CRect r;
	CRect sbr;

	Create(IDD_TABELLE, pParent);

	as = DemoData.get_anz_s();
	az = DemoData.get_anz_z();

	colums = as > maxcolums ? maxcolums : as;

	hoehe = 3 * abstand + (az + 1)*feldhoehe;
	breite = 3 * abstand + namenbreite + colums*feldbreite;

	scrollrect.SetRect(2 * abstand + namenbreite + 1, abstand + 1, breite - abstand - 1, hoehe - abstand - 1);

	maxpos = (as - maxcolums) * feldbreite;
	actpos = 0;

	if (colums < as)
	{
		hoehe += abstand + scrollbarhoehe;
		sbr.SetRect(2 * abstand + namenbreite, hoehe - abstand - scrollbarhoehe, breite - abstand, hoehe - abstand);
		sbar.Create(WS_CHILD | WS_VISIBLE | SBS_HORZ, sbr, this, 1);
		sbar.SetScrollRange(0, maxpos);
		sbar.SetScrollPos(actpos);
	}

	r.SetRect(0, 0, breite, hoehe);
	r.OffsetRect(100, 100);
	CalcWindowRect(&r, 0);

	SetWindowText(CString("Tabelle: ") + DemoData.get_name());
	MoveWindow(&r, TRUE);
	ShowWindow(SW_SHOW);
	
}

Tabelle::~Tabelle()
{
}

void Tabelle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Tabelle, CDialog)
	ON_WM_HSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Tabelle-Meldungshandler





void Tabelle::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int newpos = actpos;

	if (pScrollBar == &sbar)
	{
		switch (nSBCode)
		{
		case SB_LEFT: newpos = 0; break;
		case SB_ENDSCROLL: break;
		case SB_LINELEFT: newpos -= 8; break;
		case SB_LINERIGHT: newpos += 8;	break;
		case SB_PAGELEFT: newpos -= feldbreite; break;
		case SB_PAGERIGHT: newpos += feldbreite; break;
		case SB_RIGHT: newpos = maxpos;	break;
		case SB_THUMBPOSITION: break;
		case SB_THUMBTRACK: newpos = nPos; break;
		}

		if (newpos < 0) newpos = 0;
		if (newpos > maxpos) newpos = maxpos;

		if (newpos != actpos)
		{
			sbar.SetScrollPos(newpos);
			ScrollWindow(actpos - newpos, 0, scrollrect, scrollrect);
			actpos = newpos;
			UpdateWindow();
		}
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Tabelle::OnPaint()
{

	CPaintDC dc(this); // device context for painting
	int a;
	dc.FrameRect(scrollrect, &stdbrush.black);
	for (a = 0; a <= scrollrect.Width(); a += 8)
	{
		dc.MoveTo(scrollrect.left + a, scrollrect.top);
		dc.LineTo(scrollrect.right - a, scrollrect.bottom);
	}
	for (a = 0; a <= scrollrect.Height(); a += 8)
	{
		dc.MoveTo(scrollrect.left, scrollrect.top + a);
		dc.LineTo(scrollrect.right, scrollrect.bottom - a);
	}
}
