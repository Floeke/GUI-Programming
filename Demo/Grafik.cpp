// Grafik.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Grafik.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "dialogfont.h"
#include "draw.h"
#include "EinDaten.h"
#include "usermsg.h"


#define ANZEIGEN 1
#define GLGROUP 2
#define GLPLUS 3
#define GLMINUS 4
#define VBGROUP 5
#define VON 6
#define BIS 7
#define AUSWAHL 8 


static const int controlbreite = 72;
static const int offset1 = 22;
static const int hoehe1 = 20;
static const int offset2 = 66;
static const int hoehe2 = 40;
static const int offset3 = 50;
static const int hoehe3 = 20;
static const int offset4 = 110;
static const int hoehe4 = 40;
static const int offset5 = 94;
static const int hoehe5 = 20;
static const int offset6 = 114;
static const int minb = 400;
static const int minh = 200;
static const int padding = 5;



int scale_point(int z, CSize xy, CSize uv)
{
	int scaled_z;
	if ((xy.cy - xy.cx) == 0)
	{
		scaled_z = ((z - xy.cx)*(uv.cy - uv.cx)) + uv.cx;
	}
	else
	{
		scaled_z = ((z - xy.cx)*(uv.cy - uv.cx)) / (xy.cy - xy.cx) + uv.cx;
	}

	return scaled_z;
}


// Grafik-Dialogfeld

IMPLEMENT_DYNAMIC(Grafik, CDialog)

Grafik::Grafik(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GRAFIK, pParent)
{
	CRect r;
	Create(IDD_GRAFIK, pParent);
	r.SetRect(0, 0, minb * 3 / 2, minh * 3 / 2);
	r.OffsetRect(100, 100);
	CalcWindowRect(&r, 0);
	SetWindowText(CString("Grafik: ") + DemoData.get_name());
	MoveWindow(&r, TRUE);
	ShowWindow(SW_SHOW);
}

Grafik::~Grafik()
{
}

void Grafik::DoDataExchange(CDataExchange* pDX)
{
	DDX_Text(pDX, VON, von_value);
	DDX_Text(pDX, BIS, bis_value);
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Grafik, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(ANZEIGEN, onAnzeigen)
	ON_BN_CLICKED(GLPLUS, onGlPlus)
	ON_BN_CLICKED(GLMINUS, onGlMinus)
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Grafik-Meldungshandler


int Grafik::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CString txt;
	CRect r;
	int i;
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	anzeigen.Create(CString("Anzeigen"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, r, this, ANZEIGEN);
	anzeigen.SetFont(&dfnt.bold);
	glgroup.Create(CString("Glättung 0"), BS_GROUPBOX | WS_VISIBLE | WS_CHILD, r, this, GLGROUP);
	glgroup.SetFont(&dfnt.norm);
	glplus.Create(CString("+"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,	r, this, GLPLUS);
	glplus.SetFont(&dfnt.bold);
	glminus.Create(CString("-"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD,	r, this, GLMINUS);
	glminus.SetFont(&dfnt.bold);
	glminus.EnableWindow(FALSE);

	vbgroup.Create(CString("von bis"), BS_GROUPBOX | WS_VISIBLE | WS_CHILD,	r, this, VBGROUP);
	vbgroup.SetFont(&dfnt.norm);
	von.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, r, this, VON);
	von.SetFont(&dfnt.bold);
	txt.Format(CString("%d"), 1);
	von.SetWindowText(txt);
	bis.Create(WS_VISIBLE | WS_CHILD | WS_BORDER, r, this, BIS);
	bis.SetFont(&dfnt.bold);
	txt.Format(CString("%d"), DemoData.get_anz_s());
	bis.SetWindowText(txt);
	auswahl.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |	LBS_EXTENDEDSEL | LBS_NOINTEGRALHEIGHT | LBS_DISABLENOSCROLL, r, this, AUSWAHL);
	auswahl.SetFont(&dfnt.bold);
	for (i = 0; i < DemoData.get_anz_z(); i++)
		auswahl.InsertString(i, DemoData.get_rname(i));

	von_value = 0;
	bis_value = DemoData.get_anz_s();
	for (int i = 0; i < MAX_ZEILEN; i++)
		highlighted[i] = 0;
	return 0;

}


void Grafik::OnSize(UINT nType, int cx, int cy)
{
	//cx, cy is the bottom-right corner
	CDialog::OnSize(nType, cx, cy);
	int left_control_border = cx - controlbreite;

	anzeigen.MoveWindow(left_control_border, cy - offset1, controlbreite, hoehe1, FALSE);
	glgroup.MoveWindow(left_control_border, cy - offset2, controlbreite, hoehe2, FALSE);
	glplus.MoveWindow(left_control_border + 2, cy - offset3, (controlbreite - 2) / 2, hoehe3, FALSE);
	glminus.MoveWindow(left_control_border + (controlbreite - 2) / 2 + 2, cy - offset3, (controlbreite - 2) / 2, hoehe3, FALSE);
	vbgroup.MoveWindow(left_control_border, cy - offset4, controlbreite, hoehe4, FALSE);
	von.MoveWindow(left_control_border + 2, cy - offset5, (controlbreite - 2) / 2, hoehe5, FALSE);
	bis.MoveWindow(left_control_border + (controlbreite - 2) / 2 + 2, cy - offset5, (controlbreite - 2) / 2, hoehe5, FALSE);
	auswahl.MoveWindow(left_control_border, 0, controlbreite, cy - offset6, FALSE);
	Invalidate();

	drawable = CRect(padding, padding, cx - controlbreite, cy - padding);

}


void Grafik::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = minb;
	lpMMI->ptMinTrackSize.y = minh;

}

