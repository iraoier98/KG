#include "kamera.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define DISTANTZIA 5


vector3 bektore_unitarioa(vector3 bektorea){
    double modulua = sqrt(pow(bektorea.x, 2) + pow(bektorea.y, 2) + pow(bektorea.z, 2));
    vector3 emaitza = {bektorea.x / modulua, bektorea.y / modulua, bektorea.z / modulua};
    return emaitza;
}



/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = KG_PERSPEKTIBAKOA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int kamera_mota){
    kamera* k = (kamera*) malloc(sizeof(kamera));
    k->kamera_mota = kamera_mota;

    point3 kamera_posizioa = {0, 0, 10};
    vector3 angle = {0, 0, 0};//{0, KG_PI * 3 / 2, KG_PI / 2};

    // Perspektibakoa
    k->per_pos = kamera_posizioa;
    k->per_angle = angle;
    k->per_fov = 90;

    return k;
}


void kamera_mugitu(kamera* k, double delta_x, double delta_y, double delta_z){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        k->per_pos.x += delta_x;
        k->per_pos.y += delta_y;
        k->per_pos.z += delta_z;
    }
}


void kamera_biratu(kamera* k, double delta_x, double delta_y, double delta_z){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        k->per_angle.x += delta_x * 360 / (2*KG_PI);
        k->per_angle.y += delta_y * 360 / (2*KG_PI);
        k->per_angle.z += delta_z * 360 / (2*KG_PI);

        // printf("%f %f %f\n", k->per_angle.x, k->per_angle.y, k->per_angle.z);

        // printf("(%f %f) (%f %f) (%f %f)\n", 
        //     k->per_pos.x, k->per_pos.x + DISTANTZIA * (-sin(k->per_angle.y) - sin(k->per_angle.z)),
        //     k->per_pos.y, k->per_pos.y + DISTANTZIA * (sin(k->per_angle.x) + cos(k->per_angle.z)),
        //     k->per_pos.z, k->per_pos.z + DISTANTZIA * (-cos(k->per_angle.x) - cos(k->per_angle.y)));

        // printf("Distantzia: %f\n", sqrt(pow(k->per_pos.x - (k->per_pos.x + DISTANTZIA * (-sin(k->per_angle.y) - sin(k->per_angle.z))), 2) + 
        //     pow(k->per_pos.y - (k->per_pos.y + DISTANTZIA * (sin(k->per_angle.x) + cos(k->per_angle.z))), 2) + 
        //     pow(k->per_pos.z - (k->per_pos.z + DISTANTZIA * (-cos(k->per_angle.x) - cos(k->per_angle.y))), 2)));
    }
}


/**
 * @brief Kamera mota aldatzen du.
 * @param k Mota aldatu nahi diogun kamera.
 */
void kamera_mota_aldatu(kamera* k){
    k->kamera_mota++;
    k->kamera_mota %= 2;


    // vector3 begirada = {-sin(k->per_angle.y) - sin(k->per_angle.z), sin(k->per_angle.x) + cos(k->per_angle.z), -cos(k->per_angle.x) - cos(k->per_angle.y)};

    // printf("%f %f %f\n", begirada.x, begirada.y, begirada.z);

    // printf("(%f %f) (%f %f) (%f %f)\n", 
    //     k->per_pos.x, k->per_pos.x + DISTANTZIA * (-sin(k->per_angle.y) - sin(k->per_angle.z)),
    //     k->per_pos.y, k->per_pos.y + DISTANTZIA * (sin(k->per_angle.x) + cos(k->per_angle.z)),
    //     k->per_pos.z, k->per_pos.z + DISTANTZIA * (-cos(k->per_angle.x) - cos(k->per_angle.y)));

    // printf("Distantzia: %f\n", sqrt(pow(k->per_pos.x - (k->per_pos.x + DISTANTZIA * (-sin(k->per_angle.y) - sin(k->per_angle.z))), 2) + 
    //     pow(k->per_pos.y - (k->per_pos.y + DISTANTZIA * (sin(k->per_angle.x) + cos(k->per_angle.z))), 2) + 
    //     pow(k->per_pos.z - (k->per_pos.z + DISTANTZIA * (-cos(k->per_angle.x) - cos(k->per_angle.y))), 2)));
}

/**
 * @brief Kamera kokatzen du.
 * @param k Kokatu nahi dugun kamera.
 */
void aplikatu_kameraren_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        //vector3 begirada = {-sin(k->per_angle.y) - sin(k->per_angle.z), sin(k->per_angle.x) + cos(k->per_angle.z), -cos(k->per_angle.x) - cos(k->per_angle.y)};
        //begirada = bektore_unitarioa(begirada);
        //gluLookAt(k->per_pos.x, k->per_pos.y, k->per_pos.z, k->per_pos.x + DISTANTZIA * begirada.x, k->per_pos.y + DISTANTZIA * begirada.y, k->per_pos.z + DISTANTZIA * begirada.z, 0, 1, 0);
        // glPushMatrix();
        glRotated(-k->per_angle.x, 1, 0, 0);
        glRotated(-k->per_angle.y, 0, 1, 0);
        glRotated(-k->per_angle.z, 0, 0, 1);
        glTranslated(-k->per_pos.x, -k->per_pos.y, -k->per_pos.z);
        // glPopMatrix();

    }
}



