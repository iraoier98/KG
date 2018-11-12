#include "pila.h"
#include "stdlib.h"



pila* pila_sortu(){
    pila* p = (pila*) malloc(sizeof(pila));
    p->tail = NULL;

    GLdouble* I = (GLdouble*) malloc(16 * sizeof(GLdouble));
    I[0]=1;   I[4]=0;   I[8]=0;    I[12]=0;
    I[1]=0;   I[5]=1;   I[9]=0;    I[13]=0;
    I[2]=0;   I[6]=0;   I[10]=1;   I[14]=0;
    I[3]=0;   I[7]=0;   I[11]=0;   I[15]=1;
    push(p, I);
    return p;
}

void push(pila* p, GLdouble* matrizea){
    matrize* sartzeko = (matrize*) malloc(sizeof(matrize));
    sartzeko->matrizea = matrizea;
    sartzeko->hurrengoa = NULL;
    sartzeko->aurrekoa = p->tail;

    if (p->tail != NULL){
        p->tail->hurrengoa = sartzeko;
    }
    p->tail = sartzeko;

}

GLdouble* pop(pila* p){
    GLdouble* result = p->tail->matrizea;
    //  Lehen elementua (I) beti nahi dugu egotea pilan, beraz p->tail inoiz ere ezin da izan NULL.
    if (p->tail->aurrekoa != NULL){
        p->tail = p->tail->aurrekoa;
    }
    return result;
}


GLdouble* peek(pila* p){
    return p->tail->matrizea;
}


void depop(pila* p){
    if (p->tail != NULL && p->tail->hurrengoa != NULL){
        p->tail = p->tail->hurrengoa;
    }
}

