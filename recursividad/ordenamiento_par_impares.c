#include <stdio.h>


//primero hacemos la funcion de intercambio
void intercambio(int *a, int *b){
   int temporal = *a;
   *a = *b;
   *b = temporal;
}


void ordenar_separar(int *vector, int n, int i){

    //caso base cuando llega al final de el vector
    if(i == (n - 1)){
        return;
    }else{
        // casos recuersivos
        // si A es impar y B es par los intercambiamos
        if( ( (vector[i] % 2) == 1 ) && ( (vector[i + 1] % 2) == 0) ){

            intercambio(&vector[i],&vector[i + 1]);


         // si no, si ambos son iguales los ordenados de menor a mayor
        }else if( ( (vector[i] % 2) == (vector[i + 1] % 2) ) &&  (vector[i] > vector[i + 1]) ){
                intercambio(&vector[i],&vector[i + 1]);
        }

        ordenar_separar(vector, n, i + 1);
    }


}


void ordenamiento_principal(int *vector, int n){

    if(n == 1){
        return;
    }

    ordenar_separar(vector, n, 0);

    //recuersicion
    ordenamiento_principal(vector, n - 1);
}


int main(){

    int vector[10] = {5,6,8,12,8,3,1,7,9,3};

    ordenamiento_principal(vector,10);

    for (int i = 0; i < 10; i++)
    {
        printf("%i ", vector[i]);
    }
    printf("\n");
    


    return 0;
}