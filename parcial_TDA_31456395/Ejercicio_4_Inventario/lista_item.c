#include <stdio.h>
#include <stdlib.h>
#include "lista_item.h"

//funciones de la lista de objetos del inventario

//funciones auxiliares

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

//operaciones

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
