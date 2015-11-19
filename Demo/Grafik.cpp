// Grafik.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Grafik.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "dialogfont.h"


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
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Grafik, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
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
		auswahl.AddString(DemoData.get_rname(i));
	return 0;


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

}


void Grafik::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = minb;
	lpMMI->ptMinTrackSize.y = minh;

}