void Grafik::onAnzeigen()
{

	UpdateData(TRUE);
	Invalidate();
}

void Grafik::onGlMinus()
{

}

void Grafik::onGlPlus()
{

}




void Grafik::OnClose()
{
	DestroyWindow();
	delete this;
}


void Grafik::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!PtInRect(&drawable, point)) return;

	int x_hit = scale_point(point.x, drawable_width, value_width);
	int y_hit = scale_point(point.y, drawable_height, value_height);

	for (int row = 0; row < DemoData.get_anz_z(); row++)
	{
		if (!isSelected(row)) continue;
		for (int column = von_value; column < bis_value; column++)
		{
			int x = scale_point(column, value_width, drawable_width);
			int y = scale_point(DemoData.get_wert(row, column), value_height, drawable_height);
			CRect hit;
			hit.SetRect(x - 2 * 5, y - 2 * 5, x + 2 * 5, y + 2 * 5);

			if (PtInRect(&hit, point))  //CPoint(x, y)))
			{
				highlighted[row] = !highlighted[row];
			}
		}
	}

	RedrawWindow();
	CDialog::OnLButtonDown(nFlags, point);
}


void Grafik::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!PtInRect(&drawable, point)) return;

	int x_hit = scale_point(point.x, drawable_width, value_width);
	int y_hit = scale_point(point.y, drawable_height, value_height);

	for (int row = 0; row < DemoData.get_anz_z(); row++)
	{
		if (!isSelected(row)) continue;
		for (int column = von_value; column < bis_value; column++)
		{
			int x = scale_point(column, value_width, drawable_width);
			int y = scale_point(DemoData.get_wert(row, column), value_height, drawable_height);
			CRect hit;
			hit.SetRect(x - 2 * 5, y - 2 * 5, x + 2 * 5, y + 2 * 5);

			if (PtInRect(&hit, point))  //CPoint(x, y)))
			{
				//Auswahl -> Datenreihe
				//TODO: Get this to work
				EinDaten ed;
				ed.auswahl = row;
				ed.nummer = column;
				ed.wert = DemoData.get_wert(y_hit, x_hit);
				if (ed.DoModal())// == IDOK)
				{



					RedrawWindow();
				}
					
			}
		}
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}

int Grafik::isSelected(int row)
{
	return auswahl.GetSel(row);
}


