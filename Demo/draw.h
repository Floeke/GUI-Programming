#pragma once
#include "stdafx.h"
#include "Daten.h"


class brushes
{
public:
	CBrush white;
	CBrush black;
	CBrush red;
	CBrush green;
	CBrush yellow;
	CBrush gray;
	CBrush brush[MAX_ZEILEN];
	brushes();
	~brushes();
	void set(int nr);
	void setall();
};


class pens
{
public:
	CPen black1;
	CPen black2;
	CPen black5;
	CPen black7;
	CPen gray1;
	CPen pen[MAX_ZEILEN];
	pens();
	~pens();
	void set(int nr);
	void setall();
};

class fonts
{
public:
	CFont norm;
	CFont bold;
	CFont tiny;
	CFont medium;
	CFont big;
	fonts();
	~fonts();
};



extern brushes stdbrush;
extern pens stdpen;
extern fonts stdfont;

