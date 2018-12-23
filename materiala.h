#ifndef MATERIALA_H
#define MATERIALA_H

#include "definitions.h"

/* Emandako fitxategiaren izenetik itzultzen du materiala */
struct materiala materiala_irakurri(char* file_name);

/* Defektuzko materiala itzultzen du: CYAN RUBBER */
struct materiala materiala_default();

/* Materiala objektuan kargatzen du uneko MODELVIEW matrizean */
void materiala_kargatu(struct materiala m);

#endif