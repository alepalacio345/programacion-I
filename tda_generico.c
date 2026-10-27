#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tda_generico.h"

/* ============================================================================
 * TDA_GENERICO.C
 * ----------------------------------------------------------------------------
 * Implementacion generica de Lista, Pila y Cola.
 *
 * Cada nodo guarda:
 *      - void *dato  -> direccion de una copia de "tam" bytes del elemento.
 *      - NodoG *siguiente
 *
 * ESTILO: returns tempranos cuando simplifican, memoria validada antes de
 * enganchar el nodo, parentesis en las expresiones y bloques separados.
 * ========================================================================== */

/* ------------------------- funciones auxiliares -------------------------- */

static NodoG *nodo_g_crear(size_t tam, const void *dato)
{
    NodoG *nuevo = (NodoG *) malloc(sizeof(NodoG));

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->dato = malloc(tam);

    if (nuevo->dato == NULL) {
        free(nuevo);
        return NULL;
    }

    memcpy(nuevo->dato, dato, tam);
    nuevo->siguiente = NULL;

    return nuevo;
}

static int comparar_elementos(const ListaG *l, const void *a, const void *b)
{
    if (l->comparar != NULL) {
        return l->comparar(a, b);
    }

    return memcmp(a, b, l->tam);
}

/* =============================== TDA LISTA =============================== */

ListaG *lista_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar)
{
    ListaG *l = (ListaG *) malloc(sizeof(ListaG));

    if (l == NULL) {
        printf("Error: no hay memoria para crear la lista.\n");
        return NULL;
    }

    lista_g_iniciar(l, tam, imprimir, comparar);

    return l;
}

void lista_g_iniciar(ListaG *l, size_t tam,
                     ImpresorTDA imprimir, ComparadorTDA comparar)
{
    if (l == NULL) {
        return;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
    l->tam = ((tam == 0) ? 1 : tam);
    l->imprimir = imprimir;
    l->comparar = comparar;
}

int lista_g_es_vacia(const ListaG *l)
{
    return ((l == NULL) || (l->cabeza == NULL));
}

int lista_g_longitud(const ListaG *l)
{
    return ((l == NULL) ? 0 : l->longitud);
}

int lista_g_insertar(ListaG *l, int pos, const void *dato)
{
    NodoG *nuevo;
    NodoG *ant;
    int i;

    if ((l == NULL) || (dato == NULL) || (pos < 1) ||
        (pos > (l->longitud + 1))) {
        return 0;
    }

    nuevo = nodo_g_crear(l->tam, dato);

    if (nuevo == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return 0;
    }

    if (pos == 1) {
        nuevo->siguiente = l->cabeza;
        l->cabeza = nuevo;

        if (l->cola == NULL) {
            l->cola = nuevo;
        }
    } else if (pos == (l->longitud + 1)) {
        if (l->cabeza == NULL) {
            l->cabeza = nuevo;
            l->cola = nuevo;
        } else {
            l->cola->siguiente = nuevo;
            l->cola = nuevo;
        }
    } else {
        ant = l->cabeza;

        for (i = 1; i < (pos - 1); i++) {
            ant = ant->siguiente;
        }

        nuevo->siguiente = ant->siguiente;
        ant->siguiente = nuevo;
    }

    l->longitud++;

    return 1;
}

int lista_g_consultar(const ListaG *l, int pos, void *salida)
{
    const NodoG *act;
    int i;

    if ((l == NULL) || (salida == NULL) || (pos < 1) ||
        (pos > l->longitud)) {
        return 0;
    }

    act = l->cabeza;

    for (i = 1; i < pos; i++) {
        act = act->siguiente;
    }

    memcpy(salida, act->dato, l->tam);

    return 1;
}

int lista_g_modificar(ListaG *l, int pos, const void *dato)
{
    NodoG *act;
    int i;

    if ((l == NULL) || (dato == NULL) || (pos < 1) ||
        (pos > l->longitud)) {
        return 0;
    }

    act = l->cabeza;

    for (i = 1; i < pos; i++) {
        act = act->siguiente;
    }

    memcpy(act->dato, dato, l->tam);

    return 1;
}

int lista_g_eliminar(ListaG *l, int pos, void *salida)
{
    NodoG *ant;
    NodoG *act;
    int i;

    if ((l == NULL) || (pos < 1) || (pos > l->longitud)) {
        return 0;
    }

    if (pos == 1) {
        return lista_g_eliminar_principio(l, salida);
    }

    ant = l->cabeza;

    for (i = 1; i < (pos - 1); i++) {
        ant = ant->siguiente;
    }

    act = ant->siguiente;
    ant->siguiente = act->siguiente;

    if (act == l->cola) {
        l->cola = ant;
    }

    if (salida != NULL) {
        memcpy(salida, act->dato, l->tam);
    }

    free(act->dato);
    free(act);
    l->longitud--;

    return 1;
}

int lista_g_eliminar_principio(ListaG *l, void *salida)
{
    NodoG *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        return 0;
    }

    act = l->cabeza;
    l->cabeza = act->siguiente;

    if (l->cabeza == NULL) {
        l->cola = NULL;
    }

    if (salida != NULL) {
        memcpy(salida, act->dato, l->tam);
    }

    free(act->dato);
    free(act);
    l->longitud--;

    return 1;
}

