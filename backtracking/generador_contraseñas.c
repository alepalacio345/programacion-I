#include <stdio.h>
#define MAX_LETRAS 256
#define MAX_PALABRAS 100
#define MAX_REGLAS 1000


//vector de strings tambien se puede hacer un matriz y listo las filas son
// las palabras y las columnas sus letras
typedef struct{
    char palabra[MAX_LETRAS];
}diccionario_palabras;

typedef struct{
    char regla[MAX_LETRAS];
}diccionario_reglas;


void crear_backtracking(int cantidad_palabras, diccionario_palabras Dicionario[],int cantidad_reglas,diccionario_reglas Dicionario_reglas[]);



int main(){

    //var 
    FILE *entrada;
    int cantidad_palabras_DC;
    int cantidad_reglas;

    //vector strings
    diccionario_palabras Dicionario[MAX_PALABRAS];
    //vertor reglas
    diccionario_reglas Dicionario_reglas[MAX_REGLAS];
    //abrir archivo
    entrada = fopen("entrada_contrasena.txt", "r");

    //verificar si se abrio correctamente
    if(entrada == NULL){
        printf("Error al abrir el archivo\n");
    }else{
        
        //buscamos en el archivo hasta llegar al final
        while(fscanf(entrada,"%d\n",&cantidad_palabras_DC) != EOF){

            //leemos las palabras del dicionario
            for(int i = 0; i < cantidad_palabras_DC;i++){
                //guardamos la palabra
                fscanf(entrada,"%s\n",Dicionario[i].palabra);
            }
            
            //cantidad de reglas
            fscanf(entrada,"%d\n",&cantidad_reglas);
            
            //obtenemos las reglas del diccionario
            for (int j = 0; j < cantidad_reglas; j++){
                fscanf(entrada,"%s\n",Dicionario_reglas[j].regla);
            }

            printf("--\n");
            
        }

        //cerramos el archivo 
        fclose(entrada);
    }
    return 0;
}


void crear_backtracking(int cantidad_palabras, diccionario_palabras Dicionario[],int cantidad_reglas,diccionario_reglas Dicionario_reglas[]){

    


}