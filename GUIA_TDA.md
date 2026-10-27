# Guía: TDA Lista, Pila y Cola en C

> Material de estudio para el Tema 03 (Tipos de Datos Abstractos) de
> Programación I / Algoritmos I (CAO302). Basado en el Tema 03 y en la Guía
> Práctica de la asignatura.

---

## 1. Qué se hizo y qué archivos hay

Se amplió tu librería `mis_librerias` (que solo tenía una lista de `int` con dos
operaciones) a **tres TDA completos**, y se agregó una segunda librería
**genérica** para poder hacer listas, pilas y colas de `int`, `float`, `bool`,
`char` o `struct`.

| Archivo | Qué contiene |
|---|---|
| `mis_librerias.h` | Tipos `Nodo`, `Lista`, `Pila`, `Cola` y **todos** los prototipos. |
| `mis_librerias.c` | Implementación de la Lista, Pila y Cola de `int`. |
| `tda_generico.h` | Tipos `ListaG`, `PilaG`, `ColaG` y sus prototipos (cualquier tipo). |
| `tda_generico.c` | Implementación genérica con `void *`, `sizeof` y `memcpy`. |
| `prueba_tda.c` | Programa de pruebas: **69 verificaciones** de todo. |
| `lista.c` | Tu ejemplo original, adaptado a la nueva librería. |
| `Makefile` | Reglas para compilar los dos programas. |
| `GUIA_TDA.md` | Este documento. |

Para compilar y probar:

```bash
gcc -Wall -Wextra -std=c99 lista.c mis_librerias.c -o lista.exe
gcc -Wall -Wextra -std=c99 prueba_tda.c mis_librerias.c tda_generico.c -o prueba_tda.exe
./prueba_tda.exe
```

La salida termina con `RESUMEN: 69 verificaciones OK, 0 fallos`.

---

## 2. Recordatorio: ¿qué es un TDA?

Un **Tipo de Dato Abstracto (TDA)** es la combinación de:

1. una **representación de datos** (cómo se guardan por dentro), y
2. un **conjunto de operaciones** (qué se puede hacer con ellos).

El usuario del TDA **no necesita conocer la representación**: solo usa las
operaciones. Eso permite cambiar la implementación (por ejemplo, pasar de un
arreglo a nodos enlazados) sin cambiar los programas que lo usan.

Las operaciones se clasifican así (Tema 03):

| Tipo | Qué hace | Ejemplos en esta librería |
|---|---|---|
| **Constructoras** | Crean un objeto del TDA. | `crear_lista`, `iniciar_pila`, `crear_cola` |
| **Modificadoras** | Cambian el estado. | `lista_insertar`, `apilar`, `encolar`, `invertir` |
| **Observadoras** | Consultan sin cambiar nada. | `es_vacia`, `longitud`, `consultar`, `esta`, `tope`, `frente`, `imprimir` |
| **Destructoras** | Liberan la memoria. | `vaciar_lista`, `destruir_pila`, `destruir_cola` |
| **Persistencia** | Guardan/leen en disco. | `lista_guardar`, `lista_cargar` |

### 2.1. De la especificación del Tema 03 al código en C

En la especificación las operaciones se escriben en forma funcional (por
ejemplo `insertar: Lista × Natural × Elemento → Lista`). En C se implementan
como funciones o procedimientos que reciben un **puntero** a la estructura y la
modifican (`ref` en el pseudocódigo). Esta es la correspondencia:

| TDA | Operación en la especificación | Implementación en C |
|---|---|---|
| Lista | `vacia` | `crear_lista` / `iniciar_lista` |
| Lista | `es_vacia` | `lista_es_vacia` |
| Lista | `insertar(L, p, e)` | `lista_insertar(l, p, e)` |
| Lista | `eliminar(L, p)` | `lista_eliminar(l, p, &e)` |
| Lista | `consultar(L, p)` | `lista_consultar(l, p, &e)` |
| Lista | `esta(L, e)` | `lista_esta(l, e)` / `lista_buscar(l, e)` |
| Lista | `longitud(L)` | `lista_longitud(l)` |
| Pila | `vacia` | `crear_pila` / `iniciar_pila` |
| Pila | `es_vacia` | `pila_es_vacia` |
| Pila | `apilar(P, e)` | `apilar(p, e)` |
| Pila | `desapilar(P)` | `desapilar(p, &e)` |
| Pila | `tope(P)` | `pila_tope(p, &e)` |
| Cola | `vacia` | `crear_cola` / `iniciar_cola` |
| Cola | `es_vacia` | `cola_es_vacia` |
| Cola | `encolar(C, e)` | `encolar(c, e)` |
| Cola | `desencolar(C)` | `desencolar(c, &e)` |
| Cola | `frente(C)` | `frente(c, &e)` |

Cuando la operación "devuelve" un elemento (`consultar`, `desapilar`, `tope`,
`frente`) se le pasa la dirección de una variable (`&e`) para copiarlo ahí, y
la función devuelve `1` si pudo hacerlo o `0` si la precondición no se cumplía.

> **Idea clave:** Lista, Pila y Cola son **estructuras lineales** (cada elemento
> se relaciona con uno anterior y uno siguiente). La Pila y la Cola son
> **listas restringidas**: limitan *dónde* se inserta y *dónde* se elimina.

---

## 3. TDA Lista

### 3.1. Definición

Una lista es una secuencia de cero o más elementos:

```
L = < e1, e2, e3, ..., en >
```

- `n` es la **longitud**. Si `n = 0`, la lista es vacía: `<>`.
- `e1` es el **primer** elemento y `en` el **último**.
- Cada elemento tiene una **posición** (1, 2, 3, …). En esta librería las
  posiciones empiezan en **1**, igual que en la especificación del curso.

### 3.2. Representación usada

Nodos enlazados (lista simplemente enlazada):

