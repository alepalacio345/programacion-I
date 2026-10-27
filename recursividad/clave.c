#include <stdio.h>
#include <string.h>

void generador_clave(char *diccionario, char *regla, char *repuesta, int index);


int main(){

    printf("welcome back\n");

    //var
    FILE *entrada;

    //abrir
    entrada = fopen("entrada.txt", "r");

    //var
    int numero_caracteres;
    int numero_caracter_regla;

    char  diccionario[100];
    char  regla[100];
    char  repuesta[100];

    if(entrada == NULL){
        printf("error\n");
    }else{


        //fscanf(entrada,"%i",&numero_caracteres);

        scanf("%i",&numero_caracteres);
        


        //ciclo

        for(int i = 0; i < numero_caracteres; i++){
            fscanf(entrada," %c",&diccionario[i]);
            diccionario[i + 1] = '\0';
        }

        printf("%s ",diccionario);


        //fscanf(entrada,"%i",&numero_caracter_regla);
        scanf("%i",&numero_caracter_regla);

        for(int j = 0; j < numero_caracter_regla; j++){

            fscanf(entrada,"%s\n",regla);
            printf("--\n");
            generador_clave(diccionario,regla, repuesta, 0);
        }



    }


    //fclose(entrada);




    return 0;
}


void generador_clave(char *diccionario, char *regla, char *repuesta, int index){

    if(index < strlen(regla)){

        if(regla[index] == '#'){

            for(int i = 0; i < strlen(diccionario); i++){
                repuesta[index] = diccionario[i];
                repuesta[index + 1] = '\0';
                generador_clave(diccionario,regla,repuesta,index + 1);
            }

        }else{
            for(int j = 0; j <= 9; j++){
                repuesta[index] = j + '0';
                repuesta[index + 1] = '\0';
                generador_clave(diccionario,regla,repuesta,index + 1);
            }
        }

        repuesta[index] = '\0';
        

    }else{
        printf("%s\n",repuesta);
    }



}