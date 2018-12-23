#ifndef MATERIALA_H
#define MATERIALA_H

#include "definitions.h"

/* Emandako fitxategiaren izenetik kargatzen du eta itzultzen du materiala */
struct materiala materiala_irakurri(char* file_name);

/* Defektuzko materiala kargatzen du: CYAN RUBBER */
struct materiala materiala_default();

/* Materiala objektuan kargatzen du */
void materiala_kargatu(struct materiala m);

#endif