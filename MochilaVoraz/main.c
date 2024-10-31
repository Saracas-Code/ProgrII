#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "TAD/vectordinamico.h"

//ALGORITMO QUICKSORT
//FUNCIÓN AUXILIAR. Intercambia las posiciones de dos valores de un vector
void intercambiar(vectorD *v, unsigned long i, unsigned long j)
{
    TELEMENTO temporal = recuperar(*v, i);
    asignar(v, i, recuperar(*v, j));
    asignar(v, j, temporal);
}

//Devolver pivote. int tipo indica si se está ordenando por peso, valor o ratio.
unsigned long particion(vectorD *v, unsigned long izquierda, unsigned long derecha, int tipo)
{
    TELEMENTO pivote = recuperar(*v, izquierda);

    //Como tenemos que ordenar en función de tres parámetros diferentes, hacemos un switch case
    while(1){
        switch(tipo){
            //Ordenamos por peso (creciente)
            case 1:
                while (recuperar(*v, izquierda).peso < pivote.peso) izquierda++;
                while (recuperar(*v,derecha).peso > pivote.peso) derecha--;
                break;
                //Ordenamos por valor (decreciente)
            case 2:
                while (recuperar(*v, izquierda).valor > pivote.valor) izquierda++;
                while (recuperar(*v,derecha).valor < pivote.valor) derecha--;
                break;
                //Ordenamos por ratio (decreciente)
            case 3:
                while (recuperar(*v, izquierda).ratio > pivote.ratio) izquierda++;
                while (recuperar(*v,derecha).ratio < pivote.ratio) derecha--;
                break;
        }

        //Si no necesitamos hacer ningún intercambio porque están en orden en la iteración
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
void qs(vectorD *v, unsigned long izquierda, unsigned long derecha, int tipo)
{
    if (izquierda < derecha)
    {
        unsigned long indiceParticion = particion(v, izquierda, derecha, tipo);
        qs(v, izquierda, indiceParticion, tipo);
        qs(v, indiceParticion + 1, derecha, tipo);
    }
}

void quickSort(vectorD *v, int tipo)
{
    unsigned long tam;
    longitudVector(*v, &tam);

    qs(v, 0, tam-1, tipo);
}

/*--------------------------------------------------------------------------------------------------------*/

//Función para leer la CANTIDAD de objetos que hay escritos en un fichero.txt
unsigned long elementosFichero(char* nombreFichero)
{
    char objeto[TAM];
    float peso;
    float valor;

    FILE *f;
    f = fopen(nombreFichero, "r");

    int cantidad=0;
    while(fscanf(f, "%s %f %f", objeto, &peso, &valor) == 3)
        cantidad++;

    fclose(f);
    return cantidad;
}

//Función que lee los datos de un fichero, los guarda en una estructura y almacena cada estructura en el vector v
void cargarElementosVector(vectorD* v, char* nombreFichero)
{
    char objeto[TAM];
    float peso;
    float valor;

    TELEMENTO datosObjeto;

    FILE *f;
    f = fopen(nombreFichero, "r");

    unsigned long i=0;
    while(fscanf(f, "%s %f %f", objeto, &peso, &valor) == 3){
        strcpy(datosObjeto.nombre, objeto);
        datosObjeto.peso = peso;
        datosObjeto.valor = valor;
        datosObjeto.ratio = valor/peso;

        asignar(v, i, datosObjeto);
        i++;
    }

    fclose(f);
}

//FUNCIÓN DE IMPRESIÓN. Imprime los datos de las estructuras de un vector v por pantalla
void imprimirVector(vectorD *v)
{

    unsigned long longitud;
    longitudVector(*v, &longitud);
    TELEMENTO temp;

    for(unsigned long i=0; i<longitud; i++){
        temp = recuperar(*v, i);
        printf("\n\n%s -> %.3f gramos, %.3f céntimos. Ratio = %.3f", temp.nombre, temp.peso, temp.valor, temp.ratio);
    }
}

//Función para meter los objetos en la mochila hasta que el peso de esta sea <= pesoMax
void meterObjetoMochila(vectorD* vectorOrdenado, float pesoMax)
{
    unsigned long longitud;
    longitudVector(*vectorOrdenado, &longitud);

    unsigned long n=0;
    float pesoAcumulado=0;
    float valorAcumulado=0;

    printf("\n\n\n\t\e[1mOBJETOS QUE SERÁN INTRODUCIDOS EN LA MOCHILA:\e[0m\n");
    while(n<longitud)
    {
        TELEMENTO objeto = recuperar(*vectorOrdenado, n);
        if((pesoAcumulado+objeto.peso)<=pesoMax){
            pesoAcumulado += objeto.peso;
            valorAcumulado += objeto.valor;
            printf("\n\n%s -> %.3f gramos, %.3f céntimos. Ratio = %.3f", objeto.nombre, objeto.peso, objeto.valor, objeto.ratio);
        }
        n++;
    }
    printf("\n\n\nPeso acumulado en la mochila: %.3f gramos", pesoAcumulado);
    printf("\nValor acumulado en la mochila: %.3f céntimos\n", valorAcumulado);
}

//FUNCIÓN VORAZ POR RATIO
void voraz_valor_por_unidad_de_peso(vectorD* v, float maximoMochila)
{
    printf("\n\n\n------------ MOCHILA. PESO MÁXIMO: %f -------------\n\n", maximoMochila);
    printf("\n\t\t\e[1mORDENACIÓN POR VALOR/PESO:\e[0m\n");
    quickSort(v, 3);
    imprimirVector(v);
    meterObjetoMochila(v, maximoMochila);
}

//FUNCIÓN VORAZ POR VALOR
void voraz_valor(vectorD* v, float maximoMochila)
{
    printf("\n--------------------------------------------------------------\n");
    printf("\n\t\t\e[1mORDENACIÓN POR VALOR:\e[0m\n");
    quickSort(v, 2);
    imprimirVector(v);
    meterObjetoMochila(v, maximoMochila);
}

//FUNCIÓN VORAZ POR PESO
void voraz_peso(vectorD* v, float maximoMochila)
{
    printf("\n--------------------------------------------------------------\n");
    printf("\n\t\t\e[1mORDENACIÓN POR PESO:\e[0m\n");
    quickSort(v, 1);
    imprimirVector(v);
    meterObjetoMochila(v, maximoMochila);
}

//Programa principal
int main(int argc, char** argv){

    if (argc==3)
    {
        if (atof(argv[1])<=0){
            printf("\n\tERROR. Peso máximo no válido. Introduzca una cantidad entera positiva.\n");
            return 0;
        }

        float gramosMax = (float) strtof(argv[1], NULL);
        char nombreFichero[30];
        strcpy(nombreFichero, argv[2]);
        unsigned long cantidad = elementosFichero(nombreFichero);

        vectorD vectorElementos;
        crear(&vectorElementos, cantidad);
        cargarElementosVector(&vectorElementos, nombreFichero);
        printf("\n\n\e[1mOBJETOS DE LOS QUE DISPONEMOS:\e[0m\n");
        imprimirVector(&vectorElementos);

        voraz_valor_por_unidad_de_peso(&vectorElementos, gramosMax);
        voraz_peso(&vectorElementos, gramosMax);
        voraz_valor(&vectorElementos, gramosMax);
    }
    else
    {
        printf("\n\nERROR. Debe introducir los argumentos del programa de la siguiente manera:\n");
        printf("\n\t./mochilaVoraz Peso_Máximo Fichero_Datos.txt\n\n");
        return 0;
    }

    return(EXIT_SUCCESS);
}