#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

// DATU-EGITURAK:

/* Perspektiba kamararen inplementazioa */
typedef struct kamera{

    int kamera_mota;
    int fov;

    // Perspektibakoa
    point3 per_pos;
    point3 per_look;
    pila* per_transf_pila;

    // Ibiltaria
    pila* ibil_transf_pila;
    int tortikolis;

    // TODO

} kamera;



//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
kamera* kamera_sortu(int mota);

/* Kamera mota aldatzeko. */
void kamera_mota_aldatu(kamera* k);

/* Kameraren koordenatuak zehazteko. */
void aplikatu_kameraren_transformazioa(kamera* k);

void kamera_transformatu(kamera* k, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z);

void desegin_transformazioa(kamera* k);

void berregin_transformazioa(kamera* k);


#endif // KAMERA_H