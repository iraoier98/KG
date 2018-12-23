#ifndef MATERIALA_H
#define MATERIALA_H

#include "definitions.h"

typedef struct materiala{

    vector3* ambient;
    vector3* diffuse;
    vector3* specular;
    float shininess;
    
} materiala;

/* Materiala sortzeko balio du */
materiala* materiala_sortu(vector3* amb, vector3* dif, vector3* spec, float shin);

/* Materiala estrukturan fitzategi batetik informazioa sartzen du */
int read_material(char * file_name, materiala* mat);

/* Materiala objektuan kargatzen du */
void materiala_kargatu(materiala* m);

#endif