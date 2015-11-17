// Tabelle.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Tabelle.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"
#include "NeuerWert.h"



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
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	/*ON_COMMAND(POPUP_COMMAND_BASE, popup0)
	ON_COMMAND(POPUP_COMMAND_BASE + 1, popup1)
	ON_COMMAND(POPUP_COMMAND_BASE + 2, popup2)
	ON_COMMAND(POPUP_COMMAND_BASE + 3, popup3)
	ON_COMMAND(POPUP_COMMAND_BASE + 4, popup4)
	ON_COMMAND(POPUP_COMMAND_BASE + 5, popup5)
	ON_COMMAND(POPUP_COMMAND_BASE + 6, popup6)*/
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
	CRect update;
	COLORREF oldColor = dc.GetTextColor();

	CRect temp;
	dc.SetBkMode(TRANSPARENT);
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		int left = abstand;
		int top = 2 * abstand + feldhoehe + (index*feldhoehe);
		int right = abstand + namenbreite;
		int bottom = top + feldhoehe;
		temp = CRect(left, top, right, bottom + 1);
		dc.Rectangle(temp);
		dc.DrawText(DemoData.get_rname(index), temp, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	dc.IntersectClipRect(scrollrect);
	dc.GetClipBox(update); //Rect to be repainted


	for (int index = 0; index < DemoData.get_anz_s(); index++)
	{
		CRect field;
		field.SetRect(0, 0, feldbreite, feldhoehe + 1);


		//field.OffsetRect(feldbreite*index + 2 * abstand + namenbreite + 1, abstand + 1); <- Scrolling didn't work with that
		field.OffsetRect(feldbreite*index + 2 * abstand + namenbreite - actpos - index + 1, abstand + 1);
		if (update.IntersectRect(&scrollrect, &update))
		{
			CString text;
			text.Format(CString("%d"), index);
			dc.Rectangle(field);
			dc.DrawText(text, field, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			field.OffsetRect(0, abstand);
			for (int jndex = 0; jndex < DemoData.get_anz_z(); jndex++)
			{
				field.OffsetRect(0, feldhoehe);
				dc.Rectangle(field);

				if (selX == index && selY == jndex)
				{
					dc.FillRect(field, &stdbrush.gray);
				}

				text.Format(CString("%d"), DemoData.get_wert(jndex, index));
				if (DemoData.get_wert(jndex, index) < 0)
				{
					dc.SetTextColor(RGB(255, 0, 0));
					dc.DrawText(text, field, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					dc.SetTextColor(oldColor);
				}
				else
				{
					dc.DrawText(text, field, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

			}

		}
	}


	/*int a;
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
	}*/
}


void Tabelle::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Calculate the field that was clicked
	CPoint pRel = point - scrollrect.TopLeft();
	pRel.x += actpos;
	pRel.y -= (feldhoehe + 2*abstand + 1);
	int x, y;
	y = pRel.y / (feldhoehe - 1);
	x = pRel.x / (feldbreite - 1);

	if (x + 1 > DemoData.get_anz_s() || x < 0 || y + 1 > DemoData.get_anz_z() || y < 0)
	{
		CDialog::OnLButtonDblClk(nFlags, point);
		return;
	}

	selX = x;
	selY = y;
	RedrawWindow();

	NeuerWert ein;
	ein.new_value = DemoData.get_wert(y, x);
	if (ein.DoModal() == IDOK)
	{
		DemoData.set_wert(y, x, ein.new_value);
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
	}

	selX = -1;
	selY = -1;
	RedrawWindow();
	CDialog::OnLButtonDblClk(nFlags, point);
}


void Tabelle::OnRButtonDown(UINT nFlags, CPoint point)
{
	//Calculate the field that was clicked
	CPoint pRel = point - scrollrect.TopLeft();
	pRel.x += actpos;
	pRel.y -= (feldhoehe + 2 * abstand + 1);
	int x, y;
	y = pRel.y / (feldhoehe - 1);
	x = pRel.x / (feldbreite - 1);

	if (x + 1 > DemoData.get_anz_s() || x < 0 || y + 1 > DemoData.get_anz_z() || y < 0)
	{
		CDialog::OnRButtonDown(nFlags, point);
		return;
	}
	selX = x;
	selY = y;
	RedrawWindow();
	int value = DemoData.get_wert(y, x);
	
	CMenu popup;
	popup.CreatePopupMenu();
	CString text;
	CRect r;
	GetWindowRect(&r);
	
	for (int index = 0; index < 7; index++)
	{
		text.Format(CString("%d"), value + index - 3);
		popup.InsertMenu(index, MF_BYPOSITION | MF_STRING, POPUP_COMMAND_BASE + index, text);
	}
	popup.TrackPopupMenu(TPM_RIGHTALIGN | TPM_LEFTBUTTON, r.left + point.x, r.top + point.y, this);	

	CDialog::OnRButtonDown(nFlags, point);
}


BOOL Tabelle::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (POPUP_COMMAND_BASE <= wParam && POPUP_COMMAND_BASE + 7 > wParam)
	{
		int new_value = DemoData.get_wert(selY, selX);
		new_value += wParam - POPUP_COMMAND_BASE - 3;
		DemoData.set_wert(selY, selX, new_value);
		selY = -1;
		selX = -1;
		GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
		RedrawWindow();
		return 1;
	}

	return CDialog::OnCommand(wParam, lParam);
}
