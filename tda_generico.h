#ifndef TDA_GENERICO_H
#define TDA_GENERICO_H

/**
 * @file tda_generico.h
 * @brief TDA Lista, Pila y Cola para cualquier tipo de dato.
 *
 * @details
 * Cada nodo guarda una COPIA del elemento en memoria dinamica. Para lograr
 * genericidad sin plantillas de C++ se usan:
 *   - void *: direccion generica del dato.
 *   - size_t tam: cantidad de bytes del tipo (normalmente sizeof(TIPO)).
 *   - memcpy: copia byte a byte al insertar y al consultar.
 *   - callbacks: funciones opcionales para imprimir y comparar.
 *
 * El tipo se fija al crear la estructura. Todas las operaciones de
 * insercion, consulta y eliminacion trabajan con direcciones de memoria:
 * se pasa &variable al insertar y &variable_destino al consultar.
 *
 * @par Ejemplo con float
 * @code
 * ListaG *l = lista_g_crear(sizeof(float), imprimir_float, comparar_float);
 * float x = 2.5f;
 *
 * lista_g_insertar(l, 1, &x);
 * lista_g_imprimir(l);
 * lista_g_destruir(l);
 * @endcode
 *
 * @warning
 * El tam pasado a lista_g_crear() debe ser exactamente sizeof(TIPO). Si se
 * guarda un tipo distinto, la copia tendra el tamano equivocado y los datos
 * se interpretaran mal. La libreria no puede comprobar el tipo en tiempo de
 * ejecucion.
 */

#include <stddef.h>

/**
 * @brief Funcion que imprime un elemento por pantalla.
 *
 * @details
 * La libreria llama a esta funcion desde lista_g_imprimir(), pila_g_imprimir()
 * y cola_g_imprimir() pasando la direccion del dato guardado. La funcion debe
 * saber a que tipo corresponde y hacer el cast adecuado.
 *
 * @param dato Direccion del elemento que se imprime.
 *
 * @note Puede ser NULL al crear la estructura; en ese caso los impresores
 *       muestran "?" en lugar del valor.
 */
typedef void (*ImpresorTDA)(const void *dato);

/**
 * @brief Funcion que compara dos elementos.
 *
 * @details
 * Se usa en lista_g_buscar(), lista_g_esta() y lista_g_eliminar_valor(). Debe
 * devolver el mismo convenio que strcmp:
 *   - negativo si a < b,
 *   - 0 si a == b,
 *   - positivo si a > b.
 *
 * @param a Direccion del primer elemento.
 * @param b Direccion del segundo elemento.
 *
 * @return Negativo, 0 o positivo segun la comparacion.
 *
 * @note Si el comparador es NULL, la libreria compara con memcmp. Eso solo es
 *       confiable para tipos simples y sin bytes de relleno (padding).
 */
typedef int (*ComparadorTDA)(const void *a, const void *b);

/**
 * @brief Nodo generico: guarda una copia del elemento.
 *
 * @details
 * dato apunta a un bloque de tam bytes reservado con malloc. Cada nodo es
 * dueno de su copia; por eso al eliminar se libera con free(dato) y luego
 * free(nodo).
 */
typedef struct NodoG {
    void *dato;              /**< Copia del elemento (tam bytes). */
    struct NodoG *siguiente; /**< Siguiente nodo; NULL si es el ultimo. */
} NodoG;

/**
 * @brief TDA Lista generica.
 *
 * @details
 * Guarda punteros al primer y al ultimo nodo, la cantidad de elementos, el
 * tamano del tipo y los callbacks de impresion/comparacion. Las posiciones
 * son 1-based. La lista es duena de las copias de los elementos.
 */
typedef struct ListaG {
    NodoG *cabeza;          /**< Primer nodo; NULL si esta vacia. */
    NodoG *cola;            /**< Ultimo nodo; NULL si esta vacia. */
    int longitud;           /**< Cantidad de elementos. */
    size_t tam;             /**< Bytes que ocupa cada elemento. */
    ImpresorTDA imprimir;   /**< Impresor; puede ser NULL. */
    ComparadorTDA comparar; /**< Comparador; puede ser NULL (memcmp). */
} ListaG;

