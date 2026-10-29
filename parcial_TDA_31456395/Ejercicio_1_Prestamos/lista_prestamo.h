#ifndef LISTA_PRESTAMO_H
#define LISTA_PRESTAMO_H

//datos de un prestamo
typedef struct {
    char cedula[20];
    char codigo[20];
    char hora[10];
} Prestamo;

//nodo para la lista y la pila
typedef struct NodoPrestamo {
    Prestamo dato;
    struct NodoPrestamo *siguiente;
} NodoPrestamo;

//lista de prestamos activos
typedef struct {
    NodoPrestamo *cabeza;
    NodoPrestamo *cola;
    int longitud;
} ListaPrestamo;

//pila de prestamos deshechos
typedef struct {
    NodoPrestamo *tope;
    int longitud;
} PilaPrestamo;

//crea la lista vacia
ListaPrestamo *crear_lista_prestamo(void);

//inicializa una lista que ya existe
void iniciar_lista_prestamo(ListaPrestamo *l);

//dice si la lista esta vacia
int lista_prestamo_es_vacia(const ListaPrestamo *l);

//devuelve la cantidad de prestamos
int lista_prestamo_longitud(const ListaPrestamo *l);

//agrega un prestamo al final
int lista_prestamo_insertar_final(ListaPrestamo *l, const Prestamo *p);

//quita el ultimo prestamo y lo devuelve
int lista_prestamo_eliminar_final(ListaPrestamo *l, Prestamo *p);

//muestra todos los prestamos
void lista_prestamo_imprimir(const ListaPrestamo *l);

//libera los nodos y deja la lista vacia
void vaciar_lista_prestamo(ListaPrestamo *l);

//libera la lista completa
void destruir_lista_prestamo(ListaPrestamo *l);

//crea la pila vacia
PilaPrestamo *crear_pila_prestamo(void);

//inicializa una pila que ya existe
void iniciar_pila_prestamo(PilaPrestamo *p);

//dice si la pila esta vacia
int pila_prestamo_es_vacia(const PilaPrestamo *p);

//devuelve la cantidad de elementos de la pila
int pila_prestamo_longitud(const PilaPrestamo *p);

//apila un prestamo
int pila_prestamo_apilar(PilaPrestamo *p, const Prestamo *dato);

//saca el prestamo del tope
int pila_prestamo_desapilar(PilaPrestamo *p, Prestamo *dato);

//libera los nodos y deja la pila vacia
void vaciar_pila_prestamo(PilaPrestamo *p);

//libera la pila completa
void destruir_pila_prestamo(PilaPrestamo *p);

#endif
