#pragma once
#include <string>

using namespace std;

class Targy {
	string nev;
	double kik_ar;
	string tipus;
	bool elkelt;
	bool tenyleg_elkelt;	//mert az elkelt kell ahhoz hogy ne legyen egy draga targy vegtelenszer eladva
	int id;
public:
	Targy() {
		nev = "nagy semmi";
		kik_ar = 0;
		tipus = "levego";
		elkelt = false;
		tenyleg_elkelt = false;
		id = 0;
	}
	Targy(const string& n, double a, const string& t) {
		nev = n;
		kik_ar = a;
		tipus = t;
		elkelt = false;
		tenyleg_elkelt = false;
		id = 0;
	}
	Targy(const string& n, double a, const string& t, int i) {
		nev = n;
		kik_ar = a;
		tipus = t;
		elkelt = false;
		tenyleg_elkelt = false;
		id = i;
	}
	Targy(const Targy& masik) {
		this->nev = masik.nev;
		this->kik_ar = masik.kik_ar;
		this->tipus = masik.tipus;
		this->elkelt = masik.elkelt;
		this->tenyleg_elkelt = masik.tenyleg_elkelt;
		this->id = masik.id;
	}
	~Targy() { }
	string getNev() {
		return nev;
	}
	double getKikAr() {
		return kik_ar;
	}
	string getTipus() {
		return tipus;
	}
	void setElkelt(bool b) {
		elkelt = b;
	}
	bool getElkelt() {
		return elkelt;
	}
	void setTElkelt(bool b) {
		tenyleg_elkelt = b;
	}
	bool getTElkelt() {
		return tenyleg_elkelt;
	}
	void setAr(double ujar) {
		kik_ar = ujar;
	}
	int getId() {
		return id;
	}
	void setId(int i) {
		id = i;
	}
};
