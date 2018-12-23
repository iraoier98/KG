#ifndef ARGIA_H
#define ARGIA_H

#include "definitions.h"

typedef struct argia{

    int argi_mota;			    /* bonbila, eguzki edo foku motakoa */
    GLenum indizea;             /* Zein GL_LIGHT baliori dagokion */
    int gaituta;                /* 1 => gaituta, 0 => gaitu gabe */
    int debug;                  /* Debugeatzeko argiaren posizioa/norabidea erakusteko boolearra, 1 => erakutsi, 0 => ez erakutsi */

    /* Argia eta objektuaren arteko distantziaren arabera */
    /* intentsitatea kalkulatzeko koefizienteak zehazten  */
    /* ditu.                                              */
    float constant_atenuation;
    float linear_atenuation;
    float quadratic_atenuation;

    /* Argiaren koloreak zehazteko */
    vector4f ambient;       /* Argiaren izpiak aurpegiaren normalarekiko paraleloak direnean hartzen duen kolore "oinarri bat" */
    vector4f diffuse;       /* Argiaren kolorea */
    vector4f specular;      /* Distiraren kolorea */
    int angelua;            /* Fokuaren kasuan, argiaren angelua*/
    float gogortasuna;      /* Fokuaren kasuan, argiaren ertzetako "decay"-a. */

    pila* transformazio_pila;
    
} argia;

/* Argi berri bat sortzen du defektuzko balioekin */
argia* argia_sortu(GLenum indizea);

/* Itzalita badago, piztu, eta alderantziz. */
void argiaren_egoera_aldatu(argia* a);

/* Argiaren posizioa/norabidea erakutsi */
void toggle_debug(argia* a);

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