```
cabeza -> [10|*] -> [20|*] -> [30|NULL] <- cola
longitud = 3
```

```c
typedef struct Nodo {
    int dato;               // informacion
    struct Nodo *siguiente; // enlace al siguiente nodo
} Nodo;

typedef struct Lista {
    Nodo *cabeza;   // primer nodo
    Nodo *cola;     // ultimo nodo
    int longitud;   // cantidad de elementos
} Lista;
```

Guardar `cola` y `longitud` es una decisión de diseño:

- `cola` permite **insertar al final en O(1)** sin recorrer la lista.
- `longitud` permite responder `longitud()` en **O(1)**.

### 3.3. Operaciones (todas implementadas)

| Operación | Qué hace | Costo |
|---|---|---|
| `crear_lista()` | Reserva una `Lista` en el heap y la deja vacía. | O(1) |
| `iniciar_lista(&l)` | Inicializa una `Lista` ya declarada (en el stack). | O(1) |
| `lista_es_vacia(l)` | `1` si no hay elementos. | O(1) |
| `lista_longitud(l)` | Cantidad de elementos. | O(1) |
| `lista_insertar(l, pos, v)` | Inserta en `1 <= pos <= longitud+1`. | O(pos) |
| `lista_consultar(l, pos, &v)` | Copia el dato de `pos` en `v`. | O(pos) |
| `lista_modificar(l, pos, v)` | Cambia el dato de `pos`. | O(pos) |
| `lista_eliminar(l, pos, &v)` | Borra `pos` y devuelve su dato. | O(pos) |
| `lista_eliminar_principio(l, &v)` | Borra el primero. | O(1) |
| `lista_eliminar_final(l, &v)` | Borra el último. | O(n) |
| `lista_eliminar_valor(l, v)` | Borra **todas** las apariciones de `v`; devuelve cuántas. | O(n) |
| `lista_esta(l, v)` | `1` si `v` está. | O(n) |
| `lista_buscar(l, v)` | Posición de `v`, o `0` si no está. | O(n) |
| `lista_invertir(l)` | Da vuelta la lista. | O(n) |
| `lista_copiar(origen, destino)` | Copia los elementos. | O(n) |
| `lista_concatenar(destino, origen)` | Agrega los elementos de `origen` al final de `destino`. | O(m) |
| `lista_combinar_ordenadas(a, b, res)` | Mezcla dos listas ordenadas. | O(n+m) |
| `lista_interseccion(a, b, res)` | Elementos que están en ambas. | O(n·m) |
| `lista_esta_ordenada(l)` | `1` si está en orden no decreciente. | O(n) |
| `lista_guardar(l, "archivo.txt")` | Guarda un número por línea. | O(n) |
| `lista_cargar(l, "archivo.txt")` | Carga el archivo (vacía la lista antes). | O(n) |
| `imprimir_lista(l)` | Muestra `[10, 20, 30]  (longitud = 3)`. | O(n) |
| `vaciar_lista(l)` | Libera los nodos; la lista queda usable y vacía. | O(n) |
| `destruir_lista(l)` | Libera los nodos **y** la estructura. | O(n) |

> Para insertar al principio se usa `lista_insertar(l, 1, v)`; para insertar al
> final, `lista_insertar(l, lista_longitud(l) + 1, v)`. Los extremos son casos
> particulares de `insertar`, no operaciones aparte.

### 3.4. ¿Cuándo usar una lista?

- Cuando necesitas **acceder por posición** (`consultar(3)`).
- Cuando necesitas **insertar o eliminar en cualquier lugar**, no solo en los
  extremos.
- Cuando el orden de los elementos importa y además se van a **editar**.
- Cuando no sabes de antemano cuántos elementos habrá (crece con `malloc`).
- Ejemplos: una lista de reproducción, el inventario de un almacén, los
  pacientes de un consultorio que pueden ser reubicados, etc.

**No** conviene usarla si solo vas a insertar y sacar por un extremo: para eso
están la pila y la cola, que son más simples de usar y expresan mejor la
intención.

---

## 4. TDA Pila (Stack)

### 4.1. Definición

Una pila es una lista en la que **todo se inserta y se elimina por el mismo
extremo**, llamado **tope**. El último que entra es el primero que sale:

```
LIFO = Last In, First Out
```

El otro extremo se llama **fondo**. El único elemento visible es el del tope.

```
        tope
         |
   +-----------+
   |    30     |   <- ultimo en entrar
   |    20     |
   |    10     |   <- primero en entrar (fondo)
   +-----------+
```

### 4.2. Representación usada

La pila **reutiliza la lista**: el tope es la **cabeza** de la lista interna.

```c
typedef struct Pila {
    Lista lista;   // el tope es lista.cabeza
} Pila;
```

Por eso `apilar` es `lista_insertar(&p->lista, 1, valor)` y `desapilar` es
`lista_eliminar_principio`: ambas cosas cuestan **O(1)**.

### 4.3. Operaciones (todas implementadas)

| Operación | Qué hace | Costo |
|---|---|---|
| `crear_pila()` | Crea la pila vacía. | O(1) |
| `iniciar_pila(&p)` | Inicializa una pila ya declarada. | O(1) |
| `pila_es_vacia(p)` | `1` si no hay elementos. | O(1) |
| `pila_longitud(p)` | Cantidad de elementos. | O(1) |
| `apilar(p, v)` | **Push**: mete `v` en el tope. | O(1) |
| `desapilar(p, &v)` | **Pop**: saca el tope y lo devuelve. | O(1) |
| `pila_tope(p, &v)` | **Peek**: mira el tope sin sacarlo. | O(1) |
| `pila_contiene(p, v)` | `1` si `v` está en algún lugar de la pila. | O(n) |
| `imprimir_pila(p)` | Muestra del tope al fondo. | O(n) |
| `vaciar_pila(p)` | La deja vacía y usable. | O(n) |
| `destruir_pila(p)` | Libera nodos y estructura. | O(n) |

