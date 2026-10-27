#ifndef MIS_LIBRERIAS_H
#define MIS_LIBRERIAS_H

/**
 * @file mis_librerias.h
 * @brief TDA Lista, Pila y Cola para elementos de tipo int.
 *
 * @details
 * Implementacion con nodos enlazados y memoria dinamica. La Lista usa
 * posiciones 1-based: la primera posicion es 1 y la ultima es longitud.
 * La Pila y la Cola se construyen sobre una Lista:
 *   - Pila: el tope es la cabeza de la lista interna (LIFO).
 *   - Cola: el frente es la cabeza y el final es la cola interna (FIFO).
 *
 * Convenciones de retorno:
 *   - En las operaciones de exito/error, 1 = exito y 0 = fallo.
 *   - lista_buscar() devuelve una posicion (1..longitud) o 0 si no esta.
 *   - lista_eliminar_valor() devuelve la cantidad de nodos eliminados.
 *   - lista_longitud(), pila_longitud() y cola_longitud() devuelven una
 *     cantidad.
 *   - Los datos de salida se copian en un puntero. Si el puntero es NULL,
 *     la operacion no copia el dato, pero puede realizar el resto.
 *
 * @par Ejemplo de uso
 * @code
 * Lista *l = crear_lista();
 *
 * lista_insertar(l, 1, 10);                        // al principio
 * lista_insertar(l, lista_longitud(l) + 1, 20);    // al final
 * imprimir_lista(l);
 *
 * destruir_lista(l);
 * @endcode
 *
 * @warning
 * Una lista creada con crear_lista() se libera con destruir_lista().
 * Una lista inicializada con iniciar_lista() se libera con vaciar_lista().
 * No mezclar ambas formas: free() directo deja nodos sin liberar.
 */

/* =============================== TDA LISTA =============================== */

/**
 * @brief Nodo de la lista enlazada.
 *
 * @details
 * Cada nodo guarda un entero y la direccion del siguiente nodo. El ultimo
 * nodo de la lista tiene siguiente == NULL. Los nodos se reservan con malloc
 * y se liberan con free() desde las operaciones de la lista.
 */
typedef struct Nodo {
    int dato;               /**< Valor entero almacenado en el nodo. */
    struct Nodo *siguiente; /**< Siguiente nodo; NULL si este es el ultimo. */
} Nodo;

/**
 * @brief TDA Lista: secuencia de enteros ordenada por posicion.
 *
 * @details
 * La lista mantiene tres datos:
 *   - cabeza: direccion del primer nodo.
 *   - cola: direccion del ultimo nodo.
 *   - longitud: cantidad de nodos.
 *
 * Guardar la cola permite insertar al final en O(1) sin recorrer la lista.
 * Guardar la longitud permite consultarla en O(1). Las posiciones son
 * 1-based: 1 es el primer elemento y longitud es el ultimo.
 */
typedef struct Lista {
    Nodo *cabeza;  /**< Primer nodo; NULL si la lista esta vacia. */
    Nodo *cola;    /**< Ultimo nodo; NULL si la lista esta vacia. */
    int longitud;  /**< Cantidad de elementos; 0 si esta vacia. */
} Lista;

/**
 * @brief Crea una lista vacia en memoria dinamica.
 *
 * @details
 * Reserva con malloc la estructura Lista y la inicializa con cabeza = NULL,
 * cola = NULL y longitud = 0. Si malloc falla, imprime un mensaje de error.
 *
 * @return Puntero a la lista creada, o NULL si no hay memoria.
 *
 * @post La lista devuelta esta vacia y lista para usarse.
 *
 * @note Complejidad O(1).
 *
 * @warning La lista debe liberarse con destruir_lista(). No usar free()
 *          directamente sobre el puntero: quedarian nodos sin liberar.
 */
Lista *crear_lista(void);

