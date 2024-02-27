#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>

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
	~Targy(){ }
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

class Raktar {
	Targy* raktar;
	size_t raktar_size;
	int nincs_eladva;
public:
	Raktar(): raktar(NULL), raktar_size(0), nincs_eladva(0) {
		//cout << "r1";
	}
	Raktar(const Raktar& masik) : nincs_eladva(masik.nincs_eladva) {
		Targy* rak = new Targy[masik.raktar_size];
		raktar_size = masik.raktar_size;
		for (size_t i = 0; i < raktar_size; ++i) {
			rak[i] = masik.raktar[i];
		}
		raktar = rak;
		//cout << "r2";
	}
	~Raktar() { delete[]raktar; }
	Targy& operator[](int index) {
		return raktar[index];
	}
	void Add(Targy& t) {
		Targy* uj = new Targy[raktar_size + 1];
		for (size_t i = 0; i < raktar_size; i++) {
			uj[i] = raktar[i];
		}
		uj[raktar_size] = t;
		delete[]raktar;
		raktar = uj;
		raktar_size += 1;
		nincs_eladva += 1;
		//raktar[raktar_size].setId((int)raktar_size);
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
			getline(ss, input[2]);
			if (stod(input[1])) {

			}
			Targy t = Targy(input[0], stod(input[1]), input[2], raktar_size);
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
	Targy* getEgyTargy() {
		if (raktar_size == 0) {
			cout << "Ures a raktar\n";
			return NULL;
		}
		if (nincs_eladva < 1) {
			cout << "Minden el lett adva";
			return NULL;
		}
		int x = rand() % raktar_size;
		while (raktar[x].getElkelt()==true)
		{
			x = rand() % raktar_size;
		}
		return &raktar[x];
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
	Szervezo(): akt_targy(NULL), akt_ar(0), elkelt_ar(0){
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
	Vevo(): penz(0), akt_penz(0), megszerzett(NULL), megszerzett_size(0), col(""), id(-1), motiv(' '){
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

class Celtudatos : public Vevo {
	Targy* az_a_targy;
public:
	Celtudatos(Raktar r): Vevo() {
		setMotiv('c');
		az_a_targy = r.getEgyTargy();
		setSebMod(getSebMod() + 10); 
		//setSebMod((rand() % 11 - 5) + 10);
		cout << "c seb:" << getSebMod() << endl;
		setPenzek((double)(rand() % 2000) * 100);
		setCol("\033[33m");	//yellow
		//setId(r.getRaktarSize());
	}
	Celtudatos(Targy* t): Vevo() {
		setMotiv('c');
		az_a_targy = t;
		setSebMod(10);
		cout << "c seb:" << getSebMod() << endl;
		setPenzek((double)(rand() % 2000) * 100);
		setCol("\033[33m");
	}
	~Celtudatos() {}
	Vevo* clone() override {
		return new Celtudatos(*this);
	}
	Targy* getAzATargy() {
		return az_a_targy;
	}
	void megvesz(Szervezo sz, Targy& t) override {
		elrak(&t);
		setAktPenz(sz.getElkeltAr());
		//setMegszerzettSize(getMegszerzettSize()+1);
	}
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr();
	}
	bool ezAzATargy(Szervezo sz) {
		return az_a_targy == (sz.getAktTargy());
	}
	bool megvegyeme(Szervezo sz) override {
		return vaneRaPenz(sz) && ezAzATargy(sz);
	}
};

class Gyujto : public Vevo {
	std::string az_a_tipus;
	double mennyit_er;
public:
	Gyujto(Targy* t): Vevo() {
		setMotiv('g');
		az_a_tipus = t->getTipus();
		setSebMod(50);
		cout << "g seb:" << getSebMod() << endl;
		setMennyitEr();								//ez egy eleg egyszeru fuggveny, ami csak random modon beallitja a mennyit_er-t
		setPenzek((double)(rand() % 50000) * 100);
		setCol("\033[35m");	//purple
	}
	~Gyujto() {}
	Vevo* clone() override{
		return new Gyujto(*this);
	}
	string getAzATipus() {
		return az_a_tipus;
	}
	void megvesz(Szervezo sz, Targy& t) override {
		elrak(&t);
		setAktPenz(sz.getElkeltAr());
		//setMegszerzettSize(getMegszerzettSize() + 1);
	}
	bool vaneRaPenz(Szervezo sz) override {
		return getAktPenz() > sz.getAktAr() && getPenz() * mennyit_er > sz.getAktAr();
	}
	bool ezAzATipus(Szervezo sz) {
		return az_a_tipus == (sz.getAktTargy()->getTipus());
	}
	bool megvegyeme(Szervezo sz) override {
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
	void bemond(Szervezo& sz) {
		sz.setAktAr(bekialt());
	}
};

class Profitert : public Vevo {
	double mennyit_er;
	double profit;
public:
	Profitert(): Vevo() {
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

class ListaElem {
	Vevo* v;
	ListaElem* kov;
public:
	ListaElem() {
		v = NULL;
		kov = NULL;
		//cout << "l1";
	}
	ListaElem(Vevo *u) {
		v = u;
		kov = NULL;
		//cout << "l2";
	}
	~ListaElem() { delete v; }
	Vevo* getV() {
		return v;
	}
	ListaElem* getKov() {
		return kov;
	}
	void setV(Vevo* u) {
		v = u;
	}
	void setKov(ListaElem* e) {
		kov = e;
	}
};

class Terem {
	ListaElem* sebesseg;
	size_t vevok;
	Vevo* akt_ajanlat;
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
		return akt_ajanlat;
	}
	void Add(Vevo* v) {					//mivel rendezve rakjuk a vevoket a listaba igy nem kell rendezni oket kesobb
		ListaElem* uj = new ListaElem(v);
		ListaElem* iter = sebesseg;
		cout << "i" << v->getSebMod() << endl;
		v->setId(vevok++);
		if (iter==NULL)
		{
			sebesseg = uj;
			return;
		}
		if (iter->getKov() == NULL) {	//a masodik elem jon
			iter->setKov(uj);
			//uj->setKov(iter->getKov());
			return;
		}
		while (iter->getKov() != NULL) {
			if (iter->getKov()->getV()->getSebMod() > v->getSebMod())
			{
				uj->setKov(iter->getKov());
				iter->setKov(uj);
				return;
			}
			iter = iter->getKov();
		}
		//uj->setKov(iter->getKov());
		iter->setKov(uj);
	}
	void kiir(string filename, string data) {
		ofstream outFile;
		outFile.open(filename, ios::app);

		if (!outFile) {
			// try opening the file for writing without the "app" flag
			outFile.open(filename);

			if (!outFile) {
				cerr << "Unable to open file " << filename << endl;
				exit(1);   // call system to stop
			}

			// the file was created, so write the data to it
			outFile << data << endl;
		}
		else {
			// the file was opened in append mode, so write the data to the end of the file
			outFile << data << endl;
		}

		outFile.close();
	}
	Vevo* oVesziMeg(Szervezo sz) {		//oVeszieMeg volt
		ListaElem* iter = sebesseg;				//most: visszaadja a vevot, aki elsokent reagalna az akt_ar-ra
		while (iter!=NULL)
		{
			if (iter->getV()->megvegyeme(sz) && akt_ajanlat != iter->getV()) {
				akt_ajanlat = iter->getV();
				//cout << "[V" << iter->getV()->getId() << "]: Tartom a " << sz.getAktAr() << "€$ osszeget." << endl;
				return akt_ajanlat;//iter->getV();
			}
			iter = iter->getKov();
		}
		return NULL;
	}
	void nemVeszikMeg(Szervezo& sz, Raktar& r) {
		sz.getAktTargy()->setElkelt(true);			//kezeli a targyat
		r.eladas();									//mert lenyegeben ezt sem fogja mar senki megvenni
		//t.setAr(sz.getAktAr());		//ez is
		//sz.getAktTargy()->setAr(sz.get)
	}
	void oMegveszi(Szervezo& sz, Vevo& v, Raktar& r, Targy& t) {
		v.megvesz(sz, t);			//kezeli a vevot
		t.setElkelt(true);			//kezeli a targyat
		r.eladas();					//ez is
		t.setAr(sz.getAktAr());		//ez is
		akt_ajanlat = NULL;
	}
};

void Szervezo::eladEgyTargyat(Terem& hely, Raktar& r, chrono::milliseconds duration) {
	getNextTargy(r);											//lerendezi a szervezot
	//cout << setw(7) << right << "[Sz]: " << "A " << akt_targy->getNev() << " kikialtasi ara €$" << akt_ar << endl;
	cout << setw(7) << right << "[Sz]: " << "A kovetkezo targy az nem mas mint a hires " << akt_targy->getNev() << ", aminek kikialtasi ara €$\033[34m" << akt_ar << "\033[0m." << endl;
	Vevo* akt = hely.oVesziMeg(*this);
	this_thread::sleep_for(20*duration);
	if (akt == NULL) {
		cout << setw(7) << right << "\033[31m[Sz]: " << "A " << akt_targy->getNev() << " nem lett eladva €$" << akt_ar <<" aron.\033[0m" << endl;
		this_thread::sleep_for(chrono::milliseconds(2*duration));
		hely.nemVeszikMeg(*this, r);			//tul magas a kikialtasi ara es senki se fogja megvenni
		return;
	}
	while (akt != NULL)							//akkor lesz NULL ha egy vevo se fizetne erte tobbet
	{
		//cout << akt->getCol();
		//string aktv = "[" + akt->getCol() + "V-" + to_string(akt->getId()) + "\033[0m]: ";	//hogy jo legyen a setw()
		//cout << aktv << "Tartom a €$\033[34m" << akt_ar << "\033[0m-t." << endl;
		cout << "[" + akt->getCol() + "V-" << setw(2) << setfill('0') << to_string(akt->getId()) << setfill(' ') << "\033[0m]: " << "Tartom a €$\033[34m" << akt_ar << "\033[0m-t." << endl;
		this_thread::sleep_for(chrono::milliseconds(3*duration));
		akt = hely.oVesziMeg(*this);
		elkelt_ar = akt_ar;										//frissit
		setNextAr();											//beallitja az uj arat
		//cout << "[Szervezo]: Valaki a " << akt_targy->getNev() << "-ert " << akt_ar << "€$-ert? " << endl;
		if (akt_ar < 0) { cout << "nagybaj\n"; }
		else {cout << setw(8) << right << "[Sz]: " << "Valaki €$\033[34m" << akt_ar << "\033[0m-ert? " << endl;}
		this_thread::sleep_for(chrono::milliseconds(10*duration));

	}
	cout << setw(8) << right << "[Sz]: " << "A " << akt_targy->getNev() << " eladasi ara €$\033[36m" << elkelt_ar << "\033[0m, a vevo pedig V-" + to_string(hely.getAktAjanlat()->getId()) << "." << endl;
	this_thread::sleep_for(chrono::milliseconds(30*duration));
	hely.oMegveszi(*this, *hely.getAktAjanlat(), r, *akt_targy);	//lerendezi a megvetelt
}