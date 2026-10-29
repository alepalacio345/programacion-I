# Guía del Taller "Progra 1"

> Basada en [Taller progra 1.pdf](<Taller progra 1.pdf>). Son 4 ejercicios de
> estructuras de datos. Los archivos de ejemplo ya están creados en la raíz:
> `prestamos.txt`, `tiempos.txt`, `interceptado.txt` e `inventario.txt`.

## 1. Qué tienes hoy

| Archivo | Qué ofrece |
|---|---|
| [mis_librerias.h](mis_librerias.h) | Lista, Pila y Cola de **int** |
| `TDA/tda_generico.h` | Lista, Pila y Cola para **cualquier tipo** (`char`, `struct`, etc.) |
| `TDA/tda_generico.c` | Implementación de la versión genérica |

La librería `mis_librerias` es de enteros. La genérica está dentro de `TDA/`,
así que si la usas hay que compilar con `-I TDA` y `TDA/tda_generico.c`.

> El `Makefile` actual apunta a archivos que ya no están en la raíz. Para estos
> ejercicios conviene compilar a mano.

## 2. Ranking: de más fácil a más difícil

| Orden | Ejercicio | Dificultad | TDA principal | ¿Cambiar la librería? |
|---|---|---|---|---|
| 1 | **Ejercicio 2**: robot con quantum | Fácil | Cola de `int` | **No** |
| 2 | **Ejercicio 3**: descifrar mensaje | Fácil/Media | Lista y Pila de `char` | Sí, o usar la genérica |
| 3 | **Ejercicio 1**: préstamos con deshacer/rehacer | Media | Lista de `Prestamo` + Pila | Sí, o usar la genérica |
| 4 | **Ejercicio 4**: inventario con `struct Item` | Alta | Lista de `Item` con punteros | **Sí, obligatorio** |

**Empieza por el 2**, sigue con el 3, después el 1 y deja el 4 para el final.

---

## 3. Ejercicio 2: robot logístico (el más fácil)

**Qué pide:** leer tareas (enteros) de `tiempos.txt`. El robot atiende la
primera tarea de la cola con un quantum de 15 segundos:

- si la tarea dura 15 segundos o menos, termina y se descarta;
- si dura más de 15, se le restan 15 y vuelve al final de la cola.

**TDA:** Cola de `int`. Tu `Cola` actual sirve tal cual.

**Recorrido del programa:**

1. Crear la cola.
2. Abrir `tiempos.txt`.
3. Leer cada entero y encolarlo.
4. Imprimir el encabezado de la simulación.
5. Mientras la cola no esté vacía:
   - desencolar la tarea del frente;
   - si `tiempo <= 15`: imprimir que terminó;
   - si `tiempo > 15`: calcular `resto = tiempo - 15`, imprimir el mensaje
     con el tiempo original y el resto, y encolar `resto`.
6. Al final, imprimir que todas las tareas terminaron.
7. Destruir la cola.

**Cuidado:** en el mensaje debes mostrar el tiempo **original** de la tarea,
no el resto. Para la tarea de 45: “Procesando tarea de 45s. Restan 30s”.

**Archivo de ejemplo:** `tiempos.txt` tiene `45, 10, 20, 30, 5`, uno por línea.
El ejercicio dice “una por línea”; si el profe usa comas, hay que leer la línea
y separar por coma o usar `fscanf` con un separador.

**Sin cambios en la librería.**

---

## 4. Ejercicio 3: descifrado con Lista y Pila

**Qué pide:** leer `interceptado.txt` carácter por carácter (incluyendo
espacios), guardarlos al final de una Lista y, al recorrerla, apilar las letras.
Cuando aparece un espacio (o se acaba la lista), desapilar todo e imprimir la
palabra. No se pueden usar arreglos ni `strrev`.

**TDA:** Lista de `char` y Pila de `char`.

**Cambio de librería:** tu `mis_librerias` guarda `int`. Tienes tres caminos:

1. **Recomendado:** usar `TDA/tda_generico.c` con `sizeof(char)`,
   `imprimir_char` y `comparar_char`. No cambias la librería, solo compilas con
   la genérica.
2. Crear una `ListaChar` y una `PilaChar` copiando la librería y cambiando
   `int` por `char`. Es más código, pero queda un TDA específico de char.
3. Guardar el `char` en el `int` de la librería actual y hacer el cast al
   imprimir. Funciona, pero no es lo que pide el enunciado (que el dato sea
   `char`).

**Recorrido del programa:**

