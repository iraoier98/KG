#include <GL/glut.h>
#include <stdio.h>

#include "materiala.h"

/* @brief Fitxategi batetik parametroak esleitzen dizkio material bati
 * @param Fitxategiaren izena
 * @return fitxategiko materiala. Errorea gertatuz gero, shininess balioan -1 itzuliko du.
*/
struct materiala materiala_irakurri(char* file_name){
    FILE* file = fopen(file_name, "r");
    if (file == NULL){
        struct materiala mat;
        mat.shininess = -1;
        return mat;
    }

    char name[128];
    fscanf(file, "#%s\n", name);
    printf("Materiala: %s\n", name);

    float v1, v2, v3;
    fscanf(file, "%f %f %f\n", &v1, &v2, &v3);
    printf("Ambient: %f %f %f\n", v1, v2, v3);
    vector4f ambient = {v1, v2, v3, 1.0};

    fscanf(file, "%f %f %f\n", &v1, &v2, &v3);
    printf("Diffuse: %f %f %f\n", v1, v2, v3);
    vector4f diffuse = {v1, v2, v3, 1.0};

    fscanf(file, "%f %f %f\n", &v1, &v2, &v3);
    printf("Specular: %f %f %f\n", v1, v2, v3);
    vector4f specular = {v1, v2, v3, 1.0};

    fscanf(file, "%f %f %f\n", &v1, &v2, &v3);
    printf("Emission: %f %f %f\n", v1, v2, v3);
    vector4f emission = {v1, v2, v3, 1.0};

    float shininess;
    fscanf(file, "%f\n", &shininess);
    printf("Shininess: %f\n", shininess);

    fclose(file);

    struct materiala mat = {ambient, diffuse, specular, emission, shininess};
    return mat;
}

/* @brief Defektuzko balioak dauzkan materiala sortzen du.
 * @return Materiala, defektuzko balioekin.
*/
struct materiala materiala_default(){
    struct materiala mat;
    vector4f ambient = {0.0, 0.05, 0.05, 1.0};
    vector4f diffuse = {0.4, 0.5, 0.5, 1.0};
    vector4f specular = {0.04, 0.7, 0.7, 1.0};
    vector4f emission = {0.0, 0.0, 0.0, 1.0};
    mat.ambient = ambient;
    mat.diffuse = diffuse;
    mat.specular = specular;
    mat.emission = emission;
    mat.shininess = 0.07;
    return mat;
}



/* @brief Materialaren informazioa objektuan kargatzen du
 * @param Materialaren instantzia
 * */
void materiala_kargatu(struct materiala m){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, (float*) &m.ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, (float*) &m.diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (float*) &m.specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, (float*) &m.emission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shininess);
}