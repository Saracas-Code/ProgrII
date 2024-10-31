#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "vectordinamico.h"

//Función para imprimir un vector
void imprimir(vectorD v){

    unsigned long longitud;
    longitudVector(v, &longitud);

    printf("\nVECTOR CREADO ACTUAL:\n");

    printf("\n\t[");
    for(unsigned long i=0; i<longitud; i++) {
        printf("%d", recuperar(v, i));
        if (i < longitud - 1)
            printf(", ");
    }
    printf("]\n");
}

//Función que crea un vector y lo rellena con valores aleatorios
void alea(vectorD *v, unsigned long tam){

    crear(v, tam);
    srand(time(NULL));

    for (unsigned long i=0; i<tam; i++)
        asignar(v, i, rand());
}

//FUNCIÓN AUXILIAR. Intercambia las posiciones de dos valores de un vector
void intercambiar(vectorD *v, unsigned long i, unsigned long j){

    TELEMENTO temporal = recuperar(*v, i);
    asignar(v, i, recuperar(*v, j));
    asignar(v, j, temporal);
}

//ALGORITMO BUBBLESORT
void bubbleSort(vectorD *v){

    unsigned long tam;
    longitudVector(*v, &tam);

    for(unsigned long i=0; i<tam-1; i++){
        for(unsigned long j = i+1; j<tam; j++)
        {
            if(recuperar(*v, i) > recuperar(*v, j)) {
                intercambiar(v, i, j);
            }
        }
    }
}

//ALGORITMO QUICKSORT
//Devolver pivote
unsigned long particion(vectorD *v, unsigned long izquierda, unsigned long derecha) {

    TELEMENTO pivote = recuperar(*v, izquierda);

    while(1){
        // Mientras desde la izquierda esté ordenado avanza
        while (recuperar(*v, izquierda) < pivote)
            izquierda++;

        // Mientras desde la derecha esté ordenado avanza
        while (recuperar(*v, derecha) > pivote)
            derecha--;

        //Si no necesitamos hacer ningún intercambio porque están en orden en la iteracion
        if (izquierda >= derecha)
            return derecha;
        else {
            intercambiar(v, izquierda, derecha);
            izquierda++;
            derecha--;
        }
    }
}

//Algoritmo recursivo quicksort
void qs(vectorD *v, unsigned long izquierda, unsigned long derecha) {

    if (izquierda < derecha) {
        unsigned long indiceParticion = particion(v, izquierda, derecha);
        qs(v, izquierda, indiceParticion);
        qs(v, indiceParticion + 1, derecha);
    }
}

void quickSort(vectorD *v){

    unsigned long tam;
    longitudVector(*v, &tam);

    qs(v, 0, tam-1);
}

//BÚSQUEDA SECUENCIAL
unsigned long bussec(vectorD *v, TELEMENTO valor){

    unsigned long tam;
    longitudVector(*v, &tam);

    for(unsigned long i=0; i<tam; i++){
        if(valor == recuperar(*v, i))
            return i;
    }
    return -1;
}

//BÚSQUEDA BINARIA
unsigned long busbinRecursiva(vectorD *v, TELEMENTO valor, unsigned long bajo, unsigned long alto){

    if (bajo > alto)
        return -1;

    unsigned long central = (bajo + alto) / 2;

    TELEMENTO valorCentro = recuperar(*v,central);
    if (valor == valorCentro)
        return central;

    if (valor < valorCentro) // Entonces está hacia la izquierda
        alto = central - 1;
    else // Está hacia la derecha
        bajo = central + 1;

    //Llamamos de nuevo a la función
    return busbinRecursiva(v, valor, bajo, alto);
}
unsigned long busbin(vectorD *v, TELEMENTO valor){

    unsigned long tam;
    longitudVector(*v, &tam);
    return busbinRecursiva(v, valor, 0, tam-1);
}

