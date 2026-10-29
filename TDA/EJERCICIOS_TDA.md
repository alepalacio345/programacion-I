# Ejercicios de Listas, Pilas y Colas

> Ejercicios encontrados en la carpeta `TDA`, extraídos de:
> - [Tema03_GuiaPractica FACYT.pdf](<TDA/Tema03_GuiaPractica FACYT.pdf>) — ejercicios 10 a 15.
> - [Parcial 2 algoritmos - 17_03_2026 (2).pdf](<TDA/Parcial 2 algoritmos - 17_03_2026 (2).pdf>) — ejercicios 1 a 3.
>
> La idea es resolverlos **primero en papel** (especificación Pre/Post y algoritmo),
> y después implementarlos con [mis_librerias.h](mis_librerias.h) o
> [tda_generico.h](tda_generico.h).

## Cómo practicar

1. Escribe la **especificación**: sintaxis, precondiciones y postcondiciones.
2. Escribe el **algoritmo** usando solo las operaciones del TDA (sin tocar nodos).
3. Calcula la **complejidad**.
4. Prueba con: lista/pila/cola vacía, un solo elemento, duplicados, elemento que
   no está, y el caso normal.
5. Recién después pasa a C.

---

## 1. Ejercicios de Listas

### 10a) Concatenar dos listas

**Enunciado:** dadas dos listas `A` y `B`, agregar todos los elementos de `B`
al final de `A`.

**TDA:** Lista.
**Pista:** recorre `B` por posición con `consultar` y agrega cada elemento al
final de `A` con `insertar(A, longitud(A) + 1, v)`.
**Cuidado:** si `A` y `B` son la misma lista, el algoritmo se complica; decide
si la operación modifica `B` o no y déjalo escrito en la especificación.

**Complejidad esperada:** O(m), con m = longitud de `B`.

---

### 10b) Invertir una lista

**Enunciado:** dada una lista `L`, dejarla con los elementos en orden inverso.

**TDA:** Lista.
**Pista:** si solo puedes usar operaciones del TDA, crea una lista auxiliar y
ve insertando cada elemento de `L` en la **posición 1** de la auxiliar. Luego
copia la auxiliar sobre `L`.
**Alternativa:** si el profesor permite manejar nodos, usa tres punteros
(`anterior`, `actual`, `siguiente`).
**Cuidado:** lista vacía y lista de un solo elemento.

**Complejidad esperada:** O(n).

---

### 10c) Eliminar todos los elementos iguales a X

**Enunciado:** eliminar de la lista todas las apariciones del valor `X`.

**TDA:** Lista.
**Pista:** recorre por posición con un índice `pos`:
- si `consultar(pos) == X`, llama a `eliminar(pos)` y **no avances** el índice
  (los elementos se corren a la izquierda);
- si no, avanza a `pos + 1`.

**Cuidado:** no incrementar después de eliminar; probar con `X` repetido al
principio, al final y en toda la lista.

**Complejidad esperada:** O(n²) si `eliminar(pos)` es O(pos); O(n) si se recorre
con punteros.

---

### 10d) Combinar dos listas ordenadas

**Enunciado:** dadas `A` y `B` ordenadas de menor a mayor, construir `R`
ordenada con todos los elementos de ambas.

**TDA:** Lista.
**Pista:** como mezclar dos barajas: dos índices `i` y `j`, comparas
`consultar(A, i)` con `consultar(B, j)`, insertas el menor al final de `R` y
avanzas el índice correspondiente. Cuando una se acaba, copias el resto de la
otra.
**Cuidado:** elementos repetidos; decidir si se conservan (normalmente sí).

**Complejidad esperada:** O(n + m).

---

### 10e) Intersección de dos listas

**Enunciado:** construir una lista con los elementos que están en `A` y en `B`.

**TDA:** Lista.
**Pista:** para cada elemento `v` de `A`, si `esta(B, v)` y **no** está todavía
en el resultado, agrégalo al final. La segunda condición evita repetidos.
**Cuidado:** listas con duplicados; decidir si la intersección es con o sin
repetidos.

**Complejidad esperada:** O(n·m) con las operaciones del TDA.

---

### 10f) Verificar si una lista está ordenada

**Enunciado:** indicar si la lista está en orden no decreciente.

**TDA:** Lista.
**Pista:** recorre las posiciones 1 a `longitud-1` y compara `consultar(i)` con
`consultar(i+1)`. Si en algún momento el primero es mayor, no está ordenada.
**Cuidado:** lista vacía o de un elemento: está ordenada.

**Complejidad esperada:** O(n).

---

