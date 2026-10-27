#ifndef MIS_LIBRERIAS_H
#define MIS_LIBRERIAS_H

/**
 * @file mis_librerias.h
 * @brief TDA Lista, Pila y Cola para elementos de tipo int.
 *
 * La Lista usa nodos enlazados y posiciones 1-based (la primera es 1).
 * La Pila y la Cola estan construidas sobre una Lista:
 *   - Pila: el tope es la cabeza de la lista (LIFO).
 *   - Cola: el frente es la cabeza y el final es la cola (FIFO).
 *
 * Convencion de retorno:
 *   - Cada funcion documenta con @return lo que devuelve.
 *   - En las operaciones de exito/error, 1 = exito y 0 = error.
 *   - Los datos que "salen" de una operacion se copian en el puntero de
 *     salida que recibe la funcion (puede ser NULL si no interesa el dato).
 */

/* =============================== TDA LISTA =============================== */

/**
 * @brief Nodo de la lista enlazada.
 */
typedef struct Nodo {
    int dato;               /**< Valor entero almacenado. */
    struct Nodo *siguiente; /**< Siguiente nodo, o NULL si es el ultimo. */
} Nodo;

/**
 * @brief TDA Lista: secuencia ordenada de elementos.
 *
 * Guarda punteros al primer y al ultimo nodo para insertar en los extremos
 * en O(1), y la longitud para consultarla en O(1).
 */
typedef struct Lista {
    Nodo *cabeza;  /**< Primer nodo; NULL si la lista esta vacia. */
    Nodo *cola;    /**< Ultimo nodo; NULL si la lista esta vacia. */
    int longitud;  /**< Cantidad de elementos. */
} Lista;

/**
 * @brief Crea una lista vacia en memoria dinamica.
 * @return Puntero a la lista creada, o NULL si no hay memoria.
 * @note Debe liberarse con destruir_lista().
 */
Lista *crear_lista(void);

/**
 * @brief Inicializa una lista ya declarada (por ejemplo, en el stack).
 * @param l Lista a inicializar. Si es NULL, no hace nada.
 * @note No reserva memoria; se usa con una variable Lista ya existente.
 */
void iniciar_lista(Lista *l);

/**
 * @brief Indica si la lista no tiene elementos.
 * @param l Lista a consultar (puede ser NULL).
 * @return 1 si esta vacia o l es NULL; 0 si tiene al menos un elemento.
 */
int lista_es_vacia(const Lista *l);

/**
 * @brief Devuelve la cantidad de elementos de la lista.
 * @param l Lista a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si l es NULL.
 */
int lista_longitud(const Lista *l);

/**
 * @brief Inserta un valor en una posicion determinada.
 * @param l     Lista destino.
 * @param pos   Posicion de insercion, entre 1 y longitud+1.
 * @param valor Valor que se guarda.
 * @return 1 si se inserto; 0 si la posicion es invalida o no hay memoria.
 * @note Complejidad O(pos); en pos = 1 o pos = longitud+1 es O(1).
 * @note Para insertar al principio: pos = 1. Para insertar al final:
 *       pos = lista_longitud(l) + 1.
 */
int lista_insertar(Lista *l, int pos, int valor);

/**
 * @brief Consulta el elemento que ocupa una posicion.
 * @param l     Lista de la que se lee.
 * @param pos   Posicion entre 1 y longitud.
 * @param valor Direccion donde se copia el dato encontrado.
 * @return 1 si la posicion existe; 0 si no.
 * @note Complejidad O(pos).
 */
int lista_consultar(const Lista *l, int pos, int *valor);

/**
 * @brief Cambia el valor de un elemento en una posicion.
 * @param l     Lista que se modifica.
 * @param pos   Posicion entre 1 y longitud.
 * @param nuevo Valor nuevo.
 * @return 1 si se modifico; 0 si la posicion es invalida.
 * @note Complejidad O(pos).
 */
int lista_modificar(Lista *l, int pos, int nuevo);

/**
 * @brief Elimina el elemento de una posicion y devuelve su valor.
 * @param l     Lista de la que se elimina.
 * @param pos   Posicion entre 1 y longitud.
 * @param valor Direccion donde se copia el dato eliminado (puede ser NULL).
 * @return 1 si se elimino; 0 si la posicion es invalida.
 * @note Complejidad O(pos).
 */
int lista_eliminar(Lista *l, int pos, int *valor);

/**
 * @brief Elimina el primer elemento de la lista.
 * @param l     Lista de la que se elimina.
 * @param valor Direccion donde se copia el dato eliminado (puede ser NULL).
 * @return 1 si se elimino; 0 si la lista esta vacia.
 * @note Complejidad O(1).
 */
int lista_eliminar_principio(Lista *l, int *valor);

/**
 * @brief Elimina el ultimo elemento de la lista.
 * @param l     Lista de la que se elimina.
 * @param valor Direccion donde se copia el dato eliminado (puede ser NULL).
 * @return 1 si se elimino; 0 si la lista esta vacia.
 * @note Complejidad O(n): hay que llegar al penultimo nodo.
 */
