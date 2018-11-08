#include <stack.h>

struct pila* createStack(int maxSize){
    struct pila* p = (struct pila*) malloc(sizeof(struct pila));
    p->tail = NULL;
    return p;
}

int isEmpty(struct pila* p){
    return p->tail == NULL;
}

void push(struct pila* p, GLdouble* matrizea){
    struct matrize* sartzeko = (struct matrize*) malloc(sizeof(struct matrize));
    sartzeko->matrizea = matrizea;
    sartzeko->hurrengoa = NULL;
    sartzeko->aurrekoa = p->tail;

    p->tail->hurrengoa = sartzeko;
    p->size++;
}

GLdouble* pop(struct pila* p){
    if (isEmpty == 0){
        GLdouble* result = p->tail->matrizea;
        p->tail = p->tail->aurrekoa;
        return result;
    }
    return NULL;
}

int main(){

    stackMatrizea* s;
    s = createStack(4);
    if(isEmpty(s)){
        printf("Kaixooooo\n");
    }

    GLdouble * m = malloc (sizeof(GLdouble )*16);
    m[0]=1;   m[4]=2;   m[8]  =3;   m[12]=4;
    m[1]=5;   m[5]=6;   m[9]  =7;   m[13]=7;
    m[2]=9;   m[6]=10; m[10]=11; m[14]=12;
    m[3]=13; m[7]=14; m[11]=15; m[15]=16;

    matrizea* matrix;
    matrix->elementua = m;

    push(s,matrix);
    if(!isEmpty(s)){
        printf("Kaixooooo\n");
    }
    pop(s);
    if(isEmpty(s)){
        printf("Kaixooooo\n");
    }

    exit(0);
}