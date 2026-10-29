/*
 * Saul Alejandro Lara Palacio
 * Cedula: 31456395
 * Parcial de TDA
 * Programacion 1
 */

#include <stdio.h>
#include "mis_librerias.h"


int main(){

    //var
    Cola *cola_tiempos;
    FILE *entrada;
    int tiempo;
    int tarea_tiempo;

    //crear cola
    cola_tiempos = crear_cola();

    //abrir archivo
    entrada = fopen("tiempos.txt","r");

    //validar apertura
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
        destruir_cola(cola_tiempos);
    }else{
        
        //obtenemos info del archivo
        while(fscanf(entrada,"%d",&tiempo) != EOF){
            encolar(cola_tiempos,tiempo);
        }

        if(cola_es_vacia(cola_tiempos) != 1){
            printf("--- INICIANDO SIMULACIÓN DE RENDIMIENTO ---\n");
            printf("Quantum de procesamiento: 15s\n");

            // Mientras la cola no esté vacía desencolar el frente
            while (cola_es_vacia(cola_tiempos) != 1){
                
                if(desencolar(cola_tiempos,&tarea_tiempo) == 1 ){

                    printf("Procesando tarea de %d. ",tarea_tiempo);

                    if(tarea_tiempo <= 15){
                        printf("Terminada\n");
                    }else{
                        tarea_tiempo = tarea_tiempo - 15;
                        encolar(cola_tiempos,tarea_tiempo);
                        printf("Restan %d -> Regresa a la cola.\n",tarea_tiempo);
                    }

                }
            
            }
            printf("--- TODAS LAS TAREAS FUERON COMPLETADAS ---\n");
        }

        //cerramos
        fclose(entrada);
        destruir_cola(cola_tiempos);

    }
    
    return 0;
}