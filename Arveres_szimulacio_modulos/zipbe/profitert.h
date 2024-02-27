#pragma once

#include "vevo.h"

class Profitert : public Vevo {
	double mennyit_er;
	double profit;
public:
	Profitert() : Vevo() {
		setMotiv('p');
		setSebMod(30);
		cout << "p seb:" << getSebMod() << endl;
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		profit = 0;
		setPenzek((double)(rand() % 4000) * 100);
		setCol("\033[32m");	//green
	}
	~Profitert() {}
	void megvesz(Szervezo sz, Targy& t) override {
		elrak(&t);
		setAktPenz(sz.getElkeltAr());
		//setMegszerzettSize(getMegszerzettSize() + 1);
		addToProfit(getPenz() * mennyit_er - sz.getAktAr());
	}
	Vevo* clone() override {
		return new Profitert(*this);
	}
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool megvegyeme(Szervezo sz) override {
		return vaneRaPenz(sz);
	}
	void setMennyitEr() {
		int ran = rand();
		mennyit_er = (double)(ran % 15 + 5) / 100;//5%-20%
	}
	void addToProfit(double steal) {
		profit += steal;
	}
	double getProfit() {
		return profit;
	}
};