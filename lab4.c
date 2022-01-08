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


void Quicksort_x();


int main()
{
    Bloque *p1, *p2, *p3, *p4, *p5;
    LE *Lista;
    long p1x = 5, p1y = 10, p2x = 10, p2y = 5, p3x = -3, p3y = 3, p4x = -4, p4y = 5, p5x = -1, p5y = 0;

    p1 = (Bloque *) malloc(sizeof(Bloque));
    p2 = (Bloque *) malloc(sizeof(Bloque));
    p3 = (Bloque *) malloc(sizeof(Bloque));
    p4 = (Bloque *) malloc(sizeof(Bloque));
    p5 = (Bloque *) malloc(sizeof(Bloque));
    Lista = (LE *) malloc(sizeof(LE));

    p1->x = p1x;
    p1->y = p1y;
    p1->pre = NULL;
    p1->post = p2;


    p2->x = p2x;
    p2->y = p2y;
    p2->pre = p1;
    p2->post = p3;

    
    p3->x = p3x;
    p3->y = p3y;
    p3->pre = p2;
    p3->post = p4;

    p4->x = p4x;
    p4->y = p4y;
    p4->pre = p3;
    p4->post = p5;

    p5->x = p5x;
    p5->y = p5y;
    p5->pre = p4;
    p5->post = NULL;

    Lista->n = 5;
    Lista->init = p1;
    Lista->end = p5;    



    Bloque *aux = Lista->init;
    for (int i = 0; i < Lista->n; i++)
    {
        printf("(x, y) = (%ld, %ld)\n", aux->x, aux->y);
        aux = aux->post;

    }

    return 0;
}

void Quicksort_x()
{

}

void leer_archivo(LE *lista){

    char nombreArchivo[30];
    FILE *archivo;

    char bus;
    long x,y;
    int n = 0;

    printf("Ingrese nombre del archivo (con extension, ejemplo: matriz.txt): ");
    scanf("%s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");

    

    if (archivo == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        while ((bus = fgetc(archivo)) != ' ' || bus!='\n')
        {
            if (bus != ' ' || bus!='\n')
                n = n * 10 + (int)bus - 48;
        }
        lista->n=n;
        

        for (int i=0; i<n; i++)
        {
        while ((bus = fgetc(archivo)) != ' ' )
        {
            // if (bus != '\n')
            x = x * 10 + (long long)bus - 48;
        }
        while ((bus = fgetc(archivo)) != ' ' || bus!='\n')
        {
            // if (bus != '\n')
            y = y * 10 + (long long)bus - 48;
        }
        
        
        }

        
    }
}