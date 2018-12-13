#include "argia.h"
#include "matematikak.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>


argia* argia_sortu(){
    argia* a = (argia*) malloc(sizeof(argia));

    a->argi_mota = KG_EGUZKIA;
    a->angelua = 20;

    GLfloat kokapena [4] = {0.0, 10.0, 0.0, 1.0};
    a->kokapena =  kokapena;
    GLfloat norabidea [4] = {1.0, 0.0, 0.0, 1.0};
    a->norabidea = norabidea;
    a->constant_atenuation = 1.0;
    GLfloat horia [4] = {0.0, 1.0, 1.0,  1.0};
    GLfloat grisa [4] = {0.2, 0.2, 0.2,  1.0};
    GLfloat zuria [4] = {1.0, 1.0, 1.0,  1.0};
    a->linear_atenuation = 0.0;
    a->quadratic_atenuation = 1.0;
    a->ambient = horia;
    a->diffuse = grisa;
    a->specular = zuria;
    a->gogortasuna = 1.0;

    return a;
}

void argi_mota_aldatu(argia* a){
    a->argi_mota++;
    a->argi_mota %= 3;
}

void argia_kargatu(argia* a, int light){
    glLightfv (light , GL_AMBIENT , a->ambient );
    glLightfv (light , GL_DIFFUSE , a->diffuse );
    glLightfv (light , GL_SPECULAR , a->specular );

    glLightf (GL_LIGHT0 , GL_CONSTANT_ATTENUATION , a->constant_atenuation);
    glLightf (GL_LIGHT0 , GL_LINEAR_ATTENUATION , a->linear_atenuation);
    glLightf (GL_LIGHT0 , GL_QUADRATIC_ATTENUATION , a->quadratic_atenuation);

    if (a->argi_mota==KG_EGUZKIA){
        glLightfv (light , GL_POSITION , a->norabidea );
    }
    else{
        if (a->argi_mota==KG_BONBILA){
            glLightfv (light , GL_POSITION , a->kokapena );
            glLightf (light , GL_SPOT_CUTOFF , a->angelua);
        }
        else{
            glLightfv (GL_LIGHT0 , GL_POSITION , a->kokapena );
            glLightfv (GL_LIGHT0 , GL_SPOT_DIRECTION , a->norabidea );
            glLightf (GL_LIGHT0 , GL_SPOT_CUTOFF , 180.0); //Eguzki motak beti izango du 180ºko angelua.
            glLightf (GL_LIGHT0 , GL_SPOT_EXPONENT , a->gogortasuna);
        }
    }
}