1. Crear la lista y la pila.
2. Abrir `interceptado.txt`.
3. Leer con `fgetc` hasta EOF. Por cada carácter:
   - agregarlo al final de la lista (incluido el espacio).
4. Cerrar el archivo.
5. Recorrer la lista del primer nodo al último:
   - si el carácter es letra (`isalpha`), apilarlo;
   - si es espacio (o se llega al final), desapilar todo e imprimir la palabra.
6. Imprimir al final el mensaje completo.
7. Destruir lista y pila.

**Mensajes esperados:** “Extrayendo letras a la Pila auxiliar...”, “Espacio
detectado. Palabra descifrada: ...”, “Fin de lista detectado. Palabra
descifrada: ...”, “Mensaje original: ...”.

**Cuidado:** el archivo puede terminar con salto de línea; trátalo como espacio
o ignóralo para no imprimir una palabra vacía. Prueba también con dos espacios
seguidos.

**Archivo de ejemplo:** `interceptado.txt` contiene `SOTAD ED SARUTCURTSE`;
debe producir `DATOS DE ESTRUCTURAS`.

---

## 5. Ejercicio 1: préstamos con deshacer y rehacer

**Qué pide:** leer `prestamos.txt`, donde cada línea es:

- `P <cedula> <codigoLibro> <hora>`: registrar préstamo;
- `D`: deshacer el último préstamo;
- `R`: rehacer el último préstamo deshecho.

**Reglas importantes:**

- `D` y `R` pueden repetirse en cascada.
- Si después de un `D` se registra un `P` nuevo, el historial de “deshechos” se
  invalida: ya no se puede rehacer.
- Si `D` no tiene qué deshacer o `R` no tiene qué rehacer, avisar y seguir.
- Al final, imprimir los préstamos consolidados y su cantidad.

**TDA:** Lista de `Prestamo` (activos) y Pila de `Prestamo` (deshechos).

**Cambio de librería:** `mis_librerias` solo guarda `int`, y un préstamo tiene
cédula, código y hora. Opciones:

1. **Recomendado:** usar `TDA/tda_generico.c` con `sizeof(Prestamo)` y un
   impresor propio. No cambias la librería.
2. Crear una `ListaPrestamo` y una `PilaPrestamo` específicas (nodo con
   `Prestamo dato`). Es una librería nueva, más trabajo.

**Recorrido del programa:**

1. Definir `Prestamo` (cédula, código, hora).
2. Crear la lista de activos y la pila de deshechos.
3. Abrir `prestamos.txt` y leer línea por línea con `fgets`.
4. Según la primera letra:
   - `P`: parsear los tres datos, agregar al final de activos y **vaciar la
     pila de deshechos** (regla 2).
   - `D`: si activos está vacía, alertar; si no, quitar el último de activos y
     apilarlo en deshechos.
   - `R`: si deshechos está vacía, alertar; si no, desapilar y agregar al final
     de activos.
   - línea vacía o carácter desconocido: ignorar o alertar.
5. Al final, recorrer activos e imprimir cada préstamo y el total.
6. Destruir lista y pila.

**Cuidado:** el “último préstamo” es el último de la lista de activos. Si usas
la lista genérica, `lista_g_eliminar_final` te devuelve una copia; luego la
apilas en deshechos. No confundas la pila de deshechos con la lista de activos.

**Archivo de ejemplo:** `prestamos.txt` está armado para probar:
- dos préstamos,
- un `D`,
- un `P` que invalida el rehacer,
- un `R` sin historial (debe alertar),
- varios `D` en cascada,
- un `D` con lista vacía (debe alertar),
- un `R` que recupera,
- un `P` final, un `D` y un `R`.

Al final deberían quedar el primer y el último préstamo (2 en total).

---

## 6. Ejercicio 4: inventario con `struct Item`

**Qué pide:** leer `inventario.txt` con objetos:

```text
nombre categoria durabilidad
```

La categoría es `A` (arma), `P` (poción) o `M` (material). La durabilidad va de
0 a 100. Hay que:

- insertar cada objeto al final de una lista enlazada;
- eliminar los que tengan durabilidad 0, **puenteando punteros** y liberando
  memoria;
- no crear una segunda lista;
- imprimir los sobrevivientes y contar cuántas armas, pociones y materiales
  quedan.

**TDA:** lista enlazada de `struct Item`. El struct ya trae su propio
`siguiente`, así que **no** conviene envolverlo en otro nodo.

**Cambio de librería:** **sí, obligatorio**. `mis_librerias` tiene
`Nodo { int dato; Nodo *siguiente; }`, y aquí el nodo es el `Item` completo.
La genérica tampoco es la mejor opción: guardaría una copia del `Item` dentro
de otro nodo, y el `siguiente` del `Item` quedaría duplicado. Haz un módulo
propio, por ejemplo `inventario.c`, con:

