#include <stdio.h>

// n: cantidad de discos
// origen: varilla de donde salen
// destino: varilla a donde queremos que lleguen
// auxiliar: varilla que usamos de apoyo
void hanoi(int n, char origen, char destino, char auxiliar) {
    
    // CASO BASE: Si solo hay 1 disco, simplemente lo movemos directo.
    // Esto es vital, recuerda que "sólo se puede mover un disco cada vez".
    if (n == 1) {
        printf("Mover disco de la varilla %c a la varilla %c\n", origen, destino);
        return;
    }else{

        
        // PASO 1 (Magia recursiva 1): 
        // Movemos los n-1 discos que estorban hacia la varilla AUXILIAR.
        // Fíjate cómo intercambiamos las letras: el destino temporal ahora es 'auxiliar'
        hanoi(n - 1, origen, auxiliar, destino);

        // PASO 2 (El movimiento real):
        // Movemos el disco más grande (el que quedó en el fondo) al destino final.
        printf("Mover disco de la varilla %c a la varilla %c\n", origen, destino);

        // PASO 3 (Magia recursiva 2):
        // Agarramos los n-1 discos que estaban en la auxiliar y los pasamos al DESTINO.
        // Ahora el origen temporal es la varilla 'auxiliar'
        hanoi(n - 1, auxiliar, destino, origen);


    }

}

int main() {
    int cantidad_discos = 3;
    
    printf("Pasos para resolver las Torres de Hanoi con %d discos:\n\n", cantidad_discos);
    
    // Llamamos a la función:
    // 3 discos, desde la varilla 'A', hasta la 'C', usando la 'B' de comodín.
    hanoi(cantidad_discos, 'A', 'C', 'B');
    
    return 0;
}