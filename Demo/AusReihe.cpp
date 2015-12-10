// AusReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReihe.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"
#include "NeuerWert.h"
#include "usermsg.h"


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

	for (int i = 0; i < MAX_SPALTEN; i++)
	{
		infoflag[i] = 0;
	}

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
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

	//Old Draw-Objects
	CPen *oldPen = dc.SelectObject(&stdpen.gray1);
	CBrush *oldBrush = dc.SelectObject(&stdbrush.brush[m_selection]);
	CFont *oldFont = dc.SelectObject(&stdfont.norm);

	//Sizes for scaling
	CSize height_range = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));
	CSize width_range = CSize(0, DemoData.get_anz_s()-1);
	CSize height_drawable = CSize(rahmen.bottom - ABSTAND_RAND, rahmen.top + ABSTAND_RAND_OBEN);
	CSize width_drawable = CSize(rahmen.left + ABSTAND_RAND, rahmen.right - ABSTAND_RAND);



	if (m_xraster)
	{
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = scalePoint(index, width_range, width_drawable);
			dc.MoveTo(x, rahmen.top);
			dc.LineTo(x, rahmen.bottom);
		}
	}

	if (m_yraster) 
	{
		
		CSize height_range_horizontal_lines = CSize(-ANZ_HORIZONTAL_LINES / 2, ANZ_HORIZONTAL_LINES / 2);

		for (int index = -ANZ_HORIZONTAL_LINES / 2; index < ANZ_HORIZONTAL_LINES / 2; index++)
		{
			int y = scalePoint(index, height_range_horizontal_lines, height_drawable);
			dc.MoveTo(rahmen.left, y);
			dc.LineTo(rahmen.right, y);
		}
	}


	if (m_darstellung == 0) //Linien-Darstellung
	{

		//Draw y=0 - Line
		dc.SelectObject(&stdpen.black2);
		dc.MoveTo(rahmen.left + 2, scalePoint(0, height_range, height_drawable));
		dc.LineTo(rahmen.right - 2, scalePoint(0, height_range, height_drawable));

		//Draw background-line
		dc.SelectObject(&stdpen.black5);
		int x = scalePoint(0, width_range, width_drawable);
		int y = scalePoint(DemoData.get_wert(m_selection, 0), height_range, height_drawable);
		dc.MoveTo(x, y);

		for (int index = 1; index < DemoData.get_anz_s(); index++)
		{
			x = scalePoint(index, width_range, width_drawable);
			y = scalePoint(DemoData.get_wert(m_selection, index), height_range, height_drawable);

			dc.LineTo(x, y);
		}

		//Draw line
		dc.SelectObject(&stdpen.pen[m_selection]);
		x = scalePoint(0, width_range, width_drawable);
		y = scalePoint(DemoData.get_wert(m_selection, 0), height_range, height_drawable);		
		dc.MoveTo(x, y);

		for (int index = 1; index < DemoData.get_anz_s(); index++)
		{
			dc.Ellipse(x - POINT_SIZE, y - POINT_SIZE, x + POINT_SIZE, y + POINT_SIZE);
			x = scalePoint(index, width_range, width_drawable);
			y =  scalePoint(DemoData.get_wert(m_selection, index), height_range, height_drawable);
			
			dc.LineTo(x, y);
		}

		dc.Ellipse(x - POINT_SIZE, y - POINT_SIZE, x + POINT_SIZE, y + POINT_SIZE);

	} 
	else {  //Säulen-Darstellung

		//Width of the bar
		int rectangleWidth = scalePoint(1, width_range, width_drawable) / 10;

		//Draw y=0 - Line
		dc.SelectObject(&stdpen.black2);
		dc.MoveTo(rahmen.left + 2, scalePoint(0, height_range, height_drawable));
		dc.LineTo(rahmen.right - 2, scalePoint(0, height_range, height_drawable));


		//Draw bars
		for (int index = 0; index < DemoData.get_anz_s(); index++)
		{
			int x = scalePoint(index, width_range, width_drawable);
			int y = scalePoint(DemoData.get_wert(m_selection, index), height_range, height_drawable);
			int left = x - rectangleWidth;
			int right = x + rectangleWidth;

			CRect bar = CRect(left, y, right, scalePoint(0, height_range, height_drawable));
			dc.FillRect(&bar, &stdbrush.brush[m_selection]);
		}

	}


	//Display values
	dc.SetBkMode(TRANSPARENT);
	CRect infobox;

	for (int index = 0; index < DemoData.get_anz_s(); index++)
	{
		if (infoflag[index])
		{
			int x = scalePoint(index, width_range, width_drawable);
			int y = scalePoint(DemoData.get_wert(m_selection, index), height_range, height_drawable);

			infobox.SetRect(x, y, 0, 0);
			CString text;
			text.Format(CString("%d"), DemoData.get_wert(m_selection, index));

			dc.DrawText(text, &infobox, DT_CALCRECT);
			infobox.OffsetRect(0, -infobox.Height());
			infobox.right += 6;
			dc.FillRect(infobox, &stdbrush.yellow);
			dc.DrawText(text, &infobox, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
			dc.FrameRect(infobox, &stdbrush.black);
		}
	}

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);
	dc.SelectObject(oldFont);
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

