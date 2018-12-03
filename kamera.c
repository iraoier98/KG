#include "kamera.h"
#include "transformazioak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = KG_PERSPEKTIBAKOA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int kamera_mota){
    kamera* k = (kamera*) malloc(sizeof(kamera));
    k->kamera_mota = kamera_mota;
    k->fov = 90;

    point3 kamera_posizioa = {0, 0, 10};
    point3 origin = {0, 0, 0};

    // Perspektibakoa
    k->per_pos = kamera_posizioa;
    k->per_look = origin;

    // Ibiltaria
    k->ibil_pos = kamera_posizioa;
    k->ibil_look = origin;

    return k;
}


void kamera_mugitu(kamera* k, double x, double y, double z){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        // printf("%f %f %f %f %f %f\n", k->per_pos.x, k->per_pos.y, k->per_pos.z, k->per_look.x, k->per_look.y, k->per_look.z);
        // printf("%f\n", sqrt(pow(k->per_pos.x - k->per_look.x, 2) + pow(k->per_pos.y - k->per_look.y, 2) + pow(k->per_pos.z - k->per_look.z, 2)));
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        // printf("%f %f %f %f %f %f\n", k->ibil_pos.x, k->ibil_pos.y, k->ibil_pos.z, k->ibil_look.x, k->ibil_look.y, k->ibil_look.z);
    }
}



void kamera_biratu(kamera* k, double x, double y, double z){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        translate(&k->per_look, -k->per_pos.x, -k->per_pos.y, -k->per_pos.z);
        rotate(&k->per_look, -x, -y, -z);
        translate(&k->per_look, k->per_pos.x, k->per_pos.y, k->per_pos.z);

        printf("%f %f %f %f %f %f\n", k->per_pos.x, k->per_pos.y, k->per_pos.z, k->per_look.x, k->per_look.y, k->per_look.z);
        printf("%f\n", sqrt(pow(k->per_pos.x - k->per_look.x, 2) + pow(k->per_pos.y - k->per_look.y, 2) + pow(k->per_pos.z - k->per_look.z, 2)));
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        translate(&k->ibil_look, -k->ibil_pos.x, -k->ibil_pos.y, -k->ibil_pos.z);
        rotate(&k->ibil_look, -x, -y, -z);
        translate(&k->ibil_look, k->ibil_pos.x, k->ibil_pos.y, k->ibil_pos.z);

        printf("%f %f %f %f %f %f\n", k->ibil_pos.x, k->ibil_pos.y, k->ibil_pos.z, k->ibil_look.x, k->ibil_look.y, k->ibil_look.z);
        printf("%f\n", sqrt(pow(k->ibil_pos.x - k->ibil_look.x, 2) + pow(k->ibil_pos.y - k->ibil_look.y, 2) + pow(k->ibil_pos.z - k->ibil_look.z, 2)));
    }
}


/**
 * @brief Kamera mota aldatzen du.
 * @param k Mota aldatu nahi diogun kamera.
 */
void kamera_mota_aldatu(kamera* k){
    k->kamera_mota++;
    k->kamera_mota %= 3;
}

/**
 * @brief Kamera kokatzen du.
 * @param k Kokatu nahi dugun kamera.
 */
void aplikatu_kameraren_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        gluLookAt(k->per_pos.x, k->per_pos.y, k->per_pos.z, k->per_look.x, k->per_look.y, k->per_look.z, 0, 1, 0);
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        gluLookAt(k->ibil_pos.x, k->ibil_pos.y, k->ibil_pos.z, k->ibil_look.x, k->ibil_look.y, k->ibil_look.z, 0, 1, 0);
    }
}




void kamera_transformatu(kamera* k, int transformazio_mota, double x, double y, double z){
    if (k->kamera_mota == KG_IBILTARIA){
        if (y != 0){
            double dx = k->ibil_look.x - k->ibil_pos.x;
            double dz = k->ibil_look.z - k->ibil_pos.z;
            double ratio_x = dx / (abs(dx) + abs(dz));
            double ratio_z = dz / (abs(dx) + abs(dz));

            translate(&k->ibil_pos, y * ratio_x, 0, y * ratio_z);
            translate(&k->ibil_look, y * ratio_x, 0, y * ratio_z);
        }else {
            x *= KG_THETA;
            z *= KG_THETA;
            translate(&k->ibil_look, -k->ibil_pos.x, -k->ibil_pos.y, -k->ibil_pos.z);
            rotate(&k->ibil_look, z, -x, 0);
            translate(&k->ibil_look, k->ibil_pos.x, k->ibil_pos.y, k->ibil_pos.z);
        }
    }
    else if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        if (transformazio_mota == KG_TRANSLAZIOA){
            translate(&k->per_pos, x, y, z);
            translate(&k->per_look, x, y, z);
        }
        else if (transformazio_mota == KG_BIRAKETA){
            x *= KG_THETA;
            y *= KG_THETA;
            z *= KG_THETA;
            translate(&k->per_look, -k->per_pos.x, -k->per_pos.y, -k->per_pos.z);
            rotate(&k->per_look, -y, -x, -z);
            translate(&k->per_look, k->per_pos.x, k->per_pos.y, k->per_pos.z);
        }
    }
}