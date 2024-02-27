#pragma once
#include <string>

using namespace std;

class Targy {
	string nev;
	double kik_ar;
	string tipus;
	bool elkelt;
	int id;
public:
	Targy() {
		nev = "nagy semmi";
		kik_ar = 0;
		tipus = "levego";
		elkelt = false;
		id = 0;
		//cout << "t1";
	}
	Targy(const string& n, double a, const string& t) {
		nev = n;
		kik_ar = a;
		tipus = t;
		elkelt = false;
		id = 0;
		//cout << "t2";
	}
	Targy(const string& n, double a, const string& t, int i) {
		nev = n;
		kik_ar = a;
		tipus = t;
		elkelt = false;
		id = i;
		//cout << "t3";
	}
	Targy(const Targy& masik) {
		this->nev = masik.nev;
		this->kik_ar = masik.kik_ar;
		this->tipus = masik.tipus;
		this->elkelt = masik.elkelt;
		this->id = masik.id;
		//cout << "t4";
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
	void setAr(double ujar) {
		kik_ar = ujar;
	}
	int getId() {
		return id;
	}
	void setId(int i) {
		//setElkelt(true);
		id = i;
	}
};
