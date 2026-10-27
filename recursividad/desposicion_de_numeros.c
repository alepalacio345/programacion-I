#include <stdio.h>

// original: El número base para imprimir bonito al principio (ej. "4 = ")
// deuda: Lo que nos falta por restar hasta llegar a 0
// maximo: El "billete" más grande que tenemos permitido usar en esta vuelta
// carrito[]: El arreglo donde anotamos los billetes que vamos usando
// posicion: Cuántos billetes llevamos metidos en el carrito
void descomponer(int original, int deuda, int maximo, int carrito[], int posicion) {
    
    // 1. EL CASO BASE (El éxito)
    // Si la deuda llegó exactamente a cero, significa que los números en el carrito
    // suman exactamente el número original. ¡Imprimimos!
    if (deuda == 0) {
        printf("%d = ", original);
        // Recorremos el carrito para imprimir cada número guardado
        for (int i = 0; i < posicion; i++) {
            if (i == posicion - 1) {
                printf("%d\n", carrito[i]); // Último número sin el "+"
            } else {
                printf("%d + ", carrito[i]); // Números intermedios con el "+"
            }
        }
        return; // Terminamos esta rama y la función retrocede sola
    }

    // 2. EL MOTOR RECURSIVO (El ciclo de intentos)
    // Vamos a intentar pagar la deuda usando números desde el 'maximo' hacia abajo hasta el 1.
    for (int i = maximo; i >= 1; i--) {
        
        // Solo metemos el número en el carrito si NO nos pasamos de la deuda
        if (deuda - i >= 0) {
            
            // Metemos el número en el carrito en la posición actual
            carrito[posicion] = i; 
            
            // MAGIA RECURSIVA: Llamamos a un clon pasándole los nuevos datos
            // - La nueva deuda es: (deuda actual - el número que acabamos de usar)
            // - El nuevo límite máximo es: 'i' (para que los siguientes números sean menores o iguales y no se repitan al revés)
            // - Avanzamos la posición del carrito en +1
            descomponer(original, deuda - i, i, carrito, posicion + 1);
        }
    }
}

int main() {
    int numero = 4;
    // Creamos un vector vacío lo suficientemente grande para aguantar los números
    int vector_historial[100]; 
    
    printf("Descomposiciones del numero %d:\n\n", numero);
    
    // Llamada inicial:
    // original = 4, deuda inicial = 4, maximo billete = 4, carrito vacio, posicion = 0
    descomponer(numero, numero, numero, vector_historial, 0);
    
    return 0;
}