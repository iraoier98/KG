#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kamera.h"

/* Tekla batzuen int kodeak */
#define KG_KEY_GORA                         101
#define KG_KEY_BEHERA                       103
#define KG_KEY_EZKERRA                      100
#define KG_KEY_ESKUMA                       102

#define KG_KEY_REPAG                        104
#define KG_KEY_AVPAG                        105

#define KG_KEY_CTRL_Z                       26
#define KG_KEY_CTRL_S                       19

/* Biraketarako angelua */
#define THETA                               KG_PI / 10

/* Zizailaketarako aldaketa-faktorea */
#define DELTA                               0.1


extern object3d * _first_object;
extern object3d * _selected_object;
extern int _saretaErakutsi;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern int _transformazio_mota;
extern int _erreferentzia_sistema;
extern int _transformazio_targeta;

extern kamera* _k;

/* transformazioentzako matrizearen erazagupena */
GLdouble* m = NULL;


/* a matrizea b-rekin biderkatuta itzultzen du */
GLdouble* mult(GLdouble* a, GLdouble* b);

/* matrix matrizea pantailaratzen du iraulita*/
void printMatrix(GLdouble* matrix);

/* obj objektua tranformatzen du emandako matrizearekin */
void transformatu(object3d* obj, GLdouble* transformazio_matrizea);

/* Transformazio-matrizearen hasieraketa */
void io_init(){
    m = (GLdouble*) malloc(16 * sizeof(GLdouble));
}


/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");

    printf("Egilea: Oier Irazabal eta Txus Calleja\n");
    printf("Data: 2018ko azaroa\n");
    printf("\n\n");

    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t\t Programatik irten \n");
    printf("<CTRL + ->\t\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t\t Bistaratze-eremua txikitu\n");
    printf("<CTRL + S>\t\t Sareta erakutsi\n\n");

    printf("<F>\t\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<SUPR>\t\t\t Hautatutako objektua ezabatu\n");
    printf("<I>\t\t\t Hautatutako objektuari buruzko informazioa pantailaratu\n\n");

    printf("<M>\t\t\t Translazioa aktibatu\n");
    printf("<B>\t\t\t Biraketa aktibatu\n");
    printf("<T>\t\t\t Eskalaketa aktibatu\n");
    printf("<S>\t\t\t Zizailaketa aktibatu\n");
    printf("<->\t\t\t Objektua ardatz guztietan txikitu\n");
    printf("<+>\t\t\t Objektua ardatz guztietan handitu\n\n");

    printf("<L>\t\t\t Transformazioak objektuarekiko erreferentzia_sisteman egin\n");
    printf("<G>\t\t\t Transformazioak _erreferentzia_sistema globalean egin\n");
    printf("<O>\t\t\t Objektua transformatu\n");
    printf("<K>\t\t\t Kamera transformatu\n");
    printf("<CTRL + Z>\t\t Transformazioa desegin\n");
    printf("<CTRL + SHIFT + Z>\t Transformazioa berregin\n");
    printf("\n\n");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */
