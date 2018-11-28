#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

// DATU-EGITURAK:

/* Perspektiba kamararen inplementazioa */
typedef struct kamera{
    point3 koord;                       /* eye coordinates,x, y, z */
    int kamera_mota;                    /* kamera mota */
    point3 begirada;                    /* begiratzen dugun koordenatuak */
    vector3 up;                         /* up bektorea */
    int fov;

}kamera;

//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
kamera* kamera_sortu(int mota);

/* Kamera mota aldatzeko. */
void kamera_mota_aldatu(kamera* k);

/* Kameraren koordenatuak zehazteko. */
void kamera_begiratu(kamera* k);

#endif // KAMERA_H