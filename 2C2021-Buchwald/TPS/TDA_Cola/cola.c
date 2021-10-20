#include "cola.h"
#include <stdlib.h>

// Definición del struct cola.

struct cola {
    struct nodo* nodo_inicio;
    struct nodo* nodo_fin;
};

// Definición del struct nodo.

typedef struct nodo {
    void* dato;
    struct nodo* prox;    
} nodo_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t *cola_crear(void) {
    cola_t *cola = calloc(1, sizeof(cola_t));
    return cola;
}

nodo_t* nodo_crear(void* valor) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    while (!cola_esta_vacia(cola)) {
        void *elemento = cola_desencolar(cola);
        if (destruir_dato) destruir_dato(elemento);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {
    return cola->nodo_inicio == NULL;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t* nodo = nodo_crear(valor);
    if (!nodo) return false;
    if (cola_esta_vacia(cola)) {
        cola->nodo_inicio = nodo;
    }
    else {
        cola->nodo_fin->prox = nodo;
    }
    cola->nodo_fin = nodo;
    cola->nodo_fin->prox = NULL;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    return cola_esta_vacia(cola) ? NULL : cola->nodo_inicio->dato;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) return NULL;
    void* dato_anterior = cola->nodo_inicio->dato;
    nodo_t* nodo_aux = cola->nodo_inicio;
    if (cola->nodo_inicio == cola->nodo_fin) {
        cola->nodo_inicio = NULL;
        cola->nodo_fin = NULL;
    }
    else {
        cola->nodo_inicio = cola->nodo_inicio->prox;
    }
    free(nodo_aux);
    return dato_anterior;
}