> `desapilar` y `pila_tope` sobre una pila vacía devuelven `0` (error) y no
> modifican nada. Es la **precondición** `¬es_vacia(P)` de la especificación.

### 4.4. ¿Cuándo usar una pila?

- **Deshacer / rehacer** (Ctrl+Z): cada acción se apila y se desapila al
  deshacer.
- **Evaluar expresiones**: convertir infija a postfija y evaluar postfija
  (ejercicios 11 y 12 de la guía).
- **Verificar paréntesis, corchetes y llaves** balanceados (ejercicio 13).
- **Simular la recursión**: una llamada recursiva se comporta como una pila de
  llamadas (por eso el "stack" del programa).
- **Recorridos con retroceso** (backtracking): laberintos, sudoku, ajedrez.
- **Historial de navegación**: atrás/adelante.

La regla mental: *"lo último que guardé es lo primero que necesito"*.

---

## 5. TDA Cola (Queue)

### 5.1. Definición

Una cola es una lista en la que se **inserta por un extremo** (el final) y se
**elimina por el otro** (el frente). El primero que entra es el primero que
sale:

```
FIFO = First In, First Out
```

```
frente                          final
  |                               |
  v                               v
[10] -> [20] -> [30] -> NULL
  ^
  sale primero
```

### 5.2. Representación usada

La cola también **reutiliza la lista**: el frente es la **cabeza** y el final
es la **cola** de la lista interna.

```c
typedef struct Cola {
    Lista lista;   // el frente es lista.cabeza, el final es lista.cola
} Cola;
```

`encolar` = `lista_insertar(&c->lista, lista_longitud(&c->lista) + 1, valor)`
(O(1) gracias al puntero `cola`) y `desencolar` = `lista_eliminar_principio`
(O(1)).

> En el Tema 03 la cola se implementa con un **vector circular**. Las dos
> representaciones son válidas: la circular aprovecha un arreglo fijo y la
> enlazada crece sin límite. El TDA es el mismo; cambia la implementación.

### 5.3. Operaciones (todas implementadas)

| Operación | Qué hace | Costo |
|---|---|---|
| `crear_cola()` | Crea la cola vacía. | O(1) |
| `iniciar_cola(&c)` | Inicializa una cola ya declarada. | O(1) |
| `cola_es_vacia(c)` | `1` si no hay elementos. | O(1) |
| `cola_longitud(c)` | Cantidad de elementos. | O(1) |
| `encolar(c, v)` | **Enqueue**: agrega `v` al final. | O(1) |
| `desencolar(c, &v)` | **Dequeue**: saca el frente y lo devuelve. | O(1) |
| `frente(c, &v)` | **Peek**: mira el frente sin sacarlo. | O(1) |
| `cola_contiene(c, v)` | `1` si `v` está en la cola. | O(n) |
| `imprimir_cola(c)` | Muestra del frente al final. | O(n) |
| `vaciar_cola(c)` | La deja vacía y usable. | O(n) |
| `destruir_cola(c)` | Libera nodos y estructura. | O(n) |

### 5.4. ¿Cuándo usar una cola?

- **Turnos y atención por orden de llegada**: banco, farmacia, aeropuerto.
- **Cola de impresión**: el primer documento enviado se imprime primero.
- **Planificación de procesos** del sistema operativo.
- **Recorridos BFS** (anchura) de árboles y grafos.
- **Buffers**: teclado, red, mensajes.
- **Simulaciones** de sistemas con servidores y clientes (ejercicio típico del
  Tema 03).

La regla mental: *"lo primero que llegó es lo primero que se atiende"*.

---

## 6. Diferencias entre Lista, Pila y Cola

| Aspecto | Lista | Pila | Cola |
|---|---|---|---|
| **Acceso** | A cualquier posición | Solo al tope | Solo al frente |
| **Inserta en** | Cualquier posición | Tope | Final |
| **Elimina de** | Cualquier posición | Tope | Frente |
| **Orden de salida** | El que tú elijas | LIFO (último en entrar, primero en salir) | FIFO (primero en entrar, primero en salir) |
| **Elemento visible** | Todos (recorriendo) | Solo el tope | Solo el frente |
| **Operaciones típicas** | `insertar`, `consultar`, `eliminar` | `apilar`, `desapilar`, `tope` | `encolar`, `desencolar`, `frente` |
| **Se usa cuando…** | Necesitas flexibilidad y posición | Necesitas revertir o anidar | Necesitas respetar el orden de llegada |
| **Costo de insertar/sacar** | O(1) en extremos, O(p) en medio | O(1) | O(1) |
| **Recorrido natural** | Del primero al último | Del tope al fondo | Del frente al final |

**En una frase:**

- La **lista** es la estructura general.
- La **pila** es una lista donde solo puedes tocar un extremo (y por eso el
  orden se invierte).
- La **cola** es una lista donde insertas por un lado y sacas por el otro (y
  por eso el orden se conserva).

---

## 7. Explicación del código, función por función

### 7.1. Crear: heap vs. stack

```c
Lista *crear_lista(void)              // pide memoria con malloc
void   iniciar_lista(Lista *l)        // inicializa una variable ya existente
```

Se ofrecen las dos formas porque en clase se usan ambas:

```c
Lista *l1 = crear_lista();   // se libera con destruir_lista(l1)
Lista  l2;
iniciar_lista(&l2);          // se libera con vaciar_lista(&l2)
```

- `destruir_lista` hace `free(l)` **además** de liberar los nodos.
- `vaciar_lista` solo libera los nodos y deja la estructura lista para usarse
  otra vez.

Mezclar ambas (por ejemplo, `destruir_lista(&l2)` con `l2` en el stack) sería
un error: se estaría haciendo `free` de memoria que no se reservó con `malloc`.