## 2. Ejercicios de Pilas

### 11) Convertir una expresión de infija a postfija

**Enunciado:** dada una expresión infija bien formada (por ejemplo
`A + B * C`), convertirla a postfija (`A B C * +`).

**TDA:** Pila.
**Pista (la da la guía):**
1. Si el carácter es operando, va directo a la salida.
2. Si es `(`, se apila.
3. Si es `)`, se desapila y se saca a la salida hasta encontrar `(`.
4. Si es operador: mientras el tope sea un operador de precedencia mayor o
   igual, se desapila a la salida; luego se apila el operador leído.
5. Al final, se desapila todo lo que quede.

**Precedencia:** `^` > `*` y `/` > `+` y `-`.
**Cuidado:** paréntesis; operadores de igual precedencia (asociatividad);
expresión vacía.
**Prueba:** `(A + B) * C` → `A B + C *`.

**Complejidad esperada:** O(n).

---

### 12) Evaluar una expresión en postfija

**Enunciado:** dada una expresión postfija, calcular su valor. Ejemplo:
`6 2 4 - *` → `(2 - 4) * 6 = -12`.

**TDA:** Pila (de números).
**Pista:** recorre los tokens:
- si es número, se apila;
- si es operador, se desapilan **dos**: primero `b`, después `a`; se apila
  `a op b`.

El orden importa: para `-` y `/` no es lo mismo `a - b` que `b - a`.
**Cuidado:** división por cero, expresión inválida, pila con más de un valor al
final.

**Complejidad esperada:** O(n).

---

### 13) Verificar paréntesis, corchetes y llaves

**Enunciado:** dada una expresión con `()`, `[]` y `{}`, indicar si los
anidamientos son correctos.

**TDA:** Pila.
**Pista:** si el símbolo es de apertura, se apila. Si es de cierre:
- si la pila está vacía, error;
- si el tope no es el de apertura correspondiente, error;
- si coincide, se desapila.
Al final, la pila debe quedar vacía.

**Prueba con los ejemplos de la guía:**
- Correcta: `{X + [Y – (A + B)] * C – [(D + E) – F]} / (J – (K – (M – N)))`
- Incorrecta: `{X + [Y – (A + B)] * C – ](D + E) – F]} / (J – (K – (M – N))`

**Complejidad esperada:** O(n).

---

### Parcial 1) Lista de reproducción usando SOLO pilas

**Enunciado (resumen):** implementar un TDA que simule un reproductor:
- insertar una canción en la lista de reproducción;
- ejecutar la canción actual;
- pasar a la siguiente;
- volver a la anterior;
- consultar el estado actual;
- limpiar la lista.

**Restricción:** la implementación debe usar **exclusivamente pilas**.
Además se pide “encolar elementos para su repetición programada”.

**Por qué es interesante:** una pila solo permite LIFO, pero un reproductor
necesita avanzar y retroceder. La solución típica usa **dos pilas**:
- una pila `historial` con lo que ya se reprodujo;
- una pila `pendientes` con lo que falta por reproducir.

`siguiente`: pasa la actual a `historial` y saca la próxima de `pendientes`.
`anterior`: pasa la actual a `pendientes` y saca la anterior de `historial`.

**Reto extra:** “encolar para repetición” es una operación FIFO; si solo puedes
usar pilas, tienes que implementar una cola con dos pilas. Eso conecta este
ejercicio con el 14.

**Pista para insertar al final:** si `pendientes` es una pila, el próximo a
reproducir está en el tope; para insertar al final de la lista tendrías que
pasar todos los elementos a una pila auxiliar, apilar el nuevo y devolverlos.
Piensa si el enunciado realmente pide insertar al final o si se puede insertar
como “próxima”.

---

### Parcial 3) TDA DIÁPOLO Balanceado

**Enunciado (resumen):** definir formalmente un TDA `DIÁPOLO` con:
- `crear()`
- `es_vacio()`
- `insertar_izq(e)`
- `insertar_der(e)`
- `eliminar_izq()`
- `eliminar_der()`

**Propiedad de balance:** la cantidad de elementos del extremo izquierdo y del
derecho no puede diferir en más de 1. Si una operación rompe el balance, la
estructura se reorganiza internamente.

**Qué practicas:** es un **deque** (cola doble) con un invariante. Debes
escribir:
- sintaxis (dominio y rango de cada operación);
- precondiciones y postcondiciones;
- el invariante `|#izq − #der| ≤ 1`;
- qué hace la reorganización cuando se desbalancea.