//FUNCIÓN PARA GUARDAR LOS TIEMPOS EN LOS FICHEROS
void guardarTiempoAlg(char *tipo, unsigned long tam, double tiempoEmpleado){ //cambiar para meter en un fichero

    char *nombreFichero="bussec.txt";

    if(strcmp(tipo, "b")==0)
        nombreFichero="busbin.txt";

    FILE* fichero;
    fichero = fopen(nombreFichero, "a");
    fprintf(fichero, "%lu\t\t%.8lf\n", tam, tiempoEmpleado); //Salida de los datos n, t(n) a fichero
    fclose(fichero);
}

//FUNCIÓN PARA PRINTEAR LOS TIEMPOS DE x BÚSQUEDAS
double tiempoAlg(char *tipo, vectorD *v, unsigned long nBusquedas){
    unsigned long tam;
    longitudVector(*v,&tam);

    srand(time(NULL));
    clock_t inicio = clock();

    for(int j=0;j<nBusquedas;j++)
        if(strcmp(tipo, "b")==0)
            busbin(v, rand()); //Hacer 1000 búsquedas de números aleatorios en un array ordenado
        else if(strcmp(tipo, "s")==0)
            bussec(v, rand());

    clock_t fin = clock();
    double tiempoEmpleado=(fin-inicio)/(double)CLOCKS_PER_SEC;

    printf("\n%s\t\tn: %lu\t\tTiempo: %lf\n", tipo, tam, tiempoEmpleado);

    return tiempoEmpleado;
}
void lanzarTramo(char *tipo,vectorD *vector,unsigned long desde, unsigned long hasta, unsigned long paso, unsigned long nBusquedas){
    for (unsigned long i = desde; i <= hasta; i=i+paso) {

        alea(vector, i);
        quickSort(vector);

        double tSec = tiempoAlg(tipo,vector,nBusquedas);
        guardarTiempoAlg(tipo,i,tSec);

        liberar(vector);
    }

}
//Si no tenemos los 5 párametros de entrada sacamos un menú
void tratarMenu(){

    char opcion; /*Variable del menu*/
    vectorD vector=NULL; /*Declaramos el vector*/
    unsigned long longitud;

    do {
        printf("\n--------------------------------\n");
        printf("1) Crear vector v\n");
        printf("2) Liberar vector\n");
        printf("3) Imprimir vector\n");
        printf("4) Ordenar vector burbuja\n");
        printf("5) Ordenar vector quick\n\n");

        printf("a) BÚSQUEDA SECUENCIAL\n");
        printf("b) BÚSQUEDA BINARIA\n");
        printf("c) CALCULAR TIEMPOS AMBOS ALGORITMOS\n");
        printf("d) CALCULAR TIEMPOS BÚSQUEDA SECUENCIAL\n");
        printf("e) CALCULAR TIEMPOS BÚSQUEDA BINARIA\n\n");
        printf("s) SALIR\n");
        printf("\n-------------------------------\n");
        printf("Opción: ");
        scanf(" %c", &opcion); //OJO: Espacio antes de %c para vaciar buffer de teclado

        switch (opcion) {
            case '1': /*Crear vector v*/
                liberar(&vector);
                printf("\nLongitud del vector v: ");
                scanf("%lu", &longitud);
                alea(&vector, longitud);
                break;

            case '2': /*Liberar memoria do vector*/
                if(vector) { //Ponemos esta condición para que se puedan printear dos mensajes distintos dependiendo de la condición
                    liberar(&vector);
                    printf("\nVector liberado\n");
                }
                else
                    printf("\n\tNO EXISTE VECTOR PARA LIBERAR. Cree un nuevo vector\n");
                break;

            case '3':
                if(vector)
                    imprimir(vector);
                else
                    printf("\n\tERROR AL IMPRIMIR. El vector no está creado todavía\n");
                break;

            case '4':
                if(vector){
                    bubbleSort(&vector);
                }
                else
                    printf("\n\tERROR AL ORDENAR. El vector no está creado todavía\n");
                break;

            case '5':
                if(vector){
                    quickSort(&vector);
                }
                else
                    printf("\n\tERROR AL ORDENAR. El vector no está creado todavía\n");
                break;

            case 'a':
                if(vector){
                    TELEMENTO num;
                    printf ("Número a buscar? ");
                    scanf ("%d", &num);
                    unsigned long pos = bussec(&vector, num);
                    printf("\n%d encontrado en posición %lu", num, pos);
                }
                else
                    printf("\n\tERROR AL BUSCAR. El vector no está creado todavía\n");
                break;

            case 'b':
                if(vector){
                    TELEMENTO num;
                    printf ("Numero a buscar? ");
                    scanf ("%d", &num);
                    unsigned long pos = busbin(&vector, num);
                    printf("\n%d encontrado en posición %lu", num, pos);
                }
                else
                    printf("\n\tERROR AL BUSCAR. El vector no está creado todavía\n");
                break;

            case 'c': //tiempos ambos algoritmos
            {
                char *tipo;
                unsigned long desde, hasta, paso, nBusquedas;

                nBusquedas = 10000; tipo = "s";
                for(int veces=0; veces<5; veces++){

                    desde=paso=1000; hasta=10000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);

                    desde=paso=10000; hasta=100000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);

                    desde=paso=100000; hasta=1000000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
                }

                nBusquedas = 1000000; tipo = "b";
                for(int veces=0; veces<5; veces++)
                {
                    desde=paso=10000; hasta=100000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
                    desde=paso=100000; hasta=1000000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
                    desde=paso=1000000; hasta=10000000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
                    desde=paso=10000000; hasta=100000000;
                    printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                    lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
                }
            }
                break;

            case 'd':
            {
                unsigned long desde, hasta, paso, nBusquedas;
                char *tipo="s";

                printf ("Tamaño desde? ");
                scanf ("%lu", &desde);
                printf ("Tamaño hasta? ");
                scanf ("%lu", &hasta);
                printf ("Tamaño paso? ");
                scanf ("%lu", &paso);
                printf ("Búsquedas a medir? ");
                scanf ("%lu", &nBusquedas);

                printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
            }
                break;

            case 'e':
            {
                unsigned long desde, hasta, paso, nBusquedas;
                char *tipo="b";

                printf ("Tamaño desde? ");
                scanf ("%lu", &desde);
                printf ("Tamaño hasta? ");
                scanf ("%lu", &hasta);
                printf ("Tamaño paso? ");
                scanf ("%lu", &paso);
                printf ("Búsquedas a medir? ");
                scanf ("%lu", &nBusquedas);

                printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
                lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
            }
                break;

            case 's':
                liberar(&vector);
                printf("\nSaliendo del programa\n");
                break;

            default:
                printf("\n\tERROR. Opción incorrecta\n");

        }
    } while (opcion != 's');
}

//Programa principal; se trata la línea de comandos, si no hay nada, se llama a tratarMenú()
int main(int argc, char** argv) {

    vectorD vector = NULL; /*Declaramos el vector*/

    if (argc == 6) {
        char* tipo = argv[1];
        long desde = (long) strtol(argv[2], NULL, 10);
        long hasta = (long) strtol(argv[3], NULL, 10);
        long paso = (long) strtol(argv[4], NULL, 10);
        long nBusquedas = (long) strtol(argv[5], NULL, 10);

        if(strcmp(tipo, "s") == 0){ //Búsqueda secuencial

            printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
            lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
        }
        if(strcmp(tipo, "b") == 0){ //Búsqueda binaria

            printf("\n\n\t\tBÚSQUEDAS = %lu\n\n", nBusquedas);
            lanzarTramo(tipo,&vector,desde,hasta,paso,nBusquedas);
        }
    }
    else
        tratarMenu();

    return EXIT_SUCCESS;
}
