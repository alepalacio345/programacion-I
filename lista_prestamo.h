#ifndef LISTA_PRESTAMO_H
#define LISTA_PRESTAMO_H

/**
 * @file lista_prestamo.h
 * @brief Lista y pila para prestamos de biblioteca.
 */

/** @brief Datos de un prestamo. */
typedef struct {
    char cedula[20];
    char codigo[20];
    char hora[10];
} Prestamo;

/** @brief Nodo usado por la lista y por la pila. */
typedef struct NodoPrestamo {
    Prestamo dato;
    struct NodoPrestamo *siguiente;
} NodoPrestamo;

/** @brief Lista de prestamos activos. */
typedef struct {
    NodoPrestamo *cabeza;
    NodoPrestamo *cola;
    int longitud;
} ListaPrestamo;

/** @brief Pila de prestamos deshechos. */
typedef struct {
    NodoPrestamo *tope;
    int longitud;
} PilaPrestamo;

/**
 * @brief Crea una lista vacia.
 * @return Lista creada o NULL si no hay memoria.
 */
ListaPrestamo *crear_lista_prestamo(void);

/**
 * @brief Inicializa una lista ya declarada.
 * @param l Lista a inicializar.
 */
void iniciar_lista_prestamo(ListaPrestamo *l);

/**
 * @brief Indica si la lista esta vacia.
 * @param l Lista a revisar.
 * @return 1 si esta vacia, 0 si no.
 */
int lista_prestamo_es_vacia(const ListaPrestamo *l);

/**
 * @brief Devuelve la cantidad de prestamos.
 * @param l Lista a revisar.
 * @return Cantidad de elementos.
 */
int lista_prestamo_longitud(const ListaPrestamo *l);

/**
 * @brief Agrega un prestamo al final.
 * @param l Lista destino.
 * @param p Prestamo a copiar.
 * @return 1 si se agrego, 0 si no hay memoria.
 */
int lista_prestamo_insertar_final(ListaPrestamo *l, const Prestamo *p);

/**
 * @brief Elimina el ultimo prestamo.
 * @param l Lista de la que se elimina.
 * @param p Direccion donde se copia el prestamo eliminado.
 * @return 1 si se elimino, 0 si la lista esta vacia.
 */
int lista_prestamo_eliminar_final(ListaPrestamo *l, Prestamo *p);

/**
 * @brief Imprime todos los prestamos.
 * @param l Lista a mostrar.
 */
void lista_prestamo_imprimir(const ListaPrestamo *l);

/**
 * @brief Libera los nodos y deja la lista vacia.
 * @param l Lista a vaciar.
 */
void vaciar_lista_prestamo(ListaPrestamo *l);

/**
 * @brief Libera los nodos y la lista.
 * @param l Lista a destruir.
 */
void destruir_lista_prestamo(ListaPrestamo *l);

/**
 * @brief Crea una pila vacia.
 * @return Pila creada o NULL si no hay memoria.
 */
PilaPrestamo *crear_pila_prestamo(void);

/**
 * @brief Inicializa una pila ya declarada.
 * @param p Pila a inicializar.
 */
void iniciar_pila_prestamo(PilaPrestamo *p);

/**
 * @brief Indica si la pila esta vacia.
 * @param p Pila a revisar.
 * @return 1 si esta vacia, 0 si no.
 */
int pila_prestamo_es_vacia(const PilaPrestamo *p);

/**
 * @brief Devuelve la cantidad de elementos de la pila.
 * @param p Pila a revisar.
 * @return Cantidad de elementos.
 */
int pila_prestamo_longitud(const PilaPrestamo *p);

/**
 * @brief Apila un prestamo.
 * @param p Pila destino.
 * @param dato Prestamo a copiar.
 * @return 1 si se apilo, 0 si no hay memoria.
 */
int pila_prestamo_apilar(PilaPrestamo *p, const Prestamo *dato);

/**
 * @brief Desapila el tope.
 * @param p Pila de la que se saca.
 * @param dato Direccion donde se copia el prestamo.
 * @return 1 si se desapilo, 0 si la pila esta vacia.
 */
int pila_prestamo_desapilar(PilaPrestamo *p, Prestamo *dato);

/**
 * @brief Imprime la pila del tope al fondo.
 * @param p Pila a mostrar.
 */
void pila_prestamo_imprimir(const PilaPrestamo *p);

/**
 * @brief Libera los nodos y deja la pila vacia.
 * @param p Pila a vaciar.
 */
void vaciar_pila_prestamo(PilaPrestamo *p);

/**
 * @brief Libera los nodos y la pila.
 * @param p Pila a destruir.
 */
void destruir_pila_prestamo(PilaPrestamo *p);

#endif
