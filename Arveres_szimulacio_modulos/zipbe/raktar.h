#pragma once
#include <sstream>
#include <fstream>
#include <iostream>
#include "targy.h"

using namespace std;

class Raktar {
	Targy* raktar;
	size_t raktar_size;
	int nincs_eladva;
public:
	Raktar() : raktar(NULL), raktar_size(0), nincs_eladva(0) {
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
		while (raktar[x].getElkelt() == true)
		{
			x = rand() % raktar_size;
		}
		return &raktar[x];
	}
	void eladas() {
		nincs_eladva--;
	}
};