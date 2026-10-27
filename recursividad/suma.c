#include <stdio.h>



int suma(int a, int b);

int main(){

    int resultado;

    resultado = suma(2,2);

    printf("%i ",resultado);

    return 0;
}



int suma(int a, int b){

    if(b == 0){
        return (a);
    }else{
        return(suma(a + 1, b - 1));
    }


}