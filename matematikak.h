#ifndef MATEMATIKAK_H
#define MATEMATIKAK_H

#include "definitions.h"

/* ESKALARRAK */

/*   1,  x >  0 bada
     0,  x == 0 bada
    -1,  x <  0 bada    */
double zeinua(double x);


/* --------------------BEKTOREAK----------------------- */



/* --------------------MATRIZEAK---------------------- */

/* Identitate matrizea itzultzen du. */
GLdouble* identity();

/* Translazio matrizea itzultzen du. */
GLdouble* translation_matrix(double x, double y, double z);

/* Biraketa matrizea itzultzen du. */
GLdouble* rotation_matrix(double x, double y, double z);

/* Eskalaketa matrizea itzultzen du. */
GLdouble* scale_matrix(double x, double y, double z);

/* Identitate matrizea itzultzen du. Zizailaketa honela burutzen da:
   y x-ren gainean zizailatzen da.
   z y-ren gainean.
   x z-ren gainean. */
GLdouble* shearing_matrix(double x, double y, double z);


/* Emandako puntua emandako matrizearekin transformatu eta puntu berri batean itzultzen du emaitza */ 
point3 matrix_dot_point(GLdouble* mat, point3 vec);

/* Emandako bektorea emandako matrizearekin transformatu eta bektore berri batean itzultzen du emaitza */ 
vector3 matrix_dot_vector(GLdouble* mat, vector3 vec);

/* Matrizeen arteko dot product-a kalkulatzen du */ 
GLdouble* matrix_dot_matrix(GLdouble* mat1, GLdouble* mat2);

/* Emandako matrizea kontsolara pantailaratzen du */
void printMatrix(GLdouble* matrix);


/* ----------------------BESTETARIKOAK---------------------- */

/* Emandako objektua transformatzen du emandako matrizearekin adierazitako erreferentzia_sisteman */
void transform_object(object3d* obj, GLdouble* transf, int erreferentzia_sistema);


#endif // MATEMATIKAK_H