#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para una pila de cantidad 0. */
static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    pila_t *pila = pila_crear();
    print_test("Crear pila", pila != NULL);

    printf("\nCONDICIÓN DE BORDE\n");
    print_test("Desapilar una pila recién creada devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("Ver el tope de una pila recién creada devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("Pila_esta_vacia es verdadero", pila_esta_vacia(pila));

    pila_destruir(pila);
}

static void prueba_apilar_elementos(void) {
    printf("\nINICIO DE PRUEBAS APILAR y DESAPILAR ELEMENTOS\n");

    pila_t *pila = pila_crear();
    int valor;
    char otro_valor;

    print_test("Apilar 1 elemento", pila_apilar(pila, &valor));
    print_test("El elemento apilado es el tope", pila_ver_tope(pila) == &valor);
    print_test("Apilar 2 elementos", pila_apilar(pila, &otro_valor));
    print_test("El elemento 2 es el tope", pila_ver_tope(pila) == &otro_valor);
    print_test("Apilar 3 elementos", pila_apilar(pila, &valor));
    print_test("El elemento 3 es el tope", pila_ver_tope(pila) == &valor);
    print_test("Desapilo el elemento 3", pila_desapilar(pila) == &valor);
    print_test("El elemento 2 es el tope", pila_ver_tope(pila) == &otro_valor);
    print_test("Desapilo el elemento 2", pila_desapilar(pila) == &otro_valor);
    print_test("El elemento 1 es el tope", pila_ver_tope(pila) == &valor);
    print_test("Desapilo el elemento 1", pila_desapilar(pila) == &valor);
    print_test("La pila está vacía", pila_esta_vacia(pila));
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("Desapilar una pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("El tope de una pila vacía es igual a NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
}

static void prueba_de_volumen(void) {
    printf("\nINICIO DE PRUEBAS VOLUMEN\n");

    pila_t *pila = pila_crear();
    int valor;

    for (int i = 0; i <= 999; i++) {
        if (i == 999) {
            print_test("Puedo apilar todos los elementos", pila_apilar(pila, &valor) && pila_ver_tope(pila) == &valor);
        }
        else if (!pila_apilar(pila, &valor) || pila_ver_tope(pila) != &valor) {
            print_test("La prueba falló", false);
            break;
        }
    }

    for (int i = 999; i >= 0; i--) {
        if (i == 0) {
            print_test("Puedo desapilar todos los elementos", pila_desapilar(pila) == &valor && pila_ver_tope(pila) == NULL);
        }
        else if (pila_ver_tope(pila) != &valor || pila_desapilar(pila) != &valor) {
            print_test("La prueba falló", false);
            break;
        }
    }

    pila_destruir(pila);
}

static void prueba_apilar_NULL(void) {
    printf("\nINICIO DE PRUEBAS APILAR ELEMENTO NULL\n");

    pila_t *pila = pila_crear();

    print_test("Apilo NULL", pila_apilar(pila, NULL));
    print_test("La pila no está vacía", pila_esta_vacia(pila) == false);
    print_test("El nuevo tope es el primer elemento", pila_ver_tope(pila) == NULL);
    print_test("Desapilo NULL", pila_desapilar(pila) == NULL);
    print_test("La pila queda vacía", pila_esta_vacia(pila));

    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_apilar_elementos();
    prueba_de_volumen();
    prueba_apilar_NULL();
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