/**
 * @brief Inicializa una lista ya declarada.
 *
 * @details
 * Se usa cuando la variable Lista no se reserva con malloc, por ejemplo:
 * @code
 * Lista l;
 * iniciar_lista(&l);
 * @endcode
 * Deja cabeza = NULL, cola = NULL y longitud = 0. No reserva memoria.
 *
 * @param l Lista a inicializar. Si es NULL, no hace nada.
 *
 * @pre La lista no debe tener nodos reservados; si los tiene, se pierden.
 *
 * @post La lista queda vacia.
 *
 * @warning No libera nodos existentes. Para reutilizar una lista que ya tiene
 *          nodos, usar vaciar_lista() en lugar de iniciar_lista().
 */
void iniciar_lista(Lista *l);

/**
 * @brief Indica si la lista no tiene elementos.
 *
 * @details
 * Una lista NULL tambien se considera vacia, para simplificar las
 * validaciones del cliente.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @retval 1 La lista es NULL o su cabeza es NULL.
 * @retval 0 La lista tiene al menos un nodo.
 *
 * @note Complejidad O(1).
 */
int lista_es_vacia(const Lista *l);

/**
 * @brief Devuelve la cantidad de elementos de la lista.
 *
 * @details
 * La longitud se mantiene actualizada en cada insercion y eliminacion, por
 * lo que no hace falta recorrer la lista para contarla.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si l es NULL.
 *
 * @note Complejidad O(1).
 */
int lista_longitud(const Lista *l);

/**
 * @brief Inserta un valor en una posicion determinada.
 *
 * @details
 * La posicion debe cumplir 1 <= pos <= longitud + 1:
 *   - pos == 1 inserta al principio.
 *   - pos == longitud + 1 inserta al final.
 *   - cualquier otra posicion inserta entre dos nodos existentes.
 *
 * La funcion reserva un nodo nuevo y enlaza el valor. Si no hay memoria,
 * informa por pantalla y deja la lista sin cambios.
 *
 * @param l     Lista destino. Si es NULL, la operacion falla.
 * @param pos   Posicion de insercion, entre 1 y longitud + 1.
 * @param valor Valor entero que se guarda.
 *
 * @retval 1 Se inserto el valor.
 * @retval 0 l es NULL, pos es invalida o no hay memoria.
 *
 * @post Si hubo exito, la longitud aumenta en 1.
 *
 * @note Complejidad O(pos). En los extremos es O(1) porque la lista guarda
 *       el puntero a la cola.
 *
 * @warning Si malloc falla, se imprime un error y la lista queda intacta.
 */
int lista_insertar(Lista *l, int pos, int valor);

/**
 * @brief Consulta el elemento que ocupa una posicion.
 *
 * @details
 * Recorre la lista desde la cabeza hasta la posicion pedida y copia el valor
 * en la direccion indicada. No modifica la lista.
 *
 * @param l     Lista de la que se lee.
 * @param pos   Posicion entre 1 y longitud.
 * @param valor Direccion donde se copia el dato; si es NULL, la operacion
 *              falla.
 *
 * @retval 1 Se copio el valor.
 * @retval 0 l es NULL, valor es NULL o pos esta fuera de rango.
 *
 * @note Complejidad O(pos).
 */
int lista_consultar(const Lista *l, int pos, int *valor);

/**
 * @brief Cambia el valor de un elemento en una posicion.
 *
 * @details
 * Recorre hasta la posicion pedida y reemplaza el dato del nodo. La estructura
 * de la lista (enlaces y longitud) no cambia.
 *
 * @param l     Lista que se modifica.
 * @param pos   Posicion entre 1 y longitud.
 * @param nuevo Valor nuevo.
 *
 * @retval 1 Se modifico el valor.
 * @retval 0 l es NULL o pos esta fuera de rango.
 *
 * @note Complejidad O(pos).
 */
int lista_modificar(Lista *l, int pos, int nuevo);

