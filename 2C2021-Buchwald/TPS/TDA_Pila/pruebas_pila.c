#include "pila.h"
#include "testing.h"


static void prueba_pila_vacia(void) {
    pila_t *pila = pila_crear();
    // print_test( ... pila_esta_vacia(pila) ... );
}


void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    // ...
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
