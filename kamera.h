#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

typedef struct kamera{

    int kamera_mota;				/* ortografikoa, perspektibazioa ala ibiltaria */
    int fov;

    pila* per_pila;

    pila* ibil_pila;
    int ibil_gorabehera;			/* Kamera ibiltariak betikalean biratu duen pausu (step) kopurua gordetzen du */
    
} kamera;


/* Kamera berri bat hasieratzen eta itzultzen du. */
kamera* kamera_sortu();

/* Kamera mota aldatzen du. */
void kamera_mota_aldatu(kamera* k);

/* Kameraren transformatua aplikatzen zaio "bindetatutako" matrizeari (MODELVIEW). */
void aplikatu_kameraren_transformazioa(kamera* k);

/* Erreferentzia-sistema, transformazio mota eta aldaketaren (x, y, z) balioak emanda, kamera transformatzen du */
void kamera_transformatu(kamera* k, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z);

/* Uneko transformazioa desediten du. */
void desegin_transformazioa(kamera* k);

/* Desegindako transformazioak egonez gero, bat berregiten du */
void berregin_transformazioa(kamera* k);


#endif // KAMERA_H