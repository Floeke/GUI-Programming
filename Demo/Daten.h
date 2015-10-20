// Daten.h: Schnittstelle für die Klasse Daten.
//
//////////////////////////////////////////////////////////////////////

# ifndef DATEN_H
# define DATEN_H

# define MAX_ZEILEN		20
# define MAX_SPALTEN    50

class Daten : public CObject 
	{
	DECLARE_SERIAL( Daten)

	private:
		int anz_z;							// Anzahl Zeilen (Datenreihen)
		int anz_s;							// Anzahl Spalten (Werte pro Datenreihe)
		CString name;						// Name des gesamten Datensatzes
		int wert[MAX_ZEILEN][MAX_SPALTEN];	// Wertematrix
		CString reihenname[MAX_ZEILEN];		// Name für jede Datenreihe
		COLORREF farbe[MAX_ZEILEN];			// Farbe für jede Datenreihe
		int display_aktiv;

	public:
		Daten()	{ anz_z = 0; anz_s = 0; name = "Ohne Name"; display_aktiv = 1;} // Konstruktor

		int get_anz_z() { return anz_z;}
		int get_anz_s() { return anz_s;}

		CString &get_name() { return name;}
		void set_name( CString &n);

		int get_wert( int z, int s);
		void set_wert( int z, int s, int w);

		CString &get_rname( int z);
		void set_rname( int z, CString &n);

		COLORREF get_farbe( int z);
		void set_farbe( int z, COLORREF c);

		void init( int z, int s, const CString& n);// Initialisierung mit Zeilen-, Spaltenzahl und Name
		void testdaten( int min, int max, int abw, int namen=1, int farbe=1, int werte=1); // Testdatengenerierung

		int minimum( int z);				// Minimum einer Zeile
		int maximum( int z);				// Maximum einer Zeile
		int minimum();						// Minimum insgesamt
		int maximum();						// Maximum insgesamt

		void display( CDC *pdc);
		void update_display();
		int get_display() { return display_aktiv;}
		void set_display( int on_off);
		CSize display_size();

		void Serialize( CArchive& ar);      // Serialisierung des Datensatzes
	};

extern Daten DemoData;						// Der Datensatz für das Programm


#endif
