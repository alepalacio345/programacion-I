#include <stdio.h>
#include <stdlib.h>
#include "mis_librerias.h"

/* ============================================================================
 * MIS_LIBRERIAS.C
 * ----------------------------------------------------------------------------
 * Implementacion de los TDA Lista, Pila y Cola con nodos enlazados.
 *
 * ESTILO:
 *   - Se usan returns tempranos (clausulas de guarda) cuando simplifican.
 *   - La memoria se reserva y se valida ANTES de enganchar el nodo.
 *   - Las expresiones compuestas llevan parentesis.
 *   - Hay lineas en blanco entre bloques logicos.
 * ========================================================================== */

/* ------------------------- funciones auxiliares -------------------------- */

static Nodo *crear_nodo(int valor)
{
    Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->dato = valor;
    nuevo->siguiente = NULL;

    return nuevo;
}

/* =============================== TDA LISTA =============================== */

Lista *crear_lista(void)
{
    Lista *l = (Lista *) malloc(sizeof(Lista));

    if (l == NULL) {
        printf("Error: no hay memoria para crear la lista.\n");
        return NULL;
    }

    iniciar_lista(l);

    return l;
}

void iniciar_lista(Lista *l)
{
    if (l == NULL) {
        return;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

int lista_es_vacia(const Lista *l)
{
    return ((l == NULL) || (l->cabeza == NULL));
}

int lista_longitud(const Lista *l)
{
    return ((l == NULL) ? 0 : l->longitud);
}

int lista_insertar(Lista *l, int pos, int valor)
{
    Nodo *nuevo;
    Nodo *ant;
    int i;

    /* Guarda 1: parametros y posicion. */
    if ((l == NULL) || (pos < 1) || (pos > (l->longitud + 1))) {
        return 0;
    }

    /* Guarda 2: memoria. */
    nuevo = crear_nodo(valor);

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

int lista_consultar(const Lista *l, int pos, int *valor)
{
    const Nodo *act;
    int i;

    if ((l == NULL) || (valor == NULL) || (pos < 1) || (pos > l->longitud)) {
        return 0;
    }

    act = l->cabeza;

    for (i = 1; i < pos; i++) {
        act = act->siguiente;
    }

    *valor = act->dato;

    return 1;
}

int lista_modificar(Lista *l, int pos, int nuevo)
{
    Nodo *act;
    int i;

    if ((l == NULL) || (pos < 1) || (pos > l->longitud)) {
        return 0;
    }

    act = l->cabeza;

    for (i = 1; i < pos; i++) {
        act = act->siguiente;
    }

    act->dato = nuevo;

    return 1;
}

int lista_eliminar(Lista *l, int pos, int *valor)
{
    Nodo *ant;
    Nodo *act;
    int i;

    if ((l == NULL) || (pos < 1) || (pos > l->longitud)) {
        return 0;
    }

    if (pos == 1) {
        return lista_eliminar_principio(l, valor);
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

    if (valor != NULL) {
        *valor = act->dato;
    }

    free(act);
    l->longitud--;

    return 1;
}

int lista_eliminar_principio(Lista *l, int *valor)
{
    Nodo *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        return 0;
    }

    act = l->cabeza;
    l->cabeza = act->siguiente;

    if (l->cabeza == NULL) {
        l->cola = NULL;
    }

    if (valor != NULL) {
        *valor = act->dato;
    }

    free(act);
    l->longitud--;

    return 1;
}

int lista_eliminar_final(Lista *l, int *valor)
{
    Nodo *ant;
    Nodo *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        return 0;
    }

    if (l->longitud == 1) {
        return lista_eliminar_principio(l, valor);
    }

    ant = l->cabeza;

    while (ant->siguiente != l->cola) {
        ant = ant->siguiente;
    }

    act = l->cola;
    ant->siguiente = NULL;
    l->cola = ant;

    if (valor != NULL) {
        *valor = act->dato;
    }

    free(act);
    l->longitud--;

    return 1;
}

int lista_esta(const Lista *l, int valor)
{
    return (lista_buscar(l, valor) != 0);
}

int lista_buscar(const Lista *l, int valor)
{
    const Nodo *act;
    int pos = 1;

    if (l == NULL) {
        return 0;
    }

    act = l->cabeza;

    while (act != NULL) {
        if (act->dato == valor) {
            return pos;
        }

        act = act->siguiente;
        pos++;
    }

    return 0;
}

int lista_eliminar_valor(Lista *l, int valor)
{
    int eliminados = 0;
    Nodo *act;
    Nodo *ant = NULL;
    Nodo *sig;

    if (l == NULL) {
        return 0;
    }

    act = l->cabeza;

    while (act != NULL) {
        if (act->dato == valor) {
            sig = act->siguiente;

            if (ant == NULL) {
                l->cabeza = sig;
            } else {
                ant->siguiente = sig;
            }

            if (act == l->cola) {
                l->cola = ant;
            }

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

void lista_invertir(Lista *l)
{
    Nodo *anterior = NULL;
    Nodo *act;
    Nodo *siguiente;

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

void lista_copiar(const Lista *origen, Lista *destino)
{
    const Nodo *act;

    if ((origen == NULL) || (destino == NULL) || (origen == destino)) {
        return;
    }

    vaciar_lista(destino);

    for (act = origen->cabeza; act != NULL; act = act->siguiente) {
        lista_insertar(destino, lista_longitud(destino) + 1, act->dato);
    }
}

void lista_concatenar(Lista *destino, const Lista *origen)
{
    const Nodo *act;
    int n;

    if ((destino == NULL) || (origen == NULL) || (destino == origen)) {
        return;
    }

    n = origen->longitud;
    act = origen->cabeza;

    while ((n > 0) && (act != NULL)) {
        lista_insertar(destino, lista_longitud(destino) + 1, act->dato);
        act = act->siguiente;
        n--;
    }
}

void lista_combinar_ordenadas(const Lista *a, const Lista *b, Lista *resultado)
{
    const Nodo *pa;
    const Nodo *pb;

    if ((a == NULL) || (b == NULL) || (resultado == NULL)) {
        return;
    }

    if ((resultado == a) || (resultado == b)) {
        return;
    }

    vaciar_lista(resultado);
    pa = a->cabeza;
    pb = b->cabeza;

    while ((pa != NULL) && (pb != NULL)) {
        if (pa->dato <= pb->dato) {
            lista_insertar(resultado, lista_longitud(resultado) + 1, pa->dato);
            pa = pa->siguiente;
        } else {
            lista_insertar(resultado, lista_longitud(resultado) + 1, pb->dato);
            pb = pb->siguiente;
        }
    }

    while (pa != NULL) {
        lista_insertar(resultado, lista_longitud(resultado) + 1, pa->dato);
        pa = pa->siguiente;
    }

    while (pb != NULL) {
        lista_insertar(resultado, lista_longitud(resultado) + 1, pb->dato);
        pb = pb->siguiente;
    }
}

void lista_interseccion(const Lista *a, const Lista *b, Lista *resultado)
{
    const Nodo *pa;

    if ((a == NULL) || (b == NULL) || (resultado == NULL)) {
        return;
    }

    if ((resultado == a) || (resultado == b)) {
        return;
    }

    vaciar_lista(resultado);

    for (pa = a->cabeza; pa != NULL; pa = pa->siguiente) {
        if ((lista_esta(b, pa->dato) != 0) &&
            (lista_esta(resultado, pa->dato) == 0)) {
            lista_insertar(resultado, lista_longitud(resultado) + 1, pa->dato);
        }
    }
}

int lista_esta_ordenada(const Lista *l)
{
    const Nodo *act;

    if (l == NULL) {
        return 1;
    }

    act = l->cabeza;

    while ((act != NULL) && (act->siguiente != NULL)) {
        if (act->dato > act->siguiente->dato) {
            return 0;
        }

        act = act->siguiente;
    }

    return 1;
}

int lista_guardar(const Lista *l, const char *ruta)
{
    FILE *archivo;
    const Nodo *act;

    if ((l == NULL) || (ruta == NULL)) {
        return 0;
    }

    archivo = fopen(ruta, "w");

    if (archivo == NULL) {
        return 0;
    }

    for (act = l->cabeza; act != NULL; act = act->siguiente) {
        fprintf(archivo, "%d\n", act->dato);
    }

    fclose(archivo);

    return 1;
}

int lista_cargar(Lista *l, const char *ruta)
{
    FILE *archivo;
    int valor;

    if ((l == NULL) || (ruta == NULL)) {
        return 0;
    }

    archivo = fopen(ruta, "r");

    if (archivo == NULL) {
        return 0;
    }

    vaciar_lista(l);

    while (fscanf(archivo, "%d", &valor) == 1) {
        lista_insertar(l, lista_longitud(l) + 1, valor);
    }

    fclose(archivo);

    return 1;
}

void imprimir_lista(const Lista *l)
{
    const Nodo *act;

    if ((l == NULL) || (l->cabeza == NULL)) {
        printf("La lista esta vacia.\n");
        return;
    }

    printf("[");

    for (act = l->cabeza; act != NULL; act = act->siguiente) {
        printf("%d", act->dato);

        if (act->siguiente != NULL) {
            printf(", ");
        }
    }

    printf("]  (longitud = %d)\n", l->longitud);
}

void vaciar_lista(Lista *l)
{
    Nodo *act;
    Nodo *siguiente;

    if (l == NULL) {
        return;
    }

    act = l->cabeza;

    while (act != NULL) {
        siguiente = act->siguiente;

        free(act);
        act = siguiente;
    }

    l->cabeza = NULL;
    l->cola = NULL;
    l->longitud = 0;
}

void destruir_lista(Lista *l)
{
    if (l == NULL) {
        return;
    }

    vaciar_lista(l);

    free(l);
}

/* =============================== TDA PILA ================================ */

Pila *crear_pila(void)
{
    Pila *p = (Pila *) malloc(sizeof(Pila));

    if (p == NULL) {
        printf("Error: no hay memoria para crear la pila.\n");
        return NULL;
    }

    iniciar_pila(p);

    return p;
}

void iniciar_pila(Pila *p)
{
    if (p == NULL) {
        return;
    }

    iniciar_lista(&p->lista);
}

int pila_es_vacia(const Pila *p)
{
    return ((p == NULL) || (p->lista.cabeza == NULL));
}

int pila_longitud(const Pila *p)
{
    return ((p == NULL) ? 0 : p->lista.longitud);
}

void apilar(Pila *p, int valor)
{
    if (p == NULL) {
        return;
    }

    lista_insertar(&p->lista, 1, valor);
}

int desapilar(Pila *p, int *valor)
{
    if (p == NULL) {
        return 0;
    }

    return lista_eliminar_principio(&p->lista, valor);
}

int pila_tope(const Pila *p, int *valor)
{
    if (p == NULL) {
        return 0;
    }

    return lista_consultar(&p->lista, 1, valor);
}

int pila_contiene(const Pila *p, int valor)
{
    return ((p == NULL) ? 0 : lista_esta(&p->lista, valor));
}

void imprimir_pila(const Pila *p)
{
    const Nodo *act;

    if ((p == NULL) || (p->lista.cabeza == NULL)) {
        printf("La pila esta vacia.\n");
        return;
    }

    printf("TOPE\n");

    for (act = p->lista.cabeza; act != NULL; act = act->siguiente) {
        printf("  | %d |\n", act->dato);
    }

    printf("FONDO\n");
}

void vaciar_pila(Pila *p)
{
    if (p == NULL) {
        return;
    }

    vaciar_lista(&p->lista);
}

void destruir_pila(Pila *p)
{
    if (p == NULL) {
        return;
    }

    vaciar_pila(p);

    free(p);
}

/* =============================== TDA COLA ================================ */

Cola *crear_cola(void)
{
    Cola *c = (Cola *) malloc(sizeof(Cola));

    if (c == NULL) {
        printf("Error: no hay memoria para crear la cola.\n");
        return NULL;
    }

    iniciar_cola(c);

    return c;
}

void iniciar_cola(Cola *c)
{
    if (c == NULL) {
        return;
    }

    iniciar_lista(&c->lista);
}

int cola_es_vacia(const Cola *c)
{
    return ((c == NULL) || (c->lista.cabeza == NULL));
}

int cola_longitud(const Cola *c)
{
    return ((c == NULL) ? 0 : c->lista.longitud);
}

void encolar(Cola *c, int valor)
{
    if (c == NULL) {
        return;
    }

    lista_insertar(&c->lista, lista_longitud(&c->lista) + 1, valor);
}

int desencolar(Cola *c, int *valor)
{
    if (c == NULL) {
        return 0;
    }

    return lista_eliminar_principio(&c->lista, valor);
}

int frente(const Cola *c, int *valor)
{
    if (c == NULL) {
        return 0;
    }

    return lista_consultar(&c->lista, 1, valor);
}

int cola_contiene(const Cola *c, int valor)
{
    return ((c == NULL) ? 0 : lista_esta(&c->lista, valor));
}

void imprimir_cola(const Cola *c)
{
    const Nodo *act;

    if ((c == NULL) || (c->lista.cabeza == NULL)) {
        printf("La cola esta vacia.\n");
        return;
    }

    printf("FRENTE -> ");

    for (act = c->lista.cabeza; act != NULL; act = act->siguiente) {
        printf("%d", act->dato);

        if (act->siguiente != NULL) {
            printf(" -> ");
        }
    }

    printf(" -> FIN\n");
}

void vaciar_cola(Cola *c)
{
    if (c == NULL) {
        return;
    }

    vaciar_lista(&c->lista);
}

void destruir_cola(Cola *c)
{
    if (c == NULL) {
        return;
    }

    vaciar_cola(c);

    free(c);
}

/* ===================== utilidades para ordenamientos ===================== */

void intercambiar(int *a, int *b)
{
    int temporal = *a;

    *a = *b;
    *b = temporal;
}
