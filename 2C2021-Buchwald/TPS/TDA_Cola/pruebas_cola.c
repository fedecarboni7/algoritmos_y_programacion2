#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>

static void prueba_cola_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    cola_t *cola = cola_crear();
    print_test("Crear cola", cola != NULL);
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("La cola está vacía", cola_esta_vacia(cola));
    print_test("Desencolar una cola recién creada devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("Ver el primer elemento de una cola recién creada devuelve NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
}

void pruebas_pila_estudiante() {
    prueba_cola_vacia();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
