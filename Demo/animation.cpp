// animation.cpp: Implementierungsdatei
//



#include "stdafx.h"
#include "Demo.h"
#include "animation.h"
#include "afxdialogex.h"
#include "Daten.h"
#include "draw.h"

#define TEILER 50

// animation-Dialogfeld

IMPLEMENT_DYNAMIC(animation, CDialog)

animation::animation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ANIMATION, pParent)
{
	Create(IDD_DIALOG_ANIMATION, pParent);
	ShowWindow(SW_SHOW);
}

animation::~animation()
{
}

void animation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Control(pDX, IDC_SPEED, m_speed);
	DDX_Control(pDX, IDC_ANIMATION, m_animation);
	DDX_Control(pDX, IDC_START, m_start);
	DDX_Control(pDX, IDC_SPALTE, m_spalte);
}





BEGIN_MESSAGE_MAP(animation, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START, &animation::OnBnClickedStart)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// animation-Meldungshandler





void animation::OnClose()
{
	if (running)
		KillTimer(1);
	running = 0;
	DestroyWindow();
	delete this;
}


BOOL animation::OnInitDialog()
{
	CRect r;

	CDialog::OnInitDialog();
	m_speed.SetRange(1, 10, TRUE);
	m_speed.SetPos(5);
	m_progress.SetRange(1, DemoData.get_anz_s());
	m_progress.SetPos(0);

	position = 0;
	running = 0;
	pause = 0;

	m_spalte.GetWindowRect(&rec_spalte);
	ScreenToClient(&rec_spalte);
	m_animation.GetWindowRect(&rec_animation);
	ScreenToClient(&rec_animation);

	hoehe = rec_animation.top +
		DemoData.get_anz_z()*(balkenhoehe + balkenabstand) +
		balkenabstand + abstand;

	r.SetRect(0, 0, 3 * minbreite / 2, hoehe);
	r.OffsetRect(100, 100);
	CalcWindowRect(&r, 0);
	hoehe = r.Height();
	MoveWindow(&r, TRUE);
	
	SetWindowText(CString("Animation: ") + DemoData.get_name());
	return TRUE;
}




void animation::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if (m_animation.m_hWnd)
	{
		rec_animation.SetRect(rec_animation.left, rec_animation.top,
			cx - abstand, cy - abstand);
		m_animation.MoveWindow(rec_animation, 1);
		RedrawWindow();
	}
}


void animation::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = minbreite;
	lpMMI->ptMaxTrackSize.y = lpMMI->ptMinTrackSize.y = hoehe;
}




void animation::OnPaint()
{
	CPaintDC dc(this); 

	CString s;
	int spalte;
	int rest;

	spalte = position / TEILER;
	rest = position%TEILER;

	if (!pause)
	{
		if (running)
			dc.FillSolidRect(rec_spalte, RGB(0, 255, 0));
		else
			dc.FillSolidRect(rec_spalte, RGB(255, 255, 255));
	}
	else
		dc.FillSolidRect(rec_spalte, RGB(255, 0, 0));

	

	CDC dc2;
	CRect r = rec_animation;
	dc2.CreateCompatibleDC(&dc);
	CBitmap bmp;
	CBitmap *oldbmp;
	bmp.CreateCompatibleBitmap(&dc, r.Width(), r.Height());
	oldbmp = dc2.SelectObject(&bmp);
	//Draw me some shit

	dc2.SetBkColor(RGB(255, 255, 255));
	dc2.FillRect(CRect(0,0, r.Width(), r.Height()), &stdbrush.white);


	dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &dc2, 0, 0, SRCCOPY);
	dc2.SelectObject(oldbmp);
}


void animation::OnBnClickedStart()
{
	if (!running)
	{
		running = 1;
		position = 0;
		SetTimer(1, 50, 0);
		m_start.SetWindowText(CString("Stop"));
	}
	else
	{
		running = 0;
		KillTimer(1);
		m_start.SetWindowText(CString("Start"));
		RedrawWindow();
	}
}




void animation::OnTimer(UINT_PTR nIDEvent)
{
	if (!pause)
	{
		position += m_speed.GetPos();
		m_progress.SetPos(position / TEILER + 1);
		if (position / TEILER >= DemoData.get_anz_s() - 1)
		{
			position = (DemoData.get_anz_s() - 1)*TEILER;
			OnBnClickedStart();
		}
		else
			RedrawWindow();
	}
}




void animation::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (rec_animation.PtInRect(point))
	{
		pause = !pause;
		RedrawWindow(rec_spalte);
	}


	CDialogEx::OnLButtonDown(nFlags, point);
}