### 7.2. Insertar al principio y al final

No hay funciones aparte para los extremos: `lista_insertar` ya los resuelve.

- Al principio: `lista_insertar(l, 1, valor)`.
- Al final: `lista_insertar(l, lista_longitud(l) + 1, valor)`.

Dentro de `lista_insertar`, esos dos casos son ramas O(1):

```c
if (pos == 1) {
    nuevo->siguiente = l->cabeza;
    l->cabeza = nuevo;

    if (l->cola == NULL) {
        l->cola = nuevo;
    }
} else if (pos == (l->longitud + 1)) {
    ...
}
```

El caso "lista vacía" es el que más se olvida: si no se actualiza `cola`, la
lista queda inconsistente.

### 7.3. Insertar en una posición

`lista_insertar(l, pos, v)` acepta `1 <= pos <= longitud + 1`:

- `pos == 1` → rama O(1) para el principio.
- `pos == longitud + 1` → rama O(1) para el final.
- en medio → se camina hasta el nodo `pos-1` y se engancha el nuevo entre ese
  nodo y su siguiente.

```c
nuevo->siguiente = ant->siguiente;
ant->siguiente = nuevo;
```

El orden de esas dos líneas importa: primero se guarda el resto de la lista en
el nuevo, y después se conecta el anterior con el nuevo. Al revés se perdería
el resto.

### 7.4. Eliminar

`lista_eliminar` tiene tres casos:

1. `pos == 1`: se mueve la cabeza y, si la lista quedó vacía, `cola = NULL`.
2. `pos == longitud` (el último): además de desenlazar, hay que **retroceder
   `cola`** al nodo anterior. Si se olvida, `cola` queda apuntando a memoria
   liberada.
3. en medio: se salta el nodo (`ant->siguiente = act->siguiente`) y se hace
   `free(act)`.

En todos los casos se decrementa `longitud`.

`lista_eliminar_final` es O(n) porque, al ser una lista **simplemente**
enlazada, hay que caminar hasta el penúltimo. Si se necesitara O(1) habría que
usar una lista **doblemente** enlazada (cada nodo con `anterior` y `siguiente`).

### 7.5. Recorrer, consultar, buscar

```c
Nodo *aux = l->cabeza;
while (aux != NULL) {
    printf("%d ", aux->dato);
    aux = aux->siguiente;      // avanzar al siguiente "vagón"
}
```

- `lista_consultar` camina hasta `pos` y copia el dato.
- `lista_buscar` camina comparando y devuelve la posición (1-based) o `0`.
- `lista_esta` es simplemente `lista_buscar(...) != 0`.

Devolver `0` para "no está" es cómodo porque las posiciones válidas empiezan
en 1 (así `0` nunca es una posición real).

### 7.6. Invertir

```c
anterior = NULL;
act = l->cabeza;
while (act != NULL) {
    siguiente = act->siguiente;
    act->siguiente = anterior;   // se da vuelta al enlace
    anterior = act;
    act = siguiente;
}
l->cabeza = anterior;
l->cola = <la antigua cabeza>;
```

Son tres punteros (`anterior`, `act`, `siguiente`) para no perder el resto de
la lista al dar vuelta cada enlace.

### 7.7. Operaciones entre listas (ejercicios de la guía)

- **Concatenar**: recorre `origen` y va agregando copias al final de `destino`.
  No se comparten nodos: cada lista es dueña de su memoria.
- **Combinar ordenadas**: como mezclar dos barajas: se compara el frente de
  cada lista y se toma el menor; cuando una se acaba, se copia el resto de la
  otra.
- **Intersección**: por cada elemento de `a`, se agrega si está en `b` y aún no
  está en el resultado (para no repetirlo).
- **¿Está ordenada?**: se compara cada nodo con su siguiente; si en algún
  momento baja, no está ordenada.

### 7.8. Persistencia

`lista_guardar` escribe un número por línea:

```c
for (act = l->cabeza; act != NULL; act = act->siguiente)
    fprintf(archivo, "%d\n", act->dato);
```

`lista_cargar` vacía la lista y lee con `fscanf` hasta el final del archivo. Se
usa texto (no binario) para que el archivo se pueda abrir y revisar.

### 7.9. Pila y Cola construidas sobre la Lista

Este es el punto más importante del diseño:

```c
void apilar(Pila *p, int valor)   { lista_insertar(&p->lista, 1, valor); }
int  desapilar(Pila *p, int *v)   { return lista_eliminar_principio(&p->lista, v); }
int  pila_tope(const Pila *p, int *v) { return lista_consultar(&p->lista, 1, v); }
```

```c
void encolar(Cola *c, int valor)  { lista_insertar(&c->lista, lista_longitud(&c->lista) + 1, valor); }
int  desencolar(Cola *c, int *v)  { return lista_eliminar_principio(&c->lista, v); }
int  frente(const Cola *c, int *v){ return lista_consultar(&c->lista, 1, v); }
```

No se duplicó el código de los nodos: se **reutilizó** la Lista. Eso es
exactamente la ventaja de los TDA: la Pila y la Cola son *listas con
restricciones*, y sus operaciones se expresan con las operaciones de la Lista.
Los costos se heredan: todo lo que en la lista es O(1) en los extremos, en la
pila y en la cola también es O(1).

---

## 8. Listas, pilas y colas de `int`, `bool`, `float`, etc.

### 8.1. El problema

En C no existen las plantillas (templates) de C++. Una lista de `int` no sirve
directamente para `float` porque:

- `sizeof(int)` (4 bytes) es distinto de `sizeof(double)` (8 bytes).
- El compilador tiene que saber qué tipo hay para imprimir, comparar y asignar.

### 8.2. Las tres soluciones posibles

