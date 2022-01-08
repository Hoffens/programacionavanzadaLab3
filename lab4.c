#include <stdio.h>  /* esenciales para la comunicacion con el programa */
#include <stdlib.h> /* generador aleatorio basico, control de memoria, conversiones basicas, control de procesos */
//#include <math.h> /* funciones matematicas basicas como floor, ceil, log2, etc. */
#include <time.h> /* medicion de tiempo */

typedef struct Bloque
{
    long x;
    long y;
    struct Bloque *pre;  // bloque anterior
    struct Bloque *post; // bloque siguiente
} Bloque;

typedef struct LE // lista enlazada
{
    Bloque *init; // primer elemento de la lista
    Bloque *end;  // ultimo elemento de la lista
    int n;        // largo n de la listaJ
} LE;

void Quicksort_x();
void add_element(LE *lista, long x, long y);
void leer_archivo(LE *lista);
void view_list(LE *lista);
void intercambiar(Bloque *elemento1, Bloque *elemento2, LE *lista);
int main()
{
    LE *Lista;
    
    Lista = (LE *)malloc(sizeof(LE));
    Lista->init = NULL;
    Lista->end = NULL;


    leer_archivo(Lista);
    view_list(Lista);
    intercambiar(Lista->init->post->post,Lista->end->pre->pre,Lista);
    printf("\n\n\n");
    view_list(Lista);

    return 0;
}

void Quicksort_x()
{
}

void leer_archivo(LE *lista)
{

    Bloque *elem1, *elem2;

    char nombreArchivo[30];
    FILE *archivo;

    char bus;
    long x, y;
    int n = 0;

    // printf("Ingrese nombre del archivo (con extension, ejemplo: matriz.txt): ");
    // scanf("%s", nombreArchivo);

    archivo = fopen("archivo1", "r");

    if (archivo == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        while ((bus = fgetc(archivo)) != '\n')
        {
            if (bus != ' ' || bus != '\n')
                n = n * 10 + (int)bus - 48;
        }

        for (int i = 0; i < n; i++)
        {
            x = 0, y = 0;
            while ((bus = fgetc(archivo)) != ' ')
            {
                // if (bus != '\n')
                x = x * 10 + (long)bus - 48;
            }
            while ((bus = fgetc(archivo)) != '\n')
            {
                // if (bus != '\n')
                y = y * 10 + (long)bus - 48;
            }
            add_element(lista, x, y);
        }
    }

    fclose(archivo);
}

void add_element(LE *lista, long x, long y)
{
    // constructor elemento
    Bloque *elemento = (Bloque *)malloc(sizeof(Bloque));
    elemento->x = x;
    elemento->y = y;
    elemento->pre = NULL;
    elemento->post = NULL;

    if (lista->init == NULL)
    {
        lista->init = elemento;
        lista->end = elemento;
        lista->n = 1;
    }
    else
    {

        elemento->pre = lista->end;
        elemento->pre->post = elemento;
        elemento->post = NULL;
        lista->end = elemento;
        lista->n = lista->n + 1;
    }
}

void view_list(LE *lista)
{

    Bloque *aux = lista->init;
    for (int i = 0; i < lista->n; i++)
    {
        printf("(x, y) = (%ld, %ld)\n", aux->x, aux->y);
        aux = aux->post;
    }
}

void intercambiar(Bloque *elemento1, Bloque *elemento2, LE *lista)
{

    Bloque *post1 = elemento1->post;
    Bloque *pre1 = elemento1->pre;

    Bloque *post2 = elemento2->post;
    Bloque *pre2 = elemento2->pre;

    post1->pre = elemento2;
    pre1->post = elemento2;
    elemento2->post = post1;
    elemento2->pre = pre1;

    post2->pre = elemento1;
    pre2->post = elemento1;
    elemento1->post = post2;
    elemento1->pre = pre2;

    if (elemento1->post == NULL)
        lista->end = elemento1;
    if (elemento1->pre == NULL)
        lista->init = elemento1;

    if (elemento2->post == NULL)
        lista->end = elemento2;
    if (elemento2->pre == NULL)
        lista->init = elemento2;
}
