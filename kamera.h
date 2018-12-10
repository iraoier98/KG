#ifndef KAMERA_H
#define KAMERA_H

#include "definitions.h"

typedef struct kamera{

    int kamera_mota;
    int fov;

    // Perspektibakoa
    pila* per_transf_pila;

    // Ibiltaria
    pila* ibil_transf_pila;
    int tortikolis;
    
} kamera;



//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
kamera* kamera_sortu(int mota);

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