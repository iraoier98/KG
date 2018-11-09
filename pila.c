#include "pila.h"
#include "stdlib.h"


pila* pila_sortu(){
    pila* p = (pila*) malloc(sizeof(pila));
    p->tail = NULL;
    return p;
}

void push( pila* p, GLdouble* matrizea){
    matrize* sartzeko = (matrize*) malloc(sizeof(matrize));
    sartzeko->matrizea = matrizea;
    sartzeko->hurrengoa = NULL;
    sartzeko->aurrekoa = p->tail;

    if (p->tail == NULL){
        p->tail = sartzeko;
    }
    else{
        p->tail->hurrengoa = sartzeko;
        p->tail = p->tail->hurrengoa;
    }

}

GLdouble* pop( pila* p){
    if (p->tail == NULL){
        return NULL;
    }
    GLdouble* result = p->tail->matrizea;
    p->tail = p->tail->aurrekoa;
    return result;
}


GLdouble* peek( pila* p){
    if (p->tail == NULL){
        return NULL;
    }
    return p->tail->matrizea;
}