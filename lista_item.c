#include <stdio.h>
#include <stdlib.h>
#include "lista_item.h"

/* ============================================================================
 * LISTA_ITEM.C
 * ----------------------------------------------------------------------------
 * Implementacion del TDA Lista de objetos de inventario.
 *
 * El nodo es el propio struct Item: no hay un Nodo separado. La lista guarda
 * punteros al primero y al ultimo, y la cantidad de objetos.
 * ========================================================================== */

/* ------------------------- funciones auxiliares -------------------------- */

static int categoria_valida(char categoria)
{
    return ((categoria == 'A') || (categoria == 'P') || (categoria == 'M'));
}

static int durabilidad_valida(int durabilidad)
{
    return ((durabilidad >= ITEM_DURABILIDAD_MIN) &&
            (durabilidad <= ITEM_DURABILIDAD_MAX));
}

/* Reserva un Item y copia los datos. Devuelve NULL si los datos no son
 * validos o si no hay memoria. */
static Item *item_crear(const char *nombre, char categoria, int durabilidad)
{
    Item *nuevo = NULL;

    if ((nombre != NULL) && (nombre[0] != '\0') &&
        categoria_valida(categoria) &&
        durabilidad_valida(durabilidad)) {
        nuevo = (Item *) malloc(sizeof(Item));

        if (nuevo != NULL) {
            snprintf(nuevo->nombre, sizeof(nuevo->nombre), "%s", nombre);
            nuevo->categoria = categoria;
            nuevo->durabilidad = durabilidad;
            nuevo->siguiente = NULL;
        }
    }

    return nuevo;
}

/* =============================== OPERACIONES ============================= */

ListaItem *crear_lista_item(void)
{
    ListaItem *l = (ListaItem *) malloc(sizeof(ListaItem));

    if (l == NULL) {
        printf("Error: no hay memoria para crear la lista de inventario.\n");
        return NULL;
    }

    iniciar_lista_item(l);

    return l;
}

void iniciar_lista_item(ListaItem *l)
{
    if (l == NULL) {
        return;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

int lista_item_es_vacia(const ListaItem *l)
{
    return ((l == NULL) || (l->cabeza == NULL));
}

int lista_item_longitud(const ListaItem *l)
{
    return ((l == NULL) ? 0 : l->longitud);
}

int lista_item_insertar_final(ListaItem *l, const char *nombre,
                              char categoria, int durabilidad)
{
    Item *nuevo;

    if (l == NULL) {
        return 0;
    }

    nuevo = item_crear(nombre, categoria, durabilidad);

    if (nuevo == NULL) {
        printf("Error: datos invalidos o sin memoria para el objeto.\n");
        return 0;
    }

    if (l->cabeza == NULL) {
        l->cabeza = nuevo;
        l->cola = nuevo;
    } else {
        l->cola->siguiente = nuevo;
        l->cola = nuevo;
    }

    l->longitud++;

    return 1;
}

int lista_item_cargar(ListaItem *l, const char *ruta)
{
    FILE *archivo;
    char linea[256];
    char nombre[ITEM_NOMBRE_MAX];
    char categoria;
    int durabilidad;
    int numero_linea = 0;

    if ((l == NULL) || (ruta == NULL)) {
        return 0;
    }

    archivo = fopen(ruta, "r");

    if (archivo == NULL) {
        return 0;
    }

    vaciar_lista_item(l);

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        numero_linea++;

        if (sscanf(linea, "%29s %c %d", nombre, &categoria, &durabilidad) == 3) {
            if (categoria_valida(categoria) &&
                durabilidad_valida(durabilidad)) {
                if (!lista_item_insertar_final(l, nombre, categoria,
                                               durabilidad)) {
                    printf("Aviso: no se pudo insertar la linea %d.\n",
                           numero_linea);
                }
            } else {
                printf("Aviso: linea %d con categoria o durabilidad invalida.\n",
                       numero_linea);
            }
        } else {
            printf("Aviso: linea %d con formato invalido (se esperaba "
                   "Nombre Categoria Durabilidad).\n", numero_linea);
        }
    }

    fclose(archivo);

    return 1;
}

int lista_item_limpiar_durabilidad_cero(ListaItem *l)
{
    Item *actual;
    Item *anterior = NULL;
    Item *siguiente;
    int eliminados = 0;

    if (l == NULL) {
        return 0;
    }

    actual = l->cabeza;

    while (actual != NULL) {
        siguiente = actual->siguiente;

        if (actual->durabilidad == 0) {
            /* Puenteamos el nodo: el anterior salta al siguiente. */
            if (anterior == NULL) {
                l->cabeza = siguiente;
            } else {
                anterior->siguiente = siguiente;
            }

            if (actual == l->cola) {
                l->cola = anterior;
            }

            free(actual);
            l->longitud--;
            eliminados++;
        } else {
            anterior = actual;
        }

        actual = siguiente;
    }

    return eliminados;
}

int lista_item_contar_categoria(const ListaItem *l, char categoria)
{
    const Item *actual;
    int cantidad = 0;

    if ((l == NULL) || (!categoria_valida(categoria))) {
        return 0;
    }

    actual = l->cabeza;

    while (actual != NULL) {
        if (actual->categoria == categoria) {
            cantidad++;
        }

        actual = actual->siguiente;
    }

    return cantidad;
}

void lista_item_imprimir(const ListaItem *l)
{
    const Item *actual;

    if ((l == NULL) || (l->cabeza == NULL)) {
        printf("La lista de inventario esta vacia.\n");
        return;
    }

    actual = l->cabeza;

    while (actual != NULL) {
        printf("- %s | categoria %c | durabilidad %d\n",
               actual->nombre, actual->categoria, actual->durabilidad);
        actual = actual->siguiente;
    }
}

void lista_item_reporte(const ListaItem *l)
{
    printf("Inventario resultante:\n");

    if ((l == NULL) || (l->cabeza == NULL)) {
        printf("  (sin objetos)\n");
    } else {
        lista_item_imprimir(l);
    }

    printf("\nConteo por categoria:\n");
    printf("  Armas (A):      %d\n", lista_item_contar_categoria(l, 'A'));
    printf("  Pociones (P):   %d\n", lista_item_contar_categoria(l, 'P'));
    printf("  Materiales (M): %d\n", lista_item_contar_categoria(l, 'M'));
    printf("  Total:          %d\n", lista_item_longitud(l));
}

void vaciar_lista_item(ListaItem *l)
{
    Item *actual;
    Item *siguiente;

    if (l == NULL) {
        return;
    }

    actual = l->cabeza;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

void destruir_lista_item(ListaItem *l)
{
    if (l == NULL) {
        return;
    }

    vaciar_lista_item(l);
    free(l);
}
