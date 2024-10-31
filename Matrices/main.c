/*
 * PROGRAMA PARA REALIZAR OPERACIONES BÁSICAS CON UNA MATRIZ DINÁMICA
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES
 * DOCUMENTAR LAS CORRECCIONES INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 *
 * PRUEBAS:
 * - Número de filas o columnas: 0
 * - Acceder a un dato con índices negativos
 * - Verificar todas las operaciones, para matrices pequeñas (2,3 filas/cols)
 *      - Número de filas y columnas distintos en las dos matrices
 *      - Número de filas igual y de columnas distinto
 *      - Número de columnas igual y de filas distinto
 *
 * //LIBERACIÓN DE LA MEMORIA EXPLICADA (OPCIÓN 7)
 */

#include "matriz.h"

int main() {
    int f, c; //int i,k,f,c
    float valor;
    matriz *a = 0, *b = 0, *aux = 0;
    char opcion, resp;


    do {
        printf("\n---------------------Libreria matrices---------------------\n\n");
        printf("1-Crear matrices\n");
        printf("2-Asignar elementos\n");
        printf("3-Obtener elemento\n");
        printf("4-Imprimir matrices\n");
        printf("5-Sumar matrices\n");
        printf("6-Producto de matrices\n");
        printf("7-Eliminar matrices\n");
        printf("0-Salir\n");
        printf("Opcion: ");
        scanf(" %c", &opcion); //scanf(" %c", opcion);

        switch (opcion) {
            case '0':
                printf("Saliendo del programa\n");
                break;
            case '1':
                printf("Introduzca el numero de filas de la matriz 'a': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'a': ");
                scanf("%d", &c);
                a = crearMatriz(f, c);

                printf("Introduzca el numero de filas de la matriz 'b': ");
                scanf("%d", &f); //scanf("%f", &f);
                printf("Introduzca el numero de columnas de la matriz 'b': ");
                scanf("%d", &c);
                b = crearMatriz(f, c);
                break;
            case '2':
                if(a!=0) {
                    printf("Matriz A\n");
                    for (f = 0; f < a->filas; f++)
                        for (c = 0; c < a->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, a);
                        }
                }
                else
                    printf("\nERROR. Vuelva a definir la matriz a");
                if(b!=0){
                    printf("\nMatriz B\n");
                    for (f = 0; f < b->filas; f++)
                        for (c = 0; c < b->columnas; c++) {
                            printf("Introduzca el valor de la posicion %dx%d: ", f + 1, c + 1);
                            scanf("%f", &valor);
                            asignarElemento(f, c, valor, b); //asignarElemento(f, c, valor, a);
                        }
                }
                else
                    printf("\nERROR. Vuelva a definir la matriz b");
                break;

            case '3':
                do {
                    printf("De que matriz quieres ver un elemento? (a/b): ");
                    scanf(" %c", &resp);
                } while (resp != 'a' && resp != 'b');

                printf("Introduce fila y columna (fila columna): ");
                scanf("%d %d", &f, &c);
                if (resp == 'a') {
                    valor = obtenerElemento(f, c, a); //valor = obtenerElemento(f, c, b);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                } else if (resp == 'b') {
                    valor = obtenerElemento(f, c, b); //valor = obtenerElemento(f, c, a);
                    printf("El valor de la fila y columna seleccionada es: %f\n", valor);
                }
                break;
            case '4':
                printf("\nMatriz A\n");
                imprimirMatriz(a);
                printf("Matriz B\n");
                imprimirMatriz(b);
                break;
            case '5':
                aux = suma(a, b);
                if(aux!=0){
                    printf("\nSUMA:\n");
                    imprimirMatriz(aux);
                    destruirMatriz(aux);
                    break;
                }
                break;
            case '6':
                aux = producto(a, b);
                if(aux!=0){
                    printf("\nPRODUCTO:\n");
                    imprimirMatriz(aux);
                    destruirMatriz(aux);
                    //destruirMatriz(aux);
                    break;
                }
                break;
            case '7':
                destruirMatriz(a);
                a=NULL;
                destruirMatriz(b);
                b=NULL;
                printf("\nMatrices eliminadas...\n");
                break;
                //Tras liberar la memoria a la que está apuntando, todavía hay una dirección de memoria
                //asociada a cada puntero. Por lo tanto, hay que igualar estos punteros a NULL para
                //que no tenga ninguna
            default:
                printf("Opción incorrecta\n");
                break;
        }
    } while (opcion != '0');

    return 0;
}