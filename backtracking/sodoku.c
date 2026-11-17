#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_DIMENSIONES 9
#define ok printf("ok\n");


bool validar_fin(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES],int filas, int columnas);
void imprimir_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES],int filas, int columnas);
void cargar_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int *num);
bool es_valido(int tamano_caja, int filas, int columnas, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], char num_probar);
/**
 * @brief la mama de los helados es la funcion principal para hacer
 * el backtracking
**/
bool backtracking(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int filas, int columnas,int tamano_cajita);




int main(){

    //var
    char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES];
    int num;
    int filas, columnas;
    
    cargar_matriz(matriz,&num);

    filas = num * num;
    columnas = num * num;
    
    printf("Soduku original: \n");
    imprimir_matriz(matriz,filas,columnas);

    printf("\nResultado: \n");
    if(!backtracking(matriz,filas,columnas,num)){
        printf("NO HAY SOLUCIÓN\n");
    }
    


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
        fscanf(entrada,"%i\n",num);

        while( (letra = fgetc(entrada)) != EOF){
            //aumentamos las filas si llegamos a un \n
            if(letra == '\n'){
                fila++;
                column = 0;
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

bool es_valido(int tamano_caja, int filas, int columnas, char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], char num_probar){

    int fila_cajita;
    int columna_cajita;

    //calcumos en que cajita estamo ("alto truco de gemenis")
    fila_cajita    = filas - (filas % tamano_caja); // fila donde inicia la cajita
    columna_cajita = columnas - (columnas % tamano_caja); // columna donde inicia la cajita

    for(int i = 0; i < tamano_caja * tamano_caja; i++){
        //revisamos las filas y las columnas
        if( (matriz[filas][i] == num_probar) || (matriz[i][columnas] == num_probar) ){
            return false;
        }
    }

    for(int k = 0; k < tamano_caja; k++){
        for(int j = 0; j < tamano_caja; j++){
            if(matriz[fila_cajita + k][columna_cajita + j] == num_probar){
                return false;
            }
        }
    }

    return true;
}




bool backtracking(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES], int filas, int columnas, int tamano_cajita){

    if(validar_fin(matriz,filas,columnas)){
        imprimir_matriz(matriz,filas,columnas);
        return true;
    }
        
    for(int i = 0; i < filas;i++){
        for(int j = 0; j < columnas;j++){

            if(matriz[i][j] == '0'){
                
                for(int k = 1; k <= filas;k++){
                    
                    if(es_valido(tamano_cajita,i,j,matriz,k + '0')){
                        matriz[i][j] = k + '0';

                        //hacemos
                        if(!backtracking(matriz,filas,columnas,tamano_cajita)){
                            //desacemos
                            matriz[i][j] ='0';
                        }else{
                            return true;
                        }
                    }
                }
                //desacemos
                return false;

            }

        }
    }

}

bool validar_fin(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES],int filas, int columnas){

    for(int i = 0; i < filas;i++){
        for(int j = 0; j < columnas;j++){
            
            if(matriz[i][j] == '0'){
                return false;
            }
        }
    }

    return true;

}


void imprimir_matriz(char matriz[MAX_DIMENSIONES][MAX_DIMENSIONES],int filas, int columnas){

    printf("\n");

    for(int i = 0; i < filas;i++){
        for(int j = 0; j < columnas;j++){
            printf("%c ",matriz[i][j]);
        }
        printf("\n");
    }

}
