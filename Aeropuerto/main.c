#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "TAD/lista.h"
#include "TAD/cola.h"

#define NUM_ARCOS 10

//Leer cada pasajero
TIPOELEMENTO lee_pasajero(){

    TIPOELEMENTO pasajeroLeido;

    printf("\nDATOS DEL PASAJERO");
    printf("\nNombre: ");
    scanf(" %[^\n]", pasajeroLeido.nombre);

    printf("Apellidos: ");
    scanf(" %[^\n]", pasajeroLeido.apellidos);

    printf("Pasaporte: ");
    scanf(" %s", pasajeroLeido.pasaporte);

    printf("Código de vuelo: ");
    scanf(" %s", pasajeroLeido.codVuelo);

    return pasajeroLeido;
}

//FUNCIONES PARA IMPRIMIR DATOS
void escribe_pasajero(TIPOELEMENTO pasajero){

    for(short i = 0; i < strlen(pasajero.apellidos); i++)
        pasajero.apellidos[i] = toupper(pasajero.apellidos[i]);
    for(short i = 0; i < strlen(pasajero.nombre); i++)
        pasajero.nombre[i] = toupper(pasajero.nombre[i]);

    printf("\n\t\t(%s, %s - %s, %s)\n", pasajero.pasaporte, pasajero.apellidos, pasajero.nombre, pasajero.codVuelo);
}

void imprimir_cola(TCOLA *c){

    TIPOELEMENTO e;

    if (esColaVacia(*c) == 1)
        printf("\nCOLA VACÍA\n");

    else{
        for(int i=0; i<longitudCola(*c); i++){
            consultarPrimerElementoCola(*c,&e);
            escribe_pasajero (e);
            suprimirElementoCola(c);
            anadirElementoCola(c, e);
        }
    }
}

void imprimir_lista(TLISTA lista){

    TPOSICION actual;
    TIPOELEMENTO e;

    if (esListaVacia(lista) == 1)
        printf("\nLISTA VACÍA\n");

    else{
        actual = primeroLista(lista);
        for(int i=0; i< longitudLista(lista); i++){
            recuperarElementoLista(lista, actual, &e);
            escribe_pasajero(e);
            actual = siguienteLista(lista, actual);
        }
    }
}

void escribe_estado_zona_seguridad(TCOLA entrada, TCOLA arcosSeguridad[NUM_ARCOS], TLISTA sospechosos){

    printf("\n\n*********************************************************************");
    if(esColaVacia(entrada))
        printf("\n\nNo hay personas esperando en la cola de acceso");
    else{
        printf("\n\nListado de personas esperando para entrar en zona de seguridad:\n");
        imprimir_cola(&entrada);
    }

    printf("\n\n*********************************************************************");
    printf("\n\n\t\t\tARCOS\n");
    for (short i=0; i<NUM_ARCOS; i++){
        if(esColaVacia(arcosSeguridad[i]))
            printf("\nNo hay personas esperando en el arco %d", i+1);
        else{
            printf("\n- Listado de personas esperando para entrar en arco %d:\n", i+1);
            imprimir_cola(&arcosSeguridad[i]);
            printf("\n");
        }
    }

    printf("\n\n**********************************************************************");
    if(esListaVacia(sospechosos))
        printf("\n\nNo hay personas sospechosas\n");
    else{
        printf("\n\nListado de personas sospechosas:\n");
        imprimir_lista(sospechosos);
    }
}

//FUNCIÓN AUXILIAR. Decidir a qué arco de seguridad va cada pasajero
short arco_destino(TCOLA arcosSeguridad[NUM_ARCOS]){

    short indice = 0;
    int n = longitudCola(arcosSeguridad[0]);

    for(short i=0; i<NUM_ARCOS; i++){
        if(longitudCola(arcosSeguridad[i])==0)
            return i;

        if(n > longitudCola(arcosSeguridad[i])){
            indice = i;
            n = longitudCola(arcosSeguridad[i]);
        }
    }
    return indice;
}

//Procesos de tránsito de la zona de seguridad
void inicializa_zona_seguridad(TCOLA *entrada, TCOLA arcosSeguridad[NUM_ARCOS], TLISTA *sospechosos){

    crearCola(entrada);
    for(short i=0; i<NUM_ARCOS; i++)
        crearCola(&arcosSeguridad[i]);
    crearLista(sospechosos);
}

void llega_a_aeropuerto(TCOLA *acceso){

    TIPOELEMENTO dato;
    dato = lee_pasajero();
    anadirElementoCola(acceso, dato);
}

void entra_en_zona_seguridad(TCOLA *acceso, TCOLA arcosSeguridad[NUM_ARCOS]){

    TIPOELEMENTO viajero;

    if(esColaVacia(*acceso) == 1)
        printf("\nERROR. No hay viajeros en la cola de entrada\n");
    else{
        consultarPrimerElementoCola(*acceso, &viajero);
        suprimirElementoCola(acceso);
        anadirElementoCola(&arcosSeguridad[arco_destino(arcosSeguridad)], viajero);

        printf("\nEl pasajero se dirige al arco %hd", arco_destino(arcosSeguridad)+1);
        printf("\n\nDATOS DEL PASAJERO:\n");
        escribe_pasajero(viajero);
    }
}

