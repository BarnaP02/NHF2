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

using namespace std;

int main() {
	int menet = -1;
	bool ok = false;
	while (!ok)
	{
		cout << "Adja meg a raktar ID-t (0: test, 1: 1:1:1, 2: 3:2:1, 3: 3:1:2): ";
		menet = 0;			//csak jportara		
		//cin >> menet;		//egyeb esetben ezt
		switch (menet)
		{
		case 0:
			ok = true;
			break;
		case 1:
			ok = true;
			break;
		case 2:
			ok = true;
			break;
		case 3:
			ok = true;
			break;
		default:
			cout << "\nRossz input.\n ";
			break;
		}
	}

	if (menet == 0) {
		Terem teszt_hely;
		Terem t2h;
		Szervezo teszt_vezeto;
		Raktar teszt_raktar;
		
		Targy t1 = Targy("Elso targy", 1000, "ilyen", teszt_raktar.getRaktarSize());
		teszt_raktar.Add(t1);
		Targy t2 = Targy("Masodik targy", 200, "ilyen", teszt_raktar.getRaktarSize());
		teszt_raktar.Add(t2);
		Targy t3 = Targy("Harmadik targy", 600, "olyan", teszt_raktar.getRaktarSize());
		teszt_raktar.Add(t3);

		Celtudatos vt1 = Celtudatos(&teszt_raktar[0], 1, 3000);
		cout << "vt1 targya:" << vt1.getAzATargy()->getNev() << endl;
		teszt_hely.Add(vt1.clone());
		Gyujto vt2 = Gyujto(&teszt_raktar[1], 3, 5000);
		cout << "vt2 tipusa:" << vt2.getAzATipus() << endl;
		teszt_hely.Add(vt2.clone());
		Profitert vt3 = Profitert(2, 4500);
		teszt_hely.Add(vt3.clone());
		
		t2h.Add(vt3.clone());

		TEST(TEST1, inicializalas_targy1) {
			EXPECT_EQ(t1.getNev(), "Elso targy");
			EXPECT_EQ(t1.getKikAr(), 1000);
			EXPECT_EQ(t1.getTipus(), "ilyen");
			EXPECT_EQ(t1.getId(), 0);
		} ENDM
		TEST(TEST2, inicializalas_targy2) {
			EXPECT_EQ(t2.getNev(), "Masodik targy");
			EXPECT_EQ(t2.getKikAr(), 200);
			EXPECT_EQ(t2.getTipus(), "ilyen");
			EXPECT_EQ(t2.getId(), 1);
		} ENDM
		TEST(TEST3, inicializalas_targy3) {
			EXPECT_EQ(t3.getNev(), "Harmadik targy");
			EXPECT_EQ(t3.getKikAr(), 600);
			EXPECT_EQ(t3.getTipus(), "olyan");
			EXPECT_EQ(t3.getId(), 2);
		} ENDM
		TEST(TEST4, inicializalas_vevo_penz) {
			EXPECT_EQ(vt1.getAktPenz(), 3000);
			EXPECT_EQ(vt2.getAktPenz(), 5000);
			EXPECT_EQ(vt3.getAktPenz(), 4500);
		} ENDM
		TEST(TEST5, inicializalas_vevo_motiv) {
			EXPECT_EQ(vt1.getMotiv(), 'c');
			EXPECT_EQ(vt2.getMotiv(), 'g');
			EXPECT_EQ(vt3.getMotiv(), 'p');
		} ENDM
		TEST(TEST6, inicializalas_vevo_sebmod) {
			EXPECT_EQ(vt1.getSebMod(), 1);
			EXPECT_EQ(vt2.getSebMod(), 3);
			EXPECT_EQ(vt3.getSebMod(), 2);
		} ENDM
		TEST(TEST7, inicializalas_vevo_specialis) {
			EXPECT_EQ(vt1.getAzATargy()->getNev(), "Elso targy");
			EXPECT_EQ(vt2.getAzATipus(), "ilyen");
			EXPECT_EQ(vt3.getProfit(), 0);
		} ENDM
			
		TEST(TEST8, eladas1) {
			teszt_vezeto.eladEgyTargyat(teszt_hely, teszt_raktar, std::chrono::milliseconds(0));
			if (teszt_vezeto.getAktTargy()->getNev()=="Elso targy")	{
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Elso targy");
			}
			if (teszt_vezeto.getAktTargy()->getNev() == "Masodik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Masodik targy");
			}
			if (teszt_vezeto.getAktTargy()->getNev() == "Harmadik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Harmadik targy");
			}
			EXPECT_EQ(teszt_raktar.getNincsEladva(), 2);
		} ENDM
		TEST(TEST9, eladas2) {
			teszt_vezeto.eladEgyTargyat(teszt_hely, teszt_raktar, std::chrono::milliseconds(0));
			if (teszt_vezeto.getAktTargy()->getNev() == "Elso targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Elso targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 1000);
			}
			if (teszt_vezeto.getAktTargy()->getNev() == "Masodik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Masodik targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 428);
			}
			if (teszt_vezeto.getAktTargy()->getNev() == "Harmadik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Harmadik targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 600);
			}
			EXPECT_EQ(teszt_raktar.getNincsEladva(), 1);
		} ENDM
		TEST(TEST10, eladas3) {
			teszt_vezeto.eladEgyTargyat(teszt_hely, teszt_raktar, std::chrono::milliseconds(0));
			if (teszt_vezeto.getAktTargy()->getNev() == "Elso targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Elso targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 1000);
			}
			if (teszt_vezeto.getAktTargy()->getNev() == "Masodik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Masodik targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 428);
			}
			//ezt nem jol tesztelheto mert lehet hogy mas sorrendben kerultek bele a targyak a vevo listajaba
			/*if (teszt_vezeto.getAktTargy()->getNev() == "Harmadik targy") {
				EXPECT_EQ(teszt_hely.oVesziMeg(teszt_vezeto)->getMegszerzett(0)->getNev(), "Harmadik targy");
				EXPECT_EQ(round(teszt_vezeto.getElkeltAr()), 600);
			}
			EXPECT_EQ(teszt_hely.getSebesseg()->getV()->getMegszerzettSize(), 1);
			EXPECT_EQ(teszt_hely.getSebesseg()->getKov()->getV()->getMegszerzettSize(), 2);
			EXPECT_EQ(teszt_hely.getSebesseg()->getKov()->getKov()->getV()->getMegszerzettSize(), 0);*/
			EXPECT_EQ(teszt_raktar.getNincsEladva(), 0);
		} ENDM

		TEST(TEST11, post_eladasok) {
			double sum = 0;
			for (int i = 0; i < teszt_hely.getSebesseg()->getV()->getMegszerzettSize(); i++)
			{
				sum += teszt_hely.getSebesseg()->getV()->getMegszerzett(i)->getKikAr();
			}
			EXPECT_EQ(round(teszt_hely.getSebesseg()->getV()->getAktPenz() + sum), teszt_hely.getSebesseg()->getV()->getPenz());
			sum = 0;
			for (int i = 0; i < teszt_hely.getSebesseg()->getKov()->getV()->getMegszerzettSize(); i++)
			{
				sum += teszt_hely.getSebesseg()->getKov()->getV()->getMegszerzett(i)->getKikAr();
			}
			EXPECT_EQ(round(teszt_hely.getSebesseg()->getKov()->getV()->getAktPenz() + sum), teszt_hely.getSebesseg()->getKov()->getV()->getPenz());
			sum = 0;
			for (int i = 0; i < teszt_hely.getSebesseg()->getKov()->getKov()->getV()->getMegszerzettSize(); i++)
			{
				sum += teszt_hely.getSebesseg()->getKov()->getKov()->getV()->getMegszerzett(i)->getKikAr();
			}
			EXPECT_EQ(round(teszt_hely.getSebesseg()->getKov()->getKov()->getV()->getAktPenz() + sum), teszt_hely.getSebesseg()->getKov()->getKov()->getV()->getPenz());
		} ENDM
	}
	std::srand((unsigned int)time(NULL));

	Terem aula;
	Szervezo senior;
	Raktar raktar;
	std::chrono::milliseconds duration(0);
	string ofajlnev = "";

	if (menet != 0) {
		int seconds;		//univerzalis idoegyseg, hogy ha akarjuk latni a mentesfajlt akkor gyorsan lefusson a program
		cout << "Adja meg a standard millisec egyseget (100: valosagos sebesseg, 0: instant): ";
		cin >> seconds;		//100as ertekkel a kod futasi ideje varhatoan ~20 perc legalabb
		duration = std::chrono::milliseconds(seconds);	//ez csak akkor fut le amikor nem tesztelunk
		string ifajlnev;
		cout << "Adja meg a targyakat tartalmazo fajl nevet:";
		cin >> ifajlnev;
		cout << "Adja meg az arveres eredmenyeit eltarolando fajl nevet: ";
		cin >> ofajlnev;

		raktar.beolvas(ifajlnev, menet);
		if (menet > 0)
		{
			for (size_t i = 0; i < raktar.getRaktarSize(); ++i) {
				cout << fixed << setprecision(0) << left << setw(50) << raktar[i].getNev() << ": ";
				cout << fixed << setprecision(0) << left << "€$" << setw(10) << raktar[i].getKikAr() << " - " << right << setw(10) << raktar[i].getTipus() << endl;
			}
			senior.getNextTargy(raktar);
		}
	}

	if (menet == 1)
	{
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
	}

	if (menet == 2) {
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
		Celtudatos v11 = Celtudatos(raktar.getEgyTargy());
		cout << "v11 targya:" << v11.getAzATargy()->getNev() << endl;
		aula.Add(v11.clone());
		Celtudatos v12 = Celtudatos(raktar.getEgyTargy());
		cout << "v12 targya:" << v12.getAzATargy()->getNev() << endl;
		aula.Add(v12.clone());
		Celtudatos v13 = Celtudatos(raktar.getEgyTargy());
		cout << "v13 targya:" << v13.getAzATargy()->getNev() << endl;
		aula.Add(v13.clone());
		Celtudatos v14 = Celtudatos(raktar.getEgyTargy());
		cout << "v14 targya:" << v14.getAzATargy()->getNev() << endl;
		aula.Add(v14.clone());
		Celtudatos v15 = Celtudatos(raktar.getEgyTargy());
		cout << "v15 targya:" << v15.getAzATargy()->getNev() << endl;
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
		Profitert v21 = Profitert();
		aula.Add(v21.clone());
		Profitert v22 = Profitert();
		aula.Add(v22.clone());
		Profitert v23 = Profitert();
		aula.Add(v23.clone());
		Profitert v24 = Profitert();
		aula.Add(v24.clone());
		Profitert v25 = Profitert();
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
	}

	if (menet == 3) {
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
		Celtudatos v11 = Celtudatos(raktar.getEgyTargy());
		cout << "v11 targya:" << v11.getAzATargy()->getNev() << endl;
		aula.Add(v11.clone());
		Celtudatos v12 = Celtudatos(raktar.getEgyTargy());
		cout << "v12 targya:" << v12.getAzATargy()->getNev() << endl;
		aula.Add(v12.clone());
		Celtudatos v13 = Celtudatos(raktar.getEgyTargy());
		cout << "v13 targya:" << v13.getAzATargy()->getNev() << endl;
		aula.Add(v13.clone());
		Celtudatos v14 = Celtudatos(raktar.getEgyTargy());
		cout << "v14 targya:" << v14.getAzATargy()->getNev() << endl;
		aula.Add(v14.clone());
		Celtudatos v15 = Celtudatos(raktar.getEgyTargy());
		cout << "v15 targya:" << v15.getAzATargy()->getNev() << endl;
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
	}

	if (menet > 0) {
		while (raktar.getNincsEladva() > 0)
		{
			senior.eladEgyTargyat(aula, raktar, duration);
		}

		cout << "\nmukszik\n";
		aula.kiir(ofajlnev, raktar);
	}

	return 0;
}