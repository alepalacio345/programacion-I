#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_DIMENSIONES 9


void cargar_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int *num);
bool es_valido(int tamaño_caja, int fila, int columna, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int num_probar);

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

bool es_valido(int tamaño_caja, int fila, int columna, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int num_probar){

    bool salida;

    for(int i = 0; i < tamaño_caja; i++){
        //revisamos las filas y las columnas
        if( (matriz[fila][i] == num_probar) || (matriz[i][columna] == num_probar) ){
            salida = false;
        }


    }

    return salida;


}
