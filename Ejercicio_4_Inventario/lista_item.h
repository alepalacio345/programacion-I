#ifndef LISTA_ITEM_H
#define LISTA_ITEM_H

//tamano maximo del nombre
#define ITEM_NOMBRE_MAX 30

//durabilidad permitida
#define ITEM_DURABILIDAD_MIN 0
#define ITEM_DURABILIDAD_MAX 100

//objeto del inventario
typedef struct Item {
    char nombre[ITEM_NOMBRE_MAX];
    char categoria; //A arma, P pocion, M material
    int durabilidad;
    struct Item *siguiente;
} Item;

//lista de objetos
typedef struct ListaItem {
    Item *cabeza;
    Item *cola;
    int longitud;
} ListaItem;

//crea la lista vacia
ListaItem *crear_lista_item(void);

//inicializa una lista que ya existe
void iniciar_lista_item(ListaItem *l);

//dice si la lista esta vacia
int lista_item_es_vacia(const ListaItem *l);

//devuelve la cantidad de objetos
int lista_item_longitud(const ListaItem *l);

//agrega un objeto al final
int lista_item_insertar_final(ListaItem *l, const char *nombre,
                              char categoria, int durabilidad);

//libera los nodos y deja la lista vacia
void vaciar_lista_item(ListaItem *l);

//libera la lista completa
void destruir_lista_item(ListaItem *l);

#endif
