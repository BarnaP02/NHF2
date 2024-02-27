#pragma once

#include <chrono>
#include <thread>
#include <cmath>

#include "raktar.h"

using namespace std;

class Terem;
class Szervezo {
	Targy* akt_targy;
	double akt_ar;
	double elkelt_ar;
public:
	Szervezo() : akt_targy(NULL), akt_ar(0), elkelt_ar(0) {
	}
	Szervezo(const Szervezo& masik) {
		this->akt_targy = masik.akt_targy;
		this->akt_ar = masik.akt_ar;
		this->elkelt_ar = masik.elkelt_ar;
	}
	~Szervezo() {
	};
	void setNextAr() {
		akt_ar += round(akt_ar * 0.1);
	}
	void setAktAr(double ar) {
		akt_ar = round(ar);
	}
	void getNextTargy(Raktar& r);
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