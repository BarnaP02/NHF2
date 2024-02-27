
#include "profitert.h"

void Profitert::megvesz(Szervezo sz, Targy& t)  {
	elrak(&t);
	setAktPenz(sz.getElkeltAr());
	addToProfit(getPenz() * mennyit_er - sz.getElkeltAr());
	cout << "prof: " << getPenz() * mennyit_er - sz.getElkeltAr() << " ennyit er:" << getPenz() * mennyit_er << "\n";
}

