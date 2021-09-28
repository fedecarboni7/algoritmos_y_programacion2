#include "cola.h"
#include <stdlib.h>

// Definición del struct cola.

struct cola {
    
       // Cantidad de elementos almacenados.
      // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void) {

}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {

}

bool cola_esta_vacia(const cola_t *cola) {

}

bool cola_encolar(cola_t *cola, void *valor) {

}

void *cola_ver_primero(const cola_t *cola) {

}

void *cola_desencolar(cola_t *cola) {

}