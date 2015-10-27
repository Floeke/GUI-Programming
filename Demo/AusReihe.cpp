// AusReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReihe.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"


// AusReihe-Dialogfeld

IMPLEMENT_DYNAMIC(AusReihe, CDialog)

AusReihe::AusReihe(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AUSREIHE, pParent)
	, m_darstellung(0)
	, m_selection(0)
	, m_xraster(TRUE)
	, m_yraster(TRUE)
{
	int i;
	Create(IDD_AUSREIHE, pParent);
	for (i = 0; i < DemoData.get_anz_z(); i++)
		m_reihe.InsertString(i, DemoData.get_rname(i));

	UpdateData(FALSE);
	SetWindowText(CString("Datenreihe: ") + DemoData.get_rname(0));

	GetDlgItem(IDC_DIAGRAMM)->GetWindowRect(&rahmen);
	ScreenToClient(&rahmen);

	ShowWindow(SW_SHOW);

}

AusReihe::~AusReihe()
{
}

void AusReihe::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_LINIEN, m_darstellung);
	DDX_Control(pDX, IDC_REIHE, m_reihe);
	DDX_CBIndex(pDX, IDC_REIHE, m_selection);
	DDX_Check(pDX, IDC_XRASTER, m_xraster);
	DDX_Check(pDX, IDC_YRASTER, m_yraster);
}


BEGIN_MESSAGE_MAP(AusReihe, CDialog)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_REIHE, &AusReihe::OnCbnSelchangeReihe)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_LINIEN, &AusReihe::OnBnClickedLinien)
	ON_BN_CLICKED(IDC_SAEULEN, &AusReihe::OnBnClickedSaeulen)
	ON_BN_CLICKED(IDC_XRASTER, &AusReihe::OnBnClickedXraster)
	ON_BN_CLICKED(IDC_YRASTER, &AusReihe::OnBnClickedYraster)
END_MESSAGE_MAP()


// AusReihe-Meldungshandler


void AusReihe::OnClose()
{
	DestroyWindow();
	delete this;
}


void AusReihe::OnPaint()
{
	UpdateData(TRUE);
	CPaintDC dc(this); // device context for painting
	
	dc.FillRect(rahmen, &stdbrush.white); //Rahmen zum zeichnen weiß füllen
	CRect innen_rahmen = CRect(rahmen.TopLeft(), rahmen.BottomRight());
	innen_rahmen.DeflateRect(ABSTAND_RAND, ABSTAND_RAND_OBEN, ABSTAND_RAND, ABSTAND_RAND);

	dc.FrameRect(&innen_rahmen, &stdbrush.gray);
	CPen *oldPen;
	oldPen = dc.SelectObject(&stdpen.gray1);

	if (m_xraster) //funktioniert offenbar...
	{
		int anzahl_x = DemoData.get_anz_s();
		int verfuegbar_x = innen_rahmen.right - innen_rahmen.left - ABSTAND_RAND - ABSTAND_RAND;
		int draw_here;
		for (int i = 1; i <= anzahl_x; i++)
		{
			draw_here = ABSTAND_RAND + (i*verfuegbar_x) / (anzahl_x);
			dc.MoveTo(draw_here, innen_rahmen.bottom);
			dc.LineTo(draw_here, innen_rahmen.top);
		}
	}

	if (m_yraster) //Bissken weiter unten
	{
		int anzahl_y = DemoData.get_anz_z();
		int verfuegbar_y = innen_rahmen.bottom - innen_rahmen.top - ABSTAND_RAND_OBEN - ABSTAND_RAND;
		int draw_here;
		for (int i = 1; i <= anzahl_y; i++)
		{
			draw_here = verfuegbar_y + ABSTAND_RAND_OBEN - (ABSTAND_RAND + (i*verfuegbar_y) / (anzahl_y));// +1);
			dc.MoveTo(innen_rahmen.left, innen_rahmen.top + draw_here);
			dc.LineTo(innen_rahmen.right, innen_rahmen.top + draw_here);
		}
	}

	dc.SelectObject(oldPen);

	if (m_darstellung == 0) //Linien-Darstellung
	{

	} else { //Säulen-Darstellung

	}
}


void AusReihe::OnBnClickedLinien()
{
	InvalidateRect(rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnCbnSelchangeReihe()
{
	UpdateData(TRUE);
	SetWindowText(CString("Datenreihe: ") + DemoData.get_rname(m_selection));
	InvalidateRect(rahmen, FALSE);
	UpdateWindow();
}



void AusReihe::OnBnClickedSaeulen()
{
	InvalidateRect(rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnBnClickedXraster()
{
	InvalidateRect(rahmen, FALSE);
	UpdateWindow();
}


void AusReihe::OnBnClickedYraster()
{
	InvalidateRect(rahmen, FALSE);
	UpdateWindow();
}
