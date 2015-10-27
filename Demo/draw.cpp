#include "stdafx.h"
#include "draw.h"

brushes::brushes()
{
	int i;

	white.CreateStockObject(WHITE_BRUSH);
	black.CreateStockObject(BLACK_BRUSH);
	gray.CreateStockObject(GRAY_BRUSH);
	yellow.CreateSolidBrush(RGB(255, 255, 0));
	red.CreateSolidBrush(RGB(255, 0, 0));
	green.CreateSolidBrush(RGB(0, 255, 0));

	for (i = 0; i < MAX_ZEILEN; i++)
	{
		brush[i].CreateSolidBrush(RGB(0, 0, 0));
	}
}

brushes::~brushes()
{
	int i;

	yellow.DeleteObject();
	red.DeleteObject();
	green.DeleteObject();

	for (i = 0; i < MAX_ZEILEN; i++)
		brush[i].DeleteObject();
}

void brushes::set(int nr)
{
	brush[nr].DeleteObject();
	brush[nr].CreateSolidBrush(DemoData.get_farbe(nr));
}

void brushes::setall()
{
	for (int i = 0; i < DemoData.get_anz_z(); i++)
		set(i);
}

brushes stdbrush;

pens::pens()
{
	int i;

	black1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	black2.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	black5.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	black7.CreatePen(PS_SOLID, 7, RGB(0, 0, 0));
	gray1.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));

	for (i = 0; i < MAX_ZEILEN; i++)
		pen[i].CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
}

pens::~pens()
{
	int i;
	black1.DeleteObject();
	black2.DeleteObject();
	black5.DeleteObject();
	black7.DeleteObject();
	gray1.DeleteObject();

	for (i = 0; i < MAX_ZEILEN; i++)
		pen[i].DeleteObject();
}

void pens::set(int nr)
{
	pen[nr].DeleteObject();
	pen[nr].CreatePen(PS_SOLID, 3, DemoData.get_farbe(nr));
}

void pens::setall()
{
	for (int i = 0; i < DemoData.get_anz_z(); i++)
		set(i);
}

pens stdpen;

fonts::fonts()
{
	norm.CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, CString("Helvetica"));
	bold.CreateFont(-12, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, CString("Helvetica"));
	tiny.CreateFont(-9, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, CString("Helvetica"));
	medium.CreateFont(-16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, CString("Helvetica"));
	big.CreateFont(-32, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, CString("Helvetica"));
}

fonts::~fonts()
{
	norm.DeleteObject();
	bold.DeleteObject();
	tiny.DeleteObject();
	medium.DeleteObject();
	big.DeleteObject();
}

fonts stdfont;