int lista_g_eliminar_final(ListaG *l, void *salida)
{
    NodoG *ant;
    NodoG *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        return 0;
    }

    if (l->longitud == 1) {
        return lista_g_eliminar_principio(l, salida);
    }

    ant = l->cabeza;

    while (ant->siguiente != l->cola) {
        ant = ant->siguiente;
    }

    act = l->cola;
    ant->siguiente = NULL;
    l->cola = ant;

    if (salida != NULL) {
        memcpy(salida, act->dato, l->tam);
    }

    free(act->dato);
    free(act);
    l->longitud--;

    return 1;
}

int lista_g_buscar(const ListaG *l, const void *dato)
{
    const NodoG *act;
    int pos = 1;

    if ((l == NULL) || (dato == NULL)) {
        return 0;
    }

    act = l->cabeza;

    while (act != NULL) {
        if (comparar_elementos(l, act->dato, dato) == 0) {
            return pos;
        }

        act = act->siguiente;
        pos++;
    }

    return 0;
}

int lista_g_esta(const ListaG *l, const void *dato)
{
    return (lista_g_buscar(l, dato) != 0);
}

int lista_g_eliminar_valor(ListaG *l, const void *dato)
{
    int eliminados = 0;
    NodoG *act;
    NodoG *ant = NULL;
    NodoG *sig;

    if ((l == NULL) || (dato == NULL)) {
        return 0;
    }

    act = l->cabeza;

    while (act != NULL) {
        if (comparar_elementos(l, act->dato, dato) == 0) {
            sig = act->siguiente;

            if (ant == NULL) {
                l->cabeza = sig;
            } else {
                ant->siguiente = sig;
            }

            if (act == l->cola) {
                l->cola = ant;
            }

            free(act->dato);
            free(act);
            l->longitud--;
            eliminados++;
            act = sig;
        } else {
            ant = act;
            act = act->siguiente;
        }
    }

    return eliminados;
}

void lista_g_invertir(ListaG *l)
{
    NodoG *anterior = NULL;
    NodoG *act;
    NodoG *siguiente;

    if ((l == NULL) || (l->cabeza == NULL)) {
        return;
    }

    l->cola = l->cabeza;
    act = l->cabeza;

    while (act != NULL) {
        siguiente = act->siguiente;
        act->siguiente = anterior;
        anterior = act;
        act = siguiente;
    }

    l->cabeza = anterior;
}

void lista_g_imprimir(const ListaG *l)
{
    const NodoG *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        printf("La lista esta vacia.\n");
        return;
    }

    printf("[");

    for (act = l->cabeza; act != NULL; act = act->siguiente) {
        if (l->imprimir != NULL) {
            l->imprimir(act->dato);
        } else {
            printf("?");
        }

        if (act->siguiente != NULL) {
            printf(", ");
        }
    }

    printf("]  (longitud = %d)\n", l->longitud);
}

