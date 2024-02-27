
#include "raktar.h"


void Raktar::Add(Targy& t) {
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

void Raktar::beolvas(string fajl, int& allapot) {
	ifstream fs;
	fs.open(fajl);

	if (!fs) {
		cerr << "Nem sikerult megnyitni a fajlt.\n" << fajl << endl;
		//exit(1);
		allapot = -1;
		return;
	}
	string line;
	while (getline(fs, line)) {
		string input[3];
		stringstream ss(line);
		getline(ss, input[0], '\t');
		getline(ss, input[1], '\t');
		getline(ss, input[2]);
		Targy t = Targy(input[0], stod(input[1]), input[2], raktar_size);
		Add(t);
	}
	fs.close();
}

Targy* Raktar::getEgyTargy() {
	if (raktar_size == 0) {
		cout << "Ures a raktar\n";
		return NULL;
	}
	if (nincs_eladva < 1) {
		cout << "Minden el lett adva";
		return NULL;
	}
	int x = rand() % raktar_size;
	while (raktar[x].getElkelt() == true)
	{
		x = rand() % raktar_size;
	}
	return &raktar[x];
}