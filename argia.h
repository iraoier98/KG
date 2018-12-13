#ifndef ARGIA_H
#define ARGIA_H

#include "definitions.h"

typedef struct argia{

    GLenum argi_mota;			/* bonbila, eguzki edo foku motakoa */
    int angelua;                /* fokuaren kasuan, argiaren angelua*/

    GLfloat* kokapena;
    GLfloat* norabidea;

    float constant_atenuation;
    float linear_atenuation;
    float quadratic_atenuation;

    pila* bonbila_pila;
    pila* eguzki_pila;
    pila* foku_pila;
    
} argia;


#endif // ARGIA_H