// Daten.cpp: Implementierung der Klasse Daten.
//
//////////////////////////////////////////////////////////////////////

# include "stdafx.h"

# undef NDEBUG
# include <assert.h>

# include "Daten.h"


Daten DemoData;			// Der Datensatz

void Daten::set_name( CString &n) 
	{ 
	name = n;

	update_display();
	}

int Daten::get_wert( int z, int s)
	{
	assert( z >= 0);
	assert( z < anz_z);
	assert( s >= 0);
	assert( s < anz_s);

	return wert[z][s];
	}

void Daten::set_wert( int z, int s, int w)
	{
	assert( z >= 0);
	assert( z < anz_z);
	assert( s >= 0);
	assert( s < anz_s);

	wert[z][s] = w;

	update_display();
	}

CString &Daten::get_rname( int z)
	{
	assert( z >= 0);
	assert( z < anz_z);

	return reihenname[z];
	}

void Daten::set_rname( int z, CString &n)
	{
	assert( z >= 0);
	assert( z < anz_z);

	reihenname[z] = n;

	update_display();
	}

COLORREF Daten::get_farbe( int z)
	{
	assert( z >= 0);
	assert( z < anz_z);

	return farbe[z];
	}

void Daten::set_farbe( int z, COLORREF c)
	{
	assert( z >= 0);
	assert( z < anz_z);

	farbe[z] = c;

	update_display();
	}

void Daten::init( int z, int s, const CString& n)
	{
	int i, k;
	char buf[12];

	assert( z <= MAX_ZEILEN);
	assert( s <= MAX_SPALTEN);

	anz_z = z;
	anz_s = s;
	name = n;

	for( i = 0; i < z; i++)
		{
		sprintf( buf, "Reihe %d", i+1);
		reihenname[i] = buf;
		farbe[i] = RGB( 0, 0, 0);	
		for( k = 0; k < s; k++)
			wert[i][k] = 0;
		}

	update_display();
	}

# define NAMLEN 8

int zufall( int von, int bis)
	{
	return rand()%(bis-von+1) + von;
	}

void Daten::testdaten( int min, int max, int abw, int namen, int farben, int werte)
	{
	int i, k, len;
	int unten, oben;
	char nambuf[NAMLEN+1];

	assert( min <= max);

    srand( (unsigned)time( NULL ));

	if( abw < 0)
		abw = max - min;
	for( i = 0; i < anz_z; i++)
		{
		if( namen)
			{
			len = zufall( 3, NAMLEN);
			for( k = 0; k < len; k++)
				nambuf[k] = zufall( 'a', 'z');
			nambuf[0] = toupper( nambuf[0]);
			nambuf[len] = 0;
			reihenname[i] = nambuf;
			}
		if( farben)
			farbe[i] = RGB( rand()%256, rand()%256, rand()%256);
		if( werte)
			{
			wert[i][0] = zufall( min, max);
			for( k = 1; k < anz_s; k++)
				{
				unten = wert[i][k-1] - abw;
				if( unten < min)
					unten = min;
				oben = wert[i][k-1] + abw;
				if( oben > max)
					oben = max;
				wert[i][k] = zufall( unten, oben);
				}
			}
		}
	
	update_display();
	}

int Daten::minimum( int z)
	{
	int s, m;

	assert( z >= 0);
	assert( z < anz_z);

	m = wert[z][0];
	for( s = 1; s < anz_s; s++)
		{
		if( wert[z][s] < m)
			m = wert[z][s];
		}
	return m;
	}

int Daten::maximum( int z)
	{
	int s, m;

	assert( z >= 0);
	assert( z < anz_z);

	m = wert[z][0];
	for( s = 1; s < anz_s; s++)
		{
		if( wert[z][s] > m)
			m = wert[z][s];
		}
	return m;
	}

int Daten::minimum()
	{
	int z, s, m;

	m = wert[0][0];
	for( z = 0; z < anz_z; z++)
		{
		for( s = 0; s < anz_s; s++)
			{
			if( wert[z][s] < m)
				m = wert[z][s];
			}
		}
	return m;
	}

int Daten::maximum()
	{
	int z, s, m;

	m = wert[0][0];
	for( z = 0; z < anz_z; z++)
		{
		for( s = 0; s < anz_s; s++)
			{
			if( wert[z][s] > m)
				m = wert[z][s];
			}
		}
	return m;
	}


IMPLEMENT_SERIAL( Daten, CObject, 1);

void Daten::Serialize(CArchive& ar)
	{
	int i, k;

	if (ar.IsStoring())
		{
		ar << name;
		ar << anz_z;
		ar << anz_s;
		for( i = 0; i < anz_z; i++)
			{
			ar << reihenname[i];		
			ar << farbe[i];	
			for( k = 0; k < anz_s; k++)
				ar << wert[i][k];
			}
		}
	else
		{
		ar >> name;
		ar >> anz_z;
		ar >> anz_s;
		for( i = 0; i < anz_z; i++)
			{
			ar >> reihenname[i];		
			ar >> farbe[i];	
			for( k = 0; k < anz_s; k++)
				ar >> wert[i][k];
			}
		}
	}


