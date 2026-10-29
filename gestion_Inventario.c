/*
 * Saul Alejandro Lara Palacio
 * Cedula: 31456395
 * Parcial de TDA
 * Programacion 1
 */

#include <stdio.h>
#include <stdlib.h>
#include "lista_item.h"


int main(void){

    //var
    FILE *entrada;
    ListaItem *lista_objetos;
    char nombre[30];
    int durabilidad;
    char categoria;

    Item *actual;
    Item *anterior;
    Item *siguiente;
    int armas = 0;
    int pociones = 0;
    int materiales = 0;

    //crear lista de objetos
    lista_objetos = crear_lista_item();

    //abrir archivo
    entrada = fopen("inventario.txt","r");

    //validar apertura
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
        destruir_lista_item(lista_objetos);
        return 1;
    }else{

        //llenamos la lista con la informacion
        while(fscanf(entrada,"%s %c %d",nombre,&categoria,&durabilidad) == 3){
            lista_item_insertar_final(lista_objetos,nombre,categoria,durabilidad);
        }

        //limpieza de objetos destruidos
        actual = lista_objetos->cabeza;
        anterior = NULL;

        while(actual != NULL){
            siguiente = actual->siguiente;

            if(actual->durabilidad == 0){
                if(anterior == NULL){
                    lista_objetos->cabeza = siguiente;
                }else{
                    anterior->siguiente = siguiente;
                }

                if(actual == lista_objetos->cola){
                    lista_objetos->cola = anterior;
                }

                free(actual);
                lista_objetos->longitud--;
            }else{
                anterior = actual;
            }

            actual = siguiente;
        }

        printf("\nInventario resultante:\n");

        actual = lista_objetos->cabeza;

        while(actual != NULL){
            printf("- %s | Categoria: %c | Durabilidad: %d\n",actual->nombre,actual->categoria,actual->durabilidad);

            if(actual->categoria == 'A'){
                armas++;
            }else if(actual->categoria == 'P'){
                pociones++;
            }else if(actual->categoria == 'M'){
                materiales++;
            }

            actual = actual->siguiente;
        }

        printf("\nArmas: %d\n",armas);
        printf("Pociones: %d\n",pociones);
        printf("Materiales: %d\n",materiales);
        printf("Total: %d\n",lista_objetos->longitud);
                
        
        //cerramos
        fclose(entrada);
        destruir_lista_item(lista_objetos);

    }
    
    return 0;
}