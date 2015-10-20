// AusReihe.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "AusReihe.h"
#include "afxdialogex.h"


// AusReihe-Dialogfeld

IMPLEMENT_DYNAMIC(AusReihe, CDialog)

AusReihe::AusReihe(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AUSREIHE, pParent)
	, m_darstellung(0)
	, m_selection(0)
	, m_xraster(FALSE)
	, m_yraster(FALSE)
{

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
END_MESSAGE_MAP()


// AusReihe-Meldungshandler
