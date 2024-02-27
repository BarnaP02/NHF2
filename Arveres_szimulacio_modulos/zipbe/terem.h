#pragma once

#include "listaelem.h"

class Terem {
	ListaElem* sebesseg;
	size_t vevok;
	Vevo* akt_ajanlat;
public:
	~Terem() {
		ListaElem* iter = sebesseg;
		while (iter != NULL)
		{
			ListaElem* elozo = iter;
			iter = iter->getKov();
			delete elozo;
		}
	}
	Vevo* getAktAjanlat() {
		return akt_ajanlat;
	}
	void Add(Vevo* v) {					//mivel rendezve rakjuk a vevoket a listaba igy nem kell rendezni oket kesobb
		ListaElem* uj = new ListaElem(v);
		ListaElem* iter = sebesseg;
		cout << "i" << v->getSebMod() << endl;
		v->setId(vevok++);
		if (iter == NULL)
		{
			sebesseg = uj;
			return;
		}
		if (iter->getKov() == NULL) {	//a masodik elem jon
			iter->setKov(uj);
			//uj->setKov(iter->getKov());
			return;
		}
		while (iter->getKov() != NULL) {
			if (iter->getKov()->getV()->getSebMod() > v->getSebMod())
			{
				uj->setKov(iter->getKov());
				iter->setKov(uj);
				return;
			}
			iter = iter->getKov();
		}
		//uj->setKov(iter->getKov());
		iter->setKov(uj);
	}
	void kiir(string filename, string data) {
		ofstream outFile;
		outFile.open(filename, ios::app);

		if (!outFile) {
			// try opening the file for writing without the "app" flag
			outFile.open(filename);

			if (!outFile) {
				cerr << "Unable to open file " << filename << endl;
				exit(1);   // call system to stop
			}

			// the file was created, so write the data to it
			outFile << data << endl;
		}
		else {
			// the file was opened in append mode, so write the data to the end of the file
			outFile << data << endl;
		}

		outFile.close();
	}
	Vevo* oVesziMeg(Szervezo sz) {		//oVeszieMeg volt
		ListaElem* iter = sebesseg;				//most: visszaadja a vevot, aki elsokent reagalna az akt_ar-ra
		while (iter != NULL)
		{
			if (iter->getV()->megvegyeme(sz) && akt_ajanlat != iter->getV()) {
				akt_ajanlat = iter->getV();
				//cout << "[V" << iter->getV()->getId() << "]: Tartom a " << sz.getAktAr() << "€$ osszeget." << endl;
				return akt_ajanlat;//iter->getV();
			}
			iter = iter->getKov();
		}
		return NULL;
	}
	void nemVeszikMeg(Szervezo& sz, Raktar& r) {
		sz.getAktTargy()->setElkelt(true);			//kezeli a targyat
		r.eladas();									//mert lenyegeben ezt sem fogja mar senki megvenni
		//t.setAr(sz.getAktAr());		//ez is
		//sz.getAktTargy()->setAr(sz.get)
	}
	void oMegveszi(Szervezo& sz, Vevo& v, Raktar& r, Targy& t) {
		v.megvesz(sz, t);			//kezeli a vevot
		t.setElkelt(true);			//kezeli a targyat
		r.eladas();					//ez is
		t.setAr(sz.getAktAr());		//ez is
		akt_ajanlat = NULL;
	}
};