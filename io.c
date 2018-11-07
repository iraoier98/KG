#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

extern object3d * _first_object;
extern object3d * _selected_object;
extern int _saretaErakutsi;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern int transformazio_mota;
extern int erreferentzia_sistema;

GLdouble* m;


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
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
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
    int sarr;
    static int i = 0;
    printf("kqjbribuq\n");

    switch (key) {

    case 'm':
    case 'M':
        transformazio_mota = TRANSLAZIOA;
        break;

    case 'b':
    case 'B':
        transformazio_mota = ERROTAZIOA;
        break;

    case 't':
    case 'T':
        transformazio_mota = ESKALAKETA;
        break;

    case 'g':
    case 'G':
        erreferentzia_sistema = GLOBALA;
        break;

    case 'l':
    case 'L':
        transformazio_mota = LOKALA;
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
        if (_selected_object != NULL){
            printf("%s objektua: ",_selected_object->filename);
            printf("%d erpin eta %d aurpegi.\n", _selected_object->num_vertices, _selected_object->num_faces);
        }
        else{
            printf("Lehenik aukeratu objektu bat.\n");
        }
        break;

    case 's':
    case 'S':
        // Sareta erakutsi / ezkutatu
        _saretaErakutsi = (_saretaErakutsi == 1) ? 0 : 1;
        break;

    case 9: /* <TAB> */
        if (_selected_object != NULL){
            _selected_object = _selected_object->next;
            /*The selection is circular, thus if we move out of the list we go back to the first element*/
            if (_selected_object == 0) _selected_object = _first_object;
        }
        break;

    case 127: /* <SUPR> */
        /*Erasing an object depends on whether it is the first one or not*/
        if (_selected_object != NULL){
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
        }
        break;

    case '-':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
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
        break;

    case '+':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
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
        break;

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        exit(0);
        break;

    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}


void special_keyboard(int keyCode, int x, int y){

    printf("%d\n", keyCode);
    
    switch (keyCode) {

    // case 'a':
    //     printf("Kaizo %d", i);
    //     scanf("oeubfqjb");
    //     i++;
    //     m = (GLdouble*) malloc(16 * sizeof(GLdouble));
    //     m[0]=1;   m[4]=0;   m[8]=0;    m[12]=0;
    //     m[1]=0;   m[5]=1;   m[9]=0;    m[13]=0;
    //     m[2]=0;   m[6]=0;   m[10]=1;   m[14]=0;
    //     m[3]=0;   m[7]=0;   m[11]=0;   m[15]=1;
    //     m[12] = i;
    //     _selected_object->tmatrix = m;
    //     break;

    case KEY_GORA:
        if (transformazio_mota == TRANSLAZIOA){
            //+y
        }
        else if (transformazio_mota == ERROTAZIOA){

        }
        else if (transformazio_mota == ESKALAKETA){

        }
        else{

        }
        break;

    case KEY_BEHERA:
        if (transformazio_mota == TRANSLAZIOA){
            
        }
        else if (transformazio_mota == ERROTAZIOA){

        }
        else if (transformazio_mota == ESKALAKETA){

        }
        else{

        }
        break;

    case KEY_EZKERRA:
        if (transformazio_mota == TRANSLAZIOA){
            
        }
        else if (transformazio_mota == ERROTAZIOA){

        }
        else if (transformazio_mota == ESKALAKETA){

        }
        else{

        }
        break;

    case KEY_ESKUMA:
        if (transformazio_mota == TRANSLAZIOA){
            
        }
        else if (transformazio_mota == ERROTAZIOA){

        }
        else if (transformazio_mota == ESKALAKETA){

        }
        else{

        }
        break;

}