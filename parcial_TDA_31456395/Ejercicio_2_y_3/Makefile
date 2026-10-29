CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: simulador_de_tiempos.exe descifrado_de_comunicaciones.exe

simulador_de_tiempos.exe: simulador_de_tiempos.c mis_librerias.c mis_librerias.h
	$(CC) $(CFLAGS) simulador_de_tiempos.c mis_librerias.c -o simulador_de_tiempos.exe

descifrado_de_comunicaciones.exe: descifrado_de_comunicaciones.c mis_librerias.c mis_librerias.h
	$(CC) $(CFLAGS) descifrado_de_comunicaciones.c mis_librerias.c -o descifrado_de_comunicaciones.exe

clean:
	del /Q *.exe *.o 2>NUL
