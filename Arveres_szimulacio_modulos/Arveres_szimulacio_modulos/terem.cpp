#include "terem.h"
#include <iomanip>
#include <string>

void Terem::Add(Vevo* v) {					//mivel rendezve rakjuk a vevoket a listaba igy nem kell rendezni oket kesobb
	ListaElem* uj = new ListaElem(v);
	ListaElem* iter = sebesseg;
	v->setId(vevok++);
	if (iter == NULL)
	{
		sebesseg = uj;
		return;
	}
	if (iter->getKov() == NULL) {	//a masodik elem jon
		iter->setKov(uj);
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
	iter->setKov(uj);
}

void Terem::kiir(string filename, Raktar r) {
	ofstream outFile;
	outFile.open(filename);
	int index = 0;
	for (size_t i = 0; i < vevok; i++)					//annyiszor lefut ahany vevo van
	{
		ListaElem* iter = sebesseg;
		while (iter->getV()->getId() != index)		//megkeresi azt a listaelemet a sebessegben aminek az id-je a keresett id es kiirja az adatait
		{											//ez lenyegeben a terembe lepes sorrendjet adja vissza
			iter = iter->getKov();
		}
		outFile << "\n[V-" << setw(2) << right << setfill('0') << index << setfill(' ') << "]: ";
		index++;
		switch (iter->getV()->getMotiv()) {
		case 'c':
			outFile << "Celtudatos:\n\tceltargy:\t" << iter->getV()->getAzATargy()->getNev() << "\n";
			break;
		case 'g':
			outFile << "Gyujto:\n\tceltipus:\t" << iter->getV()->getAzATipus() << "\n";
			break;
		case 'p':
			outFile << "Profitert:\n\tprofit:\t" << fixed << setprecision(0) << left << "€$" << setw(10) << iter->getV()->getProfit() << "\n";
			break;
		}
		for (size_t j = 0; j < (size_t)iter->getV()->getMegszerzettSize(); j++)
		{
			outFile << "\t\t" << setfill(' ') << fixed << setprecision(0) << left << setw(50) << iter->getV()->getMegszerzett(j)->getNev() << ": ";
			outFile << fixed << setprecision(0) << left << "€$" << setw(10) << iter->getV()->getMegszerzett(j)->getKikAr() << endl;
		}
		outFile << "Penz az arveres elott:\t\t" << setfill(' ') << fixed << setprecision(0) << left << "€$" << setw(10) << iter->getV()->getPenz() << "\nPenz az arveres utan:\t\t" << left << "€$" << setw(10) << iter->getV()->getAktPenz() << "\nid:\t" << iter->getV()->getId() << "\n\n\n";
	}
	outFile << "Nem lett megveve:\n" << endl;
	for (size_t k = 0; k < r.getRaktarSize(); k++)
	{
		if (!r[k].getTElkelt())
		{
			outFile << "\t\t" << setfill(' ') << fixed << setprecision(0) << left << setw(50) << r[k].getNev() << ": ";
			outFile << fixed << setprecision(0) << left << "€$" << setw(10) << r[k].getKikAr() << endl;
		}
	}
	outFile << "mukszik2" << endl;

	outFile.close();
}

Vevo* Terem::oVesziMeg(Szervezo& sz) {		//oVeszieMeg volt
	ListaElem* iter = sebesseg;				//most: visszaadja a vevot, aki elsokent reagalna az akt_ar-ra
	while (iter != NULL)
	{
		if (iter->getV()->megvegyeme(sz) && akt_ajanlat != iter->getV()) {
			akt_ajanlat = iter->getV();
			return akt_ajanlat;
		}
		iter = iter->getKov();
	}
	return NULL;
}

void Terem::nemVeszikMeg(Szervezo& sz, Raktar& r) {
	sz.getAktTargy()->setElkelt(true);			//kezeli a targyat
	r.eladas();									//mert lenyegeben ezt sem fogja mar senki megvenni
}

void Terem::oMegveszi(Szervezo& sz, Vevo& v, Raktar& r, Targy& t) {
	v.megvesz(sz, t);			//kezeli a vevot
	t.setElkelt(true);			//kezeli a targyat
	t.setTElkelt(true);
	r.eladas();					//ez is
	t.setAr(sz.getElkeltAr());	//ez is
	akt_ajanlat = NULL;
}