/**
 * @brief Elimina el elemento de una posicion y devuelve su valor.
 *
 * @details
 * Si pos == 1, elimina la cabeza en O(1). En otro caso, recorre hasta el nodo
 * anterior a la posicion, lo desenlaza y libera el nodo. Si se elimina el
 * ultimo nodo, actualiza el puntero cola.
 *
 * @param l     Lista de la que se elimina.
 * @param pos   Posicion entre 1 y longitud.
 * @param valor Direccion donde se copia el dato eliminado; puede ser NULL si
 *              no interesa el valor.
 *
 * @retval 1 Se elimino el elemento.
 * @retval 0 l es NULL o pos esta fuera de rango.
 *
 * @post Si hubo exito, la longitud disminuye en 1.
 *
 * @note Complejidad O(pos).
 */
int lista_eliminar(Lista *l, int pos, int *valor);

/**
 * @brief Elimina el primer elemento de la lista.
 *
 * @details
 * Mueve la cabeza al siguiente nodo y libera el nodo eliminado. Si la lista
 * queda vacia, cola tambien pasa a NULL.
 *
 * @param l     Lista de la que se elimina.
 * @param valor Direccion donde se copia el dato eliminado; puede ser NULL.
 *
 * @retval 1 Se elimino el primer elemento.
 * @retval 0 l es NULL o la lista esta vacia.
 *
 * @note Complejidad O(1).
 */
int lista_eliminar_principio(Lista *l, int *valor);

/**
 * @brief Elimina el ultimo elemento de la lista.
 *
 * @details
 * Como la lista es simplemente enlazada, recorre hasta el penultimo nodo,
 * corta el enlace y libera el ultimo. Actualiza el puntero cola.
 *
 * @param l     Lista de la que se elimina.
 * @param valor Direccion donde se copia el dato eliminado; puede ser NULL.
 *
 * @retval 1 Se elimino el ultimo elemento.
 * @retval 0 l es NULL o la lista esta vacia.
 *
 * @note Complejidad O(n): hay que llegar al penultimo nodo.
 */
int lista_eliminar_final(Lista *l, int *valor);

/**
 * @brief Indica si un valor aparece al menos una vez en la lista.
 *
 * @details
 * Recorre la lista comparando el dato de cada nodo con el valor buscado.
 *
 * @param l     Lista a revisar.
 * @param valor Valor buscado.
 *
 * @retval 1 El valor aparece al menos una vez.
 * @retval 0 El valor no aparece o l es NULL.
 *
 * @note Complejidad O(n).
 */
int lista_esta(const Lista *l, int valor);

/**
 * @brief Busca un valor y devuelve su primera posicion.
 *
 * @details
 * Recorre la lista desde la cabeza y se detiene en la primera aparicion del
 * valor. Si el valor no esta, devuelve 0.
 *
 * @param l     Lista a revisar.
 * @param valor Valor buscado.
 *
 * @return Posicion entre 1 y longitud, o 0 si no aparece.
 *
 * @note Complejidad O(n).
 */
int lista_buscar(const Lista *l, int valor);

/**
 * @brief Elimina todas las apariciones de un valor.
 *
 * @details
 * Recorre la lista una sola vez y desenlaza todos los nodos cuyo dato sea
 * igual al valor. Actualiza cabeza y cola si es necesario. Es seguro con
 * valores repetidos, al principio, al final o en toda la lista.
 *
 * @param l     Lista que se modifica.
 * @param valor Valor que se elimina.
 *
 * @return Cantidad de nodos eliminados; 0 si no habia coincidencias o l es
 *         NULL.
 *
 * @post La longitud disminuye en la cantidad de nodos eliminados.
 *
 * @note Complejidad O(n).
 */
int lista_eliminar_valor(Lista *l, int valor);

/**
 * @brief Invierte el orden de los elementos de la lista.
 *
 * @details
 * Recorre la lista una vez y da vuelta cada enlace. Al final, la antigua
 * cabeza pasa a ser la cola y la antigua cola pasa a ser la cabeza. Si la
 * lista tiene 0 o 1 elementos, no hay cambios.
 *
 * @param l Lista a invertir. Si es NULL o esta vacia, no hace nada.
 *
 * @note Complejidad O(n).
 */
void lista_invertir(Lista *l);

