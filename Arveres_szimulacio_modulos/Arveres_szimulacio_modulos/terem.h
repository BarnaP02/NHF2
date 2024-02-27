#pragma once

#include "listaelem.h"
#include <iomanip>
#include <string>

class Terem {
	ListaElem* sebesseg;
	size_t vevok;
	Vevo* akt_ajanlat;
public:
	Terem() {
		sebesseg = NULL;
		vevok = 0;
		akt_ajanlat = 0;
	}
	~Terem() {
		ListaElem* iter = sebesseg;
		ListaElem* elozo = iter;
		while (iter != NULL)
		{
			iter = iter->getKov();
			delete elozo->getV();
			delete elozo;
			elozo = iter;
		}
		vevok = 0;
	}
	Vevo* getAktAjanlat() {
		return akt_ajanlat;
	}
	void Add(Vevo* v);
	void kiir(string filename, Raktar r);
	Vevo* oVesziMeg(Szervezo& sz);
	void nemVeszikMeg(Szervezo& sz, Raktar& r);
	void oMegveszi(Szervezo& sz, Vevo& v, Raktar& r, Targy& t);
	ListaElem* getSebesseg() {
		return sebesseg;
	}
};