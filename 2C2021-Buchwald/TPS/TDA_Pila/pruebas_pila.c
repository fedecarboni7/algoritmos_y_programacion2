#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para una pila de cantidad 0. */
static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    pila_t *pila = pila_crear();
    print_test("crear pila", pila != NULL);
    print_test("la pila está vacía" , pila_esta_vacia(pila) == true);
    print_test("desapilar una pila vacía devuelve NULL" , pila_desapilar(pila) == NULL);
    print_test("ver el tope de una pila vacía devuelve NULL" , pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
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