/**
 * @brief Copia los elementos de una lista en otra.
 *
 * @details
 * Vacia destino y luego agrega una copia de cada elemento de origen, en el
 * mismo orden. Los nodos no se comparten: cada lista tiene su propia memoria.
 * Si origen y destino son la misma lista, no hace nada.
 *
 * @param origen  Lista fuente; no se modifica.
 * @param destino Lista destino; se vacia antes de copiar.
 *
 * @pre destino debe ser una lista valida (creada o inicializada).
 *
 * @note Complejidad O(n).
 */
void lista_copiar(const Lista *origen, Lista *destino);

/**
 * @brief Agrega al final de destino una copia de los elementos de origen.
 *
 * @details
 * Recorre origen y agrega cada valor al final de destino. Origen no se
 * modifica y no se comparten nodos. Si destino y origen son la misma lista,
 * no hace nada para evitar un crecimiento indefinido.
 *
 * @param destino Lista que recibe los elementos.
 * @param origen  Lista que se copia; no se modifica.
 *
 * @note Complejidad O(m), con m = longitud de origen.
 */
void lista_concatenar(Lista *destino, const Lista *origen);

/**
 * @brief Mezcla dos listas ordenadas en una tercera lista ordenada.
 *
 * @details
 * Compara el elemento actual de a con el de b y agrega el menor al final de
 * resultado. Cuando una lista se acaba, copia el resto de la otra. Los
 * elementos repetidos se conservan.
 *
 * @param a         Primera lista ordenada.
 * @param b         Segunda lista ordenada.
 * @param resultado Lista donde se guarda la mezcla; se vacia antes.
 *
 * @pre a y b estan ordenadas de menor a mayor.
 * @pre resultado debe ser distinta de a y de b.
 *
 * @note Complejidad O(n + m).
 */
void lista_combinar_ordenadas(const Lista *a, const Lista *b, Lista *resultado);

/**
 * @brief Guarda en resultado los valores que estan en ambas listas.
 *
 * @details
 * Para cada elemento de a, comprueba si esta en b y si aun no esta en
 * resultado. Si cumple ambas condiciones, lo agrega al final. Asi el
 * resultado no tiene repetidos.
 *
 * @param a         Primera lista.
 * @param b         Segunda lista.
 * @param resultado Lista con los valores comunes; se vacia antes.
 *
 * @pre resultado debe ser distinta de a y de b.
 *
 * @note Complejidad O(n * m) usando las operaciones del TDA.
 */
void lista_interseccion(const Lista *a, const Lista *b, Lista *resultado);

/**
 * @brief Indica si la lista esta en orden no decreciente.
 *
 * @details
 * Compara cada elemento con el siguiente. Si encuentra una bajada
 * (anterior > siguiente), responde 0. Una lista vacia o de un solo elemento
 * esta ordenada.
 *
 * @param l Lista a revisar; puede ser NULL.
 *
 * @retval 1 La lista esta ordenada o tiene 0/1 elementos.
 * @retval 0 Hay al menos un par fuera de orden.
 *
 * @note Complejidad O(n).
 */
int lista_esta_ordenada(const Lista *l);

/**
 * @brief Guarda la lista en un archivo de texto, un entero por linea.
 *
 * @details
 * Abre el archivo en modo escritura y escribe cada dato con fprintf. Si no
 * puede abrir el archivo, devuelve 0 sin modificar la lista.
 *
 * @param l    Lista que se guarda.
 * @param ruta Ruta del archivo.
 *
 * @retval 1 Se escribio el archivo correctamente.
 * @retval 0 l o ruta son NULL, o no se pudo abrir el archivo.
 *
 * @note Complejidad O(n).
 */
int lista_guardar(const Lista *l, const char *ruta);

/**
 * @brief Carga una lista desde un archivo de texto.
 *
 * @details
 * Abre el archivo en modo lectura, vacia la lista destino y lee enteros con
 * fscanf hasta el final del archivo. Si el archivo tiene texto no numerico,
 * la lectura se detiene en ese punto.
 *
 * @param l    Lista destino; se vacia antes de cargar.
 * @param ruta Ruta del archivo.
 *
 * @retval 1 Se abrio y se proceso el archivo.
 * @retval 0 l o ruta son NULL, o no se pudo abrir el archivo.
 *
 * @note Complejidad O(n).
 */
