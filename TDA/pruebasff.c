#include <stdio.h>
#include <stdlib.h>
#include "mis_librerias.h"

int main(){

    //var
    int edad;
    Lista *lista_edades;
    int contador = 1;

    //iniciar lista
    lista_edades = crear_lista();

    printf("wellcome back\n");
    printf("para salir marca -1 \n");
    printf("Ingresa las edades de tus amigos: ");


    do{
        scanf("%i",&edad);

        if(edad != -1){
            lista_insertar(lista_edades,contador,edad);
            contador++;
        }
        
    }while(edad != -1);

    imprimir_lista(lista_edades);
    destruir_lista(lista_edades);

    return 0;
}
