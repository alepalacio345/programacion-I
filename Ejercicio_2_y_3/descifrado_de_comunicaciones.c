/*
 * Saul Alejandro Lara Palacio
 * Cedula: 31456395
 * Parcial de TDA
 * Programacion 1
 */

#include <stdio.h>
#include <ctype.h>
#include "mis_librerias.h"
#define OK printf("ok");


int main(){

    //var
    FILE *entrada;
    Lista *lista_chars;
    Pila *pila_palabras;
    int caracter;
    int cantidad_elementos_l = 0;
    int caracter_desapilado;
    int bandera = 1;


    //crear lista y pila
    lista_chars = crear_lista();
    pila_palabras = crear_pila();

    //abrir archivo
    entrada = fopen("interceptado.txt","r");

    //validar apertura
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
        destruir_lista(lista_chars);
        destruir_pila(pila_palabras);
    }else{


        // llenamos la lista con los caracteres
        while( (caracter = fgetc(entrada)) != EOF ){
            //obtenemos la cantidad de elementos
            cantidad_elementos_l = lista_longitud(lista_chars);
            lista_insertar(lista_chars,cantidad_elementos_l + 1,caracter);
        }

        //recorremos la lista
        for(int i = 1; i <= lista_longitud(lista_chars);i++){

            // entra al bloque si el valor se copio bien
            if(lista_consultar(lista_chars,i,&caracter)){

                //si es espacio entra 
                if( (isspace((unsigned char) caracter)) ){

                    printf("\nExtrayendo letras a la Pila auxiliar...\n");

                    if(caracter == '\n'){
                        printf("\nFin de lista detectado. Palabra descifrada:");
                    }else{
                        printf("\nEspacio detectado.Palabra descifrada:");
                    }

                    while(desapilar(pila_palabras,&caracter_desapilado)){
                        printf("%c",caracter_desapilado);
                    }

                    vaciar_pila(pila_palabras);

                    printf("\n");



                }else{
                    //apilamos 
                    apilar(pila_palabras,caracter);
                }
            }

        }
        
        printf("\nMensaje original: ");
        //mostramos mensaje completo
        for(int i = 1; i <= lista_longitud(lista_chars); i++){

            if(lista_consultar(lista_chars,i,&caracter)){

                if(isspace((unsigned char) caracter)){
                    
                    //solo imprimimos si hay una palabra pendiente
                    if(!pila_es_vacia(pila_palabras)){

                        if(!bandera){
                            printf(" ");
                        }
                        while(desapilar(pila_palabras,&caracter_desapilado)){
                            printf("%c",caracter_desapilado);
                        }
                        bandera = 0;
                    }
                }else{
                    apilar(pila_palabras,caracter);
                }
            }
        }

        if(!pila_es_vacia(pila_palabras)){
            if(!bandera){
                printf(" ");
            }
            while(desapilar(pila_palabras,&caracter_desapilado)){
                printf("%c",caracter_desapilado);
            }
        }

        printf("\n");

        fclose(entrada);
        destruir_lista(lista_chars);
        destruir_pila(pila_palabras);

    }
    
    return 0;
}