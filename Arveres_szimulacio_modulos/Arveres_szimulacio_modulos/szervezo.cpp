

#include "szervezo.h"
#include "terem.h"
#include "vevo.h"

#include <iomanip>


void Szervezo::getNextTargy(Raktar& r) {
	akt_targy = r.getEgyTargy();
	akt_ar = akt_targy->getKikAr();
	elkelt_ar = 0;
}

void Szervezo::eladEgyTargyat(Terem& hely, Raktar& r, chrono::milliseconds duration) {
	getNextTargy(r);							//lerendezi a szervezot
	cout << setw(7) << right << "[Sz]: " << "A kovetkezo targy az nem mas mint a hires " << akt_targy->getNev() << ", aminek kikialtasi ara €$\033[34m" << akt_ar << "\033[0m." << endl;
	Vevo* akt = hely.oVesziMeg(*this);
	this_thread::sleep_for(20 * duration);
	if (akt == NULL) {
		cout << setw(7) << right << "\033[31m[Sz]: " << "A " << akt_targy->getNev() << " nem lett eladva €$" << akt_ar << " aron.\033[0m" << endl;
		this_thread::sleep_for(chrono::milliseconds(2 * duration));
		hely.nemVeszikMeg(*this, r);			//tul magas a kikialtasi ara es senki se fogja megvenni
		return;
	}
	while (akt != NULL)							//akkor lesz NULL ha egy vevo se fizetne erte tobbet
	{
		if (((getElkeltAr() * 1.1 - getAktAr() >= -1) && (getElkeltAr() * 1.1 - getAktAr() <= 1)) || (getElkeltAr()==0)) {	//bekialtas nem tortent mert az akt ar at lett allitva kivulrol es nem egyezik meg a kovetkezo feltetelezett erteknek
			//cout << elkelt_ar << "\n";
			cout << "[" + akt->getCol() + "V-" << setw(2) << setfill('0') << to_string(akt->getId()) << setfill(' ') << "\033[0m]: " << "Tartom a €$\033[34m" << akt_ar << "\033[0m-t." << endl;
		}
		else
		{
			cout << "[" + akt->getCol() + "V-" << setw(2) << setfill('0') << to_string(akt->getId()) << setfill(' ') << "\033[0m]: " << "Tartom es emelem €$\033[31m" << akt_ar << "\033[0m-re." << endl;
		}
		this_thread::sleep_for(chrono::milliseconds(3 * duration));
		elkelt_ar = akt_ar;										//frissit
		setNextAr();											//beallitja az uj arat
		if (akt_ar < 0) { cerr << "nagybaj\n"; }
		cout << setw(8) << right << "[Sz]: " << "Valaki €$\033[34m" << akt_ar << "\033[0m-ert? " << endl; 
		this_thread::sleep_for(chrono::milliseconds(10 * duration));

		akt = hely.oVesziMeg(*this);
	}
	cout << setw(8) << right << "[Sz]: " << "Valaki eloszor? " << endl;
	this_thread::sleep_for(chrono::milliseconds(10 * duration));
	cout << setw(8) << right << "[Sz]: " << "Valaki masodszor? " << endl;
	this_thread::sleep_for(chrono::milliseconds(10 * duration));
	cout << setw(8) << right << "[Sz]: " << "Harmadszor? " << endl;
	this_thread::sleep_for(chrono::milliseconds(10 * duration));
	cout << setw(8) << right << "[Sz]: " << "Elkelt! " << endl;
	this_thread::sleep_for(chrono::milliseconds(10 * duration));
	cout << setw(8) << right << "[Sz]: " << "A " << akt_targy->getNev() << " eladasi ara €$\033[36m" << elkelt_ar << "\033[0m, a vevo pedig V-" + to_string(hely.getAktAjanlat()->getId()) << "." << endl;
	this_thread::sleep_for(chrono::milliseconds(30 * duration));
	hely.oMegveszi(*this, *hely.getAktAjanlat(), r, *akt_targy);	//lerendezi a megvetelt
}