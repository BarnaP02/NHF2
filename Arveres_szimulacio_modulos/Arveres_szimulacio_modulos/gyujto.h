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
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		setPenzek((double)(rand() % 500) * 1000);
		setCol("\033[35m");	//purple
	}
	Gyujto(Targy* t, int seb, double penz) : Vevo() {//teszthez
		setMotiv('g');
		az_a_tipus = t->getTipus();
		overwriteSebMod(seb);
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		setPenzek(penz);
		setCol("\033[35m");	//purple
	}
	~Gyujto() {}
	Vevo* clone() override {
		return new Gyujto(*this);
	}
	string getAzATipus() override {
		return az_a_tipus;
	}
	void megvesz(Szervezo sz, Targy& t) override;
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool ezAzATipus(Szervezo sz) {
		return az_a_tipus == (sz.getAktTargy()->getTipus());
	}
	bool megvegyeme(Szervezo& sz) override {
		if (vaneRaPenz(sz) && ezAzATipus(sz))
		{
			if (bemonde(sz)) { bemond(sz); }
			return true;
		}
		return false;
	}
	void setMennyitEr() {
		int ran = rand();
		mennyit_er = (double)(ran % 15 + 5) / 100;	//5%-20%
	}
	double bekialt() {
		return getPenz() * mennyit_er/(2*3);
	}
	bool bemonde(Szervezo sz) {
		return bekialt() > sz.getAktAr();
	}
	void bemond(Szervezo& sz) {
		sz.setAktAr(bekialt());
	}
};