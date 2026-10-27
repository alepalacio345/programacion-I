#include <stdio.h>
#define FILA 3
#define COLUMNAS 3



void imprimir_matriz(int matriz[FILA][COLUMNAS], int n, int m, int i, int j);



int main(){

    int i = 0, j = 0;

    int matriz[FILA][COLUMNAS] = {

        {9,9,7},
        {7,5,3},
        {9,7,4}
    };


    imprimir_matriz(matriz,3,3,i,j);




    return 0;
}


void imprimir_matriz(int matriz[FILA][COLUMNAS], int n, int m, int i, int j){

        if( n == i){
            return;
        
            

        if(j == m){

                j = 0;
                i = i + 1;
                printf("\n");
                printf("%i ", matriz[i][j]);
                
                imprimir_matriz(matriz,n,m,i,j);

        }else{

                printf("%i ", matriz[i][j]);
                imprimir_matriz(matriz,n,m,i,j + 1);
        }
    

}