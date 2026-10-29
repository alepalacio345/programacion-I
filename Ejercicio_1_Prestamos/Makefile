CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: sistema_de_prestamos.exe

sistema_de_prestamos.exe: sistema_de_prestamos.c lista_prestamo.c lista_prestamo.h
	$(CC) $(CFLAGS) sistema_de_prestamos.c lista_prestamo.c -o sistema_de_prestamos.exe

clean:
	del /Q *.exe *.o 2>NUL
