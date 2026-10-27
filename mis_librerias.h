#ifndef mis_librerias
#define mis_librerias

//aqui solo agregamos el prototipado 

//estructura de nodo
typedef struct Nodo{
    int dato;
    struct Nodo *siguiente;
}Nodo;

//estructura de la lista
//guardamos las direcciones de la cabeza y cola
typedef struct Lista{
    Nodo *cabeza;
    Nodo *cola;
}Lista;

void agregar_al_final(Lista *mi_lista,int valor);
void imprimir_lista(Lista *mi_lista);
Lista* crear_lista();
void agregar_al_principio(Lista *mi_lista, int valor);

#endif