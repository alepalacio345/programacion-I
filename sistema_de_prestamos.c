/*
 * Saul Alejandro Lara Palacio
 * Cedula: 31456395
 * Parcial de TDA
 * Programacion 1
 */

#include <stdio.h>
#include "lista_prestamo.h"
#include <string.h>


int main(void){

    //var
    FILE *entrada;
    ListaPrestamo *lista_prestaciones;
    PilaPrestamo *pila_Deshacer;
    Prestamo info_prestamo;

    char linea_completa[60]; 
    char letra;
    char cedula[20];
    char codigo[20];
    char hora[10];

    //crear lista y pila
    lista_prestaciones = crear_lista_prestamo();
    pila_Deshacer = crear_pila_prestamo();


    //abrir archivo
    entrada = fopen("prestamos.txt","r");

    //validar apertura
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
        destruir_lista_prestamo(lista_prestaciones);
        destruir_pila_prestamo(pila_Deshacer);
        return 1;
    }else{
        //leemos la línea completa
        while(fgets(linea_completa, sizeof(linea_completa), entrada) != NULL){

            //leemos la primera letra para saber que decision tomar 
            if(sscanf(linea_completa, " %c", &letra) == 1){

                switch (letra){
                    case 'P':
                        if(sscanf(linea_completa, " %c %19s %19s %9s",&letra,cedula,codigo,hora) != 4){
                            printf("Linea P invalida.\n");
                            break;
                        }

                        //pasamos todo a info presetamo y despues lo ponemos al final
                        // de la lista y vaciamos la pila de prestamos
                        strcpy(info_prestamo.cedula,cedula);
                        strcpy(info_prestamo.codigo,codigo);
                        strcpy(info_prestamo.hora,hora);

                        if(lista_prestamo_insertar_final(lista_prestaciones,&info_prestamo)){
                            vaciar_pila_prestamo(pila_Deshacer);
                        }
                    break;

                    case 'D':
                        // validamos si esta vacia la lista
                        if(!lista_prestamo_es_vacia(lista_prestaciones)){
                            lista_prestamo_eliminar_final(lista_prestaciones,&info_prestamo);
                            pila_prestamo_apilar(pila_Deshacer,&info_prestamo);
                        }else{
                            printf("No hay prestamos para deshacer.\n");
                        }
                    break;

                    case 'R':
                        // lo pasamos de la pila al final de la lista
                        if(pila_prestamo_desapilar(pila_Deshacer,&info_prestamo)){
                            lista_prestamo_insertar_final(lista_prestaciones,&info_prestamo);
                        }else{
                            printf("No hay prestamos para rehacer.\n");
                        }

                    break; 
                        
                    default:
                        break;
                }
            }
        }

        //mostramos la lista y la cantidad de prestamos
        lista_prestamo_imprimir(lista_prestaciones);
        printf("\nTotal de prestamos: %d\n",lista_prestamo_longitud(lista_prestaciones));



        //cerramos
        fclose(entrada);
        destruir_lista_prestamo(lista_prestaciones);
        destruir_pila_prestamo(pila_Deshacer);

    }
    
    return 0;
}