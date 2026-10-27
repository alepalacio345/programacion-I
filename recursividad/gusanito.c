#include <stdio.h>

//estudiante: saul lara
// CI: 31456395

//prototipado
int gusanito(float profundidad,float dias_metros, float noches_metros, float metros_cansancio);

int main(){

    printf("         wellcome back         \n");
    int resultado = gusanito(6,3,1,0.3);

    if(resultado > 0){
            printf("el gusanito salio en el dia : %i",resultado);
    }else{
            printf("el gusanito se rendio en el dia: %i",resultado * -1);
    }

    return 0;
}


int gusanito(float profundidad,float dias_metros, float noches_metros, float metros_cansancio){

    //primer caso base logro salir
    if(dias_metros > profundidad){
        return 1;
    }
    //segundo caso base si se queda sin fuerzas 
    if(dias_metros <= 0){
        return -1;
    }

    int resultado = gusanito((profundidad - dias_metros) + noches_metros, dias_metros - metros_cansancio, noches_metros, metros_cansancio);

    if(resultado > 0){
        return resultado + 1;

    }else{
        return resultado - 1;
    }


}