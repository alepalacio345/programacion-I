#include <stdio.h>
#include <stdlib.h>
#include "lista_prestamo.h"

static NodoPrestamo *crear_nodo(const Prestamo *p)
{
    NodoPrestamo *nuevo = (NodoPrestamo *) malloc(sizeof(NodoPrestamo));

    if (nuevo != NULL) {
        nuevo->dato = *p;
        nuevo->siguiente = NULL;
    }

    return nuevo;
}

ListaPrestamo *crear_lista_prestamo(void)
{
    ListaPrestamo *l = (ListaPrestamo *) malloc(sizeof(ListaPrestamo));

    if (l == NULL) {
        printf("No hay memoria para la lista.\n");
        return NULL;
    }

    iniciar_lista_prestamo(l);

    return l;
}

void iniciar_lista_prestamo(ListaPrestamo *l)
{
    if (l == NULL) {
        return;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

int lista_prestamo_es_vacia(const ListaPrestamo *l)
{
    return ((l == NULL) || (l->cabeza == NULL));
}

int lista_prestamo_longitud(const ListaPrestamo *l)
{
    return ((l == NULL) ? 0 : l->longitud);
}

int lista_prestamo_insertar_final(ListaPrestamo *l, const Prestamo *p)
{
    NodoPrestamo *nuevo;

    if ((l == NULL) || (p == NULL)) {
        return 0;
    }

    nuevo = crear_nodo(p);

    if (nuevo == NULL) {
        printf("No hay memoria para el prestamo.\n");
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

int lista_prestamo_eliminar_final(ListaPrestamo *l, Prestamo *p)
{
    NodoPrestamo *anterior;
    NodoPrestamo *ultimo;

    if ((l == NULL) || (p == NULL) || (l->cabeza == NULL)) {
        return 0;
    }

    if (l->longitud == 1) {
        *p = l->cabeza->dato;
        free(l->cabeza);
        l->cabeza = NULL;
        l->cola = NULL;
        l->longitud = 0;
        return 1;
    }

    anterior = l->cabeza;

    while (anterior->siguiente != l->cola) {
        anterior = anterior->siguiente;
    }

    ultimo = l->cola;
    *p = ultimo->dato;
    l->cola = anterior;
    anterior->siguiente = NULL;
    free(ultimo);
    l->longitud--;

    return 1;
}

void lista_prestamo_imprimir(const ListaPrestamo *l)
{
    const NodoPrestamo *actual;

    if ((l == NULL) || (l->cabeza == NULL)) {
        printf("No hay prestamos.\n");
        return;
    }

    actual = l->cabeza;

    while (actual != NULL) {
        printf("Cedula: %s | Libro: %s | Hora: %s\n",
               actual->dato.cedula, actual->dato.codigo, actual->dato.hora);
        actual = actual->siguiente;
    }
}

void vaciar_lista_prestamo(ListaPrestamo *l)
{
    NodoPrestamo *actual;
    NodoPrestamo *siguiente;

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

void destruir_lista_prestamo(ListaPrestamo *l)
{
    if (l == NULL) {
        return;
    }

    vaciar_lista_prestamo(l);
    free(l);
}

PilaPrestamo *crear_pila_prestamo(void)
{
    PilaPrestamo *p = (PilaPrestamo *) malloc(sizeof(PilaPrestamo));

    if (p == NULL) {
        printf("No hay memoria para la pila.\n");
        return NULL;
    }

    iniciar_pila_prestamo(p);

    return p;
}

void iniciar_pila_prestamo(PilaPrestamo *p)
{
    if (p == NULL) {
        return;
    }

    p->tope = NULL;
    p->longitud = 0;
}

int pila_prestamo_es_vacia(const PilaPrestamo *p)
{
    return ((p == NULL) || (p->tope == NULL));
}

int pila_prestamo_longitud(const PilaPrestamo *p)
{
    return ((p == NULL) ? 0 : p->longitud);
}

int pila_prestamo_apilar(PilaPrestamo *p, const Prestamo *dato)
{
    NodoPrestamo *nuevo;

    if ((p == NULL) || (dato == NULL)) {
        return 0;
    }

    nuevo = crear_nodo(dato);

    if (nuevo == NULL) {
        printf("No hay memoria para el prestamo.\n");
        return 0;
    }

    nuevo->siguiente = p->tope;
    p->tope = nuevo;
    p->longitud++;

    return 1;
}

int pila_prestamo_desapilar(PilaPrestamo *p, Prestamo *dato)
{
    NodoPrestamo *ultimo;

    if ((p == NULL) || (dato == NULL) || (p->tope == NULL)) {
        return 0;
    }

    ultimo = p->tope;
    *dato = ultimo->dato;
    p->tope = ultimo->siguiente;
    free(ultimo);
    p->longitud--;

    return 1;
}

void pila_prestamo_imprimir(const PilaPrestamo *p)
{
    const NodoPrestamo *actual;

    if ((p == NULL) || (p->tope == NULL)) {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("TOPE\n");
    actual = p->tope;

    while (actual != NULL) {
        printf("Cedula: %s | Libro: %s | Hora: %s\n",
               actual->dato.cedula, actual->dato.codigo, actual->dato.hora);
        actual = actual->siguiente;
    }

    printf("FONDO\n");
}

void vaciar_pila_prestamo(PilaPrestamo *p)
{
    NodoPrestamo *actual;
    NodoPrestamo *siguiente;

    if (p == NULL) {
        return;
    }

    actual = p->tope;

    while (actual != NULL) {
        siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    p->tope = NULL;
    p->longitud = 0;
}

void destruir_pila_prestamo(PilaPrestamo *p)
{
    if (p == NULL) {
        return;
    }

    vaciar_pila_prestamo(p);
    free(p);
}
