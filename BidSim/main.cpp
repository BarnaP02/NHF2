#include <iostream>
#include <iomanip>
#include "fuggvenyek.hpp"
#include "gtest_lite.h"
#include "memtrace.h"

int main() {
	srand((unsigned int)time(NULL));

	Terem aula;
	Szervezo senior;
	Raktar raktar;
	Celtudatos v1 = Celtudatos(raktar.getEgyTargy());
	aula.Add(v1);
	raktar.beolvas("belvasos_raktar.txt");
	for (size_t i = 0; i < raktar.getRaktarSize(); ++i) {
		cout << fixed << setprecision(0) << left << setw(30) << raktar[i].getNev() << ": ";
		cout << fixed << setprecision(0)<< left << "€$" << setw(10) << raktar[i].getKikAr() << " - " << right << setw(10) << raktar[i].getTipus() << endl;
	}
	while (raktar.getNincsEladva() > 0) {
		senior.eladEgyTargyat(aula, raktar);
	}

	cout << "mukszik\n";
	Raktar rak;
	rak.getEgyTargy();
	Targy targy1 = Targy("betonvero urkalapacs", 1000, "fegyver");
	rak.Add(targy1);
	rak.Add(targy1);
	//Celtudatos v1 = Celtudatos(&targy1);
	Targy t = *(rak.getEgyTargy());
	cout << t.getNev() << endl;
	cout << v1.getMotiv() << ", " << v1.getSebMod() << endl;
	cout << rak[1].getNev() << ", " << rak[1].getKikAr() << "€$, " << rak[1].getTipus() << endl;
}
