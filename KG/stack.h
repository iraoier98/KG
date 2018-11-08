#ifndef STACK_H
#define STACK_H

#include <GL/gl.h>

struct matrize{
    GLdouble* matrizea;
    matrize* hurrengoa;
    matrize* aurrekoa;
};

struct pila{
    matrize* tail;
    int size;
};

pila* createStack();
void push(pila p, matrize* matrix);
void pop(pila p);
int isEmpty(pila p);

#endif