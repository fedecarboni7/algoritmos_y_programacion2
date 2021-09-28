#include "pila.h"
#include "testing.h"
#include <stdio.h>

/* Pruebas para una pila de cantidad 0. */
static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    pila_t *pila = pila_crear();
    print_test("crear pila", pila != NULL);

    printf("\nCONDICIÓN DE BORDE\n");
    print_test("desapilar una pila recién creada devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("ver el tope de una pila recién creada devuelve NULL", pila_ver_tope(pila) == NULL);
    print_test("pila_esta_vacia es verdadero", pila_esta_vacia(pila) == true);


    pila_destruir(pila);
}

static void prueba_apilar_elementos(void) {
    printf("\nINICIO DE PRUEBAS APILAR y DESAPILAR ELEMENTOS\n");

    pila_t *pila = pila_crear();
    int valor;
    char otro_valor;

    print_test("apilar 1 elemento", pila_apilar(pila, &valor) == true);
    print_test("el elemento apilado es el tope", pila_ver_tope(pila) == &valor);
    print_test("apilar 2 elementos", pila_apilar(pila, &otro_valor) == true);
    print_test("el elemento 2 es el tope", pila_ver_tope(pila) == &otro_valor);
    print_test("apilar 3 elementos", pila_apilar(pila, &valor) == true);
    print_test("el elemento 3 es el tope", pila_ver_tope(pila) == &valor);
    print_test("desapilo el elemento 3", pila_desapilar(pila) == &valor);
    print_test("el elemento 2 es el tope", pila_ver_tope(pila) == &otro_valor);
    print_test("desapilo el elemento 2", pila_desapilar(pila) == &otro_valor);
    print_test("el elemento 1 es el tope", pila_ver_tope(pila) == &valor);
    print_test("desapilo el elemento 1", pila_desapilar(pila) == &valor);
    print_test("la pila está vacía", pila_esta_vacia(pila) == true);
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("desapilar una pila vacía devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("el tope de una pila vacía es igual a NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
}

static void prueba_de_volumen(void) {
    printf("\nINICIO DE PRUEBAS VOLUMEN\n");

    pila_t *pila = pila_crear();
    int valor;
    char otro_valor;

    for(int i = 0; i <= 999; i++) {
        if(i == 0) {
            print_test("apilo el primer elemento", pila_apilar(pila, &valor) == true);
            print_test("el tope es el primer elemento", pila_ver_tope(pila) == &valor);
        }
        if(i == 499) {
            print_test("apilo el elemento 500", pila_apilar(pila, &otro_valor) == true);
            print_test("el nuevo tope es el elemento 500", pila_ver_tope(pila) == &otro_valor);
        }
        if(i == 999) {
            print_test("apilo el elemento 1000", pila_apilar(pila, &otro_valor) == true);
            print_test("el nuevo tope es el elemento 1000", pila_ver_tope(pila) == &otro_valor);
        }
        else if(!pila_apilar(pila, &valor) || pila_ver_tope(pila) != &valor) {
            printf("El elemento N° %i falló", i);
        }
    }

    for(int i = 999; i >= 0; i--) {
        if(i == 999) {
            print_test("desapilo el elemento 1000", pila_desapilar(pila) == &otro_valor);
            print_test("el nuevo tope es el elemento 999", pila_ver_tope(pila) == &valor);
        }
        if(i == 499) {
            print_test("desapilo el elemento 500", pila_desapilar(pila) == &otro_valor);
            print_test("el nuevo tope es el elemento 499", pila_ver_tope(pila) == &valor);
        }
        if(i == 0) {
            print_test("desapilo el primer elemento", pila_desapilar(pila) == &valor);
            print_test("el tope es igual a NULL", pila_ver_tope(pila) == NULL);
            print_test("la pila queda vacía", pila_esta_vacia(pila) == true);
        }
        else if(pila_ver_tope(pila) != &valor || pila_desapilar(pila) != &valor) {
            printf("No se pudo desapilar el elemento N° %i \n", i);
        }
    }
    pila_destruir(pila);
}

static void prueba_apilar_NULL(void) {
    printf("\nINICIO DE PRUEBAS APILAR ELEMENTO NULL\n");

    pila_t *pila = pila_crear();

    print_test("apilo NULL", pila_apilar(pila, NULL) == true);
    print_test("el nuevo tope es el primer elemento", pila_ver_tope(pila) == NULL);
    print_test("desapilo NULL", pila_desapilar(pila) == NULL);
    print_test("la pila queda vacía", pila_esta_vacia(pila) == true);

    pila_destruir(pila);
}

static void prueba_desapilar_todo(void) {
    printf("\nINICIO DE PRUEBAS DESAPILAR TODO\n");

    pila_t *pila = pila_crear();
    int valor;

    print_test("apilo un elemento", pila_apilar(pila, &valor) == true);
    print_test("el nuevo tope es el primer elemento", pila_ver_tope(pila) == &valor);
    print_test("desapilo el elemento", pila_desapilar(pila) == &valor);
    print_test("la pila queda vacía", pila_esta_vacia(pila) == true);
    print_test("el nuevo tope es NULL", pila_ver_tope(pila) == NULL);
    print_test("volver a desapilar devuelve NULL", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_apilar_elementos();
    prueba_de_volumen();
    prueba_apilar_NULL();
    prueba_desapilar_todo();
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
