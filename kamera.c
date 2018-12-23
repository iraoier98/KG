#include "kamera.h"
#include "matematikak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define IBIL_MAX_GORA_BEHERA    8


point3 hasierako_pos = {0, 0, 0};
point3 hasierako_look = {0, 0, -1};
vector3 hasierako_up = {0, 1, 0};

/* @brief Kamarara instantzia sortu
 * @return Kamara objektua
 * */
kamera* kamera_sortu(){
    kamera* k = (kamera*) malloc(sizeof(kamera));

    k->kamera_mota = KG_ORTOGRAFIKOA;
    k->fov = 90;
    k->per_pila = pila_sortu();
    k->ibil_pila = pila_sortu();
    k->ibil_gorabehera = 0;

    return k;
}

/* @brief Kamara mota aldatu
 * @param Kamararen objektua
 * */
void kamera_mota_aldatu(kamera* k){
    k->kamera_mota++;
    k->kamera_mota %= 3;
}

/* @brief Kamararen kokapen berria kalkulatzen du
 * @param Kamararen objektua
 * */
void aplikatu_kameraren_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        point3 eye = matrix_dot_point(peek(k->per_pila), hasierako_pos);
        point3 look = matrix_dot_point(peek(k->per_pila), hasierako_look);
        vector3 up = matrix_dot_vector(peek(k->per_pila), hasierako_up);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    }
    else if (k->kamera_mota == KG_IBILTARIA){
        point3 eye = matrix_dot_point(peek(k->ibil_pila), hasierako_pos);
        point3 look = matrix_dot_point(peek(k->ibil_pila), hasierako_look);
        vector3 up = matrix_dot_vector(peek(k->ibil_pila), hasierako_up);
        gluLookAt(eye.x, eye.y, eye.z, look.x, look.y, look.z, up.x, up.y, up.z);
    }
}

/* @brief Kamararen transformazio berria lortzen da, motaren arabera
 * @param Kamararen objektua
 * @param Transformazio mota
 * @param Erreferentzia sistema: globala edo lokala.
 * @param kamararen kokapenaren x aldagaia
 * @param kamararen kokapenaren y aldagaia
 * @param kamararen kokapenaren z aldagaia
 * @return 
 * */

void kamera_transformatu(kamera* k, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z){

    /*  Gogoratu x, y eta z aldagaiek zein tekla sakatu den adierazten dutela.
        Balio hauek routeatu egin behar dira transformatzerakoan dagokion parametroetara, ez da beti (x, y, z) ordena izango!
        Adibidez, Y ardatzeko biraketa egiteko ezker-eskuin teklak daude, x aldagaiari balioa ematen dienak. */

    if (k->kamera_mota == KG_IBILTARIA){

        GLdouble* aurreko_transformazioa = peek(k->ibil_pila);

        if (y != 0){

            /* Y=0 planoan geratzeko, objektuak zein y baliotan bukatuko lukeen kalkulatzen da,
            faktore horrekin mugitzeko Y ardatzean objektua, Y=0 planoan bukatzeko. */
            point3 pos_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_pos);
            point3 look_transformatua = matrix_dot_point(aurreko_transformazioa, hasierako_look);
            double dy = look_transformatua.y - pos_transformatua.y;
            GLdouble* transformazio_berria = matrix_dot_matrix(aurreko_transformazioa, translation_matrix(0, -y * dy, 0));

            transformazio_berria = matrix_dot_matrix(translation_matrix(0, 0, -y), transformazio_berria);
            push(k->ibil_pila, transformazio_berria);
        }else {
            
            if (zeinua(z) * k->ibil_gorabehera < IBIL_MAX_GORA_BEHERA){
                k->ibil_gorabehera += z;
                GLdouble* transformazio_berria;
                if (x != 0){
                    x *= KG_THETA;

                    /* Angelu bertikalak biraketa horizontalean ez afektatzeko, lehenik biraketa bertikala desegiten dugu,
                    gero biraketa horizontala burutu eta azkenik berregin biraketa bertikala */
                    transformazio_berria = matrix_dot_matrix(rotation_matrix(-k->ibil_gorabehera * KG_THETA, 0, 0), aurreko_transformazioa);
                    transformazio_berria = matrix_dot_matrix(rotation_matrix(0, -x, 0), transformazio_berria);
                    transformazio_berria = matrix_dot_matrix(rotation_matrix(k->ibil_gorabehera * KG_THETA, 0, 0), transformazio_berria);
                }else{
                    z *= KG_THETA;
                    transformazio_berria = matrix_dot_matrix(rotation_matrix(z, 0, 0), aurreko_transformazioa);
                }
                push(k->ibil_pila, transformazio_berria);
            }
        }
    }

    else if (k->kamera_mota == KG_PERSPEKTIBAKOA){

        GLdouble* uneko_transformazioa = NULL;
        if (transformazio_mota == KG_TRANSLAZIOA){
            uneko_transformazioa = translation_matrix(x, y, z);
        }
        else if (transformazio_mota == KG_BIRAKETA){
            x *= KG_THETA;
            y *= KG_THETA;
            z *= KG_THETA;
            if (erreferentzia_sistema == KG_TRANSFORMAZIO_LOKALA){
                x *= -1;
                y *= -1;
                z *= -1;
            }
            uneko_transformazioa = rotation_matrix(y, x, z);
        }else{
            printf("Oharra: Kamerak ez du transformazio mota hori onartzen.\n");
            return;
        }

        GLdouble* aurreko_transformazioa = peek(k->per_pila);
        GLdouble* transformazio_berria = NULL;
        if (erreferentzia_sistema == KG_TRANSFORMAZIO_LOKALA){
            transformazio_berria = matrix_dot_matrix(uneko_transformazioa, aurreko_transformazioa);
        }
        else{
            transformazio_berria = matrix_dot_matrix(aurreko_transformazioa, uneko_transformazioa);
        }
        push(k->per_pila, transformazio_berria);
    }

    else{
        printf("Oharra: Kamera ortografikoa ezin daiteke transformatu.\n");
    }

}

/* @brief Kamararen transformazioa desegiten du
 * @param Kamararen objektua
 * */
void desegin_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        pop(k->per_pila);
    }else if (k->kamera_mota == KG_IBILTARIA){
        pop(k->ibil_pila);
    }
}

/* @brief Kamararen transformazioa berregiten du
 * @param Kamararen objektua
 * */
void berregin_transformazioa(kamera* k){
    if (k->kamera_mota == KG_PERSPEKTIBAKOA){
        depop(k->per_pila);
    }else if (k->kamera_mota == KG_IBILTARIA){
        depop(k->ibil_pila);
    }
}