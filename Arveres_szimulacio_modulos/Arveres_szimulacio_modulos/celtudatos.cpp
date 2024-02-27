
#include "celtudatos.h"

void Celtudatos::megvesz(Szervezo sz, Targy& t) {
	elrak(&t);
	setAktPenz(sz.getElkeltAr());
}