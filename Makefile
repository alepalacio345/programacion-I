# ============================================================================
# Makefile del proyecto TDA (Lista, Pila y Cola)
# ----------------------------------------------------------------------------
# Uso:
#     make            -> compila los dos programas
#     make lista      -> solo el ejemplo de listas
#     make pruebas    -> solo el programa de pruebas
#     make clean      -> borra ejecutables y archivos objeto
#
# Nota: en Windows, si "make" no esta instalado, se puede compilar a mano:
#     gcc -Wall -Wextra -std=c99 lista.c mis_librerias.c -o lista.exe
#     gcc -Wall -Wextra -std=c99 prueba_tda.c mis_librerias.c tda_generico.c -o prueba_tda.exe
# 
# Nota: para usar el archivo makefile hacemos en la consola mingw32-make lista o pruebas o lo que quieras
# ============================================================================

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: lista.exe prueba_tda.exe

lista.exe: lista.c mis_librerias.c mis_librerias.h
	$(CC) $(CFLAGS) lista.c mis_librerias.c -o lista.exe

prueba_tda.exe: prueba_tda.c mis_librerias.c mis_librerias.h tda_generico.c tda_generico.h
	$(CC) $(CFLAGS) prueba_tda.c mis_librerias.c tda_generico.c -o prueba_tda.exe

lista: lista.exe

pruebas: prueba_tda.exe

clean:
	del /Q *.exe *.o 2>NUL
