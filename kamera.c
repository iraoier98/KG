#include "kamera.h"
#include <stdlib.h>
#include <GL/glut.h>

/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = PERSPEKTIBADUNA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int mota){
    //Kamerarako memoria eskatu eta kamararen atributu bakoitza hasieratu.
    kamera* k = (kamera*) malloc(sizeof(kamera));
    
    k->kamera_mota = mota;

    point3 kamera_posizioa = {0,0,0};
    k->koord = kamera_posizioa;

    point3 begirada = {0,0,5};
    k->begirada = begirada;
    
    vector3 up = {0,1,0};
    k->up = up;
    
    return k;
}

/**
 * @brief Kamera mota aldatzen du.
 * @param k Mota aldatu nahi diogun kamera.
 */
void kamera_mota_aldatu(kamera* k){
    k->kamera_mota++;
    k->kamera_mota %= 2;
}

/**
 * @brief Kamera kokatzen du.
 * @param k Kokatu nahi dugun kamera.
 */
void kamera_begiratu(kamera* k){
    gluLookAt(k->koord.x + k->begirada.x, k->koord.y + k->begirada.y, k->koord.z + k->begirada.z, k->koord.x, k->koord.y, k->koord.z, k->up.x, k->up.y, k->up.z);
}

