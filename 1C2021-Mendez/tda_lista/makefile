VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CC = gcc
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -I cabeceras

all: clean valgrind

minipruebas: lista.c minipruebas.c
	$(CC) $(CFLAGS) lista.c minipruebas.c -o minipruebas 2>&1

pruebas: lista.c pruebas.c
	$(CC) $(CFLAGS) lista.c pruebas.c -o pruebas 2>&1

valgrind: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

clean:
	rm -f minipruebas *.o pruebas 2>&1
