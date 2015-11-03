// NeuerWert.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "NeuerWert.h"
#include "afxdialogex.h"


// NeuerWert-Dialogfeld

IMPLEMENT_DYNAMIC(NeuerWert, CDialog)

NeuerWert::NeuerWert(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_NEUER_WERT, pParent)
	, new_value(0)
{

}

NeuerWert::~NeuerWert()
{
}

void NeuerWert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NEUER_WERT, new_value);
}


BEGIN_MESSAGE_MAP(NeuerWert, CDialog)
END_MESSAGE_MAP()


// NeuerWert-Meldungshandler


BOOL NeuerWert::OnInitDialog()
{
	POINT mouse;
	GetCursorPos(&mouse);
	CRect rect;
	GetWindowRect(&rect);
	rect.OffsetRect(mouse.x - rect.left, mouse.y - rect.bottom);
	MoveWindow(rect);

	CDialog::OnInitDialog();
	return TRUE;  
}
