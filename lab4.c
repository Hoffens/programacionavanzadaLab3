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
    int n;        // largo n de la lista
} LE;


// QuickSort en x
void Quicksort_x(Bloque *left, Bloque *right);
Bloque *Dividir_x(Bloque *left, Bloque *right);
// QuickSort en y
void Quicksort_y(Bloque *left, Bloque *right);
Bloque *Dividir_y(Bloque *left, Bloque *right);
// Sublistado de lista que satisface cotas dadas
LE *sublistado(LE *lista, long cota_inf, long cota_sup, int x);
// Agrega un elemento a la lista
void add_element(LE *lista, long x, long y);
// Lee un archivo y carga sus puntos a una lista
void leer_archivo(LE *lista);
// Imprime en pantalla una lista
void view_list(LE *lista);


int main()
{
    LE *Lista;
    Lista = (LE *)malloc(sizeof(LE));
    Lista->init = NULL;
    Lista->end = NULL;


    leer_archivo(Lista);
    view_list(Lista);
    Quicksort_x(Lista->init, Lista->end);
    printf("\n---------------------------\n");
    printf("Lista ordenada en x:\n");
    view_list(Lista);

    /*
    printf("\n---------------------------\n");
    printf("Lista ordenada en y:\n");
    Quicksort_y(Lista->init, Lista->end);
    view_list(Lista);
    */
    printf("\n---------------------------\n");
    printf("Sublistado cotas 10<y<50:\n");
    LE *subListado = sublistado(Lista, 10, 50, 0);
    view_list(subListado);

    return 0;
}


Bloque *Dividir_x(Bloque *left, Bloque *right) 
{
    Bloque *pivot = right;
    Bloque *i = left->pre;
    
    for (Bloque *ptr = left; ptr != right; ptr = ptr->post)
    {
        if (ptr->x <= pivot->x)     // comparamos en coordenada x
        {
            i = (i == NULL ? left : i->post);
            long temp_x = i->x;
            long temp_y = i->y;
            i->x = ptr->x;
            i->y = ptr->y;
            ptr->x = temp_x;
            ptr->y = temp_y;
        }
    }

    i = (i == NULL ? left : i->post);  
    long temp_x = i->x;
    long temp_y = i->y;
    i->x = pivot->x;
    i->y = pivot->y;
    pivot->x = temp_x;
    pivot->y = temp_y;
    return i;
}


Bloque *Dividir_y(Bloque *left, Bloque *right) 
{
    Bloque *pivot = right;
    Bloque *i = left->pre;
    
    for (Bloque *ptr = left; ptr != right; ptr = ptr->post)
    {
        if (ptr->y <= pivot->y)     // comparamos en coordenada y
        {
            i = (i == NULL ? left : i->post);
            long temp_x = i->x;
            long temp_y = i->y;
            i->x = ptr->x;
            i->y = ptr->y;
            ptr->x = temp_x;
            ptr->y = temp_y;
        }
    }

    i = (i == NULL ? left : i->post);  
    long temp_x = i->x;
    long temp_y = i->y;
    i->x = pivot->x;
    i->y = pivot->y;
    pivot->x = temp_x;
    pivot->y = temp_y;
    return i;
}


void Quicksort_x(Bloque *left, Bloque *right)
{
    if (right != NULL && left != right && left != right->post)  
    {
        Bloque *p = Dividir_x(left, right); 
        Quicksort_x(left, p->pre);
        Quicksort_x(p->post, right);
    }
}


void Quicksort_y(Bloque *left, Bloque *right)
{
    if (right != NULL && left != right && left != right->post)  
    {
        Bloque *p = Dividir_y(left, right); 
        Quicksort_y(left, p->pre);
        Quicksort_y(p->post, right);
    }
}


LE *sublistado(LE *lista, long cota_inf, long cota_sup, int x)
{   
    LE *subListado;
    subListado = (LE *)malloc(sizeof(LE));
    subListado->init = NULL;
    subListado->end = NULL;
    Bloque *elem = lista->init;

    for (int i = 0; i < lista->n; i++)
    {

        if (x == 1 && elem->x >= cota_inf && elem->x <= cota_sup)  
        {
            add_element(subListado, elem->x, elem->y);
        }
        else if (x == 0 && elem->y >= cota_inf && elem->y <= cota_sup)
        {
            add_element(subListado, elem->x, elem->y);
        }
        
        elem = elem->post;
    }
    return subListado;
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

    archivo = fopen("archivo2.txt", "r");

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
