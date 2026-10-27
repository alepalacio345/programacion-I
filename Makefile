# --- VARIABLES ---
# El compilador que estamos usando
CC = gcc
# El nombre del archivo final que queremos crear
EJECUTABLE = lista.exe
# Todos los archivos .c que conforman el proyecto
ARCHIVOS = lista.c mis_librerias.c

# --- REGLA PRINCIPAL ---
$(EJECUTABLE): $(ARCHIVOS)
	$(CC) $(ARCHIVOS) -o $(EJECUTABLE)