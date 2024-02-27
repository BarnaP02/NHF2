#pragma once

#include "vevo.h"

class Celtudatos : public Vevo {
	Targy* az_a_targy;
public:
	Celtudatos(Raktar r) : Vevo() {
		setMotiv('c');
		az_a_targy = r.getEgyTargy();
		setSebMod(getSebMod() + 10);
		//setSebMod((rand() % 11 - 5) + 10);
		cout << "c seb:" << getSebMod() << endl;
		setPenzek((double)(rand() % 2000) * 100);
		setCol("\033[33m");	//yellow
		//setId(r.getRaktarSize());
	}
	Celtudatos(Targy* t) : Vevo() {
		setMotiv('c');
		az_a_targy = t;
		setSebMod(10);
		cout << "c seb:" << getSebMod() << endl;
		setPenzek((double)(rand() % 2000) * 100);
		setCol("\033[33m");
	}
	~Celtudatos() {}
	Vevo* clone() override {
		return new Celtudatos(*this);
	}
	Targy* getAzATargy() {
		return az_a_targy;
	}
	void megvesz(Szervezo sz, Targy& t) override {
		elrak(&t);
		setAktPenz(sz.getElkeltAr());
		//setMegszerzettSize(getMegszerzettSize()+1);
	}
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr();
	}
	bool ezAzATargy(Szervezo sz) {
		return az_a_targy == (sz.getAktTargy());
	}
	bool megvegyeme(Szervezo sz) override {
		return vaneRaPenz(sz) && ezAzATargy(sz);
	}
};

