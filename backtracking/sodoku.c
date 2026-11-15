#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_DIMENSIONES 9


void cargar_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int *num);
bool es_valido(int tamaño_caja, int fila, int columna, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], char num_probar);

int main(){

    //var
    char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES];
    int num;

    cargar_matriz(matriz,&num);


    return 0;
}


void cargar_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int *num){
    //var
    FILE *entrada;
    char letra;
    int column = 0; 
    int fila = 0;

    //abrir archivo
    entrada = fopen("sodoku_entrada.txt", "r");

    if(entrada == NULL){
        printf("error al abrir el archivo\n");
    }else{
        fscanf(entrada,"%i",&num);

        while( (letra = fgetc(entrada)) != EOF){
            //aumentamos las filas si llegamos a un \n
            if(letra == '\n'){
                fila++;
            }
            // si es un numero entonces se guarda
            if(isdigit((unsigned char)letra)){
                matriz[fila][column] = letra;
                column++;
            }
        }
        fclose(entrada);
    }
}

bool es_valido(int tamaño_caja, int fila, int columna, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], char num_probar){

    int fila_cajita;
    int columna_cajita;

    //calcumos en que cajita estamo ("alto truco de gemenis")
    fila_cajita    = fila - (fila % tamaño_caja); // fila donde inicia la cajita
    columna_cajita = columna - (columna % tamaño_caja); // columna donde inicia la cajita

    for(int i = 0; i < MAX_DIMENSIONES; i++){
        //revisamos las filas y las columnas
        if( (matriz[fila][i] == num_probar) || (matriz[i][columna] == num_probar) ){
            return false;
        }
    }

    for(int k = 0; k < tamaño_caja; k++){
        for(int j = 0; j < tamaño_caja; j++){
            if(matriz[fila_cajita + k][columna_cajita + j] == num_probar){
                return false;
            }
        }
    }

    return true;
}
