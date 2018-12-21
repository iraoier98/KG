#include "argia.h"
#include "matematikak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


void argia_sortu(argia* a){

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

    a->bonbila_pila = pila_sortu();
    a->eguzki_pila = pila_sortu();
    a->foku_pila = pila_sortu();

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

    
    point3 hasierako_kok = {a->kokapena.x, a->kokapena.y, a->kokapena.z};
    point3 hasierako_nor = {a->norabidea.x, a->norabidea.y, a->norabidea.z};

    GLdouble * transf;
    switch(a->argi_mota){
    case KG_EGUZKIA:
        transf = peek(a->eguzki_pila);
        break;
    case KG_BONBILA:
        transf = peek(a->bonbila_pila);
        break;
    case KG_FOKUA:
        transf = peek(a->foku_pila);
        break;
    }

    point3 kok = matrix_dot_point(transf, hasierako_kok);
    point3 nor = matrix_dot_point(transf, hasierako_nor);

    if (a->argi_mota==KG_EGUZKIA){
        vector4f eguzki_posizioa = {0.0, 1.0, 0.0, 0.0};

        point3 puntua = {eguzki_posizioa.x,eguzki_posizioa.y,eguzki_posizioa.z};

        point3 e_pos = matrix_dot_point(transf,puntua);

        vector4f eguzki_pos = {e_pos.x,e_pos.y,e_pos.z,0.0};

        glLightfv(indizea, GL_POSITION, (float *) &eguzki_pos );
    }
    else{

        vector4f kokapena = {kok.x,kok.y,kok.z,1.0};

        if (a->argi_mota==KG_BONBILA){
            glLightfv(indizea, GL_POSITION, (float *) &kokapena );
            glLightf(indizea, GL_SPOT_CUTOFF, 180.0);
        }
        else{

            vector4f norabidea = {nor.x,kok.y,kok.z,0.0};

            glLightfv(indizea, GL_POSITION, (float *) &kokapena );
            glLightfv(indizea, GL_SPOT_DIRECTION, (float *) &norabidea );
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

void argiak_hasieratu(argia* a){
    for(int i = 0; i < 4; i++){
        argia_sortu(&a[i]);
    }
}

void desegin_argiaren_transformazioa(argia* a){
    if (a->argi_mota == KG_EGUZKIA){
        pop(a->eguzki_pila);
    }else if (a->argi_mota == KG_BONBILA){
        pop(a->bonbila_pila);
    }else{
        pop(a->foku_pila);
    }
}

void berregin_argiaren_transformazioa(argia* a){
    if (a->argi_mota == KG_EGUZKIA){
        depop(a->eguzki_pila);
    }else if (a->argi_mota == KG_BONBILA){
        depop(a->bonbila_pila);
    }else{
        depop(a->foku_pila);
    }
}

void argia_transformatu(argia* a, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z){
    GLdouble* m = NULL;
    switch (transformazio_mota){
    case KG_TRANSLAZIOA:
        m = translation_matrix(x, y, z);
        transform_light(a, m, erreferentzia_sistema);
        break;
    case KG_BIRAKETA:
        x *= KG_THETA;
        y *= KG_THETA;
        z *= KG_THETA;
        m = rotation_matrix(y, x, z);
        transform_light(a, m, erreferentzia_sistema);
        break;
    }
}

void transform_light(argia* a, GLdouble* transf, int erreferentzia_sistema){
    GLdouble* aurreko_transformazioa = NULL;
    switch(a->argi_mota){
    case KG_EGUZKIA:
        aurreko_transformazioa = peek(a->eguzki_pila);
        break;
    case KG_BONBILA:
        aurreko_transformazioa = peek(a->bonbila_pila);
        break;
    case KG_FOKUA:
        aurreko_transformazioa = peek(a->foku_pila);
        break;
    }
    GLdouble* transformatua;
    if (erreferentzia_sistema == KG_TRANSFORMAZIO_LOKALA){
        transformatua = matrix_dot_matrix(transf, aurreko_transformazioa);
    }else{
        transformatua = matrix_dot_matrix(aurreko_transformazioa, transf);
    }
    switch(a->argi_mota){
    case KG_EGUZKIA:
        push(a->eguzki_pila, transformatua);
        break;
    case KG_BONBILA:
        push(a->bonbila_pila, transformatua);
        break;
    case KG_FOKUA:
        push(a->foku_pila, transformatua);
        break;
    }
}