void keyboard(unsigned char key, int x, int y) {

    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

    switch (key) {

    case 'm':
    case 'M':
        _transformazio_mota = KG_TRANSLAZIOA;
        printf("Translazioa aktibatuta\n");
        break;

    case 'b':
    case 'B':
        _transformazio_mota = KG_BIRAKETA;
        printf("Biraketa aktibatuta\n");
        break;

    case 't':
    case 'T':
        _transformazio_mota = KG_ESKALAKETA;
        printf("Eskalaketa aktibatuta\n");
        break;


    case 's':
    case 'S':
        _transformazio_mota = KG_ZIZAILAKETA;
        printf("Zizailaketa aktibatuta\n");
        break;

    case 'g':
    case 'G':
        _erreferentzia_sistema = KG_GLOBALA;
        printf("Aldaketa globalak aktibatuta\n");
        break;

    case 'l':
    case 'L':
        _erreferentzia_sistema = KG_LOKALA;
        printf("Aldaketa lokalak aktibatuta\n");
        break;


    case 'o':
    case 'O':
        printf("Aldaketak objektuei aplikatuko zaizkie\n");
        _transformazio_targeta = KG_TRANSFORMATU_OBJEKTUA;
        break;


    case 'k':
    case 'K':
        printf("Aldaketak kamerari aplikatuko zaizkio\n");
        _transformazio_targeta = KG_TRANSFORMATU_KAMERA;
        break;


    case 'c':
    case 'C':
        kamera_mota_aldatu(_k);
        break;


    case KG_KEY_CTRL_Z:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (glutGetModifiers() & GLUT_ACTIVE_SHIFT){
            /* Transformazioak berregin */
            depop(_selected_object->transformazio_pila);
        }
        else{
            /* Transformazioak desegin */
            pop(_selected_object->transformazio_pila);
        }
        break;



    case 'f':
    case 'F':
        /*Ask for file*/
        printf("%s", KG_MSSG_SELECT_FILE);
        scanf("%s", fname);
        /*Allocate memory for the structure and read the file*/
        auxiliar_object = (object3d *) malloc(sizeof (object3d));
        read = read_wavefront(fname, auxiliar_object);
        switch (read) {
        /*Errors in the reading*/
        case 1:
            printf("%s: %s\n", fname, KG_MSSG_FILENOTFOUND);
            break;
        case 2:
            printf("%s: %s\n", fname, KG_MSSG_INVALIDFILE);
            break;
        case 3:
            printf("%s: %s\n", fname, KG_MSSG_EMPTYFILE);
            break;
        /*Read OK*/
        case 0:
            /*Insert the new object in the list*/
            auxiliar_object->next = _first_object;
            _first_object = auxiliar_object;
            _selected_object = _first_object;
            printf("%s\n",KG_MSSG_FILEREAD);
            break;
        }
        break;


    case 'i':
    case 'I':
        // Objetuari buruzko informazioa printeatuko du.
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        printf("%s objektua: ",_selected_object->filename);
        printf("%d erpin eta %d aurpegi.\n", _selected_object->num_vertices, _selected_object->num_faces);
        printf("Transformazio-matrizea:\n");
        printMatrix(peek(_selected_object->transformazio_pila));
        break;

    case KG_KEY_CTRL_S:
        // Sareta erakutsi / ezkutatu
        _saretaErakutsi = (_saretaErakutsi == 1) ? 0 : 1;
        break;

    case 9: /* <TAB> */
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }
        _selected_object = _selected_object->next;
        /*The selection is circular, thus if we move out of the list we go back to the first element*/
        if (_selected_object == 0) _selected_object = _first_object;
        break;

    case 127: /* <SUPR> */
        /*Erasing an object depends on whether it is the first one or not*/
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_selected_object == _first_object)
        {
            /*To remove the first object we just set the first as the current's next*/
            _first_object = _first_object->next;
            /*Once updated the pointer to the first object it is save to free the memory*/
            free(_selected_object);
            /*Finally, set the selected to the new first one*/
            _selected_object = _first_object;
        } else {
            /*In this case we need to get the previous element to the one we want to erase*/
            auxiliar_object = _first_object;
            while (auxiliar_object->next != _selected_object)
                auxiliar_object = auxiliar_object->next;
            /*Now we bypass the element to erase*/
            auxiliar_object->next = _selected_object->next;
            /*free the memory*/
            free(_selected_object);
            /*and update the selection*/
            _selected_object = auxiliar_object;
        }
        break;

    case '-':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            if (_k->kamera_mota == KG_ORTOGRAFIKOA){
                /*Increase the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
                he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else if (_k->kamera_mota == KG_PERSPEKTIBAKOA){
                if (_k->per_fov > KG_FOV_MIN){
                    _k->per_fov--;
                }
            }
        }
        else{
            /* Objektuaren eskala txikitu ardatz guztietan*/
            if (_selected_object == NULL){
                printf("Lehenik aukeratu objektu bat.\n");
                break;
            }
            else{
                m[0]=0.9; m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=0.9; m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=0.9; m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }


        }
        break;

    case '+':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            if (_k->kamera_mota == KG_ORTOGRAFIKOA){
                /*Decrease the projection plane; compute the new dimensions*/
                wd=(_ortho_x_max - _ortho_x_min)*KG_STEP_ZOOM;
                he=(_ortho_y_max - _ortho_y_min)*KG_STEP_ZOOM;
                /*In order to avoid moving the center of the plane, we get its coordinates*/
                midx = (_ortho_x_max+_ortho_x_min)/2;
                midy = (_ortho_y_max+_ortho_y_min)/2;
                /*The the new limits are set, keeping the center of the plane*/
                _ortho_x_max = midx + wd/2;
                _ortho_x_min = midx - wd/2;
                _ortho_y_max = midy + he/2;
                _ortho_y_min = midy - he/2;
            }
            else if (_k->kamera_mota == KG_PERSPEKTIBAKOA){
                if (_k->per_fov < KG_FOV_MAX){
                    _k->per_fov++;
                }
            }
        }
        else{
            if (_selected_object == NULL){
                printf("Lehenik aukeratu objektu bat.\n");
                break;
            }

            /* Objektuaren eskala handitu ardatz guztietan*/
            if (_selected_object == NULL){
                printf("Lehenik aukeratu objektu bat.\n");
                break;
            }
            else{
                m[0]=1.1; m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=1.1; m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=1.1; m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        break;

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("Tekla arrunta: %d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}



/**
 * @brief Tekla berezientzako callback funtzioa
 * @param keyCode teklaren kodea
 * @param x saguaren x posizioa
 * @param y saguaren y posizioa
 */
void special_keyboard(int keyCode, int x, int y){

    switch (keyCode) {

    case KG_KEY_GORA:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, 0, 1, 0);
            }
            else{
                //+y
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=1;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, THETA, 0, 0);
            }
            else{
                //+x
                m[0]=1;   m[4]=0;              m[8]=0;              m[12]=0;
                m[1]=0;   m[5]=cos(THETA);     m[9]=sin(THETA);     m[13]=0;
                m[2]=0;   m[6]=-sin(THETA);    m[10]=cos(THETA);    m[14]=0;
                m[3]=0;   m[7]=0;              m[11]=0;             m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                break;
            }
            //-y
            m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=0.9; m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);

        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                break;
            }
            
            //+y
            m[0]=1;    m[4]=0;    m[8]=0;       m[12]=0;
            m[1]=0;    m[5]=1;    m[9]=DELTA;   m[13]=0;
            m[2]=0;    m[6]=0;    m[10]=1;      m[14]=0;
            m[3]=0;    m[7]=0;    m[11]=0;      m[15]=1;
            transformatu(_selected_object, m);

        }
        break;

    case KG_KEY_BEHERA:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, 0, -1, 0);
            }
            else{
                //-y
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=-1;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, -THETA, 0, 0);
            }
            else{
                //-x
                m[0]=1;   m[4]=0;              m[8]=0;              m[12]=0;
                m[1]=0;   m[5]=cos(-THETA);    m[9]=sin(-THETA);    m[13]=0;
                m[2]=0;   m[6]=-sin(-THETA);   m[10]=cos(-THETA);   m[14]=0;
                m[3]=0;   m[7]=0;              m[11]=0;             m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            //+y
            m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1.1; m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);
        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            //-y
            m[0]=1;    m[4]=0;    m[8]=0;       m[12]=0;
            m[1]=0;    m[5]=1;    m[9]=-DELTA;  m[13]=0;
            m[2]=0;    m[6]=0;    m[10]=1;      m[14]=0;
            m[3]=0;    m[7]=0;    m[11]=0;      m[15]=1;

            transformatu(_selected_object, m);

        }
        break;

    case KG_KEY_EZKERRA:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, -1, 0, 0);
            }
            else{
                //-x
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=-1;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, 0, THETA, 0);
            }
            else{
                //-y
                m[0]=cos(-THETA);    m[4]=0;    m[8]=sin(-THETA);    m[12]=0;
                m[1]=0;              m[5]=1;    m[9]=0;              m[13]=0;
                m[2]=-sin(-THETA);   m[6]=0;    m[10]=cos(-THETA);   m[14]=0;
                m[3]=0;              m[7]=0;    m[11]=0;             m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            //+x
            m[0]=1.1; m[4]=0;   m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);
        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            //-x
            m[0]=1;   m[4]=-DELTA;  m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1;       m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;       m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;       m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);

        }
        break;

    case KG_KEY_ESKUMA:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, 1, 0, 0);
            }
            else{
                //+x
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=1;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, 0, -THETA, 0);
            }
            else{
                //+y
                m[0]=cos(THETA);    m[4]=0;    m[8]=sin(THETA);    m[12]=0;
                m[1]=0;             m[5]=1;    m[9]=0;             m[13]=0;
                m[2]=-sin(THETA);   m[6]=0;    m[10]=cos(THETA);   m[14]=0;
                m[3]=0;             m[7]=0;    m[11]=0;            m[15]=1;

            transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            //-x
            m[0]=0.9; m[4]=0;   m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);
        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            //+x
            m[0]=1;   m[4]=DELTA;  m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1;      m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;      m[10]=1;   m[14]=0;
            m[3]=0;   m[7]=0;      m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);

        }
        break;

    case KG_KEY_REPAG:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, 0, 0, -1);
            }
            else{
                //-z
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=-1;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, 0, 0, THETA);
            }
                else{
                //-z
                m[0]=cos(-THETA);    m[4]=sin(-THETA);    m[8]=0;    m[12]=0;
                m[1]=-sin(-THETA);   m[5]=cos(-THETA);    m[9]=0;     m[13]=0;
                m[2]=0;              m[6]=0;             m[10]=1;   m[14]=0;
                m[3]=0;              m[7]=0;             m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            //+z
            m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
            m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=1.1; m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);
        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            //-z
            m[0]=1;       m[4]=0;    m[8]=0;    m[12]=0;
            m[1]=0;       m[5]=1;    m[9]=0;    m[13]=0;
            m[2]=-DELTA;  m[6]=0;    m[10]=1;   m[14]=0;
            m[3]=0;       m[7]=0;    m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);

        }
        break;

    case KG_KEY_AVPAG:
        if (_selected_object == NULL){
            printf("Lehenik aukeratu objektu bat.\n");
            break;
        }

        if (_transformazio_mota == KG_TRANSLAZIOA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_mugitu(_k, 0, 0, 1);
            }
            else{
                //+z
                m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
                m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
                m[2]=0;   m[6]=0;   m[10]=1;   m[14]=1;
                m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_BIRAKETA){
            if (_transformazio_targeta == KG_TRANSFORMATU_KAMERA){
                kamera_biratu(_k, 0, 0, -THETA);
            }
            else{
                //+z
                m[0]=cos(THETA);    m[4]=sin(THETA);    m[8]=0;    m[12]=0;
                m[1]=-sin(THETA);   m[5]=cos(THETA);    m[9]=0;    m[13]=0;
                m[2]=0;             m[6]=0;             m[10]=1;   m[14]=0;
                m[3]=0;             m[7]=0;             m[11]=0;   m[15]=1;

                transformatu(_selected_object, m);
            }
        }
        else if (_transformazio_mota == KG_ESKALAKETA){
            //-z
            m[0]=1;   m[4]=0;   m[8]=0;     m[12]=0;
            m[1]=0;   m[5]=1;   m[9]=0;     m[13]=0;
            m[2]=0;   m[6]=0;   m[10]=0.9;  m[14]=0;
            m[3]=0;   m[7]=0;   m[11]=0;    m[15]=1;

            transformatu(_selected_object, m);
        }
        else if (_transformazio_mota == KG_ZIZAILAKETA){
            //+z
            m[0]=1;       m[4]=0;    m[8]=0;    m[12]=0;
            m[1]=0;       m[5]=1;    m[9]=0;    m[13]=0;
            m[2]=DELTA;   m[6]=0;    m[10]=1;   m[14]=0;
            m[3]=0;       m[7]=0;    m[11]=0;   m[15]=1;

            transformatu(_selected_object, m);
        }
        break;

    default:
        printf("Tekla berezia: %d\n", keyCode);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();

}



void transformatu(object3d* obj, GLdouble* transformazio_matrizea){
    GLdouble* transformatu_gabe = peek(obj->transformazio_pila);
    GLdouble* tranformatua;

    if (_erreferentzia_sistema == KG_LOKALA){
        tranformatua = mult(m, transformatu_gabe);
    }else{
        tranformatua = mult(transformatu_gabe, m);
    }

    push(obj->transformazio_pila, tranformatua);
}

GLdouble* mult(GLdouble* a, GLdouble* b){
    GLdouble* result = (GLdouble*) malloc(16 * sizeof(GLdouble));
    float sum;
    int c, d, _k;
    for (d = 0; d < 4; d++) {
        for (c = 0; c < 4; c++) {
            sum = 0;
            for (_k = 0; _k < 4; _k++) {
                sum += a[d*4 + _k] * b[_k*4 + c];
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
