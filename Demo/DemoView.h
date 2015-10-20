
// DemoView.h: Schnittstelle der Klasse CDemoView
//

#pragma once


class CDemoView : public CView
{
protected: // Nur aus Serialisierung erstellen
	CDemoView();
	DECLARE_DYNCREATE(CDemoView)

// Attribute
public:
	CDemoDoc* GetDocument() const;

// Vorg�nge
public:

// �berschreibungen
public:
	virtual void OnDraw(CDC* pDC);  // �berschrieben, um diese Ansicht darzustellen
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementierung
public:
	virtual ~CDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Funktionen f�r die Meldungstabellen
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Debugversion in DemoView.cpp
inline CDemoDoc* CDemoView::GetDocument() const
   { return reinterpret_cast<CDemoDoc*>(m_pDocument); }
#endif

