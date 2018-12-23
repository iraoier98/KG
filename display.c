#include "definitions.h"
#include "kamera.h"
#include "argia.h"
#include "materiala.h"

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;
extern int _saretaErakutsi;

extern kamera* _k;
extern argia* _argiak[8];

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(-1 * KG_MAX_DOUBLE, 0, 0);
    glVertex3d(KG_MAX_DOUBLE, 0, 0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,-1 * KG_MAX_DOUBLE, 0);
    glVertex3d(0, KG_MAX_DOUBLE, 0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0, 0, -1 * KG_MAX_DOUBLE);
    glVertex3d(0, 0, KG_MAX_DOUBLE);
    glEnd();
}

/**
 * @brief Sareta marrazteko funtzioa
 */
void draw_sareta(){
    if (_saretaErakutsi){
        glColor3f(0, 0, 0);
        for (double i = -99 ; i < 100; i += 1){
            glBegin(GL_LINES);
            glVertex3d(i, 0, -i);
            glVertex3d(i, 0, i);
            glEnd();

            glBegin(GL_LINES);
            glVertex3d(-i, 0, i);
            glVertex3d(i, 0, i);
            glEnd();
        }
    }
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}


/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;


    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    if (_k->kamera_mota == KG_ORTOGRAFIKOA){
        /*When the window is wider than our original projection plane we extend the plane in the X axis*/
        if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
            /* New width */
            GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
            /* Midpoint in the X axis */
            GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
            /*Definition of the projection*/
            glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
        } else {/* In the opposite situation we extend the Y axis */
            /* New height */
            GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
            /* Midpoint in the Y axis */
            GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
            /*Definition of the projection*/
            glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
        }
    }
    else {
        gluPerspective(_k->fov, _window_ratio, KG_ZNEAR, KG_ZFAR);
    }

    /* Now we start drawing the objects */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    aplikatu_kameraren_transformazioa(_k);

    /* Sareta eta ardatzek euren kolorea izan dezaten */
    glEnable(GL_COLOR_MATERIAL);
    
    /*Ardatzak eta sareta marraztu*/
    draw_axes();
    draw_sareta();


    /* Objektuen kolorea ezartzeko materialak kargatuko ditugu, glColor() erabili beharrean */
    glDisable(GL_COLOR_MATERIAL);

    /* Argiak kargatu */
    for (int i = 0; i < 8; i++){
        argia_kargatu(_argiak[i]);
    }

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        glMultMatrixd(peek(aux_obj->transformazio_pila));
        materiala_kargatu(aux_obj->materiala);

        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);

            //Erpin bakoitzeko, bere aurpegiko bektore normala esleitzen dio.
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                
                glNormal3d(aux_obj->face_table[f].normal_vector.x,
                        aux_obj->face_table[f].normal_vector.y,
                        aux_obj->face_table[f].normal_vector.z);
                
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);

            }
            glEnd();
        }

        glLoadIdentity();
        aplikatu_kameraren_transformazioa(_k);
        aux_obj = aux_obj->next;
    }

    /*Do the actual drawing*/
    glFlush();
}
