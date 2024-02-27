
#include "gyujto.h"

void Gyujto::megvesz(Szervezo sz, Targy& t) {
	elrak(&t);
	setAktPenz(sz.getElkeltAr());
}