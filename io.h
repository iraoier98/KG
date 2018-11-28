#ifndef IO_H
#define IO_H

/* ASCII teklentzako callback-a */
void keyboard(unsigned char key, int x, int y);

/* non-ASCII teklentzako callback-a */
void special_keyboard(int keyCode, int x, int y);

/* Laguntza idazteko kontsolara */
void print_help();

/* Hasieratak */
void io_init();

#endif // IO_H
