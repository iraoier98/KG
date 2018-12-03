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

    // Ibiltaria
    point3 ibil_pos;
    point3 ibil_look;

    // TODO

} kamera;

//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
kamera* kamera_sortu(int mota);

/* Kamera mota aldatzeko. */
void kamera_mota_aldatu(kamera* k);


/* Kameraren koordenatuak zehazteko. */
void aplikatu_kameraren_transformazioa(kamera* k);

/* Kameraren translazioa */
void kamera_mugitu(kamera* k, double x, double y, double z);
void kamera_biratu(kamera* k, double x, double y, double z);


void kamera_transformatu(kamera* k, int transformazio_mota, double x, double y, double z);



#endif // KAMERA_H