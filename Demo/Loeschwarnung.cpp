// Loeschwarnung.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Loeschwarnung.h"
#include "afxdialogex.h"


// Loeschwarnung-Dialogfeld

IMPLEMENT_DYNAMIC(Loeschwarnung, CDialog)

Loeschwarnung::Loeschwarnung(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_LOESCHWARNUNG, pParent)
{

}

Loeschwarnung::~Loeschwarnung()
{
}

void Loeschwarnung::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Loeschwarnung, CDialog)
END_MESSAGE_MAP()


// Loeschwarnung-Meldungshandler
