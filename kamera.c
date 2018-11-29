#include "kamera.h"
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = PERSPEKTIBADUNA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int mota){
    //Kamerarako memoria eskatu eta kamararen atributu bakoitza hasieratu.
    kamera* k = (kamera*) malloc(sizeof(kamera));
    
    // k->kamera_mota = mota;

    // point3 kamera_posizioa = {0,0,5};
    // k->koord = kamera_posizioa;

    // point3 begirada = {0,0,0};
    // k->begirada = begirada;
    
    // vector3 up = {0,1,0};
    // k->up = up;

    // k->fov = 90;

    point3 kamera_posizioa = {0, 0, 0};
    k->pos = kamera_posizioa;


    point3 begirada_posizioa = {0, 0, -5};
    k->begirada = begirada_posizioa;

    point3 up_bektorea = {0, 1, 0};
    k->up = up_bektorea;

    point3 angle = {0, 0, 0};
    k->angle = angle;

    k->distantzia = 5;

    k->kamera_mota = 1;

    k->fov = 90;


    
    return k;
}


void mugitu_kamera_eskuinetara(kamera* k){
    k->pos.x += 1;
    k->begirada.x += 1;
}

void mugitu_kamera_ezkerretara(kamera* k){
    k->pos.x -= 1;
    k->begirada.x -= 1;
}

void mugitu_kamera_gora(kamera* k){
    k->pos.y += 1;
    k->begirada.y += 1;
}

void mugitu_kamera_behera(kamera* k){
    k->pos.y -= 1;
    k->begirada.y -= 1;
}

void mugitu_kamera_aurrera(kamera* k){
    k->pos.z += 1;
    k->begirada.z += 1;
}

void mugitu_kamera_atzera(kamera* k){
    k->pos.z -= 1;
    k->begirada.z -= 1;
}


void biratu_kamera_gora(kamera* k){
    k->angle.x += 0.314;
    k->begirada.y = sin(k->angle.x);
    k->begirada.z = cos(k->angle.x);
}

void biratu_kamera_behera(kamera* k){
    k->angle.x -= 0.314;
    k->begirada.y = sin(k->angle.x);
    k->begirada.z = cos(k->angle.x);
}

void biratu_kamera_ezkerretara(kamera* k){
    k->angle.y += 0.314;
    k->begirada.x = sin(k->angle.y);
    k->begirada.z = cos(k->angle.y);
}

void biratu_kamera_eskuinetara(kamera* k){
    k->angle.y -= 0.314;
    k->begirada.x = sin(k->angle.y);
    k->begirada.z = cos(k->angle.y);
}


/**
 * @brief Kamera mota aldatzen du.
 * @param k Mota aldatu nahi diogun kamera.
 */
// void kamera_mota_aldatu(kamera* k){
//     k->kamera_mota++;
//     k->kamera_mota %= 2;
// }

/**
 * @brief Kamera kokatzen du.
 * @param k Kokatu nahi dugun kamera.
 */
void aplikatu_kameraren_transformazioa(kamera* k){
    gluLookAt(k->pos.x, k->pos.y, k->pos.z, k->pos.x + k->distantzia * sin(k->angle.y), k->pos.y + k->distantzia * (sin(k->angle.x)), k->pos.z + k->distantzia * (cos(k->angle.x) + cos(k->angle.y)), 0, 1, 0);
}

