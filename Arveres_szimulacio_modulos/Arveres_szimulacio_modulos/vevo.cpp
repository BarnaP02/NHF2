
#include "vevo.h"

Vevo Vevo::operator=(const Vevo& masik) {		//ugyan olyan tipusu vevove allitja be, de nem kapja meg ugyan azokat az adatokat teljesesen
	this->penz = masik.penz;
	this->akt_penz = masik.akt_penz;
	this->sebesseg_mod = rand() % 11 - 5;//-5 - 5 hogy kulonbozo sebessegu legyen
	this->megszerzett = NULL;
	this->megszerzett_size = 0;
	this->id = masik.id;
	this->motiv = masik.motiv;
	return *this;
}

void Vevo::elrak(Targy* t) {
	Targy** uj = new Targy * [megszerzett_size + 1];
	for (size_t i = 0; i < megszerzett_size; i++) {
		uj[i] = megszerzett[i];
	}
	uj[megszerzett_size] = t;
	delete[]megszerzett;
	megszerzett = uj;
	megszerzett_size += 1;
}