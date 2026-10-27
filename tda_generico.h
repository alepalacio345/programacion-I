#ifndef TDA_GENERICO_H
#define TDA_GENERICO_H

/**
 * @file tda_generico.h
 * @brief TDA Lista, Pila y Cola para cualquier tipo de dato.
 *
 * Cada nodo guarda una COPIA del elemento. El tipo se describe con
 * sizeof(TIPO) al crear la estructura y, opcionalmente, con funciones de
 * impresion y comparacion.
 *
 * Ejemplo:
 * @code
 * ListaG *l = lista_g_crear(sizeof(float), imprimir_float, comparar_float);
 * float x = 2.5f;
 * lista_g_insertar(l, 1, &x);
 * lista_g_destruir(l);
 * @endcode
 *
 * Convencion de retorno: cada funcion documenta con @return lo que devuelve;
 * en las operaciones de exito/error, 1 = exito y 0 = error.
 */

#include <stddef.h>

/**
 * @brief Funcion que imprime un elemento por pantalla.
 * @param dato Direccion del elemento que se imprime.
 */
typedef void (*ImpresorTDA)(const void *dato);

/**
 * @brief Funcion que compara dos elementos.
 * @param a Direccion del primer elemento.
 * @param b Direccion del segundo elemento.
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
typedef int (*ComparadorTDA)(const void *a, const void *b);

/**
 * @brief Nodo generico: guarda una copia del elemento.
 */
typedef struct NodoG {
    void *dato;              /**< Copia del elemento (tam bytes). */
    struct NodoG *siguiente; /**< Siguiente nodo, o NULL si es el ultimo. */
} NodoG;

/**
 * @brief TDA Lista generica.
 *
 * Guarda punteros al primer y al ultimo nodo y la cantidad de elementos.
 * El tamano de cada elemento se fija al crear la lista.
 */
typedef struct ListaG {
    NodoG *cabeza;          /**< Primer nodo; NULL si esta vacia. */
    NodoG *cola;            /**< Ultimo nodo; NULL si esta vacia. */
    int longitud;           /**< Cantidad de elementos. */
    size_t tam;             /**< Bytes que ocupa cada elemento. */
    ImpresorTDA imprimir;   /**< Impresor; puede ser NULL. */
    ComparadorTDA comparar; /**< Comparador; puede ser NULL. */
} ListaG;

/**
 * @brief TDA Pila generica (LIFO) construida sobre ListaG.
 */
typedef struct PilaG {
    ListaG lista; /**< Lista interna; su cabeza es el tope. */
} PilaG;

/**
 * @brief TDA Cola generica (FIFO) construida sobre ListaG.
 */
typedef struct ColaG {
    ListaG lista; /**< Lista interna; su cabeza es el frente. */
} ColaG;

/* ================================ LISTA ================================== */

/**
 * @brief Crea una lista generica vacia.
 * @param tam      Bytes que ocupa el tipo guardado (normalmente sizeof(TIPO)).
 * @param imprimir Funcion que imprime un elemento; puede ser NULL.
 * @param comparar Funcion que compara dos elementos; puede ser NULL (se usa
 *                 memcmp).
 * @return Puntero a la lista, o NULL si no hay memoria.
 * @note Debe liberarse con lista_g_destruir().
 */
ListaG *lista_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una lista generica ya declarada.
 * @param l        Lista a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 */
