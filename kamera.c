#include "kamera.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define DISTANTZIA 5


void transformatuu(GLdouble* matrizea, point3* p1, point3* p2);

/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = KG_PERSPEKTIBAKOA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int kamera_mota){
    kamera* k = (kamera*) malloc(sizeof(kamera));
    k->kamera_mota = kamera_mota;

    point3 kamera_posizioa = {0, 0, -10};
    point3 origin = {0, 0, 0};

    // Perspektibakoa
    k->per_pos = origin;
    k->per_look = kamera_posizioa;
    k->per_fov = 90;

    return k;
}


void kamera_mugitu(kamera* k, GLdouble* transf){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        transformatuu(transf, &k->per_pos, &k->per_look);
    }
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
void aplikatu_kameraren_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        gluLookAt(k->per_pos.x, k->per_pos.y, k->per_pos.z, k->per_look.x, k->per_look.y, k->per_look.z, 0, 1, 0);
    }
}



void transformatuu(GLdouble* matrizea, point3* p1, point3* p2){
    point3 lag1 = {p1->x, p1->y, p1->z};
    p1->x = lag1.x * matrizea[0] + lag1.y * matrizea[4] + lag1.z * matrizea[8] + matrizea[12];
    p1->y = lag1.x * matrizea[1] + lag1.y * matrizea[5] + lag1.z * matrizea[9] + matrizea[13];
    p1->z = lag1.x * matrizea[2] + lag1.y * matrizea[6] + lag1.z * matrizea[10] + matrizea[14];

    if (p2 == NULL) return;
    point3 lag2 = {p2->x, p2->y, p2->z};
    p2->x = lag2.x * matrizea[0] + lag2.y * matrizea[4] + lag2.z * matrizea[8] + matrizea[12];
    p2->y = lag2.x * matrizea[1] + lag2.y * matrizea[5] + lag2.z * matrizea[9] + matrizea[13];
    p2->z = lag2.x * matrizea[2] + lag2.y * matrizea[6] + lag2.z * matrizea[10] + matrizea[14];
}


void biratu2(GLdouble* matrizea, point3* orig, point3* p);
void kamera_biratu(kamera* k, GLdouble* transf){
    biratu2(transf, &k->per_pos, &k->per_look);
}


void biratu2(GLdouble* matrizea, point3* orig, point3* p){
    GLdouble m[16];
    m[0]=1;   m[4]=0;   m[8]=0;    m[12]=-orig->x;
    m[1]=0;   m[5]=1;   m[9]=0;    m[13]=-orig->y;
    m[2]=0;   m[6]=0;   m[10]=1;   m[14]=-orig->z;
    m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;
    transformatuu(m, p, NULL);
    transformatuu(matrizea, p, NULL);
    m[0]=1;   m[4]=0;   m[8]=0;    m[12]=orig->x;
    m[1]=0;   m[5]=1;   m[9]=0;    m[13]=orig->y;
    m[2]=0;   m[6]=0;   m[10]=1;   m[14]=orig->z;
    m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;
    transformatuu(m, p, NULL);
}