const int y_abstand =  15;
const int x_abstand1 = 80;
const int x_abstand2 = 20;
const int x_abstand3 = 36;
const int r_abstand =   4;

void Daten::display( CDC *pdc)
	{
	if( !display_aktiv)
		return;
	CRect r, clp, sect;
	int z, s, x, y, az, as, flg, i;
	CBrush b, c;
	CFont f, *sav;
	char buf[120];

	b.CreateStockObject( BLACK_BRUSH);
	f.CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0 ,0, 0, 0, 0, 0, 0, CString("Helvetica"));
	sav = pdc->SelectObject(&f);

	pdc->GetClipBox( clp);

	r.SetRect( r_abstand, r_abstand, 800, r_abstand + y_abstand);
	if( sect.IntersectRect( clp, r))
		pdc->DrawText( DemoData.get_name(), -1, &r, DT_LEFT|DT_SINGLELINE|DT_VCENTER);

	az = DemoData.get_anz_z();
	as = DemoData.get_anz_s();
	flg = (as >= MAX_SPALTEN/2); 

	for( s = 0; s < as; s++)
		{
		x = 3*r_abstand + x_abstand1 + x_abstand2 + (s%(MAX_SPALTEN/2))*x_abstand3;
		y = 2*r_abstand + ((s >= MAX_SPALTEN/2) ? r_abstand + (az+1)*y_abstand: 0);
		r.SetRect( x, y, x + x_abstand3, y + y_abstand);
		if( sect.IntersectRect( clp, r))
			{
			sprintf( buf, "%d", s);
			pdc->DrawText( CString(buf), -1, &r, DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			}
		}

	for( z = 0, x = r_abstand; z < az; z++)
		{
		for( i = 0, y = 2*r_abstand+y_abstand + z*y_abstand; i <= flg; i++, y += (az+1)*y_abstand+r_abstand)
			{
			r.SetRect( x, y, x + x_abstand1 + 1, y + y_abstand + 1);
			if( sect.IntersectRect( clp, r))
				{
				r.left += 4;
				pdc->DrawText( DemoData.get_rname(z), -1, &r, DT_LEFT|DT_SINGLELINE|DT_VCENTER);
				r.left -= 4;
				pdc->FrameRect( r, &b);
				}
			}
		}

	for( z = 0, x = 2*r_abstand + x_abstand1; z < az; z++)
		{
		c.CreateSolidBrush( DemoData.get_farbe( z));
		for( i = 0, y = 2*r_abstand+y_abstand + z*y_abstand; i <= flg; i++, y += (az+1)*y_abstand+r_abstand)
			{
			r.SetRect( x, y, x + x_abstand2 + 1, y + y_abstand + 1);
			if( sect.IntersectRect( clp, r))
				{
				pdc->FillRect( r, &c);
				pdc->FrameRect( r, &b);
				}
			}
		c.DeleteObject();
		}

	for( s = 0; s < as; s++)
		{
		x = 3*r_abstand + x_abstand1 + x_abstand2 + (s%(MAX_SPALTEN/2))*x_abstand3;
		y = 2*r_abstand+y_abstand + (s >= MAX_SPALTEN/2 ? r_abstand + DemoData.get_anz_z()*y_abstand + y_abstand: 0);
		for( z = 0; z < az; z++, y+= y_abstand)
			{
			r.SetRect( x, y, x + x_abstand3 + 1, y + y_abstand + 1);
			if( sect.IntersectRect( clp, r))
				{
				sprintf( buf, "%d", DemoData.get_wert( z, s));
				r.right -= 4;
				pdc->DrawText( CString(buf), -1, &r, DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
				r.right += 4;
				pdc->FrameRect( r, &b);
				}
			}
		}
	pdc->SelectObject( sav);
	f.DeleteObject();
	}

void Daten::update_display()
	{
	CWinApp *a;
	CDocTemplate *t;
	CDocument *d;
	CView *v;
	POSITION p;

	a = AfxGetApp();
	p = a->GetFirstDocTemplatePosition();
	t = a->GetNextDocTemplate( p);
	p = t->GetFirstDocPosition();
	d = t->GetNextDoc( p);
	p = d->GetFirstViewPosition();
	v = d->GetNextView( p);
	v->RedrawWindow();
	}

CSize Daten::display_size()
	{
	int h, b;

	h = 3*r_abstand + (anz_z+1)*y_abstand;
	b = 4*r_abstand + x_abstand1 + x_abstand2;
	if( anz_s > MAX_SPALTEN/2)
		{
		b += (MAX_SPALTEN/2)*x_abstand3;
		h += r_abstand + (anz_z+1)*y_abstand;
		}
	else
		b += anz_s*x_abstand3;
	return CSize( b, h);
	}

void Daten::set_display( int on_off)
	{
	display_aktiv = on_off;
	update_display();
	}