void lista_g_iniciar(ListaG *l, size_t tam,
                     ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la lista no tiene elementos.
 * @param l Lista a consultar (puede ser NULL).
 * @return 1 si esta vacia; 0 si tiene elementos.
 */
int lista_g_es_vacia(const ListaG *l);

/**
 * @brief Devuelve la cantidad de elementos de la lista.
 * @param l Lista a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si l es NULL.
 */
int lista_g_longitud(const ListaG *l);

/**
 * @brief Inserta una copia del elemento en una posicion.
 * @param l    Lista destino.
 * @param pos  Posicion entre 1 y longitud+1.
 * @param dato Direccion del elemento que se copia.
 * @return 1 si se inserto; 0 si la posicion es invalida o no hay memoria.
 * @note Complejidad O(pos); en pos = 1 o pos = longitud+1 es O(1).
 * @note Para insertar al principio: pos = 1. Para insertar al final:
 *       pos = lista_g_longitud(l) + 1.
 */
int lista_g_insertar(ListaG *l, int pos, const void *dato);

/**
 * @brief Consulta el elemento de una posicion.
 * @param l      Lista de la que se lee.
 * @param pos    Posicion entre 1 y longitud.
 * @param salida Direccion donde se copia el elemento (tam bytes).
 * @return 1 si la posicion existe; 0 si no.
 * @note Complejidad O(pos).
 */
int lista_g_consultar(const ListaG *l, int pos, void *salida);

/**
 * @brief Cambia el elemento de una posicion.
 * @param l    Lista que se modifica.
 * @param pos  Posicion entre 1 y longitud.
 * @param dato Direccion del elemento nuevo (se copian tam bytes).
 * @return 1 si se modifico; 0 si la posicion es invalida.
 * @note Complejidad O(pos).
 */
int lista_g_modificar(ListaG *l, int pos, const void *dato);

/**
 * @brief Elimina el elemento de una posicion y lo devuelve.
 * @param l      Lista de la que se elimina.
 * @param pos    Posicion entre 1 y longitud.
 * @param salida Direccion donde se copia el elemento eliminado (puede ser
 *               NULL).
 * @return 1 si se elimino; 0 si la posicion es invalida.
 * @note Complejidad O(pos).
 */
int lista_g_eliminar(ListaG *l, int pos, void *salida);

/**
 * @brief Elimina el primer elemento de la lista.
 * @param l      Lista de la que se elimina.
 * @param salida Direccion donde se copia el elemento eliminado (puede ser
 *               NULL).
 * @return 1 si se elimino; 0 si la lista esta vacia.
 * @note Complejidad O(1).
 */
int lista_g_eliminar_principio(ListaG *l, void *salida);

/**
 * @brief Elimina el ultimo elemento de la lista.
 * @param l      Lista de la que se elimina.
 * @param salida Direccion donde se copia el elemento eliminado (puede ser
 *               NULL).
 * @return 1 si se elimino; 0 si la lista esta vacia.
 * @note Complejidad O(n).
 */
int lista_g_eliminar_final(ListaG *l, void *salida);

/**
 * @brief Busca un elemento y devuelve su primera posicion.
 * @param l    Lista a revisar.
 * @param dato Direccion del elemento buscado.
 * @return Posicion entre 1 y longitud, o 0 si no aparece.
 * @note Usa comparar si no es NULL; si es NULL, compara con memcmp.
 */
int lista_g_buscar(const ListaG *l, const void *dato);

/**
 * @brief Indica si un elemento esta en la lista.
 * @param l    Lista a revisar.
 * @param dato Direccion del elemento buscado.
 * @return 1 si aparece; 0 si no.
 */
int lista_g_esta(const ListaG *l, const void *dato);

/**
 * @brief Elimina todas las apariciones de un elemento.
 * @param l    Lista que se modifica.
 * @param dato Direccion del elemento que se elimina.
 * @return Cantidad de elementos eliminados.
 * @note Complejidad O(n).
 */
int lista_g_eliminar_valor(ListaG *l, const void *dato);

/**
 * @brief Invierte el orden de los elementos.
 * @param l Lista a invertir. Si es NULL o esta vacia, no hace nada.
 * @note Complejidad O(n).
 */
void lista_g_invertir(ListaG *l);

/**
 * @brief Muestra la lista por pantalla.
 * @param l Lista a mostrar.
 * @note Usa el impresor; si es NULL muestra "?".
 */
void lista_g_imprimir(const ListaG *l);

/**
 * @brief Libera todos los nodos y deja la lista vacia pero usable.
 * @param l Lista a vaciar. Si es NULL, no hace nada.
 */
void lista_g_vaciar(ListaG *l);

/**
 * @brief Libera los nodos y la estructura de la lista.
 * @param l Lista a destruir. Si es NULL, no hace nada.
 * @note Solo para listas creadas con lista_g_crear().
 */
void lista_g_destruir(ListaG *l);

/* ================================= PILA ================================== */

/**
 * @brief Crea una pila generica vacia.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 * @return Puntero a la pila, o NULL si no hay memoria.
 * @note Debe liberarse con pila_g_destruir().
 */
PilaG *pila_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una pila generica ya declarada.
 * @param p        Pila a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 */
void pila_g_iniciar(PilaG *p, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la pila no tiene elementos.
 * @param p Pila a consultar (puede ser NULL).
 * @return 1 si esta vacia; 0 si tiene elementos.
 */
int pila_g_es_vacia(const PilaG *p);

/**
 * @brief Devuelve la cantidad de elementos de la pila.
 * @param p Pila a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si p es NULL.
 */
int pila_g_longitud(const PilaG *p);

/**
 * @brief Apila una copia del elemento en el tope.
 * @param p    Pila destino. Si es NULL, no hace nada.
 * @param dato Direccion del elemento que se copia.
 * @note Complejidad O(1).
 */
void pila_g_apilar(PilaG *p, const void *dato);

/**
 * @brief Desapila el tope y devuelve una copia.
 * @param p      Pila de la que se saca.
 * @param salida Direccion donde se copia el elemento (puede ser NULL).
 * @return 1 si habia elemento; 0 si la pila esta vacia.
 * @pre La pila no debe estar vacia.
 */
int pila_g_desapilar(PilaG *p, void *salida);

/**
 * @brief Consulta el tope sin sacarlo.
 * @param p      Pila a consultar.
 * @param salida Direccion donde se copia el elemento (puede ser NULL).
 * @return 1 si habia elemento; 0 si la pila esta vacia.
 * @pre La pila no debe estar vacia.
 */
int pila_g_tope(const PilaG *p, void *salida);

/**
 * @brief Indica si un elemento esta en algun lugar de la pila.
 * @param p    Pila a revisar.
 * @param dato Direccion del elemento buscado.
 * @return 1 si aparece; 0 si no.
 */
int pila_g_contiene(const PilaG *p, const void *dato);

/**
 * @brief Muestra la pila del tope al fondo.
 * @param p Pila a mostrar.
 */
void pila_g_imprimir(const PilaG *p);

/**
 * @brief Vacia la pila y la deja usable.
 * @param p Pila a vaciar. Si es NULL, no hace nada.
 */
void pila_g_vaciar(PilaG *p);

/**
 * @brief Libera los nodos y la estructura de la pila.
 * @param p Pila a destruir. Si es NULL, no hace nada.
 * @note Solo para pilas creadas con pila_g_crear().
 */
void pila_g_destruir(PilaG *p);

/* ================================= COLA ================================== */

/**
 * @brief Crea una cola generica vacia.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 * @return Puntero a la cola, o NULL si no hay memoria.
 * @note Debe liberarse con cola_g_destruir().
 */
ColaG *cola_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una cola generica ya declarada.
 * @param c        Cola a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 */
void cola_g_iniciar(ColaG *c, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la cola no tiene elementos.
 * @param c Cola a consultar (puede ser NULL).
 * @return 1 si esta vacia; 0 si tiene elementos.
 */
int cola_g_es_vacia(const ColaG *c);

/**
 * @brief Devuelve la cantidad de elementos de la cola.
 * @param c Cola a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si c es NULL.
 */
int cola_g_longitud(const ColaG *c);

/**
 * @brief Encola una copia del elemento al final.
 * @param c    Cola destino. Si es NULL, no hace nada.
 * @param dato Direccion del elemento que se copia.
 * @note Complejidad O(1).
 */
void cola_g_encolar(ColaG *c, const void *dato);

/**
 * @brief Desencola el frente y devuelve una copia.
 * @param c      Cola de la que se saca.
 * @param salida Direccion donde se copia el elemento (puede ser NULL).
 * @return 1 si habia elemento; 0 si la cola esta vacia.
 * @pre La cola no debe estar vacia.
 */
int cola_g_desencolar(ColaG *c, void *salida);

/**
 * @brief Consulta el frente sin sacarlo.
 * @param c      Cola a consultar.
 * @param salida Direccion donde se copia el elemento (puede ser NULL).
 * @return 1 si habia elemento; 0 si la cola esta vacia.
 * @pre La cola no debe estar vacia.
 */
int cola_g_frente(const ColaG *c, void *salida);

/**
 * @brief Indica si un elemento esta en algun lugar de la cola.
 * @param c    Cola a revisar.
 * @param dato Direccion del elemento buscado.
 * @return 1 si aparece; 0 si no.
 */
int cola_g_contiene(const ColaG *c, const void *dato);

/**
 * @brief Muestra la cola del frente al final.
 * @param c Cola a mostrar.
 */
void cola_g_imprimir(const ColaG *c);

/**
 * @brief Vacia la cola y la deja usable.
 * @param c Cola a vaciar. Si es NULL, no hace nada.
 */
void cola_g_vaciar(ColaG *c);

/**
 * @brief Libera los nodos y la estructura de la cola.
 * @param c Cola a destruir. Si es NULL, no hace nada.
 * @note Solo para colas creadas con cola_g_crear().
 */
void cola_g_destruir(ColaG *c);

/* ===================== impresores y comparadores ========================= */

/**
 * @brief Imprime un elemento de tipo int.
 * @param dato Direccion del int.
 */
void imprimir_int(const void *dato);

/**
 * @brief Imprime un elemento de tipo float con dos decimales.
 * @param dato Direccion del float.
 */
void imprimir_float(const void *dato);

/**
 * @brief Imprime un elemento de tipo double con dos decimales.
 * @param dato Direccion del double.
 */
void imprimir_double(const void *dato);

/**
 * @brief Imprime un elemento de tipo char.
 * @param dato Direccion del char.
 */
void imprimir_char(const void *dato);

/**
 * @brief Imprime un elemento de tipo bool como true o false.
 * @param dato Direccion del bool.
 */
void imprimir_bool(const void *dato);

/**
 * @brief Imprime una cadena terminada en '\0'.
 * @param dato Direccion del primer caracter de la cadena.
 * @note El elemento guardado debe ser un char * valido.
 */
void imprimir_cadena(const void *dato);

/**
 * @brief Compara dos int.
 * @param a Direccion del primer int.
 * @param b Direccion del segundo int.
 * @return (x > y) - (x < y): negativo, 0 o positivo.
 */
int comparar_int(const void *a, const void *b);

/**
 * @brief Compara dos float.
 * @param a Direccion del primer float.
 * @param b Direccion del segundo float.
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
int comparar_float(const void *a, const void *b);

/**
 * @brief Compara dos double.
 * @param a Direccion del primer double.
 * @param b Direccion del segundo double.
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
int comparar_double(const void *a, const void *b);

/**
 * @brief Compara dos char.
 * @param a Direccion del primer char.
 * @param b Direccion del segundo char.
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
int comparar_char(const void *a, const void *b);

/**
 * @brief Compara dos bool.
 * @param a Direccion del primer bool.
 * @param b Direccion del segundo bool.
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
int comparar_bool(const void *a, const void *b);

/**
 * @brief Compara dos cadenas con strcmp.
 * @param a Direccion de la primera cadena.
 * @param b Direccion de la segunda cadena.
 * @return El resultado de strcmp.
 * @note Las cadenas deben terminar en '\0'.
 */
int comparar_cadena(const void *a, const void *b);

/* --------------------------- azucar sintactico --------------------------- */

/**
 * @brief Agrega un valor al final usando una variable temporal.
 * @param lista Lista generica.
 * @param tipo  Tipo del valor (int, float, bool, ...).
 * @param valor Valor que se guarda.
 * @note Equivale a lista_g_insertar(lista, lista_g_longitud(lista) + 1, &valor).
 */
#define TDA_AGREGAR_FINAL(lista, tipo, valor)                                  \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        lista_g_insertar((lista), lista_g_longitud((lista)) + 1,               \
                         &tda_valor_temporal);                                 \
    } while (0)

/**
 * @brief Agrega un valor al principio usando una variable temporal.
 * @param lista Lista generica.
 * @param tipo  Tipo del valor.
 * @param valor Valor que se guarda.
 * @note Equivale a lista_g_insertar(lista, 1, &valor).
 */
#define TDA_AGREGAR_PRINCIPIO(lista, tipo, valor)                              \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        lista_g_insertar((lista), 1, &tda_valor_temporal);                     \
    } while (0)

/**
 * @brief Apila un valor usando una variable temporal.
 * @param pila  Pila generica.
 * @param tipo  Tipo del valor.
 * @param valor Valor que se apila.
 */
#define TDA_APILAR(pila, tipo, valor)                                          \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        pila_g_apilar((pila), &tda_valor_temporal);                            \
    } while (0)

/**
 * @brief Encola un valor usando una variable temporal.
 * @param cola  Cola generica.
 * @param tipo  Tipo del valor.
 * @param valor Valor que se encola.
 */
#define TDA_ENCOLAR(cola, tipo, valor)                                         \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        cola_g_encolar((cola), &tda_valor_temporal);                           \
    } while (0)

#endif