| Estrategia | Cómo | Ventaja | Desventaja |
|---|---|---|---|
| **Copiar la librería** | Hacer `lista_float.c` cambiando `int` por `float`. | Simple, con tipado fuerte. | Mucho código repetido. |
| **Genérica con `void *`** | Guardar copias de `tam` bytes y usar callbacks. | Una sola librería para todo. | Se pierde el chequeo de tipos del compilador; hay que pasar `sizeof`. |
| **Macros / `#include` repetido** | Generar variantes con macros. | Tipado fuerte y sin repetición. | Más difícil de leer y depurar. |

En esta carpeta está implementada la **segunda** (`tda_generico`), que es la
más usada en C y la que mejor muestra el concepto de TDA genérico.

### 8.3. Cómo funciona la versión genérica

Cada nodo guarda un `void *` (dirección de memoria "sin tipo") que apunta a una
**copia** del dato:

```c
typedef struct NodoG {
    void *dato;              // copia de tam bytes
    struct NodoG *siguiente;
} NodoG;

typedef struct ListaG {
    NodoG *cabeza, *cola;
    int longitud;
    size_t tam;              // cuántos bytes ocupa el elemento
    ImpresorTDA imprimir;    // cómo mostrarlo (puede ser NULL)
    ComparadorTDA comparar;  // cómo compararlo (puede ser NULL)
} ListaG;
```

Al insertar:

```c
nuevo->dato = malloc(tam);        // espacio para el elemento
memcpy(nuevo->dato, dato, tam);   // copia byte a byte
```

Al consultar:

```c
memcpy(salida, act->dato, tam);   // devuelve una copia
```

Al eliminar:

```c
free(act->dato);
free(act);
```

Es decir: **el TDA no sabe qué tipo guarda**, solo sabe *cuántos bytes* copiar.
Tú se lo dices al crear con `sizeof`.

### 8.4. Tamaños típicos en C

| Tipo | `sizeof` típico | Se crea con |
|---|---|---|
| `char` | 1 | `sizeof(char)` |
| `bool` (`stdbool.h`) | 1 | `sizeof(bool)` |
| `int` | 4 | `sizeof(int)` |
| `float` | 4 | `sizeof(float)` |
| `double` | 8 | `sizeof(double)` |
| `struct Persona` | el que diga `sizeof(Persona)` | `sizeof(Persona)` |

> `sizeof` se calcula en **tiempo de compilación** y puede incluir relleno
> (padding) en los `struct`. Por eso siempre se escribe `sizeof(TIPO)` y nunca
> un número "a mano".

### 8.5. Los callbacks: imprimir y comparar

La librería no puede saber si un dato es un `int` o una `Persona`. Para
mostrarlo o compararlo se le pasa una función:

```c
void imprimir_int(const void *d) { printf("%d", *(const int *) d); }
int  comparar_int(const void *a, const void *b) {
    int x = *(const int *) a, y = *(const int *) b;
    return (x > y) - (x < y);      // <0, 0 o >0
}
```

`comparar` debe devolver como `strcmp`: negativo si `a < b`, `0` si son
iguales, positivo si `a > b`. Si se pasa `NULL`, la librería compara con
`memcmp` (solo confiable para tipos simples y sin padding).

### 8.6. Ejemplos de uso

**Lista de `int`:**

```c
ListaG *l = lista_g_crear(sizeof(int), imprimir_int, comparar_int);
TDA_AGREGAR_FINAL(l, int, 10);
TDA_AGREGAR_FINAL(l, int, 20);
int x;
lista_g_consultar(l, 1, &x);          // x = 10
lista_g_imprimir(l);                  // [10, 20]  (longitud = 2)
lista_g_destruir(l);
```

**Lista de `float`:**

```c
ListaG *l = lista_g_crear(sizeof(float), imprimir_float, comparar_float);
TDA_AGREGAR_FINAL(l, float, 1.5f);
TDA_AGREGAR_FINAL(l, float, 2.25f);
float f;
lista_g_consultar(l, 2, &f);          // f = 2.25
```

**Lista de `bool` (necesita `#include <stdbool.h>`):**

```c
ListaG *l = lista_g_crear(sizeof(bool), imprimir_bool, comparar_bool);
TDA_AGREGAR_FINAL(l, bool, true);
TDA_AGREGAR_FINAL(l, bool, false);
lista_g_imprimir(l);                  // [true, false]  (longitud = 2)
```

**Lista de `char`:**

```c
ListaG *l = lista_g_crear(sizeof(char), imprimir_char, comparar_char);
TDA_AGREGAR_FINAL(l, char, 'a');
TDA_AGREGAR_FINAL(l, char, 'b');
```

**Lista de `struct`:**

```c
typedef struct { char nombre[30]; int edad; } Persona;
void imprimir_persona(const void *d);
int  comparar_persona(const void *a, const void *b);

ListaG *l = lista_g_crear(sizeof(Persona), imprimir_persona, comparar_persona);
Persona p = { "Ana", 20 };
lista_g_insertar(l, lista_g_longitud(l) + 1, &p);
```

**Pila de `float` y cola de `bool`:**

```c
PilaG *p = pila_g_crear(sizeof(float), imprimir_float, comparar_float);
TDA_APILAR(p, float, 1.1f);
float tope;
pila_g_tope(p, &tope);                // tope = 1.1

ColaG *c = cola_g_crear(sizeof(bool), imprimir_bool, comparar_bool);
TDA_ENCOLAR(c, bool, true);
bool b;
cola_g_frente(c, &b);                 // b = true
```

### 8.7. Los macros de comodidad

`TDA_AGREGAR_FINAL`, `TDA_AGREGAR_PRINCIPIO`, `TDA_APILAR` y `TDA_ENCOLAR`
evitan declarar una variable temporal:

```c
TDA_AGREGAR_FINAL(l, float, 3.14f);
```

se expande a:

