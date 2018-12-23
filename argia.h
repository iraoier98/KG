#ifndef ARGIA_H
#define ARGIA_H

#include "definitions.h"

typedef struct argia{

    int argi_mota;			   /* bonbila, eguzki edo foku motakoa */
    GLenum indizea;            /* Zein GL_LIGHT baliori dagokion */
    int gaituta;               /* 1 => gaituta, 0 => gaitu gabe */

    int angelua;               /* fokuaren kasuan, argiaren angelua*/

    /* Argia eta objektuaren arteko distantziaren arabera */
    /* intentsitatea kalkulatzeko koefizienteak zehazten  */
    /* ditu.                                              */
    float constant_atenuation;
    float linear_atenuation;
    float quadratic_atenuation;

    /* Argiaren koloreak zehazteko */

    vector4f ambient;
    vector4f diffuse;
    vector4f specular;
    float gogortasuna;

    pila* transformazio_pila;
    
} argia;

argia* argia_sortu(GLenum indizea);

/* Itzalita badago, piztu, eta alderantziz. */
void argiaren_egoera_aldatu(argia* a);

/* Eguzki, bonbila edo foku moten artean mota aldatzeko */
void argi_mota_aldatu(argia* a);

/* Argia programan kargatzen da */
void argia_kargatu(argia* a);

/* Foku motako argiaren angelua handitzen du */
void argiaren_angelua_handitu(argia* a);

/* Foku motako argiaren angelua txikitzen du */
void argiaren_angelua_txikitu(argia* a);

/* Argiaren aldaketen aurrekoa berreskuratzen du */
void desegin_argiaren_transformazioa(argia* a);

/* Desegindako aldaketa berreskuratzen du */
void berregin_argiaren_transformazioa(argia* a);

/* Argia transformatzeko matrize berria kargatzen du. */
void argia_transformatu(argia* a, int transformazio_mota, double x, double y, double z);


#endif // ARGIA_H