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
    pila_t *pila = calloc(1, sizeof(pila_t));
    if (pila == NULL) return NULL;
    return pila;
}

void pila_destruir(pila_t *pila){
    while (!pila_esta_vacia(pila))
        pila_desapilar(pila);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    if (pila->cantidad == 0) return true;
    return false;
}

bool pila_apilar(pila_t *pila, void *valor){

}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;
    return pila->datos[:-1];
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)) return NULL;

}
