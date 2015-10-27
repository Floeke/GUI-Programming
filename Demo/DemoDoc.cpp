
// DemoDoc.cpp: Implementierung der Klasse CDemoDoc
//

#include "stdafx.h"
// SHARED_HANDLERS können in einem ATL-Projekt definiert werden, in dem Vorschau-, Miniaturansichts- 
// und Suchfilterhandler implementiert werden, und die Freigabe von Dokumentcode für das Projekt wird ermöglicht.
#ifndef SHARED_HANDLERS
#include "Demo.h"
#endif

#include "DemoDoc.h"
#include "Daten.h"
#include "draw.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDemoDoc

IMPLEMENT_DYNCREATE(CDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDemoDoc, CDocument)
END_MESSAGE_MAP()


// CDemoDoc-Erstellung/Zerstörung

CDemoDoc::CDemoDoc()
{
	// TODO: Hier Code für One-Time-Konstruktion einfügen

}

CDemoDoc::~CDemoDoc()
{
}

BOOL CDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}




// CDemoDoc-Serialisierung

void CDemoDoc::Serialize(CArchive& ar)
{
	DemoData.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: Hier Code zum Speichern einfügen
	}
	else
	{
		stdbrush.setall();
		stdpen.setall();
		DemoData.update_display();
	}
}

#ifdef SHARED_HANDLERS

// Unterstützung für Miniaturansichten
void CDemoDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Ändern Sie diesen Code, um die Dokumentdaten zu zeichnen.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Unterstützung für Suchhandler
void CDemoDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Suchinhalte aus Dokumentdaten festlegen. 
	// Die Inhaltsteile sollten durch ";" getrennt werden.

	// Beispiel:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDemoDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDemoDoc-Diagnose

#ifdef _DEBUG
void CDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDemoDoc-Befehle
