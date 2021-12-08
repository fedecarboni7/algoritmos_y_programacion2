#include "lista.h"
#include <stdlib.h>

// Definición del struct nodo.

typedef struct nodo {
    void* dato;
    struct nodo* prox;    
} nodo_t;

// Definición del struct lista.

struct lista {
    struct nodo* nodo_inicio;
    struct nodo* nodo_fin;
    size_t largo;
};

// Definición del struct lista_iter.

struct lista_iter {
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t *lista_crear(void) {
    lista_t *lista = malloc(sizeof(lista_t));
    lista->largo = 0;
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;
    return lista;
}

nodo_t* nodo_crear(void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return NULL;
    nodo->dato = dato;
    nodo->prox = NULL;
    return nodo;
}

void* nodo_destruir(nodo_t *nodo) {
    void *dato = nodo->dato;
    free(nodo);
    return dato;
}

bool lista_esta_vacia(const lista_t *lista) {
    return lista->largo == 0;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)) {
    while (!lista_esta_vacia(lista)) {
        void *elemento = lista_borrar_primero(lista);
        if (destruir_dato) destruir_dato(elemento);
    }
    free(lista);
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->nodo_fin = nodo;
    }
    else {
        nodo->prox = lista->nodo_inicio;
    }
    lista->nodo_inicio = nodo;
    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t *nodo = nodo_crear(dato);
    if (!nodo) return false;
    if (lista_esta_vacia(lista)) {
        lista->nodo_inicio = nodo;
    }
    else {
        lista->nodo_fin->prox = nodo;
    }
    lista->nodo_fin = nodo; 
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    void* dato_anterior = lista->nodo_inicio->dato;
    nodo_t* nodo_aux = lista->nodo_inicio;
    if (lista->largo == 1) {
        lista->nodo_fin = NULL;
    }
    lista->nodo_inicio = lista->nodo_inicio->prox;
    lista->largo--;
    free(nodo_aux);
    return dato_anterior;
}

void *lista_ver_ultimo(const lista_t* lista) {
    return lista_esta_vacia(lista) ? NULL : lista->nodo_fin->dato;
}

void *lista_ver_primero(const lista_t *lista) {
    return lista_esta_vacia(lista) ? NULL : lista->nodo_inicio->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t *actual = lista->nodo_inicio;
    while (actual != NULL) {
        if (!visitar(actual->dato, extra)) {
            return; 
        }
        actual = actual->prox; 
    }
}

lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t *lista_iter = malloc(sizeof(lista_iter_t));
    if (!lista_iter) return NULL;
    lista_iter->lista = lista;
    lista_iter->actual = lista->nodo_inicio;
    lista_iter->anterior = NULL;
    return lista_iter; 
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;
    return iter->actual->dato;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista)) return NULL;
    if (lista_iter_al_final(iter)) return NULL;
    if (iter->actual == iter->lista->nodo_inicio) {
        lista_iter_avanzar(iter);
        return lista_borrar_primero(iter->lista);
    }
    nodo_t* nodo_aux = iter->actual;
    void* dato_anterior = iter->actual->dato;
    if (iter->actual == iter->lista->nodo_fin) {
        iter->lista->nodo_fin = iter->anterior;
        iter->actual = iter->actual->prox;
    } else {
        iter->anterior->prox = iter->actual->prox;
        iter->actual = iter->anterior->prox;
    }
    free(nodo_aux);
    iter->lista->largo--;
    return dato_anterior;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return false;
    iter->anterior = iter->actual;
    if (iter->actual == iter->lista->nodo_fin) {
        iter->actual = NULL;
    } else {
        iter->actual = iter->actual->prox;
    }
    return true;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    if (lista_esta_vacia(iter->lista)) return true;
    return iter->actual == NULL;
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    if (iter->actual == iter->lista->nodo_inicio) {
        lista_insertar_primero(iter->lista, dato);
        iter->actual = iter->lista->nodo_inicio;
        return true;
    }
    if (lista_iter_al_final(iter)) {
        lista_insertar_ultimo(iter->lista, dato);
        iter->actual = iter->lista->nodo_fin;
        return true;
    }
    nodo_t* nodo_insertar = nodo_crear(dato);
    if (!nodo_insertar) return false;
    nodo_insertar->prox = iter->actual;
    iter->anterior->prox = nodo_insertar;
    iter->actual = nodo_insertar;
    iter->lista->largo++;
    return true;
}
