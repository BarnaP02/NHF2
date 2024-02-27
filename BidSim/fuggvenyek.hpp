#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Targy {
	string nev;
	double kik_ar;
	string tipus;
	bool elkelt;
public:
	Targy() {
		nev = "nagy semmi";
		kik_ar = 0;
		tipus = "levego";
		elkelt = false;
	}
	Targy(string n, double a, string t) {
		nev = n;
		kik_ar = a;
		tipus = t;
		elkelt = false;
	}
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
};

class Raktar {
	Targy* raktar;
	size_t raktar_size;
	int nincs_eladva;
public:
	Raktar(): raktar(NULL), raktar_size(0), nincs_eladva(0) { }
	~Raktar() { delete[]raktar; }
	void Add(Targy t) {
		Targy* uj = new Targy[raktar_size + 1];
		for (size_t i = 0; i < raktar_size; i++) {
			uj[i] = raktar[i];
		}
		uj[raktar_size] = t;
		delete[]raktar;
		raktar = uj;
		raktar_size += 1;
		nincs_eladva += 1;
	}
	void beolvas(string fajl) {
		ifstream fs;
		fs.open(fajl);

		if (!fs) {
			cerr << "Unable to open file " << fajl << endl;
			exit(1);   // call system to stop
		}
		string line;
		while (getline(fs, line)) {
			string input[3];
			stringstream ss(line);
			getline(ss, input[0], '\t');
			getline(ss, input[1], '\t');
			getline(ss, input[2], '\t');
			Targy t = Targy(input[0], stod(input[1]), input[2]);
			Add(t);
		}
		fs.close();
	}
	size_t getRaktarSize() {
		return raktar_size;
	}
	int getNincsEladva() {
		return nincs_eladva;
	}
	Targy* getEgyTargy() const {
		if (raktar_size == 0) {
			cout << "Ures a raktar\n";
			return NULL;
		}
		if (nincs_eladva < 1) {
			cout << "Minden el lett adva";
			return NULL;
		}
		int x = 0;
		while (raktar[x].getElkelt()==true)
		{
			x = rand() % raktar_size;
		}
		return &raktar[x];
	}
	Targy operator[](int index) {
		return raktar[index];
	}
	void eladas() {
		nincs_eladva--;
	}
};
class Terem;
class Szervezo {
	Targy* akt_targy;
	double akt_ar;
	double elkelt_ar;
public:
	Szervezo(): akt_targy(NULL), akt_ar(0), elkelt_ar(0){ }
	~Szervezo() { };
	void setNextAr() {
		akt_ar += ((int)akt_targy->getKikAr() * 0.1) - (int)(akt_targy->getKikAr() * 0.1) % 10;
	}
	void setAktAr(double ar) {
		akt_ar = ar;
	}
	void getNextTargy(Raktar r) {
		akt_targy = r.getEgyTargy();
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
	void eladEgyTargyat(Terem hely, Raktar r);
};

class Vevo {
	double penz;
	double akt_penz;
	int sebesseg_mod;
	//bool most_enyem_e;
	Targy** megszerzett;
	size_t megszerzett_size;
	int id;
	char motiv;
protected:
	void setMotiv(char c) {		//hogy a tobbi Vevo be tudja allitani
		motiv = c;
	}
	void setPenzek(double p) {
		penz = p;
		akt_penz = p;
	}
public:
	Vevo() {
		penz = 0;
		akt_penz = 0;
		sebesseg_mod = 0;
		//most_enyem_e = false;
		megszerzett = NULL;
		megszerzett_size = 0;
		id = -1;
		motiv = ' ';
	}
	Vevo(double dinero, char c, int index) {
		penz = dinero;
		akt_penz = dinero;
		sebesseg_mod = rand() % 11 - 5;//-5 - 5
		//most_enyem_e = false;
		megszerzett = NULL;
		megszerzett_size = 0;
		id = index;
		motiv = c;
	}
	~Vevo() { delete[]megszerzett; }
	bool operator!=(Vevo rhs) {
		if (this == &rhs) return false;
		else return true;
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
	void megvesz(Szervezo sz, Targy t) {
		elrak(&t);
		setAktPenz(sz.getAktAr());
		megszerzett_size++;
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
	double megszerzettSize() {
		return megszerzett_size;
	}
	Targy* getMegyszerzett(size_t i) {
		return megszerzett[i];
	}
	char getMotiv() {
		return motiv;
	}
	int getId() {
		return id;
	}
	virtual bool vaneRaPenz(Szervezo sz) { return false; }
	virtual bool megvegyeme(Szervezo sz) { return false; }
};

class Celtudatos : public Vevo {
	Targy* az_a_targy;
public:
	Celtudatos(Targy* t) {
		setMotiv('c');
		az_a_targy = t;
		setSebMod(getSebMod() + 10);
		setPenzek((double)(rand() % 200) * 100);
	}
	~Celtudatos() {}
	bool vanerapenz(Szervezo sz) {
		return getAktPenz() > sz.getAktAr();
	}
	bool ezAzATargy(Szervezo sz) {
		return az_a_targy == (sz.getAktTargy());
	}
	bool megvegyeme(Szervezo sz) {
		return vaneRaPenz(sz) && ezAzATargy(sz);
	}
};

class Gyujto : public Vevo {
	std::string az_a_tipus;
	double mennyit_er;
public:
	Gyujto(Targy* t) {
		setMotiv('g');
		az_a_tipus = t->getTipus();
		setSebMod(getSebMod() + 50);
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		setPenzek((double)(rand() % 500) * 100);
	}
	~Gyujto() {}
	bool vaneRaPenz(Szervezo sz) {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool ezAzATipus(Szervezo sz) {
		return az_a_tipus == (sz.getAktTargy()->getTipus());
	}
	bool megvegyeme(Szervezo sz) {
		return vaneRaPenz(sz) && ezAzATipus(sz);
	}
	void setMennyitEr() {
		int ran = rand();
		mennyit_er = (double)(ran % 15 + 5)/100;	//5%-20%
	}
	double bekialt() {
		return getPenz() * mennyit_er;
	}
	bool bemonde(Szervezo sz) {
		return megvegyeme(sz) && bekialt() > sz.getAktAr();
	}
	void bemond(Szervezo sz) {
		sz.setAktAr(bekialt());
	}
};

class Profitert : public Vevo {
	double mennyit_er;
	double profit;
public:
	Profitert() {
		setMotiv('p');
		setSebMod(getSebMod() + 30);
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		profit = 0;
		setPenzek((double)(rand() % 400) * 100);
	}
	~Profitert() {}
	bool vaneRaPenz(Szervezo sz) {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool megvegyeme(Szervezo sz) {
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

class ListaElem {
	Vevo v;
	ListaElem* kov;
public:
	ListaElem() {
		v = Vevo();
		kov = NULL;
	}
	ListaElem(Vevo u) {
		v = u;
		kov = NULL;
	}
	~ListaElem(){}
	Vevo getV() {
		return v;
	}
	ListaElem* getKov() {
		return kov;
	}
	void setV(Vevo u) {
		v = u;
	}
	void setKov(ListaElem* e) {
		kov = e;
	}
};

class Terem {
	ListaElem* sebesseg;
	size_t vevok;
	Vevo akt_ajanlat;
public:
	~Terem(){
		ListaElem* iter = sebesseg;
		while (iter!=NULL)
		{
			ListaElem* elozo = iter;
			iter = iter->getKov();
			delete elozo;
		}
	}
	Vevo* getAktAjanlat() {
		return &akt_ajanlat;
	}
	void Add(Vevo v) {		//mivel rendezve rakjuk a vevoket a listaba igy nem kell rendezni oket kesobb
		ListaElem* uj = new ListaElem(v);
		ListaElem* iter = sebesseg;
		if (iter==NULL)
		{
			sebesseg = uj;
			return;
		}
		while (iter->getKov()->getV().getSebMod() < v.getSebMod() && iter->getKov() != NULL) {
			iter = iter->getKov();
		}
		iter->setKov(uj);
		uj->setKov(iter->getKov());
	}
	Vevo* oVesziMeg(Szervezo sz) {		//oVeszieMeg volt
		ListaElem* iter = sebesseg;				//most: visszaadja a vevot, aki elsokent reagalna az akt_ar-ra
		while (iter!=NULL)
		{
			if (iter->getV().megvegyeme(sz) && akt_ajanlat != iter->getV()) {
				akt_ajanlat = iter->getV();
				cout << "[V" << iter->getV().getId() << "]: Tartom a " << sz.getAktAr() << "€$ osszeget." << endl;
				return &akt_ajanlat;//iter->getV();
			}
			iter = iter->getKov();
		}
		return NULL;
	}
	void oMegveszi(Szervezo sz, Vevo v, Raktar r, Targy t) {
		v.megvesz(sz, t);			//kezeli a vevot
		t.setElkelt(true);			//kezeli a targyat
		r.eladas();					//ez is
		t.setAr(sz.getAktAr());		//ez is
	}
};
void Szervezo::eladEgyTargyat(Terem hely, Raktar r) {
	getNextTargy(r);											//lerendezi a szervezot
	while (hely.oVesziMeg(*this) != NULL)							//akkor lesz NULL ha egy vevo se fizetne erte tobbet
	{
		elkelt_ar = akt_ar;										//frissit
		setNextAr();											//beallitja az uj arat
	}
	hely.oMegveszi(*this, *hely.getAktAjanlat(), r, *akt_targy);	//lerendezi a megvetelt
}