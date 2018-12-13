#include "matematikak.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* ESKALARRAK */

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

double length(vector3 vector){
    return sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
}

vector3 normalize(vector3 vector){
    vector3 result;
    double module = length(vector);
    result.x = vector.x / module;
    result.y = vector.y / module;
    result.z = vector.z / module;
    return result;
}

vector3 substract(vector3 v1, vector3 v2){
    vector3 result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}



vector3 cross_product(vector3 a, vector3 b){
    vector3 normal;
    normal.x = a.y * b.z - a.z * b.y;
    normal.y = a.z * b.x - a.x * b.z;
    normal.z = a.x * b.y - a.y * b.x;

    double module = length(normal);
    return normalize(normal);
}

vector3 sum_vectors(vector3* a, vector3* b){
    vector3 v;

    v.x = a->x + b->x;
    v.y = a->y + b->y;
    v.z = a->z + b->z;

    return v;
}

/* MATRIZEAK */


GLdouble* identity(){
    GLdouble* m = (GLdouble*) malloc(16 * sizeof(GLdouble));
    m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
    m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
    m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
    m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;
    return m;
}

GLdouble* translation_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[12] = x;
    m[13] = y;
    m[14] = z;
    return m;
}

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

GLdouble* scale_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[0] = x;
    m[5] = y;
    m[10] = z;
    return m;
}

GLdouble* shearing_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[4]=x;
    m[9]=y;
    m[2]=z;
    return m;
}



point3 matrix_dot_point(GLdouble* mat, point3 vec){
    point3 result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + mat[12];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + mat[13];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + mat[14];
    return result;
}

vector3 matrix_dot_vector(GLdouble* mat, vector3 vec){
    vector3 result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10];
    return result;
}

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


void printMatrix(GLdouble* matrix){
    int c, d;
    for (c = 0; c < 4; c++) {
        printf("%f %f %f %f\n", matrix[c], matrix[c+4], matrix[c+8], matrix[c+12]);
    }
    printf("\n");
}



/* BESTETARIKOAK */

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

