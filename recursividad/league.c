#include <stdio.h>



float total_LP(int *vector, int num, int i);
void Mayor_LP(int *vector, int num, int i, int *mayor);
void Mayor_lognitud(int *vector, int num, int i,int *acum, int *mayor);

int main(){

    int vector_jugadas[10] = {19,-21,25,18,-15,0,22,20,24,-18};

    float promedio;
    int mayor_ganancia = -9999999; 
    int mayor_racha = -999999;
    int acum = 0;


    promedio = total_LP(vector_jugadas, 10, 0);
    printf("balance total de la temporada: %1.f\n", promedio);

    Mayor_LP(vector_jugadas, 10, 0,&mayor_ganancia);
    printf("mayor LP de la temporada: %i \n", mayor_ganancia);

    Mayor_lognitud(vector_jugadas, 10, 0,&acum, &mayor_racha);
    printf("mayor logitud de numeros positivos: %i \n", mayor_racha);

    return 0; 
}


float total_LP(int *vector, int num, int i){
    //cuando se salga el tamaño del vector retorna cero
    if(i >= num){
        return 0;
    }else{

        return ( (float)vector[i] / num) + total_LP(vector,num, i + 1);

    }

}


void Mayor_LP(int *vector, int num, int i,int *mayor){

    if(i >= num){
        return;
    }else{

        if(vector[i] >= *mayor){
            *mayor = vector[i];
        }
        //importante en esta recursion solo uso la 
        // llamada a la funcion por que esta muere cuando llega al final 
        // osea no se devuelve no puedo usar el return 
        Mayor_LP(vector, num, i + 1, mayor);
    }

}


void Mayor_lognitud(int *vector, int num, int i,int *acum, int *mayor){

    if(i >= num){
        return;
    }else{

        //acumulados esta encontrar un negativo 0 cero
        if(vector[i] > 0){
            *acum = *acum + 1;
        }else{
            //vemos quien es la mayor longitud 
            if(*acum >= *mayor){
                *mayor = *acum;
            }

            //reinicio acum
            *acum = 0; 

        }

        Mayor_lognitud(vector, num, i + 1, acum, mayor);

    }

}
