#include <stdio.h> /* esenciales para la comunicacion con el programa */
#include <stdlib.h> /* generador aleatorio basico, control de memoria, conversiones basicas, control de procesos */
//#include <math.h> /* funciones matematicas basicas como floor, ceil, log2, etc. */
#include <time.h> /* medicion de tiempo */


typedef struct Bloque
{
    long x;
    long y;
    struct Bloque *pre;     // bloque anterior
    struct Bloque *post;    // bloque siguiente
} Bloque;

typedef struct LE   // lista enlazada
{
    Bloque *init;   // primer elemento de la lista
    Bloque *end;    // ultimo elemento de la lista
    int n;          // largo n de la lista
} LE;


int main()
{
    return 0;
}