
#include "matriz.h"

matriz* suma(matriz *M1, matriz *M2) {

    matriz *aux = 0;
    int i, k;

    if (M1 != 0 && M2 != 0) {
        if (M1->filas != M2->filas || M1->columnas != M2->columnas) {
            printf("El numero de filas y columnas deben ser iguales. Vuelva a crear las matrices.\n");
            return aux;
        }
        aux = crearMatriz(M1->filas, M1->columnas);
        for (i = 0; i < aux->filas; i++)
            for (k = 0; k < aux->columnas; k++) //for (k = 0; k < aux->filas; k++)
                *(aux->datos + i * aux->columnas + k) = *(M1->datos + i * M1->columnas + k) + *(M2->datos + i * M2->columnas + k);//...= *(M2->datos + i... ); k-1 -> k
        return aux;

    }
    else {
        printf("ERROR. Alguna de las matrices no existe, vuelva a definir\n");
        return 0; //Antes no existía esta línea
    }

}

