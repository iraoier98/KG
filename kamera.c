#include "kamera.h"
#include "transformazioak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


point3 hasierako_pos = {0, 0, 0};
point3 hasierako_look = {0, 0, -1};


/**
 * @brief Kamera objektua sortzen du.
 * @param mota Kamera mota definitzeko balio du. 1 = ORTOGRAFIKOA, 2 = KG_PERSPEKTIBAKOA, 3 = IBILTARIA
 * @return Kamera objektua bueltatzen du.
 */
kamera* kamera_sortu(int kamera_mota){
    kamera* k = (kamera*) malloc(sizeof(kamera));

    k->kamera_mota = kamera_mota;
    k->fov = 90;
    k->per_transf_pila = pila_sortu();
    k->ibil_transf_pila = pila_sortu();

    return k;
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
        point3 eye = matrix_dot_point(peek(k->per_transf_pila), hasierako_pos);
        point3 look = matrix_dot_point(peek(k->per_transf_pila), hasierako_look);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, 0, 1, 0);
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        point3 eye = matrix_dot_point(peek(k->ibil_transf_pila), hasierako_pos);
        point3 look = matrix_dot_point(peek(k->ibil_transf_pila), hasierako_look);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, 0, 1, 0);
    }
}



void printMatrixx(GLdouble* matrix){
    int c, d;
    for (c = 0; c < 4; c++) {
        printf("%f %f %f %f\n", matrix[c], matrix[c+4], matrix[c+8], matrix[c+12]);
    }
    printf("\n");
}

void printPoint(point3 p){
    printf("%f %f %f\n", p.x, p.y, p.z);
}

double distance(double x1, double x2, double y1, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double sign(double x){
    if (x > 0){
        return 1;
    }
    else if (x == 0){
        return 0;
    }
    else {
        return -1;
    }
}


void kamera_transformatu(kamera* k, int transformazio_mota, double x, double y, double z){
    if (k->kamera_mota == KG_IBILTARIA){
        if (y != 0){

            GLdouble* transformatu_gabe = peek(k->ibil_transf_pila);
            point3 pos_transformatua = matrix_dot_point(transformatu_gabe, hasierako_pos);
            point3 look_transformatua = matrix_dot_point(transformatu_gabe, hasierako_look);

            double dx = look_transformatua.x - pos_transformatua.x;
            double dz = look_transformatua.z - pos_transformatua.z;

            printf("%f %f\n", dx, dz);
            printMatrixx(translation_matrix(y * dx, 0, y * dz));
            //printf("%f\n", distance(look_transformatua.x, pos_transformatua.x, look_transformatua.z, pos_transformatua.z));

            GLdouble* transf_berria = matrix_dot_matrix(translation_matrix(y * dx, 0, y * dz), transformatu_gabe);
            push(k->ibil_transf_pila, transf_berria);
        }else {
            x *= KG_THETA;
            z *= KG_THETA;
            GLdouble* transf_berria = matrix_dot_matrix(rotation_matrix(z, -x, 0), peek(k->ibil_transf_pila));
            push(k->ibil_transf_pila, transf_berria);
        }
    }
    else if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        if (transformazio_mota == KG_TRANSLAZIOA){
            GLdouble* transf_berria = matrix_dot_matrix(peek(k->per_transf_pila), translation_matrix(x, y, z));
            push(k->per_transf_pila, transf_berria);
        }
        else if (transformazio_mota == KG_BIRAKETA){
            x *= KG_THETA;
            y *= KG_THETA;
            z *= KG_THETA;
            GLdouble* transf_berria = matrix_dot_matrix(peek(k->per_transf_pila), rotation_matrix(y, x, z));
            push(k->per_transf_pila, transf_berria);
        }
    }
}