**Pista de implementación:** dos pilas (`izq` y `der`) o una lista doblemente
enlazada. Si usas dos pilas, `eliminar_izq` saca del tope de `izq`; si al
insertar `izq` queda con dos elementos más que `der`, pasa uno de `izq` a
`der`.

---

## 3. Ejercicios de Colas

### 14) Implementar el TDA Cola usando el TDA Pila

**Enunciado:** implementar todas las operaciones de Cola (`encolar`,
`desencolar`, `frente`, `es_vacia`) usando solo pilas y sus operaciones.

**Pista:** dos pilas, `entrada` y `salida`.
- `encolar`: apilar en `entrada`.
- `desencolar`/`frente`: si `salida` está vacía, pasar **todos** los elementos
  de `entrada` a `salida` (desapilar de una y apilar en la otra); luego trabajar
  con el tope de `salida`.

**Cuidado:** no pasar elementos si `salida` ya tiene; si lo haces, se invierte
el orden.
**Complejidad:** `encolar` O(1); `desencolar` O(1) amortizado.

---

### 15) TDA ColaP (cola con prioridades)

**Enunciado:** los clientes tienen prioridad de 1 a M. Siempre se atiende al de
mayor prioridad; entre igual prioridad, al que llegó primero. Implementar
`vaciaCP`, `es_vaciaCP`, `encolarCP(C, e, p)`, `desencolarCP`, `frenteCP`.

**TDA:** Lista (o un arreglo de M colas).
**Pista con Lista:** guarda pares `(elemento, prioridad)` ordenados por
prioridad descendente. Para insertar, busca la primera posición cuya prioridad
sea **menor** que `p` e inserta ahí; si todas son mayores o iguales, inserta al
final. Así se respeta FIFO entre prioridades iguales.
**Alternativa:** M colas, una por prioridad; `encolarCP` encola en la cola de su
prioridad y `desencolarCP` busca desde la prioridad más alta la primera cola no
vacía.

**Complejidad:** con lista, insertar O(n) y desencolar O(1); con M colas,
insertar O(1) y desencolar O(M) en el peor caso.

---

### Parcial 2) `rotar_hasta(e)` en una cola

**Enunciado:** agregar a la Cola la operación `rotar_hasta(e)`: mueve elementos
del frente al final hasta que `e` quede en el frente. Si `e` no está, la cola
queda **igual**. Ejemplo: `⟨1,2,3,4,5⟩`, `e = 4` → `⟨4,5,1,2,3⟩`.

**Restricciones:**
- solo operaciones del TDA Cola (`encolar`, `desencolar`, `frente`, `es_vacia`,
  `longitud`);
- una sola pasada, O(n);
- si `e` no está, no cambiar la estructura.

**Pista:** no saques `e` de la cola. Mira el frente; si no es `e`, desencola y
vuelve a encolar ese elemento. Repite como máximo `n` veces:

```text
n = longitud(C)
i = 0
mientras i < n y frente(C) != e:
    v = frente(C)
    desencolar(C)
    encolar(C, v)
    i = i + 1
```

Si `e` está, el ciclo se detiene cuando queda al frente. Si no está, das `n`
vueltas y la cola vuelve a su orden original.

**Cuidado:** cola vacía; `e` repetido (se usa la primera aparición); no usar
estructuras auxiliares.

---

## 4. Orden sugerido para practicar

1. **10a, 10b, 10c** — lo básico de listas: recorrer, insertar, eliminar.
2. **10d, 10e, 10f** — combinación, intersección y verificación.
3. **13** — pila para balanceo (fácil y muy usado en exámenes).
4. **11 y 12** — expresiones con pila (clásicos de parcial).
5. **14** — cola con dos pilas (une los dos TDAs).
6. **15** — cola con prioridades (listas ordenadas).
7. **Parcial 2** — rotación de cola en O(n).
8. **Parcial 1 y 3** — nivel examen: dos pilas para el reproductor y deque con
   invariante de balance.

## 5. Checklist para cada solución

- [ ] ¿Escribí la especificación Pre/Post?
- [ ] ¿Usé solo operaciones del TDA (sin tocar `Nodo` ni `cabeza`)?
- [ ] ¿Contemplé estructura vacía?
- [ ] ¿Contemplé un solo elemento?
- [ ] ¿Contemplé duplicados?
- [ ] ¿Contemplé el elemento que no está?
- [ ] ¿Calculé la complejidad?
- [ ] ¿Liberé la memoria al terminar?

---

*Si quieres, el siguiente paso puede ser resolver uno de estos ejercicios juntos,
empezando por la especificación y el pseudocódigo, sin pasar todavía a C.*
