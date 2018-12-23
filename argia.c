#include "argia.h"
#include "matematikak.h"
#include "definitions.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

vector4f hasierako_kokapena = {0.0, 0.0, 0.0, 1.0};
vector4f hasierako_norabidea = {0.0, -1.0, 0.0, 0.0};

/* @brief Argiaren instantzia sortzen du
 * @param indizea: GL_LIGHT0, GL_LIGHT1...
 * @return Argiaren instantzia
 * */
argia* argia_sortu(GLenum indizea){

    argia* a = (argia*) malloc(sizeof(argia));
    a->argi_mota = KG_EGUZKIA;
    a->indizea = indizea;
    a->gaituta = 0;
    a->debug = 0;

    vector4f beltza = {0.0, 0.0, 0.0, 1.0};
    vector4f grisa = {0.3, 0.3, 0.3, 1.0};
    vector4f zuria = {0.7, 0.7, 0.7, 1.0};
    a->ambient = beltza;
    a->diffuse = grisa;
    a->specular = zuria;

    a->constant_atenuation = 1.0;
    a->linear_atenuation = 0.0;
    a->quadratic_atenuation = 0.0;
    a->angelua = 20;
    a->gogortasuna = 0.1;

    a->transformazio_pila = pila_sortu();

    return a;
}

/* @brief Argiaren gaitzen edo desgaitzen du.
 * @param Argiaren instantzia
 * */
void argiaren_egoera_aldatu(argia* a){
    int gaituta = a->gaituta;
    gaituta++;
    gaituta %= 2;

    if (gaituta == 1){
        printf("%d. argia gaituta.\n", a->indizea);
        glEnable(a->indizea);
    }
    else{
        printf("%d. argia desgaituta.\n", a->indizea);
        glDisable(a->indizea);
    }
    a->gaituta = gaituta;
}

/* @brief Argiaren posizioa/norabidea pantailaratzea ahalbiudetzen du.
* @param Argiaren instantzia
* */
void toggle_debug(argia* a){
    a->debug++;
    a->debug %= 2;
}



/* @brief Argi mota aldatzen du
* @param Argiaren instantzia
* */
void argi_mota_aldatu(argia* a){
    a->argi_mota++;
    a->argi_mota %= 3;
    a->transformazio_pila = pila_sortu();
}

/* @brief Uneko MODELVIEW matrizean kargatzen du argia.
 * @param Argiaren instantzia
 * */
void argia_kargatu(argia* a){

    // Desgaituta badago ez egin ezer, bestela, argiaren informazioa kargatu.
    if (a->gaituta == 0){
        return;
    }

    glLightfv(a->indizea, GL_AMBIENT, (float*) &a->ambient);
    glLightfv(a->indizea, GL_DIFFUSE, (float*) &a->diffuse);
    glLightfv(a->indizea, GL_SPECULAR, (float*) &a->specular);

    glLightf(a->indizea, GL_CONSTANT_ATTENUATION, a->constant_atenuation);
    glLightf(a->indizea, GL_LINEAR_ATTENUATION, a->linear_atenuation);
    glLightf(a->indizea, GL_QUADRATIC_ATTENUATION, a->quadratic_atenuation);

    GLdouble* transformazioa = peek(a->transformazio_pila);

    if (a->argi_mota==KG_EGUZKIA){
        vector4f norabidea = matrix_dot_vector4f(transformazioa, hasierako_norabidea);
        glLightfv(a->indizea, GL_POSITION, (float*) &norabidea);
        if (a->debug == 1){
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_LINES);
            glVertex3d(0, 0, 0);
            glVertex3d(-5 * norabidea.x, -5 * norabidea.y, -5 * norabidea.z);
            glEnd();
            glColor3f(0.0, 0.0, 0.0);
        }
    }
    else{
        vector4f kokapena = matrix_dot_vector4f(transformazioa, hasierako_kokapena);
        if (a->argi_mota==KG_BONBILA){
            glLightfv(a->indizea, GL_POSITION, (float*) &kokapena);
            glLightf(a->indizea, GL_SPOT_CUTOFF, 180.0);
            if (a->debug == 1){
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_LINES);
                glVertex3d(kokapena.x + 3, kokapena.y, kokapena.z);
                glVertex3d(kokapena.x - 3, kokapena.y, kokapena.z);
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(kokapena.x, kokapena.y + 3, kokapena.z);
                glVertex3d(kokapena.x, kokapena.y - 3, kokapena.z);
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(kokapena.x, kokapena.y, kokapena.z + 3);
                glVertex3d(kokapena.x, kokapena.y, kokapena.z - 3);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
            }
        }
        else{
            vector4f norabidea = matrix_dot_vector4f(transformazioa, hasierako_norabidea);
            glLightfv(a->indizea, GL_POSITION, (float*) &kokapena);
            glLightfv(a->indizea, GL_SPOT_DIRECTION, (float*) &norabidea);
            glLightf(a->indizea, GL_SPOT_CUTOFF, a->angelua);
            glLightf(a->indizea, GL_SPOT_EXPONENT, a->gogortasuna);
            if (a->debug == 1){
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_LINES);
                glVertex3d(kokapena.x + 3, kokapena.y, kokapena.z);
                glVertex3d(kokapena.x - 3, kokapena.y, kokapena.z);
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(kokapena.x, kokapena.y + 3, kokapena.z);
                glVertex3d(kokapena.x, kokapena.y - 3, kokapena.z);
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(kokapena.x, kokapena.y, kokapena.z + 3);
                glVertex3d(kokapena.x, kokapena.y, kokapena.z - 3);
                glEnd();
                glBegin(GL_LINES);
                glVertex3d(kokapena.x, kokapena.y, kokapena.z);
                glVertex3d(kokapena.x + 5 * norabidea.x, kokapena.y + 5 * norabidea.y, kokapena.z + 5 * norabidea.z);
                glEnd();
                glColor3f(0.0, 0.0, 0.0);
            }
        }
    }
}

