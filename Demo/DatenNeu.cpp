// DatenNeu.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "DatenNeu.h"
#include "afxdialogex.h"
#include "Loeschwarnung.h"


// DatenNeu-Dialogfeld

IMPLEMENT_DYNAMIC(DatenNeu, CDialog)

DatenNeu::DatenNeu(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DATENNEU, pParent)
	, datenname(_T(""))
	, anzahl_z(0)
	, anzahl_2(0)
{

}

DatenNeu::~DatenNeu()
{
}

void DatenNeu::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATENNAME, datenname);
	DDX_Text(pDX, IDC_ANZAHL_Z, anzahl_z);
	DDV_MinMaxInt(pDX, anzahl_z, 1, 20);
	DDX_Text(pDX, IDC_ANZAHL_S, anzahl_2);
	DDV_MinMaxInt(pDX, anzahl_2, 1, 50);
}


BEGIN_MESSAGE_MAP(DatenNeu, CDialog)
	ON_BN_CLICKED(IDOK, &DatenNeu::OnBnClickedOk)
END_MESSAGE_MAP()


// DatenNeu-Meldungshandler


void DatenNeu::OnBnClickedOk()
{
	if (!UpdateData(TRUE))
	{
		return;
	}
	if (GetParentFrame()->GetActiveDocument()->IsModified())
	{
		Loeschwarnung lw;
		if (lw.DoModal() != IDOK)
		{
			return;
		}
	}
	CDialog::OnOK();
}