int lista_eliminar_final(Lista *l, int *valor);

/**
 * @brief Indica si un valor aparece al menos una vez en la lista.
 * @param l     Lista a revisar.
 * @param valor Valor buscado.
 * @return 1 si aparece; 0 si no.
 * @note Complejidad O(n).
 */
int lista_esta(const Lista *l, int valor);

/**
 * @brief Busca un valor y devuelve su primera posicion.
 * @param l     Lista a revisar.
 * @param valor Valor buscado.
 * @return Posicion entre 1 y longitud, o 0 si no aparece.
 * @note Complejidad O(n).
 */
int lista_buscar(const Lista *l, int valor);

/**
 * @brief Elimina todas las apariciones de un valor.
 * @param l     Lista que se modifica.
 * @param valor Valor que se elimina.
 * @return Cantidad de nodos eliminados.
 * @note Complejidad O(n).
 */
int lista_eliminar_valor(Lista *l, int valor);

/**
 * @brief Invierte el orden de los elementos de la lista.
 * @param l Lista a invertir. Si es NULL o esta vacia, no hace nada.
 * @note Complejidad O(n).
 */
void lista_invertir(Lista *l);

/**
 * @brief Copia los elementos de una lista en otra.
 * @param origen  Lista fuente.
 * @param destino Lista destino; se vacia antes de copiar.
 * @note Si origen y destino son la misma lista, no hace nada.
 */
void lista_copiar(const Lista *origen, Lista *destino);

/**
 * @brief Agrega al final de destino una copia de los elementos de origen.
 * @param destino Lista que recibe los elementos.
 * @param origen  Lista que se copia (no se modifica).
 * @note No comparte nodos: cada lista conserva su propia memoria.
 */
void lista_concatenar(Lista *destino, const Lista *origen);

/**
 * @brief Mezcla dos listas ordenadas en una tercera lista ordenada.
 * @param a         Primera lista ordenada.
 * @param b         Segunda lista ordenada.
 * @param resultado Lista donde se guarda la mezcla; se vacia antes.
 * @pre a y b estan ordenadas de menor a mayor.
 * @note resultado debe ser distinta de a y de b.
 */
void lista_combinar_ordenadas(const Lista *a, const Lista *b, Lista *resultado);

/**
 * @brief Guarda en resultado los valores que estan en ambas listas.
 * @param a         Primera lista.
 * @param b         Segunda lista.
 * @param resultado Lista con los valores comunes, sin repetidos.
 * @note resultado debe ser distinta de a y de b.
 */
void lista_interseccion(const Lista *a, const Lista *b, Lista *resultado);

/**
 * @brief Indica si la lista esta en orden no decreciente.
 * @param l Lista a revisar.
 * @return 1 si esta ordenada o esta vacia; 0 si hay una bajada.
 */
int lista_esta_ordenada(const Lista *l);

/**
 * @brief Guarda la lista en un archivo de texto, un entero por linea.
 * @param l    Lista que se guarda.
 * @param ruta Ruta del archivo.
 * @return 1 si se pudo escribir; 0 si hubo error.
 */
int lista_guardar(const Lista *l, const char *ruta);

/**
 * @brief Carga una lista desde un archivo de texto.
 * @param l    Lista destino; se vacia antes de cargar.
 * @param ruta Ruta del archivo.
 * @return 1 si se pudo abrir y leer; 0 si hubo error.
 */
int lista_cargar(Lista *l, const char *ruta);

/**
 * @brief Muestra la lista por pantalla.
 * @param l Lista a mostrar.
 * @note Formato: [1, 2, 3]  (longitud = 3).
 */
void imprimir_lista(const Lista *l);

/**
 * @brief Libera todos los nodos y deja la lista vacia pero usable.
 * @param l Lista a vaciar. Si es NULL, no hace nada.
 */
void vaciar_lista(Lista *l);

/**
 * @brief Libera los nodos y la estructura de la lista.
 * @param l Lista a destruir. Si es NULL, no hace nada.
 * @note Solo para listas creadas con crear_lista().
 */
void destruir_lista(Lista *l);

/* =============================== TDA PILA ================================ */

/**
 * @brief TDA Pila (LIFO) construida sobre una Lista.
 *
 * El tope de la pila es la cabeza de la lista interna.
 */
typedef struct Pila {
    Lista lista; /**< Lista interna; su cabeza es el tope. */
} Pila;

/**
 * @brief Crea una pila vacia en memoria dinamica.
 * @return Puntero a la pila, o NULL si no hay memoria.
 * @note Debe liberarse con destruir_pila().
 */
Pila *crear_pila(void);

/**
 * @brief Inicializa una pila ya declarada.
 * @param p Pila a inicializar. Si es NULL, no hace nada.
 */
void iniciar_pila(Pila *p);

/**
 * @brief Indica si la pila no tiene elementos.
 * @param p Pila a consultar (puede ser NULL).
 * @return 1 si esta vacia; 0 si tiene elementos.
 */
int pila_es_vacia(const Pila *p);

/**
 * @brief Devuelve la cantidad de elementos de la pila.
 * @param p Pila a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si p es NULL.
 */
