CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: gestion_Inventario.exe

gestion_Inventario.exe: gestion_Inventario.c lista_item.c lista_item.h
	$(CC) $(CFLAGS) gestion_Inventario.c lista_item.c -o gestion_Inventario.exe

clean:
	del /Q *.exe *.o 2>NUL
