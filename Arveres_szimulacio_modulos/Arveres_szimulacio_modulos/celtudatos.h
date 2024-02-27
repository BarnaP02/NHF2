#pragma once

#include "vevo.h"

class Celtudatos : public Vevo {
	Targy* az_a_targy;
public:
	Celtudatos(Raktar r) : Vevo() {
		setMotiv('c');
		az_a_targy = r.getEgyTargy();
		setSebMod(getSebMod() + 10);
		setPenzek((double)(rand() % 20) * 1000);
		setCol("\033[33m");	//yellow
	}
	Celtudatos(Targy* t) : Vevo() {
		setMotiv('c');
		az_a_targy = t;
		setSebMod(10);
		setPenzek((double)(rand() % 20) * 1000);
		setCol("\033[33m");
	}
	Celtudatos(Targy* t, int seb, double penz) : Vevo() {
		setMotiv('c');
		az_a_targy = t;
		overwriteSebMod(seb);
		setPenzek(penz);
		setCol("\033[33m");
	}
	~Celtudatos() {}
	Vevo* clone() override {
		return new Celtudatos(*this);
	}
	Targy* getAzATargy() override {
		return az_a_targy;
	}
	void megvesz(Szervezo sz, Targy& t) override;
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr();
	}
	bool ezAzATargy(Szervezo sz) {
		return az_a_targy == (sz.getAktTargy());
	}
	bool megvegyeme(Szervezo& sz) override {
		return vaneRaPenz(sz) && ezAzATargy(sz);
	}
};

