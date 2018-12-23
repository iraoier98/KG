#include "matematikak.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* ESKALARRAK */

/* @brief Zenbakiaren zeinua bueltatzen du
 * @param Zenbakia
 * @return Zenbakiaren zeinua
*/
double zeinua(double x){
    if (x > 0){
        return 1;
    }
    else if (x == 0){
        return 0;
    }
    else {
        return -1;
    }
}


/* BEKTOREAK */

/* @brief Bektore baten luzera kalulatzen du
 * @param Bektorea
 * @return Bektorearen luzera
*/
double length(vector3 vector){
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

/* @brief Bektorea normalizatzen du
 * @param Bektorea
 * @return Bektore normalizatua bueltatzen du
*/
vector3 normalize(vector3 vector){
    vector3 result;
    double module = length(vector);
    result.x = vector.x / module;
    result.y = vector.y / module;
    result.z = vector.z / module;
    return result;
}

/* @brief Bi bektoreen arteko kenketa bueltatuko du
 * @param Bektore bat
 * @param Beste bektore bat
 * @return Bi bektoreen arteko kenketa.
*/
vector3 substract(vector3 v1, vector3 v2){
    vector3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}


/* @brief Bi bektore emanda, hauen bektore normala bueltatuko du
 * @param Bektore bat
 * @param Beste bektore bat
 * @return Bi bektoreen normala bueltatzen du
*/
vector3 cross_product(vector3 a, vector3 b){
    vector3 normal;
    normal.x = a.y * b.z - a.z * b.y;
    normal.y = a.z * b.x - a.x * b.z;
    normal.z = a.x * b.y - a.y * b.x;

    double module = length(normal);
    return normalize(normal);
}

/* @brief Bi bektoreen gehiketa egiten du
 * @param Bektore bat
 * @param Beste bektore bat
 * @return Bi bektoreen arteko gehiketa
*/
vector3 sum_vectors(vector3* a, vector3* b){
    vector3 v;

    v.x = a->x + b->x;
    v.y = a->y + b->y;
    v.z = a->z + b->z;

    return v;
}

/* MATRIZEAK */

/* @brief Identitate matrizea bueltatzen du
 * @return Identitate matrizea
*/
GLdouble* identity(){
    GLdouble* m = (GLdouble*) malloc(16 * sizeof(GLdouble));
    m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
    m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
    m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
    m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;
    return m;
}

/* @brief Puntu bat emanda, 4 x 4 ko translazio matrizea bueltatzen du
 * @param x koordenatua
 * @param y koordenatua
 * @param z koordenatua
 * @return Translazio matrizea
*/
GLdouble* translation_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[12] = x;
    m[13] = y;
    m[14] = z;
    return m;
}

/* @brief Puntu bat emanda, 4 x 4 ko errotazio matrizea bueltatuko du.
 * @param x koordenatua
 * @param y koordenatua
 * @param z koordenatua
 * @return Errotazio matrizea
*/
GLdouble* rotation_matrix(double x, double y, double z){
    GLdouble* m1 = identity();
    GLdouble m[16];

    m[0]=1;   m[4]=0;          m[8]=0;          m[12]=0;
    m[1]=0;   m[5]=cos(x);     m[9]=sin(x);     m[13]=0;
    m[2]=0;   m[6]=-sin(x);    m[10]=cos(x);    m[14]=0;
    m[3]=0;   m[7]=0;          m[11]=0;         m[15]=1;
    m1 = matrix_dot_matrix(m1, m);

    m[0]=cos(y);    m[4]=0;    m[8]=sin(y);    m[12]=0;
    m[1]=0;         m[5]=1;    m[9]=0;         m[13]=0;
    m[2]=-sin(y);   m[6]=0;    m[10]=cos(y);   m[14]=0;
    m[3]=0;         m[7]=0;    m[11]=0;        m[15]=1;
    m1 = matrix_dot_matrix(m1, m);

    m[0]=cos(z);    m[4]=sin(z);    m[8]=0;    m[12]=0;
    m[1]=-sin(z);   m[5]=cos(z);    m[9]=0;    m[13]=0;
    m[2]=0;         m[6]=0;         m[10]=1;   m[14]=0;
    m[3]=0;         m[7]=0;         m[11]=0;   m[15]=1;
    m1 = matrix_dot_matrix(m1, m);

    return m1;
}

