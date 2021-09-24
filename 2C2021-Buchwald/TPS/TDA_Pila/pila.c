#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL) return NULL;
    pila->cantidad = 0;
    pila->capacidad = 10;
    pila->datos = malloc(pila->capacidad * sizeof(void*));
    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    return pila;
}

void pila_destruir(pila_t *pila){
    while (!pila_esta_vacia(pila))
        pila_desapilar(pila);
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    if (pila->cantidad == pila->capacidad)
        pila->capacidad *= 2;
    pila->datos = realloc(pila->datos, pila->capacidad * sizeof(void*));
    if (pila->datos == NULL) return false;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[-1];
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    pila->cantidad--;
    if (pila->cantidad * 4 <= pila->capacidad && pila->capacidad >= 20)
        pila->capacidad /= 2;
    pila->datos = realloc(pila->datos, pila->capacidad * sizeof(void*));
    if (pila->datos == NULL) return NULL;
    return pila->datos[pila->cantidad];
}
