#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "definitions.h"
#include "materiala.h"

#define MAXLINE 200


materiala* materiala_sortu(vector3* amb, vector3* dif, vector3* spec, float shin){

    vector3* ambient = amb;
    vector3* diffuse = dif;
    vector3* specular = spec;
    float shininess = shin;
    
}

/* @brief Fitxategi batetik parametroak esleitzen dizkio material bati
 * @param Fitxategiaren izena
 * @param Materialaren instantzia
 * @return Funtzioaren kodea: ondo egin duen ala erroreren bat egon den.
 * */
int read_material(char * file_name, materiala* mat){

    FILE *mat_file;
    char line[MAXLINE], line_1[MAXLINE], aux[45];
    int k;
    int i, j;
    int values[MAXLINE];

    /* Ka: Ambient colour */
    /* Kd: Diffuse colour */
    /* Ks: Specular colour*/
    /* Ns: Shininess      */

    vector3* ka = 0;
    vector3* kd = 0;
    vector3* ks = 0;
    float ns = 0;
    if ((mat_file = fopen(file_name, "r")) == NULL) return (1);

    fscanf(mat_file, "\n%[^\n]", line);
    sscanf(line, "%lf%lf%lf", &(ka->x),
                    &(ka->y), &(ka->z));

    fscanf(mat_file, "\n%[^\n]", line);
    sscanf(line, "%lf%lf%lf", &(kd->x),
                    &(kd->y), &(kd->z));

    fscanf(mat_file, "\n%[^\n]", line);
    sscanf(line, "%lf%lf%lf", &(ks->x),
                    &(ks->y), &(ks->z));

    fscanf(mat_file, "\n%[^\n]", line);
    sscanf(line, "%f", &ns);

    fclose(mat_file);

    /*
     * Information read is introduced in the structure */

    mat->ambient = &ka;
    mat->diffuse = &kd;
    mat->specular = &ks;
    mat->shininess = ns;

    return (0);
}

/* @brief Materialaren informazioa objektuan kargatzen du
 * @param Materialaren instantzia
 * */
void materiala_kargatu(materiala* m){
    glMaterialfv (GL_FRONT_AND_BACK , GL_AMBIENT , &(GLfloat) {m->ambient->x, m->ambient->y, m->ambient->z,1.0} );
    glMaterialfv (GL_FRONT_AND_BACK , GL_DIFFUSE , &(GLfloat) {m->diffuse->x, m->diffuse->y, m->diffuse->z,1.0});
    glMaterialfv (GL_FRONT_AND_BACK , GL_SPECULAR , &(GLfloat) {m->specular->x, m->specular->y, m->specular->z,1.0});
    glMaterialf (GL_FRONT_AND_BACK , GL_SHININESS , m->shininess);
}