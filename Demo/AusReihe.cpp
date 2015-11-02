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


int scalePoint(int z, CSize xy, CSize uv)
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

	dc.FrameRect(&rahmen, &stdbrush.gray);
	CPen *oldPen = dc.SelectObject(&stdpen.gray1);
	CBrush *oldBrush = dc.SelectObject(&stdbrush.brush[m_selection]);
	CSize xy = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));//CSize(DemoData.get_anz_s(), DemoData.get_anz_z()); //Datenbereich
	CSize uv = CSize(rahmen.bottom, rahmen.top);// CSize(rahmen.Width(), rahmen.Height()); //Zeichenbereich

	if (m_xraster)
	{
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = ABSTAND_RAND + rahmen.left + (index * (rahmen.Width() - (2 * ABSTAND_RAND))) / (DemoData.get_anz_s() - 1);
			dc.MoveTo(x, rahmen.top);
			dc.LineTo(x, rahmen.bottom);
		}
	}

	if (m_yraster) 
	{
		for (int index = 0; index < DemoData.get_anz_z(); index++)
		{
			int y = ABSTAND_RAND_OBEN + rahmen.top + (index * (rahmen.Height() - ABSTAND_RAND - ABSTAND_RAND_OBEN)) / (DemoData.get_anz_z() - 1);
			dc.MoveTo(rahmen.left, y);
			dc.LineTo(rahmen.right, y);
		}
	}


	if (m_darstellung == 0) //Linien-Darstellung
	{
		//TODO: Scale right. Fix that shit.
		dc.SelectObject(&stdpen.pen[m_selection]);
		int x = scalePoint(0, xy, uv);
		int y = scalePoint(DemoData.get_wert(m_selection, 0), xy, uv);
		dc.MoveTo(x, y);

		for (int index = 1; index < DemoData.get_anz_s(); index++)
		{
			x = scalePoint(index, xy, uv);
			y = scalePoint(DemoData.get_wert(m_selection, index), xy, uv);
			dc.LineTo(x, y);
		}
	} else { 

		//Rechtecke. Ausmalen.
		//Breite der Rechtecke ermitteln
		//X = Spalte, also index
		//TODO: Find proper algorithm
		int rectangleWidth = 5;// ABSTAND_RAND / DemoData.get_anz_s();
		//TODO: Fix that shit

		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = ABSTAND_RAND + rahmen.left + (index * (rahmen.Width() - (2 * ABSTAND_RAND))) / (DemoData.get_anz_s() - 1);
			//CPoint topleft = CPoint()
			//CRect bar = CRect()
			int left = x - rectangleWidth;
			int right = x + rectangleWidth;
			int top;
			int bottom;
			if (DemoData.get_wert(m_selection, index) > 0)
			{
				top = scalePoint(DemoData.get_wert(m_selection, index), xy, uv);// +rahmen.top;
				bottom = rahmen.bottom;
			}
			else {
				top = rahmen.top;
				bottom = scalePoint(DemoData.get_wert(m_selection, index), xy, uv);// +rahmen.bottom;
			}

			CRect bar = CRect(left, top, right, bottom);
			//dc.FillRect(&bar, &stdbrush.brush[m_selection]);
			dc.FillRect(&bar, &stdbrush.gray);

		}

	}



	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
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