/**
 * @brief TDA Pila generica (LIFO) construida sobre ListaG.
 *
 * @details
 * El tope es la cabeza de la lista interna. Apilar inserta al principio y
 * desapilar elimina el principio.
 */
typedef struct PilaG {
    ListaG lista; /**< Lista interna; su cabeza es el tope. */
} PilaG;

/**
 * @brief TDA Cola generica (FIFO) construida sobre ListaG.
 *
 * @details
 * El frente es la cabeza de la lista interna y el final es su cola. Encolar
 * inserta al final y desencolar elimina el frente.
 */
typedef struct ColaG {
    ListaG lista; /**< Lista interna; su cabeza es el frente. */
} ColaG;

/* ================================ LISTA ================================== */

/**
 * @brief Crea una lista generica vacia.
 *
 * @details
 * Reserva la estructura ListaG y guarda tam, imprimir y comparar. Si tam es
 * 0, se usa 1 para evitar reservas de cero bytes. Si malloc falla, imprime
 * un mensaje de error.
 *
 * @param tam      Bytes que ocupa el tipo guardado (normalmente sizeof(TIPO)).
 * @param imprimir Funcion que imprime un elemento; puede ser NULL.
 * @param comparar Funcion que compara dos elementos; puede ser NULL (se usa
 *                 memcmp).
 *
 * @return Puntero a la lista creada, o NULL si no hay memoria.
 *
 * @post La lista esta vacia y lista para usarse.
 *
 * @note Complejidad O(1).
 * @warning Liberar con lista_g_destruir(). No usar free() directo.
 */
ListaG *lista_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una lista generica ya declarada.
 *
 * @details
 * Se usa con una variable ListaG que no se reserva con malloc. Guarda tam,
 * imprimir y comparar, y deja la lista vacia. Si tam es 0, se usa 1.
 *
 * @param l        Lista a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 *
 * @post La lista queda vacia.
 *
 * @warning No libera nodos existentes. Para reutilizar una lista con nodos,
 *          usar lista_g_vaciar().
 */
