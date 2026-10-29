#include <stdio.h>
#include "mis_librerias.h"

//librerias para generar un numero aletorio
#include <stdlib.h>
#include <time.h>


void llenamos_lista(Lista *lista, int caliadad_elementos){

    int numero;

    for(int i = 1; i <= caliadad_elementos; i++){

        numero = rand() % 100; // se crea un numero entre 0 a 99

        lista_insertar(lista,i,numero);
    }

}



int main(){

    /* Semilla: una sola vez, al inicio del programa */
    srand((unsigned int) time(NULL));



    //var 
    Lista *lista_a;
    Lista *lista_b;

    int cantidad_elementos_b;
    int valor_encontrado;

    //crear lista
    lista_a = crear_lista();
    lista_b = crear_lista();

    llenamos_lista(lista_a,20);
    llenamos_lista(lista_b,50);

    //obtenemos la cantidad de elementos
    cantidad_elementos_b = lista_longitud(lista_b);


    // imagenesmos que esta cargada las listas
    for(int i = 1; i <= cantidad_elementos_b; i++){

        if(lista_consultar(lista_b,i,&valor_encontrado)){

            lista_insertar(lista_a, lista_longitud(lista_a) + 1,valor_encontrado);
        }
    }

    //mostramos la nueva lista
    imprimir_lista(lista_a);

    //eliminar lista
    destruir_lista(lista_a);
    destruir_lista(lista_b);




    return 0;
}