/* @brief Puntu bat emanda, 4 x 4 ko eskalaketa matrizea bueltatuko du.
 * @param x koordenatua
 * @param y koordenatua
 * @param z koordenatua
 * @return Eskalaketa matrizea
*/
GLdouble* scale_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[0] = x;
    m[5] = y;
    m[10] = z;
    return m;
}

/* @brief Puntu bat emanda, 4 x 4 ko zizailaketa matrizea bueltatuko du.
 * @param x koordenatua
 * @param y koordenatua
 * @param z koordenatua
 * @return Zizailaketa matrizea
*/
GLdouble* shearing_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[4]=x;
    m[9]=y;
    m[2]=z;
    return m;
}


/* @brief Puntu bat emanda, 3 x 4 ko matrizearekin biderkatzen du.
 * @param Matrizea
 * @param Puntua
 * @return Puntu berria
*/
point3 matrix_dot_point(GLdouble* mat, point3 vec){
    point3 result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + mat[12];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + mat[13];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + mat[14];
    return result;
}

/* @brief 3 elementuko bektorea bat emanda, 3 x 3 ko matrizearekin biderkatzen du.
 * @param Matrizea
 * @param Bektorea
 * @return Bektore berria
*/
vector3 matrix_dot_vector(GLdouble* mat, vector3 vec){
    vector3 result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10];
    return result;
}


/* @brief 4 elementuko bektorea bat emanda, 4 x 4 ko matrizearekin biderkatzen du.
 * @param Matrizea
 * @param Bektorea
 * @return Bektore berria
*/
vector4f matrix_dot_vector4f(GLdouble* mat, vector4f vec){
    vector4f result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8]  + vec.t * mat[12];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9]  + vec.t * mat[13];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + vec.t * mat[14];
    result.t = vec.x * mat[3] + vec.y * mat[7] + vec.z * mat[11] + vec.t * mat[15];
    return result;
}


/* @brief 4 x 4ko bi matrizeen arteko biderketa.
 * @param Matrizea
 * @param Matrizea
 * @return Matrize berria
*/
GLdouble* matrix_dot_matrix(GLdouble* mat1, GLdouble* mat2){
    GLdouble* result = identity();
    float sum;
    int c, d, _k;
    for (d = 0; d < 4; d++) {
        for (c = 0; c < 4; c++) {
            sum = 0;
            for (_k = 0; _k < 4; _k++) {
                sum += mat1[d*4 + _k] * mat2[_k*4 + c];
            }

            result[d*4 + c] = sum;
        }
    }
    return result;
}

/* @brief Matrizea stdout-tik printeatuko du.
 * @param Matrizea
 * @oharra bakarrik erabiltzen da debugeatzeko.
*/
void printMatrix(GLdouble* matrix){
    int c, d;
    for (c = 0; c < 4; c++) {
        printf("%f %f %f %f\n", matrix[c], matrix[c+4], matrix[c+8], matrix[c+12]);
    }
    printf("\n");
}



/* BESTETARIKOAK */

/* @brief Objektuaren transformazio matrizea berrirarekin biderkatzen eta sartzen du.
 * @param Objektua
 * @param Transformazio matrizea
 * @param Erreferentzia sistema: lokala edo globala
*/
void transform_object(object3d* obj, GLdouble* transf, int erreferentzia_sistema){
    GLdouble* aurreko_transformazioa = peek(obj->transformazio_pila);
    GLdouble* transformatua;
    if (erreferentzia_sistema == KG_TRANSFORMAZIO_LOKALA){
        transformatua = matrix_dot_matrix(transf, aurreko_transformazioa);
    }else{
        transformatua = matrix_dot_matrix(aurreko_transformazioa, transf);
    }
    push(obj->transformazio_pila, transformatua);
}

