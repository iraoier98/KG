#ifndef ARGIA_H
#define ARGIA_H

#include "definitions.h"

typedef struct argia{

    GLenum argi_mota;			/* bonbila, eguzki edo foku motakoa */
    int angelua;                /* fokuaren kasuan, argiaren angelua*/

    vector4f kokapena;
    vector4f norabidea;

    float constant_atenuation;
    float linear_atenuation;
    float quadratic_atenuation;

    vector4f ambient;
    vector4f diffuse;
    vector4f specular;

    float gogortasuna;

    pila* bonbila_pila;
    pila* eguzki_pila;
    pila* foku_pila;

    struct object3d *next;
    
} argia;

argia* argia_sortu();
void argi_mota_aldatu(argia* a);
void argia_kargatu(argia* a, int indizea);
void argiaren_angelua_handitu(argia* a);
void argiaren_angelua_txikitu(argia* a);

#endif // ARGIA_H