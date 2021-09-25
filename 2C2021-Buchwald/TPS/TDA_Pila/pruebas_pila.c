#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para una pila de cantidad 0. */
static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    pila_t *pila = pila_crear();
    print_test("crear pila", pila != NULL);
    print_test("la pila está vacía", pila_esta_vacia(pila) == true);
    print_test("desapilar una pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("ver el tope de una pila vacía devuelve NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
}

static void prueba_apilar_elementos(void){
    printf("INICIO DE PRUEBAS APILAR ELEMENTOS\n");

    pila_t *pila = pila_crear();
    int valor;
    char otro_valor;
    print_test("apilar un elemento devuelve true", pila_apilar(pila, &valor) == true);
    print_test("el elemento apilado es el tope", pila_ver_tope(pila) == &valor);
    print_test("la pila no está vacía", pila_esta_vacia(pila) == false);
    print_test("apilar 2 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 3 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 4 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 5 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 6 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 7 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 8 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 9 elementos devuelve true", pila_apilar(pila, &valor) == true);
    print_test("apilar 10 elementos devuelve true", pila_apilar(pila, &otro_valor) == true);
    print_test("el ultimo elemento apilado es el tope", pila_ver_tope(pila) == &otro_valor);
    print_test("desapilo el ultimo elemento y lo devuelvo", pila_desapilar(pila) == &otro_valor);
    print_test("el tope cambió", pila_ver_tope(pila) == &valor);
    print_test("desapilo el ultimo elemento 9 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 8 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 7 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 6 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 4 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 3 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 2 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilo el ultimo elemento 1 y lo devuelvo", pila_desapilar(pila) == &valor);
    print_test("desapilar una pila vacía devuelve NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_apilar_elementos();
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
