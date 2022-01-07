#include <stdio.h> /* esenciales para la comunicacion con el programa */
#include <stdlib.h> /* generador aleatorio basico, control de memoria, conversiones basicas, control de procesos */
//#include <math.h> /* funciones matematicas basicas como floor, ceil, log2, etc. */
#include <time.h> /* medicion de tiempo */

// para el trabajo 4, NMAX debería ser 10.000.000
// para el trabajo 5, NMAX debería ser 40.000 si el compilador trabaja en 32 bits
#define NMAX 10000000
//#define NMAX 40000

void generar_archivo( void );

int main()
{
    int i,sel ;

    printf("Elegir el tipo de operacion a ejecutar:\n");
    printf("1) Generar datos (archivo)\n");
    printf("9) Salir del programa\n");
    sel = 0 ;
    do
    {
        printf("Seleccion (0 para repetir el menu): ");
        scanf("%d",&sel);
        switch (sel)
        {
            case 0:
                printf("1) Generar datos (archivo)\n");
                printf("9) Salir del programa\n");
                break ;
            case 1:
                generar_archivo();
                break ;
            case 9:
                printf("Listo para salir, entrar cualquier valor para terminar: ");
                scanf("%d",&i);
                break ;
            default:
                printf( "Seleccion invalida, reintentar (9 para salir): ");
                break ;
        }

    }
    while ( sel != 9 ) ;

    return(0);
}




void generar_archivo( void )
{
    srand(clock());
    long a ;
    int n ;
    long i ;
    FILE *archivo;
    char nombre_archivo[30];
    printf("Ingresar nombre de archivo: ");
    scanf("%s", nombre_archivo);
    
    while (getchar() != '\n')
        ;
    archivo = fopen(nombre_archivo, "w");
    printf("Ingresar la cantidad de puntos: ");
    scanf("%d", &n);
    fprintf(archivo,"%d \n",n);
    for ( i = 0 ; i < n ; i++ )
    {
        a = rand()%NMAX ;
        fprintf(archivo,"%ld ",a);
        a = rand()%NMAX ;
        fprintf(archivo,"%ld ",a);
        fprintf(archivo,"\n");
    }
    fclose(archivo);
    printf("El archivo esta listo.\n");
}




