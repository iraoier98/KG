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
    
} argia;

void argiak_hasieratu(argia* a);
void argia_sortu(argia* a);
void argi_mota_aldatu(argia* a);
void argia_kargatu(argia* a, int indizea);
void argiaren_angelua_handitu(argia* a);
void argiaren_angelua_txikitu(argia* a);
void desegin_argiaren_transformazioa(argia* a);
void berregin_argiaren_transformazioa(argia* a);
void argia_transformatu(argia* a, int transformazio_mota, int erreferentzia_sistema, double x, double y, double z);
void transform_light(argia* a, GLdouble* transf, int erreferentzia_sistema);
#endif // ARGIA_H