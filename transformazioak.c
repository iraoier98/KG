#include "transformazioak.h"

//#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

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

// GLdouble* rotation_matrix(double factor){
// 	return rotation_matrix(factor, factor, factor);
// }


GLdouble* scale_matrix(double x, double y, double z){
    GLdouble* m = identity();
    m[0] = x;
    m[5] = y;
    m[10] = z;
    return m;
}

// GLdouble* scale_matrix(double factor){
// 	return scale_matrix(factor, factor, factor);
// }



void translate(point3* p, double x, double y, double z){
	GLdouble* mat = translation_matrix(x, y, z);
	point3 translated = matrix_dot_point(mat, *p);
	p->x = translated.x;
	p->y = translated.y;
	p->z = translated.z;
}

void rotate(point3* p, double x, double y, double z){
	GLdouble* mat = rotation_matrix(x, y, z);
	point3 rotated = matrix_dot_point(mat, *p);
	p->x = rotated.x;
	p->y = rotated.y;
	p->z = rotated.z;
}

// void rotate(point3* p, double factor){
// 	rotate(p, factor, factor, factor);
// }

void scale(point3* p, double x, double y, double z){
	GLdouble* mat = scale_matrix(x, y, z);
	point3 scaled = matrix_dot_point(mat, *p);
	p->x = scaled.x;
	p->y = scaled.y;
	p->z = scaled.z;
}

// void scale(point3* p, double factor){
// 	scale(p, factor, factor, factor);
// }


void transform_object(object3d* obj, GLdouble* transf, int global){
	// TODO
}


point3 matrix_dot_point(GLdouble* mat, point3 vec){
    point3 result;
    result.x = vec.x * mat[0] + vec.y * mat[4] + vec.z * mat[8] + mat[12];
    result.y = vec.x * mat[1] + vec.y * mat[5] + vec.z * mat[9] + mat[13];
    result.z = vec.x * mat[2] + vec.y * mat[6] + vec.z * mat[10] + mat[14];
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
