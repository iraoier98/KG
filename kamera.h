#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

// DATU-EGITURAK:

/* Perspektiba kamararen inplementazioa */
typedef struct kamera{

    int kamera_mota;

    // Perspektibakoa
    point3 per_pos;
    point3 per_look;
    int per_fov;

    // Ibiltaria
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
void kamera_mugitu(kamera* k, GLdouble* transf);
void kamera_biratu(kamera* k, GLdouble* transf);



#endif // KAMERA_H