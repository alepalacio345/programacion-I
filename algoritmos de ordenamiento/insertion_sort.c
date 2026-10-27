#include <stdio.h>




void insertion_sort(int *vector, int n){

    for(int i = 1; i < n; i++){
        
        int actual = vector[i];

        int j = i - 1;

        while(j >= 0 && vector[j] > actual){
            vector[j + 1] = vector[j];
            j--;
        }

        vector[j + 1] = actual;

    }

}


void imprimir(int *vector, int n){
    for(int i = 0; i < n; i++){
        printf("%i ", vector[i]);
    }
    printf("\n");
}


int main(){

    int vector[5] = {3,4,5,1,-3};

    imprimir(vector,5);

    insertion_sort(vector,5);

    imprimir(vector,5);


    return 0;
}