#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

// DATU-EGITURAK:

/* Perspektiba kamararen inplementazioa */
typedef struct kamera{
    //point3 koord;                       /* eye coordinates,x, y, z */
    //int kamera_mota;                    /* kamera mota */
    //point3 begirada;                    /* begiratzen dugun koordenatuak */
    //vector3 up;                         /* up bektorea */
    //int fov;

    point3 angle;
    point3 pos;
    point3 begirada;
    point3 up;

    int distantzia;
    int kamera_mota;
    int fov;


}kamera;

//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
kamera* kamera_sortu(int mota);

/* Kamera mota aldatzeko. */
//void kamera_mota_aldatu(kamera* k);

/* Kameraren koordenatuak zehazteko. */
void aplikatu_kameraren_transformazioa(kamera* k);

void mugitu_kamera_gora(kamera* k);

void mugitu_kamera_behera(kamera* k);

void mugitu_kamera_ezkerretara(kamera* k);

void mugitu_kamera_eskuinetara(kamera* k);

void mugitu_kamera_aurrera(kamera* k);

void mugitu_kamera_atzera(kamera* k);



void biratu_kamera_gora(kamera* k);

void biratu_kamera_behera(kamera* k);

void biratu_kamera_ezkerretara(kamera* k);

void biratu_kamera_eskuinetara(kamera* k);



#endif // KAMERA_H