/* @brief Fokuaren angelua handitzen du.
 * @param Argiaren instantzia
 * */
void argiaren_angelua_handitu(argia* a){
    if(a->argi_mota == KG_FOKUA && a->angelua < 90){
        a->angelua+=1;
    }
}

/* @brief Fokuaren angelua txikitzen du
 * @param Argiaren instantzia
 * */
void argiaren_angelua_txikitu(argia* a){
    if(a->argi_mota == KG_FOKUA && a->angelua > 10){
        a->angelua-=1;
    }
}

/* @brief Argiaren transformazioa desegiten du
 * @param Argiaren instantzia
 * */
void desegin_argiaren_transformazioa(argia* a){
    pop(a->transformazio_pila);
}

/* @brief Argiaren transformazioa berregiten du
 * @param Argiaren instantzia
 * */
void berregin_argiaren_transformazioa(argia* a){
    depop(a->transformazio_pila);
}


/* @brief Argiaren transformatu berria lortzen du
 * @param Argiaren instantzia
 * @param Transformazio mota.
 * @param x, y, z. Zein tekla sakatu den.
 * */   
void argia_transformatu(argia* a, int transformazio_mota, double x, double y, double z){

    if (a->argi_mota == KG_EGUZKIA && transformazio_mota == KG_TRANSLAZIOA){
        printf("Oharra: Eguzki motako argiek bakarrik biraketak onartzen dituzte.\n");
        return;
    }

    if (a->argi_mota == KG_BONBILA && transformazio_mota == KG_BIRAKETA){
        printf("Oharra: Bonbila motako argiek bakarrik translazioak onartzen dituzte.\n");
        return;
    }

    GLdouble* aurreko_transformazioa = peek(a->transformazio_pila);
    GLdouble* transformazioa = NULL;
    if (transformazio_mota == KG_TRANSLAZIOA){
        transformazioa = matrix_dot_matrix(aurreko_transformazioa, translation_matrix(x, y, z));
    }
    else if (transformazio_mota == KG_BIRAKETA){
        x *= KG_THETA;
        y *= KG_THETA;
        z *= KG_THETA;

        if (a->argi_mota == KG_FOKUA){

            /*  Fokuaren kasuan norabidea bakarrik biratu nahi dugu, beraz lehenik desegin behar dugu posizioa,
                gero biratu eta azkenik berregin posizioa */
            vector4f posizio_transformatua = matrix_dot_vector4f(aurreko_transformazioa, hasierako_kokapena);
            transformazioa = matrix_dot_matrix(aurreko_transformazioa, translation_matrix(-posizio_transformatua.x, -posizio_transformatua.y, -posizio_transformatua.z));
            transformazioa = matrix_dot_matrix(transformazioa, rotation_matrix(-y, -x, -z));
            transformazioa = matrix_dot_matrix(transformazioa, translation_matrix(posizio_transformatua.x, posizio_transformatua.y, posizio_transformatua.z));
        }else{
            transformazioa = matrix_dot_matrix(aurreko_transformazioa, rotation_matrix(-y, -x, -z));
        }

    }
    else{
        printf("Oharra: Argiek ez dute transformazio mota hau onartzen.\n");
        return;
    }

    /* Sartu pilan transformazio berria */
    push(a->transformazio_pila, transformazioa);
}