int pila_longitud(const Pila *p);

/**
 * @brief Apila un valor en el tope.
 * @param p     Pila destino. Si es NULL, no hace nada.
 * @param valor Valor que se apila.
 * @note Complejidad O(1).
 */
void apilar(Pila *p, int valor);

/**
 * @brief Desapila el tope y devuelve su valor.
 * @param p     Pila de la que se saca.
 * @param valor Direccion donde se copia el dato (puede ser NULL).
 * @return 1 si habia elemento; 0 si la pila esta vacia.
 * @pre La pila no debe estar vacia.
 */
int desapilar(Pila *p, int *valor);

/**
 * @brief Consulta el valor del tope sin sacarlo.
 * @param p     Pila a consultar.
 * @param valor Direccion donde se copia el dato (puede ser NULL).
 * @return 1 si habia elemento; 0 si la pila esta vacia.
 * @pre La pila no debe estar vacia.
 */
int pila_tope(const Pila *p, int *valor);

/**
 * @brief Indica si un valor esta en algun lugar de la pila.
 * @param p     Pila a revisar.
 * @param valor Valor buscado.
 * @return 1 si aparece; 0 si no.
 * @note Complejidad O(n).
 */
int pila_contiene(const Pila *p, int valor);

/**
 * @brief Muestra la pila del tope al fondo.
 * @param p Pila a mostrar.
 */
void imprimir_pila(const Pila *p);

/**
 * @brief Vacia la pila y la deja usable.
 * @param p Pila a vaciar. Si es NULL, no hace nada.
 */
void vaciar_pila(Pila *p);

/**
 * @brief Libera todos los nodos y la estructura de la pila.
 * @param p Pila a destruir. Si es NULL, no hace nada.
 * @note Solo para pilas creadas con crear_pila().
 */
void destruir_pila(Pila *p);

/* =============================== TDA COLA ================================ */

/**
 * @brief TDA Cola (FIFO) construida sobre una Lista.
 *
 * El frente es la cabeza de la lista interna y el final es su cola.
 */
typedef struct Cola {
    Lista lista; /**< Lista interna; su cabeza es el frente. */
} Cola;

/**
 * @brief Crea una cola vacia en memoria dinamica.
 * @return Puntero a la cola, o NULL si no hay memoria.
 * @note Debe liberarse con destruir_cola().
 */
Cola *crear_cola(void);

/**
 * @brief Inicializa una cola ya declarada.
 * @param c Cola a inicializar. Si es NULL, no hace nada.
 */
void iniciar_cola(Cola *c);

/**
 * @brief Indica si la cola no tiene elementos.
 * @param c Cola a consultar (puede ser NULL).
 * @return 1 si esta vacia; 0 si tiene elementos.
 */
int cola_es_vacia(const Cola *c);

/**
 * @brief Devuelve la cantidad de elementos de la cola.
 * @param c Cola a consultar (puede ser NULL).
 * @return Cantidad de elementos; 0 si c es NULL.
 */
int cola_longitud(const Cola *c);

/**
 * @brief Encola un valor al final.
 * @param c     Cola destino. Si es NULL, no hace nada.
 * @param valor Valor que se encola.
 * @note Complejidad O(1).
 */
void encolar(Cola *c, int valor);

/**
 * @brief Desencola el frente y devuelve su valor.
 * @param c     Cola de la que se saca.
 * @param valor Direccion donde se copia el dato (puede ser NULL).
 * @return 1 si habia elemento; 0 si la cola esta vacia.
 * @pre La cola no debe estar vacia.
 */
int desencolar(Cola *c, int *valor);

/**
 * @brief Consulta el valor del frente sin sacarlo.
 * @param c     Cola a consultar.
 * @param valor Direccion donde se copia el dato (puede ser NULL).
 * @return 1 si habia elemento; 0 si la cola esta vacia.
 * @pre La cola no debe estar vacia.
 */
int frente(const Cola *c, int *valor);

/**
 * @brief Indica si un valor esta en algun lugar de la cola.
 * @param c     Cola a revisar.
 * @param valor Valor buscado.
 * @return 1 si aparece; 0 si no.
 * @note Complejidad O(n).
 */
int cola_contiene(const Cola *c, int valor);

/**
 * @brief Muestra la cola del frente al final.
 * @param c Cola a mostrar.
 */
void imprimir_cola(const Cola *c);

/**
 * @brief Vacia la cola y la deja usable.
 * @param c Cola a vaciar. Si es NULL, no hace nada.
 */
void vaciar_cola(Cola *c);

/**
 * @brief Libera todos los nodos y la estructura de la cola.
 * @param c Cola a destruir. Si es NULL, no hace nada.
 * @note Solo para colas creadas con crear_cola().
 */
void destruir_cola(Cola *c);

/* ===================== utilidades para ordenamientos ===================== */

/**
 * @brief Intercambia los valores apuntados por a y b.
 * @param a Puntero al primer entero.
 * @param b Puntero al segundo entero.
 */
void intercambiar(int *a, int *b);

#endif
