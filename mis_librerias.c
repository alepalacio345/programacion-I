#include <stdio.h>
#include <stdlib.h>
#include "mis_librerias.h"


// inicializamos la lista
Lista* crear_lista(){

    Lista *mi_lista = (Lista *)(malloc(sizeof(Lista)));
    mi_lista->cabeza = NULL;
    mi_lista->cola = NULL;

    return mi_lista;

}

//imprimimos todos los elementos de la lista
void imprimir_lista(Lista *mi_lista){
    Nodo *aux = mi_lista->cabeza;
    //validacion para ver si la cabeza esta vacia
    if(aux == NULL){
        printf("la lista esta vacia :( \n");
    }else{
        //forma de recorrer la lista y mostrar el valor 
        while(aux != NULL){
            printf("%d \n",aux->dato);
            //avancamos al siguiente vagon
            aux = aux->siguiente;
        }
    }
}



void agregar_al_principio(Lista *mi_lista, int valor){

    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo)); //reservamos espacio en la memoria

    if(nuevo == NULL){
        printf("error no hay espacio en la memoria");
        return;
    }else{
        //le vamos el valor al nodo
        nuevo->dato = valor;
        //paso todo lo anterior detras de la nuevo
        nuevo->siguiente = mi_lista->cabeza;
        // y pongo el nuevo como cabeza
        mi_lista->cabeza = nuevo;

        //validamos si la cola esta vacia
        if(mi_lista->cola == NULL){
            mi_lista->cola = nuevo;
        }
    }
}


void agregar_al_final(Lista *mi_lista,int valor){
    //ahora pedimos memoria para los nodos 
    // y hacemos una validacion por si no queda memoria libre
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));

    if(nuevo == NULL){
        printf("error no hay memoria disponible para usar\n");
        return ;
    }else{

        nuevo->dato = valor;
        nuevo->siguiente = NULL;

        //validamos que la cabeza este vacia y si lo esta la cabeza y la cola apuntan ahora al nuevo elemento
        if(mi_lista->cabeza == NULL){
            mi_lista->cabeza = nuevo; 
            mi_lista->cola   = nuevo;
        }else{

            //enganchamos el nuevo elemento al final
            mi_lista->cola->siguiente = nuevo;
            mi_lista->cola = nuevo;      
        }
    }
}



//// FUNCIONES NECESARIAS PARA USAR EN EL ALGORITMO DE ORDENAMIENTO ////


/// intercambio de variables ///
void intercambiar(int *a, int *b){
    int temporal = *a;
    *a = *b;
    *b = temporal;
}


