#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LETRAS 50
#define MAX_MUNICIPIOS 100

typedef struct{
    char nombre[MAX_LETRAS];
}municipios;

typedef struct{
    char municipio01[MAX_LETRAS];
    char municipio02[MAX_LETRAS];
}fronteras_muni;


int main(){

    FILE *entrada;
    int num_proyectos = 0;
    int num_de_municipios = 0;
    int cantidad_colores = 0;
    int fronteras = 0;
    char linea[256];
    char letra;
    char vector_aux[MAX_LETRAS];

    municipios vector_municipios[MAX_MUNICIPIOS];
    fronteras_muni vector_fonteras[MAX_MUNICIPIOS];

    //abrir archivo
    entrada = fopen("entrada_03_ejemplo_parcial.txt", "r");

    //validamos apertura del archivo
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
    }else{
        fscanf(entrada,"%i\n",&num_proyectos);
        printf("%d\n",num_proyectos);

        //cantidad de proyectos
        for (int  i = 0; i < num_proyectos; i++){

            fscanf(entrada,"%d %d\n", &num_de_municipios, &cantidad_colores);
            printf("%d %d\n", num_de_municipios, cantidad_colores);

            // guardamos municipios
            for(int j = 0; j < num_de_municipios; j++){
                // Leemos la línea
                if(fgets(vector_municipios[j].nombre, sizeof(vector_municipios[j].nombre), entrada) != NULL) {
                    // Le cortamos el \n
                    vector_municipios[j].nombre[strcspn(vector_municipios[j].nombre, "\n")] = '\0';
                }
                printf("%s\n", vector_municipios[j].nombre);
            }

            fscanf(entrada,"%i\n",&fronteras);
            printf("%i\n",fronteras);

            // Guardamos fronteras
            for (int k = 0; k < fronteras; k++) {
                
                // Leemos la línea COMPLETA
                if (fgets(linea, sizeof(linea), entrada) != NULL) {
                    
                    // Le cortamos el \n
                    linea[strcspn(linea, "\n")] = '\0';
                    
                    // PARTIMOS LA LÍNEA usando strtok buscará el separador "|"
                    char *parte_1 = strtok(linea, "|");
                    char *parte_2 = strtok(NULL, "|");
                    
                    // Guardamos en la estructura
                    strcpy(vector_fonteras[k].municipio01, parte_1);
                    strcpy(vector_fonteras[k].municipio02, parte_2);
                    
                    printf("%s|%s\n", vector_fonteras[k].municipio01, vector_fonteras[k].municipio02);
                }
            }
        }
        fclose(entrada);
    }
        
    return 0;
}