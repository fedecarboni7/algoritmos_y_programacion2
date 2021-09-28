#include "pila.h"
#include "testing.h"
#include <stdio.h>

static void prueba_cola_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

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
