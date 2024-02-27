#pragma once
#include <iostream>

#include "szervezo.h"

using namespace std;

class Vevo {
	double penz;
	double akt_penz;
	int sebesseg_mod;
	Targy** megszerzett;
	size_t megszerzett_size;
	int id;
	char motiv;
	string col;
protected:
	void setMotiv(char c) {		//hogy a tobbi Vevo be tudja allitani
		motiv = c;
	}
	void setPenzek(double p) {
		penz = p;
		akt_penz = p;
	}
	void setCol(string s) {
		col = s;
	}
public:
	Vevo() : penz(0), akt_penz(0), megszerzett(NULL), megszerzett_size(0), id(-1), motiv(' '), col("") {
		sebesseg_mod = 0;
		sebesseg_mod = rand() % 11 - 5;//-5 - 5
	}
	Vevo(double dinero, char c, int index) {	//a fajl beolvasashoz
		penz = dinero;
		akt_penz = dinero;
		sebesseg_mod = rand() % 11 - 5;//-5 - 5
		megszerzett = NULL;
		megszerzett_size = 0;
		col = "";
		id = index;
		motiv = c;
	}
	virtual ~Vevo() { delete[]megszerzett; ; }

	void torol() {
		delete this;
	}

	Vevo operator=(const Vevo& masik);
	bool operator!=(Vevo rhs) {
		if (this == &rhs) return false;
		else return true;
	}
	int getId() {
		return id;
	}
	void setId(int i) {
		id = i;
	}
	string getCol() {
		return col;
	}
	void setAktPenz(double koltott) {
		akt_penz -= koltott;
	}
	void setSebMod(int seb) {
		sebesseg_mod += seb;
	}
	void overwriteSebMod(int seb) {
		sebesseg_mod = seb;
	}
	void elrak(Targy* t);
	double getPenz() {
		return penz;
	}
	double getAktPenz() {
		return akt_penz;
	}
	int getSebMod() {
		return sebesseg_mod;
	}
	void setMegszerzettSize(int m) {
		megszerzett_size = m;
	}
	int getMegszerzettSize() {
		return megszerzett_size;
	}
	Targy* getMegszerzett(size_t i) {
		return megszerzett[i];
	}
	char getMotiv() {
		return motiv;
	}
	virtual Targy* getAzATargy() { return NULL; }
	virtual string getAzATipus() { return ""; }
	virtual double getProfit() { return 0; }
	virtual void megvesz(Szervezo sz, Targy& t) { }
	virtual Vevo* clone() { return NULL; }
	virtual bool vaneRaPenz(Szervezo sz) { return false; }
	virtual bool megvegyeme(Szervezo& sz) { return false; }
};