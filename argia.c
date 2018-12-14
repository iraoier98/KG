#include "argia.h"
#include "matematikak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


argia* argia_sortu(){
    argia* a = (argia*) malloc(sizeof(argia));

    a->argi_mota = KG_EGUZKIA;
    a->angelua = 20;

    vector4f kokapena = {0.0, 10.0, 0.0, 1.0};
    a->kokapena =  kokapena;
    vector4f norabidea = {0.0, -1.0, 0.0, 0.0};
    a->norabidea = norabidea;
    vector4f horia = {1.0, 1.0, 0.0, 1.0};
    vector4f grisa = {0.2, 0.2, 0.2, 1.0};
    vector4f zuria = {1.0, 1.0, 1.0, 1.0};

    a->constant_atenuation = 1.0;
    a->linear_atenuation = 0.0;
    a->quadratic_atenuation = 0.0;
    a->ambient = horia;
    a->diffuse = grisa;
    a->specular = zuria;
    a->gogortasuna = 1.0;

    return a;
}

void argi_mota_aldatu(argia* a){
    a->argi_mota++;
    a->argi_mota %= 3;
}

void argia_kargatu(argia* a, int indizea){

    glLightfv(indizea, GL_AMBIENT, (float *) &a->ambient );
    glLightfv(indizea, GL_DIFFUSE, (float *) &a->diffuse );
    glLightfv(indizea, GL_SPECULAR, (float *) &a->specular );

    glLightf(indizea, GL_CONSTANT_ATTENUATION, a->constant_atenuation);
    glLightf(indizea, GL_LINEAR_ATTENUATION, a->linear_atenuation);
    glLightf(indizea, GL_QUADRATIC_ATTENUATION, a->quadratic_atenuation);

    if (a->argi_mota==KG_EGUZKIA){
        vector4f eguzki_posizioa = {0.0, 1.0, 0.0, 0.0};
        glLightfv(indizea, GL_POSITION, (float *) &eguzki_posizioa );
    }
    else{
        if (a->argi_mota==KG_BONBILA){
            glLightfv(indizea, GL_POSITION, (float *) &a->kokapena );
            glLightf(indizea, GL_SPOT_CUTOFF, 180.0);
        }
        else{
            glLightfv(indizea, GL_POSITION, (float *) &a->kokapena );
            glLightfv(indizea, GL_SPOT_DIRECTION, (float *) &a->norabidea );
            glLightf(indizea, GL_SPOT_CUTOFF, a->angelua);
            glLightf(indizea, GL_SPOT_EXPONENT, a->gogortasuna);
        }
    }
}

void argiaren_angelua_handitu(argia* a){
    if(a->angelua < 90){
        a->angelua+=1;
    }
}

void argiaren_angelua_txikitu(argia* a){
    if(a->angelua >0){
        a->angelua-=1;
    }
}