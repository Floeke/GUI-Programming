// Legende.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Legende.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"

#define ABSTAND 2
#define COLORRECTWITH 15


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
	size.right = 2 * ABSTAND + maxWidth + COLORRECTWITH;
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
	CRect color = CRect(2 * ABSTAND, 2 * ABSTAND, COLORRECTWITH, COLORRECTWITH);
	CPoint colorPos = CPoint(2 * ABSTAND, 2 * ABSTAND);
	CPoint textPos = CPoint(3 * ABSTAND + COLORRECTWITH, 1 * ABSTAND);
	for (int index = 0; index < DemoData.get_anz_z(); index++)
	{
		CBrush brush(DemoData.get_farbe(index));
		dc.SelectObject(&brush);
		dc.Rectangle(&color);
		color.OffsetRect(0, ABSTAND + COLORRECTWITH);
		CRect text = CRect(textPos.x, textPos.y, 0, 0);
		dc.DrawText(DemoData.get_rname(index), &text, DT_CALCRECT);
		dc.DrawText(DemoData.get_rname(index), &text, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		textPos.y = color.top - ABSTAND;
	}


	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);
}
