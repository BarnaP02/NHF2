#pragma once

#include <chrono>
#include <thread>

#include "raktar.h"

using namespace std;

class Terem;
class Szervezo {
	Targy* akt_targy;
	double akt_ar;
	double elkelt_ar;
public:
	Szervezo() : akt_targy(NULL), akt_ar(0), elkelt_ar(0) {
		//cout << "s1";
	}
	Szervezo(const Szervezo& masik) {
		this->akt_targy = masik.akt_targy;
		this->akt_ar = masik.akt_ar;
		this->elkelt_ar = masik.elkelt_ar;
		//cout << "s2";
	}
	~Szervezo() {
		//cout << "s-";
	};
	void setNextAr() {
		//cout << "aktar: " << akt_ar << endl;
		akt_ar += (akt_ar * 0.1);// -(akt_targy->getKikAr() * 0.1) % 10;
		//cout << "aktar: " << akt_ar << endl;
	}
	void setAktAr(double ar) {
		akt_ar = ar;
	}
	void getNextTargy(Raktar& r) {
		akt_targy = r.getEgyTargy();
		cout << " itt! \n";
		akt_ar = akt_targy->getKikAr();
		elkelt_ar = 0;
	}
	Targy* getAktTargy() {
		return akt_targy;
	}
	double getAktAr() {
		return akt_ar;
	}
	double getElkeltAr() {
		return elkelt_ar;
	}
	void eladEgyTargyat(Terem& hely, Raktar& r, chrono::milliseconds duration);
};