void AusReihe::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Point isn't inside of the drawable area -> return
	if (!PtInRect(&rahmen, point)) return;

	//Sizes for scaling
	CSize height_range = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));
	CSize width_range = CSize(0, DemoData.get_anz_s() - 1);
	CSize height_drawable = CSize(rahmen.bottom - ABSTAND_RAND, rahmen.top + ABSTAND_RAND_OBEN);
	CSize width_drawable = CSize(rahmen.left + ABSTAND_RAND, rahmen.right - ABSTAND_RAND);

	//Get the selected point
	int x = scalePoint(point.x, width_drawable, width_range);
	int y = DemoData.get_wert(m_selection, x);

	int x_hit = point.x;
	int y_hit = scalePoint(y, height_range, height_drawable);

	//Hit
	CRect hit;
	hit.SetRect(x_hit - 2 * POINT_SIZE, y_hit - 2 * POINT_SIZE, x_hit + 2 * POINT_SIZE, y_hit + 2 * POINT_SIZE);

	if (PtInRect(&hit, point))
	{
		infoflag[x] = !infoflag[x];
	}
	else { 
		return; 
	}


	hit.InflateRect(40, 40);

	RedrawWindow(&hit, 0, RDW_INVALIDATE | RDW_UPDATENOW);

	CDialog::OnLButtonDown(nFlags, point);
}


void AusReihe::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Point isn't inside of the drawable area -> return
	if (!PtInRect(&rahmen, point)) return;

	//Sizes for scaling
	CSize height_range = CSize(DemoData.minimum(m_selection), DemoData.maximum(m_selection));
	CSize width_range = CSize(0, DemoData.get_anz_s() - 1);
	CSize height_drawable = CSize(rahmen.bottom - ABSTAND_RAND, rahmen.top + ABSTAND_RAND_OBEN);
	CSize width_drawable = CSize(rahmen.left + ABSTAND_RAND, rahmen.right - ABSTAND_RAND);

	//Get the selected point
	int x = scalePoint(point.x, width_drawable, width_range);
	int y = DemoData.get_wert(m_selection, x);

	int x_hit = point.x;
	int y_hit = scalePoint(y, height_range, height_drawable);

	//Hit
	CRect hit;
	hit.SetRect(x_hit - 2 * POINT_SIZE, y_hit - 2 * POINT_SIZE, x_hit + 2 * POINT_SIZE, y_hit + 2 * POINT_SIZE);

	if (PtInRect(&hit, point))
	{
		NeuerWert nw;
		nw.new_value = DemoData.get_wert(m_selection, x);
		if (nw.DoModal() == IDOK)
		{
			DemoData.set_wert(m_selection, x, nw.new_value);
			UpdateData(FALSE);
			GetParentFrame()->GetActiveDocument()->SetModifiedFlag();
			InvalidateRect(&rahmen, FALSE);
		}
	}


	

	CDialog::OnLButtonDblClk(nFlags, point);
}





void AusReihe::change_name()
{
	SetWindowText(DemoData.get_name());
}

void AusReihe::change_reihe(int z, int name, int farbe)
{
	if (name)
	{
		m_reihe.Clear();

		for (int i = 0; i < DemoData.get_anz_z(); i++)
			m_reihe.InsertString(i, DemoData.get_rname(i));
	}
	
	if (farbe)
	{
		RedrawWindow();
	}
	
}

void AusReihe::change_wert(int z, int s)
{
	if (z == m_selection)
		RedrawWindow();
}

void AusReihe::change_all(int rnamen, int farben, int werte)
{
	if (rnamen)
	{

		for (int i = 0; i < DemoData.get_anz_z(); i++)
		{
			m_reihe.DeleteString(i);
			m_reihe.InsertString(i, DemoData.get_rname(i));
		}
		m_reihe.SetCurSel(m_selection);
	}

	if (farben || werte)
	{
		RedrawWindow();
	}
}




BOOL AusReihe::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
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