void lista_g_iniciar(ListaG *l, size_t tam,
                     ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la lista no tiene elementos.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @retval 1 La lista es NULL o esta vacia.
 * @retval 0 La lista tiene al menos un elemento.
 *
 * @note Complejidad O(1).
 */
int lista_g_es_vacia(const ListaG *l);

/**
 * @brief Devuelve la cantidad de elementos de la lista.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si l es NULL.
 *
 * @note Complejidad O(1).
 */
int lista_g_longitud(const ListaG *l);

/**
 * @brief Inserta una copia del elemento en una posicion.
 *
 * @details
 * La posicion debe cumplir 1 <= pos <= longitud + 1. Para insertar al
 * principio se usa pos = 1; para insertar al final, pos = longitud + 1.
 * La funcion reserva un nodo, reserva tam bytes para la copia y hace memcpy.
 * Si falla alguna reserva, libera lo que haya reservado y no modifica la
 * lista.
 *
 * @param l    Lista destino. Si es NULL, falla.
 * @param pos  Posicion entre 1 y longitud + 1.
 * @param dato Direccion del elemento que se copia (tam bytes).
 *
 * @retval 1 Se inserto la copia.
 * @retval 0 l o dato son NULL, pos es invalida o no hay memoria.
 *
 * @post Si hubo exito, la longitud aumenta en 1.
 *
 * @note Complejidad O(pos); en los extremos es O(1).
 */
int lista_g_insertar(ListaG *l, int pos, const void *dato);

/**
 * @brief Consulta el elemento de una posicion.
 *
 * @details
 * Recorre hasta la posicion pedida y copia tam bytes del dato guardado en
 * salida con memcpy. No modifica la lista.
 *
 * @param l      Lista de la que se lee.
 * @param pos    Posicion entre 1 y longitud.
 * @param salida Direccion donde se copia el elemento; debe tener espacio para
 *               tam bytes.
 *
 * @retval 1 Se copio el elemento.
 * @retval 0 l o salida son NULL, o pos esta fuera de rango.
 *
 * @note Complejidad O(pos).
 */
int lista_g_consultar(const ListaG *l, int pos, void *salida);

/**
 * @brief Cambia el elemento de una posicion.
 *
 * @details
 * Recorre hasta la posicion pedida y copia tam bytes desde dato sobre la
 * copia guardada en el nodo. La estructura de la lista no cambia.
 *
 * @param l    Lista que se modifica.
 * @param pos  Posicion entre 1 y longitud.
 * @param dato Direccion del elemento nuevo (se copian tam bytes).
 *
 * @retval 1 Se modifico el elemento.
 * @retval 0 l o dato son NULL, o pos esta fuera de rango.
 *
 * @note Complejidad O(pos).
 */
int lista_g_modificar(ListaG *l, int pos, const void *dato);

/**
 * @brief Elimina el elemento de una posicion y lo devuelve.
 *
 * @details
 * Desenlaza el nodo, copia tam bytes en salida (si salida no es NULL),
 * libera la copia del dato y libera el nodo. Si se elimina el ultimo nodo,
 * actualiza cola.
 *
 * @param l      Lista de la que se elimina.
 * @param pos    Posicion entre 1 y longitud.
 * @param salida Direccion donde se copia el elemento eliminado; puede ser
 *               NULL si no interesa el valor.
 *
 * @retval 1 Se elimino el elemento.
 * @retval 0 l es NULL o pos esta fuera de rango.
 *
 * @note Complejidad O(pos).
 */
int lista_g_eliminar(ListaG *l, int pos, void *salida);

/**
 * @brief Elimina el primer elemento de la lista.
 *
 * @details
 * Mueve la cabeza al siguiente nodo, copia el dato en salida si no es NULL y
 * libera el nodo. Si la lista queda vacia, cola pasa a NULL.
 *
 * @param l      Lista de la que se elimina.
 * @param salida Direccion donde se copia el elemento eliminado; puede ser
 *               NULL.
 *
 * @retval 1 Se elimino el primer elemento.
 * @retval 0 l es NULL o la lista esta vacia.
 *
 * @note Complejidad O(1).
 */
int lista_g_eliminar_principio(ListaG *l, void *salida);

/**
 * @brief Elimina el ultimo elemento de la lista.
 *
 * @details
 * Recorre hasta el penultimo nodo, corta el enlace y libera el ultimo.
 * Actualiza cola.
 *
 * @param l      Lista de la que se elimina.
 * @param salida Direccion donde se copia el elemento eliminado; puede ser
 *               NULL.
 *
 * @retval 1 Se elimino el ultimo elemento.
 * @retval 0 l es NULL o la lista esta vacia.
 *
 * @note Complejidad O(n).
 */
int lista_g_eliminar_final(ListaG *l, void *salida);

/**
 * @brief Busca un elemento y devuelve su primera posicion.
 *
 * @details
 * Recorre la lista comparando cada dato con el buscado. Usa el callback
 * comparar si no es NULL; si es NULL, usa memcmp con tam bytes.
 *
 * @param l    Lista a revisar.
 * @param dato Direccion del elemento buscado.
 *
 * @return Posicion entre 1 y longitud, o 0 si no aparece.
 *
 * @note Complejidad O(n) si el comparador es O(1).
 */
int lista_g_buscar(const ListaG *l, const void *dato);

/**
 * @brief Indica si un elemento esta en la lista.
 *
 * @details
 * Es equivalente a comprobar si lista_g_buscar() devuelve una posicion
 * distinta de 0.
 *
 * @param l    Lista a revisar.
 * @param dato Direccion del elemento buscado.
 *
 * @retval 1 El elemento aparece.
 * @retval 0 El elemento no aparece o l/dato son NULL.
 *
 * @note Complejidad O(n).
 */
int lista_g_esta(const ListaG *l, const void *dato);

/**
 * @brief Elimina todas las apariciones de un elemento.
 *
 * @details
 * Recorre la lista una vez y elimina los nodos cuyo dato sea igual al
 * buscado. Actualiza cabeza y cola si es necesario. Es seguro con valores
 * repetidos.
 *
 * @param l    Lista que se modifica.
 * @param dato Direccion del elemento que se elimina.
 *
 * @return Cantidad de elementos eliminados; 0 si no habia coincidencias.
 *
 * @note Complejidad O(n).
 */
int lista_g_eliminar_valor(ListaG *l, const void *dato);

/**
 * @brief Invierte el orden de los elementos.
 *
 * @details
 * Recorre la lista y da vuelta cada enlace con tres punteros. Al final, la
 * antigua cabeza es la nueva cola y viceversa.
 *
 * @param l Lista a invertir. Si es NULL o esta vacia, no hace nada.
 *
 * @note Complejidad O(n).
 */
void lista_g_invertir(ListaG *l);

/**
 * @brief Muestra la lista por pantalla.
 *
 * @details
 * Imprime los elementos entre corchetes usando el callback imprimir. Si el
 * callback es NULL, muestra "?" por cada elemento.
 *
 * @param l Lista a mostrar; puede ser NULL.
 *
 * @note Complejidad O(n).
 */
void lista_g_imprimir(const ListaG *l);

/**
 * @brief Libera todos los nodos y deja la lista vacia pero usable.
 *
 * @details
 * Recorre la lista, libera la copia de cada dato y el nodo. Al terminar deja
 * cabeza = NULL, cola = NULL y longitud = 0. La estructura ListaG no se
 * libera.
 *
 * @param l Lista a vaciar. Si es NULL, no hace nada.
 *
 * @post La lista queda vacia.
 *
 * @note Complejidad O(n).
 */
void lista_g_vaciar(ListaG *l);

/**
 * @brief Libera los nodos y la estructura de la lista.
 *
 * @details
 * Llama a lista_g_vaciar() y luego hace free(l).
 *
 * @param l Lista a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 * @warning Solo para listas creadas con lista_g_crear(). No usar con una
 *          lista declarada en el stack ni llamar dos veces.
 */
void lista_g_destruir(ListaG *l);

/* ================================= PILA ================================== */

/**
 * @brief Crea una pila generica vacia.
 *
 * @details
 * Reserva la estructura PilaG y llama a pila_g_iniciar() con tam, imprimir y
 * comparar. Si malloc falla, informa por pantalla.
 *
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 *
 * @return Puntero a la pila, o NULL si no hay memoria.
 *
 * @post La pila esta vacia.
 *
 * @note Complejidad O(1).
 * @warning Liberar con pila_g_destruir().
 */
PilaG *pila_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una pila generica ya declarada.
 *
 * @details
 * Se usa con una variable PilaG que no se reserva con malloc. No reserva
 * memoria; inicializa la lista interna con tam, imprimir y comparar.
 *
 * @param p        Pila a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 *
 * @post La pila queda vacia.
 */
void pila_g_iniciar(PilaG *p, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la pila no tiene elementos.
 *
 * @param p Pila a consultar; puede ser NULL.
 *
 * @retval 1 La pila es NULL o esta vacia.
 * @retval 0 La pila tiene al menos un elemento.
 *
 * @note Complejidad O(1).
 */
int pila_g_es_vacia(const PilaG *p);

/**
 * @brief Devuelve la cantidad de elementos de la pila.
 *
 * @param p Pila a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si p es NULL.
 *
 * @note Complejidad O(1).
 */
int pila_g_longitud(const PilaG *p);

/**
 * @brief Apila una copia del elemento en el tope.
 *
 * @details
 * Inserta en la posicion 1 de la lista interna: reserva nodo, reserva tam
 * bytes y copia con memcpy. Si no hay memoria, informa y no modifica la pila.
 *
 * @param p    Pila destino. Si es NULL, no hace nada.
 * @param dato Direccion del elemento que se copia.
 *
 * @post Si hubo exito, la pila tiene un elemento mas en el tope.
 *
 * @note Complejidad O(1).
 */
void pila_g_apilar(PilaG *p, const void *dato);

/**
 * @brief Desapila el tope y devuelve una copia.
 *
 * @details
 * Elimina el primer nodo de la lista interna, copia tam bytes en salida (si
 * salida no es NULL) y libera el nodo y su copia.
 *
 * @param p      Pila de la que se saca.
 * @param salida Direccion donde se copia el elemento; puede ser NULL.
 *
 * @retval 1 Se desapilo un elemento.
 * @retval 0 p es NULL o la pila esta vacia.
 *
 * @pre La pila deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int pila_g_desapilar(PilaG *p, void *salida);

/**
 * @brief Consulta el tope sin sacarlo.
 *
 * @details
 * Copia tam bytes del dato del tope en salida (si salida no es NULL). La
 * pila no cambia.
 *
 * @param p      Pila a consultar.
 * @param salida Direccion donde se copia el elemento; puede ser NULL.
 *
 * @retval 1 Se copio el tope.
 * @retval 0 p es NULL o la pila esta vacia.
 *
 * @pre La pila deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int pila_g_tope(const PilaG *p, void *salida);

/**
 * @brief Indica si un elemento esta en algun lugar de la pila.
 *
 * @details
 * Recorre la lista interna desde el tope hasta el fondo, usando el comparador
 * o memcmp.
 *
 * @param p    Pila a revisar.
 * @param dato Direccion del elemento buscado.
 *
 * @retval 1 El elemento aparece.
 * @retval 0 El elemento no aparece o p/dato son NULL.
 *
 * @note Complejidad O(n).
 */
int pila_g_contiene(const PilaG *p, const void *dato);

/**
 * @brief Muestra la pila del tope al fondo.
 *
 * @details
 * Imprime TOPE, luego cada elemento entre barras usando el impresor y al
 * final FONDO. Si el impresor es NULL, muestra "?".
 *
 * @param p Pila a mostrar; puede ser NULL.
 *
 * @note Complejidad O(n).
 */
void pila_g_imprimir(const PilaG *p);

/**
 * @brief Vacia la pila y la deja usable.
 *
 * @details
 * Libera todos los nodos de la lista interna y la deja vacia. La estructura
 * PilaG no se libera.
 *
 * @param p Pila a vaciar. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 */
void pila_g_vaciar(PilaG *p);

/**
 * @brief Libera los nodos y la estructura de la pila.
 *
 * @details
 * Vacia la pila y luego hace free(p).
 *
 * @param p Pila a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 * @warning Solo para pilas creadas con pila_g_crear(). No usar con una pila
 *          del stack ni llamar dos veces.
 */
void pila_g_destruir(PilaG *p);

/* ================================= COLA ================================== */

/**
 * @brief Crea una cola generica vacia.
 *
 * @details
 * Reserva la estructura ColaG y llama a cola_g_iniciar() con tam, imprimir y
 * comparar. Si malloc falla, informa por pantalla.
 *
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 *
 * @return Puntero a la cola, o NULL si no hay memoria.
 *
 * @post La cola esta vacia.
 *
 * @note Complejidad O(1).
 * @warning Liberar con cola_g_destruir().
 */
ColaG *cola_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Inicializa una cola generica ya declarada.
 *
 * @details
 * Se usa con una variable ColaG que no se reserva con malloc. No reserva
 * memoria; inicializa la lista interna con tam, imprimir y comparar.
 *
 * @param c        Cola a inicializar. Si es NULL, no hace nada.
 * @param tam      Bytes del tipo guardado.
 * @param imprimir Funcion de impresion o NULL.
 * @param comparar Funcion de comparacion o NULL.
 *
 * @post La cola queda vacia.
 */
void cola_g_iniciar(ColaG *c, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar);

/**
 * @brief Indica si la cola no tiene elementos.
 *
 * @param c Cola a consultar; puede ser NULL.
 *
 * @retval 1 La cola es NULL o esta vacia.
 * @retval 0 La cola tiene al menos un elemento.
 *
 * @note Complejidad O(1).
 */
int cola_g_es_vacia(const ColaG *c);

/**
 * @brief Devuelve la cantidad de elementos de la cola.
 *
 * @param c Cola a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si c es NULL.
 *
 * @note Complejidad O(1).
 */
int cola_g_longitud(const ColaG *c);

/**
 * @brief Encola una copia del elemento al final.
 *
 * @details
 * Inserta en la ultima posicion de la lista interna: reserva nodo, reserva
 * tam bytes y copia con memcpy. Si no hay memoria, informa y no modifica la
 * cola.
 *
 * @param c    Cola destino. Si es NULL, no hace nada.
 * @param dato Direccion del elemento que se copia.
 *
 * @post Si hubo exito, la cola tiene un elemento mas al final.
 *
 * @note Complejidad O(1).
 */
void cola_g_encolar(ColaG *c, const void *dato);

/**
 * @brief Desencola el frente y devuelve una copia.
 *
 * @details
 * Elimina el primer nodo de la lista interna, copia tam bytes en salida (si
 * salida no es NULL) y libera el nodo y su copia.
 *
 * @param c      Cola de la que se saca.
 * @param salida Direccion donde se copia el elemento; puede ser NULL.
 *
 * @retval 1 Se desencolo un elemento.
 * @retval 0 c es NULL o la cola esta vacia.
 *
 * @pre La cola deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int cola_g_desencolar(ColaG *c, void *salida);

/**
 * @brief Consulta el frente sin sacarlo.
 *
 * @details
 * Copia tam bytes del dato del frente en salida (si salida no es NULL). La
 * cola no cambia.
 *
 * @param c      Cola a consultar.
 * @param salida Direccion donde se copia el elemento; puede ser NULL.
 *
 * @retval 1 Se copio el frente.
 * @retval 0 c es NULL o la cola esta vacia.
 *
 * @pre La cola deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int cola_g_frente(const ColaG *c, void *salida);

/**
 * @brief Indica si un elemento esta en algun lugar de la cola.
 *
 * @details
 * Recorre la lista interna desde el frente hasta el final, usando el
 * comparador o memcmp.
 *
 * @param c    Cola a revisar.
 * @param dato Direccion del elemento buscado.
 *
 * @retval 1 El elemento aparece.
 * @retval 0 El elemento no aparece o c/dato son NULL.
 *
 * @note Complejidad O(n).
 */
int cola_g_contiene(const ColaG *c, const void *dato);

/**
 * @brief Muestra la cola del frente al final.
 *
 * @details
 * Imprime FRENTE ->, luego los elementos separados por flechas usando el
 * impresor y al final FIN. Si el impresor es NULL, muestra "?".
 *
 * @param c Cola a mostrar; puede ser NULL.
 *
 * @note Complejidad O(n).
 */
void cola_g_imprimir(const ColaG *c);

/**
 * @brief Vacia la cola y la deja usable.
 *
 * @details
 * Libera todos los nodos de la lista interna y la deja vacia. La estructura
 * ColaG no se libera.
 *
 * @param c Cola a vaciar. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 */
void cola_g_vaciar(ColaG *c);

/**
 * @brief Libera los nodos y la estructura de la cola.
 *
 * @details
 * Vacia la cola y luego hace free(c).
 *
 * @param c Cola a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 * @warning Solo para colas creadas con cola_g_crear(). No usar con una cola
 *          del stack ni llamar dos veces.
 */
void cola_g_destruir(ColaG *c);

/* ===================== impresores y comparadores ========================= */

/**
 * @brief Imprime un elemento de tipo int.
 *
 * @param dato Direccion del int.
 *
 * @warning El dato guardado debe ser realmente un int.
 */
void imprimir_int(const void *dato);

/**
 * @brief Imprime un elemento de tipo float con dos decimales.
 *
 * @param dato Direccion del float.
 *
 * @warning El dato guardado debe ser realmente un float.
 */
void imprimir_float(const void *dato);

/**
 * @brief Imprime un elemento de tipo double con dos decimales.
 *
 * @param dato Direccion del double.
 *
 * @warning El dato guardado debe ser realmente un double.
 */
void imprimir_double(const void *dato);

/**
 * @brief Imprime un elemento de tipo char.
 *
 * @param dato Direccion del char.
 *
 * @warning El dato guardado debe ser realmente un char.
 */
void imprimir_char(const void *dato);

/**
 * @brief Imprime un elemento de tipo bool como true o false.
 *
 * @param dato Direccion del bool.
 *
 * @warning El dato guardado debe ser realmente un bool (stdbool.h).
 */
void imprimir_bool(const void *dato);

/**
 * @brief Imprime una cadena terminada en '\0'.
 *
 * @param dato Direccion del primer caracter de la cadena.
 *
 * @note El elemento guardado debe ser un char * valido.
 * @warning La cadena debe seguir existiendo y terminar en '\0'.
 */
void imprimir_cadena(const void *dato);

/**
 * @brief Compara dos int.
 *
 * @param a Direccion del primer int.
 * @param b Direccion del segundo int.
 *
 * @return (x > y) - (x < y): negativo, 0 o positivo.
 *
 * @warning Los datos deben ser realmente int.
 */
int comparar_int(const void *a, const void *b);

/**
 * @brief Compara dos float.
 *
 * @param a Direccion del primer float.
 * @param b Direccion del segundo float.
 *
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 *
 * @note No usa tolerancia: para igualdad exacta puede fallar por la
 *       representacion binaria. Si necesitas tolerancia, escribe tu propio
 *       comparador.
 */
int comparar_float(const void *a, const void *b);

/**
 * @brief Compara dos double.
 *
 * @param a Direccion del primer double.
 * @param b Direccion del segundo double.
 *
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 *
 * @note Igual que comparar_float(): no usa tolerancia.
 */
int comparar_double(const void *a, const void *b);

/**
 * @brief Compara dos char.
 *
 * @param a Direccion del primer char.
 * @param b Direccion del segundo char.
 *
 * @return Negativo si a < b, 0 si son iguales, positivo si a > b.
 */
int comparar_char(const void *a, const void *b);

/**
 * @brief Compara dos bool.
 *
 * @param a Direccion del primer bool.
 * @param b Direccion del segundo bool.
 *
 * @return Negativo si false < true, 0 si son iguales, positivo si true > false.
 */
int comparar_bool(const void *a, const void *b);

/**
 * @brief Compara dos cadenas con strcmp.
 *
 * @param a Direccion de la primera cadena.
 * @param b Direccion de la segunda cadena.
 *
 * @return El resultado de strcmp.
 *
 * @note Las cadenas deben terminar en '\0'.
 * @warning Los datos deben ser punteros a caracteres validos.
 */
int comparar_cadena(const void *a, const void *b);

/* --------------------------- azucar sintactico --------------------------- */

/**
 * @brief Agrega un valor al final usando una variable temporal.
 *
 * @details
 * Declara una variable local del tipo indicado, le asigna valor y llama a
 * lista_g_insertar() con la posicion longitud + 1.
 *
 * @param lista Lista generica.
 * @param tipo  Tipo del valor (int, float, bool, ...).
 * @param valor Valor que se guarda.
 *
 * @note Equivale a lista_g_insertar(lista, lista_g_longitud(lista) + 1,
 *       &valor), pero sin declarar la variable temporal a mano.
 */
#define TDA_AGREGAR_FINAL(lista, tipo, valor)                                  \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        lista_g_insertar((lista), lista_g_longitud((lista)) + 1,               \
                         &tda_valor_temporal);                                 \
    } while (0)

/**
 * @brief Agrega un valor al principio usando una variable temporal.
 *
 * @details
 * Declara una variable local del tipo indicado, le asigna valor y llama a
 * lista_g_insertar() con la posicion 1.
 *
 * @param lista Lista generica.
 * @param tipo  Tipo del valor.
 * @param valor Valor que se guarda.
 *
 * @note Equivale a lista_g_insertar(lista, 1, &valor).
 */
#define TDA_AGREGAR_PRINCIPIO(lista, tipo, valor)                              \
    do {                                                                       \
        tipo tda_valor_temporal = (valor);                                     \
        lista_g_insertar((lista), 1, &tda_valor_temporal);                     \
    } while (0)

/**
 * @brief Apila un valor usando una variable temporal.
 *
 * @details
 * Declara una variable local del tipo indicado, le asigna valor y llama a
 * pila_g_apilar().
 *
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
 *
 * @details
 * Declara una variable local del tipo indicado, le asigna valor y llama a
 * cola_g_encolar().
 *
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
