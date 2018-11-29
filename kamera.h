#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

// DATU-EGITURAK:

/* Perspektiba kamararen inplementazioa */
typedef struct kamera{

    int kamera_mota;

    // Perspektibakoa
    point3 per_pos;
    vector3 per_angle;
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
void kamera_mugitu(kamera* k, double delta_x, double delta_y, double delta_z);

/* Kameraren errotazioa */
void kamera_biratu(kamera* k, double delta_x, double delta_y, double delta_z);



#endif // KAMERA_H