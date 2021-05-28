VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2
CC = gcc
CFLAGS =-g -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror  -I cabeceras

all: clean valgrind

minidemo: abb.c minidemo.c
	$(CC) $(CFLAGS) abb.c minidemo.c -o minidemo 2>&1

pruebas: abb.c abb_pruebas.c
	$(CC) $(CFLAGS) abb.c pruebas.c -o pruebas 2>&1

valgrind: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

clean:
	rm -f minidemo pruebas_chanutron 2>&1