void pasa_por_arco(TCOLA arcosSeguridad[NUM_ARCOS], TLISTA *sospechosos) {

    int opcionArco;
    int esSospechoso;
    TIPOELEMENTO e;

    printf("\nArco del que proviene el pasajero:\n");
    scanf(" %d", &opcionArco);

    if (opcionArco>NUM_ARCOS || opcionArco<1){
        printf("\nERROR. No existe ese arco. Ingresa un número de arco del 1 al 10");
        return;
    }
    else{
        if (esColaVacia(arcosSeguridad[opcionArco - 1]))
            printf("\nERROR. La cola de este arco está vacía\n");

        else {
            consultarPrimerElementoCola(arcosSeguridad[opcionArco - 1], &e);
            suprimirElementoCola(&arcosSeguridad[opcionArco - 1]);
            printf("\nPersona que viene del arco %d:\n", opcionArco);
            escribe_pasajero(e);
            do {
                printf("\n\n¿Ha generado sospecha el pasajero?\n1.Sí\n0.No\nRespuesta: ");
                scanf(" %d", &esSospechoso);
                if (esSospechoso == 1){
                    insertarElementoLista(sospechosos, primeroLista(*sospechosos), e);
                    printf("\nVIAJERO INTRODUCIDO EN LA LISTA DE SOSPECHOSOS\n");
                }
                else if (esSospechoso == 0)
                    printf("\nVIAJERO PASA A LA ZONA DE LAS PUERTAS DE EMBARQUE\n");
            } while (esSospechoso != 0 && esSospechoso != 1);
        }
    }
}

//Liberación de la zona de seguridad
void destruir(TCOLA *acceso, TCOLA arcosSeguridad[NUM_ARCOS], TLISTA *sospechosos){

    destruirCola(acceso);
    for(short i=0; i<NUM_ARCOS; i++)
        destruirCola(&arcosSeguridad[i]);
    destruirLista(sospechosos);
}

//Tratamiento de fichero por la cmd
void strip_line(char *linea) {
    linea [strcspn(linea, "\r\n")] = 0;
}

void procesar_fichero(TCOLA *acceso){

    char linea[200];

    FILE *datosPasajeros = fopen(optarg, "r");
    fseek(datosPasajeros, 0, SEEK_SET);
    while(!feof(datosPasajeros)){

        TIPOELEMENTO viajero;
        fgets(linea, 200, datosPasajeros);
        strip_line(linea);

        char *token = strtok(linea, ",");
        if(token != NULL)
            strcpy(viajero.pasaporte, token);

        token = strtok(NULL, ",");
        if(token != NULL)
            strcpy(viajero.apellidos, token);

        token = strtok(NULL, ",");
        if(token != NULL)
            strcpy(viajero.nombre, token);

        token = strtok(NULL, ",");
        if(token != NULL)
            strcpy(viajero.codVuelo, token);

        anadirElementoCola(acceso, viajero);
    }
    fclose(datosPasajeros);
}

//Programa principal
int main(int argc, char **argv) {

    TCOLA entrada;
    TCOLA arcos[NUM_ARCOS];
    TLISTA sospechosos;
    inicializa_zona_seguridad(&entrada, arcos, &sospechosos);

    if (argc <= 2)
        printf("\nPara insertar los datos de un archivo, escribir por línea de comandos: ./ejecutable -f NOMBRE_DEL_FICHERO\n");
    else{
        /*Lectura desde datos de fichero*/
        getopt(argc, argv, "f:");
        procesar_fichero(&entrada);
        escribe_estado_zona_seguridad(entrada, arcos, sospechosos);
    }

    char opcion;
    do {
        printf("\n\n-------------------- MENÚ -------------------\n\n");
        printf("a) Entrada de un pasajero al aeropuerto\n");
        printf("b) Situar a un pasajero en un arco\n");
        printf("c) Checkeo de seguridad\n");
        printf("s) Cerrar zona seguridad");
        printf("\n\n---------------------------------------------\n");

        printf("Opción: ");
        scanf(" %c", &opcion); //OJO: Espacio antes de %c para vaciar buffer de teclado

        switch (opcion) {
            case 'a':
                llega_a_aeropuerto(&entrada);
                escribe_estado_zona_seguridad(entrada, arcos, sospechosos);
                break;
            case 'b':
                arco_destino(arcos);
                entra_en_zona_seguridad(&entrada, arcos);
                escribe_estado_zona_seguridad(entrada, arcos, sospechosos);
                break;
            case 'c':
                arco_destino(arcos);
                pasa_por_arco(arcos, &sospechosos);
                escribe_estado_zona_seguridad(entrada, arcos, sospechosos);
                break;
            case 's':
                printf("\nSaliendo del programa...\n");
                destruir(&entrada, arcos, &sospechosos);
                break;
            default:
                printf("\nOPCIÓN INCORRECTA");
        }
    } while (opcion != 's');
}