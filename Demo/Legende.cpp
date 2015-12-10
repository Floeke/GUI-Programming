// Legende.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Legende.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"
#include "EinReihe.h"
#include "usermsg.h"

#define ABSTAND 2
#define COLORRECTWIDTH 15


// Legende-Dialogfeld

IMPLEMENT_DYNAMIC(Legende, CDialog)

Legende::Legende(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LEGENDE, pParent)
{
	Create(IDD_LEGENDE, pParent);
	ShowWindow(SW_SHOW);
	Invalidate();
}

Legende::~Legende()
{
}

void Legende::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Legende, CDialog)
	ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// Legende-Meldungshandler




void Legende::OnPaint()
{
	CPaintDC dc(this); 

	//Position the Window
	CRect size;
	size.top = 0;
	size.left = 0;
	CRect temp = CRect(0, 0, 0, 0);
	int maxWidth = 0;
	//Get max wordlength
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		dc.DrawText(DemoData.get_rname(index), &temp, DT_CALCRECT);
		if (temp.Width()>maxWidth)
			maxWidth = temp.Width();
	}
	size.bottom = 4 * ABSTAND + DemoData.get_anz_z()*temp.Height();
	size.right = 2 * ABSTAND + maxWidth + COLORRECTWIDTH;
	CRect pos;
	GetWindowRect(&pos);
	size.OffsetRect(pos.TopLeft());
	MoveWindow(&size, TRUE);

	//Draw the Rect
	size.bottom -= 2 * ABSTAND;
	size.right -= 2 * ABSTAND;
	size.OffsetRect(-size.TopLeft());
	size.OffsetRect(ABSTAND, ABSTAND);

	CPen* oldPen = dc.SelectObject(&stdpen.black1);
	CBrush* oldBrush = dc.SelectObject(&stdbrush.white);

	dc.Rectangle(size);

	//draw the legend
	CRect color = CRect(2 * ABSTAND, 2 * ABSTAND, COLORRECTWIDTH, COLORRECTWIDTH);
	CPoint colorPos = CPoint(2 * ABSTAND, 2 * ABSTAND);
	CPoint textPos = CPoint(3 * ABSTAND + COLORRECTWIDTH, 1 * ABSTAND);
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		CBrush brush(DemoData.get_farbe(index));
		dc.SelectObject(&brush);
		dc.Rectangle(&color);
		color.OffsetRect(0, ABSTAND + COLORRECTWIDTH);
		CRect text = CRect(textPos.x, textPos.y, 0, 0);
		dc.DrawText(DemoData.get_rname(index), &text, DT_CALCRECT);
		dc.DrawText(DemoData.get_rname(index), &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		textPos.y = color.top - ABSTAND;
	}


	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
}


void Legende::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CRect r;
	GetWindowRect(&r);
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		CRect hit = CRect(0, 2 * ABSTAND + index*(COLORRECTWIDTH + ABSTAND), 200, 2 * ABSTAND + index*(COLORRECTWIDTH + ABSTAND) + COLORRECTWIDTH);
		if (hit.PtInRect(point))
		{
			EinReihe r(NULL, index+1);
			r.DoModal();
		}
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}





void Legende::change_name()
{
	//Nothing to do
}

void Legende::change_reihe(int z, int name, int farbe)
{
	RedrawWindow();
}

void Legende::change_wert(int z, int s)
{
	//Nothing to do
}

void Legende::change_all(int rnamen, int farben, int werte)
{
	if(rnamen || farben)
		RedrawWindow();
}




BOOL Legende::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch (message)
	{
	case UPDATE_NAME: change_name(); return 1;
	case UPDATE_REIHE: change_reihe((int)wParam, (int)lParam & FLAG_NAME, (int)lParam & FLAG_FARBE); return 1;
	case UPDATE_WERT: change_wert((int)wParam, (int)lParam); return 1;
	case UPDATE_ALL: change_all((int)lParam & FLAG_NAME, (int)lParam & FLAG_FARBE, (int)lParam & FLAG_WERT); return 1;
	case CLOSE_ALL: SendMessage(WM_CLOSE); return 1;
	default: return CDialog::OnWndMsg(message, wParam, lParam, pResult);
	}
}