#ifndef ARGIA_H
#define ARGIA_H

#include "definitions.h"

typedef struct argia{

    int argi_mota;			   /* bonbila, eguzki edo foku motakoa */
    GLenum indizea;            /* Zein GL_LIGHT baliori dagokion */
    int gaituta;               /* 1 => gaituta, 0 => gaitu gabe */

    int angelua;               /* fokuaren kasuan, argiaren angelua*/

    float constant_atenuation;
    float linear_atenuation;
    float quadratic_atenuation;

    vector4f ambient;
    vector4f diffuse;
    vector4f specular;
    float gogortasuna;

    pila* transformazio_pila;
    
} argia;

argia* argia_sortu(GLenum indizea);

/* Itzalita badago, piztu, eta alderantziz. */
void argiaren_egoera_aldatu(argia* a);
void argi_mota_aldatu(argia* a);
void argia_kargatu(argia* a);
void argiaren_angelua_handitu(argia* a);
void argiaren_angelua_txikitu(argia* a);
void desegin_argiaren_transformazioa(argia* a);
void berregin_argiaren_transformazioa(argia* a);
void argia_transformatu(argia* a, int transformazio_mota, double x, double y, double z);


#endif // ARGIA_H