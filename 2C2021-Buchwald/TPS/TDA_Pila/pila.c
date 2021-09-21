#include "pila.h"
#include <stdio.h>
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
    
    return pila;
}

void pila_destruir(pila_t *pila){

}

bool pila_esta_vacia(const pila_t *pila){

}

bool pila_apilar(pila_t *pila, void *valor){

}

void *pila_ver_tope(const pila_t *pila){

}

void *pila_desapilar(pila_t *pila){

}