int lista_cargar(Lista *l, const char *ruta);

/**
 * @brief Muestra la lista por pantalla.
 *
 * @details
 * Imprime los elementos entre corchetes, separados por coma, y al final la
 * longitud. Si la lista esta vacia, muestra un mensaje.
 *
 * @param l Lista a mostrar; puede ser NULL.
 *
 * @note Formato: [1, 2, 3]  (longitud = 3).
 * @note Complejidad O(n).
 */
void imprimir_lista(const Lista *l);

/**
 * @brief Libera todos los nodos y deja la lista vacia pero usable.
 *
 * @details
 * Recorre la lista liberando cada nodo con free(). Al terminar, deja
 * cabeza = NULL, cola = NULL y longitud = 0. La estructura Lista no se
 * libera, por lo que puede volver a usarse.
 *
 * @param l Lista a vaciar. Si es NULL, no hace nada.
 *
 * @post La lista queda vacia.
 *
 * @note Complejidad O(n).
 *
 * @warning Los punteros a nodos que el cliente guardara antes de llamar a
 *          esta funcion quedan invalidos.
 */
void vaciar_lista(Lista *l);

/**
 * @brief Libera los nodos y la estructura de la lista.
 *
 * @details
 * Llama a vaciar_lista() y despues hace free(l). Se usa con listas creadas
 * con crear_lista().
 *
 * @param l Lista a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 *
 * @warning No usar con una lista declarada en el stack (iniciar_lista), porque
 *          free() sobre esa direccion es un error. Tampoco llamar dos veces
 *          sobre el mismo puntero.
 */
void destruir_lista(Lista *l);

/* =============================== TDA PILA ================================ */

/**
 * @brief TDA Pila (LIFO) construida sobre una Lista.
 *
 * @details
 * El tope de la pila es la cabeza de la lista interna. Apilar inserta al
 * principio y desapilar elimina el principio. El fondo es el ultimo nodo.
 */
typedef struct Pila {
    Lista lista; /**< Lista interna; su cabeza es el tope de la pila. */
} Pila;

/**
 * @brief Crea una pila vacia en memoria dinamica.
 *
 * @details
 * Reserva la estructura Pila y llama a iniciar_pila(). Si malloc falla,
 * imprime un mensaje de error.
 *
 * @return Puntero a la pila creada, o NULL si no hay memoria.
 *
 * @post La pila devuelta esta vacia.
 *
 * @note Complejidad O(1).
 * @warning Liberar con destruir_pila().
 */
Pila *crear_pila(void);

/**
 * @brief Inicializa una pila ya declarada.
 *
 * @details
 * Se usa con una variable Pila que no se reserva con malloc. No reserva
 * memoria; solo deja la lista interna vacia.
 *
 * @param p Pila a inicializar. Si es NULL, no hace nada.
 *
 * @post La pila queda vacia.
 */
void iniciar_pila(Pila *p);

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
int pila_es_vacia(const Pila *p);

/**
 * @brief Devuelve la cantidad de elementos de la pila.
 *
 * @param p Pila a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si p es NULL.
 *
 * @note Complejidad O(1).
 */
int pila_longitud(const Pila *p);

/**
 * @brief Apila un valor en el tope.
 *
 * @details
 * Inserta el valor en la posicion 1 de la lista interna. Si no hay memoria,
 * informa por pantalla y no modifica la pila.
 *
 * @param p     Pila destino. Si es NULL, no hace nada.
 * @param valor Valor que se apila.
 *
 * @post Si hubo exito, la pila tiene un elemento mas y el nuevo es el tope.
 *
 * @note Complejidad O(1).
 */
void apilar(Pila *p, int valor);