void lista_g_vaciar(ListaG *l)
{
    NodoG *act;
    NodoG *siguiente;

    if (l == NULL) {
        return;
    }

    act = l->cabeza;

    while (act != NULL) {
        siguiente = act->siguiente;

        free(act->dato);
        free(act);
        act = siguiente;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

void lista_g_destruir(ListaG *l)
{
    if (l == NULL) {
        return;
    }

    lista_g_vaciar(l);

    free(l);
}

/* =============================== TDA PILA ================================ */

PilaG *pila_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar)
{
    PilaG *p = (PilaG *) malloc(sizeof(PilaG));

    if (p == NULL) {
        printf("Error: no hay memoria para crear la pila.\n");
        return NULL;
    }

    pila_g_iniciar(p, tam, imprimir, comparar);

    return p;
}

void pila_g_iniciar(PilaG *p, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar)
{
    if (p == NULL) {
        return;
    }

    lista_g_iniciar(&p->lista, tam, imprimir, comparar);
}

int pila_g_es_vacia(const PilaG *p)
{
    return ((p == NULL) || (p->lista.cabeza == NULL));
}

int pila_g_longitud(const PilaG *p)
{
    return ((p == NULL) ? 0 : p->lista.longitud);
}

void pila_g_apilar(PilaG *p, const void *dato)
{
    if (p == NULL) {
        return;
    }

    lista_g_insertar(&p->lista, 1, dato);
}

int pila_g_desapilar(PilaG *p, void *salida)
{
    if (p == NULL) {
        return 0;
    }

    return lista_g_eliminar_principio(&p->lista, salida);
}

int pila_g_tope(const PilaG *p, void *salida)
{
    if (p == NULL) {
        return 0;
    }

    return lista_g_consultar(&p->lista, 1, salida);
}

int pila_g_contiene(const PilaG *p, const void *dato)
{
    return ((p == NULL) ? 0 : lista_g_esta(&p->lista, dato));
}

void pila_g_imprimir(const PilaG *p)
{
    const NodoG *act;

    if ((p == NULL) || (p->lista.cabeza == NULL)) {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("TOPE\n");

    for (act = p->lista.cabeza; act != NULL; act = act->siguiente) {
        printf("  | ");

        if (p->lista.imprimir != NULL) {
            p->lista.imprimir(act->dato);
        } else {
            printf("?");
        }

        printf(" |\n");
    }

    printf("FONDO\n");
}

void pila_g_vaciar(PilaG *p)
{
    if (p == NULL) {
        return;
    }

    lista_g_vaciar(&p->lista);
}

void pila_g_destruir(PilaG *p)
{
    if (p == NULL) {
        return;
    }

    pila_g_vaciar(p);

    free(p);
}

/* =============================== TDA COLA ================================ */

ColaG *cola_g_crear(size_t tam, ImpresorTDA imprimir, ComparadorTDA comparar)
{
    ColaG *c = (ColaG *) malloc(sizeof(ColaG));

    if (c == NULL) {
        printf("Error: no hay memoria para crear la cola.\n");
        return NULL;
    }

    cola_g_iniciar(c, tam, imprimir, comparar);

    return c;
}

void cola_g_iniciar(ColaG *c, size_t tam,
                    ImpresorTDA imprimir, ComparadorTDA comparar)
{
    if (c == NULL) {
        return;
    }

    lista_g_iniciar(&c->lista, tam, imprimir, comparar);
}

int cola_g_es_vacia(const ColaG *c)
{
    return ((c == NULL) || (c->lista.cabeza == NULL));
}

int cola_g_longitud(const ColaG *c)
{
    return ((c == NULL) ? 0 : c->lista.longitud);
}

void cola_g_encolar(ColaG *c, const void *dato)
{
    if (c == NULL) {
        return;
    }

    lista_g_insertar(&c->lista, lista_g_longitud(&c->lista) + 1, dato);
}

int cola_g_desencolar(ColaG *c, void *salida)
{
    if (c == NULL) {
        return 0;
    }

    return lista_g_eliminar_principio(&c->lista, salida);
}

int cola_g_frente(const ColaG *c, void *salida)
{
    if (c == NULL) {
        return 0;
    }

    return lista_g_consultar(&c->lista, 1, salida);
}

int cola_g_contiene(const ColaG *c, const void *dato)
{
    return ((c == NULL) ? 0 : lista_g_esta(&c->lista, dato));
}

void cola_g_imprimir(const ColaG *c)
{
    const NodoG *act;

    if ((c == NULL) || (c->lista.cabeza == NULL)) {
        printf("La cola esta vacia.\n");
        return;
    }

    printf("FRENTE -> ");

    for (act = c->lista.cabeza; act != NULL; act = act->siguiente) {
        if (c->lista.imprimir != NULL) {
            c->lista.imprimir(act->dato);
        } else {
            printf("?");
        }

        if (act->siguiente != NULL) {
            printf(" -> ");
        }
    }

    printf(" -> FIN\n");
}

void cola_g_vaciar(ColaG *c)
{
    if (c == NULL) {
        return;
    }

    lista_g_vaciar(&c->lista);
}

void cola_g_destruir(ColaG *c)
{
    if (c == NULL) {
        return;
    }

    cola_g_vaciar(c);

    free(c);
}

/* ===================== impresores y comparadores ========================= */

void imprimir_int(const void *dato)
{
    printf("%d", *(const int *) dato);
}

void imprimir_float(const void *dato)
{
    printf("%.2f", ((double) (*(const float *) dato)));
}

void imprimir_double(const void *dato)
{
    printf("%.2lf", *(const double *) dato);
}

void imprimir_char(const void *dato)
{
    printf("%c", *(const char *) dato);
}

void imprimir_bool(const void *dato)
{
    printf("%s", ((*(const bool *) dato) ? "true" : "false"));
}

void imprimir_cadena(const void *dato)
{
    printf("%s", (const char *) dato);
}

int comparar_int(const void *a, const void *b)
{
    int x = *(const int *) a;
    int y = *(const int *) b;

    return ((x > y) - (x < y));
}

int comparar_float(const void *a, const void *b)
{
    float x = *(const float *) a;
    float y = *(const float *) b;

    return ((x > y) - (x < y));
}

int comparar_double(const void *a, const void *b)
{
    double x = *(const double *) a;
    double y = *(const double *) b;

    return ((x > y) - (x < y));
}

int comparar_char(const void *a, const void *b)
{
    char x = *(const char *) a;
    char y = *(const char *) b;

    return ((x > y) - (x < y));
}

int comparar_bool(const void *a, const void *b)
{
    return (((int) (*(const bool *) a)) - ((int) (*(const bool *) b)));
}

int comparar_cadena(const void *a, const void *b)
{
    return (strcmp((const char *) a, (const char *) b));
}
