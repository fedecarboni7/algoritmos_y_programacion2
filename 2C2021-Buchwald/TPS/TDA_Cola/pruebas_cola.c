#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>

static void prueba_cola_vacia(void) {
    printf("INICIO DE PRUEBAS CON COLA VACIA\n");

    cola_t *cola = cola_crear();
    print_test("Crear cola", cola != NULL);
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("La cola está vacía", cola_esta_vacia(cola));
    print_test("Desencolar una cola recién creada devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("Ver el primer elemento de una cola recién creada devuelve NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void prueba_encolar_elementos(void) {
    printf("\nINICIO DE PRUEBAS ENCOLAR y DESENCOLAR ELEMENTOS\n");

    cola_t *cola = cola_crear();
    int valor;
    char otro_valor;

    print_test("Encolar 1 elemento", cola_encolar(cola, &valor));
    print_test("El elemento encolado es el primero", cola_ver_primero(cola) == &valor);
    print_test("Encolar 2 elementos", cola_encolar(cola, &otro_valor));
    print_test("Encolar 3 elementos", cola_encolar(cola, &valor));
    print_test("Desencolo el elemento 3", cola_desencolar(cola) == &valor);
    print_test("Desencolo el elemento 2", cola_desencolar(cola) == &otro_valor);
    print_test("Desencolo el elemento 1", cola_desencolar(cola) == &valor);
    print_test("La cola está vacía", cola_esta_vacia(cola));
    
    printf("\nCONDICIÓN DE BORDE\n");
    print_test("Desencolar una cola vacía devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("El primero de una cola vacía es igual a NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
}

static void prueba_de_volumen(void) {
    printf("\nINICIO DE PRUEBAS VOLUMEN\n");

    cola_t *cola = cola_crear();
    int valor;
    bool resultado = true;

    for (int i = 0; i <= 999; i++) {
        resultado = cola_encolar(cola, &valor);
        if (!resultado) break;
    }
    print_test("Puedo encolar todos los elementos", resultado);

    for (int i = 999; i >= 0; i--) {
        if (i == 0) {
            resultado = cola_desencolar(cola) == &valor && cola_esta_vacia(cola);
            break;
        }
        resultado = cola_desencolar(cola) == &valor;
        if (!resultado) break;
    }
    print_test("Puedo desencolar todos los elementos", resultado);

    cola_destruir(cola, NULL);
}

static void prueba_encolar_NULL(void) {
    printf("\nINICIO DE PRUEBAS ENCOLAR ELEMENTO NULL\n");

    cola_t *cola = cola_crear();

    print_test("Encolo NULL", cola_encolar(cola, NULL));
    print_test("La cola no está vacía", cola_esta_vacia(cola) == false);
    print_test("El primer elemento es NULL", cola_ver_primero(cola) == NULL);
    print_test("Desencolo NULL", cola_desencolar(cola) == NULL);
    print_test("La cola queda vacía", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
}

void pila_destruir_wrapper(void* pila) {
    pila_destruir(pila);
}

static void prueba_destruccion(void) {
    printf("\nINICIO DE PRUEBAS DESTRUCCIÓN\n");

    pila_t *pila = pila_crear();
    cola_t *cola = cola_crear();
    int valor;

    print_test("Agrego elementos a una pila", pila_apilar(pila, &valor) && pila_apilar(pila, &valor) && pila_apilar(pila, &valor));
    print_test("Encolo una pila que tiene elementos", cola_encolar(cola, pila));
    print_test("El primer elemento es la pila", cola_ver_primero(cola) == pila);

    cola_destruir(cola, pila_destruir_wrapper);
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_encolar_elementos();
    prueba_de_volumen();
    prueba_encolar_NULL();
    prueba_destruccion();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
