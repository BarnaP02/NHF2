#pragma once

#include "vevo.h"

class Gyujto : public Vevo {
	std::string az_a_tipus;
	double mennyit_er;
public:
	Gyujto(Targy* t) : Vevo() {
		setMotiv('g');
		az_a_tipus = t->getTipus();
		setSebMod(50);
		cout << "g seb:" << getSebMod() << endl;
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		setPenzek((double)(rand() % 50000) * 100);
		setCol("\033[35m");	//purple
	}
	~Gyujto() {}
	Vevo* clone() override {
		return new Gyujto(*this);
	}
	string getAzATipus() {
		return az_a_tipus;
	}
	void megvesz(Szervezo sz, Targy& t) override {
		elrak(&t);
		setAktPenz(sz.getElkeltAr());
		//setMegszerzettSize(getMegszerzettSize() + 1);
	}
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool ezAzATipus(Szervezo sz) {
		return az_a_tipus == (sz.getAktTargy()->getTipus());
	}
	bool megvegyeme(Szervezo sz) override {
		return vaneRaPenz(sz) && ezAzATipus(sz);
	}
	void setMennyitEr() {
		int ran = rand();
		mennyit_er = (double)(ran % 15 + 5) / 100;	//5%-20%
	}
	double bekialt() {
		return getPenz() * mennyit_er;
	}
	bool bemonde(Szervezo sz) {
		return megvegyeme(sz) && bekialt() > sz.getAktAr();
	}
	void bemond(Szervezo& sz) {
		sz.setAktAr(bekialt());
	}
};