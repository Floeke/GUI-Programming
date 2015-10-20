// Name.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "Demo.h"
#include "Name.h"
#include "afxdialogex.h"


// Name-Dialogfeld

IMPLEMENT_DYNAMIC(Name, CDialog)

Name::Name(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_NAME, pParent)
	, datenname(_T(""))
{

}

Name::~Name()
{
}

void Name::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATENNAME, datenname);
}


BEGIN_MESSAGE_MAP(Name, CDialog)
END_MESSAGE_MAP()


// Name-Meldungshandler
