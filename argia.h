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

    GLfloat* ambient;
    GLfloat* diffuse;
    GLfloat* specular;

    GLfloat gogortasuna;

    pila* bonbila_pila;
    pila* eguzki_pila;
    pila* foku_pila;

    struct object3d *next;
    
} argia;

argia* argia_sortu();
void argi_mota_aldatu(argia* a);
void argia_kargatu(argia* a, int light);

#endif // ARGIA_H