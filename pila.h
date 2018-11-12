#ifndef STACK_H
#define STACK_H

#include <GL/gl.h>


// DATU-EGITURAK:

/* Matrize baten inplementazioa: balioen matrizea eta zerrendako matrize honen aurrekoa eta ondorengoa. */
struct matrize{
    GLdouble* matrizea;
    struct matrize* hurrengoa;
    struct matrize* aurrekoa;
};
typedef struct matrize matrize;

/* Pilaren inplementazioa: pilako gailurreko elementuaren pointerra. */
struct pila{
    struct matrize* tail;
};
typedef struct pila pila;



//  FUNTZIOAK:

/* Pila berri bat sortzeko funtzioa, identitate matrizea sartuko du pilan. */
pila* pila_sortu();

/* Pilaren gailurrean sartzen du emandako matrizea */
void push(pila* p, GLdouble* matrix);

/* Pilaren gailurreko matrizea despilatzen du. */
GLdouble* pop(pila* p);

/* Pilaren gailurreko matrizea itzultzen du. */
GLdouble* peek(pila* p);

/* Pilatik kendutako azken elementua berriro pilaratuko du */
void depop(pila* p);

#endif