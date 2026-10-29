#ifndef LISTA_ITEM_H
#define LISTA_ITEM_H

/**
 * @file lista_item.h
 * @brief TDA Lista Enlazada para objetos de inventario (struct Item).
 *
 * @details
 * El nodo de la lista es el propio struct Item: cada objeto guarda su
 * nombre, su categoria, su durabilidad y el puntero al siguiente objeto.
 * La lista mantiene punteros al primero y al ultimo para insertar al final
 * en O(1), y la cantidad de elementos.
 *
 * Categorias validas:
 *   - 'A': Arma
 *   - 'P': Pocion
 *   - 'M': Material
 *
 * La durabilidad valida va de 0 a 100.
 *
 * @par Ejemplo
 * @code
 * ListaItem *inv = crear_lista_item();
 * lista_item_cargar(inv, "inventario.txt");
 * lista_item_limpiar_durabilidad_cero(inv);
 * lista_item_reporte(inv);
 * destruir_lista_item(inv);
 * @endcode
 */

#define ITEM_NOMBRE_MAX 30
#define ITEM_DURABILIDAD_MIN 0
#define ITEM_DURABILIDAD_MAX 100

/**
 * @brief Objeto del inventario.
 *
 * @details
 * Es el nodo de la lista: el campo siguiente enlaza con el proximo objeto.
 * El ultimo objeto del inventario tiene siguiente == NULL.
 */
typedef struct Item {
    char nombre[ITEM_NOMBRE_MAX]; /**< Nombre del objeto (sin espacios). */
    char categoria;               /**< 'A' arma, 'P' pocion, 'M' material. */
    int durabilidad;              /**< Valor entre 0 y 100. */
    struct Item *siguiente;       /**< Siguiente objeto; NULL si es el ultimo. */
} Item;

/**
 * @brief TDA Lista de objetos de inventario.
 *
 * @details
 * Guarda el primero y el ultimo objeto, mas la cantidad de objetos.
 */
typedef struct ListaItem {
    Item *cabeza; /**< Primer objeto; NULL si la lista esta vacia. */
    Item *cola;   /**< Ultimo objeto; NULL si la lista esta vacia. */
    int longitud; /**< Cantidad de objetos en la lista. */
} ListaItem;

/**
 * @brief Crea una lista de inventario vacia.
 *
 * @return Puntero a la lista, o NULL si no hay memoria.
 *
 * @note Liberar con destruir_lista_item().
 */
ListaItem *crear_lista_item(void);

/**
 * @brief Inicializa una lista de inventario ya declarada.
 *
 * @param l Lista a inicializar. Si es NULL, no hace nada.
 *
 * @note No reserva memoria; usar con una variable ListaItem del stack.
 */
void iniciar_lista_item(ListaItem *l);

/**
 * @brief Indica si la lista no tiene objetos.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @retval 1 La lista es NULL o esta vacia.
 * @retval 0 La lista tiene al menos un objeto.
 */
int lista_item_es_vacia(const ListaItem *l);

/**
 * @brief Devuelve la cantidad de objetos de la lista.
 *
 * @param l Lista a consultar; puede ser NULL.
 *
 * @return Cantidad de objetos; 0 si l es NULL.
 */
int lista_item_longitud(const ListaItem *l);

/**
 * @brief Inserta un objeto al final de la lista.
 *
 * @details
 * Valida el nombre, la categoria y la durabilidad, reserva un Item, copia
 * los datos y lo engancha al final. Si la lista esta vacia, el objeto nuevo
 * es cabeza y cola.
 *
 * @param l           Lista destino.
 * @param nombre      Nombre del objeto; no debe ser NULL ni vacio.
 * @param categoria   'A', 'P' o 'M'.
 * @param durabilidad Entero entre 0 y 100.
 *
 * @retval 1 Se inserto el objeto.
 * @retval 0 l es NULL, los datos son invalidos o no hay memoria.
 *
 * @note Complejidad O(1).
 */
int lista_item_insertar_final(ListaItem *l, const char *nombre,
                              char categoria, int durabilidad);

/**
 * @brief Carga el inventario desde un archivo de texto.
 *
 * @details
 * Cada linea debe tener el formato:
 * @code
 * Nombre Categoria Durabilidad
 * @endcode
 * Por ejemplo: `Espada_Larga A 45`.
 *
 * La funcion vacia la lista antes de cargar. Las lineas que no tengan los
 * tres campos, o cuyos datos sean invalidos, se ignoran y se avisa por
 * pantalla.
 *
 * @param l    Lista destino; se vacia antes de cargar.
 * @param ruta Ruta del archivo.
 *
 * @retval 1 Se abrio el archivo y se proceso.
 * @retval 0 l o ruta son NULL, o no se pudo abrir el archivo.
 *
 * @note Complejidad O(n).
 */
int lista_item_cargar(ListaItem *l, const char *ruta);

/**
 * @brief Elimina todos los objetos con durabilidad igual a 0.
 *
 * @details
 * Recorre la lista una sola vez con tres punteros (anterior, actual y
 * siguiente). Cuando encuentra un objeto con durabilidad 0, puentea los
 * enlaces, actualiza cabeza/cola si hace falta y libera el objeto. No crea
 * una segunda lista.
 *
 * @param l Lista a limpiar. Si es NULL, no hace nada.
 *
 * @return Cantidad de objetos eliminados.
 *
 * @note Complejidad O(n).
 */
int lista_item_limpiar_durabilidad_cero(ListaItem *l);

/**
 * @brief Cuenta cuantos objetos hay de una categoria.
 *
 * @param l         Lista a revisar.
 * @param categoria 'A', 'P' o 'M'.
 *
 * @return Cantidad de objetos de esa categoria; 0 si l es NULL o la
 *         categoria no es valida.
 */
int lista_item_contar_categoria(const ListaItem *l, char categoria);

/**
 * @brief Imprime todos los objetos de la lista.
 *
 * @param l Lista a mostrar; puede ser NULL.
 *
 * @note Si la lista esta vacia, muestra un mensaje.
 */
void lista_item_imprimir(const ListaItem *l);

/**
 * @brief Imprime el inventario resultante y el conteo por categoria.
 *
 * @details
 * Muestra cada objeto sobreviviente y al final cuantas armas, pociones y
 * materiales quedaron.
 *
 * @param l Lista a reportar; puede ser NULL.
 */
void lista_item_reporte(const ListaItem *l);

/**
 * @brief Libera todos los objetos y deja la lista vacia pero usable.
 *
 * @param l Lista a vaciar. Si es NULL, no hace nada.
 */
void vaciar_lista_item(ListaItem *l);

/**
 * @brief Libera los objetos y la estructura de la lista.
 *
 * @param l Lista a destruir. Si es NULL, no hace nada.
 *
 * @warning Solo para listas creadas con crear_lista_item(). No usar con una
 *          lista del stack ni llamar dos veces.
 */
void destruir_lista_item(ListaItem *l);

#endif
