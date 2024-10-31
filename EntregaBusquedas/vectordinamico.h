//
// Created by Sarac on 15/02/2023.
//

#ifndef P1_V0_VECTORDINAMICO_H
#define P1_V0_VECTORDINAMICO_H

//Tipo de datos de los elementos del vector
typedef int TELEMENTO;

//Tipo opaco, los detalles de implementación están ocultos para el usuario.
typedef void *vectorD;

/*Función crear: asigna memoria y devuelve la asignación al vector.
 Recibir v por referencia para devolver al programa principal
 la dirección de memoria reservada por ese procedimiento*/
void crear (vectorD *v, unsigned long longitud);

/*Función asignar: Llena una posición del vector con un valor. Recibe una copia de
la dirección de memoria reservada para el vector v.*/
void asignar(vectorD *v, unsigned long posicion, TELEMENTO valor);

/*Función liberar: Libera la memoria asociada a un vector e inicializa el vector a NULL*/
void liberar(vectorD *v);

/*Función recuperar: Obtiene el valor entero de una posición del vector que se pasa por argumento.
  Se pasa una copia, tanto del vector como de la posicion*/
TELEMENTO recuperar(vectorD v, unsigned long posicion);

/*Función longitudVector: Obtiene el tamaño actual del vector. El vector se pasa como copia,
 * mientras que la longitud se pasa por puntero para que salga modificada de la función*/
void longitudVector(vectorD v, unsigned long *longitud);

#endif //P1_V0_VECTORDINAMICO_H
