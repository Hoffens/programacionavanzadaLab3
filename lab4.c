#include <stdio.h>  /* esenciales para la comunicacion con el programa */
#include <stdlib.h> /* generador aleatorio basico, control de memoria, conversiones basicas, control de procesos */
//#include <math.h> /* funciones matematicas basicas como floor, ceil, log2, etc. */
#include <time.h> /* medicion de tiempo */

#define NMAX 10000000

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
// Genera un punto aleatorio y lo agrega a una lista
void add_random_element(LE *lista);
// Lee un archivo y carga sus puntos a una lista
int leer_archivo(LE *lista);
// Imprime en pantalla una lista
void view_list(LE *lista);


int main()
{
    // falta liberar memoria
    srand(time(NULL));
    int i, sel, isOk, n;
    long cota_inf, cota_sup;
    double t0, t1, time1;
    LE *Lista;
    Lista = (LE *)malloc(sizeof(LE));
    Lista->init = NULL;
    Lista->end = NULL;
    
    printf("Elegir el tipo de operacion a ejecutar:\n");
    printf("1) Leer puntos desde archivo.\n");
    printf("2) Generar puntos aleatorios.\n");
    printf("3) Ordenar listado de puntos por coordenada x.\n");
    printf("4) Ordenar listado de puntos por coordenada y.\n");
    printf("5) Sublistado que satisface cotas en coordenada x.\n");
    printf("6) Sublistado que satisface cotas en coordenada y.\n");
    printf("9) Salir del programa.\n");
    sel = 0;

    do
    {   
        printf("Seleccion (0 para repetir el menu): ");
        scanf("%d",&sel);
        switch (sel)
        {   
            case 0:
                printf("Elegir el tipo de operacion a ejecutar:\n");
                printf("1) Leer puntos desde archivo.\n");
                printf("2) Generar puntos aleatorios.\n");
                printf("3) Ordenar listado de puntos por coordenada x.\n");
                printf("4) Ordenar listado de puntos por coordenada y.\n");
                printf("5) Sublistado que satisface cotas en coordenada x.\n");
                printf("6) Sublistado que satisface cotas en coordenada y.\n");
                printf("9) Salir del programa.\n");
                break;
            case 1:
                do 
                {   
                    printf("-----------------------------------------------\n");
                    int isOk = leer_archivo(Lista); 
                } while (isOk == 1);
                break;
            case 2:
                printf("\nIngrese cantidad de puntos a generar: ");
                scanf("%ld", &n);
                printf("Generando...\n");

                Lista = (LE *)malloc(sizeof(LE));
                Lista->init = NULL;
                Lista->end = NULL;

                for (int i = 0; i < n; i++)
                {
                    add_random_element(Lista);
                }

                printf("Puntos generados correctamente.\n");

                if (Lista->n <= 100)
                {
                    printf("Listado: \n");
                    view_list(Lista);
                }
                break;
            case 3:
                if (Lista != NULL && Lista->init != NULL)
                {   
                    printf("\nResolviendo...\n"); 

                    t0 = clock(); // Inicio medición de tiempo
                    Quicksort_x(Lista->init, Lista->end);
                    t1 = clock(); // Fin medición de tiempo

                    if (Lista->n <= 100)
                    {
                        printf("Listado ordenado en coordenada x: \n");
                        view_list(Lista);
                    }
                    printf("\nFINALIZADO, TIEMPO TOTAL EN SEGUNDOS: %f  \n", ((t1 - t0) / CLOCKS_PER_SEC)); 
                }
                else
                {
                    printf("Error: primero debe generar un listado de puntos o leerlo desde un archivo.\n");
                }
                break;
            case 4:
                if (Lista != NULL && Lista->init != NULL)
                {   
                    printf("\nResolviendo...\n"); 

                    t0 = clock(); // Inicio medición de tiempo
                    Quicksort_y(Lista->init, Lista->end);
                    t1 = clock(); // Fin medición de tiempo

                    if (Lista->n <= 100)
                    {
                        printf("Listado ordenado en coordenada y: \n");
                        view_list(Lista);
                    }
                    printf("\nFINALIZADO, TIEMPO TOTAL EN SEGUNDOS: %f  \n", ((t1 - t0) / CLOCKS_PER_SEC)); 
                }
                else
                {
                    printf("Error: primero debe generar un listado de puntos o leerlo desde un archivo.\n");
                }
                break;
            case 5:
                if (Lista != NULL && Lista->init != NULL)
                {   
                    printf("\nIngrese cota inferior en x: ");
                    scanf("%ld", &cota_inf);
                    printf("\nIngrese cota superior en x: ");
                    scanf("%ld", &cota_sup);
                    printf("\nResolviendo...\n"); 

                    t0 = clock(); // Inicio medición de tiempo
                    LE *subListado = sublistado(Lista, cota_inf, cota_sup, 1);
                    t1 = clock(); // Fin medición de tiempo

                    if (subListado->n <= 100)
                    {
                        printf("Sublistado que satisface las cotas %ld <= x <= %ld \n", cota_inf, cota_sup);
                        view_list(subListado);
                    }
                    printf("\nFINALIZADO, TIEMPO TOTAL EN SEGUNDOS: %f  \n", ((t1 - t0) / CLOCKS_PER_SEC)); 
                }
                else
                {
                    printf("Error: primero debe generar un listado de puntos o leerlo desde un archivo.\n");
                }
                break;
            case 6:
                if (Lista != NULL && Lista->init != NULL)
                {   
                    printf("\nIngrese cota inferior en y: ");
                    scanf("%ld", &cota_inf);
                    printf("\nIngrese cota superior en y: ");
                    scanf("%ld", &cota_sup);
                    printf("\nResolviendo...\n"); 

                    t0 = clock(); // Inicio medición de tiempo
                    LE *subListado = sublistado(Lista, cota_inf, cota_sup, 0);
                    t1 = clock(); // Fin medición de tiempo

                    if (subListado->n <= 100)
                    {
                        printf("Sublistado que satisface las cotas %ld <= y <= %ld \n", cota_inf, cota_sup);
                        view_list(subListado);
                    }
                    printf("\nFINALIZADO, TIEMPO TOTAL EN SEGUNDOS: %f  \n", ((t1 - t0) / CLOCKS_PER_SEC)); 
                }
                else
                {
                    printf("Error: primero debe generar un listado de puntos o leerlo desde un archivo.\n");
                }
                break;
            case 9:
                printf("Listo para salir, entrar cualquier valor para terminar: ");
                scanf("%d",&i);
                break;
            default:
                printf("Seleccion invalida, reintentar (9 para salir): ");
                break;
        }
    } while (sel != 9);
    
    /*
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
    
    printf("\n---------------------------\n");
    printf("Sublistado cotas 10<y<50:\n");
    LE *subListado = sublistado(Lista, 10, 50, 0);
    view_list(subListado);
    */
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
    int n = 0;
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
            n++;
        }
        else if (x == 0 && elem->y >= cota_inf && elem->y <= cota_sup)
        {
            add_element(subListado, elem->x, elem->y);
            n++;
        }
        
        elem = elem->post;
    }
    subListado->n = n;
    return subListado;
}


int leer_archivo(LE *lista)
{

    Bloque *elem1, *elem2;

    char nombreArchivo[30];
    FILE *archivo;

    char bus;
    long x, y;
    int n = 0;

    printf("Ingrese nombre del archivo (con extension, ejemplo: archivo1.txt): ");
    scanf("%s", nombreArchivo);

    archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("\nError de apertura del archivo.\n");
        return 0;
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
    printf("\nPuntos cargados correctamente.\n");
    return 1;
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


void add_random_element(LE *lista)
{
    // constructor elemento
    long x = rand()%NMAX;
    long y = rand()%NMAX;
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