- `Item *cabeza` y `Item *cola`;
- `item_agregar_final`;
- `item_limpiar` (la limpieza);
- `item_imprimir_reporte`;
- `item_destruir`.

**Recorrido del programa:**

1. Definir el `struct Item` exactamente como lo pide el taller.
2. Inicializar `cabeza = NULL` y `cola = NULL`.
3. Abrir `inventario.txt`.
4. Leer cada línea con `fgets` y parsear con
   `sscanf(linea, "%29s %c %d", nombre, &categoria, &durabilidad)`.
5. Reservar un `Item`, copiar los datos y engancharlo al final:
   - si la lista está vacía, `cabeza = item`;
   - si no, `cola->siguiente = item`;
   - actualizar `cola`.
6. Recorrer con `actual`, `anterior` y `siguiente`:
   - si `durabilidad == 0`, desenganchar:
     - si `anterior == NULL`, `cabeza = siguiente`;
     - si no, `anterior->siguiente = siguiente`;
     - si `actual == cola`, `cola = anterior`;
     - `free(actual)`;
   - si no, avanzar `anterior = actual`.
7. Recorrer los sobrevivientes, imprimir cada uno y contar categorías.
8. Liberar los que queden.

**Cuidado:** si borras el primero o el último, actualiza `cabeza` y `cola`.
No avances `anterior` cuando borras. Prueba con todos los objetos en 0, con la
lista vacía y con un solo objeto.

**Archivo de ejemplo:** `inventario.txt` tiene 6 objetos; 3 tienen durabilidad
0. Deberían quedar `Espada_Larga` (A), `Hierro_Bruto` (M) y `Pocion_Mayor` (P):
1 arma, 1 poción y 1 material.

---

## 7. Los archivos de ejemplo

| Archivo | Contenido | Para qué sirve |
|---|---|---|
| `prestamos.txt` | 11 líneas con `P`, `D` y `R` | Probar cascadas, rehacer inválido y regla de invalidación |
| `tiempos.txt` | `45, 10, 20, 30, 5` (uno por línea) | Probar el quantum y el reencolado |
| `interceptado.txt` | `SOTAD ED SARUTCURTSE` | Debe descifrar `DATOS DE ESTRUCTURAS` |
| `inventario.txt` | 6 objetos, 3 con durabilidad 0 | Probar eliminación y conteo por categoría |

Si el profesor entrega sus propios archivos, respeta el mismo formato:
- `prestamos.txt`: una acción por línea;
- `tiempos.txt`: un entero por línea (o separados por coma, según el enunciado);
- `interceptado.txt`: una sola línea;
- `inventario.txt`: un objeto por línea, con nombre sin espacios.

## 8. Orden de trabajo recomendado

1. **Ejercicio 2**: hazlo completo, es el más corto y no requiere tocar la
   librería. Sirve para calentar.
2. **Ejercicio 3**: usa la librería genérica con `char`. Concéntrate en el
   recorrido de la lista y en el vaciado de la pila al llegar al espacio.
3. **Ejercicio 1**: primero define bien `Prestamo`, luego la lista de activos y
   la pila de deshechos. Prueba las reglas con `prestamos.txt`.
4. **Ejercicio 4**: déjalo al final. Es el que exige manejar punteros a mano y
   crear una lista específica para `Item`.

## 9. Checklist por ejercicio

- [ ] ¿Leí el archivo con el formato correcto?
- [ ] ¿Validé los datos (categoría, durabilidad, líneas vacías)?
- [ ] ¿Usé solo las operaciones del TDA o los punteros cuando el enunciado lo pide?
- [ ] ¿Liberé toda la memoria?
- [ ] ¿Probé lista/cola/pila vacía?
- [ ] ¿Probé el caso de un solo elemento?
- [ ] ¿Probé los errores (deshacer sin historial, rehacer sin pendientes)?
- [ ] ¿La salida coincide con la esperada?

## 10. Compilación

Ejercicio 2, con tu librería actual:

```bash
gcc robot.c mis_librerias.c -o robot.exe
```

Ejercicios 1 y 3, con la genérica que está en `TDA/`:

```bash
gcc descifrar.c TDA/tda_generico.c -I TDA -o descifrar.exe
gcc prestamos.c TDA/tda_generico.c -I TDA -o prestamos.exe
```

Ejercicio 4, con tu módulo propio:

```bash
gcc inventario.c -o inventario.exe
```
