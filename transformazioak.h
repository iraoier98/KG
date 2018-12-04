#ifndef TRANSFORMAZIOAK_H
#define TRANSFORMAZIOAK_H

#include "definitions.h"


GLdouble* identity();

GLdouble* translation_matrix(double x, double y, double z);

GLdouble* rotation_matrix(double x, double y, double z);

//GLdouble* rotation_matrix(double factor);

GLdouble* scale_matrix(double x, double y, double z);

//GLdouble* scale_matrix(double factor);



void translate(point3* p, double x, double y, double z);

void rotate(point3* p, double x, double y, double z);

//void rotate(point3* p, double factor);

void scale(point3* p, double x, double y, double z);

//void scale(point3* p, double factor);

void transform_object(object3d* obj, GLdouble* transf, int erreferentzia_sistema);



point3 matrix_dot_point(GLdouble* mat, point3 vec);

GLdouble* matrix_dot_matrix(GLdouble* mat1, GLdouble* mat2);



#endif // TRANSFORMAZIOAK_H