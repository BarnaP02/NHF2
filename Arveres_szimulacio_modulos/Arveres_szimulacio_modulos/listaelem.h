#pragma once

#include "vevo.h"

class ListaElem {
	Vevo* v;
	ListaElem* kov;
public:
	ListaElem() {
		v = NULL;
		kov = NULL;
	}
	ListaElem(Vevo* u) {
		v = u;
		kov = NULL;
	}
	~ListaElem() { }
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