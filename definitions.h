#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>
#include "pila.h"

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Best OpenGL code ever"
#define KG_WINDOW_WIDTH                     1280
#define KG_WINDOW_HEIGHT                    720
#define KG_WINDOW_X                         400
#define KG_WINDOW_Y                         150

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia utsik dago"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"

#define KG_STEP_MOVE                        5.0f
#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
#define KG_STEP_CAMERA_ANGLE                5.0f

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -100
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_FOV_INIT                         100
#define KG_FOV_MIN                          20
#define KG_FOV_MAX                          120
#define KG_ZNEAR                            0.1
#define KG_ZFAR                             1000

#define KG_COL_BACK_R                       1.00f
#define KG_COL_BACK_G                       0.00f
#define KG_COL_BACK_B                       1.00f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   1.00f
#define KG_COL_SELECTED_B                   0.00f

#define KG_COL_NONSELECTED_R                0.00f
#define KG_COL_NONSELECTED_G                0.00f
#define KG_COL_NONSELECTED_B                0.00f

#define KG_COL_X_AXIS_R                     0.0f
#define KG_COL_X_AXIS_G                     0.5f
#define KG_COL_X_AXIS_B                     1.0f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     1.0f
#define KG_COL_Y_AXIS_B                     0.5f

#define KG_COL_Z_AXIS_R                     1.0f
#define KG_COL_Z_AXIS_G                     0.5f
#define KG_COL_Z_AXIS_B                     0.0f

#define KG_MAX_DOUBLE                       10E5

#define KG_PI                               3.14159265358979323846
#define KG_THETA                            KG_PI / 20
#define KG_DELTA                            0.1

#define KG_TRANSLAZIOA                      0
#define KG_BIRAKETA                         1
#define KG_ESKALAKETA                       2
#define KG_ZIZAILAKETA                      3

#define KG_TRANSFORMAZIO_LOKALA             0
#define KG_TRANSFORMAZIO_GLOBALA            1

#define KG_TRANSFORMATU_OBJEKTUA            0
#define KG_TRANSFORMATU_KAMERA              1
#define KG_TRANSFORMATU_ARGIA               2

#define KG_ORTOGRAFIKOA                     0
#define KG_PERSPEKTIBAKOA                   1
#define KG_IBILTARIA                        2

#define KG_EGUZKIA                          0
#define KG_BONBILA                          1
#define KG_FOKUA                            2





/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices         *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
    vector3 normal_vector;             /* normal vector of vertex */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
    vector3 normal_vector;              /* normal vector of face */
} face;


/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d{
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    struct object3d *next;              /* next element in the pile of objects */
    char* filename;                     /* which file contains this object*/
    pila* transformazio_pila;           /* transformazio matrizeen pila */
};

typedef struct object3d object3d;


#endif // DEFINITIONS_H