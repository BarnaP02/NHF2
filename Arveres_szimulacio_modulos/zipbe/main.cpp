#include <iostream>
#include <iomanip>

#include <chrono>
#include <thread>

#include "targy.h"
#include "raktar.h"
#include "szervezo.h"
#include "vevo.h"
#include "celtudatos.h"
#include "gyujto.h"
#include "profitert.h"
#include "listaelem.h"
#include "terem.h"

#include "gtest_lite.h"
#include "memtrace.h"

int main() {
	srand((unsigned int)time(NULL));
	//Vevo::next_id = 0;

	int seconds;		//univerzalis idoegyseg, hogy ha akarjuk latni a mentesfajlt akkor gyorsan lefusson a program
	cout << "Adja meg a standard millisec egyseget (100: valosagos sebesseg, 0: instant): ";
	cin >> seconds;		//100as ertekkel a kod futasi ideje varhatoan ~20 perc legalabb
	std::chrono::milliseconds duration(seconds);
	string ifajlnev;
	cout << "Adja meg a targyakat tartalmazo fajl nevet: ";
	cin >> ifajlnev;
	string ofajlnev;
	cout << "Adja meg az arveres eredmenyeit eltarolando fajl nevet: ";
	cin >> ofajlnev;

	//lehetne tobb vevo halmaz amik kozul lehetne valasztani
	//pl sok c es keves g (5/3/1) vagy ami most van hogy 1/1/1 vagy pont 5/3/1 vagy 3/5/1

	Terem aula;
	Szervezo senior;
	Raktar raktar;
	raktar.beolvas(ifajlnev);
	for (size_t i = 0; i < raktar.getRaktarSize(); ++i) {
		cout << fixed << setprecision(0) << left << setw(50) << raktar[i].getNev() << ": ";
		cout << fixed << setprecision(0) << left << "€$" << setw(10) << raktar[i].getKikAr() << " - " << right << setw(10) << raktar[i].getTipus() << endl;
	}
	senior.getNextTargy(raktar);

	Celtudatos v1 = Celtudatos(raktar.getEgyTargy());
	cout << "v1 targya:" << v1.getAzATargy()->getNev() << endl;
	aula.Add(v1.clone());
	Celtudatos v2 = Celtudatos(raktar.getEgyTargy());
	cout << "v2 targya:" << v2.getAzATargy()->getNev() << endl;
	aula.Add(v2.clone());
	Celtudatos v3 = Celtudatos(raktar.getEgyTargy());
	cout << "v3 targya:" << v3.getAzATargy()->getNev() << endl;
	aula.Add(v3.clone());
	Celtudatos v4 = Celtudatos(raktar.getEgyTargy());
	cout << "v4 targya:" << v4.getAzATargy()->getNev() << endl;
	aula.Add(v4.clone());
	Celtudatos v5 = Celtudatos(raktar.getEgyTargy());
	cout << "v5 targya:" << v5.getAzATargy()->getNev() << endl;
	aula.Add(v5.clone());
	Celtudatos v6 = Celtudatos(raktar.getEgyTargy());
	cout << "v6 targya:" << v6.getAzATargy()->getNev() << endl;
	aula.Add(v6.clone());
	Celtudatos v7 = Celtudatos(raktar.getEgyTargy());
	cout << "v7 targya:" << v7.getAzATargy()->getNev() << endl;
	aula.Add(v7.clone());
	Celtudatos v8 = Celtudatos(raktar.getEgyTargy());
	cout << "v8 targya:" << v8.getAzATargy()->getNev() << endl;
	aula.Add(v8.clone());
	Celtudatos v9 = Celtudatos(raktar.getEgyTargy());
	cout << "v9 targya:" << v9.getAzATargy()->getNev() << endl;
	aula.Add(v9.clone());
	Celtudatos v10 = Celtudatos(raktar.getEgyTargy());
	cout << "v10 targya:" << v10.getAzATargy()->getNev() << endl;
	aula.Add(v10.clone());

	Profitert v11 = Profitert();
	aula.Add(v11.clone());
	Profitert v12 = Profitert();
	aula.Add(v12.clone());
	Profitert v13 = Profitert();
	aula.Add(v13.clone());
	Profitert v14 = Profitert();
	aula.Add(v14.clone());
	Profitert v15 = Profitert();
	aula.Add(v15.clone());
	Profitert v16 = Profitert();
	aula.Add(v16.clone());
	Profitert v17 = Profitert();
	aula.Add(v17.clone());
	Profitert v18 = Profitert();
	aula.Add(v18.clone());
	Profitert v19 = Profitert();
	aula.Add(v19.clone());
	Profitert v20 = Profitert();
	aula.Add(v20.clone());

	Gyujto v21 = Gyujto(raktar.getEgyTargy());
	cout << "v21 tipusa:" << v21.getAzATipus() << endl;
	aula.Add(v21.clone());
	Gyujto v22 = Gyujto(raktar.getEgyTargy());
	cout << "v22 tipusa:" << v22.getAzATipus() << endl;
	aula.Add(v22.clone());
	Gyujto v23 = Gyujto(raktar.getEgyTargy());
	cout << "v23 tipusa:" << v23.getAzATipus() << endl;
	aula.Add(v23.clone());
	Gyujto v24 = Gyujto(raktar.getEgyTargy());
	cout << "v24 tipusa:" << v24.getAzATipus() << endl;
	aula.Add(v24.clone());
	Gyujto v25 = Gyujto(raktar.getEgyTargy());
	cout << "v25 tipusa:" << v25.getAzATipus() << endl;
	aula.Add(v25.clone());
	Gyujto v26 = Gyujto(raktar.getEgyTargy());
	cout << "v26 tipusa:" << v26.getAzATipus() << endl;
	aula.Add(v26.clone());
	Gyujto v27 = Gyujto(raktar.getEgyTargy());
	cout << "v27 tipusa:" << v27.getAzATipus() << endl;
	aula.Add(v27.clone());
	Gyujto v28 = Gyujto(raktar.getEgyTargy());
	cout << "v28 tipusa:" << v28.getAzATipus() << endl;
	aula.Add(v28.clone());
	Gyujto v29 = Gyujto(raktar.getEgyTargy());
	cout << "v29 tipusa:" << v29.getAzATipus() << endl;
	aula.Add(v29.clone());
	Gyujto v30 = Gyujto(raktar.getEgyTargy());
	cout << "v30 tipusa:" << v30.getAzATipus() << endl;
	aula.Add(v30.clone());

	while (raktar.getNincsEladva() > 0)
	{
		senior.eladEgyTargyat(aula, raktar, duration);
		cout << "YO";
	}

	cout << "\nmukszik\n";

	std::cout << "Waiting..." << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "Done waiting!" << std::endl;
	return 0;
}