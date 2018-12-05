#include "kamera.h"
#include "transformazioak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


point3 hasierako_pos = {0, 0, 0};
point3 hasierako_look = {0, 0, -1};
vector3 hasierako_up = {0, 1, 0};
int max_tortikolis = 8;


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
    k->tortikolis = 0;

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
        point3 up = matrix_dot_vector(peek(k->per_transf_pila), hasierako_up);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        point3 eye = matrix_dot_point(peek(k->ibil_transf_pila), hasierako_pos);
        point3 look = matrix_dot_point(peek(k->ibil_transf_pila), hasierako_look);
        point3 up = matrix_dot_vector(peek(k->ibil_transf_pila), hasierako_up);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
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

double distance(double x1, double x2, double y1, double y2, double z1, double z2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
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


void kamera_transformatu(kamera* k, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z){

    if (k->kamera_mota == KG_IBILTARIA){ /* Aldaketa lokalak beti */
        GLdouble* aurreko_transformazioa = peek(k->ibil_transf_pila);
        if (y != 0){

            point3 pos_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_pos);
            point3 look_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_look);

            double dy = look_transformatua.y - pos_transformatua.y;

        
            GLdouble* transformazio_berria = matrix_dot_matrix(aurreko_transformazioa, translation_matrix(0, -y * dy, 0));
            transformazio_berria = matrix_dot_matrix(translation_matrix(0, 0, -y), transformazio_berria);
            push(k->ibil_transf_pila, transformazio_berria);
        }else {
            
            if (sign(z) * k->tortikolis < max_tortikolis){
                k->tortikolis += z;
            }
            else{
                return;
            }
            point3 pos_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_pos);
            point3 look_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_look);

            double dx = look_transformatua.x - pos_transformatua.x;
            double dy = look_transformatua.y - pos_transformatua.y;
            double dz = look_transformatua.z - pos_transformatua.z;

            //printf("%f %f %f\n", dx, dy, dz);
            //printMatrixx(translation_matrix(y * dx, -dy, y * dz));
            //printf("%f\n", distance(look_transformatua.x, pos_transformatua.x, look_transformatua.y, pos_transformatua.y, look_transformatua.z, pos_transformatua.z));

            x *= KG_THETA;
            z *= KG_THETA;
            GLdouble* transformazio_berria = matrix_dot_matrix(rotation_matrix(z, -x, 0), aurreko_transformazioa);
            push(k->ibil_transf_pila, transformazio_berria);
        }
    }

    else if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        GLdouble* aurreko_transformazioa = peek(k->per_transf_pila);
        GLdouble* uneko_transformazioa = NULL;

        if (transformazio_mota == KG_TRANSLAZIOA){
            uneko_transformazioa = translation_matrix(x, y, z);
        }
        else if (transformazio_mota == KG_BIRAKETA){
            x *= KG_THETA;
            y *= KG_THETA;
            z *= KG_THETA;
            uneko_transformazioa = rotation_matrix(-y, -x, -z);
        }

        if (uneko_transformazioa != NULL){
            GLdouble* transformazio_berria = NULL;
            if (erreferentzia_sistema == KG_LOKALA){
                transformazio_berria = matrix_dot_matrix(uneko_transformazioa, aurreko_transformazioa);
            }
            else{
                transformazio_berria = matrix_dot_matrix(aurreko_transformazioa, uneko_transformazioa);
            }
            push(k->per_transf_pila, transformazio_berria);
        }
    }

}


void desegin_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        pop(k->per_transf_pila);
    }else if (k->kamera_mota == KG_IBILTARIA){
        pop(k->ibil_transf_pila);
    }
}

void berregin_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        depop(k->per_transf_pila);
    }else if (k->kamera_mota == KG_IBILTARIA){
        depop(k->ibil_transf_pila);
    }
}