```c
do {
    float tda_valor_temporal = (3.14f);
    lista_g_insertar((l), lista_g_longitud((l)) + 1, &tda_valor_temporal);
} while (0);
```

Es solo "azúcar sintáctico": el `&` y la variable temporal siguen ahí, pero
escritos por el macro. Si prefieres verlo explícito, usa la forma larga:

```c
float v = 3.14f;
lista_g_insertar(l, lista_g_longitud(l) + 1, &v);
```

### 8.8. Cuidados con la versión genérica

1. **Siempre pasar `&variable`**, nunca `variable`:
   `lista_g_insertar(l, pos, &x)` ✅ / `lista_g_insertar(l, pos, x)` ❌
2. **El `sizeof` debe coincidir con lo que se guarda**:
   si creas con `sizeof(int)` y guardas un `float`, se copian 4 bytes, pero se
   interpretan mal al imprimir.
3. **Comparar `float`/`double` con cuidado**: `0.1 + 0.2 != 0.3`. Para
   igualdad usa una tolerancia:
   ```c
   int iguales(float a, float b) { return fabs(a - b) < 1e-6f; }
   ```
   (En las pruebas de esta carpeta, comparar `3.3f` contra el literal falló por
   la representación binaria; se guardó el esperado en otra variable `float`.)
4. **Structs con `memcmp`**: puede fallar por bytes de relleno. Mejor pasar un
   `comparar_persona` que compare campo por campo.
5. **Cadenas**: si guardas `char *` solo se copia el puntero, no el texto. Para
   guardar texto, usa un arreglo de tamaño fijo (`char nombre[30]`) o pide
   memoria aparte y libera a mano.

---

## 9. Cómo compilar

Con `gcc` directamente:

```bash
gcc -Wall -Wextra -std=c99 lista.c mis_librerias.c -o lista.exe
gcc -Wall -Wextra -std=c99 prueba_tda.c mis_librerias.c tda_generico.c -o prueba_tda.exe
```

Con el `Makefile` (si tienes `make`):

```bash
make            # compila todo
make pruebas    # solo las pruebas
make clean      # borra .exe y .o
```

`-Wall -Wextra` activa los avisos: si el compilador no dice nada, es buena
señal. `-std=c99` habilita `bool`, declaraciones en medio del bloque y
literales compuestos.

---

## 10. Errores comunes (y cómo los evita esta librería)

| Error | Qué pasa | Cómo se evita |
|---|---|---|
| Usar `l->cabeza->dato` con la lista vacía | Segfault | `lista_es_vacia` / `lista_consultar` valida |
| Olvidar actualizar `cola` al borrar el último | Puntero colgante | `lista_eliminar` lo actualiza |
| Usar posiciones desde 0 | Se pierde el primer elemento | Las posiciones son 1..n |
| Hacer `free` dos veces | Corrupción del heap | `destruir_*` una sola vez |
| No liberar los nodos | Fuga de memoria | `vaciar_*` / `destruir_*` |
| `desapilar` en pila vacía | Antes: error lógico | Devuelve `0` y no toca nada |
| Pasar `x` en vez de `&x` a la genérica | Lee una dirección inválida | Siempre `&` |
| `sizeof` equivocado | Datos corruptos | `sizeof(TIPO)` exacto |
| Comparar floats con `==` | Resultado inesperado | Tolerancia o variables |

---

## 11. Los ejercicios de la guía práctica, resueltos

La Guía Práctica del Tema 03 pide:

| Ejercicio | Solución en esta carpeta |
|---|---|
| 10a) Concatenar dos listas | `lista_concatenar(destino, origen)` |
| 10b) Invertir una lista | `lista_invertir(l)` |
| 10c) Eliminar todos los `X` | `lista_eliminar_valor(l, X)` |
| 10d) Combinar dos listas ordenadas | `lista_combinar_ordenadas(a, b, res)` |
| 10e) Intersección de dos listas | `lista_interseccion(a, b, res)` |
| 10f) Verificar si está ordenada | `lista_esta_ordenada(l)` |
| 11) Infija → postfija | Usar `Pila`: operandos a la salida; operadores a la pila según precedencia; paréntesis. |
| 12) Evaluar postfija | Usar `Pila`: los números se apilan; al leer un operador se desapilan dos y se apila el resultado. |
| 13) Paréntesis balanceados | Usar `Pila`: se apila el símbolo de apertura y se compara con el de cierre. |
| 14) Cola usando Pila | Dos pilas: una para encolar y otra para desencolar (cuando la de salida está vacía, se pasan todos). |
| 15) Cola con prioridades | Lista ordenada por prioridad: se inserta en la posición que le corresponde (mayor prioridad primero, y a igual prioridad, el que llegó antes). |

**Infija → postfija (resumen del algoritmo):**

```
para cada caracter c de la expresion:
    si c es operando:            agregar c a la salida
    si c es '(':                 apilar c
    si c es ')':                 desapilar y sacar a la salida hasta '('
    si c es operador:
        mientras la pila no este vacia y el tope tenga precedencia >= c:
            desapilar el tope a la salida
        apilar c
al final: desapilar todo lo que quede a la salida
```

**Evaluar postfija:**

```
para cada token:
    si es numero: apilar(numero)
    si es operador: b = desapilar(); a = desapilar(); apilar(a op b)
al final: el resultado es el tope
```

---

## 12. Chuleta final

```text
LISTA                          PILA (LIFO)                 COLA (FIFO)
-----                          -----------                 -----------
crear_lista()                  crear_pila()                crear_cola()
insertar(l,1,v)  -> principio  apilar(p,v)                 encolar(c,v)
insertar(l,n+1,v)-> final      desapilar(p,&v)             desencolar(c,&v)
insertar(l,pos,v)-> en medio   tope(p,&v)                  frente(c,&v)
consultar(l,pos,&v)            es_vacia / longitud         es_vacia / longitud
eliminar(l,pos,&v)             contiene                    contiene
esta / buscar / longitud       imprimir_pila               imprimir_cola
invertir / concatenar          vaciar_pila                 vaciar_cola
guardar / cargar               destruir_pila               destruir_cola
destruir_lista

GENERICO: cambiar sizeof(TIPO) y el par (imprimir_TIPO, comparar_TIPO).
```

