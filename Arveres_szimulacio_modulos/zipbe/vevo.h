#pragma once
#include <iostream>

#include "szervezo.h"

using namespace std;

class Vevo {
	double penz;
	double akt_penz;
	int sebesseg_mod;
	//bool most_enyem_e;
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
	//static int next_id;
	Vevo() : penz(0), akt_penz(0), megszerzett(NULL), megszerzett_size(0), id(-1), motiv(' '), col("") {
		sebesseg_mod = 0;
		sebesseg_mod = rand() % 11 - 5;//-5 - 5
		cout << "v seb:" << getSebMod() << endl;
	}
	Vevo(double dinero, char c, int index) {	//a fajl beolvasashoz
		penz = dinero;
		akt_penz = dinero;
		sebesseg_mod = rand() % 11 - 5;//-5 - 5
		//most_enyem_e = false;
		megszerzett = NULL;
		megszerzett_size = 0;
		col = "";
		id = index;
		motiv = c;
	}
	~Vevo() { delete[]megszerzett; }
	Vevo operator=(const Vevo& masik) {		//ugyan olyan tipusu vevove allitja be, de nem kapja meg ugyan azokat az adatokat teljesesen
		this->penz = masik.penz;
		this->akt_penz = masik.akt_penz;
		this->sebesseg_mod = rand() % 11 - 5;//-5 - 5 hogy kulonbozo sebessegu legyen
		this->megszerzett = NULL;
		this->megszerzett_size = 0;
		this->id = masik.id;
		//nextId();
		this->motiv = masik.motiv;
		return *this;
	}
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
	void elrak(Targy* t) {
		Targy** uj = new Targy * [megszerzett_size + 1];
		for (size_t i = 0; i < megszerzett_size; i++) {
			uj[i] = megszerzett[i];
		}
		uj[megszerzett_size] = t;
		delete[]megszerzett;
		megszerzett = uj;
		megszerzett_size += 1;
	}
	double getPenz() {
		return penz;
	}
	double getAktPenz() {
		return akt_penz;
	}
	int getSebMod() {
		return sebesseg_mod;
	}
	/*bool getEnyeme() {
		return most_enyem_e;
	}*/
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
	/*int getId() {
		return id;
	}*/
	virtual void megvesz(Szervezo sz, Targy& t) { }
	virtual Vevo* clone() { return NULL; }
	virtual bool vaneRaPenz(Szervezo sz) { return false; }
	virtual bool megvegyeme(Szervezo sz) { return false; }
};