/**
 * @brief Desapila el tope y devuelve su valor.
 *
 * @details
 * Elimina el primer nodo de la lista interna y copia su dato en valor (si
 * valor no es NULL). La pila pierde su elemento superior.
 *
 * @param p     Pila de la que se saca.
 * @param valor Direccion donde se copia el dato; puede ser NULL.
 *
 * @retval 1 Se desapilo un elemento.
 * @retval 0 p es NULL o la pila esta vacia.
 *
 * @pre La pila deberia tener al menos un elemento; si esta vacia, la funcion
 *      devuelve 0 sin modificar nada.
 *
 * @note Complejidad O(1).
 */
int desapilar(Pila *p, int *valor);

/**
 * @brief Consulta el valor del tope sin sacarlo.
 *
 * @details
 * Copia el dato de la cabeza de la lista interna en valor (si valor no es
 * NULL). La pila no cambia.
 *
 * @param p     Pila a consultar.
 * @param valor Direccion donde se copia el dato; puede ser NULL.
 *
 * @retval 1 Se copio el tope.
 * @retval 0 p es NULL o la pila esta vacia.
 *
 * @pre La pila deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int pila_tope(const Pila *p, int *valor);

/**
 * @brief Indica si un valor esta en algun lugar de la pila.
 *
 * @details
 * Recorre la lista interna desde el tope hasta el fondo comparando los datos.
 *
 * @param p     Pila a revisar.
 * @param valor Valor buscado.
 *
 * @retval 1 El valor aparece en la pila.
 * @retval 0 El valor no aparece o p es NULL.
 *
 * @note Complejidad O(n).
 */
int pila_contiene(const Pila *p, int valor);

/**
 * @brief Muestra la pila del tope al fondo.
 *
 * @details
 * Imprime una linea con TOPE, luego cada elemento entre barras y al final
 * FONDO. Si la pila esta vacia, muestra un mensaje.
 *
 * @param p Pila a mostrar; puede ser NULL.
 *
 * @note Complejidad O(n).
 */
void imprimir_pila(const Pila *p);

/**
 * @brief Vacia la pila y la deja usable.
 *
 * @details
 * Libera todos los nodos de la lista interna y la deja vacia. La estructura
 * Pila no se libera.
 *
 * @param p Pila a vaciar. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 */
void vaciar_pila(Pila *p);

/**
 * @brief Libera todos los nodos y la estructura de la pila.
 *
 * @details
 * Vacia la pila y despues hace free(p). Se usa con pilas creadas con
 * crear_pila().
 *
 * @param p Pila a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 * @warning No usar con una pila declarada en el stack ni llamar dos veces.
 */
void destruir_pila(Pila *p);

/* =============================== TDA COLA ================================ */

/**
 * @brief TDA Cola (FIFO) construida sobre una Lista.
 *
 * @details
 * El frente es la cabeza de la lista interna y el final es su cola. Encolar
 * inserta al final y desencolar elimina el frente; ambas operaciones son O(1).
 */
typedef struct Cola {
    Lista lista; /**< Lista interna; su cabeza es el frente de la cola. */
} Cola;

/**
 * @brief Crea una cola vacia en memoria dinamica.
 *
 * @details
 * Reserva la estructura Cola y llama a iniciar_cola(). Si malloc falla,
 * imprime un mensaje de error.
 *
 * @return Puntero a la cola creada, o NULL si no hay memoria.
 *
 * @post La cola devuelta esta vacia.
 *
 * @note Complejidad O(1).
 * @warning Liberar con destruir_cola().
 */
Cola *crear_cola(void);

/**
 * @brief Inicializa una cola ya declarada.
 *
 * @details
 * Se usa con una variable Cola que no se reserva con malloc. No reserva
 * memoria; solo deja la lista interna vacia.
 *
 * @param c Cola a inicializar. Si es NULL, no hace nada.
 *
 * @post La cola queda vacia.
 */
void iniciar_cola(Cola *c);

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
int cola_es_vacia(const Cola *c);