**Para recordar cuál usar:**

- ¿Necesito **cualquier posición**? → **Lista**.
- ¿Necesito **deshacer** o **volver atrás**? → **Pila**.
- ¿Necesito **respetar el turno** de llegada? → **Cola**.

---

## 13. Estilo: returns tempranos, memoria primero y Doxygen

### 13.1. La regla actual

En este proyecto ya se permite **más de un `return`** por función. La idea es
usar el que haga el código más legible:

- **Cláusula de guarda:** si un parámetro es inválido o falta memoria, se sale
  de inmediato con `return 0;`, `return NULL;` o `return;`. Así el resto de la
  función queda sin anidar.
- **Un solo `return`:** se usa cuando el cálculo es corto y un solo punto de
  salida se lee mejor (por ejemplo, `lista_longitud`).
- **Función:** devuelve un solo valor.
- **Procedimiento:** es `void`; si necesita devolver datos, los entrega por
  punteros.
- **Memoria:** se pide y se valida antes de usar el nodo.

Ejemplo de guarda:

```c
int lista_insertar(Lista *l, int pos, int valor)
{
    Nodo *nuevo;

    if ((l == NULL) || (pos < 1) || (pos > (l->longitud + 1))) {
        return 0;
    }

    nuevo = crear_nodo(valor);

    if (nuevo == NULL) {
        return 0;
    }

    ...
    return 1;
}
```

La ventaja es que el "camino feliz" queda al mismo nivel y no dentro de tres
`if` anidados.

### 13.2. Técnicas para evitar el segundo `return` (referencia)

Si en algún momento se vuelve a exigir un solo `return`, estas son las técnicas:

**a) Variable de resultado.** Se declara al principio, se inicializa en el valor
"no se pudo" y se cambia solo si todo salió bien:

```c
int lista_insertar(Lista *l, int pos, int valor)
{
    int exito = 0;
    ...
    if (condiciones) {
        ...
        exito = 1;
    }
    return exito;
}
```

**b) Condicionales anidados.** En vez de salir cuando algo falla, se entra
cuando todo está bien:

```c
/* antes: dos returns */
if (l == NULL) {
    return 0;
}
... resto ...
return 1;

/* después: un solo return */
if (l != NULL) {
    ... resto ...
}
return 1;
```

**c) Bandera en la condición del `while`.** Para buscar sin `return` anticipado:

```c
int lista_buscar(const Lista *l, int valor)
{
    int pos = 0;
    const Nodo *act;
    int i = 1;

    if (l != NULL) {
        act = l->cabeza;
        while (act != NULL && pos == 0) {   /* se detiene al encontrar */
            if (act->dato == valor) {
                pos = i;
            }
            act = act->siguiente;
            i++;
        }
    }
    return pos;
}
```

`break` también sirve para salir del ciclo (no es un `return`), pero la bandera
en la condición es más fácil de leer y no necesita `break`.

**d) Limpieza al final.** Si se reservan varios recursos, se liberan al final
comprobando si existen (`free(NULL)` no hace nada, así que es seguro):

```c
int procesar(void)
{
    int exito = 0;
    Nodo *a = NULL;
    Nodo *b = NULL;

    a = crear_nodo(1);
    if (a != NULL) {
        b = crear_nodo(2);
        if (b != NULL) {
            /* ... trabajar ... */
            exito = 1;
        }
    }
    free(b);                        /* free(NULL) no hace nada */
    free(a);
    return exito;
}
```

En C la variante clásica para no anidar tanto es `goto limpieza;`, que salta a
un único bloque final que libera todo. Es un solo punto de salida, pero muchos
profesores prefieren los `if` anidados; para el curso, usa los `if`.

### 13.3. Antes y después en este proyecto

**`crear_nodo`:**

```c
/* antes: dos returns */
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

/* despues: un return, y la memoria se valida primero */
static Nodo *crear_nodo(int valor)
{
    Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));

    if (nuevo != NULL) {
        nuevo->dato = valor;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}
```

**Procedimiento de impresión:**

```c
/* antes */
void imprimir_lista(const Lista *l)
{
    if (l == NULL || l->cabeza == NULL) {
        printf("La lista esta vacia.\n");
        return;                    /* salida anticipada */
    }
    ...
}

/* despues */
void imprimir_lista(const Lista *l)
{
    if (l != NULL && l->cabeza != NULL) {
        ...
    } else {
        printf("La lista esta vacia.\n");
    }
}
```

### 13.4. ¿Hay casos en los que esto no se pueda hacer?

**En C, estrictamente imposible, no.** Cualquier función se puede reescribir con
un solo `return` usando una variable de resultado, banderas y condicionales
anidados. Pero hay situaciones en las que el estilo **pierde claridad o
rendimiento**, y conviene saberlo:

| Caso | ¿Se puede? | Comentario |
|---|---|---|
| **Búsqueda en una lista** | Sí | Con `while (... && pos == 0)` o `break`. Sin pérdida de rendimiento. |
| **Varios `malloc` encadenados** | Sí | Hay que liberar lo reservado si falla el siguiente: `if` anidados o `goto limpieza`. Es donde más se anida. |
| **Recursión** | Sí | `if (casoBase) r = ...; else r = f(...); return r;`. |
| **`void` que debe abortar a mitad** | Sí | Se anida el resto dentro de un `if`. No se usa `return;`. |
| **`main` con códigos de error** | Sí | `int codigo = 0; ... return codigo;`. |
| **Callbacks (`comparar`, `imprimir`)** | Sí | Un solo `return` con `if/else`. |
| **Devolver varios valores de distinto tipo** | **No en C** | Una función solo tiene un tipo de retorno. Se usa un `struct` (un valor) o un procedimiento con varios punteros. |
| **`exit()`, `longjmp`, señales** | No aplica | No son `return`: terminan el programa o saltan fuera de la función. |
| **Funciones muy largas** | Sí, pero… | El anidamiento puede volverse ilegible ("flecha"). En código de curso no debería pasar. |
| **Profesor que también prohíbe `break` y `goto`** | Sí | Con banderas y variables de estado; el código queda más feo, pero se puede. |

