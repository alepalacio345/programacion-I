#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LETRAS 50
#define MAX_MUNICIPIOS 15
#define MAX_FRONTERAS 100

typedef struct{
    char nombre[MAX_LETRAS];
}municipios;

typedef struct{
    char municipio01[MAX_LETRAS];
    char municipio02[MAX_LETRAS];
}fronteras_muni;

// prototipos
void quitar_salto_de_linea(char cadena[]);
void separar_por_barra(char linea[], char nombre01[], char nombre02[]);
int  buscar_municipio(municipios vector_municipios[], int num_de_municipios, char nombre[]);
bool es_posible_colorear(int indice, int num_de_municipios, int cantidad_colores, int matriz_adyacencia[][MAX_MUNICIPIOS], int vector_colores[]);


int main(){

    FILE *entrada;

    int num_proyectos = 0;
    int num_de_municipios = 0;
    int cantidad_colores = 0;
    int fronteras = 0;
    int indice01, indice02;

    municipios vector_municipios[MAX_MUNICIPIOS];
    fronteras_muni vector_fronteras[MAX_FRONTERAS];

    // estado del proyecto: quien es vecino de quien y que color tiene cada uno
    int matriz_adyacencia[MAX_MUNICIPIOS][MAX_MUNICIPIOS];
    int vector_colores[MAX_MUNICIPIOS];

    // buffer de lectura
    char linea[MAX_LETRAS];

    //abrir archivo
    entrada = fopen("entrada_03_ejemplo_parcial.txt", "r");

    //validamos apertura del archivo
    if(entrada == NULL){
        printf("error al abrir el archivo\n");
        return 1;
    }

    //cantidad de proyectos
    if(fscanf(entrada, "%d", &num_proyectos) != 1){
        printf("error al leer la cantidad de proyectos\n");
        fclose(entrada);
        return 1;
    }
    fgets(linea, MAX_LETRAS, entrada);          // nos comemos el resto de esa linea

    for(int i = 0; i < num_proyectos; i++){

        if(fscanf(entrada, "%d %d", &num_de_municipios, &cantidad_colores) != 2){
            break;
        }
        fgets(linea, MAX_LETRAS, entrada);      // el fscanf deja el '\n' pendiente

        //guardamos municipios: la linea completa, porque los nombres traen espacios
        for(int j = 0; j < num_de_municipios; j++){
            if(fgets(vector_municipios[j].nombre, MAX_LETRAS, entrada) == NULL){
                break;
            }
            quitar_salto_de_linea(vector_municipios[j].nombre);
        }

        if(fscanf(entrada, "%d", &fronteras) != 1){
            break;
        }
        fgets(linea, MAX_LETRAS, entrada);      // otra vez, consumimos el '\n'

        //la matriz arranca en cero: cada proyecto es independiente del anterior
        for(int a = 0; a < MAX_MUNICIPIOS; a++){
            for(int b = 0; b < MAX_MUNICIPIOS; b++){
                matriz_adyacencia[a][b] = 0;
            }
        }

        //guardamos fronteras entre los municipios
        for(int k = 0; k < fronteras; k++){
            if(fgets(linea, MAX_LETRAS, entrada) == NULL){
                break;
            }
            quitar_salto_de_linea(linea);

            separar_por_barra(linea, vector_fronteras[k].municipio01, vector_fronteras[k].municipio02);

            indice01 = buscar_municipio(vector_municipios, num_de_municipios, vector_fronteras[k].municipio01);
            indice02 = buscar_municipio(vector_municipios, num_de_municipios, vector_fronteras[k].municipio02);

            //solo marcamos si los dos nombres existen en la lista
            if(indice01 != -1 && indice02 != -1){
                matriz_adyacencia[indice01][indice02] = 1;
                matriz_adyacencia[indice02][indice01] = 1;
            }
        }

        //nadie pintado todavia (0 = sin color)
        for(int v = 0; v < num_de_municipios; v++){
            vector_colores[v] = 0;
        }

        if(es_posible_colorear(0, num_de_municipios, cantidad_colores, matriz_adyacencia, vector_colores)){
            printf("SI\n");
        }else{
            printf("NO\n");
        }
    }

    fclose(entrada);

    return 0;
}


// descarta el '\n' y el '\r' que deja fgets al final de la linea
void quitar_salto_de_linea(char cadena[]){
    int i = 0;
    while(cadena[i] != '\0' && cadena[i] != '\n' && cadena[i] != '\r'){
        i++;
    }
    cadena[i] = '\0';
}


// parte "Nombre1|Nombre2" en dos cadenas
void separar_por_barra(char linea[], char nombre01[], char nombre02[]){
    int i = 0;
    int j = 0;

    while(linea[i] != '\0' && linea[i] != '|'){
        nombre01[i] = linea[i];
        i++;
    }
    nombre01[i] = '\0';

    if(linea[i] == '|'){
        i++;
    }

    while(linea[i] != '\0'){
        nombre02[j] = linea[i];
        j++;
        i++;
    }
    nombre02[j] = '\0';
}


// devuelve la posicion del municipio en el vector, o -1 si no esta
int buscar_municipio(municipios vector_municipios[], int num_de_municipios, char nombre[]){
    for(int i = 0; i < num_de_municipios; i++){
        if(strcmp(vector_municipios[i].nombre, nombre) == 0){
            return i;
        }
    }
    return -1;
}


/*
 * es_posible_colorear: backtracking.
 *   indice            -> municipio que se esta pintando
 *   num_de_municipios -> total de municipios
 *   cantidad_colores  -> colores disponibles (1 hasta cantidad_colores)
 *   matriz_adyacencia -> 1 si dos municipios comparten frontera
 *   vector_colores    -> color de cada municipio, 0 = sin pintar
 */
bool es_posible_colorear(int indice, int num_de_municipios, int cantidad_colores,
                         int matriz_adyacencia[][MAX_MUNICIPIOS], int vector_colores[]){

    // ya pintamos todos los municipios
    if(indice == num_de_municipios){
        return true;
    }

    // los colores son intercambiables: solo probamos hasta "un color nuevo mas"
    // que el mayor usado hasta ahora. Asi no repetimos la misma solucion
    // con los colores permutados y el arbol deja de explotar.
    int max_color_usado = 0;
    for(int v = 0; v < indice; v++){
        if(vector_colores[v] > max_color_usado){
            max_color_usado = vector_colores[v];
        }
    }

    int limite_colores = max_color_usado + 1;
    if(limite_colores > cantidad_colores){
        limite_colores = cantidad_colores;
    }

    // probamos cada color
    for(int color = 1; color <= limite_colores; color++){

        bool hay_conflicto = false;

        // solo revisamos los vecinos YA pintados
        for(int vecino = 0; vecino < indice; vecino++){
            if(matriz_adyacencia[indice][vecino] == 1 && vector_colores[vecino] == color){
                hay_conflicto = true;
                break;
            }
        }

        if(hay_conflicto){
            continue;
        }

        // marco el color y bajo un nivel
        vector_colores[indice] = color;

        if(es_posible_colorear(indice + 1, num_de_municipios, cantidad_colores, matriz_adyacencia, vector_colores)){
            return true;
        }

        // deshago el color al volver
        vector_colores[indice] = 0;
    }

    return false;
}
