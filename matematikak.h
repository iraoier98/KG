#ifndef MATEMATIKAK_H
#define MATEMATIKAK_H

#include "definitions.h"

/* ESKALARRAK */

/*  1,  x >  0
    0,  x == 0
    -1, x <  0    */
double zeinua(double x);


/* BEKTOREAK */



/* MATRIZEAK */


GLdouble* identity();

GLdouble* translation_matrix(double x, double y, double z);

GLdouble* rotation_matrix(double x, double y, double z);

GLdouble* scale_matrix(double x, double y, double z);


point3 matrix_dot_point(GLdouble* mat, point3 vec);

vector3 matrix_dot_vector(GLdouble* mat, vector3 vec);

GLdouble* matrix_dot_matrix(GLdouble* mat1, GLdouble* mat2);


void printMatrix(GLdouble* matrix);


/* BESTETARIKOAK */

void transform_object(object3d* obj, GLdouble* transf, int erreferentzia_sistema);


#endif // MATEMATIKAK_H