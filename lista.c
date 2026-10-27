#include <stdio.h>
#include <stdlib.h>
#include "mis_librerias.h"

int main(){

    Lista *lista = crear_lista();


    agregar_al_final(lista,20);
    agregar_al_final(lista,30);
    agregar_al_final(lista,35);

    imprimir_lista(lista);

    agregar_al_principio(lista,42);
    imprimir_lista(lista);



    return 0;
}