/**
 * @brief Devuelve la cantidad de elementos de la cola.
 *
 * @param c Cola a consultar; puede ser NULL.
 *
 * @return Cantidad de elementos; 0 si c es NULL.
 *
 * @note Complejidad O(1).
 */
int cola_longitud(const Cola *c);

/**
 * @brief Encola un valor al final.
 *
 * @details
 * Inserta el valor en la ultima posicion de la lista interna. Si no hay
 * memoria, informa por pantalla y no modifica la cola.
 *
 * @param c     Cola destino. Si es NULL, no hace nada.
 * @param valor Valor que se encola.
 *
 * @post Si hubo exito, la cola tiene un elemento mas al final.
 *
 * @note Complejidad O(1) porque la lista guarda el puntero cola.
 */
void encolar(Cola *c, int valor);

/**
 * @brief Desencola el frente y devuelve su valor.
 *
 * @details
 * Elimina el primer nodo de la lista interna y copia su dato en valor (si
 * valor no es NULL). Los demas elementos se corren conceptualmente un lugar
 * hacia el frente.
 *
 * @param c     Cola de la que se saca.
 * @param valor Direccion donde se copia el dato; puede ser NULL.
 *
 * @retval 1 Se desencolo un elemento.
 * @retval 0 c es NULL o la cola esta vacia.
 *
 * @pre La cola deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int desencolar(Cola *c, int *valor);

/**
 * @brief Consulta el valor del frente sin sacarlo.
 *
 * @details
 * Copia el dato de la cabeza de la lista interna en valor (si valor no es
 * NULL). La cola no cambia.
 *
 * @param c     Cola a consultar.
 * @param valor Direccion donde se copia el dato; puede ser NULL.
 *
 * @retval 1 Se copio el frente.
 * @retval 0 c es NULL o la cola esta vacia.
 *
 * @pre La cola deberia tener al menos un elemento; si esta vacia, devuelve 0.
 *
 * @note Complejidad O(1).
 */
int frente(const Cola *c, int *valor);

/**
 * @brief Indica si un valor esta en algun lugar de la cola.
 *
 * @details
 * Recorre la lista interna desde el frente hasta el final comparando los
 * datos.
 *
 * @param c     Cola a revisar.
 * @param valor Valor buscado.
 *
 * @retval 1 El valor aparece en la cola.
 * @retval 0 El valor no aparece o c es NULL.
 *
 * @note Complejidad O(n).
 */
int cola_contiene(const Cola *c, int valor);

/**
 * @brief Muestra la cola del frente al final.
 *
 * @details
 * Imprime FRENTE ->, luego los elementos separados por flechas y al final
 * FIN. Si la cola esta vacia, muestra un mensaje.
 *
 * @param c Cola a mostrar; puede ser NULL.
 *
 * @note Complejidad O(n).
 */
void imprimir_cola(const Cola *c);

/**
 * @brief Vacia la cola y la deja usable.
 *
 * @details
 * Libera todos los nodos de la lista interna y la deja vacia. La estructura
 * Cola no se libera.
 *
 * @param c Cola a vaciar. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 */
void vaciar_cola(Cola *c);

/**
 * @brief Libera todos los nodos y la estructura de la cola.
 *
 * @details
 * Vacia la cola y despues hace free(c). Se usa con colas creadas con
 * crear_cola().
 *
 * @param c Cola a destruir. Si es NULL, no hace nada.
 *
 * @note Complejidad O(n).
 * @warning No usar con una cola declarada en el stack ni llamar dos veces.
 */
void destruir_cola(Cola *c);

/* ===================== utilidades para ordenamientos ===================== */

/**
 * @brief Intercambia los valores apuntados por a y b.
 *
 * @details
 * Guarda el valor de *a en una variable temporal, copia *b en *a y luego el
 * temporal en *b.
 *
 * @param a Puntero al primer entero; no debe ser NULL.
 * @param b Puntero al segundo entero; no debe ser NULL.
 *
 * @pre a y b deben apuntar a enteros validos.
 *
 * @note Complejidad O(1).
 */
void intercambiar(int *a, int *b);

#endif