**El único caso realmente imposible es devolver varios valores de tipos
distintos con un solo `return`**, porque el lenguaje no lo permite. La solución
es empaquetarlos en un `struct` (que sigue siendo *un* valor) o usar un
procedimiento con parámetros por referencia.

### 13.5. El matiz de "memoria primero"

Pedir la memoria antes que nada es correcto **para el nodo nuevo**, pero hay que
distinguir dos cosas:

1. **Validar los parámetros** (barato): si `l` es `NULL` o la posición es
   inválida, no tiene sentido reservar memoria.
2. **Reservar y validar la memoria** antes de enganchar el nodo.

El orden correcto es:

```c
if (l != NULL && pos >= 1 && pos <= l->longitud + 1) {  /* 1. parametros */
    nuevo = crear_nodo(valor);                          /* 2. memoria     */
    if (nuevo != NULL) {                                /* 3. validar     */
        ... enganchar ...                               /* 4. usar        */
    }
}
```

Si se reserva antes de validar la posición, se gasta un `malloc`/`free` inútil
cuando la posición es inválida. Y si se reserva antes de comprobar `l`, se
pierde la memoria cuando `l` es `NULL`. Por eso "memoria primero" significa
**antes de usar el nodo**, no antes de validar los parámetros.

En funciones que reservan **varios** nodos (copiar, concatenar), no basta con
"validar primero": si el tercer `malloc` falla, hay que liberar los dos
anteriores. Ese es el caso donde el `goto limpieza` o los `if` anidados con
`free` condicional son obligatorios.

### 13.6. Si el profesor exige procedimientos puros

La librería usa funciones que devuelven un estado (`1`/`0`) y, además, escriben
el dato por puntero:

```c
int lista_consultar(const Lista *l, int pos, int *valor);
```

Eso sigue devolviendo **un solo valor** (el estado), pero si tu profesor
considera que "si hay puntero de salida debe ser `void`", la versión
procedimiento sería:

```c
void lista_consultar(const Lista *l, int pos, int *valor, int *ok)
{
    const Nodo *act;
    int i;

    *ok = 0;
    if (l != NULL && valor != NULL && pos >= 1 && pos <= l->longitud) {
        act = l->cabeza;
        for (i = 1; i < pos; i++) {
            act = act->siguiente;
        }
        *valor = act->dato;
        *ok = 1;
    }
}
```

Y se usa así:

```c
int dato;
int ok;
lista_consultar(l, 2, &dato, &ok);
if (ok) {
    printf("El dato es %d\n", dato);
}
```

Es más verboso, pero cumple al 100 % la regla "procedimiento = `void` + todo por
referencia". Si tu profesor prefiere esa forma, se puede cambiar toda la API;
solo hay que actualizar las llamadas en [prueba_tda.c](prueba_tda.c).

### 13.7. Lo que se aplicó en esta librería

- Las funciones usan **returns tempranos** cuando simplifican: parámetros
  inválidos, falta de memoria o lista vacía se resuelven con una guarda.
- Las funciones cortas (`lista_longitud`, `lista_es_vacia`, etc.) mantienen un
  solo `return` porque se leen bien así.
- La memoria se pide y se valida antes de enganchar el nodo.
- Las búsquedas devuelven la posición apenas encuentran el valor.
- Hay una línea en blanco entre los bloques lógicos de cada función, para que
  el código no quede amontonado.
- Las expresiones compuestas van entre paréntesis: `(l != NULL) && (pos >= 1)`,
  `(pos <= (l->longitud + 1))`, `((x > y) - (x < y))`, `((total_fallos == 0) ? 0 : 1)`.
- Los archivos `.h` tienen comentarios **Doxygen** con `@brief`, `@param`,
  `@return`, `@note` y `@pre`.
- Las pruebas siguen dando **69 verificaciones OK, 0 fallos**.

### 13.8. Comentarios Doxygen en los `.h`

Cada función y procedimiento de [mis_librerias.h](mis_librerias.h) y
[tda_generico.h](tda_generico.h) tiene un bloque como este:

```c
/**
 * @brief Inserta un valor en una posición determinada.
 * @param l     Lista destino.
 * @param pos   Posición de inserción, entre 1 y longitud+1.
 * @param valor Valor que se guarda.
 * @return 1 si se insertó; 0 si la posición es inválida o no hay memoria.
 * @note Complejidad O(pos); en pos = 1 o pos = longitud+1 es O(1).
 */
int lista_insertar(Lista *l, int pos, int valor);
```

Las etiquetas usadas son:

| Etiqueta | Para qué sirve |
|---|---|
| `@file` | Nombre y propósito del archivo. |
| `@brief` | Qué hace la función en una línea. |
| `@param` | Qué es y qué recibe cada parámetro. |
| `@return` | Qué devuelve y qué significa cada valor. |
| `@note` | Aclaraciones (complejidad, memoria, liberación). |
| `@pre` | Precondición que debe cumplirse antes de llamar. |
| `@code` / `@endcode` | Ejemplo de uso (en los archivos de cabecera). |

Con eso se puede generar documentación con Doxygen, y de paso el `.h` queda
como contrato legible sin tener que mirar el `.c`.

---

*Fin de la guía.*
