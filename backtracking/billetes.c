#include <stdio.h>
#include <stdbool.h>
#define MAX_BILLTES 5
#define MAX_COMBINACIONES 1000

bool backtracking_primera_solucion(int vector[], int acumulador, int vector_num[], int *j);
void imprimir_vector(int vector[], int n);

int main(){
    //var
    int vector_billetes[MAX_BILLTES] = {1,5,10,50,100}; // billetes que tiene el cajero
    int vector_numeros[MAX_COMBINACIONES];
    int j = 0;
    backtracking_primera_solucion(vector_billetes,0,vector_numeros,&j);
    return 0;
}

bool backtracking_primera_solucion(int vector[], int acumulador, int vector_num[], int *j){

    //var
    int i = 0;

    //primero validamos que se cumpla el problema de entregar
    // 100 dolares, buscamos la primera solucion no importa 
    // cual sea 
    if(acumulador == 100){
        printf("solucion encontrada\n");
        imprimir_vector(vector_num,*j);
        
        return true;
    }

    if(acumulador > 100){
        return false;
    }

    while(i < MAX_BILLTES){

        vector_num[*j] = vector[i];
        (*j)++;
        
        if(backtracking_primera_solucion(vector,acumulador + vector[i],vector_num,j)){
            return true;
        }
        acumulador = acumulador - vector[i];
        vector_num[*j] = 0;
        i++;
        
    }
}

void imprimir_vector(int vector[], int n){
    printf("[");
    for(int i = 0; i < n;i++){
        printf("%d ",vector[i]);
    }
    printf("] \n");
}
