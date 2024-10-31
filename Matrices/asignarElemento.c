#include "matriz.h"

void asignarElemento(int fila, int columna, float valor, matriz *M) {
    *((M->datos) + fila * M->columnas + columna) = valor;
}