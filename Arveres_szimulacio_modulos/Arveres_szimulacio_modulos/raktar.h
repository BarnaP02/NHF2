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
	}
	Raktar(const Raktar& masik) : nincs_eladva(masik.nincs_eladva) {
		Targy* rak = new Targy[masik.raktar_size];
		raktar_size = masik.raktar_size;
		for (size_t i = 0; i < raktar_size; ++i) {
			rak[i] = masik.raktar[i];
		}
		raktar = rak;
	}
	~Raktar() { delete[]raktar; raktar_size = 0; nincs_eladva = 0; }
	Targy& operator[](int index) {
		return raktar[index];
	}
	void Add(Targy& t);
	void beolvas(string fajl, int& allapot);
	size_t getRaktarSize() {
		return raktar_size;
	}
	int getNincsEladva() {
		return nincs_eladva;
	}
	Targy* getEgyTargy();
	void eladas() {
		nincs_eladva--;
	}
};