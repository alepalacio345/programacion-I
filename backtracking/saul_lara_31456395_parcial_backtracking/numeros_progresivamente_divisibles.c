#include <stdio.h>
#include <stdbool.h>

#define MIN_CIFRAS 1
#define MAX_CIFRAS 9

bool validar_no_repetido(bool vector_estados[], int digito);
void backtracking_generar_num(int cifras, int numero, int nivel, bool vector_estados[]);

int main(){
    // var
    int cifras;
    bool vector_estados[10] = {false};   // true = el digito ya se uso

    printf("ingresa la cifra de los numeros: ");
    if(scanf("%d", &cifras) != 1){
        printf("Error al leer M\n");
        return 1;
    }

    // validar el rango
    if(cifras < MIN_CIFRAS || cifras > MAX_CIFRAS){
        printf("M debe estar entre %d y %d\n", MIN_CIFRAS, MAX_CIFRAS);
        return 1;
    }

    backtracking_generar_num(cifras, 0, 0, vector_estados);

    return 0;
}

/*
 * backtracking_generar_num: arma el numero cifra por cifra.
 *   cifras -> cuantas cifras debe tener el numero
 *   numero -> numero armado hasta ahora
 *   nivel  -> cuantas cifras lleva "numero"
 *   vector_estados -> que digitos ya se usaron
 */
void backtracking_generar_num(int cifras, int numero, int nivel, bool vector_estados[]){

    // ya tiene las cifras pedidas
    if(nivel == cifras){
        printf("%d\n", numero);
        return;
    }

    // probamos cada digito
    for(int i = 1; i <= 9; i++){

        // si el digito ya se uso, lo saltamos
        if(!validar_no_repetido(vector_estados, i)){
            continue;
        }

        // armamos el nuevo numero
        int nuevo = numero * 10 + i;

        // el prefijo debe ser divisible entre su cantidad de cifras
        if(nuevo % (nivel + 1) != 0){
            continue;
        }

        // hacer marco el digito y bajo
        vector_estados[i] = true;

        backtracking_generar_num(cifras, nuevo, nivel + 1, vector_estados);

        // deshacer lo libero al volver
        vector_estados[i] = false;
    }
}

// revisa si el digito esta libre
bool validar_no_repetido(bool vector_estados[], int digito){
    return vector_estados[digito] == false;
}
