#include "cola.h"
#include <stdlib.h>

// Definición del struct cola.

typedef struct cola {
    nodo_t* nodo_inicio;
    nodo_t* nodo_fin;
} cola_t;

// Definición del struct nodo.

typedef struct nodo {
    void* dato;
    struct nodo* prox;    
} nodo_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void) {
    cola_t *cola = malloc(sizeof(cola_t));
    if (!cola) return NULL;
    return cola;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {

}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->nodo_inicio == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    if(!cola) return false;
    if(!cola->nodo_inicio) {
        nodo_t* nodo = calloc(1, sizeof(nodo_t));
        if(!nodo) return false;
        nodo->dato = valor;
        cola->nodo_inicio = nodo;
        cola->nodo_fin = nodo;
        cola->nodo_inicio->prox = cola->nodo_fin;
    }
    else {
        nodo_t* nodo = calloc(1, sizeof(nodo_t));
        if(!nodo) return false;
        nodo->dato = valor;
        cola->nodo_fin->prox = nodo;
        cola->nodo_fin = nodo;
    }
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if(cola_esta_vacia(cola)) return NULL;
    return cola->nodo_inicio->dato;
}

void *cola_desencolar(cola_t *cola) {
    if(cola_esta_vacia(cola)) return NULL;
    void* dato_anterior = cola->nodo_inicio->dato;
    nodo_t* nodo_aux = cola->nodo_inicio;
    cola->nodo_inicio = cola->nodo_inicio->prox;
    free(nodo_aux);
    return dato_anterior;
}

nodo_t* nodo_crear(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if(!nodo) return NULL;
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}