void Grafik::OnPaint()
{
	CPaintDC dc(this); 
	dc.FillRect(&drawable, &stdbrush.white);
	dc.FrameRect(&drawable, &stdbrush.black);
	int min_value = INT_MAX;
	int max_value = INT_MIN;

	for (int i = 0; i < DemoData.get_anz_z(); i++)
	{
		if (DemoData.minimum(i) < min_value)
			min_value = DemoData.minimum(i);
		if (DemoData.maximum(i) > max_value)
			max_value = DemoData.maximum(i);
	}

	drawable_height = CSize(drawable.bottom, drawable.top);
	value_height = CSize(min_value, max_value);
	drawable_width = CSize(drawable.left, drawable.right);
	value_width = CSize(0, (bis_value - von_value - 1));

	dc.SelectObject(&stdpen.gray1);

	for (int column = von_value + 1; column < bis_value; column++)
	{
		int x = scale_point(column, value_width, drawable_width);
		dc.MoveTo(x, drawable.bottom);
		dc.LineTo(x, drawable.top);
	}


	dc.SelectObject(&stdpen.black7);

	//For highlighting
	for (int row = 0; row < DemoData.get_anz_z(); row++)
	{
		if (!isSelected(row)) continue;
		if (!highlighted[row]) continue;
		int x = scale_point(von_value, value_width, drawable_width);
		int y = scale_point(DemoData.get_wert(row, von_value), value_height, drawable_height);
		dc.MoveTo(x, y);

		for (int column = von_value + 1; column < bis_value; column++)
		{
			int x = scale_point(column, value_width, drawable_width);
			int y = scale_point(DemoData.get_wert(row, column), value_height, drawable_height);
			dc.LineTo(x, y);
		}
	}

	for (int row = 0; row < DemoData.get_anz_z(); row++)
	{
		if (!isSelected(row)) continue;
		dc.SelectObject(&stdpen.pen[row]);
		int x = scale_point(von_value, value_width, drawable_width);
		int y = scale_point(DemoData.get_wert(row, von_value), value_height, drawable_height);
		dc.MoveTo(x, y);

		for (int column = von_value + 1; column < bis_value; column++)
		{
			int x = scale_point(column, value_width, drawable_width);
			int y = scale_point(DemoData.get_wert(row, column), value_height, drawable_height);
			dc.LineTo(x, y);

			//Infobox
			if (highlighted[row])
			{
				CRect infobox;
				infobox.SetRect(x, y, 0, 0);
				CString text;
				text.Format(CString("%d"), DemoData.get_wert(row, column));

				dc.DrawText(text, &infobox, DT_CALCRECT);
				infobox.OffsetRect(0, -infobox.Height());
				infobox.right += 6;
				dc.FillRect(infobox, &stdbrush.yellow);
				dc.DrawText(text, &infobox, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
				dc.FrameRect(infobox, &stdbrush.black);
			}
		}
	}


}

void Grafik::change_name()
{
	SetWindowText(DemoData.get_name());
}

void Grafik::change_reihe(int z, int name, int farbe)
{
	auswahl.DeleteString(z);
	auswahl.InsertString(z, DemoData.get_rname(z));
	for (int i = 0; i < DemoData.get_anz_z(); i++)
	{
		auswahl.SetSel(i, isSelected(i));
	}

	if (farbe)
	{
		RedrawWindow();
	}
}

void Grafik::change_wert(int z, int s)
{
	if (isSelected(z))
	{
		RedrawWindow();
	}
}

void Grafik::change_all(int rnamen, int farben, int werte)
{
	if (rnamen)
	{
		for (int i = 0; i < DemoData.get_anz_z(); i++)
		{
			auswahl.DeleteString(i);
			auswahl.InsertString(i, DemoData.get_rname(i));
			auswahl.SetSel(i, isSelected(i));
		}
	}	

	if (werte)
	{
		RedrawWindow();
	}
}


BOOL Grafik::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch (message)
	{
	case UPDATE_NAME: change_name(); return 1;
	case UPDATE_REIHE: change_reihe((int) wParam, (int)lParam & FLAG_NAME, (int)lParam & FLAG_FARBE); return 1;
	case UPDATE_WERT: change_wert((int)wParam, (int)lParam); return 1;
	case UPDATE_ALL: change_all((int)lParam & FLAG_NAME, (int)lParam & FLAG_FARBE, (int)lParam & FLAG_WERT); return 1;
	case CLOSE_ALL: SendMessage(WM_CLOSE); return 1;
	default: return CDialog::OnWndMsg(message, wParam, lParam, pResult);
	}
}
