//
// Created by Sarac on 15/02/2023.
//

#include <stdlib.h>
#include <stdio.h>

/*Se vuelve a definir el tipo de datos que contiene el vector*/
typedef int TELEMENTO;

/*Implementación del TAD vectorD*/
typedef struct {
    TELEMENTO *datos; /*valores del vector*/
    unsigned long tam;        /*tamaño del vector*/
} STVECTOR;           /*definición del tipo de datos estructura*/

typedef STVECTOR *vectorD; /*puntero a estructura*/

/*Funciones de manipulación de datos*/
/*Función crear: asigna memoria y devuelve la asignación al vector*/
void crear(vectorD *v, unsigned long longitud){
    if(longitud > 0){
        *v = (vectorD) malloc(sizeof (STVECTOR));
        (*v)->datos = (TELEMENTO*) malloc(longitud * sizeof (TELEMENTO));
        (*v)->tam = longitud;
        for(unsigned long i = 0; i < longitud; i++)
            //Inicialización a 0 de las componentes del vector.
            *((*v)->datos + i) = 0;
    }
    else
        printf("\n\tERROR AL CREAR. Introduce una longitud mayor que 0\n");
}

//Función asignar: Asigna un valor a una posición del vector:
void asignar(vectorD *v, unsigned long posicion, TELEMENTO valor) {
    if (posicion < (*v)->tam)
        *((*v)->datos + posicion) = valor;
    else
        printf("\n\tERROR DE ASIGNACIÓN. Esa posición del vector no es válida\n");
}

void liberar(vectorD *v){
    if (*v){
        free((*v)->datos);
        free(*v);
        (*v) = NULL;
    }
}


TELEMENTO recuperar(vectorD v, unsigned long posicion){
    TELEMENTO x;

    if (v){
        if (posicion > v->tam-1){
            return 0;
        }
        x = *(v->datos + posicion);
        return x;
    }
    else
        return 0;

}

void longitudVector(vectorD v, unsigned long *longitud){
    if (v)
        *longitud = v->tam;
}

